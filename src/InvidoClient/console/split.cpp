

// split.cpp

#include "StdAfx.h"
#include "split.h"

#ifdef __WIN32__
#include <stdio.h>
#include <stdarg.h>

//irgendwie gabs unter Windows kein snprintf.. machen wir halt schnell unser eigenes :-)
int snprintf(char* str, int size, const char* format, ...) {
	va_list opts;
	va_start(opts, format);
	vsnprintf(str, size, format, opts);
	va_end(opts);
}
#endif

/*!
 * splitline is a destructive argument parser, much like a very primitive
 * form of a shell parser. it supports quotes for embedded spaces and
 * literal quotes with the backslash escape.
 */


char *splitnext(char **pos) {
	char *a, *d, *s;

	s = *pos;
	while (*s == ' ' || *s == '\t')
		s++;
	a = d = s;
	//printf("tokenbegin:%s\\0\n", a);

	while (*s && *s != ' ' && *s != '\t') {
		if (*s == '"') {
			s++;
			while (*s && *s != '"') {
				if (*s == '\\')
					s++;
				if (*s)
					*(d++) = *(s++);
			}
			if (*s == '"')
				s++;
		} else {
			if (*s == '\\')
				s++;
			*(d++) = *(s++);
		}
	}
	while (*s == ' ' || *s == '\t')
		s++;
	*d = 0;
	*pos = s;
	//  printf("token:%s\\0\n", a);
	return a;
}

int splitline(char **argv, int max, char *line) {
	char *s;
	int i = 0;

	s = line;
	while(*s && i < max) {
		argv[i] = splitnext(&s);
		i++;
	}
	if(!argv[0])
		return(0);
	return i;
}




