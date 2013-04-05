#include <cstdio>
#include <cstdlib>
#include <cmath>
#include <set>
#include <algorithm>

using namespace std ;

const double eps = 1e-10;

struct node
{
    long long x, y;
    double angle;
    
    node(long long a, long long b)
    {
        x = a;
        y = b;
    }
    node()
    {}
    
    inline double dist()
    {
        return sqrt(x * x + y * y);
    }
    
    inline friend bool operator == (node a, node b)
    {
        return a.x == b.x && a.y == b.y && fabs(a.angle - b.angle) < eps;
    }
    
    inline friend node operator - (node a, node b)
    {
        return node(a.x - b.x, a.y - b.y);
    }
    
    inline friend long long operator * (node a, node b)
    {
        return a.x * b.y - b.x * a.y;
    }
    
    inline friend bool operator < (node a, node b)
    {
        return a.angle - eps > b.angle;
    }
    void read()
    {
        scanf("%lld%lld", &x, &y);
    }
};

node origin;
int N;
set<node> hull;
long long area;

node lower(node x)
{
    set<node> :: iterator it = hull.lower_bound(x);
    if(it == hull.end())
        return *hull.begin();
    return *it;
}

node next(node x)
{
    set<node> :: iterator it = hull.upper_bound(x);
    if(it == hull.end())
        return *hull.begin();
    return *it;
}
node prev(node x)
{
    set<node> :: iterator it = hull.lower_bound(x);
    if(it == hull.begin())
        return *(-- hull.end());
    return *(-- it);
}

void handle(node x)
{
    x = x - origin;
    x.angle = atan2(x.y, x.x);
    
    node d1 = prev(x), d2 = lower(x);

    if((d2 - d1) * (x - d1) < 0)
        return ;
    
    area -= abs(d1 * d2);
    area += abs(x * d1) + abs(x * d2);
    
    if(fabs(d2.angle - x.angle) < eps)
    {
        area -= abs(next(x) * d2);
        area += abs(next(x) * x);
        hull.erase(d2);
    }
    hull.insert(x);
    
    node p1, p2, p3;
    
    p1 = *hull.find(x);
    for(;hull.size() > 2;)
    {
        p2 = next(p1);
        p3 = next(p2);
        if((p2 - p1) * (p3 - p1) < 0)
            break;
        area -= abs(p1 * p2) + abs(p2 * p3);
        area += abs(p1 * p3);
        hull.erase(p2);
    }
    
    for(;hull.size() > 2;)
    {
        p2 = prev(p1);
        p3 = prev(p2);
        if((p2 - p1) * (p3 - p1) > 0)
            break;
        area -= abs(p1 * p2) + abs(p2 * p3);
        area += abs(p1 * p3);
        hull.erase(p2);
    }
}

void init()
{
    freopen("t.in", "r", stdin);
    
    node tri[3];
    for(int i(0); i < 3; ++ i)
        tri[i].read();
    origin = node((tri[0].x + tri[1].x + tri[2].x) / 3, (tri[0].y + tri[1].y + tri[2].y) / 3);
    for(int i(0); i < 3; ++ i)
    {
        tri[i] = tri[i] - origin;
        tri[i].angle = atan2(tri[i].y, tri[i].x);
        hull.insert(tri[i]);
    }
    area = abs((tri[1] - tri[0]) * (tri[2] - tri[0]));
    
    scanf("%d", &N);
    for(int i(1); i <= N; ++ i)
    {
        node tmp;
        tmp.read();
        handle(tmp);
        printf("%lld\n", area);
    }
}

int main()
{
    init();
    return 0 ;
}
