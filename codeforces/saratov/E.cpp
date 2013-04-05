/*
 * $Date: Wed Oct 19 10:38:39 2011 +0800
 * $Author: csimstu
 * $Source: School Regional Team Contest, Saratov, 2011 Problem E
 * $Method: Symmetry
 */
#include <string>
#include <iostream>
#include <cstdio>
#include <algorithm>
using namespace std;
int main(){
	freopen("input.txt", "r", stdin);
	freopen("output.txt", "w", stdout);
	int T, n;
	scanf("%d", &T);
	while(T --){
		scanf("%d", &n);
		printf("%d\n", !(n & 1));
	}
}
