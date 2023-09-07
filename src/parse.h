#ifndef PARSE_H
#define PARSE_H

#include <stdio.h>
#include <ctype.h>
#include <stdbool.h>
#include <string>
#include <vector>

typedef enum toktype
{
	tok_greater, tok_lesser,
	tok_equal, tok_equiv,
	tok_goto, tok_end,
	tok_str, tok_menu,
	tok_get, tok_struct,
	tok_lsquare, tok_rsquare,
	tok_lcurly, tok_rcurly,
	tok_lbrack, tok_rbrack,
	tok_quote, tok_dollar,
	tok_strlit,
	tok_none, tok_intlit,
	tok_colon, tok_tell,
	tok_alpha, tok_int,
	tok_whsp_s, tok_whsp_t,
	tok_comma, tok_whsp_n,
	tok_start, tok_backsl,
	tok_end, tok_EOF
} toktype;

typedef enum node_type
{
	node_tell, node_get
} node_type;

typedef enum ErrorType
{
	IdenNotDefined,
	ExpectedColon, ExpectedQuote
} ErrorType;

struct token
{
	std::string value;
	toktype type;
	unsigned int line_number;
};

struct relnode
{
	token left;
	token op;

	bool end;
	token right;
	relnode nright;
};

struct ifnode
{
	std::vector <relnode> conditions;
	std::vector <relnode> nodes;
	std::vector <ifnode> ifnodes;
};

struct var
{
	int type;
	token name;
	token val;
}

struct strct
{
	token name;
	std::vector <var> vars;
};

struct mitems
{
	std::vector <relnode> nodes;
	std::vector <ifnode> ifnodes;
};

struct narr
{
	std::vector <relnode> nodes;
	std::vector <mitems> menu;
	std::vector <token> excess;
	std::vector <ifnode> ifnodes;
};

// Parser

class Parser
{
	public:
		std::string value;
		std::string file;
		std::string start;
		token current_token;
		int line_number;
		unsigned int current_index;

		std::vector <token> tokens;
		std::vector <narr> locs;
		std::vector <strct> structs;
		std::vector <var> vars;

		bool running = true;
		bool lever = false;

		Parser(std::string);

	private:
		void lex();
		void show_error(ErrorType err);
		void consume();
		toktype return_toktype(const char);
		
		std::string parse_string();
		relnode parse_tell();
		relnode parse_goto();
		relnode parse_get();
		relnode parse_reln();

		var parse_assign();
		strct parse_struct();
		ifnode parse_if();
		
		struct node
		{
			node *left;
			std::string op;
			node *right;
			std::string value;
		};

		node parse_expr();
		node parse_term();
		node parse_factor();
		int evaluate_expr();

}

#endif
