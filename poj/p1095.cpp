#include <cstdio>
typedef long long ll;
const int N_CATALAN_MAX = 20;
ll catalan[N_CATALAN_MAX + 1];
void init_catalan()
{
	catalan[0] = 1;
	for(int i = 1; i <= N_CATALAN_MAX; i ++)
		for(int j = 0; j < i; j ++)
			catalan[i] += catalan[j] * catalan[i - 1 - j];
}
void solve(int n, int rank)
{
	if(n == 1)
	{
		printf("X");
		return;
	}
	ll cnt = 0, i;
	for(i = 0; cnt < rank; i ++)
		cnt += catalan[i] * catalan[n - 1 - i];
	i --;
	rank -= cnt - catalan[i] * catalan[n - 1 - i];
	if(i > 0)
	{
		printf("(");
		solve(i, (rank - 1) / catalan[n - 1 - i] + 1);
		printf(")");
	}
	printf("X");
	if(n - i - 1 > 0)
	{
		printf("(");
		solve(n - i - 1, (rank - 1) % catalan[n - 1 - i] + 1);
		printf(")");
	}
}
int main()
{
	freopen("t.in", "r", stdin);
	init_catalan();
	while(1)
	{
		int rank;
		scanf("%d", &rank);
		if(rank == 0) break;
		int cnt = 0, j;
		for(int i = 0; i <= N_CATALAN_MAX && rank > cnt - 1; i ++)
			cnt += catalan[i], j = i;
		rank -= cnt - catalan[j];
		solve(j, rank + 1);
		printf("\n");
	}
}
