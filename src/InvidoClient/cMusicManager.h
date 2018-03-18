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

// cMusicManager.h: interface for the cMusicManager class.
//
//////////////////////////////////////////////////////////////////////

#if !defined(AFX_CMUSICMANAGER_H__166CCA3D_1404_45EE_821B_544A592F0B4F__INCLUDED_)
#define AFX_CMUSICMANAGER_H__166CCA3D_1404_45EE_821B_544A592F0B4F__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000

#include "SDL_mixer.h"


//! class cMusicManager  
class cMusicManager  
{
public:
    enum
    {
        /*
        // DON'T change the position or change the load sequence
        SND_IG_CHIAMAPIU = 0,
        SND_IG_FUORIGIOCO,
        SND_IG_INV_LONG,
        SND_IG_INV_NORM,
        SND_IG_INV_SECCO,
        SND_IG_MONTE_AMUNT,
        SND_IG_MONTE_NORM,
        SND_IG_NO_BORTOLO,
        SND_IG_NO_FRONTE,
        SND_IG_NO_NORMAL,
        SND_IG_PARTIDA,
        SND_IG_TRASMAS_LONG,
        SND_IG_TRASMAS_NEUT,
        SND_IG_NOEF_DILECT,
        SND_IG_NOEF_NORMA,
        SND_IG_VABENE_GIOCA,
        SND_IG_VABENEONLY,
        SND_IG_VAVIA,
        // DON'T change the position or change the load sequence 
        SND_IG_VUVIA,
     // if you want to add music, make here:
     */
        MUSIC_INIT_SND,
        //MUSIC_ONPLAY,
     //... untill herre. Thank you.
        NUM_OF_SOUNDS
    };
    enum
    {
        // synth voice
        SND_WAV_SYF_MONTE,
        SND_WAV_SYF_VUVIA,
        SND_WAV_SYF_CHIADIPIU,
        SND_WAV_SYF_FUORIGI,
        SND_WAV_SYF_INVIDO,
        SND_WAV_SYF_NO,
        SND_WAV_SYF_PARTIDA,
        SND_WAV_SYF_TRASMAS,
        SND_WAV_SYF_NOEF,
        SND_WAV_SYF_VABENE,
        SND_WAV_SYF_GIOCA,
        // igor voice
        SND_IG_CHIAMAPIU,
        SND_IG_FUORIGIOCO,
        SND_IG_GIOCA,
        SND_IG_INV_NORM,
        SND_IG_MONTE_NORM,
        SND_IG_NO,
        SND_IG_PARTIDA,
        SND_IG_TRASMAS,
        SND_IG_TRASNOEF,
        SND_IG_VABENE,
        SND_IG_VUVIA,
        //effects
        SND_EFC_CLICK,

        NUM_OF_WAV
    };
    enum eLoopType
    {
        LOOP_ON,
        LOOP_OFF
    };
    //! constructor
	cMusicManager();
    //! destructor
	virtual ~cMusicManager();

    //! init stuff
    void Init();
    //! stop playng music
    void StopMusic();
    //! play a music resource
    BOOL PlayMusic(int iID, eLoopType eVal);
    //! play an effect (wav only)
    BOOL PlayEffect(int iID);
    //! load music resource
    void LoadMusicRes();
    //! info on playing music
    BOOL IsPLayingMusic();
    //! change the volume music
    void SetVolumeMusic(int iVal);

private:
    //! music collection  
    Mix_Chunk*        m_pMusicsWav[NUM_OF_WAV];
    Mix_Music*        m_pMusics[NUM_OF_SOUNDS];
    //! music available flag
    BOOL     m_bMusicAvailable;

};

#endif // !defined(AFX_CMUSICMANAGER_H__166CCA3D_1404_45EE_821B_544A592F0B4F__INCLUDED_)
