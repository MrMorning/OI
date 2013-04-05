#include <cstdio>
#include <cstring>
#include <algorithm>
using namespace std;
const int N_MAX = 150010;
char str[N_MAX];
char s[N_MAX * 2];
int sa[N_MAX * 2], rank[N_MAX * 2];
bool vis[N_MAX];

inline bool isSame(int *x, int i, int j, int l)
{
	return x[i] == x[j] && x[i + l] == x[j + l];
}

void radixSort(int *x, int *y, int z, int n)
{
	static int w[N_MAX * 2];
	memset(w, 0, sizeof(int) * z);
	for(int i = 0; i < n; i ++)
		w[x[y[i]]] ++;
	for(int i = 1; i < z; i ++)
		w[i] += w[i - 1];
	for(int i = n - 1; i >= 0; i --)
		sa[-- w[x[y[i]]]] = y[i];
}

void initSA(char *str, int z, int n)
{
	static int _x[N_MAX * 2], _y[N_MAX * 2];
	int *x = _x, *y = _y;
	for(int i = 0; i < n; i ++)
		x[i] = str[i] - '0', y[i] = i;
	radixSort(x, y, z, n);
	for(int len = 1, p = 0, i; p < n; z = p, len <<= 1)
	{
		for(p = 0, i = n - len; i < n; i ++)
			y[p ++] = i;
		for(i = 0; i < n; i ++)
			if(sa[i] >= len)
				y[p ++] = sa[i] - len;
		radixSort(x, y, z, n);
		for(swap(x, y), x[sa[0]] = 0, i = 1, p = 1; i < n; i ++)
			x[sa[i]] = isSame(y, sa[i], sa[i - 1], len) ? p - 1 : p ++;
	}
	for(int i = 0; i < n; i ++)
		rank[sa[i]] = i;
}

int main()
{
	freopen("t.in", "r", stdin);
	int n, k;
	scanf("%d%d", &n, &k);
	scanf("%s", str);
	for(int i = 0; i < n; i ++)
		s[i] = str[i];
	for(int i = 0; i < n; i ++)
		s[n + i] = s[i];
	s[2 * n] = '9' + 1;
	initSA(s, 11, 2 * n + 1);
	for(int i = 0; ; i = (i + k) % n)
	{
		if(!vis[i])
			vis[i] = true;
		else
			break;
	}
	int ans = -1;
	for(int i = 0; i < n; i ++)
		if(vis[i])
		{
			if(ans == -1 || rank[i] > rank[ans])
				ans = i;
		}
	for(int i = ans; i < ans + n; i ++)
		printf("%c", s[i]);
}
