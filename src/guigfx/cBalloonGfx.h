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


// cBalloonGfx.h: interface for the cBalloonGfx class.
//
//////////////////////////////////////////////////////////////////////

#if !defined(AFX_CBALLOONGFX_H__E3B36325_213E_4794_8FDC_43E3046E0A79__INCLUDED_)
#define AFX_CBALLOONGFX_H__E3B36325_213E_4794_8FDC_43E3046E0A79__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000

#include "win_type_global.h"
#include <SDL.h>
#include <SDL_ttf.h>



//! class   cBalloonGfx  
class DLL_EXPORTIMPORT cBalloonGfx  
{
public:
    //! enum eStyle
    enum eStyle
    {
        ARROW_DWN_LEFT,
        ARROW_DWN_RIGHT,
        ARROW_UP
    };
public:
	cBalloonGfx();
	virtual ~cBalloonGfx();

    //! init balloon
    void Init(SDL_Rect& rct, SDL_Surface* pImage, TTF_Font* pFont);
    //! set style
    void SetStyle(eStyle eVal, SDL_Surface* pImage);
    //! draw control
    void Draw(SDL_Surface* pScreen);
    //! start show the control
    void StartShow(LPCSTR lpszText);
    void StartShow(LPCSTR lpszText, Uint32 uiTick);
    //! disable
    void Disable();
    //! provides the enable flag
    BOOL GetEnableState(){return m_bEnabled;}

private:
    void    startshow(LPCSTR lpszText, Uint32 uiTick);

private:
    //! ballon position
    SDL_Rect      m_destWIN;
    //! arrow position
    SDL_Rect      m_ArrWIN;
    //! ballon image
    SDL_Surface*  m_pImageBall;
    //! arrow image
    SDL_Surface*  m_pImageArrow;
    //! string text
    STRING        m_strText;
    //! second line text
    STRING        m_strText2;
    //! init tick
    Uint32        m_uiInitTick;
    //! showing time
    Uint32        m_uiShowTick;
    //! balloon enabled
    BOOL          m_bEnabled;
    //! button font
    TTF_Font*	  m_pFontText;
    //! current text color
    SDL_Color     m_colCurrent;
    //! style
    eStyle        m_eStyle;
};

#endif // !defined(AFX_CBALLOONGFX_H__E3B36325_213E_4794_8FDC_43E3046E0A79__INCLUDED_)
