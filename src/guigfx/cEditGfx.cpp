// cEditGfx.cpp: implementation of the cEditGfx class.
//
//////////////////////////////////////////////////////////////////////

#include "StdAfx.h"
#include "cEditGfx.h"
#include "gfx_util.h"

#define MAX_TEXT_LENGTH 256

//////////////////////////////////////////////////////////////////////
// Construction/Destruction
//////////////////////////////////////////////////////////////////////

cEditGfx::cEditGfx()
{
	m_eState = INVISIBLE;
	m_pFontText = 0;
	m_iButID = 0;
	m_bIsEnabled = TRUE;
	m_pSurf_Bar = 0;
	m_bShowCaret = FALSE;
	m_iCarLogPos = 0;
	//SDL_EnableUNICODE(1); // SDL 1.2 in SDL 2.0 is gone
	m_bOnlyNum = FALSE;
	m_iMaxLen = 256;
}

cEditGfx::~cEditGfx()
{
	if (m_pSurf_Bar)
	{
		SDL_FreeSurface(m_pSurf_Bar);
		m_pSurf_Bar = NULL;
	}
}

////////////////////////////////////////
//       Init
/*! Init the button
// \param SDL_Rect* pRect :
// \param SDL_Surface*  pScreen :
*/
void  cEditGfx::Init(SDL_Rect* pRect, SDL_Surface*  pScreen, TTF_Font* pFont, int iButID, SDL_Renderer* psdlRenderer)
{
	m_rctButt = *pRect;

	m_pFontText = pFont;

	m_colCurrent = GFX_UTIL_COLOR::White;
	m_colBorder = m_colCurrent;
	m_iButID = iButID;
	m_psdlRenderer = psdlRenderer;

}


////////////////////////////////////////
//       SetState
/*!
// \param eSate eVal :
*/
void   cEditGfx::SetState(eSate eVal)
{
	eSate eOldState = m_eState;
	m_eState = eVal;
	if (eOldState != m_eState &&
		m_eState == VISIBLE)
	{
		m_colCurrent = GFX_UTIL_COLOR::White;
		m_colBorder = GFX_UTIL_COLOR::White;
	}
	else if (eOldState != m_eState &&
		m_eState == SELECTED)
	{
		m_colBorder = GFX_UTIL_COLOR::Orange;
	}
}

////////////////////////////////////////
//       MouseMove
/*!
// \param SDL_Event &event :
*/
void   cEditGfx::MouseMove(SDL_Event &event, SDL_Surface* pScreen, SDL_Surface* pScene_background)
{

}


////////////////////////////////////////
//       MouseUp
/*! Mouse up event
// \param SDL_Event &event :
*/
void   cEditGfx::MouseUp(SDL_Event &event)
{
	if (m_eState == VISIBLE && m_bIsEnabled)
	{
		if (event.motion.x >= m_rctButt.x  && event.motion.x <= m_rctButt.x + m_rctButt.w &&
			event.motion.y >= m_rctButt.y  && event.motion.y <= m_rctButt.y + m_rctButt.h)
		{
			// mouse go up inner the control
			if (m_eState != INVISIBLE)
			{
				GetFocus();
				//m_fncbClickEvent( m_iButID);
			}
		}
	}
	else if (m_eState == SELECTED && m_bIsEnabled)
	{
		if (event.motion.x >= m_rctButt.x  && event.motion.x <= m_rctButt.x + m_rctButt.w &&
			event.motion.y >= m_rctButt.y  && event.motion.y <= m_rctButt.y + m_rctButt.h)
		{
			// control selected and mouse inside the control
			// change the position of the caret
			int tx, ty;
			TTF_SizeText(m_pFontText, m_strButText.c_str(), &tx, &ty);
			if (event.motion.x < m_rctButt.x + XOFFSET)
			{
				// caret at the begin
				m_iCarLogPos = 0;
			}
			else if (event.motion.x < (m_rctButt.x + XOFFSET + tx))
			{
				// caret in word
				m_iCarLogPos = (UINT)((m_strButText.length() * (event.motion.x - (m_rctButt.x + XOFFSET)) * 100 / tx) / 100);
				ASSERT(m_iCarLogPos >= 0 && m_iCarLogPos <= m_strButText.length());

			}
			else
			{
				// cursor outside the text
				m_iCarLogPos = (UINT)m_strButText.length();
			}
		}
		else
		{
			// control lost the focus
			LostFocus();
		}
	}
}

void   cEditGfx::TextInput(SDL_Event &event)
{
	if (SDL_strlen(event.text.text) == 0 || event.text.text[0] == '\n')
	{
		// ignore
	}
	else
	{
		char buff[MAX_TEXT_LENGTH];
		//fprintf(stderr, "Keyboard: text input \"%s\"\n", event.text.text);
		if (SDL_strlen(m_strButText.c_str()) + SDL_strlen(event.text.text) < m_iMaxLen) {
			SDL_strlcpy(buff, m_strButText.c_str(), sizeof(buff));
			SDL_strlcat(buff, event.text.text, sizeof(buff));
			m_strButText = buff;
			m_iCarLogPos = (UINT)m_strButText.length();
		}
	}
}

////////////////////////////////////////
//       KeyDown
/*! Keydown event
// \param SDL_Event &event :
*/
void   cEditGfx::KeyDown(SDL_Event &event)
{
	if (m_eState != SELECTED)
		return;

	// SDL 2.0 use SDL_TEXTINPUT
	/*int c = event.key.keysym.unicode;
	SDL_Keycode key = event.key.keysym.sym;
	if (key >= SDLK_KP0 && key <= SDLK_KP9) {
		c = 48 + key - SDLK_KP0;
	}*/
	SDL_Keycode key = event.key.keysym.sym;
	if (key == SDLK_LEFT)
	{
		m_iCarLogPos--;
		if (m_iCarLogPos <= 1)
		{
			m_iCarLogPos = 1;
		}
	}
	else if (key == SDLK_RIGHT)
	{
		m_iCarLogPos++;
		if (m_iCarLogPos >= m_strButText.length())
		{
			m_iCarLogPos = (UINT)m_strButText.length();
		}
	}
	else if (key == SDLK_BACKSPACE)
	{
		size_t textlen = SDL_strlen(m_strButText.c_str());
		if (m_iCarLogPos == 0)
		{
			m_iCarLogPos = (UINT)m_strButText.length();
		}
		do {
			if (textlen == 0)
			{
				break;
			}
			if ((m_strButText[m_iCarLogPos - 1] & 0x80) == 0x00)
			{
				/* One byte */
				m_strButText[m_iCarLogPos - 1] = 0x00;
				m_iCarLogPos--;
				break;
			}
			if ((m_strButText[m_iCarLogPos - 1] & 0xC0) == 0x80)
			{
				/* Byte from the multibyte sequence */
				m_strButText[m_iCarLogPos - 1] = 0x00;
				m_iCarLogPos--;
			}
			if ((m_strButText[m_iCarLogPos - 1] & 0xC0) == 0xC0)
			{
				/* First byte of multibyte sequence */
				m_strButText[m_iCarLogPos - 1] = 0x00;
				m_iCarLogPos--;
				break;
			}
		} while (1);

	}
	/*if (m_iCarLogPos > 0) //SDLK_BACKSPACE SDL 1.2
	{
		m_iCarLogPos--;
		if (m_iCarLogPos <= 0)
		{
			m_iCarLogPos = 0;
		}

		STRING strBegText = m_strButText.substr(0, m_iCarLogPos);
		STRING strEndText = "";
		if (m_iCarLogPos < m_strButText.length())
		{
			strEndText = m_strButText.substr(m_iCarLogPos+1, m_strButText.length());
		}
		m_strButText = strBegText + strEndText;
	}*/
	//else if (key >= SDLK_RSHIFT && key <= SDLK_COMPOSE || // SDL 1.2
	else if (key >= SDLK_RSHIFT ||
		key == SDLK_TAB || key == SDLK_RETURN || key == SDLK_ESCAPE ||
		key == SDLK_DELETE)
	{
		// ignore key
	}
	else
	{
		// SDL 1.2
		//BOOL bContinue = TRUE;
		//// check mask
		//if (m_bOnlyNum)
		//{
		//	if (key < SDLK_0 || key > SDLK_9)
		//	{
		//		// not a num key, reject it
		//		bContinue = FALSE;
		//	}
		//}
		//if (bContinue)
		//{
		//	// a key used to build the text
		//	UINT ch;
		//	if ((event.key.keysym.unicode & 0xFF80) == 0) {
		//		ch = event.key.keysym.unicode & 0x7F;
		//	}
		//	else {
		//		//An international character..
		//		ch = event.key.keysym.unicode;
		//	}
		//	char strBuff[2] = { '\0','\0' };
		//	strBuff[0] = ch; //event.key.keysym.sym;
		//	STRING strBegText = "";
		//	if (m_iCarLogPos > 0)
		//	{
		//		strBegText = m_strButText.substr(0, m_iCarLogPos);
		//	}
		//	STRING strEndText = "";
		//	if (m_iCarLogPos < m_strButText.length())
		//	{
		//		strEndText = m_strButText.substr(m_iCarLogPos, m_strButText.length());
		//	}
		//	STRING strNew = strBuff;
		//	m_strButText = strBegText + strNew + strEndText;
		//	m_iCarLogPos++;
		//	if (m_iCarLogPos >= m_strButText.length())
		//	{
		//		m_iCarLogPos = m_strButText.length();
		//	}
		//}
	}
}



////////////////////////////////////////
//       LostFocus
/*! The Edit control lost the focus
*/
void cEditGfx::LostFocus()
{
	SetState(VISIBLE);
	m_bShowCaret = FALSE;
}


////////////////////////////////////////
//       GetFocus
/*! The control get the focus
*/
void cEditGfx::GetFocus()
{
	SetState(SELECTED);
	m_uiStartTime = SDL_GetTicks();
	m_bShowCaret = TRUE;
	m_iCarLogPos = (UINT)m_strButText.length();

}

////////////////////////////////////////
//       DrawControl
/*! Draw the button suface with text
// \param SDL_Surface*  pScreen :
*/
void   cEditGfx::DrawControl(SDL_Surface*  pScreen)
{
	if (m_eState != INVISIBLE)
	{
		if (m_bIsEnabled)
		{

			//GFX_UTIL::DrawStaticSpriteEx(pScreen, 0, 0, m_rctButt.w, m_rctButt.h, m_rctButt.x, m_rctButt.y, m_pSurf_Bar);
			int tx, ty;
			TTF_SizeText(m_pFontText, m_strButText.c_str(), &tx, &ty);
			int iXOffSet = XOFFSET;
			int iYOffset = (m_rctButt.h - ty) - 2;

			GFX_UTIL::DrawString(pScreen, m_strButText.c_str(), m_rctButt.x + iXOffSet,
				m_rctButt.y + iYOffset, m_colCurrent, m_pFontText);


			// draw border
			GFX_UTIL::DrawRect(pScreen, m_rctButt.x - 1, m_rctButt.y - 1, m_rctButt.x + m_rctButt.w + 1,
				m_rctButt.y + m_rctButt.h + 1, GFX_UTIL_COLOR::Gray);
			GFX_UTIL::DrawRect(pScreen, m_rctButt.x - 2, m_rctButt.y - 2, m_rctButt.x + m_rctButt.w + 2,
				m_rctButt.y + m_rctButt.h + 2, GFX_UTIL_COLOR::Black);
			/*
			GFX_UTIL::DrawRect(pScreen, m_rctButt.x, m_rctButt.y, m_rctButt.x +  m_rctButt.w,
								m_rctButt.y + m_rctButt.h , m_colBorder);
								*/
								//drawRect(m_rctButt.x, m_rctButt.y, m_rctButt.w, m_rctButt.y, staColor_white);

			if (m_eState == SELECTED)
			{
				// draw the caret
				Uint32 uiNowTime = SDL_GetTicks();
				if (uiNowTime < m_uiStartTime + 500)
				{
					if (m_bShowCaret)
					{

						// show caret
						int txSubString = 0;
						if (m_iCarLogPos > 0)
						{
							// make a substring to get the position of the caret
							STRING strSubText = m_strButText.substr(0, m_iCarLogPos);
							TTF_SizeText(m_pFontText, strSubText.c_str(), &txSubString, &ty);
						}
						else if (m_iCarLogPos == 0)
						{
							txSubString = -1;
						}

						int iXStart = m_rctButt.x + iXOffSet + txSubString;
						GFX_UTIL::DrawStaticLine(pScreen, iXStart, m_rctButt.y + 4, iXStart,
							m_rctButt.y + m_rctButt.h - 2, m_colCurrent);
					}

				}
				else
				{
					// change caret state
					m_uiStartTime = uiNowTime;
					if (m_bShowCaret)
					{
						m_bShowCaret = FALSE;
					}
					else
					{
						m_bShowCaret = TRUE;
					}
				}

			}


			//ASSERT(m_strButText != "-");
		}
		else
		{
			// button disabled 
			// TO DO
		}
	}
}



////////////////////////////////////////
//       RedrawButton
/*! Redraw the button
// \param SDL_Surface* pScreen :
// \param SDL_Surface* pScene_background :
*/
void   cEditGfx::RedrawButton(SDL_Surface* pScreen, SDL_Texture* pScene_background, SDL_Texture* pScreenTexture)
{
	if (pScene_background)
	{
		//SDL_BlitSurface(pScene_background, &m_rctButt, pScreen, &m_rctButt); //SDL 1.2
		SDL_RenderCopy(m_psdlRenderer, pScene_background, &m_rctButt, &m_rctButt); //SDL 2.0
	}
	DrawControl(pScreen);
	//SDL_Flip(pScreen); //SDL 1.2
	// SDL 2.0
	SDL_UpdateTexture(pScreenTexture, NULL, pScreen->pixels, pScreen->pitch);
	SDL_RenderCopy(m_psdlRenderer, pScreenTexture, NULL, NULL);
	SDL_RenderPresent(m_psdlRenderer);
}
