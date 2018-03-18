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

// fading.h

/* 
  Fading with alphablending
  (c) Patrick Kooman, 2002
  contact: patrick@2dgame-tutorial.com
*/

#include <stdio.h>
#include "SDL.h"

/* Fades the given surface in or out to the given screen within the given time */
void fade (SDL_Surface* p_surf_screen, SDL_Surface* p_surf_img, Uint32 ui_seconds, int i_fade_out) ;

/* Cross-Fades the given surfaces onto the given screen within the given time */
void crossFade (SDL_Surface* p_surf_screen, SDL_Surface* p_surf_img1, SDL_Surface* p_surf_img2, Uint32 ui_seconds) ;
