#include <cstdio>
#include <iostream>
#define MAXN 500010

using std::cout;

int A[MAXN], tmp[MAXN];
long long ans = 0;
int n;

void Merge(int l, int mid, int r)
{
	int p1 = l, p2 = mid + 1;
	int cnt = 0;
	while(p1 <= mid && p2 <= r)
	{
		ans += p2 - mid - 1;
		while(A[p1] > A[p2] && p2 <= r) 
		{
			tmp[++ cnt] = A[p2];
			p2 ++, ans ++;
		}
		tmp[++ cnt] = A[p1];
		p1 ++;
	}
	while(p1 <= mid) 
	{
		tmp[++ cnt] = A[p1];
		ans += r-mid;
		p1 ++;
	}
	
	while(p2 <= r) 
		tmp[++ cnt] = A[p2 ++];
	for(int i = 1; i <= cnt; i ++) A[l + i - 1] = tmp[i];
}

void Divide(int l, int r)
{
	if(l == r) return;
	int mid = (l + r) >> 1;
	Divide(l, mid);
	Divide(mid + 1, r);
	Merge(l, mid, r);
}

int main()
{
	freopen("t.in", "r", stdin);
	std::ios::sync_with_stdio(false);
	while(1)
	{
		scanf("%d\n", &n);
		if(n == 0) break;
		for(int i = 1; i <= n; i ++) scanf("%d\n", &A[i]);
		ans = 0;
		Divide(1, n);
		cout << ans << '\n';
	}
}
