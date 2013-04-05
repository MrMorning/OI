#include <cstdio>
#include <algorithm>
#include <cmath>
using namespace std;
int n;
struct Stuff
{
	int idx;
	double val;
	bool operator<(const Stuff &t) const
	{
		return val < t.val;
	}
} a[6000], b[6000];
int main()
{
	freopen("t.in", "r", stdin);
	scanf("%d", &n);
	for(int i = 0; i < n; i ++)
	{
		scanf("%lf", &a[i].val);
		a[i].idx = i;
	}
	sort(a, a + n);
	if(n % 2 == 0)
		for(int i = 0; i < n; i += 2)
		{
			b[i] = a[i / 2];
			b[i + 1] = a[n - i / 2 - 1];
		}
	else
	{
		for(int i = 0; i < n - 1; i += 2)
		{
			b[i] = a[i / 2];
			b[i + 1] = a[n - i / 2 - 1];
		}
		b[n - 1] = a[n / 2];
	}
	printf("yes\n");
	for(int i = 0; i < n; i ++)
		printf("%d ", b[i].idx + 1);
}
