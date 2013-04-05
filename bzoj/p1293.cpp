#include <cstdio>
#include <algorithm>

#define MIN(a, b) ((a) < (b) ? (a) : (b))

const int N_BEAD_MAX = 1000000;
const int N_COLOR_MAX = 60;
const int INFINITY = 1 << 31 - 1;

struct Bead
{
	int x, c;
	Bead(int _x = -1, int _c = -1):
		x(_x), c(_c){}
	bool operator< (const Bead &t) const
	{
		return x < t.x;
	}
};

Bead bead[N_BEAD_MAX];
int hash[N_COLOR_MAX];
int n_bead, n_color;
int ans = INFINITY;

int main()
{
	freopen("t.in", "r", stdin);
	freopen("t.out", "w", stdout);
	scanf("%d%d", &n_bead, &n_color);
	n_bead = 0;
	for(int i = 0; i < n_color; i ++)
	{
		int c, t;
		scanf("%d", &c);
		while(c --)
		{
			scanf("%d", &t);
			bead[n_bead ++] = Bead(t, i);
		}
	}		
	std::sort(bead, bead + n_bead);
	for(int i = 0, j = -1, cnt = 0; i < n_bead; i ++)
	{
		bool over = false;
		while(1)
		{
			if(cnt == n_color)
				break;
			j ++;
			if(j == n_bead)
			{
				over = true;
				break;
			}
			if(hash[bead[j].c] == 0)
				cnt ++;
			hash[bead[j].c] ++;
		}
		if(over)
			break;
		//printf("[%d, %d]\n", bead[i].x, bead[j].x);
		ans = MIN(ans, bead[j].x - bead[i].x);
		hash[bead[i].c] --;
		if(hash[bead[i].c] == 0)
			cnt --;
	}
	printf("%d\n", ans);
}
