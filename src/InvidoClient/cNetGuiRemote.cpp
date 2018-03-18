/*
    Invido
    Copyright (C) 2005  Igor Sarzi Sartori

    This library is free software; you can redistribute it and/or
    modify it under the terms of the GNU Library General Public
    License as published by the Free Software Foundation; either
    version 2 of the License, or (at your option) any later version.

    This library is distributed in the hope that it will be useful,
    but WITHOUT ANY WARRANTY; without even the implied warranty of
    MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the GNU
    Library General Public License for more details.

    You should have received a copy of the GNU Library General Public
    License along with this library; if not, write to the Free
    Foundation, Inc., 59 Temple Place, Suite 330, Boston, MA  02111-1307  USA

    Igor Sarzi Sartori
    www.invido.it
    6colpiunbucosolo@gmx.net
*/


//cNetGuiRemote.cpp

#include "StdAfx.h"

#include "win_type_global.h"
#include "Socket.h"
#include "MsgQueueServer.h"
#include "cnetguiremote.h"
#include "Log.h"
#include "cSettings.h"
#include "cListenDataClient.h"
#include "myexception.h"
#include "cMsgCMD.h"
#include "cMsgSrv_Msg.h"
#include "cProtocolNet.h"
#include "cNetClient.h"

static const char* lpszApplicationGUI = "NetRemoteGui.exe";


////////////////////////////////////////
//       cNetGuiRemote
/*! Constructor
*/
cNetGuiRemote::cNetGuiRemote(void)
{
    m_bGuiClientConn = FALSE;
    m_pSock = 0;
    m_pTh_WaitConn = 0;
    ZeroMemory( &m_PiremoteGui, sizeof(m_PiremoteGui) );
    m_bTerminateListen = FALSE;
    m_pNetClient = 0;
    m_pGUIConnClient = 0;
    m_pListenGui = 0;
    m_eMainState = IDLE;
}


////////////////////////////////////////
//       ~cNetGuiRemote
/*! Destructor
*/
cNetGuiRemote::~cNetGuiRemote()
{
    closeRemoteGui();
}


////////////////////////////////////////
//       Init
/*! Initialize stuff
*/
void cNetGuiRemote::Init(cNetClient* pVal)
{
    ASSERT(pVal);

    // listening socket for client that want to connect with the server
    m_pSock = new Socket();
    m_pSock->Init("", g_Options.Net.iPortGui); 
    
    // init queue (mutex, conditions...)
    m_MsgQueue.Init();
    m_bGuiClientConn = FALSE;
    m_pNetClient = pVal;

}


////////////////////////////////////////
//       Start
/*! Start communication with the GUI
*/
void cNetGuiRemote::Start()
{
    closeRemoteGui();

    if ( m_pSock->Open() )
    {
       TRACE("[GUIREMOTE] Open port %d, listening gui \n", g_Options.Net.iPortGui);
       m_eMainState = LISTENING;
    }
    else
    {
        TRACE("[GUIREMOTE] socket open error\n");
        CHAR ErrBuff[512];
		sprintf(ErrBuff, "[GUIREMOTE] socket open error");
		throw Error::Init(ErrBuff);
    }

    // start wait connection thread
    if (m_pTh_WaitConn == 0)
    {
        m_bTerminateListen = FALSE;
        m_pTh_WaitConn = SDL_CreateThread((LP_FNTHREAD)stath_WaitConn, this);
        SDL_Delay(100); 
    }

    if (g_Options.Net.bStartAutoRemoteGui)
    {
        STARTUPINFO si;
        
        ZeroMemory( &si, sizeof(si) );
        si.cb = sizeof(si);
        ZeroMemory( &m_PiremoteGui, sizeof(m_PiremoteGui) );
        
        // lunch application
        std::string strFileName = lpszApplicationGUI;
        if( !CreateProcess( NULL, const_cast<char*>(strFileName.c_str()),   
            NULL, NULL, FALSE, 0, NULL, NULL,&si, &m_PiremoteGui ) ) 
        {
            return;
        }
    }
}

////////////////////////////////////////
//       closeRemoteGui
/*! Close the remote gui
*/
void cNetGuiRemote::closeRemoteGui()
{
    if(m_pSock)
    {
        m_pSock->Disconnect(); 
    }

    
    m_bTerminateListen = TRUE;
    m_MsgQueue.Reset();
    if (m_pGUIConnClient)
    {
        delete m_pGUIConnClient;
        m_pGUIConnClient = 0;
    }

    if (m_pListenGui)
    {
        m_pListenGui->StopThread(); 
        SDL_Delay(100);
        delete m_pListenGui;
        m_pListenGui = 0;
    }

    Sleep(500);

    if (m_PiremoteGui.hProcess)
    {
        // stop current simulation
        TerminateProcess(m_PiremoteGui.hProcess, 0) ;
        Sleep(500);
    }

}

////////////////////////////////////////
//       th_WaitConnections
/*! Thread procedure  wait for gui remote client connections
*/
int  cNetGuiRemote::th_WaitConnections()
{
    TRACE("[GUIREMOTE]is waiting a gui connection...\n");
    ASSERT(m_pSock);
    Socket* pSockClient = 0;
    while(!m_bTerminateListen)
    {
        pSockClient = m_pSock->Accept();
		if(!pSockClient)
		{ 
            // no connection accepted
			SDL_Delay(100); 
			continue;
		}
        else
        {
            // new client initialization stuff
            TRACE("[GUIREMOTE] Connection with a new gui client \n");
            m_eMainState = COMMUNICATING;

            // listen thread init
            m_pListenGui = new cListenDataClient(this, pSockClient);
            // net gui client
            m_pGUIConnClient = new cConnClient(pSockClient, m_pListenGui);
            m_pListenGui->SetConnClient(m_pGUIConnClient);

           
            // start listening data client
            m_pListenGui->Run();
            // terminate listening thread
            m_bGuiClientConn = TRUE;
            break;
        }
        
    }
    m_pTh_WaitConn =0;
    return 0;
}

////////////////////////////////////////
//       ClientDisconnected
/*! Client disconnected notification
// \param ULONG ulID : id of the disconnected client (not used)
*/
void  cNetGuiRemote::ClientDisconnected(ULONG ulID)
{
    m_bGuiClientConn = FALSE;
    m_eMainState = END;
}



////////////////////////////////////////
//       AddMsg
/*! Add message in the main server queue. This functin is called from listen data thread.
// \param cMsgBase* pMsgBase : Message type
// \param cConnClient* pConnClient : player
*/
void  cNetGuiRemote::AddMsg(cMsgBase* pMsgBase, cConnClient* pConnClient)
{
    cQueueMSG Msg(pConnClient, pMsgBase);

    m_MsgQueue.PutMsg(Msg);
}

////////////////////////////////////////
//       ProcMsgInQueue
/*! Polling function to process all the messages in the queue received from remote GUI.
*/
void cNetGuiRemote::ProcMsgInQueue()
{
    if (m_bGuiClientConn)
    {
        // process the queue only if we are connected
        cQueueMSG MsgToProc;
        BOOL bExit = FALSE;
        while (!bExit)
        {
            m_MsgQueue.GetMsgNoSig(&MsgToProc);
            if ( MsgToProc.GetIsValid() )
            {
                // message to process
                cMsgBase::eMsgType eMsgType = MsgToProc.pMsgBase->GetType();  
                if (eMsgType == cMsgBase::CMD)
                {
                    examsRecCmd(MsgToProc);
                }
                MsgToProc.pMsgBase->Release();  
            }
            else
            {
                // no more messages in the queue
                bExit = TRUE;
            }
        }
    }
}

////////////////////////////////////////
//       examsRecCmd
/*! Exams a received command
// \param cQueueMSG& MsgToProc : message detail
*/
void cNetGuiRemote::examsRecCmd(cQueueMSG& MsgToProc)
{
    // downcasting garanted by type id
    cMsgCMD*  pMsgCMD = (cMsgCMD*)(MsgToProc.pMsgBase);

    cMsgSrv_Msg  msgResp;

    BYTE byPara1 = pMsgCMD->GetParam1();
    if (byPara1 == cProtocolNet::CMDMSG_CONNECTSRV_GUI)
    {
        // user want to connect the server
        int iPort = pMsgCMD->GetParam2() + ( pMsgCMD->GetParam3() << 8);  
        STRING strServerName = pMsgCMD->GetText();
        m_pNetClient->Connect(strServerName.c_str(), iPort);
    }
    else if (byPara1 == cProtocolNet::CMDMSG_LOGINSRV_GUI)
    {
        // user want to login
        STRING strComplete = pMsgCMD->GetText();
        STRING strLogin;
        STRING strPassword;
        char seps[]   = ";";
        char* token = strtok( (char*)strComplete.c_str() , seps );
        int iCount = 0;
        while( token != NULL )
        {
            if (iCount == 0)
            {
                strLogin = token;
                iCount++;
            }
            else
            {
                strPassword = token;
                break;
            }
            
            token = strtok( NULL, seps );
        }
        m_pNetClient->LoginServer(strLogin.c_str(), strPassword.c_str() );
    }
    else if (byPara1 == cProtocolNet::CMDMSG_LOGOUTSRV_GUI)
    {
        // user logout request
        m_pNetClient->Logout(); 
    }
    else if (byPara1 == cProtocolNet::CMDMSG_DISCONNECT_GUI)
    {
        // user want disconnect the game server
        m_pNetClient->Disconnect();
        
        cMsgCMD aMsgCmd;
        aMsgCmd.PrepareSend(cProtocolNet::CMDMSG_SRVDISCONNECTED_GUI, 0); 
        m_pGUIConnClient->m_pProto->Send(aMsgCmd);
        

    }
    else if (byPara1 == cProtocolNet::CMDMSG_DESTROYED_GUI)
    {
        // user closed the remote gui
        m_eMainState = END;
    }
    else
    {
        ASSERT(0);
    }
}


////////////////////////////////////////
//       Ntf_Net_ServerDiscon
/*! server is disconnected
*/
void cNetGuiRemote::Ntf_Net_ServerDiscon()
{
    cMsgCMD aMsgCmd;
    aMsgCmd.PrepareSend(cProtocolNet::CMDMSG_SRVDISCONNECTED_GUI, 0); 
    m_pGUIConnClient->m_pProto->Send(aMsgCmd);
}

////////////////////////////////////////
//       Ntf_Net_ServerInfo
/*!  server send an info
// \param LPCSTR strTextInfo : 
*/
void cNetGuiRemote::Ntf_Net_ServerInfo(LPCSTR strTextInfo)
{
    ASSERT(m_pGUIConnClient);

    cMsgCMD aMsgCmd;
    aMsgCmd.PrepareSend(strTextInfo, cProtocolNet::CMDMSG_SRVINFO_GUI, 0,0,0); 
    m_pGUIConnClient->m_pProto->Send(aMsgCmd);
}

////////////////////////////////////////
//       Ntf_Net_ServerConnected
/*! Connected to the game server 
*/
void cNetGuiRemote::Ntf_Net_ServerConnected()
{
    cMsgCMD aMsgCmd;
    aMsgCmd.PrepareSend(cProtocolNet::CMDMSG_SRVCONNECTED_GUI, 0); 
    m_pGUIConnClient->m_pProto->Send(aMsgCmd);
}


////////////////////////////////////////
//       Ntf_Net_ServerError
/*! Server connection error notification
// \param int iErrCode : 
// \param LPCSTR strText : 
*/
void cNetGuiRemote::Ntf_Net_ServerError(int iErrCode, LPCSTR strText)
{
    cMsgCMD aMsgCmd;
    aMsgCmd.PrepareSend(strText, cProtocolNet::CMDMSG_SRVCONNERROR_GUI, iErrCode,0,0); 
    m_pGUIConnClient->m_pProto->Send(aMsgCmd);
}

////////////////////////////////////////
//       Ntf_Net_LoginRes
/*! login notification result
// \param int iResCode : 
// \param LPCSTR strText : 
*/
void cNetGuiRemote::Ntf_Net_LoginRes(int iResCode, LPCSTR strText)
{
    cMsgCMD aMsgCmd;

    if (iResCode == cNetClient::RES_OK)
    {
        // correctly logged in
        aMsgCmd.PrepareSend(strText, cProtocolNet::CMDMSG_SRVLOGGEDIN_GUI, 0,0,0); 
        m_pGUIConnClient->m_pProto->Send(aMsgCmd);
    }
    else
    {
        aMsgCmd.PrepareSend("Login error", cProtocolNet::CMDMSG_ERRMSG_GUI, cProtocolNet::ERRCODE_LOGIN,0,0); 
        m_pGUIConnClient->m_pProto->Send(aMsgCmd);
    }
}


////////////////////////////////////////
//       Ntf_Net_UserConnected
/*! User is connected
// \param LPCSTR lpstrLogin : nick name 
// \param BYTE byPoints_L : points (low byte)
// \param BYTE byPoints_H : points (high byte)
*/
void cNetGuiRemote::Ntf_Net_UserConnected(LPCSTR lpstrLogin, BYTE byPoints_L, BYTE byPoints_H)
{
    cMsgCMD aMsgCmd;
    aMsgCmd.PrepareSend(lpstrLogin, cProtocolNet::CMDMSG_USERCONN_GUI, byPoints_L,byPoints_H,0); 
    m_pGUIConnClient->m_pProto->Send(aMsgCmd);
}


////////////////////////////////////////
//       Ntf_Net_UserDisconnected
/*! User disconnected notification
// \param LPCSTR lpstrUser : user disconnected
*/
void cNetGuiRemote::Ntf_Net_UserDisconnected(LPCSTR lpstrUser)
{
    cMsgCMD aMsgCmd;
    aMsgCmd.PrepareSend(lpstrUser, cProtocolNet::CMDMSG_USERDISC_GUI, 0,0,0); 
    m_pGUIConnClient->m_pProto->Send(aMsgCmd);
}


////////////////////////////////////////
//       Ntf_Net_LogoutRes
/*! logout notification
// \param int iResCode : 
// \param LPCSTR strText : 
*/
void cNetGuiRemote::Ntf_Net_LogoutRes(int iResCode, LPCSTR strText)
{
    cMsgCMD aMsgCmd;

    if (iResCode == cNetClient::RES_OK)
    {
        // correctly logged out
        aMsgCmd.PrepareSend(cProtocolNet::CMDMSG_SRVLOGGEDOUT_GUI, iResCode); 
        m_pGUIConnClient->m_pProto->Send(aMsgCmd);
    }
    else
    {
        aMsgCmd.PrepareSend("Logout error", cProtocolNet::CMDMSG_ERRMSG_GUI, cProtocolNet::ERRCODE_LOGOUT,0,0); 
        m_pGUIConnClient->m_pProto->Send(aMsgCmd);
    }
}





