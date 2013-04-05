#include <cstdio>
#include <cstring>
#include <algorithm>

namespace Solve
{
	const int MAXN = 200010;
	char str[MAXN];
	int sa[MAXN], ta[MAXN], tb[MAXN], *x = ta, *y = tb;
	int n, upperlim;

	bool cmp(int i, int j, int l);
	void radixSort();
	void calcSuffixArr();
	void solve();
}

bool Solve::cmp(int i, int j, int l)
{
	return y[i] == y[j] && y[i + l] == y[j + l];
}

void Solve::radixSort()
{
	static int w[MAXN];
	memset(w, 0, sizeof(int) * upperlim);
	for(int i = 0; i < n; i ++) w[x[y[i]]] ++;
	for(int i = 1; i < upperlim; i ++) w[i] += w[i - 1];
	for(int i = n - 1; i >= 0; i --) sa[-- w[x[y[i]]]] = y[i];
}

void Solve::calcSuffixArr()
{
	int i, j, p;
	for(int i = 0; i < n; i ++)
		x[i] = str[i], y[i] = i;
	radixSort();
	for(p = j = 1; p < n; upperlim = p, j <<= 1)
	{
		for(p = 0, i = n - j; i < n; i ++) y[p ++] = i;
		for(int i = 0; i < n; i ++)
			if(sa[i] >= j)
				y[p ++] = sa[i] - j;
		radixSort();
		std::swap(x, y);
		for(i = 1, p = 1, x[sa[0]] = 0; i < n; i ++)
			x[sa[i]] = cmp(sa[i - 1], sa[i], j) ? p - 1 : p ++;
	}
}

void Solve::solve()
{
	gets(str); n = strlen(str);
	for(int i = 0; i < n; i ++)
		str[i + n] = str[i];
	n <<= 1; str[n ++] = 0; upperlim = 256;
	calcSuffixArr();
	int tmp = n >> 1;
	for(int i = 0; i < n; i ++)
		if(sa[i] < tmp)
			printf("%c", str[sa[i] + tmp - 1]);
	printf("\n");
}

int main()
{
	freopen("t.in", "r", stdin);
	freopen("t.out", "w", stdout);
	Solve::solve();
}
