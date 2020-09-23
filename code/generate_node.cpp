#include "stdafx.h"
#include "generate_node.h"
#include "init.h"
#include "utils.h"

void generate_node(char *init_path) {
	int dotnum;
	const char* dot_path;
	map<string, string>fname;
	CParseIniFile config;	
	bool flag = config.ReadConfig(init_path, fname, "0");
	if (flag) {
		dotnum = stoi(fname["dotnum"]);
		dot_path = fname["dot_path"].c_str();
	}
	else {
		cout << "Loading ini 0 error!" << endl;
		return;
	}
	int *dot = (int *)malloc((dotnum * 2) * sizeof(int));
	srand((unsigned)time(0));
	generate_dot_set(dot, dotnum);
	ofstream out(dot_path, ios::app);
	for (int i = 0; i < dotnum; i++) {
		out << dot[i * 2] << " " << dot[i * 2 + 1] << endl;
	}
	out.close();
	free(dot);
	cout << "Genrate nodes successfully!" << endl;
}