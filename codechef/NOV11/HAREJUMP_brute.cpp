#include <cstring>
#include <cstdio>
int L[15];
int f[1000000];
long long N;
void work(){
	int K;
	scanf("%lld", &N);
	scanf("%d", &K);
	for(int i = 0; i < K; i ++)
		scanf("%d", &L[i]);
	memset(f, 0, sizeof(f));
	f[0] = 1;
	for(int i = 1; i <= N; i ++)
		for(int j = 0; j < K; j ++)
			if(i >= L[j])
				f[i] = (f[i] + f[i - L[j]]) % 1000000007;
	printf("%d\n", f[N]);
}

int main(){
	freopen("t.in", "r", stdin);
	int T;
	scanf("%d", &T);
	while(T --)
		work();
}
