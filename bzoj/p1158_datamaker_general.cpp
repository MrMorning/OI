#include <cstdio>
#include <cstdlib>
#include <vector>
#define RANGE 100
using namespace std;
int toyNum, compareTimes, seed, weight[1000];
bool appear[1000][2];
int main()
{
	freopen("t.in", "w", stdout);
	scanf("%d%d%d", &toyNum, &compareTimes, &seed);
	srand(seed);
	printf("%d %d\n", toyNum, compareTimes);
	for(int i = 0; i < toyNum; i ++)
	{
		weight[i] = rand() % RANGE + 1;
		printf("%d %d ", weight[i] - rand() % weight[i], weight[i] + rand() % RANGE);
	}
	printf("\n");
	for(int i = 0; i < compareTimes; i ++)
	{
		vector<int> vl, vr;
		int suml = 0, sumr = 0;
		int l = rand() % (toyNum / 3), r = rand() % (toyNum / 3);
		for(int j = 0; j < l; j ++)
		{
			int a = rand() % toyNum;
			while(appear[a][0])
				a = rand() % toyNum;
			appear[a][0] = true;
			vl.push_back(a);
			suml += weight[a];
		}
		for(int j = 0; j < r; j ++)
		{
			int b = rand() % toyNum;
			while(appear[b][0])
				b = rand() % toyNum;
			appear[b][0] = true;
			vr.push_back(b);
			sumr += weight[b];
		}
		printf("%d %d %d ", l, r, suml - sumr);
		for(int i = 0; i < (int)vl.size(); i ++)
			printf(" %d", vl[i] + 1);
		for(int i = 0; i < (int)vr.size(); i ++)
			printf(" %d", vr[i] + 1);
		printf("\n");
	}
	for(int i = 0; i < toyNum; i ++)
		fprintf(stderr, "%d\n", weight[i]);
}
