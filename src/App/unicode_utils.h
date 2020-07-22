#ifndef _UNICODE_UTILS_H
#define _UNICODE_UTILS_H



#include "includes.h"


// Convert UTF8 char to ANSI char
// Return ANSI char
char		UTF8toANSI(uint8_t *utfchar);

// Convert UNICODE char to UTF8 char
// Return UTF8 char
uint16_t	UnicodeToUTF8(uint16_t unichar);

// Convert UNICODE char to ANSI char
// Return ANSI char
char		UnicodeToANSI(uint16_t unichar);

// Convert UTF8 string to ANSI string
// Return count of converted chars
// maxlen - max lenght of cstr buffer
uint16_t	UTF8ToANSI_Str(char *cstr, uint8_t *utfstr, uint16_t maxlen);

// Convert UNICODE string to UTF8 string
// Return count of converted chars
// maxlen - max lenght of utfstr buffer
uint16_t	UnicodeToUTF8_Str(char *utfstr, uint16_t *unistr, uint16_t maxlen);

// Convert UNICODE string to ANSI string
// Return count of converted chars
// maxlen - max lenght of cstr buffer
uint16_t	UnicodeToANSI_Str(char *cstr, uint16_t *unistr, uint16_t maxlen);

uint32_t	strlen_utf(char *text);

char*		strcpy_utf(char *dst, char* src);

uint16_t*	strcpy_uni(uint16_t *dst, uint16_t *src);

uint16_t*	strcat_uni(uint16_t *dst, uint16_t *src);

#endif