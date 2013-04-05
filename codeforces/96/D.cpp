#include <cstdio>
#include <cstring>
#include <algorithm>
using namespace std;

char str[1111111];
int f[1111111][2], g[1111111][2];
int main(){
	//freopen("t.in", "r", stdin);
	scanf("%s", str + 1);
	str[0] = '0';
	int n = strlen(str);
	memset(f, 0x3f, sizeof(f));
	f[n][0] = 0;
	for(int i = n; i >= 1; i --){
		if(f[i][0] + (str[i - 1] == '1') < f[i - 1][0]){
			f[i - 1][0] = f[i][0] + (str[i - 1] == '1');
			g[i - 1][0] = 0;
		}
		if(str[i - 1] == '0' && f[i][1] + 1 < f[i - 1][0]){
			f[i - 1][0] = f[i][1] + 1;
			g[i - 1][0] = 1;
		}
		if(str[i - 1] == '1' && f[i][0] + 1 < f[i - 1][1]){
			f[i - 1][1] = f[i][0] + 1;
			g[i - 1][1] = 0;
		}
		if(str[i - 1] == '0' && f[i][1] + 1 < f[i - 1][1]){
			f[i - 1][1] = f[i][1] + 1;
			g[i - 1][1] = 1;
		}
		if(str[i - 1] == '1' && f[i][1] < f[i - 1][1]){
			f[i - 1][1] = f[i][1];
			g[i - 1][1] = 1;
		}
	}
	printf("%d\n", f[0][0]);
	for(int i = 0, j = 0; i < n; i ++){
		int k = g[i][j];
		if(j == 0 && k == 0){
			if(str[i] == '1')
				printf("+2^%d\n", n - i - 1);
		}
		else if(j == 0 && k == 1){
			printf("+2^%d\n", n - i - 1);
		}
		else if(j == 1 && k == 0){
			printf("-2^%d\n", n - i - 1);
		}
		else{
			if(str[i] == '0')
				printf("-2^%d\n", n - i - 1);
		}
		j = k;
	}
}
