#include <cstdio>
#include <cstring>
#include <algorithm>
using namespace std;

char str[1111111];
int f[1111111][2];
int main(){
	freopen("t.in", "r", stdin);
	scanf("%s", str + 1);
	str[0] = '0';
	int n = strlen(str);
	memset(f, 0x3f, sizeof(f));
	f[n][0] = 0;
	for(int i = n; i >= 1; i --){
		if(f[i][0] + (str[i - 1] == '1') < f[i - 1][0]){
			f[i - 1][0] = f[i][0] + (str[i - 1] == '1');
		}
		if(str[i - 1] == '0' && f[i][1] + 1 < f[i - 1][0]){
			f[i - 1][0] = f[i][1] + 1;
		}
		if(str[i - 1] == '1' && f[i][0] + 1 < f[i - 1][1]){
			f[i - 1][1] = f[i][0] + 1;
		}
		if(str[i - 1] == '0' && f[i][1] + 1 < f[i - 1][1]){
			f[i - 1][1] = f[i][1] + 1;
		}
		if(str[i - 1] == '1' && f[i][1] < f[i - 1][1]){
			f[i - 1][1] = f[i][1];
		}
	}
	int ans = f[0][0];
	printf("%d\n", ans);
}
