#include <cstdio>
#include <cstring>
#include <iostream>

#define MAXN 250000
#define MAX_VAL 250000

using std::cin;
using std::cout;

int tree[MAXN + 1];
int a[MAXN + 1], ans[MAXN + 1];
int n, testNum;
int BIT_MASK;
bool exist[MAXN + 1];

inline int lowbit(int i)
{return i & (- i);}

void Add(int i, int val)
{
	while(i <= n)
	{
		tree[i] += val;
		i += lowbit(i);
	}
}

int Sum(int i)
{
	int cnt = 0;
	while(i > 0)
	{
		cnt += tree[i];
		i -= lowbit(i);
	}
	return cnt;
}

int Find(int cumVal)
{
	int bitMask = BIT_MASK, idx = 0;
	while(bitMask != 0 && idx < n)
	{
		int tIdx = idx + bitMask;
		if(cumVal == tree[tIdx])
			return tIdx;
		else if(cumVal > tree[tIdx])
		{
			idx = tIdx;
			cumVal -= tree[tIdx];
		}
		bitMask >>= 1;
	}
	if(cumVal != 0)
		return -1;
	else 
		return idx;
}

int main()
{
	freopen("t.in", "r", stdin);
	std::ios::sync_with_stdio(false);
	cin >> testNum;
	while(testNum --)
	{
		memset(tree, 0x3f, sizeof(tree));
		memset(exist, 1, sizeof(exist));
		cin >> n;
		for(int i = 1; i <= n; i ++)
			tree[i] = 0;
		BIT_MASK = 1 << 17;
		while(BIT_MASK > n) BIT_MASK >>= 1;
		for(int i = 1; i <= n; i ++)
			cin >> a[i], Add(i, 1);
		int cnt = n;
		for(int i = n; i >= 1; i --)
		{
			int tmp = Find(cnt - a[i]);
			//int pre = Sum(tmp), next;
			//while(pre == (next = Sum(tmp - 1)))
		    //	tmp -= 1, pre = next;
			while(!exist[tmp]) tmp --;
			ans[i] = tmp;
			Add(ans[i], -1);
			exist[ans[i]] = false;
			cnt --;
		}
		for(int i = 1; i <= n - 1; i ++)
			cout << ans[i] << ' ';
		cout << ans[n] << '\n';
	}
}
