/*
 * Date: Tue Jan 18 11:30:33 CST 2011
 * Author: csimstu
 * Problem: Palindrome
 * Source: IOI 2000 day1 task1
 * Submission: WA
 * Algorithm: easy DP 
 */
#include <cstdio> #include <cstring>
#define MAXN 5001

int n, f1[MAXN], f2[MAXN];
char s[MAXN];

void update(int &a, int x)
{
	if(a > x)
		a = x;
}

int main(){
	freopen("t.in", "r", stdin);
	scanf("%d\n", &n);
	for(int i = 1; i <= n; i ++)
		scanf("%c", &s[i]);
	for(int i = n; i >= 1; i --){
		memset(f2, 0x3f, sizeof(f2));
		f2[i] = f1[i] = 0;
		for(int j = i; j <= n; j ++){
			update(f2[j], f1[j-1] + !(s[i] == s[j]) * 2);
			if(i < j){
				update(f2[j], f1[j] + 1);
				update(f2[j], f2[j-1] + 1);
			}
		}
		memcpy(f1, f2, sizeof(f1));
	}
	printf("%d\n", f1[n]);
}
