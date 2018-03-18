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

// cAlgPythonPlayer.cpp: implementation of the cAlgPythonPlayer class.
//
//////////////////////////////////////////////////////////////////////
#include "StdAfx.h"
#include "cAlgPythonPlayer.h"
#include "cInvidoCoreEngine.h"
#include "PythonExport.h"


#ifdef _DEBUG
#undef THIS_FILE
static char THIS_FILE[]=__FILE__;
#define new DEBUG_NEW
#endif

//////////////////////////////////////////////////////////////////////
// Construction/Destruction
//////////////////////////////////////////////////////////////////////

cAlgPythonPlayer::cAlgPythonPlayer()
{
    m_pCoreGame = 0;
    m_iOppIndex = NOT_VALID_INDEX;
}

cAlgPythonPlayer::~cAlgPythonPlayer()
{

}


////////////////////////////////////////
//       ALG_SetCoreInterface
/*! 
// \param I_CORE_Game* pCore : 
*/
void cAlgPythonPlayer::ALG_SetCoreInterface(I_CORE_Game* pCore)
{
    m_pCoreGame = pCore;
}


////////////////////////////////////////
//       ALG_SetPlayerIndex
/*! set player index
// \param int iIndex : 
*/
void cAlgPythonPlayer::ALG_SetPlayerIndex(int iIndex) 
{
    m_iMyIndex = iIndex;
}


////////////////////////////////////////
//       ALG_SetOpponentIndex
/*! set opponent index
// \param int iIndex : 
// \param int iOpponentNr : 
*/
void cAlgPythonPlayer::ALG_SetOpponentIndex(int iIndex, int iOpponentNr) 
{
    m_iOppIndex =  iIndex;
}


////////////////////////////////////////
//       ALG_SetAssociateIndex
/*! 
// \param int iIndex : 
*/
void cAlgPythonPlayer::ALG_SetAssociateIndex(int iIndex) 
{

}


////////////////////////////////////////
//       ALG_NewMatch
/*! new match notification
// \param int iNumPlayer : 
*/
void cAlgPythonPlayer::ALG_NewMatch(int iNumPlayer) 
{
    
}


////////////////////////////////////////
//       ALG_NewGiocata
/*! new giocata notification
// \param CARDINFO* pCardArray : 
// \param int iNumOfCards : 
*/
void cAlgPythonPlayer::ALG_NewGiocata(CARDINFO* pCardArray, int iNumOfCards, int iPlayerIx) 
{
    ASSERT(iNumOfCards == NUM_CARDS_HAND);
    for (int i = 0; i < NUM_CARDS_HAND; i++)
    {
        m_vct_Cards_CPU[i].SetCardInfo(pCardArray[i]); 
    }
}


////////////////////////////////////////
//       ALG_PlayerHasPlayed
/*! player has played a card
// \param int iPlayerIx : 
// \param CARDINFO* pCard : 
*/
void cAlgPythonPlayer::ALG_PlayerHasPlayed(int iPlayerIx, CARDINFO* pCard) 
{
    ASSERT(pCard);
    if (iPlayerIx == m_iMyIndex)
    {
        CardSpec Card;
        CardSpec CardUndef;
        Card.SetCardInfo(*pCard); 
        BOOL bFound = FALSE;
        // card successfully played
        for (int i = 0; !bFound && i < NUM_CARDS_HAND; i++)
        {
            if (Card == m_vct_Cards_CPU[i])
            {
                // card found
                m_vct_Cards_CPU[i] = CardUndef;
                bFound = TRUE;
            }
        }
        ASSERT(bFound);
    }
}

////////////////////////////////////////
//       ALG_PlayerHasSaid
/*! player has said something
// \param int iPlayerIx : 
// \param eSayPlayer eSay : 
*/
void cAlgPythonPlayer::ALG_PlayerHasSaid(int iPlayerIx, eSayPlayer eSay) 
{
    if (iPlayerIx == m_iOppIndex)
    {
        m_OpponentSay = eSay;
    }
}


////////////////////////////////////////
//       ALG_Play
/*! player have to play notification
*/
void cAlgPythonPlayer::ALG_Play() 
{
    std::cout << "[ALG] have to play\n";
   
    g_pInvidoCore->NotifyScriptAlgorithm(m_iMyIndex, SCR_NFY_HAVETO_PLAY);
}

////////////////////////////////////////
//       ALG_ManoEnd
/*! mano end notification
*/
void cAlgPythonPlayer::ALG_ManoEnd(I_MatchScore* pScore) 
{
    g_pInvidoCore->NotifyScriptAlgorithm(m_iMyIndex, SCR_NFY_ALGMANOEND);
}

////////////////////////////////////////
//       ALG_GiocataEnd
/*! 
*/
void cAlgPythonPlayer::ALG_GiocataEnd(I_MatchScore* pScore) 
{
    g_pInvidoCore->NotifyScriptAlgorithm(m_iMyIndex, SCR_NFY_ALGGIOCATAEND);
}

////////////////////////////////////////
//       ALG_MatchEnd
/*! match end notification
*/
void cAlgPythonPlayer::ALG_MatchEnd(I_MatchScore* pScore) 
{
    g_pInvidoCore->NotifyScriptAlgorithm(m_iMyIndex, SCR_NFY_ALGMATCHEND);
}

////////////////////////////////////////
//       ALG_Say
/*! Algorithm is invited to responce
*/
void cAlgPythonPlayer::ALG_Say()
{

    //eSayPlayer eSayRsp = AMONTE;
    //m_pCoreGame->Player_saySomething(m_iMyIndex, eSayRsp); 
    std::cout << "[ALG] have to response\n";
    g_pInvidoCore->NotifyScript(SCR_NFY_HAVETO_SAY);
}


////////////////////////////////////////
//       ALG_GicataScoreChange
/*! 
// \param eGiocataScoreState eNewScore : 
*/
void cAlgPythonPlayer::ALG_GicataScoreChange(eGiocataScoreState eNewScore)
{
    m_eScoreCurrent = eNewScore;
}


////////////////////////////////////////
//       ALG_PLayerSaidFalse
/*! player said somithing false
// \param int iPlayerIx : 
*/
void cAlgPythonPlayer::ALG_PLayerSaidFalse(int iPlayerIx)
{
}


