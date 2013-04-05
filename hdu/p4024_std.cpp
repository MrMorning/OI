#include <iostream>
#include <cstdio>
#include <cstring>
#include <cmath>
using namespace std;
const double eps = 1e-6;
const double inf = 1e9;
int comp(double x)
{
    if(fabs(x) < eps)
        return 0;
    else if(x < -eps)
        return -1;
    else
        return 1;
}
struct point
{
    double x,y;
    point(){}
    point(double a,double b):x(a),y(b){}
    point operator - (const point p)
    {
        return point(x - p.x,y - p.y);
    }
    point operator *(const double a)
    {
        return point(x * a,y * a);
    }
    point operator +(const point p)
    {
        return point(x + p.x,y + p.y);
    }
    double norm()
    {
        return sqrt(x * x + y * y);
    }
}p1,p2,L;
double vd,vb,limit;
int main()
{
	freopen("t.in", "r", stdin);
    while(scanf("%lf %lf %lf %lf %lf %lf %lf %lf %lf",&p1.x,&p1.y,&p2.x,&p2.y,&L.x,&L.y,&vd,&vb,&limit) == 9)
    {
        if(!comp(p1.x) && !comp(p1.y) && !comp(p2.x) && !comp(p2.y) && !comp(L.x) && !comp(L.y) && !comp(vd) && !comp(vb) && !comp(limit))
            break;
        double t2 = limit / vb;
        double l = 0.0,r = inf,mid;
        while(comp(l - r) < 0)
        {
            mid = (l + r) / 2.0;
            point now = p1 + L * mid;
            if(comp(t2 - mid) > 0)
            {
                l = mid;
                continue;
            }
            double d = (now - p2).norm();
            double most = (mid - t2) * vd;
            if(comp(d - limit) <= 0)
            {
                if(comp(d + most - limit) < 0)
                    l = mid;
                else
                    r = mid;
            }
            else
            {
                if(comp(most + limit - d) < 0)
                    l = mid;
                else
                    r = mid;
            }
        }
        printf("%.3lf %.3lf\n",limit,mid);
    }
}
