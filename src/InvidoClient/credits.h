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

// credits.h

#ifndef __CREDITS_H
#define __CREDITS_H



//! class cCredits
class cCredits
{
	enum eTypeFont
	{
		EASY,
		MAIN
	};
public:
	cCredits(TTF_Font* pFont);
	int Show(SDL_Surface* screen,SDL_Surface *pSurfTitle);

private:
	void draw_text(char * str, int offset, SDL_Surface* screen);

	void draw_textFontM(char * str, int offset, SDL_Surface* screen);

private:
	//! current line in scrolling
	int               m_iLine;
	//! font used
    TTF_Font*         m_pMainFont;
	//! type of font
	eTypeFont         m_eFontType;
    //! text color
    //! current text color
    SDL_Color         m_colCurrent;
};


#endif
