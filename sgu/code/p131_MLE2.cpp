#include <cstdio>
#include <cstring>
#include <vector>
using namespace std;

typedef pair<int, int> trans_t;
typedef long long ll;
#ifdef unix
#define LL_T_FMT "%lld"
#else
#define LL_T_FMT "%I64d"
#endif

namespace tri
{
	int pow[11];
	int get(int x, int k)
	{
		return x / pow[k] % 3;
	}
	int set(int x, int k, int y)
	{
		int t = x % pow[k];
		x /= pow[k + 1];
		x = (x * 3 + y) * pow[k] + t;
		return x;
	}
	void init()
	{
		pow[0] = 1;
		for(int i = 1; i < 11; i ++)
			pow[i] = 3 * pow[i - 1];
	}
}

vector<trans_t> into[3][3];
ll f[10][59049];

int main()
{
	freopen("t.in", "r", stdin);

	tri::init();

#define ADD(i, j, x, y) into[i][j].push_back(make_pair(x, y))
	ADD(0, 0, 1, 0);
	ADD(0, 0, 0, 1);
	ADD(0, 0, 1, 1);
	ADD(0, 0, 2, 0);
	ADD(0, 0, 0, 2);
	ADD(1, 0, 0, 0);
	ADD(0, 1, 0, 0);
	ADD(2, 0, 1, 0);
	ADD(0, 2, 0, 1);
	ADD(2, 2, 0, 0);

	int n, m;
	scanf("%d%d", &n, &m);
	f[0][0] = 1;
	for(int i = 1, upperlim = tri::pow[m + 1]; i <= n; i ++)
	{
		for(int j = 0; j < m; j ++)
			for(int s = 0; s < upperlim; s ++)
				if(f[j][s])
				{
					int a = tri::get(s, j),
						b = tri::get(s, j + 1);
					for(int k = 0; k < (int)into[a][b].size(); k ++)
					{
						int c = into[a][b][k].first,
							d = into[a][b][k].second;
						int ns1 = tri::set(s, j, c),
							ns2 = tri::set(ns1, j + 1, d);
						f[j + 1][ns2] += f[j][s];
					}
				}
		memset(f[0], 0, sizeof(f[0]));
		for(int s = 0; s < upperlim; s ++)
			if(tri::get(s, m) == 0)
				f[0][(s * 3) % upperlim] += f[m][s];
		for(int j = 1; j <= m; j ++)
			memset(f[j], 0, sizeof(f[j]));
	}
	printf(LL_T_FMT "\n", f[0][0]);
}
