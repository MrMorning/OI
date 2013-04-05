#include <cstdio>
#include <algorithm>
using namespace std;
int P, M, C, K, R, V;
int main()
{
	freopen("t.in", "r", stdin);
	scanf("%d%d%d%d%d%d", &P, &M, &C, &K, &R, &V);
	printf("%d\n", min(P / K, min(M / R, C / V)));
}
