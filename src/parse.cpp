#include "parse.h"
#include <iostream>

toktype Parser::return_toktype(const char value)
{
	if(value == ':') return tok_colon;
	else if(value == '>') return tok_greater;
	else if(value == '<') return tok_lesser;
	else if(value == '=') return tok_equal;
	else if(value == '{') return tok_lcurly;
	else if(value == '}') return tok_rcurly;
	else if(value == '[') return tok_lsquare;
	else if(value == ']') return tok_rsquare;
	else if(value == '\"') return tok_quote;
	else if(value == '\\') return tok_backsl;
	else if(value == '(') return tok_lbrack;
	else if(value == ')') return tok_rbrack;
	else if(isalpha(value) || value == '_' || value == '?') return tok_alpha;
	else if(isdigit(value)) return tok_intlit;
	else if(value == '$') return tok_dollar;
	else if(value == ',') return tok_comma;
	else if(value == ' ') return tok_whsp_s;
	else if(value == '\t') return tok_whsp_t;
	else if(value == '\n') return tok_whsp_n;
	else if(value == '\0') return tok_EOF;
}

void Parser::lex()
{
	while(current_index <= file.length())
	{
		toktype ret_type = return_toktype(file[current_index]);
		current_token.line_number = line_number + 1;
		if(ret_type == tok_alpha)
		{
			std::string value = "";
			while(current_index <= file.length())
			{
				value.push_back(file[current_index]);
				if(current_index + 1 <= file.length())
				{
					if(return_toktype(file[current_index + 1]) != tok_alpha) break;
					else
					{
						current_index = current_index + 1;
						ret_type = return_toktype(file[current_index]);
					}
				}
			}
			
			if(value == "end") current_token.type = tok_end;
			else if(value == "goto") current_token.type = tok_goto;
			else if(value == "str") current_token.type = tok_str;
			else if(value == "struct") current_token.type = tok_struct;
			else if(value == "menu") current_token.type = tok_menu;
			else if(value == "get") current_token.type = tok_get;
			else if(value == "tell") current_token.type = tok_tell;
			else if(value == "none") current_token.type = tok_none;
			else if(value == "start") current_token.type = tok_start;
			else current_token.type = tok_iden;
			current_token.value = value;
			current_index = current_index + 1;

			tokens.push_back(current_token);

		}
		else if(ret_type == tok_intlit)
		{
			std::string value = "";
			while(current_index <= file.length() && ret_type == tok_intlit)
			{
				value.push_back(file[current_index]);
				current_index = current_index + 1;
				if(current_index + 1 <= file.length()) ret_type = return_toktype(file[current_index]);
			}
			current_token.value = value;
			current_token.type = tok_int;
			current_index = current_index + 1;
			tokens.push_back(current_token);
		}
		else if(ret_type == tok_lcurly)
		{
			current_token.value = "{";
			current_token.type = tok_lcurly;
			current_index = current_index + 1;
			tokens.push_back(current_token);
		}
		else if(ret_type == tok_equal)
		{
			current_token.value = "=";
			current_token.type = tok_equal;
			current_index = current_index + 1;
			tokens.push_back(current_token);
		}

		else if(ret_type == tok_rcurly)
		{
			current_token.value = "}";
			current_token.type = tok_rcurly;
			current_index = current_index + 1;
			tokens.push_back(current_token);
		}
		else if(ret_type == tok_lsquare)
		{
			current_token.value = "[";
			current_token.type = tok_lsquare;
			current_index = current_index + 1;
			tokens.push_back(current_token);
		}
		else if(ret_type == tok_rsquare)
		{
			current_token.value = "]";
			current_token.type = tok_rsquare;
			current_index = current_index + 1;
			tokens.push_back(current_token);
		}
		else if(ret_type == tok_lbrack)
		{
			current_token.value = "(";
			current_token.type = tok_lbrack;
			current_index = current_index + 1;
			tokens.push_back(current_token);
		}
		else if(ret_type == tok_rbrack)
		{
			current_token.value = ")";
			current_token.type = tok_rbrack;
			current_index = current_index + 1;
			tokens.push_back(current_token);
		}
		else if(ret_type == tok_quote)
		{
			current_token.value = "\"";
			current_token.type = tok_quote;
			current_index = current_index + 1;
			tokens.push_back(current_token);
		}
		else if(ret_type == tok_backsl)
		{
			current_token.value = "\\";
			current_token.type = tok_backsl;
			current_index = current_index + 1;
			tokens.push_back(current_token);
		}
		else if(ret_type == tok_dollar)
		{
			current_token.value = "$";
			current_token.type = tok_dollar;
			current_index = current_index + 1;
			tokens.push_back(current_token);
		}
		else if(ret_type == tok_colon)
		{
			current_token.value = ":";
			current_token.type = tok_colon;
			current_index = current_index + 1;
			tokens.push_back(current_token);
		}
		else if(ret_type == tok_comma)
		{
			current_token.value = ",";
			current_token.type = tok_comma;
			current_index = current_index + 1;
			tokens.push_back(current_token);
		}
		else if(ret_type == tok_whsp_s)
		{
			current_index = current_index + 1;
		}
		else if(ret_type == tok_whsp_t)
		{
			current_index = current_index + 1;
		}
		else if(ret_type == tok_whsp_n)
		{
			line_number = line_number + 1;
			current_index = current_index + 1;
			tokens.push_back(current_token);
		}
		else
		{
			printf("\n[STORY FILE ERROR] Unexpected token value: %c, Does not exist in grammar.\n\n",
				   file[current_index]);
			*R = false;
		}
	}
}

void Parser::show_error(ErrorType err)
{
	switch(err)
	{
		case IdenNotDefined:
			printf("\n[Syntax Error: Identifier '%s' not defined at line number: %d\n\n",
				   current_token.value.c_str(), current_token.line_number);
	}
}

std::string Parser::parse_string()
{
	std::string value;
	token current_token;
	bool lever = false;
	while(current_index < file.length() && running)
	{
		if(current_token.type == tok_quote)
		{
			if(lever)
			{
				value.append(current_token.value);
				lever = false;
			}
			else
			{
				current_index = current_index + 1;
				break;
			}
		}
		else if(current_token.type == tok_backsl)
		{
			lever = true;
		}
		else value.append(current_token.value);
	}
	return value;
}

void Parser::consume()
{
	current_index = current_index + 1;
	if(current_index <= tokens.size()) current_token = tokens[current_index];
}

relnode Parser::parse_tell()
{
	relnode current;
	current.left = current_token;
	consume();
	if(current_token.type != tok_colon)
	{
		show_error(ExpectedColon);
		return NULL;
	}
	current.op = current_token;
	consume();
	if(current_node.type != tok_strlit)
	{
		show_error(ExpectedStrLit);
		return NULL;
	}
	current.right = current_token;
	consume();
	return current;
}

var Parser::parse_assign()
{
	var current;
	if(current_token.type == tok_str)
	{
		current.type = 1;
		consume();
		if(current_token.type != tok_iden)
		{
			show_error(ExpectedIden);
			return NULL;
		}
		current.name = current_token;
		consume();
		if(current_token.type != tok_equal)
		{
			show_error(ExpectedAssignment);
			return NULL;
		}
		consume();
		if(current_token.type != tok_strlit)
		{
			show_error(ExpectedStrLit);
			return NULL;
		}
		current.sval = current_token;
	}
	else if(current_token.type == tok_int)
	{
		current.type = 0;
		consume();
		if(current_token.type != tok_iden)
		{
			show_error(ExpectedIden);
			return NULL;
		}
		current.name = current_token;
		consume();
		if(current_token.type != tok_equal)
		{
			show_error(ExpectedAssignment);
			return NULL;
		}
		consume();
		if(current_token.type != tok_intlit)
		{
			show_error(ExpectedStrLit);
			return NULL;
		}
		current.val = current_token;
	}
	consume();
	return current;
}

strct parse_struct()
{
	consume();
	strct current;
	consume();
	if(current_token.type != tok_iden)
	{
		show_error(ExpectedIden);
		return NULL;
	}
	current.name = current_token;
	consume();
	if(current_token.type != tok_lcurly)
	{
		show_error(ExpectedLcurly);
		return NULL;
	}
	consume();
	while(current_token.type != tok_rcurly)
	{
		if(current_token.type == tok_str || current_token.type == tok_int)
		{
			relnode current_in = parse_assign();
			if(current == NULL) return NULL;
			current.vars.push_back(current_in);
		}
		else if(current_token.type == tok_comma)
		{
			consume();
		}
		else
		{
			show_error(ExpectedDecln | ExpectedComma);
			return NULL;
		}
	}
}

relnode parse_reln()
{
	/*
		Lets conceal the mathematics, like +, -, *, /
		Develop a separate expr parser and return the final value.
		Expression evaluation can be done at once in one place.
		All we'll need is a final value.
	*/
}

Parser::Parser(std::string gfile) : file(gfile)
{
	lex();
	while(current_index <= tokens.size() && running)
	{
		current_token = tokens[current_index];
		if(current_token.type == tok_iden)
		{
			show_error(IdenNotDefined);
			break;
		}
		else if(current_token.type == tok_tell)
		{
			show_error(TellOutNarrative);
		}
		else if(current_token.type == tok_start)
		{
			consume();
			if(current_token.type != tok_colon)
			{
				show_error(ExpectedColon);
				break;
			}
			consume();
			if(current_token.type != tok_iden)
			{
				show_error(ExpectedIden);
				break;
			}
			start_loc = current_token.value;
		}
		else if(current_token.type == tok_str || current_token.type == tok_int)
		{
			relnode current = parse_assign();
			if(current == NULL) break;
			vars.push_back(current);
		}

		current_index = current_index + 1;
	}
}
