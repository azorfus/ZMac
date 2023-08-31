#include "parse.h"
#include <iostream>

toktype return_toktype(const char value)
{
	if(value == ':') return tok_colon;
	else if(value == '{') return tok_lcurly;
	else if(value == '}') return tok_rcurly;
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

void next_token(std::string* file, unsigned int* current_index, token* current_token, bool* R)
{
	bool ragain = false;
	while(!ragain)
	{
	toktype ret_type = return_toktype((*file)[*current_index]);
	ragain = false;
	if(ret_type == tok_alpha)
	{
		std::string value = "";
		while(*current_index <= file->length())
		{
			value.push_back((*file)[*current_index]);
			if(*current_index + 1 <= file->length())
			{
				if(return_toktype((*file)[*current_index + 1]) != tok_alpha) break;
				else
				{
					*current_index = *current_index + 1;
					ret_type = return_toktype((*file)[*current_index]);
				}
			}
		}
		
		if(value == "name") current_token->type = tok_name;
		else if(value == "forward") current_token->type = tok_forward;
		else if(value == "objects") current_token->type = tok_objects;
		else if(value == "desc") current_token->type = tok_desc;
		else if(value == "indesc") current_token->type = tok_indesc;
		else if(value == "paths") current_token->type = tok_paths;
		else if(value == "interact") current_token->type = tok_interact;
		else if(value == "location") current_token->type = tok_location;
		else if(value == "object") current_token->type = tok_object;
		else if(value == "synonym") current_token->type = tok_synonym;
		else if(value == "CF") current_token->type = tok_cf;
		else if(value == "ZF") current_token->type = tok_zf;
		else if(value == "SF") current_token->type = tok_sf;
		else if(value == "article") current_token->type = tok_article;
		else if(value == "mass") current_token->type = tok_mass;
		else if(value == "tell") current_token->type = tok_tell;
		else if(value == "none") current_token->type = tok_none;
		else if(value == "start") current_token->type = tok_start;
		else current_token->type = tok_iden;
		current_token->value = value;
		*current_index = *current_index + 1;
	}
	else if(ret_type == tok_intlit)
	{
		std::string value = "";
		while(*current_index <= file->length() && ret_type == tok_intlit)
		{
			value.push_back((*file)[*current_index]);
			*current_index = *current_index + 1;
			if(*current_index + 1 <= file->length()) ret_type = return_toktype((*file)[*current_index]);
		}
		current_token->value = value;
		current_token->type = tok_int;
		*current_index = *current_index + 1;
	}
	else if(ret_type == tok_lcurly)
	{
		current_token->value = "{";
		current_token->type = tok_lcurly;
		*current_index = *current_index + 1;
	}
	else if(ret_type == tok_rcurly)
	{
		current_token->value = "}";
		current_token->type = tok_rcurly;
		*current_index = *current_index + 1;
	}
	else if(ret_type == tok_lbrack)
	{
		current_token->value = "(";
		current_token->type = tok_lbrack;
		*current_index = *current_index + 1;
	}
	else if(ret_type == tok_rbrack)
	{
		current_token->value = ")";
		current_token->type = tok_rbrack;
		*current_index = *current_index + 1;
	}
	else if(ret_type == tok_quote)
	{
		current_token->value = "\"";
		current_token->type = tok_quote;
		*current_index = *current_index + 1;
	}
	else if(ret_type == tok_backsl)
	{
		current_token->value = "\\";
		current_token->type = tok_backsl;
		*current_index = *current_index + 1;
	}
	else if(ret_type == tok_dollar)
	{
		current_token->value = "$";
		current_token->type = tok_dollar;
		*current_index = *current_index + 1;
	}
	else if(ret_type == tok_colon)
	{
		current_token->value = ":";
		current_token->type = tok_colon;
		*current_index = *current_index + 1;
	}
	else if(ret_type == tok_comma)
	{
		current_token->value = ",";
		current_token->type = tok_comma;
		*current_index = *current_index + 1;
	}
	else if(ret_type == tok_whsp_s)
	{
		*current_index = *current_index + 1;
		ragain = true;
	}
	else if(ret_type == tok_whsp_t)
	{
		*current_index = *current_index + 1;
		ragain = true;
	}
	else if(ret_type == tok_whsp_n)
	{
		current_token->line_number = current_token->line_number + 1;
		*current_index = *current_index + 1;
		ragain = true;
	}
	else
	{
		printf("\n[STORY FILE ERROR] Unexpected token value: %c, Does not exist in grammar.\n\n",
			   (*file)[*current_index]);
		*R = false;
	}
	}

}

void show_error(ErrorType err, token* current_token)
{
	switch(err)
	{
		case IdenNotDefined:
			printf("\n[Syntax Error: Identifier '%s' not defined at line number: %d\n\n",
				   current_token->value.c_str(), current_token->line_number);
	}
}

std::string parse_string(std::string* file, unsigned int* current_index)
{
	std::string value;
	token current_token;
	bool running = true;
	bool lever = false;
	while(*current_index < file->length() && running)
	{
		next_token(file, current_index, &current_token, &running);
		if(current_token.type == tok_quote)
		{
			if(lever)
			{
				value.append(current_token.value);
				lever = false;
			}
			else
			{
				*current_index = *current_index + 1;
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

void parse(std::vector <location>* loc_stack, std::vector <object>* obj_stack,
		   std::string* file)
{
	unsigned int current_index = 0;
	token current_token;
	std::string buffer = "";
	bool run = true;
	bool running = true;
	bool lever = false;
	while(current_index <= file->length() && running == true)
	{
		next_token(file, &current_index, &current_token, &running);
		if(current_token.type == tok_iden)
		{
			show_error(IdenNotDefined, &current_token);
			break;
		}
		else if(current_token.type == tok_tell)
		{
			next_token(file, &current_index, &current_token, &running);
			if(current_token.type != tok_colon)
			{
				show_error(ExpectedColon, &current_token);
				break;
			}
			next_token(file, &current_index, &current_token, &running);
			if(current_token.type != tok_quote)
			{
				show_error(ExpectedQuote, &current_token);
				break;
			}
			std::cout << parse_string(file, &current_index) << std::endl;
		}
	}
}
