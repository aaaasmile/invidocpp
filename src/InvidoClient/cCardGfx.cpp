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

// cCardGfx.cpp

#include "StdAfx.h"
#include "win_type_global.h"
#include "cCardGfx.h"
#include "gfx_util.h"


////////////////////////////////////////
//       cCardGfx
/*! Constructor
*/
cCardGfx::cCardGfx()
{
    m_iX = 0; 
    m_iY = 0;
    m_iVx = 0;
    m_iVy = 0;
    m_iWidth = 0; 
    m_iHeight = 0; 
    State = CSW_ST_INVISIBLE; 
    m_pDeck = 0;
    m_pSymbols = 0;
    m_iZOrder = 0;
    m_pSurf_Bar = 0;
    m_iBarHeight = 0;
    m_iBarWidth = 0;
    m_bDrawReversed = FALSE; 
    m_pReversedSurf = NULL;
    
}


////////////////////////////////////////
//       ~cCardGfx
/*! 
*/
cCardGfx::~cCardGfx()
{
    if (m_pReversedSurf)
    {
       SDL_FreeSurface( m_pReversedSurf);
       m_pReversedSurf = 0;
    }
}

////////////////////////////////////////
//       MouseInCard
/*! True if the mouse is inner to the card
// \param int xCoord : x coordinate to check
// \param int yCoord : y coordinate to check
*/
bool cCardGfx::MouseInCard(int xCoord, int yCoord)
{
    if(State == CSW_ST_INVISIBLE)
    {
		return false;
    }

	bool bRet = false;
	
	if( xCoord >= m_iX  && xCoord <= m_iX + m_iWidth &&   yCoord >= m_iY   && yCoord <= m_iY  + m_iHeight)
    {
	    bRet = true;
    }

	return bRet;
}


////////////////////////////////////////
//       SetSymbolTocard
/*! Set information about card symbol
// \param int iSymbol : symbol index
// \param int iWidth : width of the symbol
// \param int iHeight : height of the symbol
*/
void cCardGfx::SetSymbolTocard(int iSymbol, int iW, int iH, SDL_Surface*  pScreen)
{
    
    m_iWidth = iW  ;
    m_iHeight = iH;
    cardSpec.SetSymbol(iSymbol);
    State = CSW_ST_SYMBOL; 
}


////////////////////////////////////////
//       SetCardInfo
/*! Set information of a front card
// \param int iIndex : index of the card
// \param int iW : width of the card
// \param int iH : height of the card
*/
void cCardGfx::SetCardInfo(int iIndex, int iW, int iH)
{
    m_iWidth = iW  ;
    m_iHeight = iH;
    cardSpec.SetCardIndex(iIndex);
    State = cCardGfx::CSW_ST_VISIBLE;
}


////////////////////////////////////////
//       StartShowReversed
/*! Start point to show a card in reversed color
*/
void cCardGfx::StartShowReversed()
{
    m_bDrawReversed = TRUE;    
    m_uiInitRevTick = SDL_GetTicks();
    m_uiShowRevTick = 120;
}



////////////////////////////////////////
//       Copy
/*! Build the card information from a model
// \param cCardGfx* pModel : model to copy
*/
void cCardGfx::Copy(cCardGfx* pModel)
{
    m_iWidth = pModel->m_iWidth   ;
    m_iHeight = pModel->m_iHeight ;
    m_iX = pModel->m_iX;
    m_iY = pModel->m_iY;
    m_iVy = pModel->m_iVy;
    m_iVx = pModel->m_iVx; 
    State = pModel->State;
    cardSpec = pModel->cardSpec; 
}


////////////////////////////////////////
//       CopyButNoPosition
/*! Copy some information, but not the position
// \param cCardGfx* pModel : reference to copy
*/
void cCardGfx::CopyButNoPosition(cCardGfx* pModel)
{
    m_iWidth = pModel->m_iWidth   ;
    m_iHeight = pModel->m_iHeight ;
    State = pModel->State;
    cardSpec = pModel->cardSpec; 
}

////////////////////////////////////////
//       DrawCard
/*! Draw a card on the surface s
// \param SDL_Surface *s : destination surface
*/
int cCardGfx::DrawCard(SDL_Surface *s)
{
	ASSERT(m_pDeck);
    ASSERT(s);
    int nCdIndex = cardSpec.GetCardIndex();

	if(nCdIndex < 0) 
    {
        nCdIndex = 0;
        ASSERT(0);
    }
	if(nCdIndex > NUM_CARDS_MAZZBRI) 
    {
        nCdIndex = NUM_CARDS_MAZZBRI - 1;
        ASSERT(0)
    }

	int iSegnoIx = nCdIndex / 10;
	int iCartaIx = nCdIndex % 10;


    SDL_Rect SrcCard;
	SrcCard.x = iSegnoIx * m_iWidth;
    SrcCard.y = iCartaIx * m_iHeight;
    SrcCard.w = m_iWidth;
    SrcCard.h = m_iHeight;

    SDL_Rect dest;
	dest.x = m_iX;
	dest.y = m_iY;

    if (m_bDrawReversed)
    {
        // we have to show the card reversed
        Uint32 uiNowTime = SDL_GetTicks();
        if ( (uiNowTime - m_uiInitRevTick) < m_uiShowRevTick)
        {
            SDL_Rect rctCardDim;
            rctCardDim.w = m_iWidth;
            rctCardDim.h = m_iHeight;
            rctCardDim.x = 0;
            rctCardDim.y = 0;
            if (m_pReversedSurf == NULL)
            {
                m_pReversedSurf = SDL_CreateRGBSurface(SDL_SWSURFACE, rctCardDim.w, rctCardDim.h, 32, 0, 0, 0, 0);
                SDL_FillRect(m_pReversedSurf, NULL, SDL_MapRGBA(s->format, 0, 0, 0, 0));
            
            }
            return SDL_BlitSurface(m_pReversedSurf, &rctCardDim, s, &dest);
        }
        else
        {
            // time out, restore normal view
            m_bDrawReversed = FALSE;
        }
    }
    
    /*
    TRACE("Draw card ix = %d, segno = %d, nome = %s \n", 
        pCard->cardSpec.GetCardIndex() , pCard->cardSpec.GetSuit(), pCard->cardSpec.GetName() ); 
        */

	return SDL_BlitSurface(m_pDeck, &SrcCard, s, &dest);
}

////////////////////////////////////////
//       DrawSymbol
/*! Draw a card as symbol
// \param SDL_Surface *s : destination surface
// \param nSymbol: symbol number
*/
int cCardGfx::DrawSymbol( SDL_Surface *s)
{
    ASSERT(m_pSymbols);

    int nSymbol = cardSpec.GetSymbol();
	ASSERT(nSymbol>= 1 && nSymbol <= 3);

	SDL_Rect SrcCard;
	SrcCard.x = nSymbol * m_iWidth;
    SrcCard.y = 0;
    SrcCard.w = m_iWidth;
    SrcCard.h = m_iHeight;


	SDL_Rect dest;
	dest.x = m_iX;
	dest.y = m_iY;

    //GFX_UTIL::DrawStaticSpriteEx(s, SrcCard.x, SrcCard.y, SrcCard.w, SrcCard.h, dest.x, dest.y, m_pSurf_Bar);
    SDL_SetAlpha (m_pSymbols, SDL_SRCALPHA, 120) ;
    SDL_BlitSurface(m_pSymbols, &SrcCard, s, &dest);
    return 0;
}

////////////////////////////////////////
//       DrawCardBack
/*! Draw the back site of the card
// \param SDL_Surface *s : destination surface
*/
int cCardGfx::DrawCardBack( SDL_Surface *s)
{
	ASSERT(s);
    ASSERT(m_pSymbols);
	SDL_Rect dest;
	dest.x = m_iX;
	dest.y = m_iY;

    SDL_Rect SrcCard;
	SrcCard.x = 0;
    SrcCard.y = 0;
    SrcCard.w = m_iWidth;
    SrcCard.h = m_iHeight;
    SDL_SetAlpha (m_pSymbols, SDL_SRCALPHA, 255) ;
	return SDL_BlitSurface(m_pSymbols, &SrcCard, s, &dest);
}


////////////////////////////////////////
//       DrawGeneric
/*! Draw card, symbol or nothing, depend on the state
*/
int cCardGfx::DrawGeneric(SDL_Surface *s)
{
    int iRetVal = 0;
    if (this->State == cCardGfx::CSW_ST_INVISIBLE)
    {
        return 0;
    }
    else if (this->State == cCardGfx::CSW_ST_SYMBOL)
    {
        iRetVal = this->DrawSymbol( s );
    }
    else if (this->State == cCardGfx::CSW_ST_VISIBLE)
    {
        iRetVal = this->DrawCard( s );
    }
    else if (this->State == cCardGfx::CSW_ST_BACK)
    {
        iRetVal = this->DrawCardBack(s);
    }
    else
    {
        ASSERT(0);
    }
    return iRetVal;
}
