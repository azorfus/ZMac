#include "parse.h"

toktype return_toktype(const char value)
{
	if(value == ':') return tok_colon;
	else if(value == '{') return tok_lcurly;
	else if(value == '}') return tok_rcurly;
	else if(value == '\"') return tok_quote;
	else if(value == '(') return tok_lbrack;
	else if(value == ')') return tok_rbrack;
	else if(isalpha(value) || value == '_') return tok_alpha;
	else if(isdigit(value)) return tok_intlit;
	else if(value == '$') return tok_dollar;
}

void next_token(zstring* file, unsigned int curr_index, token* curr_token)
{
		toktype ret_type = return_toktype(file->Data[curr_index]);
		if(ret_type == tok_alpha)
		{
			int i = curr_index;
			zstring value;
			zstring_init(&value);
			while(i <= file->Len && ret_type == tok_alpha)
			{
				zstring_appendC(&value, file->Data[i]);
				i++;
				if(i + 1 <= file->Len) ret_type = return_toktype(file->Data[i]);
			}
			printf("**** %s ****\n", value.Data);
			zstring_charp(&curr_token->value, value.Data);
			if(value.Data == "name") curr_token->type = tok_name;
			else if(value.Data == "forward") curr_token->type = tok_forward;
			else if(value.Data == "objects") curr_token->type = tok_objects;
			else if(value.Data == "desc") curr_token->type = tok_desc;
			else if(value.Data == "indesc") curr_token->type = tok_indesc;
			else if(value.Data == "paths") curr_token->type = tok_paths;
			else if(value.Data == "interact") curr_token->type = tok_interact;
			else if(value.Data == "location") curr_token->type = tok_location;
			else if(value.Data == "object") curr_token->type = tok_object;
			else if(value.Data == "synonym") curr_token->type = tok_synonym;
			else if(value.Data == "CF") curr_token->type = tok_cf;
			else if(value.Data == "ZF") curr_token->type = tok_zf;
			else if(value.Data == "SF") curr_token->type = tok_sf;
			else if(value.Data == "article") curr_token->type = tok_article;
			else if(value.Data == "mass") curr_token->type = tok_mass;
			else if(value.Data == "tell") curr_token->type = tok_tell;
			else if(value.Data == "none") curr_token->type = tok_none;
			else curr_token->type = tok_iden;
			
			zstring_destroy(&value);
		}
		else if(ret_type == tok_intlit)
		{
			int i = curr_index;
			zstring value;
			zstring_init(&value);
			while(i <= file->Len && ret_type == tok_intlit)
			{
				zstring_appendC(&value, file->Data[i]);
				i++;
				if(i + 1 <= file->Len) ret_type = return_toktype(file->Data[i]);
			}
			zstring_charp(&curr_token->value, value.Data);
			curr_token->type = tok_int;
			
			zstring_destroy(&value);
		}
		else if(ret_type == tok_lcurly)
		{
			zstring_charp(&curr_token->value, "{");
			curr_token->type == tok_lcurly;
		}
		else if(ret_type == tok_rcurly)
		{
			zstring_charp(&curr_token->value, "}");
			curr_token->type == tok_rcurly;
		}
		else if(ret_type == tok_lbrack)
		{
			zstring_charp(&curr_token->value,"(");
			curr_token->type == tok_lbrack;
		}
		else if(ret_type == tok_rbrack)
		{
			zstring_charp(&curr_token->value, ")");
			curr_token->type == tok_rbrack;
		}
		else if(ret_type == tok_quote)
		{
			zstring_charp(&curr_token->value, "\"");
			curr_token->type == tok_rbrack;
		}
		else if(ret_type == tok_dollar)
		{
			zstring_charp(&curr_token->value, "$");
			curr_token->type == tok_dollar;
		}
		else if(ret_type == tok_colon)
		{
			zstring_charp(&curr_token->value, ":");
			curr_token->type == tok_colon;
		}
		else
		{
			printf("[STORY FILE ERROR] Unexpected token value: %c, Does not exist in grammar.",
				   file->Data[curr_index]);
		}
}

