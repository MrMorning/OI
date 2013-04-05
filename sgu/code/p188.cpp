#include <cstdio>
#include <vector>
#define foreach(it, c) for(__typeof((c).begin()) it = (c).begin(); it != (c).end(); it ++)
using namespace std;

inline int abs(int x)
{
	return x > 0 ? x : -x;
}

struct Segment
{
	double l, r;
	Segment(double _l, double _r):
		l(_l), r(_r){}
};

inline bool cross(const Segment &s1, const Segment &s2)
{
	return s1.r >= s2.l && s1.l <= s2.r;
}

int V[21], pos[21], ans[21];
int N, T;

void getSeg(int i, vector<Segment> &output)
{
	if(V[i] > 0)
	{
		int next = (pos[i] + V[i]) % 1000;
		if(pos[i] < next)
			output.push_back(Segment(pos[i] + 0.1, next));
		else
		{
			if(pos[i] != 999)
				output.push_back(Segment(pos[i] + 0.1, 999));
			output.push_back(Segment(0, next));
		}
	}
	else
	{
		int next = (pos[i] + V[i] + 1000) % 1000;
		if(next < pos[i])
			output.push_back(Segment(next, pos[i] - 0.1));
		else
		{
			if(pos[i] != 0)
				output.push_back(Segment(0, pos[i] - 0.1));
			output.push_back(Segment(next, 999));
		}
	}
}

int main()
{
	freopen("t.in", "r", stdin);
	scanf("%d%d", &N, &T);
	for(int i = 1; i <= N; i ++)
		scanf("%d", &pos[i]);
	for(int i = 1; i <= N; i ++)
		scanf("%d", &V[i]);
	for(int ctime = 1; ctime <= T; ctime ++)
	{
		for(int i = 1; i <= N; i ++)
			for(int j = i + 1; j <= N; j ++)
				if(V[i] / abs(V[i]) != V[j] / abs(V[j]))
				{
					static vector<Segment> vs1, vs2;
					vs1.clear(), vs2.clear();
					getSeg(i, vs1); getSeg(j, vs2);
					bool suc = false;
					foreach(it1, vs1)
						foreach(it2, vs2)
						if(cross(*it1, *it2))
						{
							suc = true;
							break;
						}
					ans[i] += suc, ans[j] += suc;
				}
		for(int i = 1; i <= N; i ++)
			pos[i] = (pos[i] + V[i] + 1000) % 1000;
	}
	for(int i = 1; i <= N; i ++)
		printf("%d ", ans[i]);
}
