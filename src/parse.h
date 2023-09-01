#ifndef PARSE_H
#define PARSE_H

#include <stdio.h>
#include <ctype.h>
#include <stdbool.h>
#include <string>
#include <vector>

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
	tok_alpha, tok_int,
	tok_whsp_s, tok_whsp_t,
	tok_comma, tok_whsp_n,
	tok_start, tok_backsl,
	tok_EOF
} toktype;

typedef enum ErrorType
{
	IdenNotDefined,
	ExpectedColon, ExpectedQuote
} ErrorType;

typedef struct token
{
	std::string value;
	toktype type;
	unsigned int line_number;
} token;

typedef struct location
{
	std::string name;
	bool forward;
	bool CF, SF, ZF;
	std::string desc;
	std::string indesc;
	std::vector <std::string> paths;
	bool path_dir[10];
	std::vector <std::string> interact;
} location;

typedef struct object
{
	std::string name;
	bool forward;
	bool CF, SF, ZF;
	std::string desc;
	std::string indesc;
	std::vector <std::string> status;
	std::vector <std::string> interact;
	std::vector <std::string> objects;
	int mass;
	
} object;

// Parser

class Parser
{
	public:
		std::string value;
		std::string file;
		token current_token;
		int line_number;
		unsigned int current_index;

		std::vector <token> tokens;

		std::vector <location> loc_stack;
		std::vector <object> obj_stack;

		bool running = true;
		bool lever = false;

		Parser(std::string gfile);

	private:
		void lex();
		std::string parse_string();
		void show_error(ErrorType err, token current_token);
		toktype return_toktype(const char);
}

void parse(std::vector <location>* loc_stack, std::vector <object>* obj_stack,
		   std::string* file);

#endif
