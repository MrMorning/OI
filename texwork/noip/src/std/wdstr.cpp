#include <cstdio>
#include <cstring>
#include <algorithm>
using namespace std;
const int WD_LEN = 8;
const char WDPAL[2][2 * WD_LEN] = {"zcwwzdjnjdzwwcz", "njdzwwczcwwzdjn"};
const int N_MAX = 2010;
char str[N_MAX], now[N_MAX], ansStr[N_MAX];
int ans;

void solve(){
	scanf("%s", str);
	int n = strlen(str);
	if(n < 15){
		printf("-1\n");
		return;
	}
	ans = 0x3f3f3f3f;
	for(int ct = 0; ct < 2; ct ++){
		for(int i = 0; i + WD_LEN - 1 < (n + 1) / 2; i ++){
			strcpy(now, str);
			int res = 0;
			for(int k = i; k < i + WD_LEN; k ++){
				if(now[k] != WDPAL[ct][k - i])
					now[k] = WDPAL[ct][k - i], res ++;
				if(now[n - k - 1] != WDPAL[ct][k - i])
					now[n - k - 1] = WDPAL[ct][k - i], res ++;
			}
			for(int k = 0; k <= n / 2; k ++)
				if(now[k] != now[n - k - 1])
					now[k] = now[n - k - 1] = min(now[k], now[n - k - 1]), res ++;
			if(res < ans || (res == ans && strcmp(now, ansStr) < 0))
				ans = res, strcpy(ansStr, now);
		}
	}
	printf("%d %s\n", ans, ansStr);
}

int main(){
	freopen("wdstr.in", "r", stdin);
	freopen("wdstr.out", "w", stdout);
	int _;
	scanf("%d", &_);
	while(_ --)
		solve();
}
