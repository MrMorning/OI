#include <cstdio>
#include <cstring>
#include <algorithm>
using namespace std;
int w[18];
int V, f[100001];
int main()
{
	freopen("t.in", "r", stdin);
	for(int i = 1; i <= 17; i ++)
		w[i - 1] = i * i * i * i; 
	scanf("%d", &V);
	memset(f, 0x3f, sizeof(f));
	f[0] = 0;
	for(int i = 0; i < 17; i ++)
		for(int j = w[i]; j <= V; j ++)
			f[j] = min(f[j], f[j - w[i]] + 1);
	printf("%d\n", f[V]);
}
