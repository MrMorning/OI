#include <cstdio>
#include <algorithm>
#ifdef unix
	#define INT64_FMT "%lld"
#else
	#define INT64_FMT "%I64d"
#endif
using namespace std;
typedef long long int64;
typedef pair<int, int64> pair_t;

const int N_MAX = 100010;
const int64 INF = 0x3f3f3f3f3f3f3f3fLL;

struct Segment{
	int l, r;
	int64 w;
	bool operator< (const Segment &t) const{
		return r < t.r;
	}
} seg[N_MAX];

int64 f[N_MAX];
int N, M, E;

void init(){
	scanf("%d%d%d", &N, &M, &E);
	E = E - M + 1;
	for(int i = 1; i <= N; i ++){
		scanf("%d%d" INT64_FMT, &seg[i].l, &seg[i].r, &seg[i].w);
		seg[i].l = seg[i].l - M + 1;
		seg[i].r = seg[i].r - M + 1;
	}
	sort(seg + 1, seg + N + 1);
}

void work(){
	static pair_t stack[N_MAX];
	f[0] = 0;
	int top = 0;
	stack[top ++] = make_pair(0, 0);
	for(int i = 1; i <= N; i ++){
		int lb = -1, rb = top - 1;
		for(int mid = (lb + rb) / 2; lb < rb - 1; mid = (lb + rb) / 2)
			if(stack[mid].first >= seg[i].l - 1)
				rb = mid;
			else
				lb = mid;
		if(stack[rb].first < seg[i].l - 1)
			f[i] = INF;
		else
			f[i] = stack[rb].second + seg[i].w;
		while(top && stack[top - 1].second > f[i])
			top --;
		stack[top ++] = make_pair(seg[i].r, f[i]);
	}
	int64 ans = INF;
	for(int i = 1; i <= N; i ++)
		if(seg[i].r == E)
			ans = min(ans, f[i]);
	if(ans == INF)
		printf("-1\n");
	else
		printf(INT64_FMT "\n", ans);
}

int main(){
	freopen("t.in", "r", stdin);
	init();
	work();
}
