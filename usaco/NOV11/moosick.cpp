#include <cstdio>
int a[22222], b[11], cnt[100];
int N, M, nAns;
int ans[22222];
int main(){
	freopen("moosick.in", "r", stdin);
	freopen("moosick.out", "w", stdout);
	scanf("%d", &N);
	for(int i = 1; i <= N; i ++)
		scanf("%d", &a[i]);
	scanf("%d", &M);
	for(int i = 1; i <= M; i ++)
		scanf("%d", &b[i]);
	for(int i = 1; i < M; i ++)
		cnt[a[i]] ++;
	for(int i = M; i <= N; i ++){
		cnt[a[i]] ++;
		for(int delta = -87; delta <= 87; delta ++){
			bool fail = false;
			for(int j = 1; j <= M; j ++){
				if(b[j] + delta < 1 || b[j] + delta > 88){
					fail = true;
					break;
				}
				if(cnt[b[j] + delta] == 0){
					fail = true;
					break;
				}
			}
			if(!fail){
				ans[nAns ++] = i - M + 1;
				break;
			}
		}
		cnt[a[i - M + 1]] --;
	}
	printf("%d\n", nAns);
	for(int i = 0; i < nAns; i ++)
		printf("%d\n", ans[i]);
}
