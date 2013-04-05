#include <cstdio>
#include <cstdlib>
#include <algorithm>
#include <iostream>
#include <vector>
#include <cmath>
 
typedef long double ld;
const ld EPS = 1e-8;
const ld SIM_EPS = 1e-8;
const ld INF = 1e100;
using std::vector;
 
struct Vect {
 
    ld x, y;
 
    Vect(ld _x, ld _y) { x = _x, y = _y; }
    Vect() {}
};
 
struct Line {
 
    ld y;
    bool ch;
 
    Line(ld _y, bool _ch) { y = _y, ch = _ch; }
    Line() {}
 
    bool operator<(const Line &b) const {
 
        return y > b.y;
    }
};
 
typedef std::pair<ld, ld> Pair_t;
typedef vector<Vect> VectArr_t;
typedef vector<Pair_t> PairArr_t;
typedef vector<Line> LineArr_t;
 
ld lfabs(ld x) { return x < 0 ? -x : x; }
 
struct Poly {
 
    VectArr_t arr;
    Pair_t bound;
 
    void get_seg(ld x0, PairArr_t *seq) {
 
        if (x0 - bound.first < -EPS || x0 - bound.second > EPS) return;
        static LineArr_t res;
        res.clear();
        Vect o(x0, 0);
        for (VectArr_t::iterator it = arr.begin(); it != arr.end() - 1; it++)
        {
            Vect st = *it, ed = *(it + 1);
            ld dl = x0 - st.x, dr = x0 - ed.x;
            ld dd = dl * dr;
 
            if (dd < EPS)
            {
                ld dx = ed.x - st.x;
                if (lfabs(dx) > EPS) 
                {
                    res.push_back(
                            Line(st.y + (ed.y - st.y) * dl / dx,
                                (lfabs(dd) < EPS ? (dl > EPS || dr > EPS) : 1)
                                )
                            );
                }
            }
        }
        if (res.begin() == res.end()) return;
        std::sort(res.begin(), res.end());
 
        bool t = res.begin() -> ch;
        for (LineArr_t::iterator it = res.begin() + 1; it != res.end(); it++)
        {
            ld prev = (it - 1) -> y, now = it -> y;
            t ^= it -> ch;
            if (!(t & 1)) seq -> push_back(Pair_t(now, prev));
        }
    }
 
};
 
typedef vector<Poly> PolyArr_t;
PolyArr_t polys;
 
ld f(ld x) {
 
    static PairArr_t seq;
 
    seq.clear();
    Pair_t t;
    for (PolyArr_t::iterator it = polys.begin(); it != polys.end(); it++)
        it -> get_seg(x, &seq);
 
    std::sort(seq.begin(), seq.end());
    ld res = 0, inc = 0, r = -INF;
    for (PairArr_t::iterator it = seq.begin(); it != seq.end(); it++)
        if (it -> second > r)
        {
            if (it -> first > r) 
            {
                res += inc;
                inc = it -> second - it -> first;
            }
            else inc += it -> second - r;
 
            r = it -> second;
        }
    return res + inc;
}
 
ld s(ld l, ld r, ld fl, ld fm, ld fr) {
 
    return (r - l) / 6.0 * (fl + 4 * fm + fr);
}
 
ld sim(ld l, ld r, ld fl, ld fm, ld fr) {
 
    ld m = (l + r) / 2;
    ld flm = f((l + m) / 2),
       frm = f((m + r) / 2);
 
    ld al = s(l, r, fl, fm, fr),
       sl = s(l, m, fl, flm, fm),
       sr = s(m, r, fm, frm, fr);
 
    if (lfabs(sl + sr - al) < SIM_EPS) return al;
    return sim(l, m, fl, flm, fm) + sim(m, r, fm, frm, fr);
}
 
ld L = INF, R = -INF;
 
PairArr_t interv;
 
void pre_work() {
 
    int N, n;
    ld x, y, x0, y0;
 
    double alpha = 0 / 180 * M_PI;
    scanf("%d", &N);
    for (int i = 1; i <= N; i++)
    {
        Poly t;
        ld l = INF, r = -INF;
        for (int j = 1; j <= 3; j++)
        {
            scanf("%Lf %Lf", &x0, &y0);
            x = x0 * cos(alpha) + y0 * sin(alpha);
            y = y0 * cos(alpha) - x0 * sin(alpha);
 
            l = std::min(l, x);
            r = std::max(r, x);
            t.arr.push_back(Vect(x, y));
        }
        t.arr.push_back(*t.arr.begin());
        t.bound = Pair_t(l, r);
        polys.push_back(t);
 
        interv.push_back(t.bound);
        L = std::min(L, l);
        R = std::max(R, r);
    }
}
 
void work() {
 
    ld ans = 0;
 
    ld fl = f(L), fm = f((L + R) / 2), fr = f(R);
    ans += sim(L, R, fl, fm, fr);
    printf("%.2Lf\n", ans);
}
 
int main() {
 
    freopen("t.in", "r", stdin);
 
    pre_work();
    work();
 
    return 0;
}
