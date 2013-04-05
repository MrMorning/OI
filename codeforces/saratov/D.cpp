/*
 * $Date: Wed Oct 19 10:38:05 2011 +0800
 * $Author: csimstu
 * $Source: School Regional Team Contest, Saratov, 2011 Problem D
 * $Method: Prefix sums
 */
#include <string>
#include <iostream>
#include <cstdio>
#include <algorithm>
using namespace std;
int n, m, c[55][55], p[55][55], r[3];
int getSum(int x1, int y1, int x2, int y2){
	return p[x2][y2] - p[x1 - 1][y2] - p[x2][y1 - 1] + p[x1 - 1][y1 - 1];
}
int main(){
	freopen("input.txt", "r", stdin);
	freopen("output.txt", "w", stdout);
	scanf("%d%d", &n, &m);
	for(int i = 1; i <= n; i ++)
		for(int j = 1; j <= m; j ++){
			scanf("%d", &c[i][j]);
			p[i][j] = p[i - 1][j] + p[i][j - 1] - p[i - 1][j - 1] + c[i][j];
		}
	scanf("%d%d%d", &r[0], &r[1], &r[2]);
	sort(r, r + 3);
	int res = 0;
	for(int i = 1; i < m; i ++)
		for(int j = i + 1; j < m; j ++){
			int s[3];
			s[0] = getSum(1, 1, n, i);
			s[1] = getSum(1, i + 1, n ,j);
			s[2] = getSum(1, j + 1, n, m);
			sort(s, s + 3);
			if(s[0] == r[0] && s[1] == r[1] && s[2] == r[2])
				res ++;
		}
	for(int i = 1; i < n; i ++)
		for(int j = i + 1; j < n; j ++){
			int s[3];
			s[0] = getSum(1, 1, i, m);
			s[1] = getSum(i + 1, 1, j ,m);
			s[2] = getSum(j + 1, 1, n, m);
			sort(s, s + 3);
			if(s[0] == r[0] && s[1] == r[1] && s[2] == r[2])
				res ++;
		}
	printf("%d\n", res);
}
