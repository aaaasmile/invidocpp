
// cSettings.h 
// used to handle settings 
// Automatic generated header file by xml->xslt = header

#ifndef   __INVSETTINGS_INI_H_
#define   __INVSETTINGS_INI_H_  
 



#include <string>



namespace SpaceInvidoSettings
{

//! class InvidoSettings
class InvidoSettings
{
public:
    
    InvidoSettings();
    
    
    class SubAll
    {
        public:
            SubAll();
              
            //! Delay animation timer
            int iDelayTimer;
              
            //! Automatic termination hand
            int bAutoterminate;
              
            //! CPU level engine
            int iLevel;
              
            //! Kind of stack
            int iTipoMazzo;
              
            //! Language ID
            int iLanguageID;
              
            //! Music enabled
            int bMusicOn;
              
            //! Music volume
            int iMusicVolume;
              
            //! Trace debug level
            int iDebugLevel;
              
            //! Flag for using python
            int bUsePython;
              
            //! Verbose level
            int iVerbose;
              
            //! Player calls echo
            int bMyCallEcho;
              
            //! Enable sound effect
            int bSoundEffect;
              
            //! Enable foto on background
            int bFotoBack;
              
            //! Enable jpg image on splash
            int bUseSplashJpg;
              
            //! Animation speed
            int iAniSpeedLevel;
              
            //! Player name
            std::string strPlayerName;
              
    };
    
    
    
public:
    SubAll All;

    class SubNetwork
    {
        public:
            SubNetwork();
              
            //! Port server value
            int iPortServer;
              
            //! Port client value
            int iPortClient;
              
            //! Port gui value
            int iPortGui;
              
            //! Start automatically the remote gui
            int bStartAutoRemoteGui;
              
            //! Server name
            std::string strServerName;
              
            //! Peer name
            std::string strPeerName;
              
            //! Login name
            std::string strLogin;
              
            //! login password
            std::string strPassw;
              
    };
    
    
    
public:
    SubNetwork Net;


};



    //! write settings in the registry
    void    WriteProfile(const char* strKeyRoot);
    //! retrieves setting from the registry
    void    GetProfile(const char* strKeyRoot);
    
    
};//end namespace

extern SpaceInvidoSettings::InvidoSettings g_Options;

#endif
