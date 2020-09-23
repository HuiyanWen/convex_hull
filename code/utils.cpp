#include "stdafx.h"
#include "utils.h"

int duplicate(int *dot, int i, int temp1, int temp2) {
	for (int m = 0; m < i; m++) {
		if (dot[m * 2] == temp1&&dot[m * 2 + 1] == temp2) return 1;
	}
	return 0;
}

bool happened(double probability)//probability 0~1
{
	double MinProb = 1.0 / (RAND_MAX + 1);
	if (probability <= 0)
	{
		return false;
	}
	if (probability<MinProb)
	{
		return rand() == 0 && happened(probability*(RAND_MAX + 1));
	}
	if (rand() <= probability*(RAND_MAX + 1))
	{
		return true;
	}
	return false;
}

long myrandom(long n)//����0~n-1֮��ĵȸ��������
{
	long t = 0;
	if (n <= RAND_MAX)
	{
		long r = RAND_MAX - (RAND_MAX + 1) % n;//β��
		t = rand();
		while (t > r)
		{
			t = rand();
		}
		return t % n;
	}
	else
	{
		long r = n % (RAND_MAX + 1);//����
		if (happened((double)r / n))//ȡ�������ĸ���
		{
			return n - r + myrandom(r);
		}
		else
		{
			return rand() + myrandom(n / (RAND_MAX + 1))*(RAND_MAX + 1);
		}
	}
}

void generate_dot_set(int *dot, int n) {
	int temp1;
	int temp2;
	for (int i = 0; i<n; i++) {		
		do {
			temp1 = myrandom(100);
			temp2 = myrandom(100);
		} while (duplicate(dot, i, temp1, temp2));
		dot[i * 2] = temp1;
		dot[i * 2 + 1] = temp2;
	}
}

//����m��xy������ȷ��ֱ����һ��
int f_value(int *x, int *y, int *m) {
	if((x[0] - y[0])>0)
		return m[0] * (y[1] - x[1]) + m[1] * (x[0] - y[0]) + y[0] * x[1] - x[0] * y[1];
	return -(m[0] * (y[1] - x[1]) + m[1] * (x[0] - y[0]) + y[0] * x[1] - x[0] * y[1]);
}

////�ж�d�Ƿ���abc�ڲ�
//int judge_node(int *a, int *b, int *c, int *d) {
//	if (a[0] == -1 || b[0] == -1 || c[0] == -1 || d[0] == -1) return 0;
//	if ((f_value(a, b, c)*f_value(a, b, d)) > 0) {
//		if ((f_value(a, c, b)*f_value(a, c, d)) > 0) {
//			if ((f_value(b, c, a)*f_value(b, c, d)) > 0) {
//				return 1;
//			}
//		}
//	}
//	return 0;
//}

//bool cmp(int x, int y) {
//	return x > y;
//}

void Print_process(int total_num, int cur_num, int process) {
	if (cur_num % process == 0) {
		printf("The progeress:%.2f/1.00\r", (float)cur_num / total_num);
		fflush(stdout);
	}
}