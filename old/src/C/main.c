#include <stdio.h>
#include "parse.h"

int main(int argc, char* argv[])
{
	zstring value;
	token current_token;
	zstring_charp(&value, "forward: objects: $i$n:it$");

	for(int i = 0; i <= value.Len; i++)
	{
		next_token(&value, i, &current_token);
		printf("Value: %s\nType: %d\n", current_token.value.Data, current_token.type);
	}

	zstring_destroy(&value);
	return 0;
}
