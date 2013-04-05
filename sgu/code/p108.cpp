#include <cstdio>
#include <cstring>
#include <algorithm>
using namespace std;

const int BLK_SIZE = 100;
const int K_MAX = 5000;

struct Query
{
	int idx, org, res;
} q[K_MAX];
bool a[2][BLK_SIZE];
int nn, nq, selfCnt;

bool cmp1(const Query &q1, const Query &q2)
{
	return q1.idx < q2.idx;
}

bool cmp2(const Query &q1, const Query &q2)
{
	return q1.org < q2.org;
}

int gen(int x)
{
	int res = x;
	while(x)
		res += x % 10, x /= 10;
	return res;
}

int main()
{
	freopen("t.in", "r", stdin);
	scanf("%d%d", &nn, &nq);
	for(int i = 0; i < nq; i ++)
	{
		scanf("%d", &q[i].idx);
		q[i].org = i;
	}
	sort(q, q + nq, cmp1);
	int cur = 0, qi = 0;
	for(int i = 1; i <= nn; i ++)
	{
		if(i % BLK_SIZE == 0)
		{
			memset(a[cur], 0, sizeof(a[cur]));
			cur ^= 1;
		}
#define POS(x) (x - x / BLK_SIZE * BLK_SIZE)
		if(!a[cur][POS(i)])
		{
			selfCnt ++;
			while(selfCnt == q[qi].idx)
				q[qi ++].res = i;
		}
		int next = gen(i);
		if(POS(next) > POS(i))
			a[cur][POS(next)] = true;
		else
			a[!cur][POS(next)] = true;
	}
	sort(q, q + nq, cmp2);
	printf("%d\n", selfCnt);
	for(int i = 0; i < nq; i ++)
		printf("%d ", q[i].res);
}

