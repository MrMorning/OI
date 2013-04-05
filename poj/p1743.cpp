#include <cstdio>
#include <cstring>
#include <algorithm>
#define MAX(a, b) ((a) > (b) ? (a) : (b))
#define MIN(a, b) ((a) < (b) ? (a) : (b))
using namespace std;
const int N_MAX = 20001;
int rank[N_MAX], sa[N_MAX], height[N_MAX];
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
	int i;
	static int x_backup[N_MAX], y_backup[N_MAX];
	int *x = x_backup, *y = y_backup;
	for(i = 0; i < n; i ++) x[i] = s[i], y[i] = i;
	radix_sort(x, y, n, z);
	for(int len = 1, p; p < n; z = p, len <<= 1)
	{
		for(p = 0, i = n - len; i < n; i ++) y[p ++] = i;
		for(i = 0; i < n; i ++) if(sa[i] >= len) y[p ++] = sa[i] - len;
		radix_sort(x, y, n, z);
		for(swap(x, y), x[sa[0]] = 0, p = 1, i = 1; i < n; i ++)
			x[sa[i]] = is_equal(y, sa[i - 1], sa[i], len) ? p - 1 : p ++;
	}
}
void init_height(int *s, int n)
{
	for(int i = 0; i < n; i ++) rank[sa[i]] = i;
	for(int i = 0, k = 0, j; i < n; height[rank[i ++]] = k)
		if(rank[i]) for(k ? k -- : 0, j = sa[rank[i] - 1]; s[i + k] == s[j + k]; k ++);
}
int str[N_MAX];
bool check(int k, int n)
{
	int max = sa[0], min = sa[0];
	for(int i = 1 ; i < n; i ++)
		if(height[i] < k)
		{
			if(max - min >= k)
				return true;
			max = min = sa[i];
		}
		else
			max = MAX(max, sa[i]), min = MIN(min, sa[i]);
	return max - min >= k;
}
int main()
{
	freopen("t.in", "r", stdin);
	int n;
	while(1)
	{
		scanf("%d", &n);
		if(n == 0)
			break;
		for(int i = 0; i < n; i ++)
			scanf("%d", &str[i]);
		for(int i = 0; i < n - 1; i ++)
			str[i] = 88 + str[i + 1] - str[i];
		str[n - 1] = 0;
		init_SA(str, n, 256);
		init_height(str, n);
		int l = 4, r = n / 2, mid = (l + r) / 2;
		while(l < r)
		{
			if(check(mid, n))
				l = mid;
			else
				r = mid - 1;
			mid = (l + r - 1) / 2 + 1;
		}
		if(check(mid, n))
			printf("%d\n", mid + 1);
		else
			printf("0\n");
	}
}
