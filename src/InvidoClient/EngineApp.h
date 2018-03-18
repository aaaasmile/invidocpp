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

//EngineApp.h

#ifndef __ENGINE_APP_H
#define __ENGINE_APP_H

#include <stack>
#include "myexception.h"


class cHightScoreMgr;
class cLanguages;
class cInvidoGfx;
class cMusicManager;
class cMenuMgr;
class cNetClient;
class cNetGuiRemote;

//! class cEngineApp
class cEngineApp
{
public:
    cEngineApp();
    ~cEngineApp();

    //! init stuff
    void    Init();
    //! init network
    void    InitNetwork();
    //! application entry point
    void    MainMenu();
    //! language translation
    cLanguages*     GetLanguageMan(){return m_pLanString;}
    //! play the invido
    int		PlayGame();
    //! main loop
    void    MainLoop();
    //! provides font vera
    TTF_Font*   GetFontVera(){return m_pfontVera;}
    //! provide font ariblk
    TTF_Font*   GetFontAriblk(){return m_pfontAriblk;}
    //! Leave current menu
    void   LeaveMenu();
    //! set next menu
    void   SetNextMenu(int iVal){m_Histmenu.push(iVal);}
    //! show menu help
    void   ShowHelp();
    //! provides music manager
    cMusicManager*  GetMusicManager(){return m_pMusicManager;}
    //! show credits screen
    void  ShowCredits();
    //! start a network game
    void  PlayNetGame();
    //! show options
    void ShowOptionsGeneral();
    STRING GetApplicationDir(){return m_strApplicationDir;}
    void   SetApplicationDir(STRING val){m_strApplicationDir = val;}
    
   
private:
    void    mainMenu();
    void    setVideoResolution();
    void    terminate();
    void    hightScoreMenu();
	
    void    initInvido2Player();
    void    loadProfile();
    void    writeProfile();
    void    drawSplash();
    void    loadSplash();
    void    showEditUserName();
   
private:
    //! main screen surface
    SDL_Surface*      m_pScreen;
    //! splash surface
    SDL_Surface*      m_pSlash;
    //! title credits
    SDL_Surface*      m_pTitleCredits;
    //! screen width
    int               m_iScreenW;
    //! screen height
    int               m_iScreenH;
    //! bit per pixel
    int               m_iBpp;
    //! hight score data
    cHightScoreMgr*   m_pHScore;
    //! get strings on differnt languages
    cLanguages*       m_pLanString;
	//! grafic game engines
	cInvidoGfx*       m_pInvidoGfx;
	//! music player  
    cMusicManager*    m_pMusicManager;
    //! menu state stack
    std::stack<int>   m_Histmenu; 
    //! menu handler
    cMenuMgr*         m_pMenuMgr;
    //! font 
    TTF_Font*         m_pfontVera;
    //! font
    TTF_Font*	      m_pfontAriblk;
    //! mutex access dialog opions
    SDL_mutex*        m_pMxAccOptions;
    //! condition dialog terminated
    SDL_cond*         m_pOptCond;
	//! running flag option window
	BOOL              m_bOpzWinRunning;
    //! client network
    cNetClient*       m_pClientNetwork;
    //! remote gui client
    cNetGuiRemote*    m_pRemoteGui;
    // application directory
    STRING            m_strApplicationDir;
};


#endif