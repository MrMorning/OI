#include <cstdio>
#include <cstring>
char str[111];
int rev(int x){
	int res = 0;
	for(int d = 0; d < 8; d ++)
		if(x & (1 << d))
			res |= 1 << (7 - d); 
	return res;
}
int main(){
	//freopen("t.in", "r", stdin);
	char ch;
	int n = 0;
	while(scanf("%c", &ch) != EOF)
		str[n ++] = ch;
	n --;
	for(int i = 0; i < n; i ++){
		int t = (i == 0 ? 0 : rev((int)str[i - 1]));
		int k = (t - rev(str[i]) + 256) % 256;
		printf("%d\n", k);
	}
}
