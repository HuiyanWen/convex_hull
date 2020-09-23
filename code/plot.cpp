#include "stdafx.h"
#include "plot.h"
#include "utils.h"

using namespace cv;

const int gap = 0;
const Scalar wall_color(255, 255, 255);

void print_node(int *node) {
	cout << "(" << node[0] << "," << node[1] << ") ";
}

void drawBlock(Mat &img, int row, int col, int height, int width, Scalar color)
{
	Point p1 = Point(col * width + gap, row * height + gap);
	Point p2 = Point((col + 1) * width - gap, (row + 1) * height - gap);
	rectangle(img, p1, p2, color, -1);
}

void plot(int *dot, int *convex, const char *path, int dotnum, int convex_num, int whether_show_img) {
	
	int *min_node = (int *)malloc(2 * sizeof(int));
	int *max_node = (int *)malloc(2 * sizeof(int));
	int *temp_node = (int *)malloc(2 * sizeof(int));
	min_node[0] = 100;
	max_node[0] = 0;
	for (int i = 0; i < convex_num; i++) {
		if (convex[i * 2] < min_node[0]) {
			min_node[0] = convex[i * 2];
			min_node[1] = convex[i * 2 + 1];
		}
		if (convex[i * 2] > max_node[0]) {
			max_node[0] = convex[i * 2];
			max_node[1] = convex[i * 2 + 1];
		}
	}
	int up_node_count = 0;
	int down_node_count = 0;
	for (int i = 0; i < convex_num; i++) {
		if (f_value(min_node, max_node, &convex[i * 2]) < 0) {
			up_node_count++;
		}
		else if (f_value(min_node, max_node, &convex[i * 2]) > 0) {
			down_node_count++;
		}
	}
	vector <vector<int>> up_node(up_node_count);
	vector <vector<int>> down_node(down_node_count);
	if (up_node_count) {
		for (int i = 0; i <up_node_count; i++)
			up_node[i].resize(2);
	}
	if (down_node_count) {
		for (int i = 0; i <down_node_count; i++)
			down_node[i].resize(2);
	}	
	
	int up_node_count_temp = 0;
	int down_node_count_temp = 0;
	for (int i = 0; i < convex_num; i++) {
		if (f_value(min_node, max_node, &convex[i * 2]) < 0) {
			up_node[up_node_count_temp][0] = convex[i * 2];
			up_node[up_node_count_temp][1] = convex[i * 2 + 1];
			up_node_count_temp++;
		}
		else if (f_value(min_node, max_node, &convex[i * 2]) > 0) {
			down_node[down_node_count_temp][0] = convex[i * 2];
			down_node[down_node_count_temp][1] = convex[i * 2 + 1];
			down_node_count_temp++;
		}
	}
	if (up_node_count)	sort(down_node.begin(), down_node.end());
	if (down_node_count) sort(up_node.begin(), up_node.end());

	print_node(min_node);
	if (down_node_count) {
		for (int i = 0; i < down_node_count; i++) {
			temp_node[0] = down_node[i][0];
			temp_node[1] = down_node[i][1];
			print_node(temp_node);
		}
	}
	print_node(max_node);
	if (up_node_count) {
		for (int i = up_node_count-1; i >=0; i--) {
			temp_node[0] = up_node[i][0];
			temp_node[1] = up_node[i][1];
			print_node(temp_node);
		}
	}
	cout << endl;
	int large_size = 20;
	int line_size = 5;
	int gap_temp = 10;
	if (whether_show_img) {
		///
		Mat img = Mat::zeros(Size(100* large_size, 100* large_size), CV_8UC3);
		for (int m = 0; m < 100; m++) {
			for (int n = 0; n < 100; n++) {
				drawBlock(img, m, n, large_size, large_size, wall_color);
			}
		}
		///
		
		for (int i = 0; i < dotnum; i++) {
			drawBlock(img, dot[i * 2 + 1], dot[i * 2], large_size, large_size, Scalar(0, 0, 255));
			//if (dot[i * 2] == 0, dot[i * 2 + 1] == 7) cout << "yes" << endl;
		}
		
		//drawBlock(img, 0, 7, large_size, large_size, Scalar(0, 0, 255));
		//drawBlock(img, 99, 99, large_size, large_size, Scalar(0, 0, 255));
		//line(img, Point(0*large_size,0 * large_size), Point(0 * large_size, 81 * large_size), Scalar(0, 255, 0), 10);

		//	//Point p(dot[i * 2], dot[i * 2 + 1]);
		//	//circle(img, p, 1, Scalar(0, 255, 0), -1);
		//}
		//

		if (convex_num > 3) {
			//Á¬Ïß
			if (down_node_count) {
				line(img, Point(min_node[0] * large_size + gap_temp, min_node[1] * large_size + gap_temp), Point(down_node[0][0] * large_size + gap_temp, down_node[0][1] * large_size + gap_temp), Scalar(0, 255, 0), line_size);
				//cout << min_node[0] << " " << min_node[1] << "," << down_node[0][0] << " " << down_node[0][1] << endl;
				if (down_node.size() > 1) {
					for (int i = 0; i < down_node.size() - 1; i++) {
						line(img, Point(down_node[i][0] * large_size + gap_temp, down_node[i][1] * large_size + gap_temp), Point(down_node[i + 1][0] * large_size + gap_temp, down_node[i + 1][1] * large_size + gap_temp), Scalar(0, 255, 0), line_size);
					}
				}
				line(img, Point(down_node[down_node.size() - 1][0] * large_size + gap_temp, down_node[down_node.size() - 1][1] * large_size + gap_temp), Point(max_node[0] * large_size + gap_temp, max_node[1] * large_size + gap_temp), Scalar(0, 255, 0), line_size);
			}
			else
				line(img, Point(min_node[0] * large_size + gap_temp, min_node[1] * large_size + gap_temp), Point(max_node[0] * large_size + gap_temp, max_node[1] * large_size + gap_temp), Scalar(0, 255, 0), line_size);
			if (up_node_count) {
				line(img, Point(up_node[up_node.size() - 1][0] * large_size + gap_temp, up_node[up_node.size() - 1][1] * large_size + gap_temp), Point(max_node[0] * large_size + gap_temp, max_node[1] * large_size + gap_temp), Scalar(0, 255, 0), line_size);
				if (up_node_count > 1) {
					for (int i = 0; i < up_node.size() - 1; i++) {
						line(img, Point(up_node[i][0] * large_size + gap_temp, up_node[i][1] * large_size + gap_temp), Point(up_node[i + 1][0] * large_size + gap_temp, up_node[i + 1][1] * large_size + gap_temp), Scalar(0, 255, 0), line_size);
					}
				}
				line(img, Point(min_node[0] * large_size + gap_temp, min_node[1] * large_size + gap_temp), Point(up_node[0][0] * large_size + gap_temp, up_node[0][1] * large_size + gap_temp), Scalar(0, 255, 0), line_size);
			}

		}
		else {
			line(img, Point(convex[0 * 2] * large_size + gap_temp, convex[0 * 2 + 1] * large_size + gap_temp), Point(convex[1 * 2] * large_size + gap_temp, convex[1 * 2 + 1] * large_size + gap_temp), Scalar(0, 255, 0), line_size);
			line(img, Point(convex[1 * 2] * large_size + gap_temp, convex[1 * 2 + 1] * large_size + gap_temp), Point(convex[2 * 2] * large_size + gap_temp, convex[2 * 2 + 1] * large_size + gap_temp), Scalar(0, 255, 0), line_size);
			line(img, Point(convex[2 * 2] * large_size + gap_temp, convex[2 * 2 + 1] * large_size + gap_temp), Point(convex[0 * 2] * large_size + gap_temp, convex[0 * 2 + 1] * large_size + gap_temp), Scalar(0, 255, 0), line_size);
		}
		imwrite(path, img);
		cout << "Saved img result successfully." << endl;
	}

	
	free(min_node);
	free(max_node);
	free(temp_node);
}