#include <cstdio>
#include <cstring>
#include <algorithm>
using namespace std;
int main()
{
	freopen("t.in", "r", stdin);
	int n, m;
	scanf("%d %d", &n, &m);
	for(int i = 0; i < n; i ++)
	{
		int s, f, t;
		int U, D;
		bool F = 0;
		
		scanf("%d %d %d", &s, &f, &t);

		U = s - 1;
		D = m - s;

		int val = U + D + D + U;
		int ans = t / val;
		int ret = ans * val;

		ret += U;

		if(ret < t)
		{
			ret += D + D;
			F = 1;
		}
		if(ret < t)
		{
			ret += U + U;
			F = 0;
		}
		if(F == 0)
		{
			if(s <= f) ret += f - s;
			else ret += D + D + s - f;
		}
		else
		{
			if(s <= f) ret += U + U + f - s;
			else ret += s - f;
		}

		if(s == f) printf("%d\n", t);
		else printf("%d\n", ret);
	}
}
