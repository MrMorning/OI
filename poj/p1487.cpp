/*
 * Date: Sun Jan 30 21:54:45 CST 2011
 * Author: csimstu
 * Problem: poj1487
 * Algorithm: Recursion + Caching + Gauss Elimination
 */
#include <cstdio>
#include <cstring>
#include <iostream>
#include <algorithm>
#include <string>
#define INFINITY 0x3f3f3f3f
#define EPS 1E-8
//#define DEBUG

using std::cin;
using std::string;
using std::swap;

int n, now;
double matrix[27][28], ans[27];
string str;

double abs(double x)
{
	return x < 0 ? -x : x;
}

void solve(int l, int r, double expt)
{
	int num = 0, minusFlag = 1;
	bool numFlag = false;
	int cache[100], top = 0, type[100], sonNum = 0;//1:num;2:alpha;3:node
	for(int i = l; i <= r; i ++)
	{
		if(str[i] == '(')
		{
			int cnt = 0;
			int j;
			for(j = i; ; j ++)
			{
				if(str[j] == '(')
					cnt ++;
				else if(str[j] == ')')
					cnt --;
				if(cnt == 0)
					break;
			}
			//solve(i + 1, j - 1, depth + 1);
			cache[++ top] = i + 1;
			cache[++ top] = j - 1;
			type[top - 1] = 3;
			i = j + 1;
			sonNum ++;
		}
		if(str[i] == ' ' || str[i] == ')')
		{
			//refresh num
			if(numFlag)
			{
				cache[++ top] = minusFlag * num;
				type[top] = 1;
				sonNum ++;
				numFlag = false;
				minusFlag = 1;
			}
		}
		else if(str[i] == '-')
		{
			numFlag = true;
			minusFlag = -1;
			num = 0;
		}
		else if('0' <= str[i] && str[i] <= '9')
		{
			if(! numFlag)//如果还没有开始计数
			{
				numFlag = true;
				minusFlag = 1;
				num = str[i] - '0';
			}
			else
				num = num * 10 + str[i] - '0';
		}
		else if('a' <= str[i] && str[i] <= 'z')// is an alphabet
		{
			//matrix[now][str[i] - 'a' + 1] = - expt;
			cache[++ top] = str[i] - 'a' + 1;
			type[top] = 2;
			sonNum ++;
		}
	}
	if(numFlag)
	{
		cache[++ top] = minusFlag * num;
		type[top] = 1;
		sonNum ++;
		numFlag = false;
		minusFlag = 1;
	}
	if(sonNum != 0)
		expt /= sonNum;
	for(int i = 1; i <= top; i ++)
	{
		if(type[i] == 1)
			matrix[now][27] += cache[i] * expt;
		else if(type[i] == 2)
			matrix[now][cache[i]] += -expt;
		else
		{
			solve(cache[i], cache[i + 1], expt);
			i ++;
		}
	}
#ifdef DEBUG
	printf("finsh searching [%d, %d]\n", l, r);
	printf("row %d change into:\n", now);
	for(int k = 1; k <= 27; k ++)
		printf("%.2f ", matrix[now][k]);
	printf("\n");
#endif
}

void elimination()
{
	int j = 1;
	for(int i = 1; i <= n; i ++)
	{
		int p = i;
		while(abs(matrix[p][j]) < EPS)
		{
			while(p <= n && abs(matrix[p][j]) < EPS)
				p ++;
			if(p == n + 1)
			{
				j ++;
				p = i;
			}
		}
		for(int k = 1; k <= 27; k ++)
			swap(matrix[p][k], matrix[i][k]);
		double tmp = matrix[i][j];
		for(int k = j; k <= 27; k ++)
			matrix[i][k] /= tmp;
		for(p = 1; p <= n; p ++)
			if(p != i && abs(matrix[p][j]) > EPS)
			{
				tmp = matrix[p][j];
				for(int k = 1; k <= 27; k ++)
					matrix[p][k] -= tmp * matrix[i][k];
			}
	}
}

int main()
{
	freopen("t.in", "r", stdin);
	int testCnt = 0;
	while(1)
	{
		scanf("%d\n", &n);
		if(n == 0)
			break;
		testCnt ++;
		memset(matrix, 0, sizeof(matrix));
		for(int i = 1; i <= n; i ++)
		{
			getline(cin, str);
			int pos = str.find("(");
			str = str.substr(pos, str.size() - pos);
			matrix[i][i] = 1;
			now = i;
			solve(0, str.size() - 1, 1);
		}
		elimination();
		for(int i = 1; i <= n; i ++)
			ans[i] = INFINITY;
		for(int i = 1; i <= n; i ++)
		{
			int tmp = 0;
			for(int k = 1; k <= 26; k ++)
				if(abs(matrix[i][k]) > EPS)
				{
					tmp = k;
					break;
				}
			bool failed = false;
			if(abs(tmp) < EPS)
				failed = true;
			else
				for(int k = tmp + 1; k <= 26; k ++)
					if(abs(matrix[i][k]) > 0)
					{
						failed = true;
						break;
					}
			if(! failed)
				ans[tmp] = matrix[i][27];
		}
		printf("Game %d\n", testCnt);
		for(int i = 1; i <= n; i ++)
			if(abs(ans[i] - INFINITY) > EPS)
				printf("Expected score for %c = %.3f\n", i + 'a' - 1, ans[i]);
			else
				printf("Expected score for %c undefined\n", i + 'a' - 1);
		printf("\n");
	}
}
