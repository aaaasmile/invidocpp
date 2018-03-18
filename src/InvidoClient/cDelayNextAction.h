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

//cDelayNextAction.h

#ifndef __CDELAY_NO_ACTION_H
#define __CDELAY_NO_ACTION_H




//! class cDelayNextAction 
// delay next action
class cDelayNextAction
{
public:
    enum eChangeble
    {
        NOCHANGE,
        CHANGE_AVAIL
    };
	cDelayNextAction();
	//! provides trigger to call next action
	BOOL  CanStart();
	//! reset
	void  Reset();
	//! start delay
	void  CheckPoint(Uint32 uiVal, eChangeble eVal);
    //! change the delay time only
    void  ChangeCurrDelay(Uint32 uiVal);

private:
	//! delay start time
	Uint32   m_uiStartDelTime;
	//! delay next action
	BOOL     m_bDelayNextAction;
	//! tick to delay
	Uint32   m_uiDelayTick;
    //! mutex access data
    SDL_mutex*        m_pMxAcc;
    //! chaange type of delay
    eChangeble  m_eChangeVal;
};





#endif