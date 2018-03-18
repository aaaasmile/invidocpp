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



//cPopUpMenuGfx.h

#ifndef C_POPUPMENUGFX_H__
#define C_POPUPMENUGFX_H__

#include "win_type_global.h"
#include <SDL.h>
#include <SDL_ttf.h>
#include <vector>



//! class cPopUpMenuGfx
class DLL_EXPORTIMPORT cPopUpMenuGfx
{
    typedef std::vector<STRING> VCT_STRING;
public:
    cPopUpMenuGfx(void);
    ~cPopUpMenuGfx(void);

    //! init the msgbox
    void   Init(SDL_Rect* pRect, SDL_Surface*  pScreen, TTF_Font* pFont );
    //! show the message box
    void   Show(SDL_Surface* pScene_background);
    //! add a line in the combo
    void   AddLineText(LPCSTR strLine);
    //! provides the selected index
    int    GetSlectedIndex(){return m_iCurrDataIndex;}
    //! provides the selected flag
    BOOL   MenuIsSelected(){return m_bMenuSelected;}

private:
    //! rectangle of the messagebox
    SDL_Rect      m_rctMsgBox; 
    //! surface where to draw the button
    SDL_Surface*    m_pSurf_Bar;
    //! surface screen
    SDL_Surface*    m_pScreen;
    //! button font
    TTF_Font*	    m_pFontText;
    //! current text color
    SDL_Color       m_colCurrent;
    //! terminated flag
    BOOL            m_bTerminated;
    //! vector of data strings
    VCT_STRING      m_vctDataStrings;
    //! current index
    int             m_iCurrDataIndex;
    //! menu selected flag
    BOOL            m_bMenuSelected;

};


#endif

