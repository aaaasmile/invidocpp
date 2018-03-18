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

// OptionGfx.h: interface for the OptionGfx class.
//
//////////////////////////////////////////////////////////////////////

#if !defined(AFX_OPTIONGFX_H__A046DEBA_EC10_4D5D_A499_EF9A331516FD__INCLUDED_)
#define AFX_OPTIONGFX_H__A046DEBA_EC10_4D5D_A499_EF9A331516FD__INCLUDED_

#include "win_type_global.h"
#include <SDL.h>
#include <SDL_ttf.h>
#include <vector>

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000

class cButtonGfx;
class cCheckBoxGfx;
class cEditGfx;
class cComboGfx;
class cProgressBarGfx;

//! calss OptionGfx
class OptionGfx  
{
    typedef std::vector<STRING> VCT_STRING;
    enum
    {
        MYIDOK = 0,
        MYIDCANCEL = 1,
        MYIDMUSICCHK = 2,
        MYEDITNAME = 3,
        MYIDCOMBOLAN = 4,
        MYIDSOUNDEFFECT = 5,
        MYIDCOMBOALG_PL1 = 6,
        MYIDCOMBOALG_PL2 = 7,
        MYIDCOMBOALG_PL3 = 8,
        MYIDCOMBOALG_PL4 = 9,
        MYIDCHKSHOWALGCONTROL = 10,
        MYIDCHKSHOWANIMATIONS = 11,
        MYIDPROGBARSPEEDANI = 12,
        MYIDCHKBLOCKAFTERMANOEND = 13,
        MYIDCHKSIGNALRMOUSE = 14,
        MYIDSHOWFOTOBACK = 15
    };
public:
	OptionGfx();
	virtual ~OptionGfx();

    //! init control
    void Init(SDL_Rect* pRect, SDL_Surface*  pScreen, TTF_Font* pFontTxt, TTF_Font* pFontWinCtrl);
    //! shows the control
    void Show(SDL_Surface* pScene_background);
    //! button click callback
    void ButCmdClicked(int iButID);
    //! checkbox callback
    void ClickCheckBox(int iButID);
    //! combobox callback
    void ComboCmdClicked(int iButID);
    //! set caption text
    void SetCaption(STRING& strCaption){m_strHeaderText = strCaption;}

    
private:
    //! rectangle of the options control
    SDL_Rect        m_rctOptBox; 
    //! text on the messagebox
    SDL_Surface*    m_pSurf_Bar;
    //! surface screen
    SDL_Surface*    m_pScreen;
    //! text font
    TTF_Font*	    m_pFontText;
    //! button font
    TTF_Font*	    m_pFontCtrl;
    //! current text color
    SDL_Color       m_colCurrent;
    //! button 1
    cButtonGfx*     m_pBtOK;
    //! button 2
    cButtonGfx*     m_pBtCancel;
    //! terminated flag
    BOOL            m_bTerminated;
    //! result of click
    int             m_iResult;
    //! header text
    STRING          m_strHeaderText;
    //! checkbox music
    cCheckBoxGfx*   m_pCheckMusic;
    //! checkbox effect
    cCheckBoxGfx*   m_pCheckSoundEffect;
    //! checkbox show foto back 
    cCheckBoxGfx*   m_pCheckShowFotoBack;
    //! Name edit control
    cEditGfx*       m_pEditName;
    //! combo language selection
    cComboGfx*      m_pComboLang;
    //! installed plugin list
    VCT_STRING      m_vct_InstPlugDllName;
    //! installed plugin engine name
    VCT_STRING      m_vct_PlugEngineName;
    //! shows advanced flag
    BOOL            m_bShowAlgControls;
    //! flag show progress bar animation speed
    BOOL              m_bShowProgSpeedAni;
   
};

#endif // !defined(AFX_OPTIONGFX_H__A046DEBA_EC10_4D5D_A499_EF9A331516FD__INCLUDED_)
