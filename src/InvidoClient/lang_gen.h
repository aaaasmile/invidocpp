
// Lang_Gen.h 
// used to handle languages resource 
// Automatic generated header file by xml->xslt = header

#ifndef   __LANGUAG_GEN_HEAD_H_
#define   __LANGUAG_GEN_HEAD_H_  
 



#include <string>


//! class cLanguages
class cLanguages
{
public:
    
    cLanguages();
    enum eLangId
    {
    
    		LANG_ITA=0,
        		LANG_DIAL_MN,
        		LANG_ENG,
        
    	TOT_LANG // it mus be  always on the last place
    };
    enum eStringID
    {
        	ID_START=0,
        		ID_LANGUAGESEL,
        		ID_HISCORE,
        		ID_VIDEOSET,
        		ID_MAINMENU,
        		ID_EXIT,
        		ID_CHOOSELEVEL,
        		ID_BACKMAINMENU,
        		ID_EASY,
        		ID_HARD,
        		ID_HARDER,
        		ID_BACK,
        		ID_SELECTDISPLAYSETTINGS,
        		ID_INVIDO,
        		ID_CHOOSELANGUA,
        		ID_ENGLISH,
        		ID_DIALETMN,
        		ID_ITALIANO,
        		ID_ANONIM,
        		ID_PUSHBUTTON,
        		ID_CMD_UNKNOWN,
        		ID_CMD_HELP,
        		ID_CMD_CHATWELCOME,
        		ID_CMD_CHATLIST,
        		ID_MAZZONAME,
        		ID_S_AMONTE,
        		ID_S_INVIDO,
        		ID_S_TRASMAS,
        		ID_S_TRASMASNOEF,
        		ID_S_FUERAJEUQ,
        		ID_S_PARTIDA,
        		ID_S_VABENE,
        		ID_S_VADOVIA,
        		ID_S_CHIAMADIPIU,
        		ID_S_NO,
        		ID_S_GIOCA,
        		ID_S_BT_AMONTE,
        		ID_S_BT_INVIDO,
        		ID_S_BT_TRASMAS,
        		ID_S_BT_TRASMASNOEF,
        		ID_S_BT_FUERAJEUQ,
        		ID_S_BT_PARTIDA,
        		ID_S_BT_VABENE,
        		ID_S_BT_VADOVIA,
        		ID_S_BT_CHIAMADIPIU,
        		ID_S_BT_NO,
        		ID_S_BT_GIOCA,
        		ID_S_CANELA,
        		ID_S_PATA,
        		ID_MEN_OPTIONS,
        		ID_CREDITS,
        		ID_WELCOMETITLEBAR,
        		ID_STA_PTCURRENT,
        		ID_CHOOSEMAZZO,
        		ID_PIACENTINA,
        		ID_BERGAMO,
        		ID_BOLOGNA,
        		ID_GENOVA,
        		ID_MILANO,
        		ID_NAPOLI,
        		ID_PIEMONTE,
        		ID_ROMAGNA,
        		ID_SARDEGNA,
        		ID_TOSCANA,
        		ID_TRENTO,
        		ID_TREVISO,
        		ID_TRIESTE,
        		ID_SICILIA,
        		ID_CP_RISP1,
        		ID_CP_PLAYER,
        		ID_CP_DICE,
        		ID_CP_MANOPATA,
        		ID_CP_MANOVINTA,
        		ID_CP_GIOCATAPATA,
        		ID_CP_GIOCATAMONTE,
        		ID_CP_GIOCATAVINTA,
        		ID_CP_PUNTI,
        		ID_CP_PARTITAFIN,
        		ID_CP_NOWPOINTS,
        		ID_CP_BUIADA,
        		ID_CP_VINCE,
        		ID_MN_HELP,
        		ID_OK,
        		ID_CANCEL,
        		ID_NAME,
        		ID_OPT_CONTRL_GENERAL,
        		ID_MUSIC,
        		ID_SOUNDEFFECT,
        		ID_LANGUAGE,
        		ID_MATCHENDQUESTION,
        		ID_YES,
        		ID_NO,
        		ID_CHOOSENAME,
        		ID_SHOWFOTOBACK,
        
        TOT_STRINGS // it mus be always on the last place
    };
    
public:
    void  SetLang(eLangId eVal){m_eLangid = eVal;}
    eLangId  GetLang(){return m_eLangid ;}
    std::string  GetStringId(eStringID eId);
    char*        GetCStringId(eStringID eId);

private:
    eLangId      m_eLangid;
    std::string  m_matStringsLang[TOT_LANG][TOT_STRINGS];

};

#endif

