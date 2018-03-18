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


//cNetGuiRemote.h


#ifndef  GUI_REMOTENET__H_
#define  GUI_REMOTENET__H_

#include "I_BinderMsg.h"
#include "I_NetGuiRemote.h"

class cNetClient;


//! class cNetGuiRemote
/** This class is used to communicate with a remote (another process) gui.
// The gui handle tasks: such server connection, tables, chat and visualization.
// Server communication is handled with cNetClient object.
*/
class cNetGuiRemote :public  I_BinderMsg,
                     public  INetGuiRemote
{
    enum eState_Main
    {
        //! initial state
        IDLE,
        //! wait connection
        LISTENING,
        //! communcation stablished with gui
        COMMUNICATING,
        //! request begin match
        TRIGGERNEWMATCH,
        //! gui is closed
        END
    };
public:
    cNetGuiRemote(void);
    ~cNetGuiRemote(void);
    //! init 
    void   Init(cNetClient* pVal);
    //! start communication with gui
    void   Start();
    //! polling function to exams received messages
    void   ProcMsgInQueue();
    //! status communication with remote gui 
    BOOL   IsTerminated(){if(m_eMainState==END)return TRUE;else return FALSE;}

// I_BinderMsg interface
    //! client is disconnected
    virtual void  ClientDisconnected(ULONG ulID);
    //! add message from player
    virtual void  AddMsg(cMsgBase* pMsgBase, cConnClient* pConnClient);
// Interface INetGuiRemote
    //! server is disconnected
    void Ntf_Net_ServerDiscon();
    //! server send an info
    void Ntf_Net_ServerInfo(LPCSTR strTextInfo);
    //! login notification result
    void Ntf_Net_LoginRes(int iResCode, LPCSTR strText);
    //! logout notification
    void Ntf_Net_LogoutRes(int iResCode, LPCSTR strText);
    //! connected to the server
    void Ntf_Net_ServerConnected();
    //! server connection error
    void Ntf_Net_ServerError(int iErrCode, LPCSTR strText);
    //! notify user connected
    void Ntf_Net_UserConnected(LPCSTR lpstrLogin, BYTE byPoints_L, BYTE byPoints_H);
    //! notify user is disconnected
    void Ntf_Net_UserDisconnected(LPCSTR lpstrUser);

private:
    static int stath_WaitConn(cNetGuiRemote* pThis)
        {return pThis->th_WaitConnections();}
    int th_WaitConnections();
    void  closeRemoteGui();
    void  examsRecCmd(cQueueMSG& MsgToProc);

private:
    //! server connection socket
    Socket*              m_pSock;
    //! meassage queue
    cQueueMsgServer      m_MsgQueue;
    //! flag of connected client
    BOOL                 m_bGuiClientConn;
    //! wait connection thread
	SDL_Thread*          m_pTh_WaitConn;
    //! remote gui process information
    PROCESS_INFORMATION    m_PiremoteGui;
    //! terminate thread accept connection flag
    BOOL                   m_bTerminateListen;
    //! netclient obj for server communication
    cNetClient*            m_pNetClient;
    //! gui remote object
    cConnClient*           m_pGUIConnClient;
    //! listen GUI thread object
    cListenDataClient*     m_pListenGui;
    //! main state
    eState_Main            m_eMainState;
};


#endif