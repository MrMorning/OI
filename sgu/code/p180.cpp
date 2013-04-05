#include <cstdio>
#include <cstring>
#include <iostream>
using namespace std;
typedef long long ll;
const int N_MAX = 65547;
int a[N_MAX];
ll ans;
void mergeSort(int l, int r)
{
	if(l == r)
		return;
	int mid = (l + r) >> 1;
	mergeSort(l, mid);
	mergeSort(mid + 1, r);
	for(int i = l, j = mid; i <= mid; i ++)
	{
		while(j + 1 <= r && a[i] > a[j + 1])
			j ++;
		ans += j - mid;
	}
	static int b[N_MAX];
	int i = l, j = mid + 1, nb = 0;
	while(nb < r - l + 1)
	{
		while(i <= mid && (j > r || a[i] < a[j]))
			b[nb ++] = a[i ++];
		while(j <= r && (i > mid || a[i] >= a[j]))
			b[nb ++] = a[j ++];
	}
	memcpy(a + l, b, sizeof(int) * nb);
}
int main()
{
	int n;
	freopen("t.in", "r", stdin);
	scanf("%d", &n);
	for(int i = 0; i < n; i ++)
		scanf("%d", &a[i]);
	ans = 0;
	mergeSort(0, n - 1);
	cout << ans;
}
