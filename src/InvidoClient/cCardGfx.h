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

// cCardGfx.h: interface for the cCardGfx class.
//
//////////////////////////////////////////////////////////////////////

#if !defined(AFX_CCARDGFX_H__847DB6F1_F1C0_4EC1_84D4_D3309DE28A52__INCLUDED_)
#define AFX_CCARDGFX_H__847DB6F1_F1C0_4EC1_84D4_D3309DE28A52__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000

#include "SDL.h"
#include "cInvidoCoreEnv.h"
#include "CardSpec.h"



//! class cCardGfx
class cCardGfx  
{
public:
    enum eState
    {
        CSW_ST_INVISIBLE,
        CSW_ST_VISIBLE,
        CSW_ST_ROTATE90,
        CSW_ST_SELECTED1,
        CSW_ST_SELECTED2,
        CSW_ST_MAZZO,
        CSW_ST_SYMBOL,
        CSW_ST_BACK,

    };
    enum
    {
        SYMBOL_O = 1,
        SYMBOL_X = 2,
        SYMBOL_BRISCNET = 3,
    };

    //! constructor
    cCardGfx();
    //! destructor
    virtual ~cCardGfx();
    
    //! set symbol card
    void SetSymbolTocard(int iSymbol, int iW, int iH, SDL_Surface*  pScreen);

    //! set card information
    void SetCardInfo(int iIndex, int iW, int iH);
    //! set deck sourface
    void SetDeckSurface(SDL_Surface* pVal, int w, int h ){m_pDeck = pVal; m_iWidth = w; m_iHeight = h;}
    //! set deck simbol sourface
    void SetSymbSurf(SDL_Surface* pVal, int w, int h){m_pSymbols = pVal; m_iSymbWidth = w; m_iSmbHeight = h; }
    
    //! return true if the point is inner the card
    bool MouseInCard(int xCoord, int yCoord);
    //! copy from model
    void Copy(cCardGfx* pModel);
    //! copy model but not the position
    void CopyButNoPosition(cCardGfx* pModel);
    //! draw a card
    int  DrawCard(SDL_Surface *s);
    //! draw symbol
    int  DrawSymbol(SDL_Surface *s);
    //! draw card backside
    int  DrawCardBack( SDL_Surface *s);
    //! draw card, symbol or nothing, depend on the state
    int  DrawGeneric(SDL_Surface *s);
    //! start to draw a card reversed
    void StartShowReversed();

    CardSpec   cardSpec;

    //! x coordinate
    int        m_iX;
    //! y coordinate
    int        m_iY;
    //! speed in x
    int        m_iVx;
    //! speed in y
    int        m_iVy;
    //! width
    int        m_iWidth;
    //! height
    int        m_iHeight;
    //! symbol width
    int        m_iSymbWidth;
    //! symbol height
    int        m_iSmbHeight;
    //! state
    eState     State;
    //! complete deck image
    SDL_Surface*      m_pDeck;
    //! complete symbol sourface
    SDL_Surface*      m_pSymbols;
    //! z order
    int               m_iZOrder;
    //! surface where to draw the button
    SDL_Surface*      m_pSurf_Bar;
    //! bar height
    int               m_iBarHeight;
    //! bar width
    int               m_iBarWidth;
private:
    //! reversed flag
    BOOL     m_bDrawReversed;
    //! init tick for reversing
    Uint32   m_uiInitRevTick;
    //! tick to shows reversed
    Uint32   m_uiShowRevTick;
    //! reversed card surface
    SDL_Surface* m_pReversedSurf;
 
};

#endif // !defined(AFX_CCARDGFX_H__847DB6F1_F1C0_4EC1_84D4_D3309DE28A52__INCLUDED_)
