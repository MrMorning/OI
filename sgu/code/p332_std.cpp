#include<stdio.h>
#include<algorithm>
#include<math.h>
struct point
{
    double x,y;
}jiao[100001],data[100001];

int dbl(double a)
{
    if(fabs(a)<1e-10)
        return 0;
    if(a<0)
        return -1;
    return 1;
}
double cha(double x1,double y1,double x2,double y2)
{
    return x1*y2-x2*y1;
}
double cha(point a,point b,point c)
{
    return cha(b.x-a.x,b.y-a.y,c.x-a.x,c.y-a.y);
}
double dist(point a,point b)
{
    return sqrt((a.x-b.x)*(a.x-b.x)+(a.y-b.y)*(a.y-b.y));
}

void inner(point a,point b,double pos,point &a2,point &b2)
{
    a2.x=a.y-b.y;
    a2.y=b.x-a.x;
    double d=dist(a,b);
    a2.x*=pos/d;
    a2.y*=pos/d;
    b2.x=b.x+a2.x;
    b2.y=b.y+a2.y;
    a2.x+=a.x;
    a2.y+=a.y;
    while(fabs(a2.x)<1e+7*2&&fabs(a2.y)<1e+7*2)
    {
        a2.x+=a2.x-b2.x;
        a2.y+=a2.y-b2.y;
    }
    while(fabs(b2.x)<1e+7*2&&fabs(b2.y)<1e+7*2)
    {
        b2.x+=b2.x-a2.x;
        b2.y+=b2.y-a2.y;
    }
}
point cross(point a,point b,point c,point d)
{
    double c1=fabs(cha(a,b,c)),c2=fabs(cha(a,b,d)),bi=c1/(c1+c2);
    point ans={c.x+(d.x-c.x)*bi,c.y+(d.y-c.y)*bi};
    return ans;
}

int main()
{
    int n,i,j,fr,to;
    double min,max;
    freopen("t.in","r",stdin);
    scanf("%d",&n);
    for(i=0;i<n;++i)
        scanf("%lf%lf",&data[i].x,&data[i].y);
    data[n]=data[0];
    
    for(min=0,max=1e+8;fabs(max-min)>1e-4;)
    {
        double cen=(min+max)/2.0;
        inner(data[0],data[1],cen,jiao[0],jiao[1]);
        point js;
        inner(data[1],data[2],cen,js,jiao[2]);
        jiao[1]=cross(jiao[0],jiao[1],js,jiao[2]);
        for(i=2,fr=0,to=2;i<n;++i)
        {
            point a,b;
            inner(data[i],data[i+1],cen,a,b);
            while(fr<to&&dbl(cha(a,b,jiao[to-1]))<=0&&dbl(cha(a,b,jiao[to]))<=0)    --to;
            if(fr>=to)    break;
            if(dbl(cha(a,b,jiao[to]))<=0)
            {
                jiao[to]=cross(a,b,jiao[to-1],jiao[to]);
                jiao[++to]=b;
            }
            
            while(fr<to&&dbl(cha(a,b,jiao[fr]))<=0&&dbl(cha(a,b,jiao[fr+1]))<=0)    ++fr;
            if(fr>=to)    break;
            if(dbl(cha(a,b,jiao[fr]))<=0)
            {
                jiao[fr]=cross(a,b,jiao[fr],jiao[fr+1]);
                jiao[to]=jiao[fr];
            }
        }
        if(i<n)
            max=cen;
        else
            min=cen;
    }
    printf("%.3lf\n",max);
    return 0;
}
