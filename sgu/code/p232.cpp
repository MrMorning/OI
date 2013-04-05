#include <cstdio>
#include <cstring>
#include <algorithm>
using namespace std;

const int N_MAX = 150010;
char input[N_MAX], str[N_MAX], ans[N_MAX], tmp[N_MAX];
bool vis[N_MAX];

int main()
{
	freopen("t.in", "r", stdin);
	int n, step;
	scanf("%d%d", &n, &step);
	step %= n;
	scanf("%s", input);
	for(int i = 0; i < n; i ++)
		if(!vis[i])
		{
			int strCnt = 0;
			for(int j = i; ; j = (j + step) % n)
			{
				if(vis[j])
					break;
				vis[j] = true;
				str[strCnt ++] = input[j];
			}
			int p = 0, q = 1;
			while(q < strCnt && p < strCnt)
			{
				if(p > q)
					swap(p, q);
				int k = 0;
#define M(x) ((x) % strCnt)
				if(p == q)
					q ++;
				if(q >= strCnt)
					break;
				while(k < strCnt && str[M(p + k)] == str[M(q + k)]) 
					k ++;
				if(str[M(p + k)] > str[M(q + k)])
					q = q + k + 1;
				else
					p = p + k + 1;
			}
			p = min(p, q);
			for(int j = 0; j < strCnt; j ++)
				tmp[j] = str[M(j + p)];
			tmp[strCnt] = 0;
			if(strcmp(tmp, ans) > 0)
				memcpy(ans, tmp, sizeof(tmp));
		}
	int cnt = 0, ansCnt = strlen(ans);
	while(cnt < n)
	{
		printf("%s", ans);
		cnt += ansCnt;
	}
	printf("\n");
}
