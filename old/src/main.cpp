#include <stdio.h>
#include <iostream>
#include <fstream>
#include <sstream>
#include "parse.h"

using namespace std;

int main(int argc, char* argv[])
{
    ifstream file;
    string buffer;
	token curr;
	vector <location> loc_stack;
	vector <object> obj_stack;
    file.open(argv[1], ios::in);

    if(file)
    {
        ostringstream ss;
        ss << file.rdbuf();
        buffer.append(ss.str());
    }
    file.close();
	
	parse(&loc_stack, &obj_stack, &buffer);

    return 0;
};
