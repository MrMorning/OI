/*
 * $Date: Wed Oct 19 10:36:58 2011 +0800
 * $Author: csimstu
 * $Source: School Regional Team Contest, Saratov, 2011 Problem A
 * $Method: ...
 */
#include <string>
#include <iostream>
#include <cstdio>
using namespace std;
int main(){
	freopen("input.txt", "r", stdin);
	freopen("output.txt", "w", stdout);
	string s;
	int a;
	cin >> s >> a;
	if(s == "front"){
		if(a == 1)
			printf("L");
		else
			printf("R");
	}
	else{
		if(a == 1)
			printf("R");
		else
			printf("L");
	}
}
