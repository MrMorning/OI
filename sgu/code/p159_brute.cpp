#include <cstdio>
#include <cstring>
#include <algorithm>
using namespace std;

const int D_MAX = 2000;
const int K_MAX = 2000;
int base;
struct BigInt
{
	int num[D_MAX], len;
	BigInt()
	{
		memset(num, 0, sizeof(num));
		len = 0;
	}
	void output()
	{
		for(int i = len - 1; i >= 0; i --)
			printf("%c", (num[i] > 9 ? 'A' + num[i] - 10 : '0' + num[i]));
	}
};
typedef pair<BigInt, int> pair_t;

BigInt sqr(const BigInt &a)
{
	BigInt res;
	for(int i = 0; i < a.len; i ++)
		for(int j = 0; i + j < a.len; j ++)
			res.num[i + j] += a.num[i] * a.num[j];
	for(int i = 0; i < D_MAX; i ++)
	{
		if(i != D_MAX - 1)
			res.num[i + 1] += res.num[i] / base;
		res.num[i] %= base;
	}
	for(int i = D_MAX - 1; i >= 0; i --)
		if(res.num[i])
		{
			res.len = i + 1;
			break;
		}
	return res;
}

BigInt ans[K_MAX];
pair_t queue[K_MAX];
int ansCnt;
int main()
{
	freopen("t.in", "r", stdin);
	int n;
	scanf("%d%d", &base, &n);
	int qh = 0, qt = 0;
	queue[qt ++] = make_pair(BigInt(), 0);
	while(qh != qt)
	{
		const pair_t &u = queue[qh];
		qh = (qh + 1) % K_MAX;
		if(u.second == n)
		{
			if(u.first.num[u.second - 1] != 0)
				ans[ansCnt ++] = u.first;
			continue;
		}
		for(int d = 0; d < base; d ++)
		{
			BigInt v = u.first;
			v.len = u.second + 1;
			v.num[v.len - 1] = d;
			BigInt r = sqr(v);
			bool flag = false;
			for(int i = 0; i < u.second + 1; i ++)
				if(r.num[i] != v.num[i])
				{
					flag = true;
					break;
				}
			if(!flag)
			{
				queue[qt] = make_pair(v, u.second + 1);
				qt = (qt + 1) % K_MAX;
			}
		}
	}

	printf("%d\n", (n == 1) + ansCnt);
	for(int i = 0; i < ansCnt; i ++)
	{
		ans[i].output();
		printf("\n");
	}
	if(n == 1)
		printf("0");
}
