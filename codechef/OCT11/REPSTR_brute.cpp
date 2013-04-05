#include <cstdio>
#include <iostream>
#include <string>
#include <map>
#include <algorithm>
using namespace std;
map<string, int> M;
string str;

int main()
{
	freopen("t.in", "r", stdin);
	while(1)
	{
		M.clear();
		int L, H;
		scanf("%d%d", &L, &H);
		if(L == 0 && H == 0)
			break;
		cin >> str;
		int n = str.length();
		pair<int, int> ans = make_pair(0, 0);
		for(int l = L; l <= H; l ++)
			for(int i = 0; i <= n - l; i ++)
			{
				M[str.substr(i, l)] ++;
				ans = max(ans, make_pair(M[str.substr(i, l)], l));
			}
		printf("%d %d\n", ans.first, ans.second);
	}
}
