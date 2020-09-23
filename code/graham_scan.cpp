#include "stdafx.h"
#include "graham_scan.h"
#include "init.h"
#include "utils.h"
#include "stack"
#include "plot.h"
#include <string>

#define max_num 99999
struct node
{
	int x, y;
	//float r;
};
node min_node;

int cross(node a, node b, node c)//º∆À„≤Êª˝
{
	return (b.x - a.x)*(c.y - a.y) - (c.x - a.x)*(b.y - a.y);
}

double dis(node a, node b)//º∆À„æ‡¿Î
{
	return sqrt((a.x - b.x)*(a.x - b.x)*1.0 + (a.y - b.y)*(a.y - b.y));
}

bool compare(node a, node b) {
	int m = cross(min_node, a, b);
	if (m<0)
		return 1;
	else if (m == 0 && dis(min_node, a) - dis(min_node, b) <= 0)
		return 1;
	else return 0;
}

int next_top(stack<int> s)
{
	int top = s.top();
	s.pop();
	int next_top = s.top();
	s.push(top);
	return next_top;	
}

void graham_scan(char *init_path) {
	const char *img_path;
	const char *dot_path;
	int dotnum, whether_show_img;;
	map<string, string>fname;
	CParseIniFile config;
	bool flag = config.ReadConfig(init_path, fname, "2");
	if (flag) {
		dotnum = stoi(fname["dotnum"]);
		whether_show_img = stoi(fname["whether_show_img"]);
		img_path = fname["img_path"].c_str();
		dot_path = fname["dot_path"].c_str();
	}
	else {
		cout << "Loading ini 2 error!" << endl;
		return;
	}
	//load dots
	int *dot = (int *)malloc((dotnum * 2) * sizeof(int));
	if (dotnum < 3) {
		cout << "Please generate more than 3 dots." << endl;
		exit(-1);
	}
	Load_file(dot_path, dot);

	clock_t begin, end;
	begin = clock();
	min_node.y = 100;
	for (int i = 0; i < dotnum; i++) {
		if (dot[i * 2 + 1] <= min_node.y) {
			if (dot[i * 2 + 1] == min_node.y) {
				if (dot[i * 2] < min_node.x) {
					min_node.x = dot[i * 2];
					min_node.y = dot[i * 2 + 1];
				}
			}
			else {
				min_node.x = dot[i * 2];
				min_node.y = dot[i * 2 + 1];
			}			
		}
	}
	struct node *dot_angle = (struct node *)malloc(dotnum * sizeof(struct node));

	for (int i = 0; i < dotnum; i++) {
		if (dot[i * 2] != min_node.x || dot[i * 2 + 1] != min_node.y) {
			//dot_angle[i].r = atan2(dot[i * 2 + 1], -dot[i * 2]);
			dot_angle[i].x = dot[i * 2];
			dot_angle[i].y = dot[i * 2 + 1];
		}
		else {
			//dot_angle[i].r = -max_num;
			dot_angle[i].x = dot[i * 2];
			dot_angle[i].y = dot[i * 2 + 1];
		}
	}

	sort(dot_angle, dot_angle+dotnum, compare);


	stack<int> s;
	s.push(0);
	s.push(1);
	s.push(2);
	int next_to_top, top;
	for (int i = 3; i < dotnum; i++) {
		Print_process(dotnum , i, 1);
		while (cross(dot_angle[next_top(s)], dot_angle[s.top()], dot_angle[i])>=0){
			s.pop();
			if (s.size() == 1) break;
		}
		s.push(i);
	}	
	end = clock();
	int *convex = (int *)malloc((s.size()*2) * sizeof(int));
	int convex_num = 0;
	while (!s.empty()) {
		convex[convex_num * 2] = dot_angle[s.top()].x;
		convex[convex_num * 2 + 1] = dot_angle[s.top()].y;
		convex_num++;
		s.pop();
	}
	cout << endl;
	cout << "convex_num:" << convex_num << endl;
	plot(dot, convex, img_path, dotnum, convex_num, whether_show_img);	
	free(dot);
	cout << "Calculation time:" << end - begin << endl;
}

