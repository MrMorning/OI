#include<stdio.h>
#include<string.h>
#include<cmath>
#include<vector>
#include<algorithm>
#define eps 1e-4
#define inf 1e100
#define N 20
#define pi acos(-1.0)
#define G 9.18
using namespace std;
int Sig(double a)
{
    return a<-eps?-1:a>eps;
}
struct Point
{
    double x,y;
    Point(){}
    Point(double x0,double y0):x(x0),y(y0){}
    void in()
    {
        scanf("%lf%lf",&x,&y);
    }
    void out()
    {
        printf("%.3f %.3f\n",x,y);
    }
    Point operator * (double t)
    {
        return Point(t*x,t*y);
    }
    double len()
    {
        return sqrt(x*x+y*y);
    }
    double operator *(Point pt)
    {
        return x*pt.y-y*pt.x;
    }
    double operator ^(Point pt)
    {
        return pt.x*x+pt.y*y;
    }
    Point operator -(Point pt)
    {
        return Point(x-pt.x,y-pt.y);
    }
    Point operator +(Point pt)
    {
        return Point(x+pt.x,y+pt.y);
    }
};
struct Polygon
{
    Point p[20];
    int n;
    double h;
    int id;
    double k;
    void in()
    {
        scanf("%lf",&h);
        scanf("%d",&n);
        for(int i=0;i<n;i++)
            p[i].in();
        scanf("%d%lf",&id,&k);
        if(id==0)
        {
            if(k<0)
                k+=2*pi;
            if(k>pi)
                k-=2*pi;
        }
        double sum=0;
        for(int i=0;i<n;i++)
            sum+=p[i]*p[(i+1)%n];
        if(sum<0)
        {
            for(int i=0;i<n/2;i++)
                swap(p[i],p[n-i-1]);
        }
    }
};
int cmp(Polygon p1,Polygon p2)
{
    if(p1.h==p2.h)
        return p1.id>p2.id;
    return p1.h>p2.h;
}
double Dis(Point a,Point b)
{
    return sqrt( (a.x-b.x)*(a.x-b.x)+(a.y-b.y)*(a.y-b.y));
}
Point Intersection(Point u1,Point u2,Point v1,Point v2)//ÇóÁœÖ±ÏßµÄœ»µã
{
    Point ret=u1;
    double t=((u1.x-v1.x)*(v1.y-v2.y)-(u1.y-v1.y)*(v1.x-v2.x))/
             ((u1.x-u2.x)*(v1.y-v2.y)-(u1.y-u2.y)*(v1.x-v2.x));
    ret.x+=(u2.x-u1.x)*t;
    ret.y+=(u2.y-u1.y)*t;
    return ret;
}
bool Is_inter(Point a,Point b,Point c,Point d)
{
    return Sig((b-a)*c)*Sig((b-a)*d)<=0;
}
bool Judge(Point a,Point p[],int n)
{
    Point p1,p2;
    for(int i=0;i<n;i++)
    {
        p1=p[(i+1)%n]-p[i];
        p2=a-p[i];
        if(Sig(p1*p2)<0)
            return 0;
    }
    return 1;
}
bool On_line(Point o,Point a,Point b)
{
    return Sig(Dis(a,b)-Dis(a,o)-Dis(b,o))==0;
}
void Get_inter(Point a,Point v,Point p[],int n,Point &inter)
{
    for(int i=0;i<n;i++)
    {
        if(Is_inter(a,a+v,p[i],p[(i+1)%n]))
        {
            Point pp=Intersection(a,a+v,p[i],p[(i+1)%n]);
            if(Sig((pp-a)^v)>0)
            {
                inter=pp;
                return ;
            }
        }
    }
    for(int i=0;i<n;i++)
    {
        if(Is_inter(a,a+v,p[i],p[(i+1)%n]))
        {
            Point pp=Intersection(a,a+v,p[i],p[(i+1)%n]);
            if(Sig((pp-a)^v)>=0)
            {
                inter=pp;
                return ;
            }
        }
    }
}
int main()
{
	freopen("t.in", "r", stdin);
    Polygon p[20];
    int n;
    double h;
    Point v;
    Point o;
    int all;
    int cas=1;
    scanf("%d",&all);
    for(cas=1;cas<=all;cas++)
    {
        printf("Case %d: ",cas);
        v.in();
        scanf("%lf",&h);
        scanf("%d",&n);
        o=Point(0,0);
        for(int i=0;i<n;i++)
            p[i].in();
        p[n].h=0,p[n].id=3,p[n].k=0;//增加一个高度为0的平面
        n++;
        sort(p,p+n,cmp);
        if(Sig(h)<0)
        {
            printf("Forever!\n");
            continue;
        }
        double cnt=0;
        int flag=1;
        for(int i=0;i<n;i++)
        {
            if(p[i].h==0)//当下一个平面的高度为0时 退出
            {
                cnt+=sqrt(2*h/G);
                break;
            }
            if(p[i].h>h)
                continue;
            double th=h-p[i].h;
            double tt=sqrt(2*th/G);
            Point tv=v*tt;
            Point inter;
            if(Judge(o+tv,p[i].p,p[i].n))//当点在凸包内
            {
                double k=p[i].k;
                o=o+tv;
                if(p[i].id==0)//改变速度
                {
                    Point vv=v;
                    vv.x=v.x*cos(k)-v.y*sin(k);
                    vv.y=v.x*sin(k)+v.y*cos(k);
                    v=vv;
                }
                else if(p[i].id==1)
                    v.x=k;
                else
                    v.y=k;
                if(!Sig(v.len()))//没有了水平速度 而且在平面上
                {
                    flag=0;
                    printf("Forever!\n");
                    break;
                }
                Get_inter(o,v,p[i].p,p[i].n,inter);
                h=p[i].h;
                cnt+=tt;
                cnt+=Dis(o,inter)/v.len();
                o=inter;
            }
        }
        if(flag)
            printf("%.2f\n",cnt);
    }
    return 0;
}



