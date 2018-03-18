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

//cDelayNextAction.cpp

#include "StdAfx.h"
#include "win_type_global.h"
#include "SDL.h"
#include "cDelayNextAction.h"

////////////////////// cDelayNextAction 

cDelayNextAction::cDelayNextAction()
{
    m_eChangeVal = CHANGE_AVAIL;
}

////////////////////////////////////////
//       CanStart
/*! Provides TRUE if not delay is ongoing, FALSE if delay is active
*/
BOOL cDelayNextAction::CanStart()
{

	BOOL bRet = FALSE;
	if (!m_bDelayNextAction)
	{
		// no delay request
		return TRUE;
	}

	Uint32 uiNowTime = SDL_GetTicks();
	if (uiNowTime - m_uiStartDelTime > m_uiDelayTick)
	{
		bRet = TRUE;
		m_bDelayNextAction = FALSE;
	}

	return bRet;
}


////////////////////////////////////////
//       Reset
/*! Reset the delay action ( disable delay)
*/
void cDelayNextAction::Reset()
{
    TRACE ("Reset Check point called\n");

	m_uiStartDelTime = 0;
	m_bDelayNextAction = FALSE;
	m_uiDelayTick = 0;
    m_eChangeVal = CHANGE_AVAIL;
}


////////////////////////////////////////
//       ChangeCurrDelay
/*! Chenge the value of the current delay
// \param Uint32 uiVal : new value
*/
void cDelayNextAction::ChangeCurrDelay(Uint32 uiVal)
{
    if (m_eChangeVal == CHANGE_AVAIL)
    {
        TRACE ("Change current delay\n");
        m_uiDelayTick = uiVal;
    }
}

////////////////////////////////////////
//       CheckPoint
/*! Set a checkpoint to delay an action. The action should be enable after a acknowledge 
// with the function call CanStart()
// \param Uint32 uiVal : 
// \param eChangeble eVal:  if no changeble, change the curret delay as noeffect
*/
void cDelayNextAction::CheckPoint(Uint32 uiVal, eChangeble eVal)
{
    TRACE ("Check point called\n");

	m_uiStartDelTime = SDL_GetTicks();
	m_bDelayNextAction = TRUE;
	m_uiDelayTick = uiVal;
    m_eChangeVal = eVal;

}
