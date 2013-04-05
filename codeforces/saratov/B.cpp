/*
 * $Date: Wed Oct 19 10:37:25 2011 +0800
 * $Author: csimstu
 * $Source: School Regional Team Contest, Saratov, 2011 Problem B
 * $Method: ...
 */
#include <string>
#include <iostream>
#include <cstdio>
int n, k, a[1001];
int main(){
	freopen("input.txt", "r", stdin);
	freopen("output.txt", "w", stdout);
	scanf("%d%d", &n, &k);
	for(int i = 1; i <= n; i ++)
		scanf("%d", &a[i]);
	while(a[k] == 0)
		k = k % n + 1;
	printf("%d\n", k);
}
