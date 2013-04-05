#include<stdio.h>
#include<math.h>
#include<algorithm>
using namespace std;
const double pi=3.1415926535897932384626;

struct point
{
    double x,y,z;
};
int sgn(double a)
{
    if(fabs(a)<1e-14)
        return 0;
    if(a<0)
        return -1;
    return 1;
}

int main()
{
    double i,r;
    point p1,p2;
    freopen("t.in","r",stdin);
    scanf("%lf%lf%lf%lf%lf%lf%lf",&r,&p1.x,&p1.y,&p1.z,&p2.x,&p2.y,&p2.z);
    double oa=sqrt(p1.x*p1.x+p1.y*p1.y+p1.z*p1.z),
           ob=sqrt(p2.x*p2.x+p2.y*p2.y+p2.z*p2.z),
           ab=sqrt((p2.x-p1.x)*(p2.x-p1.x)+(p2.y-p1.y)*(p2.y-p1.y)+(p2.z-p1.z)*(p2.z-p1.z)),
           cos_alpha=(ob*ob+oa*oa-ab*ab)/2.0/oa;
    p1.z=p2.z=0;
    p1.x=oa;
    p1.y=0;
    p2.x=cos_alpha;
    p2.y=sqrt(ob*ob-cos_alpha*cos_alpha);
    double ans=2.0*pi*r*r*(2.0-r*(1.0/oa+1.0/ob)),h=r*r/oa;
    if(sgn(p2.y)==0)
    {
        if(p2.x>0)
            printf("%.3lf",2.0*pi*(r*r-r*r*r*(1.0/(oa>ob?oa:ob))));
        else
            printf("%.3lf",ans);
        return 0;
    }
    double cos_theta=r/ob,sin_theta=sqrt(1-cos_theta*cos_theta);
    point dw={p2.x/ob*r,p2.y/ob*r},
          pc={dw.x*cos_theta-dw.y*sin_theta,dw.x*sin_theta+dw.y*cos_theta};
    double kk=-p2.x/p2.y;
    //double eps=0.00002;
    double eps=(r-h)/400000.0;
    for(i=h+eps/2.0;i<r;i+=eps)
    {
        double y2=pc.y+(i-pc.x)*kk;
        double yd=sqrt(r*r-i*i);
        //double sina=((p2.x-i)*(p2.x-i)+p2.y*p2.y+yd*yd-ob*ob+r*r)/2.0/yd/p2.y;
        if(y2>yd)
        //if(sina>1)
            continue;
        double cosa=acos(y2/yd);
        if(y2<=-yd)
        //if(sina<=-1)
        {
            ans-=2*pi*r*eps;
            continue;
        }
        ans-=2*r*eps*acos(y2/yd);
        //ans-=(pi/2.0-asin(sina))*2.0*r*eps;
    }
    printf("%.3lf\n",ans);
    return 0;
}
