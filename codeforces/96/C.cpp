#include <cstdio>
#include <cstring>
#include <algorithm>
using namespace std;
char str[111];
int fl[111][55][2], fr[111][55][2];
void upd(int &x, int y){
	if(x < y)
		x = y;
}
int main(){
	//freopen("t.in", "r", stdin);
	scanf("%s", str);
	int n = strlen(str), m;
	scanf("%d", &m);
	memset(fl, -0x3f, sizeof(fl));
	memset(fr, -0x3f, sizeof(fr));
	fl[n][0][0] = fl[n][0][1]
		= fr[n][0][0] = fr[n][0][1] = 0;
	for(int i = n - 1; i >= 0; i --)
		for(int j = 0; j <= m; j ++){
			//T
			if(!(j == 0 && str[i] == 'F'))
				for(int d = 0; d < 2; d ++){
					upd(fl[i][j][d], fr[i+1][j - (str[i] != 'T')][d]);
					upd(fr[i][j][d], fl[i+1][j - (str[i] != 'T')][d]);
				}
			//F
			if(!(j == 0 && str[i] == 'T')){
				upd(fl[i][j][0], fl[i+1][j - (str[i] != 'F')][0] + 1);
				upd(fl[i][j][1], fl[i+1][j - (str[i] != 'F')][1] - 1);
				upd(fr[i][j][0], fr[i+1][j - (str[i] != 'F')][0] - 1);
				upd(fr[i][j][1], fr[i+1][j - (str[i] != 'F')][1] + 1);
			}

		}
	int ans = 0;
	for(int j = m & 1; j <= m; j += 2)
		for(int d = 0; d < 2; d ++)
			ans = max(ans, max(fl[0][j][d], fr[0][j][d]));
	printf("%d\n", ans);
}
