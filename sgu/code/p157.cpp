#include <cstdio>
#include <cstring>
#include <algorithm>
using namespace std;
int idx[13], cur[13], perm[13], pos[14];
int n;
bool check()
{
	for(int i = 0; i < n; i ++)
		cur[i] = idx[perm[i]];
	for(int i = 0; i < n; i ++)
		pos[cur[i]] = i;
	while(1)
	{
		int t;
		if(pos[0] == 0)
			t = 13 - n + 1;
		else
			t = cur[pos[0] - 1];
		if(t == 13)
		{
			for(int i = 0; i < n - 2; i ++)
				if(cur[i] > cur[i + 1])
					return false;
			return true;
		}
		int k = pos[t + 1], bl = pos[0];
		pos[0] = k, pos[t + 1] = bl;
		swap(cur[k], cur[bl]);
	}
}

int main()
{
//	freopen("t.in", "r", stdin);
	scanf("%d", &n);
	for(int i = 13 - n + 2; i <= 13; i ++)
		idx[i - (13 - n + 2)] = i;
	idx[n - 1] = 0;
	for(int i = 0; i < n; i ++)
		perm[i] = i;
	int res = 0;
	do
		res += check();
	while(next_permutation(perm, perm + n));
	printf("%d\n", res);
}
