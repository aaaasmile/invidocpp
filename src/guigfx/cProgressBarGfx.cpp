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



// cProgressBarGfx.cpp: implementation of the cProgressBarGfx class.
//
//////////////////////////////////////////////////////////////////////

#include "StdAfx.h"
#include "cProgressBarGfx.h"
#include "gfx_util.h"

//////////////////////////////////////////////////////////////////////
// Construction/Destruction
//////////////////////////////////////////////////////////////////////

cProgressBarGfx::cProgressBarGfx()
{
	m_eState = INVISIBLE;
	m_pFontText = 0;
	m_iButID = 0;
	m_bIsEnabled = TRUE;
	m_pSurf_Bar = 0;
	m_pImageCursor = 0;
	m_pSurf_BoxSel = 0;
	m_pSurf_BoxUNSel = 0;
	m_iLowRange = 0;
	m_iUpRange = 5;
	m_iNumOfStep = 6;
	m_iCurrLevel = 0;
	m_bOnDrag = FALSE;
}

cProgressBarGfx::~cProgressBarGfx()
{
	if (m_pSurf_Bar)
	{
		SDL_FreeSurface(m_pSurf_Bar);
		m_pSurf_Bar = NULL;
	}
	if (m_pSurf_BoxSel)
	{
		SDL_FreeSurface(m_pSurf_BoxSel);
		m_pSurf_BoxSel = NULL;
	}
	if (m_pSurf_BoxUNSel)
	{
		SDL_FreeSurface(m_pSurf_BoxUNSel);
		m_pSurf_BoxUNSel = NULL;
	}
}




////////////////////////////////////////
//       Init
/*! Init the progressbar
// \param SDL_Rect* pRect : control dimension
// \param SDL_Surface*  pScreen : screen
// \param SDL_Surface*  pCursor : cursor image
*/
void  cProgressBarGfx::Init(SDL_Rect* pRect, SDL_Surface*  pScreen, SDL_Surface*  pCursor,
	TTF_Font* pFont, int iButID)
{
	m_rctButt = *pRect;

	// black bar surface
	m_pSurf_Bar = SDL_CreateRGBSurface(SDL_SWSURFACE, m_rctButt.w, m_rctButt.h, 32, 0, 0, 0, 0);
	SDL_FillRect(m_pSurf_Bar, NULL, SDL_MapRGBA(pScreen->format, 255, 0, 0, 0));
	//SDL_SetAlpha(m_pSurf_Bar, SDL_SRCALPHA, 127);
	SDL_SetSurfaceAlphaMod(m_pSurf_Bar, 127);
	m_pFontText = pFont;

	m_colCurrent = GFX_UTIL_COLOR::White;
	m_iButID = iButID;
	m_pImageCursor = pCursor;

	m_rctCursor.w = 15;
	m_rctCursor.h = 20;

	// selected surface cursor
	m_pSurf_BoxSel = SDL_CreateRGBSurface(SDL_SWSURFACE, m_rctCursor.w, m_rctCursor.h, 32, 0, 0, 0, 0);
	SDL_FillRect(m_pSurf_BoxSel, NULL, SDL_MapRGBA(pScreen->format, 200, 200, 130, 0));
	//SDL_SetAlpha(m_pSurf_BoxSel, SDL_SRCALPHA, 127);
	SDL_SetSurfaceAlphaMod(m_pSurf_BoxSel, 127);

	//unselected suface cursor
	m_pSurf_BoxUNSel = SDL_CreateRGBSurface(SDL_SWSURFACE, m_rctCursor.w, m_rctCursor.h, 32, 0, 0, 0, 0);
	SDL_FillRect(m_pSurf_BoxUNSel, NULL, SDL_MapRGBA(pScreen->format, 255, 128, 30, 0));
	//SDL_SetAlpha(m_pSurf_BoxUNSel, SDL_SRCALPHA, 127);
	SDL_SetSurfaceAlphaMod(m_pSurf_BoxUNSel, 127);

	m_bOnDrag = FALSE;

	m_strLabelBEG = "slow";
	m_strLabelEND = "fast";

}


////////////////////////////////////////
//       SetState
/*!
// \param eSate eVal :
*/
void   cProgressBarGfx::SetState(eSate eVal)
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
void   cProgressBarGfx::MouseMove(SDL_Event &event, SDL_Surface* pScreen, SDL_Surface* pScene_background)
{

}


////////////////////////////////////////
//       MouseUp
/*! Mouse up event
// \param SDL_Event &event :
*/
void   cProgressBarGfx::MouseUp(SDL_Event &event)
{
	if (m_eState == VISIBLE && m_bIsEnabled)
	{
		if (event.motion.x >= m_rctButt.x - m_rctCursor.w / 2 && event.motion.x <= m_rctButt.x + m_rctButt.w + m_rctCursor.w / 2 &&
			event.motion.y >= m_rctButt.y  && event.motion.y <= m_rctButt.y + m_rctButt.h)
		{
			if (m_bOnDrag)
			{
				// we are dragging the cursor
				int iXspace = (m_rctButt.x - m_rctButt.x + m_rctButt.w) / (m_iNumOfStep - 1);
				if (event.motion.x <= m_rctButt.x + iXspace / 2)
				{
					m_iCurrLevel = 0;
				}
				else if (event.motion.x >= m_rctButt.x + m_rctButt.w - iXspace / 2)
				{
					m_iCurrLevel = m_iNumOfStep - 1;
				}
				else
				{
					for (int i = 1; i < m_iNumOfStep; i++)
					{
						int iXInf = m_rctButt.x + iXspace * i - iXspace / 2;
						int iXSup = m_rctButt.x + iXspace * i + iXspace / 2;
						if (event.motion.x >= iXInf &&
							event.motion.x <= iXSup)
						{
							// level found
							m_iCurrLevel = i;
							break;
						}

					}
				}
				m_bOnDrag = FALSE;
			}
		}
		else
		{
			m_bOnDrag = FALSE;
		}
	}
}


////////////////////////////////////////
//       MouseDown
/*!
// \param SDL_Event &event :
*/
void   cProgressBarGfx::MouseDown(SDL_Event &event)
{
	if (m_eState == VISIBLE && m_bIsEnabled)
	{
		if (event.motion.x >= m_rctButt.x - m_rctCursor.w / 2 && event.motion.x <= m_rctButt.x + m_rctButt.w + m_rctCursor.w / 2 &&
			event.motion.y >= m_rctButt.y  && event.motion.y <= m_rctButt.y + m_rctButt.h)
		{
			m_bOnDrag = TRUE;
		}
	}
}


////////////////////////////////////////
//       Draw
/*! Draw the label with text
// \param SDL_Surface*  pScreen :
*/
void   cProgressBarGfx::Draw(SDL_Surface*  pScreen)
{
	ASSERT(m_iNumOfStep > 0);

	if (m_eState != INVISIBLE)
	{
		if (m_bIsEnabled)
		{

			// draw the horizontal base line
			int iX0 = m_rctButt.x;
			int iY0 = m_rctButt.y + (m_rctButt.h / 2);
			int iX1 = m_rctButt.x + m_rctButt.w;
			int iY1 = iY0;
			GFX_UTIL::DrawStaticLine(pScreen, iX0, iY0, iX1, iY1, GFX_UTIL_COLOR::Black);
			GFX_UTIL::DrawStaticLine(pScreen, iX0, iY0 - 1, iX1, iY1 - 1, GFX_UTIL_COLOR::Gray);
			// draw vertical marks
			int iYmarkoff = 3;
			int iXspace = (iX1 - iX0) / (m_iNumOfStep - 1);
			for (int i = 0; i < m_iNumOfStep; i++)
			{

				int iVX0 = i* iXspace + iX0;
				int iVY0 = iY0 - iYmarkoff;
				int iVX1 = iVX0;
				int iVY1 = iY0 + iYmarkoff;
				GFX_UTIL::DrawStaticLine(pScreen, iVX0, iVY0, iVX1, iVY1, GFX_UTIL_COLOR::Black);
				GFX_UTIL::DrawStaticLine(pScreen, iVX0 - 1, iVY0, iVX1 - 1, iVY1, GFX_UTIL_COLOR::Gray);
			}

			// draw labels

			// label on x0
			int tx, ty;
			int iXOffSet = 1;
			TTF_SizeText(m_pFontText, m_strLabelBEG.c_str(), &tx, &ty);
			int iYOffset = iYmarkoff + 1;
			GFX_UTIL::DrawString(pScreen, m_strLabelBEG.c_str(), iX0 + iXOffSet,
				iY0 + iYOffset, GFX_UTIL_COLOR::White, m_pFontText);

			// label on x1
			TTF_SizeText(m_pFontText, m_strLabelEND.c_str(), &tx, &ty);

			iXOffSet = iX1 - tx - iX0;
			GFX_UTIL::DrawString(pScreen, m_strLabelEND.c_str(), iX0 + iXOffSet,
				iY0 + iYOffset, GFX_UTIL_COLOR::White, m_pFontText);



			BOOL bUpBoxSel = FALSE;
			// draw the cursor
			if (m_iCurrLevel < 0)
			{
				m_iCurrLevel = 0;
			}
			else if (m_iCurrLevel >= m_iNumOfStep)
			{
				m_iCurrLevel = m_iNumOfStep - 1;
			}
			m_rctCursor.x = iX0 + m_iCurrLevel  * iXspace - m_rctCursor.w / 2;
			m_rctCursor.y = iY1 - m_rctCursor.h / 2;
			if (bUpBoxSel || m_bOnDrag)
			{
				GFX_UTIL::DrawStaticSpriteEx(pScreen, 0, 0, m_rctCursor.w, m_rctCursor.h, m_rctCursor.x,
					m_rctCursor.y, m_pSurf_BoxSel);
			}
			else
			{
				// draw unselected cursor
				GFX_UTIL::DrawStaticSpriteEx(pScreen, 0, 0, m_rctCursor.w, m_rctCursor.h, m_rctCursor.x,
					m_rctCursor.y, m_pSurf_BoxUNSel);
			}

			// draw the cursor border
			GFX_UTIL::DrawRect(pScreen, m_rctCursor.x, m_rctCursor.y,
				m_rctCursor.x + m_rctCursor.w, m_rctCursor.y + m_rctCursor.h, GFX_UTIL_COLOR::Black);

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
void   cProgressBarGfx::Redraw(SDL_Surface* pScreen, SDL_Surface* pScene_background)
{
	if (pScene_background)
	{
		SDL_BlitSurface(pScene_background, &m_rctButt, pScreen, &m_rctButt);
	}
	Draw(pScreen); // SDL_RenderPresent(renderer);
	//SDL_Flip(pScreen);
	SDL_Window* window;
	SDL_Renderer* renderer = SDL_CreateRenderer(window, -1, 0);
	SDL_RenderPresent(renderer);
}



////////////////////////////////////////
//       GetCurrLevel
/*! Provides the level
*/
int  cProgressBarGfx::GetCurrLevel()
{
	int iValOffset = (m_iUpRange - m_iLowRange) / m_iNumOfStep;
	if (iValOffset < 1)
	{
		iValOffset = 1;
	}

	int iValFin = m_iCurrLevel * iValOffset + m_iLowRange;

	return iValFin;
}
