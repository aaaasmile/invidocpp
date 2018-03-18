

//EngineApp.cpp
// Engine application for Invido game

#include "StdAfx.h"
#include "win_type_global.h"

#include <SDL.h>
#include <SDL_ttf.h>
#include "EngineApp.h"
#include <sdl.h>
#include <SDL_thread.h>
#include <SDL_mixer.h>
#include <SDL_image.h>
#include <string>
#include "Lang_Gen.h"
#include "cHightScoreMgr.h"
#include "cMusicManager.h"
#include "cSettings.h"
#include "cDelayNextAction.h"
#include "cInvidoGfx.h"
#include "cTipoDiMazzo.h"
#include "cMenuMgr.h"
#include "credits.h"
#include "fading.h"
#include "OptionGfx.h"
#include "EnterNameGfx.h"


//#include "font.h"

static const char* lpszIconRes = "data/images/icona_asso.bmp";
// key is stored in regestry as HKU
#ifdef WIN32
static const char* lpszIniFileOptions = "Software\\BredaSoft\\InvidoClientSdl";
#else
static const char* lpszIniFileOptions = "data/options.ini";
#endif
static const char* lpszIniFontAriblk = "data/font/ariblk.ttf";
static const char* lpszIniFontVera = "data/font/vera.ttf"; 
static const char* lpszImageDir = "data/images/";
static const char* lpszImageSplash = "mainmenu.jpg";
static const char* lpszCreditsTitle = "data/images/titlecredits.png";
static const char* lpszHelpFileName = "data/help/invido.pdf";


cEngineApp* g_MainApp = 0;



//////////////////////////////////////////////////////////////////////////////////////////////
///////////////////////////////////// class cEngineApp ///////////////////////////////////////
//////////////////////////////////////////////////////////////////////////////////////////////


////////////////////////////////////////
//       cEngineApp
/*! constructor
*/
cEngineApp::cEngineApp()
{
    m_pScreen = NULL;
    m_iScreenW = 800 ; //640;
    m_iScreenH = 600 ; //480;
    m_iBpp = 0;
    m_pMusicManager = 0;
    m_pLanString = 0;
    m_pMenuMgr = 0;
    m_pfontAriblk = 0;
    m_pfontVera = 0;
    m_pSlash = 0;
    m_pMxAccOptions = 0;
    m_pOptCond = 0;
	g_MainApp = this;
    m_bOpzWinRunning = FALSE;
    m_pTitleCredits = 0;
    m_pRemoteGui = 0;
    m_pClientNetwork = 0;
}


////////////////////////////////////////
//       ~cEngineApp
/*! destructor
*/
cEngineApp::~cEngineApp()
{
    terminate();
}


////////////////////////////////////////
//       loadProfile
/*! Load profiles in g_Options
*/
void cEngineApp::loadProfile()
{
    SpaceInvidoSettings::GetProfile(lpszIniFileOptions);
}


////////////////////////////////////////
//       writeProfile
/*! Write profiles g_Options in ini file
*/
void cEngineApp::writeProfile()
{
    SpaceInvidoSettings::WriteProfile(lpszIniFileOptions);
}



////////////////////////////////////////
//       Init
/*! Init application
*/
void cEngineApp::Init()
{
    // load settings in the registry
    loadProfile();

    CHAR ErrBuff[512];
    // Initialize SDL 
    if ( SDL_Init(0) < 0 ) 
    {
        sprintf(ErrBuff, "Couldn't initialize SDL: %s\n",SDL_GetError());
        throw Error::Init(ErrBuff);
    }    
    setVideoResolution();

    m_pMusicManager = new cMusicManager;
    m_pMusicManager->Init(); 

    m_pInvidoGfx = new cInvidoGfx(this);
    m_pLanString = new cLanguages;
    m_pHScore = new cHightScoreMgr;
     
    // set application language
    m_pLanString->SetLang((cLanguages::eLangId)g_Options.All.iLanguageID);
    
    // caption
    SDL_WM_SetCaption(m_pLanString->GetCStringId(cLanguages::ID_INVIDO) ,NULL);	
    
    // hight score
    //m_HScore.Load(); 
    
    //trasparent icon
    SDL_Surface * psIcon = SDL_LoadBMP(lpszIconRes);
    if (psIcon == 0)
    {
        sprintf(ErrBuff, "Icon not found");
        throw Error::Init(ErrBuff);
    }
    SDL_SetColorKey(psIcon, SDL_SRCCOLORKEY|SDL_RLEACCEL, SDL_MapRGB(psIcon->format, 0, 128, 0));
    SDL_WM_SetIcon(psIcon, NULL);
    
    //HICON  hicon = LoadIcon(hAppInstance, MAKEINTRESOURCE(IDI_ICON1));
    
    // font TTF
    if (TTF_Init() == -1) 
    {
        sprintf(ErrBuff, "Font init error");
        throw Error::Init(ErrBuff);
    }
    // font Ariblk
    std::string strFileFontStatus = lpszIniFontAriblk; 
    m_pfontAriblk = TTF_OpenFont(strFileFontStatus.c_str()  , 22);
    if (m_pfontAriblk == 0)
    {
        sprintf(ErrBuff, "Unable to load font %s, error: %s\n", strFileFontStatus.c_str() , SDL_GetError());
        throw Error::Init(ErrBuff);
    }
	// font Vera
    strFileFontStatus = lpszIniFontVera;
    m_pfontVera = TTF_OpenFont(strFileFontStatus.c_str(), 11);
    if (m_pfontVera == 0)
    {
        sprintf(ErrBuff, "Unable to load font %s, error: %s\n", strFileFontStatus.c_str() , SDL_GetError());
        throw Error::Init(ErrBuff);
    }

    // game invido app
    m_pInvidoGfx->SetMainApp(this);
    
    // menu manager
    m_pMenuMgr = new cMenuMgr(this, m_pInvidoGfx);
    m_pMenuMgr->Init(m_pScreen); 

    // set main menu
    m_Histmenu.push(cMenuMgr::QUITAPP);
    m_Histmenu.push(cMenuMgr::MENU_ROOT);

    // background
    loadSplash();
    drawSplash();

    // credits title
    m_pTitleCredits = IMG_Load(lpszCreditsTitle);
    if (m_pTitleCredits == 0)
    {
        CHAR ErrBuff[512];
        sprintf(ErrBuff, "Unable to load %s  image\n" , lpszCreditsTitle);
        throw Error::Init(ErrBuff);
    }

    // load music
    // music manager initialization is a long process, update also a progress bar
    m_pMusicManager->LoadMusicRes(); 

    m_pMxAccOptions = SDL_CreateMutex();
    m_pOptCond = SDL_CreateCond();
}


////////////////////////////////////////
//       InitNetwork
/*! Init network stuff
*/
void cEngineApp::InitNetwork()
{
    // network
    
    // initialize SDL_net
	if(SDLNet_Init()==-1)
	{
        CHAR ErrBuff[512];
		sprintf(ErrBuff, "SDLNet_Init: %s\n",SDLNet_GetError());
		throw Error::Init(ErrBuff);
	}

    // NOTE: don't separate this 2 stuff, because the initilization need an instantiated object
    // The order of initialiaziation (call of Init()) is not relevant.
    // creation stuff
    m_pClientNetwork = new cNetClient();
    m_pRemoteGui = new cNetGuiRemote();

    // init stuff
    m_pClientNetwork->Init(m_pRemoteGui);
    m_pRemoteGui->Init(m_pClientNetwork);

}


////////////////////////////////////////
//       loadSplash
/*! load splash screen
*/
void cEngineApp::loadSplash()
{
    // load background
    if (g_Options.All.bUseSplashJpg)
    {
        SDL_Surface *Temp;
        std::string strFileName = lpszImageDir;
        strFileName += lpszImageSplash;

        SDL_RWops *srcBack = SDL_RWFromFile(strFileName.c_str(), "rb");
        if (srcBack==0)
        {
            CHAR ErrBuff[512];
            sprintf(ErrBuff, "Unable to load %s background image\n" , strFileName.c_str());
            throw Error::Init(ErrBuff);
        }
        Temp = IMG_LoadJPG_RW(srcBack);
        m_pSlash = SDL_DisplayFormat(Temp);
        SDL_FreeSurface(Temp);
    }
    else
    {
        m_pSlash = SDL_CreateRGBSurface(SDL_SWSURFACE, m_pScreen->w, m_pScreen->h, 32, 0, 0, 0, 0);
        SDL_FillRect(m_pSlash, NULL, SDL_MapRGBA(m_pScreen->format, 0, 80, 0, 0));
    }
	
}


////////////////////////////////////////
//       drawSplash
/*! 
*/
void cEngineApp::drawSplash()
{
   	SDL_BlitSurface(m_pSlash, NULL, m_pScreen, NULL);
    SDL_Flip(m_pScreen);
}


////////////////////////////////////////
//       terminate
/*! Terminate stuff
*/
void cEngineApp::terminate()
{
    writeProfile();

    SDL_ShowCursor( SDL_ENABLE );
    
    if (m_pScreen!=NULL)
    {
        SDL_FreeSurface(m_pScreen);
        m_pScreen=NULL;
    }
    if (m_pSlash)
    {
        SDL_FreeSurface(m_pSlash);
        m_pSlash = 0;
    }
    if (m_pTitleCredits)
    {
        SDL_FreeSurface(m_pTitleCredits);
        m_pTitleCredits = 0;
    }

    delete m_pLanString;
    delete m_pInvidoGfx;
    delete m_pMusicManager;
    delete m_pHScore;

    delete m_pRemoteGui;
    delete m_pClientNetwork;
    // shutdown SDL_net
	SDLNet_Quit();

    SDL_Quit();
}



////////////////////////////////////////
//       MainLoop
/*! Main loop
*/
void cEngineApp::MainLoop()
{
    bool bquit = false;
    
    // set background of menu
    m_pMenuMgr->SetBackground(m_pSlash);
   	
    while (!bquit && !m_Histmenu.empty()) 
    {
		switch (m_Histmenu.top()) 
        {
            case cMenuMgr::MENU_ROOT:
                if (g_Options.All.bMusicOn && !m_pMusicManager->IsPLayingMusic()  )
                {
                    m_pMusicManager->PlayMusic(cMusicManager::MUSIC_INIT_SND, cMusicManager::LOOP_ON);
                }
                m_pMenuMgr->HandleRootMenu();

                break;

            case cMenuMgr::MENU_GAME:
                PlayGame();
                break;

            case cMenuMgr::MENU_HELP:
                ShowHelp();
                break;

            case cMenuMgr::MENU_CREDITS:
                ShowCredits();
                break;

            case cMenuMgr::MENU_OPTIONS:
                ShowOptionsGeneral();
                break;

            case cMenuMgr::QUITAPP:
            default:
                bquit = true;
                break;
            
		}
	
        // actualize display
		SDL_Flip(m_pScreen);

	}
}


////////////////////////////////////////
//       showEditUserName
/*! Show a dialogbox to change the user name
*/
void cEngineApp::showEditUserName()
{
    EnterNameGfx Dlg;
    SDL_Rect rctWin;
    rctWin.w = 350;
    rctWin.h = 200;

    rctWin.x = (m_pScreen->w  - rctWin.w)/2;
    rctWin.y = (m_pScreen->h - rctWin.h) / 2;
    

    Dlg.Init(&rctWin, m_pScreen, m_pfontVera, m_pfontAriblk);
    Dlg.SetCaption(m_pLanString->GetStringId(cLanguages::ID_CHOOSENAME)); 
    Dlg.Show(m_pSlash);

    drawSplash();
}

////////////////////////////////////////
//       ShowHelp
/*! Show help menu
*/
void cEngineApp::ShowHelp()
{
    //std::string strFileName = lpszHelpFileName;
	//ShellExecute(0, "open", strFileName.c_str() , 0, 0, SW_SHOWNORMAL);	
#ifdef WIN32
    std::string strFileName = lpszHelpFileName;
    STRING strCompleteHelpPath = m_strApplicationDir + "\\" + strFileName;
	::ShellExecute(NULL, TEXT("open"), strCompleteHelpPath.c_str() , 0, 0, SW_SHOWNORMAL);
#endif

    LeaveMenu();
}


////////////////////////////////////////
//       ShowCredits
/*! Show credits screen
*/
void cEngineApp::ShowCredits()
{
    cCredits aCred(m_pfontVera);

    aCred.Show(m_pScreen, m_pTitleCredits);

    LeaveMenu();
}

////////////////////////////////////////
//       setVideoResolution
/*! Set video resolution
*/
void cEngineApp::setVideoResolution()
{
    if (m_pScreen)
    {
        SDL_FreeSurface(m_pScreen);
    }
    m_pScreen = SDL_SetVideoMode(m_iScreenW, m_iScreenH, m_iBpp, SDL_SWSURFACE);
    if ( m_pScreen == NULL )
    {
        fprintf(stderr, "Error setvideomode: %s\n", SDL_GetError());
        exit(1);
        
    }
    
}



////////////////////////////////////////
//       hightScoreMenu
/*! Shows the hight score menu
*/
void cEngineApp::hightScoreMenu()
{
    // to do
}





////////////////////////////////////////
//       LeaveMenu
/*! Leave the current menu
*/
void   cEngineApp::LeaveMenu()
{
    drawSplash();

    m_Histmenu.pop();
}

////////////////////////////////////////
//       PlayGame
/*! Play the game vs cpu
*/
int  cEngineApp::PlayGame()
{
    if (g_Options.All.strPlayerName == "Anonimo" )
    {
        // default name, show  a dialogbox to set the name
        showEditUserName();
    }

    m_pMusicManager->StopMusic();
    
    // load and initialize background
    m_pInvidoGfx->Initialize(m_pScreen);
    // init invido core stuff
    m_pInvidoGfx->InitInvidoVsCPU();
    
    // match main loop
    m_pInvidoGfx->MatchLoop();
    
    // game terminated
    
    LeaveMenu();
    
    return 0;
}


////////////////////////////////////////
//       PlayNetGame
/*! Start playing a network game
*/
void  cEngineApp::PlayNetGame()
{
    // init invido newtork core stuff
    m_pInvidoGfx->InitInvido2Player();
    // net client need to know the current hmi user (local)
    cPlayer* pPlayer1 = m_pInvidoGfx->GetPlayer(PLAYER1) ;
    m_pClientNetwork->SetPlayer(pPlayer1); 

    // start network GUI in order to connect a game server and user login
    ASSERT(m_pRemoteGui);
    m_pRemoteGui->Start(); 

    
    // loop on waiting that the remote gui start a network game 
    // GUI-remote: 1) connect to the game server
    //             2) login
    //             3) join/create a table
    //             4) start a new match
    //             5) opponent accept a match
    SDL_Event event;
    BOOL bTriggerMatch = FALSE;
    while(!bTriggerMatch)
    {
        while(SDL_PollEvent(&event))
        {
            switch(event.type)
            {
            case SDL_QUIT:
                return ;
            }
        }
        // to do: display some progress bar
      
        m_pClientNetwork->ProcMsgInQueue();
        m_pRemoteGui->ProcMsgInQueue();
        if (m_pRemoteGui->IsTerminated())
        {
            // something wrong with server communication, exit
            return;
        }

        // actualize display
		SDL_Flip(m_pScreen);

        SDL_Delay(10);
    }
    
    m_pMusicManager->StopMusic();
    // load and initialize background
    m_pInvidoGfx->Initialize(m_pScreen);
    
    // match main loop
    m_pInvidoGfx->MatchLoop();
}


////////////////////////////////////////
//       ShowOptionsGeneral
/*! Show the option general control
*/
void cEngineApp::ShowOptionsGeneral()
{
	OptionGfx Optio;

    SDL_Rect rctOptionWin;

    rctOptionWin.w = 500;
    rctOptionWin.h = 500;

    rctOptionWin.x = (m_pScreen->w  - rctOptionWin.w)/2;
    rctOptionWin.y = (m_pScreen->h - rctOptionWin.h) / 2;
    

    Optio.Init(&rctOptionWin, m_pScreen, m_pfontVera, m_pfontAriblk);
    Optio.SetCaption(m_pLanString->GetStringId(cLanguages::ID_OPT_CONTRL_GENERAL)); 
    Optio.Show(m_pSlash);

    LeaveMenu();
}


