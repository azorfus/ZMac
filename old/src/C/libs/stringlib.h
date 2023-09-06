#ifndef STRING_LIB_H
#define STRING_LIB_H

#include <stdio.h>
#include <string.h>

typedef struct zstring
{
	char* Data;
	size_t Len;
} zstring;

void zstring_init(zstring* str);
void zstring_charp(zstring* dest, const char* Source);
void zstring_alloc_size(zstring* str, size_t size);
void zstring_realloc(zstring* str, size_t size);
void zstring_fread(zstring* str, FILE* source);
void zstring_fwrite_stdout(zstring* str);
void zstring_fwrite(zstring* str, FILE* dest);

void zstring_append(zstring* str, const char* source);
void zstring_appendC(zstring* str, const char);
void zstring_append_string(zstring* str, zstring* source);

void zstring_remsubstr(zstring *str, const char *toRemove);
void zstring_resize(zstring* str, size_t newsize, char fill_char);
void zstring_destroy(zstring* str);

typedef struct zbuffer
{
	zstring* Data;
	size_t Size;
} zbuffer;

void zbuffer_init(zbuffer* buff);
void zbuffer_append(zbuffer* buff, zstring* str);
void zbuffer_pop(zbuffer* buff);
void zbuffer_destroy(zbuffer* buff);

#endif // 
