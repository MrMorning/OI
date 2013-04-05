#include <cstdio>
#include <cstdlib>
#include <algorithm>
using namespace std;
pair<int, int> P[100010];
int a[100010];
int randval()
{
	return rand() % 100000000 + 1;
}
int n, m, seed;
int main()
{
	freopen("t.in", "w", stdout);
	scanf("%d%d%d", &n, &m, &seed);
	srand(seed);
	printf("%d\n", n);
	for(int i = 1; i < n; i ++)
	{
		int p = rand() % i;
		P[i] = make_pair(p, i);
	}
	for(int i = 0; i < n; i ++)
		a[i] = i;
	for(int i = 0; i < n; i ++)
		swap(a[rand() % n], a[rand() % n]);
	for(int i = 1; i < n; i ++)
		printf("%d %d %d\n", a[P[i].first] + 1, a[P[i].second] + 1, randval());
	while(m --)
	{
		int t = rand() % 4;
		if(t == 0)
			printf("Change %d %d\n", rand() % (n - 1) + 1, randval());
		else if(t == 1)
			printf("Cover %d %d %d\n", rand() % n + 1, rand() % n + 1, randval());
		else if(t == 2)
			printf("Add %d %d %d\n", rand() % n + 1, rand() % n + 1, randval());
		else
			printf("Max %d %d\n", rand() % n + 1, rand() % n + 1);
	}
	printf("Stop\n");
}
