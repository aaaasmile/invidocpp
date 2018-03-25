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


// cComboGfx.h: interface for the cComboGfx class.
//
//////////////////////////////////////////////////////////////////////

#if !defined(AFX_cComboGfx_H__2F3F455A_3EA3_49D6_84D9_A7D4188985C3__INCLUDED_)
#define AFX_cComboGfx_H__2F3F455A_3EA3_49D6_84D9_A7D4188985C3__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000

#include "win_type_global.h"
#include <SDL.h>
#include <SDL_ttf.h>

#include <vector>
#include "FastDelegate.h"
using namespace fastdelegate;


//! class  cComboGfx  
class DLL_EXPORTIMPORT cComboGfx  
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

	cComboGfx();
   	virtual ~cComboGfx();

    //! init the control 
    void   Init(SDL_Rect* pRect, SDL_Surface*  pScreen, TTF_Font* pFont, int iButID);
    //! set window text
    void   SetWindowText(LPCSTR strCaption){m_strButText = strCaption;}
    //! mouse move event
    void   MouseMove(SDL_Event &event, SDL_Surface* pScreen, SDL_Surface* pScene_background);
    //! mouse up
    void   MouseUp(SDL_Event &event);
    //! draw the button 
    void   DrawButton(SDL_Surface*  pScreen);
    //! enable the button
    void   EnableWindow(BOOL bVal){m_bIsEnabled = bVal;}
    //! set button state
    void   SetState(eSate eVal);
    //! redraw the button
    void   RedrawButton(SDL_Surface* pScreen, SDL_Surface* pScene_background);
    //! add a line in the combo
    void   AddLineText(LPCSTR strLine);
    //! select an index
    void   SelectIndex(UINT iIndex);
    //! provides the selected index
    int    GetSlectedIndex(){return m_iCurrDataIndex;}
    //! provides the selected text
    LPCSTR GetSelectedText(){return m_vctDataStrings[m_iCurrDataIndex].c_str();}

public:
    //! button state
    eSate         m_eState;
    //! rectangle of the button
    SDL_Rect      m_rctButt; 
    //! rect area text
    SDL_Rect      m_rctText;
    //! rect area up
    SDL_Rect      m_rctBoxUp;
    //! rect area down
    SDL_Rect      m_rctBoxDown;
    //! text on the button
    STRING        m_strButText;
    //! enabled flag
    BOOL          m_bIsEnabled;
    //! click the event
    CLICKEVENT    m_fncbClickEvent;

private:
    //! surface where to draw the button
    SDL_Surface*    m_pSurf_Bar;
    //! selected surface
    SDL_Surface*    m_pSurf_BoxSel;
    //! unselected surface
    SDL_Surface*    m_pSurf_BoxUNSel;
    //! button font
    TTF_Font*	    m_pFontText;
    //! current text color
    SDL_Color       m_colCurrent;
    //! button id
    int             m_iButID;
    //! vector of data strings
    VCT_STRING      m_vctDataStrings;
    //! current index
    UINT            m_iCurrDataIndex;
    

};

#endif // !defined(AFX_cComboGfx_H__2F3F455A_3EA3_49D6_84D9_A7D4188985C3__INCLUDED_)
