#include <cstdio>
int f[31][2];
int main(){
	int N;
	scanf("%d", &N);
	long long ans = 0;
	for(int i = 1; i <= N; i ++){
		int x;
		scanf("%d", &x);
		for(int d = 30; d >= 0; d --){
			ans += (1LL << d) * f[d][(x & (1 << d)) == 0];
			f[d][(x & (1 << d)) > 0] ++;
		}
	}
	printf("%lld\n", ans);
}
