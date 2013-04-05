#include <cstdio>
#include <cmath>
#include <cassert>
#include <vector>
#include <algorithm>
#define foreach(it, c) for(__typeof((c).begin()) it = (c).begin(); it != (c).end(); it ++)
#define SQR(x) ((x)*(x))
using namespace std;
typedef double val_t;
const val_t INF = 10E100;
const val_t EPS = 10E-6;
 
struct Point
{
    val_t x, y;
    Point(val_t _x = 0, val_t _y = 0):
        x(_x), y(_y){}
};
 
struct Interval
{
    val_t l, r;
    Interval(val_t _l = 0, val_t _r = 0):
        l(_l), r(_r){}
    bool operator< (const Interval &t) const
    {return l < t.l || (l == t.l && r < t.r);}
};
 
struct Polygon
{
    vector<Point> vp;
    void get_itv(vector<Interval> &output, val_t x0)
    {
        static vector<val_t> backup;
        backup.clear();
        int np = (int)vp.size();
        for(int i = 0; i < np; i ++)
        {
            Point cur = vp[i], next = vp[(i + 1) % np];
            if(cur.x > next.x)
                swap(cur, next);
            if(cur.x <= x0 && x0 < next.x)
                backup.push_back((next.y - cur.y) * (x0 - cur.x) / (next.x - cur.x) + cur.y);
        }
        sort(backup.begin(), backup.end());
        for(int i = 1; i < (int)backup.size(); i += 2)
            output.push_back(Interval(backup[i - 1], backup[i]));
    }
};
 
struct Circle
{
    val_t r;
    Point core;
    void get_itv(vector<Interval> &output, val_t x0)
    {
        if(fabs(x0 - core.x) >= r)
            return;
        val_t d = core.x - x0;
        val_t l = sqrt(r * r - d * d);
        output.push_back(Interval(core.y - l, core.y + l));
    }
};
 
vector<Polygon> poly;
vector<Circle> circ;
 
val_t calc_f(val_t x0)
{
    static vector<Interval> vi;
    vi.clear();
 
    foreach(c, circ)
        c->get_itv(vi, x0);
    foreach(it, poly)
        it->get_itv(vi, x0);
 
    sort(vi.begin(), vi.end());
    val_t focus = -INF, res = 0, acc = 0;
    foreach(itv, vi)
    {
        if(itv->l <= focus)
        {
            if(itv->r > focus)
                acc += itv->r - focus, focus = itv->r;
        }
        else
            res += acc, acc = itv->r - itv->l, focus = itv->r;
    }
    return res + acc;
}
 
val_t self_adjust(val_t l, val_t r, val_t lval, val_t mval, val_t rval)
{
    val_t now = (r - l) * (lval + 4 * mval + rval) / 6, mid = (l + r) / 2;
    val_t tmp1 = calc_f((l + mid) / 2), tmp2 = calc_f((mid + r) / 2);
    if(fabs(now - (mid - l) * (lval + 4 * tmp1 + mval) / 6 
                - (r - mid) * (mval + 4 * tmp2 + rval) / 6) < EPS)
        return now;
    else
        return self_adjust(l, mid, lval, tmp1, mval) + self_adjust(mid, r, mval, tmp2, rval);
}
 
int n;
val_t alpha, h[510], r[510], sum;
int main()
{
    scanf("%d%lf", &n, &alpha);
    for(int i = 0; i <= n; i ++)
        scanf("%lf", &h[i]);
    for(int i = 0; i < n; i ++)
        scanf("%lf", &r[i]);
    r[n] = 0;
    val_t k = tan(alpha);
    val_t lb = INF, rb = -INF;
    for(int i = 0; i <= n; i ++)
    {
        sum += h[i];
        static Circle c;
        c.core.x = 0, c.core.y = sum / k, c.r = r[i];
        circ.push_back(c);
        lb = min(lb, -r[i]);
        rb = max(rb, r[i]);
    }
    for(int i = 0; i < n; i ++)
    {
        if(max(circ[i].r, circ[i + 1].r) - min(circ[i].r, circ[i + 1].r) >= circ[i + 1].core.y - circ[i].core.y)
            continue;
        val_t u = (circ[i].r - circ[i + 1].r) / (circ[i + 1].core.y - circ[i].core.y);
        val_t y1 = circ[i].r * u + circ[i].core.y,
              y2 = circ[i + 1].r * u + circ[i + 1].core.y;
        val_t x1 = sqrt(SQR(circ[i].r) - SQR(y1 - circ[i].core.y)),
              x2 = sqrt(SQR(circ[i + 1].r) - SQR(y2 - circ[i + 1].core.y));
        assert(y2 > y1);
        static Polygon t;
        t.vp.clear();
        t.vp.push_back(Point(x2, y2));
        t.vp.push_back(Point(x1, y1));
        t.vp.push_back(Point(-x1, y1));
        t.vp.push_back(Point(-x2, y2));
        poly.push_back(t);
    }
    printf("%.2lf\n", self_adjust(lb, rb, calc_f(lb), calc_f((lb + rb) / 2), calc_f(rb)));
}
