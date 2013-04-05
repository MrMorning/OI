#include <cstdio>
#include <cstring>
#include <vector>
using namespace std;
typedef pair<int, int> into_t;
const int oo = 0x3f3f3f3f;

namespace tri
{
	int pow[10];
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
		for(int i = 1; i < 10; i ++)
			pow[i] = 3 * pow[i - 1];
	}
}

int f[2][6561];
int board[70][7];
vector<into_t> into[2][3][3];
char str[10];

inline void update(int &x, int y)
{
	x = min(x, y);
}

int main()
{
	freopen("t.in", "r", stdin);

	int n, m;
	tri::init();
#define ADD(a, b, c, d, e) into[a][b][c].push_back(make_pair(d, e))
	ADD(0, 0, 0, 2, 1);
	ADD(0, 0, 0, 1, 2);
	ADD(0, 1, 0, 2, 1);
	ADD(0, 1, 0, 1, 2);
	ADD(0, 0, 1, 2, 1);
	ADD(0, 0, 1, 1, 2);
	ADD(0, 1, 1, 2, 1);
	ADD(0, 1, 1, 1, 2);
	ADD(0, 1, 1, 0, 0);

	ADD(0, 2, 0, 1, 1);
	ADD(0, 0, 2, 1, 1);
	ADD(0, 2, 1, 1, 1);
	ADD(0, 1, 2, 1, 1);
	
	ADD(1, 0, 0, 1, 1);
	ADD(1, 1, 0, 1, 1);
	ADD(1, 0, 1, 1, 1);
	ADD(1, 1, 1, 1, 1);

	scanf("%d%d", &n, &m);
	for(int i = 0; i < n; i ++)
	{
		scanf("%s", str);
		for(int j = 0; j < m; j ++)
			board[i][j] = str[j] == '*';
	}

	int upperlim = tri::pow[m + 1];
	int initS = 0;
	for(int i = 0; i < m + 1; i ++)
		initS = tri::set(initS, i, 1);
	int now = 0;
	memset(f, 0x3f, sizeof(f));
	f[now][initS] = 0;

	for(int i = 0; i < n; i ++, now ^= 1)
	{
		for(int j = 0; j < m; j ++, now ^= 1)
		{
			memset(f[!now], 0x3f, sizeof(f[!now]));
			for(int s = 0; s < upperlim; s ++)
				if(f[now][s] < oo)
				{
					int t = board[i][j];
					int a = tri::get(s, j),
						b = tri::get(s, j + 1);
					for(int k = 0; k < (int)into[t][a][b].size(); k ++)
					{
						int c = into[t][a][b][k].first,
							d = into[t][a][b][k].second;
						int ns1 = tri::set(s, j, c),
							ns2 = tri::set(ns1, j + 1, d);
						update(f[!now][ns2], f[now][s] + (c == 2 || d == 2));
					}
				}
		}

		memset(f[!now], 0x3f, sizeof(f[!now]));
		for(int s = 0; s < upperlim; s ++)
			if(tri::get(s, m) != 2)
				update(f[!now][s * 3 % upperlim + 1], f[now][s]);
	}

	int ans = oo;
	for(int s = 0; s < upperlim; s ++)
		if(tri::get(s, 0) == 1)
		{
			bool fail = false;
			for(int i = 1; i <= m; i ++)
				if(tri::get(s, i) == 2)
				{
					fail = true;
					break;
				}
			if(!fail)
				update(ans, f[now][s]);
		}
	printf("%d\n", ans);
}
