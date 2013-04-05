#include <cstdio>
#include <cstring>
#include <algorithm>
using namespace std;
const int N_MAX = 100010;
const int oo = 0x3f3f3f3f;

int sa[N_MAX], rank[N_MAX], height[N_MAX];
char str[N_MAX];
int a[N_MAX];

void radixSort(int *x, int *y, int n, int z)
{
	static int w[N_MAX];
	memset(w, 0, sizeof(int) * z);
	for(int i = 0; i < n; i ++)
		w[x[y[i]]] ++;
	for(int i = 1; i < z; i ++)
		w[i] += w[i - 1];
	for(int i = n - 1; i >= 0; i --)
		sa[-- w[x[y[i]]]] = y[i];
}

inline bool isEqual(int *x, int i, int j, int l)
{
	return x[i] == x[j] && x[i + l] == x[j + l];
}

void initSA(int *s, int n, int z)
{
	static int _x[N_MAX], _y[N_MAX];
	int *x = _x, *y = _y;
	for(int i = 0; i < n; i ++)
		x[i] = s[i], y[i] = i;
	radixSort(x, y, n, z);
	for(int p = 0, len = 1; p < n; z = p, len <<= 1)
	{
		p = 0;
		for(int i = n - len; i < n; i ++)
			y[p ++] = i;
		for(int i = 0; i < n; i ++)
			if(sa[i] >= len)
				y[p ++] = sa[i] - len;
		radixSort(x, y, n, z);
		int i;
		for(swap(x, y), x[sa[0]] = 0, i = 1, p = 1; i < n; i ++)
			x[sa[i]] = isEqual(y, sa[i], sa[i - 1], len) ? p - 1: p ++;
	}
}

void initHeight(int *s, int n)
{
	for(int i = 0; i < n; i ++)
		rank[sa[i]] = i;
	for(int i = 0, k = 0; i < n; height[rank[i ++]] = k)
		if(rank[i])
			for(k ? k -- : 0; s[i + k] == s[sa[rank[i] - 1] + k]; k ++);
}

int main()
{
	freopen("t.in", "r", stdin);
	while(1)
	{
		int L, H;
		scanf("%d%d", &L, &H);
		if(L == 0 && H == 0)
			break;
		scanf("%s", str);
		int n = strlen(str);
		for(int i = 0; i < n; i ++)
			a[i] = str[i] - 'a' + 1;
		a[n ++] = 0;
		initSA(a, n, 256);
		initHeight(a, n);

		int curMin = oo, cnt = 0;
		pair<int, int> ans = make_pair(1, min(H, n - 1));
		for(int i = 1; i < n; i ++)
		{
			cnt ++;
			curMin = min(curMin, height[i]);
			if(curMin > H)
				continue;
			if(curMin < L)
			{
				cnt = 0;
				curMin = oo;
			}
			if(cnt)
				ans = max(ans, make_pair(cnt + 1, curMin));
		}
		printf("%d %d\n", ans.first, ans.second);
	}
}
