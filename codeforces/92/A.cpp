#include <cstdio>
#include <cstring>
#include <algorithm>
using namespace std;
char str[1011], ans[1011];
int prime[1011], primeCnt;
int cnt[27];

void initPrimes(){
	static bool notprime[1001];
	for(int x = 2; x <= 1000; x ++)
		if(!notprime[x]){
			prime[primeCnt ++] = x;
			for(int y = x + x; y <= 1000; y += x)
				notprime[y] = true;
		}
}
int main(){
//	freopen("t.in", "r", stdin);
	initPrimes();
	scanf("%s", str);
	int N = strlen(str);
	for(int i = 0; i < N; i ++)
		cnt[str[i] - 'a'] ++;
	int best = -1;
	for(int i = 0; i < 26; i ++)
		if(best == -1 || cnt[i] > cnt[best])
			best = i;
	for(int i = 1; i <= N; i ++){
		bool divided = false;
		for(int j = 0; 2 * prime[j] <= N && j < primeCnt; j ++)
			if(i % prime[j] == 0){
				divided = true;
				break;
			}
		if(divided){
			ans[i] = best + 'a';
			cnt[best] --;
			if(cnt[best] < 0){
				printf("NO\n");
				return 0;
			}
		}
	}
	printf("YES\n");
	for(int i = 1; i <= N; i ++)
		if(ans[i])
			printf("%c", ans[i]);
		else{
			int j;
			for(j = 0; j < 26; j ++)
				if(cnt[j] > 0){
					printf("%c", j + 'a');
					cnt[j] --;
					break;
				}
		}
}
