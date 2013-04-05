/*
 * $Date: Mon Oct 31 16:05:54 2011 +0800
 * $Author: csimstu
 * $Source: Codechef COOK15 GENARSEQ
 * $Method: Brute force
 */
#include <cstdio>
#include <cstring>
int x[1111];
bool hash[1000010];
void solve(){
	int a, b, n;
	memset(hash, 0, sizeof(hash));
	scanf("%d%d%d", &a, &b, &n);
	x[1] = 1;
	if(a * x[1] - b * x[1] > 0)
		hash[a * x[1] - b * x[1]] = true;
	int next = 2;
	for(int i = 2; i <= n; i ++){
		while(hash[next])
			next ++;
		x[i] = next;
		hash[x[i]] = true;
		for(int j = 1; j <= i; j ++){
			int tmp = a * x[i] - b * x[j];
			if(tmp > 0)
				hash[tmp] = true;
			tmp = a * x[j] - b * x[i];
			if(tmp > 0)
				hash[tmp] = true;
		}
	}
	for(int i = 1; i <= n; i ++)
		printf("%d ", x[i]);
	printf("\n");
}
int main(){
	int T;
	scanf("%d", &T);
	while(T --)
		solve();
}
