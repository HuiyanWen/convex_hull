#include "stdafx.h"
#include "divide_and_conquer.h"
#include "init.h"
#include "utils.h"
#include <opencv2\opencv.hpp>
#include <opencv2\core\core.hpp>  
#include <opencv2\highgui\highgui.hpp>
#include <time.h>
#include <windows.h>
#include "plot.h"

using namespace cv;

int Cal_S(Point a1, Point a2, Point a3)
{
	int calculate = a1.x*a2.y + a3.x*a1.y + a2.x*a3.y - a3.x*a2.y - a2.x*a1.y - a1.x*a3.y;
	return calculate;
}
bool cmp_x(Point a, Point b) //按x轴排序,如果x相同,按y轴排序
{
	if (a.x != b.x)
		return a.x < b.x;
	else
		return a.y < b.y;
}
void Divide(int first, int last, vector<Point> &node, int *vst)
{
	int max_p = 0, index = -1;
	int i = first;
	if (first < last)
	{
		for (i = first + 1; i < last; i++) 
		{
			int calcu = Cal_S(node[first], node[i], node[last]);
			if (calcu > max_p)
			{
				max_p = calcu;
				index = i;
			}

		}
	}
	else
	{
		for (i - 1; i >last; i--) 
		{
			int calcu = Cal_S(node[first], node[i], node[last]);
			if (calcu > max_p)
			{
				max_p = calcu;
				index = i;
			}
		}
	}
	if (index != -1)
	{
		vst[index] = 1; 
		Divide(first, index, node, vst);
		Divide(index, last, node, vst);
	}
}


void divide_and_conquer(char* init_path) {
	const char *img_path;
	const char *dot_path;
	int dotnum, whether_show_img;
	map<string, string>fname;
	CParseIniFile config;
	bool flag = config.ReadConfig(init_path, fname, "4");
	if (flag) {
		dotnum = stoi(fname["dotnum"]);
		whether_show_img = stoi(fname["whether_show_img"]);
		img_path = fname["img_path"].c_str();
		dot_path = fname["dot_path"].c_str();
	}
	else {
		cout << "Loading ini 4 error!" << endl;
		return;
	}
	//load dots
	int *dot = (int *)malloc((dotnum * 2) * sizeof(int));
	if (dotnum < 3) {
		cout << "Please generate more than 3 dots." << endl;
		exit(-1);
	}
	Load_file(dot_path, dot);
	int *vst = (int *)malloc(dotnum * sizeof(int));

	clock_t begin, end;
	begin = clock();
	vector<Point> node;
	Point temp_node;
	for (int i = 0; i < dotnum; i++) {
		vst[i] = 0;
		temp_node.x = dot[2 * i];
		temp_node.y = dot[2 * i + 1];
		node.push_back(temp_node);
	}
	vst[0] = 1;
	vst[dotnum - 1] = 1;
	sort(node.begin(), node.end(), cmp_x);
	Divide(0, dotnum - 1, node, vst);
	Divide(dotnum - 1, 0, node, vst);
	int convex_num = 0;
	for (int i = 0; i < dotnum; i++) {
		if (vst[i] == 1) convex_num++;
	}	
	int *convex = (int *)malloc((convex_num * 2) * sizeof(int));
	//cout << "convex_num:" << convex_num << endl;
	convex_num = 0;
	for (int i = 0; i < dotnum; i++) {
		if (vst[i] == 1) {
			convex[2 * convex_num] = node[i].x;
			convex[2 * convex_num + 1] = node[i].y;
			convex_num++;
		}
	}
	end = clock();
	cout << "convex_num:" << convex_num << endl;
	plot(dot, convex, img_path, dotnum, convex_num, whether_show_img);
	free(convex);
	free(dot);
	cout << "Calculation time:" << end - begin << endl;
}