#include <cstdio>
#include <cstdlib>
#include <algorithm>

const int UPPERLIM = 1 << 15;
using namespace std;
const char MAP[5] = {'U', 'D', 'S', 'I', 'C'};
int main()
{
	int n, seed;
	freopen("t.in", "w", stdout);
	scanf("%d%d", &n, &seed);
	srand(seed);
	for(int i = 1; i <= n; i ++)
	{
		int l = rand() % UPPERLIM;
		int r = rand() % UPPERLIM;
		if(l > r) swap(l ,r);
		int k = rand()%5;
		printf("%c [%d,%d]\n", MAP[k], i, i);
	}

}
