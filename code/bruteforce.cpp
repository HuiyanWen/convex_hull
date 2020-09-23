#include "stdafx.h"
#include "init.h"
#include "utils.h"
#include "plot.h"

#define ABS_FLOAT_0 0.0001   


struct point_float
{
	float x;
	float y;
};

float GetTriangleSquar(const point_float pt0, const point_float pt1, const point_float pt2)
{
	point_float AB, BC;    
	AB.x = pt1.x - pt0.x;   
	AB.y = pt1.y - pt0.y;   
	BC.x = pt2.x - pt1.x;   
	BC.y = pt2.y - pt1.y;     
	return fabs((AB.x * BC.y - AB.y * BC.x)) / 2.0f;    
}
 
bool IsInTriangle(const point_float A, const point_float B, const point_float C, const point_float D)
{
	if (A.x == -1 || B.x == -1 || C.x == -1 || D.x == -1) return false;
	float SABC, SADB, SBDC, SADC;
	SABC = GetTriangleSquar(A, B, C);
	SADB = GetTriangleSquar(A, D, B);
	SBDC = GetTriangleSquar(B, D, C);
	SADC = GetTriangleSquar(A, D, C);
 
	float SumSuqar = SADB + SBDC + SADC;
 
	if ((-ABS_FLOAT_0 < (SABC - SumSuqar)) && ((SABC - SumSuqar) < ABS_FLOAT_0))
	{
		return true;
	}
	else
	{
		return false;
	}
}


void bruteforce(char* init_path) {
	const char *img_path;
	const char *dot_path;
	int dotnum, whether_show_img;;
	int convex_num = 0;
	map<string, string>fname;
	CParseIniFile config;
	bool flag = config.ReadConfig(init_path, fname, "1");
	if (flag) {
		dotnum = stoi(fname["dotnum"]);
		whether_show_img = stoi(fname["whether_show_img"]);
		img_path = fname["img_path"].c_str();
		dot_path = fname["dot_path"].c_str();
	}
	else {
		cout << "Loading ini 1 error!" << endl;
		return;
	}
	//load dots
	int *dot = (int *)malloc((dotnum * 2) * sizeof(int));
	if (dotnum < 3) {
		cout << "Please generate more than 3 dots." << endl;
		exit(-1);
	}
	Load_file(dot_path, dot);
	
	int *dot_cpy = (int *)malloc((dotnum * 2) * sizeof(int));
	for (int i = 0; i < dotnum; i++) {
		dot_cpy[i * 2] = dot[i * 2];
		dot_cpy[i * 2 + 1] = dot[i * 2 + 1];
	}
	clock_t begin, end;
	begin = clock();
	point_float pt1, pt2, pt3, pt4;
	for (int i = 0; i < dotnum-2; i++) {
		Print_process(dotnum , i, 1);
		pt1.x = dot[i * 2];
		pt1.y = dot[i * 2 + 1];
		for (int j = i+1; j < dotnum-1; j++) {
			if (i == j) continue;
			pt2.x = dot[j * 2];
			pt2.y = dot[j * 2 + 1];
			for (int k = j+1; k < dotnum; k++) {
				if (k == i || k == j) continue;
				pt3.x = dot[k * 2];
				pt3.y = dot[k * 2 + 1];
				for (int m = 0; m < dotnum; m++){
					if (m == i || m == j || m == k) continue;
					//取m作为外点
					pt4.x = dot[m * 2];
					pt4.y = dot[m * 2 + 1];
					if (IsInTriangle(pt1, pt2, pt3, pt4)) {
						dot[m * 2] = -1;
						dot[m * 2 + 1] = -1;
						convex_num++;
					}
					/*if (judge_node(&dot[i * 2], &dot[j * 2], &dot[k * 2], &dot[m * 2])) {
						dot[m * 2] = -1;
						dot[m * 2 + 1] = -1;
						convex_num++;
					}	*/				
				}
			}
		}
	}
	end = clock();
	convex_num = dotnum - convex_num;
	int *convex = (int *)malloc((convex_num * 2) * sizeof(int));
	convex_num = 0;
	for (int i = 0; i < dotnum; i++) {
		if (dot[i * 2] != -1) {
			convex[convex_num * 2] = dot[i * 2];
			convex[convex_num * 2 + 1] = dot[i * 2 + 1];
			convex_num++;
		}
	}
	cout << endl;
	cout << "convex_num:" << convex_num << endl;
	plot(dot_cpy, convex, img_path, dotnum, convex_num, whether_show_img);
	free(dot);
	free(dot_cpy);
	cout << "Calculation time:" << end - begin << endl;
}