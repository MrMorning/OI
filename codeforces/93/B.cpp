#include <cstdio>
#include <cstring>
#include <cstdlib>

char str[1000010];
int f[1000010];

void noSol(){
	printf("Just a legend\n");
	exit(0);
}
int main(){
//	freopen("t.in", "r", stdin);
	scanf("%s", str + 1);
	int n = strlen(str + 1);
	f[0] = f[1] = 0;
	for(int i = 2; i <= n; i ++){
		int t = f[i - 1];
		while(t && str[t + 1] != str[i])
			t = f[t];
		if(str[t + 1] == str[i])
			t ++;
		f[i] = t;
	}
	if(f[n] == 0)
		noSol();
	for(int i = f[n] + 1; i < n; i ++)
		if(f[i] == f[n]){
			for(int k = 1; k <= f[n]; k ++)
				printf("%c", str[k]);
			return 0;
		}
	if(f[f[n]] == 0)
		noSol();
	for(int k = 1; k <= f[f[n]]; k ++)
		printf("%c", str[k]);
}
