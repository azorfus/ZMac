#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include "stringlib.h"

void zbuffer_init(zbuffer* buff)
{
	buff->Data = NULL;
	buff->Size = 0;
}

void zbuffer_append(zbuffer* buff, zstring* str)
{
	/*
	buff->Data = realloc(buff->Data, buff->Size + str->Len + 1);
	str->Len += source->Len;
	strcpy(buff->Data + str->Len, str->Data);
	*/
}

void zbuffer_pop(zbuffer* buff)
{

}

void zbuffer_destroy(zbuffer* buff)
{
	free(buff->Data);
	buff->Data = NULL;
	buff->Size = 0;
}

void zstring_init(zstring* str)
{
	str->Data = NULL;
	str->Len = 0;
}

void zstring_charp(zstring* dest, const char* Source)
{
	dest->Len = strlen(Source);
	dest->Data = malloc(dest->Len + 1);
	strcpy(dest->Data, Source);
}

void zstring_alloc_size(zstring* str, size_t size)
{
	str->Data = malloc(size);
	str->Len = size-1;
}

void zstring_realloc(zstring* str, size_t size)
{
	str->Data = realloc(str->Data, str->Len + size);
}

void zstring_fread(zstring* str, FILE* source)
{
	fseek(source, 0, SEEK_END);
	size_t fileSize = ftell(source);
	str->Data = malloc(fileSize + 1);
	str->Len = fileSize + 1;
	rewind(source);
	fread(str->Data, 1, fileSize, source);
	//str->Data[str->Len]='\0';
}

void zstring_fwrite_stdout(zstring* str)
{
	fwrite(str->Data, sizeof(char), str->Len, stdout);
}

void zstring_fwrite(zstring* str, FILE* dest)
{
	fwrite(str->Data, sizeof(char), str->Len, dest);	
}

void zstring_append(zstring* str, const char* source)
{
	size_t source_len = strlen(source);
	str->Data = realloc(str->Data, str->Len + source_len + 1);
	char* end_of_dst = str->Data  + str->Len;
	str->Len += source_len;
	strcpy(end_of_dst, source);	

	/* you can use this if you want:
	 * memcpy(end_of_dst, str->Data, str->Len);
	 */
}

void zstring_appendC(zstring* str, const char source)
{
	printf(" 1 ___ %s ___\n", str->Data);
	str->Data = realloc(str->Data, str->Len + 2);
	str->Len += 1;
	strcat(str->Data, "f");
	printf(" 2 ___ %s ___\n", str->Data);
}

void zstring_append_string(zstring* str, zstring* source)
{
	str->Data = realloc(str->Data, str->Len + source->Len + 1);
	char* end_of_dst = str->Data  + str->Len;
	str->Len += source->Len;
	strcpy(end_of_dst, source->Data);	
}

void zstring_remsubstr(zstring *str, const char *toRemove) {
    if (NULL == (str->Data = strstr(str->Data, toRemove)))
    {  
        // no match.
        printf("No match in %s\n", str->Data);
        return;
    }

    // str points to toRemove in str now.
    const size_t remLen = strlen(toRemove);
    char *copyEnd;
    char *copyFrom = str->Data + remLen;
    while (NULL != (copyEnd = strstr(copyFrom, toRemove)))
    {  
        // printf("match at %3ld in %s\n", copyEnd - str, str);
        memmove(str->Data, copyFrom, copyEnd - copyFrom);
        str->Data += copyEnd - copyFrom;
        copyFrom = copyEnd + remLen;
    }
    memmove(str->Data, copyFrom, 1 + strlen(copyFrom));
}

void zstring_resize(zstring* str, size_t resize, char fill_char)
{
	str->Data = realloc(str->Data, str->Len + resize + 1);
	//str->Data =  
}

void zstring_destroy(zstring* str)
{
	free(str->Data);
	str->Data = NULL;
	str->Len = 0;
}

