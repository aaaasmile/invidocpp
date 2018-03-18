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

//cTipoDiMazzo.h

#ifndef __CTIPODIMAZZO__H_
#define __CTIPODIMAZZO__H_

#include <string>
#include "Lang_Gen.h"


//! class cTipoDiMazzo 
/* Collect all info about deck
*/
class cTipoDiMazzo
{
public:
enum eTypeMazzo
{
    PIACENTINA=0,
    BERGAMO,
    BOLOGNA,
    GENOVA,
    MILANO,
    NAPOLI,
    PIEMONTE,
    ROMAGNA,
    SARDEGNA,
    SICILIA,
    TOSCANA,
    TRENTO,
    TREVISO,
    TRIESTE,
};
public:
    cTipoDiMazzo()
    {
    }
public:
    void          SetType(eTypeMazzo eType);
    std::string   GetResFileName(){return m_strResFileName;}
    std::string   GetMazzoName(){return m_strMazzoName;}
    std::string   GetSymbolFileName(){return m_strSymbolName;}
    eTypeMazzo    GetType(){return m_eType;}
    void          Clone(cTipoDiMazzo &Val);
    void          SetTypeIndex(int iVal);
    int           GetTypeIndex(){return (int)m_eType;}
private:
    //! id mazzo
	eTypeMazzo   m_eType;
    //! name
    std::string  m_strMazzoName;
    //! resource file name
    std::string  m_strResFileName;
    //! symbol file name
    std::string  m_strSymbolName;
};



#endif