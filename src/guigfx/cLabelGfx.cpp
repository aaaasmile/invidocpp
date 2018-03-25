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



// cLabelGfx.cpp: implementation of the cLabelGfx class.
//
//////////////////////////////////////////////////////////////////////

#include "StdAfx.h"
#include "cLabelGfx.h"
#include "gfx_util.h"

//////////////////////////////////////////////////////////////////////
// Construction/Destruction
//////////////////////////////////////////////////////////////////////

cLabelGfx::cLabelGfx()
{
    m_eState = INVISIBLE;
    m_pFontText = 0;
    m_iButID = 0;
    m_bIsEnabled = TRUE;
    m_pSurf_Bar = 0;
}

cLabelGfx::~cLabelGfx()
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
void  cLabelGfx::Init(SDL_Rect* pRect, SDL_Surface*  pScreen, TTF_Font* pFont, int iButID)
{
    m_rctButt = *pRect;

    // black bar surface
    m_pSurf_Bar = SDL_CreateRGBSurface(SDL_SWSURFACE, m_rctButt.w, m_rctButt.h, 32, 0, 0, 0, 0);
    SDL_FillRect(m_pSurf_Bar, NULL, SDL_MapRGBA(pScreen->format, 255, 0, 0, 0));
    SDL_SetAlpha(m_pSurf_Bar, SDL_SRCALPHA, 127);
    m_pFontText = pFont;

    m_colCurrent = GFX_UTIL_COLOR::White;
    m_iButID = iButID;

}


////////////////////////////////////////
//       SetState
/*! 
// \param eSate eVal : 
*/
void   cLabelGfx::SetState(eSate eVal)
{
    eSate eOldState = m_eState;
    m_eState = eVal;
    if (eOldState != m_eState &&
        m_eState == VISIBLE)
    {
        m_colCurrent = GFX_UTIL_COLOR::White;
    }
}

////////////////////////////////////////
//       MouseMove
/*! 
// \param SDL_Event &event : 
*/
void   cLabelGfx::MouseMove(SDL_Event &event, SDL_Surface* pScreen, SDL_Surface* pScene_background)
{
    if (m_eState == VISIBLE && m_bIsEnabled)
    {
        if ( event.motion.x >=  m_rctButt.x  && event.motion.x <= m_rctButt.x + m_rctButt.w &&
             event.motion.y >=  m_rctButt.y  && event.motion.y <= m_rctButt.y + m_rctButt.h)
        {
            // mouse inner button
            m_colCurrent = GFX_UTIL_COLOR::Orange;
            Redraw(pScreen, pScene_background);
        }
        else
        {
            // mouse outside
            if (m_colCurrent.r == GFX_UTIL_COLOR::Orange.r &&
                m_colCurrent.g == GFX_UTIL_COLOR::Orange.g &&
                m_colCurrent.b == GFX_UTIL_COLOR::Orange.b)
            {
                // button was selected
                m_colCurrent = GFX_UTIL_COLOR::White;
                Redraw(pScreen, pScene_background);
            }
        }
    }
}


////////////////////////////////////////
//       MouseUp
/*! Mouse up event
// \param SDL_Event &event : 
*/
void   cLabelGfx::MouseUp(SDL_Event &event)
{
    if (m_eState == VISIBLE && m_bIsEnabled)
    {
        if ( event.motion.x >=  m_rctButt.x  && event.motion.x <= m_rctButt.x + m_rctButt.w &&
             event.motion.y >=  m_rctButt.y  && event.motion.y <= m_rctButt.y + m_rctButt.h)
        {
            // mouse go up inner the button
            // send a click event 
             m_fncbClickEvent( m_iButID);
        }
    }
}


////////////////////////////////////////
//       Draw
/*! Draw the label with text
// \param SDL_Surface*  pScreen : 
*/
void   cLabelGfx::Draw(SDL_Surface*  pScreen)
{
    if (m_eState != INVISIBLE)
    {
        if (m_bIsEnabled)
        {
            // begin stuff mouse
            /* // label don't use mouse over
            Uint8 state;
            int mx, my;
            state = SDL_GetMouseState(&mx, &my);
            if ( mx >=  m_rctButt.x  && mx <= m_rctButt.x + m_rctButt.w &&
                  my >=  m_rctButt.y  && my <= m_rctButt.y + m_rctButt.h)
            {
                // mouse on button
                m_colCurrent = GFX_UTIL_COLOR::Orange;
            }
            else
            {
                m_colCurrent = GFX_UTIL_COLOR::White;
            }
            // end stuff mouse
            */

            int tx, ty;
	        TTF_SizeText(m_pFontText, m_strButText.c_str(), &tx, &ty);
            int iXOffSet = (m_rctButt.w - tx)/2 ;
            if (iXOffSet < 0)
            {
                iXOffSet = 1;
            }
            int iYOffset = (m_rctButt.h - ty)/2 ;

            iYOffset = 0;
            iXOffSet = 0;
            GFX_UTIL::DrawString(pScreen, m_strButText.c_str(), m_rctButt.x + iXOffSet, 
                                 m_rctButt.y + iYOffset, m_colCurrent, m_pFontText);

            
        }
        else
        {
            // label disabled 
            // TO DO
        }
    }
}



////////////////////////////////////////
//       Redraw
/*! Redraw the button
// \param SDL_Surface* pScreen : 
// \param SDL_Surface* pScene_background : 
*/
void   cLabelGfx::Redraw(SDL_Surface* pScreen, SDL_Surface* pScene_background)
{
    if (pScene_background)
    {
        SDL_BlitSurface(pScene_background, &m_rctButt, pScreen, &m_rctButt);
    }
    Draw(pScreen);
    SDL_Flip(pScreen);
}
