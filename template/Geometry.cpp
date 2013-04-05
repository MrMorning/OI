 #include <cstdio>
#include <cmath>
#include <algorithm>
#include <vector>
#include <cassert>
using namespace std;
const double EPS = 1e-5;
const double PI = acos(-1), THETA = 0.1;
inline bool feq(double x, double y) {
    return fabs(x - y) < EPS;
}
struct Point {
    double x, y;
    Point(){}
    Point(double _x, double _y):
        x(_x), y(_y){}
    bool operator< (const Point &t) const {
        return x < t.x || (feq(x, t.x) && y < t.y );
    }
    bool operator== (const Point &t) const {
        return feq(x, t.x) && feq(y, t.y);
    }
    double mod() {
        return sqrt(x * x + y * y);
    }
};
Point operator+ (const Point &p1, const Point &p2) {
    return Point(p1.x + p2.x, p1.y + p2.y);
}
Point operator* (const Point &p1, double k) {
    return Point(p1.x * k, p1.y * k);
}
Point operator- (const Point &p1, const Point &p2) {
    return Point(p1.x - p2.x, p1.y - p2.y);
}
double dot(const Point &p1, const Point &p2) {
    return p1.x * p2.x + p1.y * p2.y;
}
double cross(const Point &p1, const Point &p2) {
    return p1.x * p2.y - p1.y * p2.x;
}
bool is_its(const Point &p1, const Point &p2, double k, double t) {
    Point q1(0, t), q2(1, k + t);
    double t1 = cross(p1 - q2, q1 - q2),
           t2 = cross(q1 - q2, p2 - q2);
    bool b = t1 * t2 >= 0; 
    if ( fabs(t1) < EPS )
        b = true; 
    if ( fabs(t2) < EPS )
        b = true; 
    return b;
}
Point calc_its(const Point &p1, const Point &p2, double k, double t) {
    double k2 = (p2.y - p1.y) / (p2.x - p1.x),
           t2 = p1.y - k2 * p1.x;
    double x = (t2 - t) / (k - k2),
           y = k * x + t;
    return Point(x, y);
}
 
struct Circle {
    double a, b, r;
    Circle(double _a, double _b, double _r):
        a(_a), b(_b), r(_r){}
    vector<Point> get_its(double k, double t) {
        double k2 = k, t2 = a * k - b + t;
        double delta = 4 * k2 * k2 * t2 * t2 - 4 * (k2 * k2 + 1) * (t2 * t2 - r * r);
        vector<Point> res;
        if ( delta < 0 )
            return res;
        double tmp = sqrt(delta);
        double x1 = (tmp - 2 * k2 * t2) / 2 / (k2 * k2 + 1),
               x2 = (-tmp - 2 * k2 * t2) / 2 / (k2 * k2 + 1),
               y1 = x1 * k2 + t2,
               y2 = x2 * k2 + t2;
        res.push_back(Point(x1 + a, y1 + b));
        res.push_back(Point(x2 + a, y2 + b));
        sort(res.begin(), res.end());
        return res;
    }
};
 
struct Poly {
    Point p[33];
    int sz;
    vector<Point> get_its(double k, double t) {
        vector<Point> res;
        for ( int i = 0; i < sz; i ++ ) {
            if ( is_its(p[i], p[i + 1], k, t) ) 
                res.push_back(calc_its(p[i], p[i + 1], k, t));
        }
        sort(res.begin(), res.end());
        res.resize(unique(res.begin(), res.end()) - res.begin());
        assert(!((int)res.size() & 1));
        return res;
    }
} land[22];
int n_land;
double ans;
 
bool check(Point p1, Point p2, double rad) {
    if ( p1.x > p2.x )
        swap(p1, p2);
    pair<double, int> arr[10000];
    double k = (p2.y - p1.y) / (p2.x - p1.x),
           b = p1.y - k * p1.x;
    int n_arr = 0;
    for ( int i = 0; i < n_land; i ++ )
        for ( int j = 0; j < land[i].sz; j ++ ) {
            Circle tc = Circle(land[i].p[j].x, land[i].p[j].y, rad);
            vector<Point> vp = tc.get_its(k, b);
            if ( vp.size() ) {
                arr[n_arr ++] = make_pair(vp[0].x, 1);
                arr[n_arr ++] = make_pair(vp[1].x, -1);
            }
        }
 
    for ( int i = 0; i < n_land; i ++ ) {
        vector<Point> vp = land[i].get_its(k, b);
        for ( int i = 0; i < (int)vp.size(); i ++ ) 
            arr[n_arr ++] = make_pair(vp[i].x, (i & 1) ? - 1 : 1);
    }
 
    for ( int i = 0; i < n_land; i ++ ) 
        for ( int j = 0; j < land[i].sz; j ++ ) {
            Point pp1 = land[i].p[j], pp2 = land[i].p[j + 1];
            double ppa = pp2.y - pp1.y,
                   ppb = pp1.x - pp2.x;
            Point ppv(ppa, ppb);
            ppv = ppv * (1 / ppv.mod());
            static Poly land_tmp;
            land_tmp.sz = 4;
            land_tmp.p[0] = (ppv * rad) + pp1;
            land_tmp.p[1] = (ppv * rad) + pp2;
            land_tmp.p[2] = (ppv * (-rad)) + pp2;
            land_tmp.p[3] = (ppv * (-rad)) + pp1;
            land_tmp.p[4] = land_tmp.p[0];
 
            vector<Point> vp = land_tmp.get_its(k, b);
            for ( int i = 0; i < (int)vp.size(); i ++ ) 
                arr[n_arr ++] = make_pair(vp[i].x, (i & 1) ? - 1 : 1);
        }
    sort(arr, arr + n_arr);
    arr[n_arr ++] = make_pair(p1.x, 0);
    arr[n_arr ++] = make_pair(p2.x, 0);
    sort(arr, arr + n_arr);
    for ( int i = 0,
            start = lower_bound(arr, arr + n_arr, make_pair(p1.x, 0)) - arr,
            lim = lower_bound(arr, arr + n_arr, make_pair(p2.x, 0)) - arr, cnt = 0; i <= lim; i ++ ) {
        cnt += arr[i].second;
        if ( i >= start && cnt == 0 )
            return true;
    }   
    return false;
}
 
void process(Point p1, Point p2) {
    double lb = ans, rb = 1e5;
    for ( double mid = (lb + rb) / 2; lb < rb - 1e-4; mid = (lb + rb) / 2 ) {
        if ( check(p1, p2, mid) )
            lb = mid;
        else
            rb = mid;
    }
    ans = lb;
}
void rotate(Point &p) {
    Point vx = Point(cos(THETA), sin(THETA)),
          vy = Point(cos(-(PI / 2 - THETA)), sin(-(PI / 2 - THETA)));
    p = Point(dot(vx, p), dot(vy, p));
}
int n_turn;
Point turn[22];
int main() {
    scanf("%d%d", &n_land, &n_turn);
    for ( int i = 0; i < n_turn; i ++ ) {
        scanf("%lf%lf", &turn[i].x, &turn[i].y);
        rotate(turn[i]);
    }
    for ( int i = 0; i < n_land; i ++ ) {
        scanf("%d", &land[i].sz);
        for ( int j = 0; j < land[i].sz; j ++ )
            scanf("%lf%lf", &land[i].p[j].x, &land[i].p[j].y);
        land[i].p[land[i].sz] = land[i].p[0];
        for ( int j = 0; j <= land[i].sz; j ++ )
            rotate(land[i].p[j]);
    }
    ans = 0.0;
    for ( int i = 1; i < n_turn; i ++ )
        process(turn[i - 1], turn[i]); 
    printf("%.2lf\n", ans);
}
