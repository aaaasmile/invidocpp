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


//ConsoleCmdHand.h

#ifndef __CONSOLE_CMD_HAND__H
#define __CONSOLE_CMD_HAND__H

#include "win_type_global.h"
#include "SDL.h"
#include <string>
#include "CON_console.h"
#include "Lang_Gen.h"


class cInvidoGfx;
class cEngineApp;

//! class cConsoleCmdHandler
/**
// class used to hanfle all commands on the console
*/
class cConsoleCmdHandler
{
public:
    enum eCmdStatus
    {
        DEFAULT,
        IN_CHAT,
    };
    cConsoleCmdHandler(SDL_Surface* pVal, cInvidoGfx* pVal2, cLanguages* pVal3, cEngineApp* pVal4);

    void    Command_Handler(ConsoleInformation *console, char* command) ;
    void    ListCommands(ConsoleInformation* console);    
    void    HelpText(SDL_Surface *Screen) ;
    void    PrepPrompt(ConsoleInformation *console);

private:
    cConsoleCmdHandler(){}// avoid standard construct
    void    KillView() ;
    void    Echo(ConsoleInformation *console, int argc, char* argv[]) ;
    void    SetPrompt(ConsoleInformation *console, int argc, char* argv[]) ;
    void    Resize(ConsoleInformation *console, int argc, char* argv[]) ;
    void    Move(ConsoleInformation *console, int argc, char* argv[]); 
    void    AlphaChange(ConsoleInformation *console, int argc, char* argv[]);
    void    SetNewNickName(ConsoleInformation *console, int argc, char* argv[]) ;
    void    StartChat(ConsoleInformation *console, int argc, char* argv[]);
    void    ExitChat(ConsoleInformation *console, int argc, char* argv[]);
    BOOL    isInvidoCmd(LPCSTR lpsCmd);

private:
    //! main screen pointer
    SDL_Surface*   m_pScreen;
    //! parent view pointer
    cInvidoGfx*    m_pParent;
    //! language manager
    cLanguages*    m_pLanString;
    //! main application
    cEngineApp*    m_pApp;
    //! status
    eCmdStatus     m_eCmdStatus;

};



#endif