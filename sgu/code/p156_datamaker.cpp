#include <cstdio>
#include <cstdlib>
#include <vector>
using namespace std;
int n, m, seed;
vector<int> whole[100];
vector<pair<int, int> > output;
int main()
{
	freopen("t.in", "w", stdout);
	scanf("%d%d%d", &n, &m, &seed);
	srand(seed);
	int idx = 0;
	for(int i = 0; i < m; i ++)
	{
		int u = rand() % n, v = rand() % n;
		if(u == v)
			continue;
		int a = idx ++, b = idx ++, c = idx ++;
		whole[u].push_back(a), whole[v].push_back(c);
		output.push_back(make_pair(a, b));
		output.push_back(make_pair(b, c));
	}
	for(int i = 0; i < n; i ++)
		if((int)whole[i].size() == 1)
		{
			int a = idx ++, b = idx ++, c = idx ++;
			int v = (i + 1) % n;
			whole[i].push_back(a), whole[v].push_back(c);
			output.push_back(make_pair(a, b));
			output.push_back(make_pair(b, c));
		}

	for(int i = 0; i < n; i ++)
		for(int j = 0; j < (int)whole[i].size(); j ++)
			for(int k = j + 1; k < (int)whole[i].size(); k ++)
				output.push_back(make_pair(whole[i][j], whole[i][k]));
	printf("%d %d\n", idx, output.size());
	for(int i = 0; i < (int)output.size(); i ++)
		printf("%d %d\n", output[i].first + 1, output[i].second + 1);
}
