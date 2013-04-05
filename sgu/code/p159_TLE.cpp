#include <cstdio>
#include <cstring>
#include <algorithm>
#include <cassert>
using namespace std;

const int D_MAX = 4000;
const int K_MAX = 1000;
int base;
struct BigInt
{
	int num[D_MAX], len;
	BigInt()
	{
		memset(num, 0, sizeof(num));
		len = 0;
	}

	void shl(int k)
	{
		assert(len + k <= D_MAX);
		for(int i = len - 1 + k; i >= k; i --)
			num[i] = num[i - k];
		for(int i = k - 1; i >= 0; i --)
			num[i] = 0;
		len += k;
	}

	void adjust()
	{
		for(int i = 0; i < D_MAX; i ++)
		{
			if(i < D_MAX - 1)
				num[i + 1] += num[i] / base;
			num[i] %= base;
		}
		for(int i = D_MAX - 1; i >= 0; i --)
			if(num[i])
			{
				len = i + 1;
				return;
			}
		len = 0;
	}

	void output()
	{
		for(int i = len - 1; i >= 0; i --)
			printf("%c", (num[i] > 9 ? 'A' + num[i] - 10 : '0' + num[i]));
	}
};

struct State
{
	BigInt val, sqr;
	int step;
	State(const BigInt &_val, const BigInt &_sqr, int _step):
		val(_val), sqr(_sqr), step(_step){}
	State(){}
};

BigInt plus(const BigInt &a, const BigInt &b)
{
	BigInt res;
	res.len = max(a.len, b.len);
	for(int i = 0; i < res.len; i ++)
		res.num[i] += a.num[i] + b.num[i];
	res.adjust();
	return res;
}

BigInt mul(const BigInt &x, int k)
{
	BigInt res = x;
	for(int i = 0; i < res.len; i ++)
		res.num[i] *= k;
	res.adjust();
	return res;
}

BigInt ans[K_MAX];
State queue[K_MAX];
int ansCnt;
int main()
{
	freopen("t.in", "r", stdin);
	int n;
	scanf("%d%d", &base, &n);
	int qh = 0, qt = 0;
	queue[qt ++] = State(BigInt(), BigInt(), 0);
	while(qh != qt)
	{
		const State &u = queue[qh];
		qh = (qh + 1) % K_MAX;
		if(u.step == n)
		{
			if(u.val.num[u.step - 1] != 0)
				ans[ansCnt ++] = u.val;
			continue;
		}

		for(int d = 0; d < base; d ++)
		{
			BigInt v = u.val;
			v.len = u.step + 1;
			v.num[v.len - 1] = d;
			v.adjust();
			BigInt r = u.sqr;
			r.num[2 * u.step] += d * d;
			r.adjust();
			BigInt t = u.val;
			t = mul(t, 2 * d);
			t.shl(u.step);
			r = plus(r, t);
			r.adjust();

			bool flag = false;
			for(int i = 0; i < u.step + 1; i ++)
				if(r.num[i] != v.num[i])
				{
					flag = true;
					break;
				}
			if(!flag)
			{
				queue[qt] = State(v, r, u.step + 1);
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
