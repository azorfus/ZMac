#ifndef PARSE_H
#define PARSE_H

#include <stdio.h>
#include <ctype.h>
#include <stdbool.h>
#include "libs/stringlib.h"

typedef enum toktype
{
	tok_iden, tok_name,
	tok_forward, tok_objects,
	tok_desc, tok_indesc,
	tok_paths, tok_interact,
	tok_location, tok_object,
	tok_lcurly, tok_rcurly,
	tok_lbrack, tok_rbrack,
	tok_quote, tok_dollar,
	tok_none, tok_intlit,
	tok_colon, tok_cf,
	tok_sf, tok_zf,
	tok_mass, tok_synonym,
	tok_article, tok_tell,
	tok_alpha, tok_int
} toktype;

typedef struct token
{
	zstring value;
	toktype type;
} token;

typedef struct location
{
	zstring name;
	bool forward;
	bool CF, SF, ZF;
	zstring desc;
	zstring indesc;
	zbuffer paths;
	bool path_dir[10];
	zbuffer interact;
} location;

typedef struct object
{
	zstring name;
	bool forward;
	bool CF, SF, ZF;
	zstring desc;
	zstring indesc;
	zbuffer status;
	zbuffer interact;
	zbuffer objects;
	int mass;
	
} object;

toktype return_toktype(const char);
void next_token(zstring* file, unsigned int, token*);

#endif
