#include <cstdio>
#include <cstdlib>
#include <cstring>
#include <cctype>
int n, m;
char str[1000000];
int c[1000000], r[1000000];
void noSol()
{
	printf("0\n");
	exit(0);
}
int main()
{
//	freopen("t.in", "r", stdin);
	memset(c, -1, sizeof(c));
	memset(r, -1, sizeof(r));
	scanf("%d%d", &n, &m);
	for(int i = 0; i < n; i ++)
	{
		scanf("%s", str);
		for(int j = 0; j < m; j ++)
		{
			if(isdigit(str[j]))
			{
				int v, h, t = str[j] - '0';
				if(t == 1 || t == 4)
					v = 1;
				else
					v = 0;

				if(t == 1 || t == 2)
					h = 1;
				else
					h = 0;
				if(r[i] == -1)
					r[i] = h ^ (j & 1);
				else if(r[i] != (h ^ (j & 1)))
					noSol();

				if(c[j] == -1)
					c[j] = v ^ (i & 1);
				else if(c[j] != (v ^ (i & 1)))
					noSol();
			}
		}
	}
	int cnt = 0;
	for(int i = 0; i < n; i ++)
		if(r[i] == -1)
			cnt ++;
	for(int i = 0; i < m; i ++)
		if(c[i] == -1)
			cnt ++;
	int res = 1;
	for(int i = 0; i < cnt; i ++)
		res = (res << 1) % 1000003;
	printf("%d\n", res);
}
