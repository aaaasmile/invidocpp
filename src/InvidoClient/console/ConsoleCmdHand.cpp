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

//ConsoleCmdHand.cpp

#include "StdAfx.h"
#include "win_type_global.h"
#include <stdio.h>
#include <stdlib.h>
#include <sdl.h>
#include <SDL_image.h>
#include <SDL_ttf.h>
#include "cDelayNextAction.h"

#include "ConsoleCmdHand.h"
#include "split.h"
#include "DT_drawtext.h"
#include "EngineApp.h"
#include "cInvidoGfx.h"

#include "cSettings.h"


////////////////////////////////////////
//       cConsoleCmdHandler
/*! constructor
// \param SDL_Surface* pVal : 
// \param cClientView* pVal2 : 
*/
cConsoleCmdHandler::cConsoleCmdHandler(SDL_Surface* pVal, cInvidoGfx* pVal2, 
                                       cLanguages* pVal3, cEngineApp* pVal4)
{
    m_pScreen = pVal;
    m_pParent = pVal2;
    m_pLanString = pVal3;
    m_pApp = pVal4;
    m_eCmdStatus = DEFAULT;
}


////////////////////////////////////////
//       Command_Handler
/*! 
// \param ConsoleInformation *console : 
// \param char* command : 
*/
void cConsoleCmdHandler::Command_Handler(ConsoleInformation *console, char* command) 
{
	int argc;
	char* argv[128];
	char* linecopy;

	linecopy = strdup(command);
	argc = splitline(argv, (sizeof argv)/(sizeof argv[0]), linecopy);
	if(!argc) 
    {
		free(linecopy);
		return;
	}

    if (m_eCmdStatus == IN_CHAT)
    {
        if(!strcmp(argv[0], "quit"))
		    ExitChat(console, argc, argv);
        else if(!strcmp(argv[0], "help"))
		    ListCommands(console);
        else
        {
            //TODO:send the string in the chat
        }
    }
    else
    {

        if(isInvidoCmd(argv[0]))
        {
        }
	    else if(!strcmp(argv[0], "quit"))
		    KillView();
        else if(!strcmp(argv[0], "help"))
		    ListCommands(console);
        else
            CON_Out(console, m_pLanString->GetCStringId(cLanguages::ID_CMD_UNKNOWN));
    }

}


////////////////////////////////////////
//       isInvidoCmd
/*! Check if it is an invido command
// \param LPCSTR lpsCmd : 
*/
BOOL cConsoleCmdHandler::isInvidoCmd(LPCSTR lpsCmd)
{
    BOOL bRes = FALSE;
    eSayPlayer eSay;

    if (!strcmp(lpsCmd, "invido"))
    {
        eSay = INVIDO;
        bRes = TRUE;
    }
    else if (!strcmp(lpsCmd, "va bene") ||
             !strcmp(lpsCmd, "vabene") ||
             !strcmp(lpsCmd, "si") ||
             !strcmp(lpsCmd, "gioca"))
    {
        eSay = VABENE;
        bRes = TRUE;
    }
    else if (!strcmp(lpsCmd, "monte") ||
             !strcmp(lpsCmd, "a munt") ||
             !strcmp(lpsCmd, "munt") || 
             !strcmp(lpsCmd, "munt a mo"))
    {
        eSay = AMONTE;
        bRes = TRUE;
    }
    else if (!strcmp(lpsCmd, "trasmas") )
    {
        eSay = TRASMAS;
        bRes = TRUE;
    }
    else if (!strcmp(lpsCmd, "trasmasnof") )
    {
        eSay = TRASMASNOEF;
        bRes = TRUE;
    }
    else if (!strcmp(lpsCmd, "fuorigioco") )
    {
        eSay = FUERAJEUQ;
        bRes = TRUE;
    }
    else if (!strcmp(lpsCmd, "partida") )
    {
        eSay = PARTIDA;
        bRes = TRUE;
    }
    else if (!strcmp(lpsCmd, "vu via") ||
             !strcmp(lpsCmd, "vadovia"))
    {
        eSay = VADOVIA;
        bRes = TRUE;
    }
    else if (!strcmp(lpsCmd, "no") ||
             !strcmp(lpsCmd, "in frunt"))
    {
        eSay = NO;
        bRes = TRUE;
    }

    if (bRes)
    {
        m_pParent->INP_PlayerSay(eSay);
    }

    return bRes;
}


////////////////////////////////////////
//       KillView
/*! 
*/
void cConsoleCmdHandler::KillView() 
{
    if (m_pParent)
    {
        // to do : exit to the game
        //m_pParent->KillView() ;
    }
}


////////////////////////////////////////
//       Echo
/*! Prints the string you pass it into the console
// \param ConsoleInformation *console : 
// \param int argc : 
// \param char* argv[] : 
*/
void cConsoleCmdHandler::Echo(ConsoleInformation *console, int argc, char* argv[]) 
{
	int i;

	for(i = 0; i < argc; i++) 
    {
		CON_Out(console, "%s", argv[i]);
	}
}


////////////////////////////////////////
//       StartChat
/*! 
// \param console : 
// \param argc : 
// \param argv : 
*/
void cConsoleCmdHandler::StartChat(ConsoleInformation *console, int argc, char* argv[])
{
    m_pParent->ShowChat(true);
    std::string strPromt = g_Options.All.strPlayerName;
    strPromt += "_CHAT>";
    m_eCmdStatus = IN_CHAT;
    CON_SetPrompt(console, const_cast<char*>(strPromt.c_str()) );
}


////////////////////////////////////////
//       ExitChat
/*! 
// \param ConsoleInformation *console : 
// \param int argc : 
// \param char* argv[] : 
*/
void cConsoleCmdHandler::ExitChat(ConsoleInformation *console, int argc, char* argv[])
{
    m_pParent->ShowChat(false);
    PrepPrompt(console);
    m_eCmdStatus = DEFAULT;
    
}

////////////////////////////////////////
//       AlphaChange
/*! lets the user change the alpha level
// \param ConsoleInformation *console : 
// \param int argc : 
// \param char* argv[] : 
*/
void cConsoleCmdHandler::AlphaChange(ConsoleInformation *console, int argc, char* argv[])
{
	if(argc > 1) 
    {
		CON_Alpha(console, atoi(argv[1]));
		CON_Out(console, "Alpha set to %s.", argv[1]);
	} 
    else
    {
		CON_Out(console, "usage: %s <alphavalue>", argv[0]);
    }
}

////////////////////////////////////////
//       Move
/*! Move the console, takes and x and a y
// \param ConsoleInformation *console : 
// \param int argc : 
// \param char* argv[] : 
*/
void cConsoleCmdHandler::Move(ConsoleInformation *console, int argc, char* argv[]) 
{
	int x, y;

	if(argc > 2) 
    {
		x = atoi(argv[1]);
		y = atoi(argv[2]);
		CON_Position(console, x, y);
	} 
    else 
    {
		CON_Position(console, 0, 0);
		CON_Out(console, "usage: %s <x> <y>", argv[0]);
	}
}

////////////////////////////////////////
//       Resize
/*! resizes the console window, takes and x and y, and a width and height 
// \param ConsoleInformation *console : 
// \param int argc : 
// \param char* argv[] : 
*/
void cConsoleCmdHandler::Resize(ConsoleInformation *console, int argc, char* argv[]) 
{
	SDL_Rect rect;

	if(argc > 4) 
    {
		rect.x = atoi(argv[1]);
		rect.y = atoi(argv[2]);
		rect.w = atoi(argv[3]);
		rect.h = atoi(argv[4]);
		CON_Resize(console, rect);
	} 
    else
		CON_Out(console, "usage: %s <x> <y> <width> <height>", argv[0]);
}


////////////////////////////////////////
//       SetPrompt
/*! Change prompt in console
// \param ConsoleInformation *console : 
// \param int argc : 
// \param char* argv[] : 
*/
void cConsoleCmdHandler::SetPrompt(ConsoleInformation *console, int argc, char* argv[]) 
{
	if(argc > 1)
		CON_SetPrompt(console, argv[1]);
	else
		CON_Out(console, "usage: %s <new_prompt>", argv[0]);
}


////////////////////////////////////////
//       SetNewNickName
/*! 
// \param ConsoleInformation *console : 
// \param int argc : 
// \param char* argv[] : 
*/
void cConsoleCmdHandler::SetNewNickName(ConsoleInformation *console, int argc, char* argv[]) 
{
	if(argc > 1)
    {
		g_Options.All.strPlayerName = argv[1];
        PrepPrompt(console);
    }
	else
    {
		CON_Out(console, "usage: %s <new_name>", argv[0]);
    }
}


////////////////////////////////////////
//       PrepPrompt
/*! 
*/
void cConsoleCmdHandler::PrepPrompt(ConsoleInformation *console)
{
    std::string strPromt = g_Options.All.strPlayerName;
    strPromt += ">";
    CON_SetPrompt(console, const_cast<char*>(strPromt.c_str()) );
}

////////////////////////////////////////
//       ListCommands
/*! 
// \param ConsoleInformation* console : 
*/
void cConsoleCmdHandler::ListCommands(ConsoleInformation* console)
 {
    CON_Out(console, "[INFO]%s", m_pLanString->GetCStringId(cLanguages::ID_CMD_HELP));
    if (m_eCmdStatus == IN_CHAT)
    {
        CON_Out(console, "exit");
        CON_Out(console, "quit");
        CON_Out(console, "help");
        CON_Out(console, "listcommands");
    }
    else
    {
	    CON_Out(console, "invido, si, no, monte");
	    CON_Out(console, "trasmas, trasmasnof ");
	    CON_Out(console, "fuorigioco, partida");
	    CON_Out(console, "vadovia");
    }
}

////////////////////////////////////////
//       HelpText
/*! This function displays a help message
// \param SDL_Surface *Screen : 
*/
void cConsoleCmdHandler::HelpText(SDL_Surface *Screen) 
{
	DT_DrawText("Show/Hide the consoles with Ctrl-1 to Ctrl-3", Screen, 0, 100, Screen->h - 30);
	DT_DrawText("Change input with Alt-1 to Alt-3. Alt-4 disables Input.", Screen, 0, 100, Screen->h - 20);
}
