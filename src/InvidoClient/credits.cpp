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


// credits.cpp

#include "StdAfx.h"
#include "win_type_global.h"

#include <SDL.h>
#include <SDL_ttf.h>

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <SDL.h>
#include "gfx_util.h"
#include "fading.h"
#include "credits.h"


char * credit_text[] = {
  "-INVIDO",  /* '-' at beginning makes highlighted: */
  "",
  "",
  "PART OF THE 'CUPERATIVA' PROJECT",
  "",
  "",
  "",
  "",
  "",
  "-PROJECT",
  "IGOR SARZI SARTORI",
  "",
  "",
  "",
  "",
  "",
  "",
  "-INVIDO TECHNICAL EVANGELIST ",
  "REALDO SARTORI",
  "",
  "",
  "",
  "",
  "",
  "",
  "-HOME PAGE ",
  "www.invido.it",
  "",
  "",
  "",
  "", /* The following blanks cause the screen to scroll to complete blank: */
  "",
  "",
  "",
  "",
  "",
  "",
  "",
  "",
  "",
  "",
  "",
  "",
  "",
  NULL
};


/* Some simple pixel-based characters we can blit quickly: */

char chars[38][5][6] = {
  {".###.",
   "#..##",
   "#.#.#",
   "##..#",
   ".###."},

  {"..#..",
   ".##..",
   "..#..",
   "..#..",
   ".###."},

  {".###.",
   "....#",
   "..##.",
   ".#...",
   "#####"},

  {".###.",
   "....#",
   "..##.",
   "....#",
   ".###."},

  {"...#.",
   "..##.",
   ".#.#.",
   "#####",
   "...#."},

  {"#####",
   "#....",
   "####.",
   "....#",
   "####."},

  {".###.",
   "#....",
   "####.",
   "#...#",
   ".###."},

  {"#####",
   "....#",
   "...#.",
   "..#..",
   ".#..."},

  {".###.",
   "#...#",
   ".###.",
   "#...#",
   ".###."},

  {".###.",
   "#...#",
   ".####",
   "....#",
   ".###."},

  {".###.",
   "#...#",
   "#####",
   "#...#",
   "#...#"},

  {"####.",
   "#...#",
   "####.",
   "#...#",
   "####."},
  
  {".###.",
   "#....",
   "#....",
   "#....",
   ".###."},
  
  {"####.",
   "#...#",
   "#...#",
   "#...#",
   "####."},
  
  {"#####",
   "#....",
   "###..",
   "#....",
   "#####"},
  
  {"#####",
   "#....",
   "###..",
   "#....",
   "#...."},
  
  {".###.",
   "#....",
   "#.###",
   "#...#",
   ".###."},
  
  {"#...#",
   "#...#",
   "#####",
   "#...#",
   "#...#"},
  
  {".###.",
   "..#..",
   "..#..",
   "..#..",
   ".###."},
  
  {"....#",
   "....#",
   "....#",
   "#...#",
   ".###."},
  
  {"#..#.",
   "#.#..",
   "##...",
   "#.#..",
   "#..#."},
  
  {"#....",
   "#....",
   "#....",
   "#....",
   "#####"},
  
  {"#...#",
   "##.##",
   "#.#.#",
   "#...#",
   "#...#"},
  
  {"#...#",
   "##..#",
   "#.#.#",
   "#..##",
   "#...#"},
  
  {".###.",
   "#...#",
   "#...#",
   "#...#",
   ".###."},
  
  {"####.",
   "#...#",
   "####.",
   "#....",
   "#...."},
  
  {".###.",
   "#...#",
   "#.#.#",
   "#..#.",
   ".##.#"},
  
  {"####.",
   "#...#",
   "####.",
   "#...#",
   "#...#"},
  
  {".###.",
   "#....",
   ".###.",
   "....#",
   ".###."},
  
  {"#####",
   "..#..",
   "..#..",
   "..#..",
   "..#.."},
  
  {"#...#",
   "#...#",
   "#...#",
   "#...#",
   ".###."},
  
  {"#...#",
   "#...#",
   ".#.#.",
   ".#.#.",
   "..#.."},
  
  {"#...#",
   "#...#",
   "#.#.#",
   "##.##",
   "#...#"},
  
  {"#...#",
   ".#.#.",
   "..#..",
   ".#.#.",
   "#...#"},

  {"#...#",
   ".#.#.",
   "..#..",
   "..#..",
   "..#.."},
  
  {"#####",
   "...#.",
   "..#..",
   ".#...",
   "#####"},
  
  {".....",
   ".....",
   ".....",
   "..#..",
   ".#..."},
  
  {"..#..",
   "..#..",
   ".....",
   ".....",
   "....."}
};


////////////////////////////////////////
//       cCredits
/*! Constructor
*/
cCredits::cCredits(TTF_Font* psdlFont)
{
	m_pMainFont = psdlFont;
	//m_eFontType = EASY;
	m_eFontType = MAIN;
    m_colCurrent = GFX_UTIL_COLOR::White;
}



////////////////////////////////////////
//       credits
/*! Show credits
// \param SDL_Surface* screen : 
// \param SDL_Surface *pSurfTitle : 
*/
int cCredits::Show(SDL_Surface* screen, SDL_Surface *pSurfTitle)
{
	int done, quit, scroll;
	SDL_Rect src, dest;
	SDL_Event event;
	Uint32 last_time, now_time;
	SDLKey key;


	/* Clear window: */
	fade (screen, screen, 2, 1) ;
	//SDL_FillRect(screen, NULL, SDL_MapRGB(screen->format, 0, 0, 0));


	/* Draw title: */

	dest.x = (screen->w - pSurfTitle->w) / 2;
	dest.y = 0;
	dest.w = pSurfTitle->w;
	dest.h = pSurfTitle->h;

	SDL_BlitSurface(pSurfTitle, NULL, screen, &dest);


	/* --- MAIN OPTIONS SCREEN LOOP: --- */

	done = 0;
	quit = 0;
	scroll = 0;
	m_iLine = 0;
	int iLocalScroll;
	BOOL bLineShow = FALSE; 

	do
    {
		last_time = SDL_GetTicks();

		/* Handle any incoming events: */      
		while (SDL_PollEvent(&event) > 0)
		{
			if (event.type == SDL_QUIT)
			{
				/* Window close event - quit! */
	      
				quit = 1;
				done = 1;
			}
			else if (event.type == SDL_KEYDOWN)
			{
				key = event.key.keysym.sym;
				if (key == SDLK_ESCAPE)
				{
					/* Escape key - quit! */
					done = 1;
				}
			}
		}
		/* Scroll: */
		src.x = 0;
		src.y = (pSurfTitle->h) + 2;
		src.w = screen->w;
		src.h = screen->h - (pSurfTitle->h);

		dest.x = 0;
		dest.y = (pSurfTitle->h);
		dest.w = src.w;
		dest.h = src.h;

		SDL_BlitSurface(screen, &src, screen, &dest);

		dest.x = 0;
		dest.y = (screen->h) - 2;
		dest.w = screen->w;
		dest.h = 2;

		SDL_FillRect(screen, &dest, SDL_MapRGB(screen->format, 0, 0, 0));
		scroll++;

		if (m_eFontType == EASY)
		{
			draw_text(credit_text[m_iLine], scroll, screen);
			iLocalScroll = 9;
		}
		else
		{
			iLocalScroll = 9;
			if (!bLineShow)
			{
				draw_textFontM(credit_text[m_iLine], scroll, screen);
				bLineShow = TRUE;
				
			}
		}


		if (scroll >= iLocalScroll)
		{
			scroll = 0;
			bLineShow = FALSE;
			m_iLine++;

			if (credit_text[m_iLine] == NULL)
			{
				done = 1;
			}
		}
		SDL_Flip(screen);
      
        /* Pause (keep frame-rate event) */
      
		now_time = SDL_GetTicks();
		if (now_time < last_time + (1000 / 20))
		{
			SDL_Delay(last_time + (1000 / 20) - now_time);
		}
    }
	while (!done);
  
	fade (screen, screen, 1, 1) ;
	/* Return the chosen command: */
  
	return quit;
}



////////////////////////////////////////
//       draw_text
/*! Draw credit text
// \param char * str : 
// \param int offset : 
// \param SDL_Surface* screen : 
*/
void cCredits::draw_text(char * str, int offset, SDL_Surface* screen)
{
	int i, c, x, y, cur_x, start, hilite;
	SDL_Rect dest;
	Uint8 r, g, b;


	if (str[0] == '-')
	{
		start = 1;
		hilite = 1;
	}
	else
	{
		start = 0;
		hilite = 0;
	}


	cur_x = (screen->w - ((strlen(str) - start) * 18)) / 2;

	for (i = start; i < (int)strlen(str); i++)
	{
		c = -1;

		if (str[i] >= '0' && str[i] <= '9')
			c = str[i] - '0';
		else if (str[i] >= 'A' && str[i] <= 'Z')
			c = str[i] - 'A' + 10;
		else if (str[i] == ',')
			c = 36;
		else if (str[i] == '\'')
			c = 37;
      
      
		if (c != -1)
		{
			for (y = 0; y < 5; y++)
			{
				if (hilite == 0)
				{
					r = 255 - ((m_iLine * y) % 256);
					g = 255 / (y + 2);
					b = (m_iLine * m_iLine * 2) % 256;
				}
				else
				{
					r = 128;
					g = 192;
					b = 255 - (y * 40);
				}
			  
				for (x = 0; x < 5; x++)
				{
					if (chars[c][y][x] == '#')
					{
						dest.x = cur_x + (x * 3);
						dest.y = ((screen->h - (5 * 3)) + (y * 3) +
						(18 - offset * 2));
						dest.w = 3;
						dest.h = 3;

						SDL_FillRect(screen, &dest, SDL_MapRGB(screen->format, r, g, b));
					}
				}
			}
		} 
		/* Move virtual cursor: */ 
		cur_x = cur_x + 18;
    }
}


////////////////////////////////////////
//       draw_textFontM
/*! 
// \param char * str : 
// \param int offset : 
// \param SDL_Surface* screen : 
*/
void cCredits::draw_textFontM(char* pstrLine, int offset, SDL_Surface* screen)
{
	ASSERT(m_pMainFont);

    int tx, ty;
	TTF_SizeText(m_pMainFont,pstrLine, &tx, &ty);
	int iY = screen->h - (offset * ty);
	SDL_Rect trect;
	STRING strLayout = pstrLine;
	STRING strRes = strLayout;
	int iLen = strRes.length(); 
	if (pstrLine[0] == '-')
	{
		// highlight
		// eat '-'
		strRes = strLayout.substr(1,iLen - 1); 
		trect.y= iY - 2;
		//trect.x =  (screen->w/2 - ((int)strRes.size()*tx + 3)/2) - 4;
        trect.x =  (screen->w  - tx)/ 2;
		//trect.w = (int)strRes.size()*tx + 8;
        trect.w = tx;
		trect.h = ty + 4;
        SDL_Rect rctBox = trect;
        rctBox.x -= 4;
        rctBox.w += 4;
		Uint32 tcolor = SDL_MapRGBA(screen->format, 128, 0, 0,255);
		SDL_FillRect(screen,&rctBox,tcolor);
	}
	else
	{
		trect.y= iY - 2;
		trect.x =  (screen->w  - tx)/ 2;
		
	}
	//m_pMainFont->DrawString(screen, strRes, TEXTMIXED, TEXTALIGNCENTER, 0, iY, 0);
    GFX_UTIL::DrawString(screen, strRes.c_str(), trect.x, 
                                trect.y, m_colCurrent, m_pMainFont);

}
