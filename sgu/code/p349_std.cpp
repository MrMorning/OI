#include <iostream>
#include <cstdio>
#include <cstring>
#include <algorithm>
using namespace std;

struct sp
{
	int x, y;
	sp() {}
	sp(int a, int b): x(a), y(b) {}
	void read() {scanf("%d%d", &x, &y);}
	void write() {printf("%d %d\n", x, y);}
};

int det(const sp &u, const sp &v)
{return u.x*v.y-v.x*u.y;}

bool operator<(const sp &u, const sp &v)
{return det(u, v)<0;}

bool operator==(const sp &u, const sp &v)
{return det(u, v)==0;}

struct ss
{
	bool type;//0 for wolf, 1 for sheep
	sp l, r;
	ss() {}
	ss(sp u, sp v): l(u), r(v) {}
	void read() {l.read(); r.read(); if (r < l) swap (l, r);}
}s[200020];

bool operator<(const ss &u, const ss &v)
{
	sp p = u.type?u.l:u.r;
	sp q = v.type?v.l:v.r;
	if (det(p, q)==0)
		return u.type>v.type;
	else
		return det(p, q)<0;
}

int N, M;

int main()
{
	freopen("t.in", "r", stdin);
	int i, j, k;
	cin>>N>>M;
	for (i = 0; i < N; ++i)
	{
		s[i].read();
		s[i].type = 0;
	}
	for (i = N; i < N+M; ++i)
	{
		s[i].read();
		s[i].type = 1;
	}
	sort(s, s+N+M);
	sp lsheep=sp(-1, 0), rsheep=sp(-1, 0);
	sp shot=sp(-1, 0);
	int ans = 0;
	bool cross = 1;
	for (i = 0; i < N+M; ++i)
		if (s[i].type)
		{
			if (rsheep < s[i].l) lsheep = s[i].l;
			rsheep = max(s[i].r, rsheep);
		}
		else
		{
			if (shot<s[i].l || !cross&&shot==s[i].l)
			{
				ans++;
				if (rsheep < s[i].r)
				{
					cross = 1;
					shot = s[i].r;
				}
				else if (s[i].l < lsheep)
				{
					cross = 0;
					shot = lsheep;
				}
				else
				{
					puts("No solution");
					return 0;
				}
			}
		}
	cout << ans << endl;
	return 0;
}

