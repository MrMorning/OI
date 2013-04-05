/*
 * $Date: Sat Oct 29 14:36:54 2011 +0800
 * $Author: csimstu
 * $Source: Codeforces Beta Round #91 Problem B
 * $Method: Finding loops
 */
#include <cstdio>
char str[111111];
int s[111111];
int main(){
	int n, k;
	scanf("%d%d", &n, &k);
	scanf("%s", str);
	for(int i = 1; i <= n; i ++)
		s[i] = str[i - 1] - '0';
	for(int i = 1; k > 0 && i < n; i ++){
		if(s[i] == 4 && s[i + 1] == 7){
			if(i & 1)
				s[i + 1] = 4, k --;
			else{
				s[i] = 7;
				k --;
				if(i && s[i - 1] == 4){
					k %= 2;
					i -= 2;
				}
			}
		}
	}
	for(int i = 1; i <= n; i ++)
		printf("%d", s[i]);
}
