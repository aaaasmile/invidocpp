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



//gfx_util.h

#ifndef __GFX_UTIL__H
#define __GFX_UTIL__H

#include "SDL.h"
#include "SDL_ttf.h"
#include <string>

namespace  GFX_UTIL
{
	///READ PIXEL FROM A SURFACE
	DLL_EXPORTIMPORT Uint32 inline GetPixel(SDL_Surface *surface, int x, int y);
	///WRITE PIXEL TO A SURFACE
	DLL_EXPORTIMPORT void inline   SetPixel(SDL_Surface *surface, int x, int y, Uint32 pixel);

	///DRAW A NON-FILLED BOX (RGBA)
	DLL_EXPORTIMPORT void rectangleRGBA(SDL_Surface *screen,int x,int y,int x2,int y2,unsigned char r,unsigned char g,unsigned char b,unsigned char a);
	///DRAW A FILLED BOX (RGBA)
	DLL_EXPORTIMPORT void boxRGBA(SDL_Surface *screen,int x1,int y1,int x2,int y2,unsigned char r,unsigned char g,unsigned char b,unsigned char a);

	///SET TRANSLUCENCY FOR AN AREA
	DLL_EXPORTIMPORT void ScreenShade(SDL_Surface *surface, SDL_Rect *rect, float opacity, unsigned char r, unsigned char g,unsigned char b);
	///SHAKE THE SCREEN FOR THE SPECIFIED TIME PERIOD
	DLL_EXPORTIMPORT void ScreenShake(SDL_Surface *screen,int val, int time,int delay);
    //! draw a string
    DLL_EXPORTIMPORT void DrawString(SDL_Surface *screen, const char* tmp, int x, int y, SDL_Color color, TTF_Font* customfont);
    //! draw a sprite
    DLL_EXPORTIMPORT void DrawStaticSpriteEx(SDL_Surface *screen, int src_x, int src_y, int src_dx, int src_dy, int dst_x, int dst_y, SDL_Surface* sprite);
    //! draw a line
    DLL_EXPORTIMPORT void DrawStaticLine(SDL_Surface *screen, int x0, int y0, int x1, int y1, SDL_Color color);
    //! draw a broken line
	DLL_EXPORTIMPORT void DrawStaticBrokenLine(SDL_Surface *screen, int x0, int y0, int x1, int y1, const SDL_Color *color1, const SDL_Color *color2, int break_size);	
    //! draw rectangle
    DLL_EXPORTIMPORT void DrawRect(SDL_Surface *screen,int x, int y, int dx, int dy, SDL_Color c) ;
};

//! class GFX_UTIL_COLOR
/** define colors constant
*/ 
class DLL_EXPORTIMPORT GFX_UTIL_COLOR
{
public:
    GFX_UTIL_COLOR(){}
    static SDL_Color White;
    static SDL_Color Gray;
    static SDL_Color Red;
    static SDL_Color Green;
    static SDL_Color Black;
    static SDL_Color Orange;
    static SDL_Color Blue;
};

//! namespace for std::string utility functions
namespace STR_UTIL
{
    //! convert a number to string
    std::string intToString(int iNumber);
};

#endif
