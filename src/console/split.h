/***************************************************************************
                          split.h  -  description
                             -------------------
    begin                : Mon May 27 2002
    copyright            : (C) 2002 by Clemens Wacha
    email                : wacha@gmx.ch
 ***************************************************************************/

/***************************************************************************
 *                                                                         *
 *   This program is free software; you can redistribute it and/or modify  *
 *   it under the terms of the GNU General Public License as published by  *
 *   the Free Software Foundation; either version 2 of the License, or     *
 *   (at your option) any later version.                                   *
 *                                                                         *
 ***************************************************************************/


/*! file
    Hilfs-Datei für rc_command (siehe rcvars.h|cpp)    
 
    @author Clemens Wacha
*/

#ifndef _SPLIT_H
#define _SPLIT_H

#ifdef __cplusplus
extern "C" {
#endif

char *splitnext(char **pos);
/*! splitline macht aus einer Textzeile einzelne Wörter. Wörter sind Buchstabenkombinationen
    die durch Leerzeichen getrennt werden. Leerzeichen kann man mit Hilfe von Anführungszeichen "" 
    einbetten. Die original Textzeile wird beim zerschneiden zerstört.
*/
int splitline(char **argv, int max, char *line);

#ifdef __WIN32__
int snprintf(char* str, int size, const char* format, ...);
#endif

#ifdef __cplusplus
};
#endif

#endif  /* _SPLIT_H */
