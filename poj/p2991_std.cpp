#include <cstdio>
#include <cmath>
#define PI acos(-1.0)
#define eps 1e-8
#define L(x) (x << 1)
#define R(x) ((x << 1) | 1)
#define maxn 10001

int N, Q;
int len[maxn], sum[maxn];
double mySin[720], myCos[720];

struct Point
{
    double x, y;

    Point operator +(const Point & a)const
    {
        Point ret;
        ret.x = x + a.x;
        ret.y = y + a.y;
        return ret;
    }

    Point operator -(const Point & a)const
    {
        Point ret;
        ret.x = x - a.x;
        ret.y = y - a.y;
        return ret;
    }
};

struct Segtree
{
    int l, r, deg;
    Point s, e;
    bool mark;

    int mid()
    {
        return (l + r) >> 1;
    }

    void Rotate(int angle)
    {
        double dx = e.x - s.x, dy = e.y - s.y;
        double newx = dx * myCos[angle + 360] - dy * mySin[angle + 360];
        double newy = dx * mySin[angle + 360] + dy * myCos[angle + 360];
        e.x = s.x + newx;
        e.y = s.y + newy;
    }
} tree[maxn * 4];

void Build(int rt, int l, int r)
{
    tree[rt].l = l, tree[rt].r = r;
    tree[rt].deg = 0;
    tree[rt].mark = 0;
    tree[rt].s.x = tree[rt].e.x = 0;
    tree[rt].s.y = sum[l] - len[l];
    tree[rt].e.y = sum[r];
    if (l != r)
    {
        Build(L(rt), l, tree[rt].mid());
        Build(R(rt), tree[rt].mid() + 1, r);
    }
}

void Update(int rt)
{
    int l = L(rt), r = R(rt);
    //提出向量根据新节点进行旋转
    tree[l].deg += tree[rt].deg;
    tree[l].deg %= 360;
    tree[l].e = tree[l].e - tree[l].s + tree[rt].s;
    tree[l].s = tree[rt].s;
    tree[l].Rotate(tree[rt].deg);

    tree[r].e = tree[r].e - tree[r].s + tree[l].e;
    tree[r].s = tree[l].e;
    tree[r].deg += tree[rt].deg;
    tree[r].deg %= 360;

    tree[r].Rotate(tree[rt].deg);

    tree[l].mark = tree[r].mark = 1;
    tree[rt].mark = 0;
    tree[rt].deg = 0;
}

int Query(int rt, int order)
{
    if (tree[rt].l == tree[rt].r) return tree[rt].deg;
    //只用叶节点记录真实的角度
    if (tree[rt].mark) Update(rt);
    int LL = L(rt), RR = R(rt);
    if (order <= tree[LL].r) return Query(LL, order);
    else return Query(RR, order);
}

void Change(int rt, int l, int angle)
{
    if (tree[rt].l != tree[rt].r && tree[rt].mark) Update(rt);
    if (tree[rt].l == l)
    {
        tree[rt].deg += angle;
        tree[rt].deg %= 360;
        tree[rt].Rotate(angle);
        tree[rt].mark = 1;
        return;
    }
    int LL = L(rt), RR = R(rt);
    int mid = (tree[rt].l + tree[rt].r) >> 1;
    if (l <= mid)
    {
        Change(LL, l, angle);
        tree[RR].e = tree[RR].e + tree[LL].e - tree[RR].s;
        tree[RR].s = tree[LL].e;
        Change(RR, mid + 1, angle);
    }
    else Change(RR, l, angle);
    tree[rt].e = tree[RR].e;
}

int main()
{
	freopen("t.in", "r", stdin);
	freopen("t.out", "w", stdout);
    int cases = 0;
    for (int i = -360; i <= 360; ++i)
    {
        mySin[i + 360] = sin(i * PI / 180);
        myCos[i + 360] = cos(i * PI / 180);
    }
    while (~scanf("%d%d", &N, &Q))
    {
        if (cases++) puts("");
        sum[0] = 0;
        for (int i = 1; i <= N; ++i)
        {
            scanf("%d", len + i);
            sum[i] = sum[i - 1] + len[i];
        }
        Build(1, 1, N);

        for (int i = 1; i <= Q; ++i)
        {
            int a, b;
            scanf("%d%d", &a, &b);
            b = ((Query(1, a) - Query(1, a + 1) + 180 + b) % 360 + 360) % 360;
            Change(1, a + 1, b);
            printf("%.2lf %.2lf\n", tree[1].e.x + eps, tree[1].e.y + eps);
        }
    }
    return 0;
}
