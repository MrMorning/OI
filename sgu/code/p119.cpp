#include <cstdio>
#include <vector>
#include <algorithm>
using namespace std;
typedef pair<int, int> pair_t;
int n, a, b;
vector<pair_t> res;
int main()
{
	scanf("%d%d%d", &n, &a, &b);
	for(int i = 0; i < n; i ++)
		res.push_back(make_pair(a * i % n, b * i % n));
	sort(res.begin(), res.end());
	vector<pair_t>::iterator it = unique(res.begin(), res.end());
	res.resize(it - res.begin());
	printf("%d\n", res.size());
	for(int i = 0; i < (int)res.size(); i ++)
		printf("%d %d\n", res[i].first, res[i].second);
}
