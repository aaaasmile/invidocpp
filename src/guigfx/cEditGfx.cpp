/*
    Tressette
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


// cEditGfx.cpp: implementation of the cEditGfx class.
//
//////////////////////////////////////////////////////////////////////

#include "StdAfx.h"
#include "cEditGfx.h"
#include "gfx_util.h"

//////////////////////////////////////////////////////////////////////
// Construction/Destruction
//////////////////////////////////////////////////////////////////////

cEditGfx::cEditGfx()
{
    m_eState = INVISIBLE;
    m_pFontText = 0;
    m_iButID = 0;
    m_bIsEnabled = TRUE;
    m_pSurf_Bar = 0;
    m_bShowCaret = FALSE;
    m_iCarLogPos = 0;
    SDL_EnableUNICODE(1);
    m_bOnlyNum = FALSE;
}

cEditGfx::~cEditGfx()
{
    if (m_pSurf_Bar)
    {
        SDL_FreeSurface(m_pSurf_Bar);
        m_pSurf_Bar = NULL;
    }
}




////////////////////////////////////////
//       Init
/*! Init the button
// \param SDL_Rect* pRect : 
// \param SDL_Surface*  pScreen : 
*/
void  cEditGfx::Init(SDL_Rect* pRect, SDL_Surface*  pScreen, TTF_Font* pFont, int iButID)
{
    m_rctButt = *pRect;

    // black bar surface background
    /*
    m_pSurf_Bar = SDL_CreateRGBSurface(SDL_SWSURFACE, m_rctButt.w, m_rctButt.h, 32, 0, 0, 0, 0);
    SDL_FillRect(m_pSurf_Bar, NULL, SDL_MapRGBA(pScreen->format, 255, 0, 0, 0));
    SDL_SetAlpha(m_pSurf_Bar, SDL_SRCALPHA, 127);
    */
    m_pFontText = pFont;

    m_colCurrent = GFX_UTIL_COLOR::White;
    m_colBorder = m_colCurrent;
    m_iButID = iButID;

}


////////////////////////////////////////
//       SetState
/*! 
// \param eSate eVal : 
*/
void   cEditGfx::SetState(eSate eVal)
{
    eSate eOldState = m_eState;
    m_eState = eVal;
    if (eOldState != m_eState &&
        m_eState == VISIBLE)
    {
        m_colCurrent = GFX_UTIL_COLOR::White;
        m_colBorder = GFX_UTIL_COLOR::White; 
    }
    else if (eOldState != m_eState &&
        m_eState == SELECTED)
    {
        m_colBorder = GFX_UTIL_COLOR::Orange;
    }
}

////////////////////////////////////////
//       MouseMove
/*! 
// \param SDL_Event &event : 
*/
void   cEditGfx::MouseMove(SDL_Event &event, SDL_Surface* pScreen, SDL_Surface* pScene_background)
{
    
}


////////////////////////////////////////
//       MouseUp
/*! Mouse up event
// \param SDL_Event &event : 
*/
void   cEditGfx::MouseUp(SDL_Event &event)
{
    if (m_eState == VISIBLE && m_bIsEnabled)
    {
        if ( event.motion.x >=  m_rctButt.x  && event.motion.x <= m_rctButt.x + m_rctButt.w &&
             event.motion.y >=  m_rctButt.y  && event.motion.y <= m_rctButt.y + m_rctButt.h)
        {
            // mouse go up inner the control
            if (m_eState != INVISIBLE)
            {
                GetFocus();
                //m_fncbClickEvent( m_iButID);
            }
        }
    }
    else if (m_eState == SELECTED && m_bIsEnabled)
    {
        if ( event.motion.x >=  m_rctButt.x  && event.motion.x <= m_rctButt.x + m_rctButt.w &&
             event.motion.y >=  m_rctButt.y  && event.motion.y <= m_rctButt.y + m_rctButt.h)
        {
            // control selected and mouse inside the control
            // change the position of the caret
            int tx, ty;
	        TTF_SizeText(m_pFontText, m_strButText.c_str(), &tx, &ty);
            if (event.motion.x < m_rctButt.x + XOFFSET)
            {
                // caret at the begin
                m_iCarLogPos = 0;
            }
            else if (event.motion.x < (m_rctButt.x +  XOFFSET + tx))
            {
                // caret in word
                m_iCarLogPos = (m_strButText.length() * (event.motion.x - (m_rctButt.x +  XOFFSET)) * 100 / tx) / 100 ;
                ASSERT(m_iCarLogPos >= 0 && m_iCarLogPos <=  m_strButText.length());

            }
            else
            {
                // cursor outside the text
                m_iCarLogPos = m_strButText.length();
            }
        }
        else
        {
            // control lost the focus
            LostFocus();
        }
    }
}


////////////////////////////////////////
//       KeyDown
/*! Keydown event
// \param SDL_Event &event : 
*/
void   cEditGfx::KeyDown(SDL_Event &event)
{
    if (m_eState != SELECTED )
        return;

    int c = event.key.keysym.unicode;
	SDLKey key = event.key.keysym.sym;
	if (key >= SDLK_KP0 && key <= SDLK_KP9) {
		c = 48 + key - SDLK_KP0;
	}
    if (key == SDLK_LEFT)
    {
        m_iCarLogPos--;
        if (m_iCarLogPos <= 0)
        {
            m_iCarLogPos = 0;
        }
    }
    else if (key == SDLK_RIGHT)
    {
        m_iCarLogPos++;
        if (m_iCarLogPos >= m_strButText.length())
        {
            m_iCarLogPos = m_strButText.length();
        }
    }
    else if (key == SDLK_BACKSPACE)
    {
        if (m_iCarLogPos > 0)
        {
            m_iCarLogPos--;
            if (m_iCarLogPos <= 0)
            {
                m_iCarLogPos = 0;
            }

            STRING strBegText = m_strButText.substr(0, m_iCarLogPos);
            STRING strEndText = "";
            if (m_iCarLogPos < m_strButText.length())
            {
                strEndText = m_strButText.substr(m_iCarLogPos+1, m_strButText.length());
            }
            m_strButText = strBegText + strEndText;
        }
    }
    else if (key >= SDLK_RSHIFT && key <= SDLK_COMPOSE ||
             key == SDLK_TAB || key == SDLK_RETURN || key == SDLK_ESCAPE  ||
             key == SDLK_DELETE)
    {
        // ignore key
    }
    else
    {
        BOOL bContinue = TRUE;
        // check mask
        if (m_bOnlyNum)
        {
            if (key < SDLK_0 || key > SDLK_9)
            {
                // not a num key, rejject it
                bContinue = FALSE;
            }
        }
        if (bContinue)
        {
            // a key used to build the text
            UINT ch;
	        if ( (event.key.keysym.unicode & 0xFF80) == 0 ) {
		        ch = event.key.keysym.unicode & 0x7F;
	        } else {
		        //An international character..
                ch = event.key.keysym.unicode;
	        }
            char strBuff[2] = {'\0','\0'};
            strBuff[0] =  ch; //event.key.keysym.sym;
            STRING strBegText = "";
            if (m_iCarLogPos > 0)
            {
                strBegText = m_strButText.substr(0, m_iCarLogPos);
            }
            STRING strEndText = "";
            if (m_iCarLogPos < m_strButText.length())
            {
                strEndText = m_strButText.substr(m_iCarLogPos, m_strButText.length());
            }
            STRING strNew = strBuff;
            m_strButText = strBegText + strNew + strEndText;
            m_iCarLogPos++;
            if (m_iCarLogPos >= m_strButText.length())
            {
                m_iCarLogPos = m_strButText.length();
            }
        }
    }

}



////////////////////////////////////////
//       LostFocus
/*! The Edit control lost the focus
*/
void cEditGfx::LostFocus()
{
    SetState(VISIBLE);
    m_bShowCaret = FALSE;
}


////////////////////////////////////////
//       GetFocus
/*! The control get the focus
*/
void cEditGfx::GetFocus()
{
    SetState(SELECTED);
    m_uiStartTime = SDL_GetTicks();
    m_bShowCaret = TRUE;
    m_iCarLogPos = m_strButText.length();
                 
}

////////////////////////////////////////
//       DrawControl
/*! Draw the button suface with text
// \param SDL_Surface*  pScreen : 
*/
void   cEditGfx::DrawControl(SDL_Surface*  pScreen)
{
    if (m_eState != INVISIBLE)
    {
        if (m_bIsEnabled)
        {
            
            //GFX_UTIL::DrawStaticSpriteEx(pScreen, 0, 0, m_rctButt.w, m_rctButt.h, m_rctButt.x, m_rctButt.y, m_pSurf_Bar);
            int tx, ty;
	        TTF_SizeText(m_pFontText, m_strButText.c_str(), &tx, &ty);
            int iXOffSet = XOFFSET ;
            int iYOffset = (m_rctButt.h - ty) - 2 ;
            
            GFX_UTIL::DrawString(pScreen, m_strButText.c_str(), m_rctButt.x + iXOffSet, 
                                 m_rctButt.y + iYOffset, m_colCurrent, m_pFontText);
                                 

            // draw border
            GFX_UTIL::DrawRect(pScreen, m_rctButt.x-1, m_rctButt.y-1, m_rctButt.x + m_rctButt.w + 1, 
                                m_rctButt.y + m_rctButt.h + 1, GFX_UTIL_COLOR::Gray );
            GFX_UTIL::DrawRect(pScreen, m_rctButt.x-2, m_rctButt.y-2, m_rctButt.x + m_rctButt.w + 2,
                                m_rctButt.y + m_rctButt.h + 2, GFX_UTIL_COLOR::Black);
            /*
            GFX_UTIL::DrawRect(pScreen, m_rctButt.x, m_rctButt.y, m_rctButt.x +  m_rctButt.w, 
                                m_rctButt.y + m_rctButt.h , m_colBorder);
                                */
	        //drawRect(m_rctButt.x, m_rctButt.y, m_rctButt.w, m_rctButt.y, staColor_white);

            if (m_eState == SELECTED)
            {
                // draw the caret
                Uint32 uiNowTime = SDL_GetTicks();
                if (uiNowTime < m_uiStartTime + 500)
                {
                    if (m_bShowCaret)
                    {
                        
                        // show caret
                        int txSubString = 0;
                        if (m_iCarLogPos > 0)
                        {
                            // make a substring to get the position of the caret
                            STRING strSubText = m_strButText.substr(0, m_iCarLogPos);
                            TTF_SizeText(m_pFontText, strSubText.c_str(), &txSubString, &ty);
                        }
                        else if (m_iCarLogPos == 0)
                        {
                            txSubString = -1;
                        }
                         
                        int iXStart = m_rctButt.x + iXOffSet + txSubString;
                        GFX_UTIL::DrawStaticLine(pScreen, iXStart, m_rctButt.y + 4, iXStart, 
                                             m_rctButt.y + m_rctButt.h - 2, m_colCurrent);
                    }
                    
                }
                else
                {
                    // change caret state
                    m_uiStartTime = uiNowTime;
                    if (m_bShowCaret)
                    {
                        m_bShowCaret = FALSE;
                    }
                    else
                    {
                        m_bShowCaret = TRUE;
                    }
                }
		
            }
	        

            //ASSERT(m_strButText != "-");
        }
        else
        {
            // button disabled 
            // TO DO
        }
    }
}



////////////////////////////////////////
//       RedrawButton
/*! Redraw the button
// \param SDL_Surface* pScreen : 
// \param SDL_Surface* pScene_background : 
*/
void   cEditGfx::RedrawButton(SDL_Surface* pScreen, SDL_Surface* pScene_background)
{
    if (pScene_background)
    {
        SDL_BlitSurface(pScene_background, &m_rctButt, pScreen, &m_rctButt);
    }
    DrawControl(pScreen);
    SDL_Flip(pScreen);
}
