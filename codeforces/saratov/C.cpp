/*
 * $Date: Wed Oct 19 10:37:43 2011 +0800
 * $Author: csimstu
 * $Source: School Regional Team Contest, Saratov, 2011 Problem C
 * $Method: ...
 */
#include <string>
#include <iostream>
#include <cstdio>
int n, k, a[101], cnt[101], done[101];
int main(){
	freopen("input.txt", "r", stdin);
	freopen("output.txt", "w", stdout);
	scanf("%d%d", &n, &k);
	for(int i = 1; i <= n; i ++)
		scanf("%d", &a[i]);
	int res = 0;
	while(1){
		int most = 0;
		for(int i = 1; i <= n; i ++)
			if(!done[i])
				if(most == 0 || (a[i] > a[most]))
					most = i;
		if(most == 0)
			break;
		if(a[most] < k || cnt[most] == 3)
			res += a[most], done[most] = true;
		else
			cnt[most] ++, a[most] -= k;
	}
	printf("%d\n", res);
}
