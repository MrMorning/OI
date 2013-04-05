#include <cstdio>
#define INFINITY 0x3f3f3f3f
#define MAXN 1010
#define MIN(a,b) ((a)<(b)?(a):(b))
struct State
{
	int idx, val;
	State(){};
	State(int _idx, int _val): idx(_idx), val(_val){};
};
class monoQueue_t
{
	private:
		State q[MAXN];
		int qt, qh;
		bool cmp;
	public:
		monoQueue_t()
		{
			qh = qt = 0;
		}
		void setCmp(bool c){cmp = c;};
		void push(State x)
		{
			while(qh < qt && (q[qt - 1].val < x.val) ^ cmp)
				qt --;
			q[qt ++] = x;
		}
		State top()
		{
			return q[qh];
		}
		void pop(int i)
		{
			while(qh < qt && q[qh].idx < i)
				qh ++;
		}
} qArr[MAXN][2];
int sq[MAXN][MAXN];
int main()
{
	freopen("t.in", "r", stdin);
	int a, b, n;
	scanf("%d%d%d", &a, &b, &n);
	for(int i = 1; i <= a; i ++)
		for(int j = 1; j <= b; j ++)
			scanf("%d", &sq[i][j]);
	for(int i = 1; i <= a; i ++)
		qArr[i][0].setCmp(1), qArr[i][1].setCmp(0);
	for(int i = 1; i <= a; i ++)
		for(int j = 1; j < n; j ++)
			qArr[i][0].push(State(j, sq[i][j])), qArr[i][1].push(State(j, sq[i][j]));
	int ans = INFINITY;
	for(int j = n; j <= b; j ++)
	{
		monoQueue_t vmin, vmax;
		vmin.setCmp(1), vmax.setCmp(0);
		for(int i = 1; i <= a; i ++)
		{
			qArr[i][0].pop(j - n + 1), qArr[i][1].pop(j - n + 1);
			qArr[i][0].push(State(j, sq[i][j])), qArr[i][1].push(State(j, sq[i][j]));
		}
		for(int i = 1; i < n; i ++)
			vmin.push(State(i, qArr[i][0].top().val)), vmax.push(State(i, qArr[i][1].top().val));
		for(int i = n; i <= a; i ++)
		{
			vmin.pop(i - n + 1), vmax.pop(i - n + 1);
			vmin.push(State(i, qArr[i][0].top().val)), vmax.push(State(i, qArr[i][1].top().val));
			ans = MIN(ans, vmax.top().val - vmin.top().val);
		}
	}
	printf("%d\n", ans);
}
