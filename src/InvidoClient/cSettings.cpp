
// cSettings.cpp
// implementation of  settings 
// Automatic generated header file by xml->xslt = header
  

#include "StdAfx.h"
#include "cSettings.h"
#include "win_type_global.h"
#include "regkey.h"


  


 

using namespace SpaceInvidoSettings;

    
// global options object
InvidoSettings  g_Options;
    

static const char* lpszSubAll = "SubAll";
    
        
    
static const char* lpszSubAlliDelayTimer = "SubAlliDelayTimer";
    
static const char* lpszSubAllbAutoterminate = "SubAllbAutoterminate";
    
static const char* lpszSubAlliLevel = "SubAlliLevel";
    
static const char* lpszSubAlliTipoMazzo = "SubAlliTipoMazzo";
    
static const char* lpszSubAlliLanguageID = "SubAlliLanguageID";
    
static const char* lpszSubAllbMusicOn = "SubAllbMusicOn";
    
static const char* lpszSubAlliMusicVolume = "SubAlliMusicVolume";
    
static const char* lpszSubAlliDebugLevel = "SubAlliDebugLevel";
    
static const char* lpszSubAllbUsePython = "SubAllbUsePython";
    
static const char* lpszSubAlliVerbose = "SubAlliVerbose";
    
static const char* lpszSubAllbMyCallEcho = "SubAllbMyCallEcho";
    
static const char* lpszSubAllbSoundEffect = "SubAllbSoundEffect";
    
static const char* lpszSubAllbFotoBack = "SubAllbFotoBack";
    
static const char* lpszSubAllbUseSplashJpg = "SubAllbUseSplashJpg";
    
static const char* lpszSubAlliAniSpeedLevel = "SubAlliAniSpeedLevel";
    
static const char* lpszSubAllstrPlayerName = "SubAllstrPlayerName";
    
static const char* lpszSubNetwork = "SubNetwork";
    
        
    
static const char* lpszSubNetworkiPortServer = "SubNetworkiPortServer";
    
static const char* lpszSubNetworkiPortClient = "SubNetworkiPortClient";
    
static const char* lpszSubNetworkiPortGui = "SubNetworkiPortGui";
    
static const char* lpszSubNetworkbStartAutoRemoteGui = "SubNetworkbStartAutoRemoteGui";
    
static const char* lpszSubNetworkstrServerName = "SubNetworkstrServerName";
    
static const char* lpszSubNetworkstrPeerName = "SubNetworkstrPeerName";
    
static const char* lpszSubNetworkstrLogin = "SubNetworkstrLogin";
    
static const char* lpszSubNetworkstrPassw = "SubNetworkstrPassw";
    
    

//! constructor
InvidoSettings::InvidoSettings()
{

}


InvidoSettings::SubAll::SubAll()
{
        
        
    iDelayTimer = 300;
    bAutoterminate = 1;
    iLevel = 1;
    iTipoMazzo = 0;
    iLanguageID = 0;
    bMusicOn = 0;
    iMusicVolume = 80;
    iDebugLevel = 0;
    bUsePython = 0;
    iVerbose = 3;
    bMyCallEcho = 1;
    bSoundEffect = 1;
    bFotoBack = 1;
    bUseSplashJpg = 1;
    iAniSpeedLevel = 2;
    strPlayerName = "Anonimo";
    
}

InvidoSettings::SubNetwork::SubNetwork()
{
        
        
    iPortServer = 8790;
    iPortClient = 8791;
    iPortGui = 8792;
    bStartAutoRemoteGui = 1;
    strServerName = "127.0.0.1";
    strPeerName = "127.0.0.1";
    strLogin = "";
    strPassw = "";
    
}




void SpaceInvidoSettings::WriteProfile(const char* strKeyRoot)
{
    RegistryKey RegKey;
    LONG lRes;
    char buff[1024];

   
  
    strcpy(buff, strKeyRoot);
    strcat(buff, "\\");
    strcat(buff, lpszSubAll);
    lRes = RegKey.Open(HKEY_CURRENT_USER, buff);  
    if (lRes)
    {
    	lRes = RegKey.Create(HKEY_CURRENT_USER, buff);
    }
    if (!lRes)
    {
	
        RegKey.setRegDWordValue(g_Options.All.iDelayTimer,lpszSubAlliDelayTimer);
	
        RegKey.setRegDWordValue(g_Options.All.bAutoterminate,lpszSubAllbAutoterminate);
	
        RegKey.setRegDWordValue(g_Options.All.iLevel,lpszSubAlliLevel);
	
        RegKey.setRegDWordValue(g_Options.All.iTipoMazzo,lpszSubAlliTipoMazzo);
	
        RegKey.setRegDWordValue(g_Options.All.iLanguageID,lpszSubAlliLanguageID);
	
        RegKey.setRegDWordValue(g_Options.All.bMusicOn,lpszSubAllbMusicOn);
	
        RegKey.setRegDWordValue(g_Options.All.iMusicVolume,lpszSubAlliMusicVolume);
	
        RegKey.setRegDWordValue(g_Options.All.iDebugLevel,lpszSubAlliDebugLevel);
	
        RegKey.setRegDWordValue(g_Options.All.bUsePython,lpszSubAllbUsePython);
	
        RegKey.setRegDWordValue(g_Options.All.iVerbose,lpszSubAlliVerbose);
	
        RegKey.setRegDWordValue(g_Options.All.bMyCallEcho,lpszSubAllbMyCallEcho);
	
        RegKey.setRegDWordValue(g_Options.All.bSoundEffect,lpszSubAllbSoundEffect);
	
        RegKey.setRegDWordValue(g_Options.All.bFotoBack,lpszSubAllbFotoBack);
	
        RegKey.setRegDWordValue(g_Options.All.bUseSplashJpg,lpszSubAllbUseSplashJpg);
	
        RegKey.setRegDWordValue(g_Options.All.iAniSpeedLevel,lpszSubAlliAniSpeedLevel);
	
        RegKey.setRegStringValue(g_Options.All.strPlayerName.c_str(),  lpszSubAllstrPlayerName);
	
		RegKey.Close();
    }
  
    strcpy(buff, strKeyRoot);
    strcat(buff, "\\");
    strcat(buff, lpszSubNetwork);
    lRes = RegKey.Open(HKEY_CURRENT_USER, buff);  
    if (lRes)
    {
    	lRes = RegKey.Create(HKEY_CURRENT_USER, buff);
    }
    if (!lRes)
    {
	
        RegKey.setRegDWordValue(g_Options.Net.iPortServer,lpszSubNetworkiPortServer);
	
        RegKey.setRegDWordValue(g_Options.Net.iPortClient,lpszSubNetworkiPortClient);
	
        RegKey.setRegDWordValue(g_Options.Net.iPortGui,lpszSubNetworkiPortGui);
	
        RegKey.setRegDWordValue(g_Options.Net.bStartAutoRemoteGui,lpszSubNetworkbStartAutoRemoteGui);
	
        RegKey.setRegStringValue(g_Options.Net.strServerName.c_str(),  lpszSubNetworkstrServerName);
	
        RegKey.setRegStringValue(g_Options.Net.strPeerName.c_str(),  lpszSubNetworkstrPeerName);
	
        RegKey.setRegStringValue(g_Options.Net.strLogin.c_str(),  lpszSubNetworkstrLogin);
	
        RegKey.setRegStringValue(g_Options.Net.strPassw.c_str(),  lpszSubNetworkstrPassw);
	
		RegKey.Close();
    }
  
    
  
}


void SpaceInvidoSettings::GetProfile(const char* strKeyRoot)
{
    RegistryKey RegKey;
    LONG lRes;
	char buff[1024];
	
    lRes = RegKey.Open(HKEY_CURRENT_USER, strKeyRoot);  
    if (!lRes)
    {
  
        strcpy(buff, strKeyRoot);
        strcat(buff, "\\");
        strcat(buff, lpszSubAll);
        RegKey.Close();
        lRes = RegKey.Open(HKEY_CURRENT_USER, buff);  
        if (!lRes)
        {
    
           g_Options.All.iDelayTimer = RegKey.getRegDWordValue(300, lpszSubAlliDelayTimer );
    
           g_Options.All.bAutoterminate = RegKey.getRegDWordValue(1, lpszSubAllbAutoterminate );
    
           g_Options.All.iLevel = RegKey.getRegDWordValue(1, lpszSubAlliLevel );
    
           g_Options.All.iTipoMazzo = RegKey.getRegDWordValue(0, lpszSubAlliTipoMazzo );
    
           g_Options.All.iLanguageID = RegKey.getRegDWordValue(0, lpszSubAlliLanguageID );
    
           g_Options.All.bMusicOn = RegKey.getRegDWordValue(0, lpszSubAllbMusicOn );
    
           g_Options.All.iMusicVolume = RegKey.getRegDWordValue(80, lpszSubAlliMusicVolume );
    
           g_Options.All.iDebugLevel = RegKey.getRegDWordValue(0, lpszSubAlliDebugLevel );
    
           g_Options.All.bUsePython = RegKey.getRegDWordValue(0, lpszSubAllbUsePython );
    
           g_Options.All.iVerbose = RegKey.getRegDWordValue(3, lpszSubAlliVerbose );
    
           g_Options.All.bMyCallEcho = RegKey.getRegDWordValue(1, lpszSubAllbMyCallEcho );
    
           g_Options.All.bSoundEffect = RegKey.getRegDWordValue(1, lpszSubAllbSoundEffect );
    
           g_Options.All.bFotoBack = RegKey.getRegDWordValue(1, lpszSubAllbFotoBack );
    
           g_Options.All.bUseSplashJpg = RegKey.getRegDWordValue(1, lpszSubAllbUseSplashJpg );
    
           g_Options.All.iAniSpeedLevel = RegKey.getRegDWordValue(2, lpszSubAlliAniSpeedLevel );
    
           g_Options.All.strPlayerName = RegKey.getRegStringValue("Anonimo", lpszSubAllstrPlayerName);
    
        }
        else
        {
        	RegKey.Create(HKEY_CURRENT_USER, buff); 
        }
  
        strcpy(buff, strKeyRoot);
        strcat(buff, "\\");
        strcat(buff, lpszSubNetwork);
        RegKey.Close();
        lRes = RegKey.Open(HKEY_CURRENT_USER, buff);  
        if (!lRes)
        {
    
           g_Options.Net.iPortServer = RegKey.getRegDWordValue(8790, lpszSubNetworkiPortServer );
    
           g_Options.Net.iPortClient = RegKey.getRegDWordValue(8791, lpszSubNetworkiPortClient );
    
           g_Options.Net.iPortGui = RegKey.getRegDWordValue(8792, lpszSubNetworkiPortGui );
    
           g_Options.Net.bStartAutoRemoteGui = RegKey.getRegDWordValue(1, lpszSubNetworkbStartAutoRemoteGui );
    
           g_Options.Net.strServerName = RegKey.getRegStringValue("127.0.0.1", lpszSubNetworkstrServerName);
    
           g_Options.Net.strPeerName = RegKey.getRegStringValue("127.0.0.1", lpszSubNetworkstrPeerName);
    
           g_Options.Net.strLogin = RegKey.getRegStringValue("", lpszSubNetworkstrLogin);
    
           g_Options.Net.strPassw = RegKey.getRegStringValue("", lpszSubNetworkstrPassw);
    
        }
        else
        {
        	RegKey.Create(HKEY_CURRENT_USER, buff); 
        }
  
    }
    else
    {
    	RegKey.Create(HKEY_CURRENT_USER, strKeyRoot); 
    }
    RegKey.Close();
}
