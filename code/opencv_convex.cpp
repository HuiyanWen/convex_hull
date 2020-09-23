#include "stdafx.h"
#include "init.h"
#include "utils.h"
#include "plot.h"
using namespace cv;

void opencv_convex(char* init_path) {
	const char *img_path;
	const char *dot_path;
	int dotnum, whether_show_img;;
	map<string, string>fname;
	CParseIniFile config;
	bool flag = config.ReadConfig(init_path, fname, "3");
	if (flag) {
		dotnum = stoi(fname["dotnum"]);
		whether_show_img = stoi(fname["whether_show_img"]);
		img_path = fname["img_path"].c_str();
		dot_path = fname["dot_path"].c_str();
	}
	else {
		cout << "Loading ini 3 error!" << endl;
		return;
	}
	//load dots
	int *dot = (int *)malloc((dotnum * 2) * sizeof(int));
	if (dotnum < 3) {
		cout << "Please generate more than 3 dots." << endl;
		exit(-1);
	}
	Load_file(dot_path, dot);
	vector <int> hull;
	vector<Point> points;
	Point temp_point;
	for (int i = 0; i < dotnum; i++) {
		temp_point.x = dot[i * 2];
		temp_point.y = dot[i * 2 + 1];
		points.push_back(temp_point);
	}
	clock_t begin, end;
	begin = clock();
	convexHull(Mat(points), hull, true);
	end = clock();
	cout << "convex_num:" << hull.size() << endl;
	int *convex = (int *)malloc((hull.size() * 2) * sizeof(int));
	for (int i = 0; i < hull.size(); i++) {
		convex[i * 2] = points[hull[i]].x;
		convex[i * 2 + 1] = points[hull[i]].y;
	}
	plot(dot, convex, img_path, dotnum, hull.size(), whether_show_img);
	cout << "Calculation time:" << end - begin << endl;
}