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


// cButtonGfx.h: interface for the cButtonGfx class.
//
//////////////////////////////////////////////////////////////////////

#if !defined(AFX_CBUTTONGFX_H__2F3F455A_3EA3_49D6_84D9_A7D4188985C3__INCLUDED_)
#define AFX_CBUTTONGFX_H__2F3F455A_3EA3_49D6_84D9_A7D4188985C3__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000

#include "win_type_global.h"
#include <SDL.h>
#include <SDL_ttf.h>

#include "FastDelegate.h"
using namespace fastdelegate;


//! class  cButtonGfx  
class DLL_EXPORTIMPORT cButtonGfx  
{
    // use fastdelegate to implement the observer pattern and avoid using the callback interface on observer
    typedef FastDelegate1<int> CLICKEVENT;
    
public:
    //! enum eSate
    enum  eSate
    {
        VISIBLE,
        INVISIBLE,
        PRESSED
    };

    enum eType
    {
        TEXT_BUTTON,
        BITMAP_BUTTON
    };

	cButtonGfx();
   	virtual ~cButtonGfx();

    //! init the control 
    void   Init(SDL_Rect* pRect, SDL_Surface*  pScreen, TTF_Font* pFont, int iButID);
    //! set window text
    void   SetWindowText(LPCSTR strCaption){m_strButText = strCaption;}
    //! mouse move event
    void   MouseMove(SDL_Event &event, SDL_Surface* pScreen, SDL_Surface* pScene_background);
    //! mouse up
    void   MouseUp(SDL_Event &event);
    //! mouse down
    void   MouseDown(SDL_Event &event, SDL_Surface* pScreen, SDL_Surface* pScene_background);
    //! draw the button 
    void   DrawButton(SDL_Surface*  pScreen);
    //! enable the button
    void   EnableWindow(BOOL bVal){m_bIsEnabled = bVal;}
    //! set button state
    void   SetState(eSate eVal);
    //! redraw the button
    void   RedrawButton(SDL_Surface* pScreen, SDL_Surface* pScene_background);
    //! set a button type (bitmap or text)
    void   SetButtonType(eType eTypevalue){m_eButType = eTypevalue;}
    //! set bitmap surfaces
    void   SetButBitmapSurfaces(SDL_Surface* pS1, SDL_Surface* pS2, SDL_Surface* pS3)
        {m_pSurf_Bitmap_Act1 = pS1; m_pSurf_Bitmap_MOv2 = pS2; m_pSurf_Bitmap_Pus3 = pS3;}

private:
    void   drawBtAsBitmap(SDL_Surface*  pScreen);

public:
    //! button state
    eSate         m_eState;
    //! rectangle of the button
    SDL_Rect      m_rctButt; 
    //! text on the button
    STRING        m_strButText;
    //! enabled flag
    BOOL          m_bIsEnabled;
    //! click the event
    CLICKEVENT    m_fncbClickEvent;

private:
    //! surface where to draw the button
    SDL_Surface*    m_pSurf_Bar;
    //! button font
    TTF_Font*	    m_pFontText;
    //! current text color
    SDL_Color       m_colCurrent;
    //! button id
    int             m_iButID;
    //! button is hold down
    BOOL            m_bMouseIsDown;
    //! button type
    eType           m_eButType;
    //! normal bitmap bitmap
    SDL_Surface*    m_pSurf_Bitmap_Act1;
    //! mouse over bitmap
    SDL_Surface*    m_pSurf_Bitmap_MOv2;
    //! button pushed bitmap
    SDL_Surface*    m_pSurf_Bitmap_Pus3;
    

};

#endif // !defined(AFX_CBUTTONGFX_H__2F3F455A_3EA3_49D6_84D9_A7D4188985C3__INCLUDED_)
