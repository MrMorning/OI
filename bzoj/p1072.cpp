#include <cstdio>
#include <cstring>
const int N_MAX = 10;
int log[1 << N_MAX];
int f[1 << N_MAX][1000];
int main()
{
	freopen("t.in", "r", stdin);
	for(int i = 0; i < 10; i ++)
		log[1 << i] = i;
	int n_test;
	scanf("%d", &n_test);
	while(n_test --)
	{
		char str[15];
		int d;
		scanf("%s%d", str, &d);
		memset(f, 0, sizeof(f));
		int n = strlen(str);
		int upperlim = 1 << n;
		
		f[0][0] = 1;

		for(int i = 0; i < upperlim; i ++)
			for(int j = 0; j < d; j ++)
				if(f[i][j])
				{
					int tmp = (~ i) & (upperlim - 1);
					static bool hash[10];
					memset(hash, 0, sizeof(hash));
					//find the rightest 1
					while(tmp)
					{
						int pos = ((~ tmp) + 1) & tmp;
						int x = str[log[pos]] - '0';
						tmp -= pos;
						if(hash[x])
							continue;
						hash[x] = true;
						f[i + pos][(j * 10 + x) % d] += f[i][j];
					}
				}
		printf("%d\n", f[upperlim - 1][0]);
	}
}
