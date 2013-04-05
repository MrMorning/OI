#include <cstdio>
#include <cstring>
#include <algorithm>
#include <set>
#include <map>

const int N_MAX = 20010;

int str[N_MAX], sa[N_MAX], rank[N_MAX], height[N_MAX];

void radix_sort(int *x, int *y, int n, int z)
{
	static int w[N_MAX];
	memset(w, 0, sizeof(int) * z);
	for(int i = 0; i < n; i ++) w[x[y[i]]] ++;
	for(int i = 1; i < z; i ++) w[i] += w[i - 1];
	for(int i = n - 1; i >= 0; i --) sa[-- w[x[y[i]]]] = y[i];
}
inline bool is_equal(int *x, int i, int j, int l)
{return x[i] == x[j] && x[i + l] == x[j + l];}
void init_SA(int *s, int n, int z)
{
	static int _x[N_MAX], _y[N_MAX];
	int i, *x = _x, *y = _y;
	for(int i = 0; i < n; i ++)
		x[i] = s[i], y[i] = i;
	radix_sort(x, y, n, z);
	for(int len = 1, p; p != n; z = p, len <<= 1)
	{
		for(p = 0, i = n - len; i < n; i ++) y[p ++] = i;
		for(i = 0; i < n; i ++) if(sa[i] >= len) y[p ++] = sa[i] - len;
		radix_sort(x, y, n, z);
		for(std::swap(x, y), x[sa[0]] = 0, p = 1, i = 1; i < n; i ++)
			x[sa[i]] = is_equal(y, sa[i - 1], sa[i], len) ? p - 1: p ++;
	}
}
void init_height(int *s, int n)
{
	for(int i = 0; i < n; i ++) rank[sa[i]] = i;
	for(int i = 0, k = 0, j; i < n; height[rank[i ++]] = k)
		if(rank[i])
			for(k ? k -- : 0, j = sa[rank[i] - 1]; s[i + k] == s[j + k]; k ++);
}
void discrete(int n)
{
	using namespace std;
	set<int> S;
	map<int, int> M;
	int idx = 0;

	for(int i = 0; i < n; i ++)
		S.insert(str[i]);
	for(set<int>::iterator it = S.begin(); it != S.end(); it ++)
		M[* it] = idx ++;
	for(int i = 0 ;i < n; i ++)
		str[i] = M[str[i]];
}
bool check(int len, int k, int n)
{
	for(int i = 1; i < n; i ++)
	{
		int j = i;
		while(height[i] >= len)
			i ++;
		if(i - j + 1 >= k)
			return true;
	}
	return false;
}
int main()
{
	freopen("patterns.in", "r", stdin);
	freopen("patterns.out", "w", stdout);
	int n, k;
	scanf("%d%d", &n, &k);
	for(int i = 0; i < n; i ++)
		scanf("%d", &str[i]);
	str[n ++] = -1;
	discrete(n);
	init_SA(str, n, n);
	init_height(str, n);
	int l = 1, r = n, mid = (l + r) >> 1;
	while(l < r - 1)
	{
		if(check(mid, k, n))
			l = mid;
		else
			r = mid;
		mid = (l + r) >> 1;
	}
	printf("%d\n", l);
}
