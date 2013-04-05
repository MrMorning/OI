#include <cstdio>
#include <cstring>
const int N_MAX = 100010;
const char DIGIT[10][8] = {"1111110", "0110000", "1101101", "1111001", "0110011", "1011011", "1011111", "1110000", "1111111", "1111011"};
int mask[10], weight[10][10];
char str[2 * N_MAX];
int a[N_MAX], b[N_MAX];
int f[N_MAX], g[N_MAX];

int countBits(int x){
	int res = 0;
	while(x)
		res += x & 1, x >>= 1;
	return res;
}
int main(){
	freopen("input.txt", "r", stdin);
	freopen("output.txt", "w", stdout);
	for(int x = 0; x <= 9; x ++)
		for(int j = 0; j < 7; j ++)
			if(DIGIT[x][j] == '1')
				mask[x] |= 1 << j;
	for(int x = 0; x <= 9; x ++)
		for(int y = 0; y <= 9; y ++)
			weight[x][y] = countBits(mask[x] & mask[y]);
	scanf("%s", str);
	int n = strlen(str) / 2;
	for(int i = 0; i < n; i ++)
		a[i + 1] = str[i] - '0';
	for(int i = n; i < 2 * n; i ++)
		b[i + 1 - n] = str[i] - '0';
	for(int i = 1; i <= n; i ++){
		f[i] = f[i - 1] + weight[a[i]][b[i]];
		g[i] = g[i - 1] + weight[a[i]][8];
	}
	for(int i = n; i >= 1; i --)
		for(int j = b[i] + 1; j <= 9; j ++){
			int now = f[i - 1] + weight[j][a[i]] + g[n] - g[i];
			if(now > f[n]){
				b[i] = j;
				for(int k = i + 1; k <= n; k ++){
					b[k] = 8;
					int pre = weight[8][a[k]];
					for(int l = 0; l <= 7; l ++){
						int delta = weight[l][a[k]] - pre;
						if(now + delta > f[n]){
							now += delta;
							b[k] = l;
							break;
						}
					}
				}
				for(int k = 1; k <= n; k ++)
					printf("%d", a[k]);
				for(int k = 1; k <= n; k ++)
					printf("%d", b[k]);
				return 0;
			}
		}
	for(int i = n; i >= 1; i --)
		for(int j = a[i] + 1; j <= 9; j ++){
			int now = g[i - 1] + 7 * (n - i) + weight[8][j];
			if(now > f[n]){
				a[i] = j;
				for(int k = i + 1; k <= n; k ++){
					a[k] = 8;
					int pre = 7;
					for(int l = 0; l <= 7; l ++){
						int delta = weight[l][8] - pre;
						if(now + delta > f[n]){
							now += delta;
							a[k] = l;
							break;
						}
					}
				}
				for(int k = 1; k <= n; k ++){
					b[k] = 8;
					int pre = weight[8][a[k]];
					for(int l = 0; l <= 7; l ++){
						int delta = weight[l][a[k]] - pre;
						if(now + delta > f[n]){
							now += delta;
							b[k] = l;
							break;
						}
					}
				}
				for(int k = 1; k <= n; k ++)
					printf("%d", a[k]);
				for(int k = 1; k <= n; k ++)
					printf("%d", b[k]);
				return 0;
			}
		}
	printf("-1");
}
