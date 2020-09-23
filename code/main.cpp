#include "stdafx.h"
#include "init.h"
#include "bruteforce.h"
#include "generate_node.h"
#include "graham_scan.h"
#include "opencv_convex.h"
#include "divide_and_conquer.h"

int main()
{
	map<string, string>fname;
	CParseIniFile config;
	char* config_path = "config.ini";
	bool flag = config.ReadConfig(config_path, fname, "method");
	if (!flag) return -1;
	switch (stoi(fname["method"])) {
	case 0:
		generate_node(config_path);
		break;
	case 1:
		bruteforce(config_path);
		break;	
	case 2:
		graham_scan(config_path);
		break;
	case 3:
		opencv_convex(config_path);
		break;
	case 4:
		divide_and_conquer(config_path);
		break;
	}
	char ch;
	while (1) {
		if ((ch = getchar()) == '\n')
			break;
	}
    return 0;
}

