#include <cstdio>
#include <cstdlib>
#include <cstring>
#include <algorithm>
#define MAX_COL_NUM 100010
#define ASSERT(b) if(!(b)) exit(1)

class set_t
{
	int p[8];
	public:
	set_t(){for(int i = 0; i < 8; i ++) p[i] = i;};
	int find(int u){return p[u] != u ? p[u] = find(p[u]) : p[u];};
	void comb(int u, int v){if(find(u) != find(v)) p[find(u)] = find(v);};
};
struct node_t
{
	int l, r;
	bool f[4][4], e;
	node_t(bool _e = true): e(_e){memset(f, 0, sizeof(f));};
} node[MAX_COL_NUM << 2];
bool link_h[MAX_COL_NUM][2];
bool link_v[MAX_COL_NUM];

node_t operator+ (const node_t &lch, const node_t &rch)
{
	if(! lch.e) return rch;
	else if(! rch.e) return lch;
#define LV(i) (i)
#define RV(i) ((i)+4)
	static set_t S;
	S = set_t();
	node_t x; x.l = lch.l, x.r = rch.r;
	for(int i = 0; i < 4; i ++){
		if(i == 3 ? lch.f[0][3] : lch.f[i][i+1]) S.comb(LV(i), LV((i+1)%4));
		if(i == 3 ? rch.f[0][3] : rch.f[i][i+1]) S.comb(RV(i), RV((i+1)%4));
	}
	if(lch.f[0][2]) S.comb(LV(0), LV(2));
	if(lch.f[1][3]) S.comb(LV(1), LV(3));
	if(rch.f[0][2]) S.comb(RV(0), RV(2));
	if(rch.f[1][3]) S.comb(RV(1), RV(3));
	if(link_h[rch.l][0]) S.comb(LV(3), RV(0));
	if(link_h[rch.l][1]) S.comb(LV(2), RV(1));
	for(int i = 0; i <= 1; i ++)
		for(int j = 2; j <= 3; j ++)
			if(S.find(LV(i)) == S.find(RV(j))) x.f[i][j] = 1;
	if(S.find(LV(0)) == S.find(LV(1))) x.f[0][1] = 1;
	if(S.find(RV(2)) == S.find(RV(3))) x.f[2][3] = 1;
	return x;
#undef LV
#undef RV
}

void build(int i, int l, int r)
{
	node_t &x = node[i];
	x.l = l, x.r = r;
	if(l == r)
		x.f[1][2] = x.f[0][3] = true;
	else{
		build(i * 2, l, (l + r) / 2), build(i * 2 + 1, (l + r) / 2 + 1, r);
		x = node[i * 2] + node[i * 2 + 1];
	}
}

void change(int i, int pos, int val)
{
	node_t &x = node[i];
	if(x.l > pos || x.r < pos) return;
	if(x.l == pos && x.r == pos){
		if(val == -1) return;
		x.f[0][1] = x.f[2][3] = val;
		return;
	}
	change(i * 2, pos, val), change(i * 2 + 1, pos, val);
	x = node[i * 2] + node[i * 2 + 1];
}

node_t ask(int i, int l, int r)
{
	node_t &x = node[i];
	if(x.l > r || x.r < l) return node_t(false);
	if(l <= x.l && x.r <= r) return x;
	return ask(i * 2, l, r) + ask(i * 2 + 1, l, r);
}

char oprt[50];
int main()
{
	freopen("t.in", "r", stdin);
	int nC, r1, c1, r2, c2;
	scanf("%d", &nC);
	build(1, 1, nC);
	while(1){
		scanf("%s", oprt);
		if(oprt[0] == 'E') break;
		scanf("%d%d%d%d", &r1, &c1, &r2, &c2);
		if(c1 > c2) std::swap(c1, c2), std::swap(r1, r2);
		if(oprt[0] == 'O' || oprt[0] == 'C')
		{
			bool tmp = oprt[0] == 'O';
			if(r1 != r2)
			{
				if(link_v[c1] != tmp)
					change(1, c1, tmp), link_v[c1] = tmp;
			}
			else{
				if(link_h[c2][r1 - 1] == tmp) continue;
				link_h[c2][r1 - 1] = tmp;
				change(1, c2, -1);
			}
		}
		else{
			node_t mid = ask(1, c1, c2), l = ask(1, 1, c1), r = ask(1, c2, nC);
			set_t S;
			if(l.f[2][3]) S.comb(0, 1);
			if(r.f[0][1]) S.comb(2, 3);
			for(int i = 0; i <= 3; i ++)
				for(int j = i + 1; j <= 3; j ++)
					if(mid.f[i][j]) S.comb(i, j);
			if(S.find(r1 - 1) == S.find(4 - r2)) printf("Y\n");
			else printf("N\n");
		}
	}
}
