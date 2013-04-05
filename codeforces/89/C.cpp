#include <cstdio>
#include <string>
#include <algorithm>
using namespace std;
struct State
{
	int a, b;
	State(){}
	State(int _a, int _b):
		a(_a), b(_b){}
	bool operator< (const State &t) const
	{
		if(a <= 0 && t.a <= 0)
		{
			if(b != t.b)
			{
				if(b < t.b)
					return false;
				else
					return true;
			}
			if(a < t.a)
				return true;
			else
				return false;
		}
		else if(a <= 0 && t.a >= 0)
			return true;
		else if(a >= 0 && t.a <= 0)
			return false;
		else
		{
			if(b != t.b)
			{
				if(b < t.b)
					return true;
				else
					return false;
			}
			if(a < t.a)
				return true;
			else
				return false;
		}
	}
};
int N, K;
char str[10010];
pair<int, State> tmp[10010];

int main()
{
	//freopen("t.in", "r", stdin);
	scanf("%d%d", &N, &K);
	scanf("%s", str);
	pair<int, string> res = make_pair(0x3f3f3f3f, "");
	for(int targ = 0; targ < 10; targ ++)
	{
		for(int i = 0; i < N; i ++)
			tmp[i].first = abs(str[i] - '0' - targ), tmp[i].second = State((targ - (int)(str[i] - '0')), N - i - 1);
		sort(tmp, tmp + N);
		string ts(str);
		int acc = 0;
		for(int i = 0; i < K; i ++)
			acc += tmp[i].first, ts[N - tmp[i].second.b - 1] = (char)(targ + '0');
		res = min(res, make_pair(acc, ts));
	}
	printf("%d\n%s\n", res.first, res.second.c_str());
}
