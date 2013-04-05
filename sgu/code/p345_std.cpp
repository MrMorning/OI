#include<stdio.h>
#include<math.h>
#include<algorithm>
using namespace std;

struct point
{
    double x,y;
}pol[50011];
template <class T>
T operator + (T a,T b)
{
    a.x+=b.x;
    a.y+=b.y;
    return a;
}
template <class T>
T operator - (T a,T b)
{
    a.x-=b.x;
    a.y-=b.y;
    return a;
}
template <class T>
double operator / (T a,T b)
{
    return a.x*b.y-a.y*b.x;
}
int sgn(double a)
{
    if(fabs(a)<1e-12)
        return 0;
    if(a<0)
        return -1;
    return 1;
}

struct fq
{
    point a,b;
    double at;
    int wh;
}query[50011];
bool operator < (fq a,fq b)
{
    return a.at<b.at;
}

int erfen1(int a,int b,fq data)
{
    if(a>b)
        return -1;
    int mid=(a+b)>>1;
    if(sgn((data.b-data.a)/(pol[mid]-data.a))>=0&&sgn((data.b-data.a)/(pol[mid+1]-data.a))<=0)
        return mid;
    if(sgn((data.b-data.a)/(pol[mid]-data.a))<0)
        return erfen1(a,mid-1,data);
    return erfen1(mid+1,b,data);
}
int erfen2(int a,int b,fq data)
{
    if(a>b)
        return -1;
    int mid=(a+b)>>1;
    if(sgn((data.b-data.a)/(pol[mid]-data.a))<=0&&sgn((data.b-data.a)/(pol[mid+1]-data.a))>=0)
        return mid;
    if(sgn((data.b-data.a)/(pol[mid]-data.a))>0)
        return erfen2(a,mid-1,data);
    return erfen2(mid+1,b,data);
}

point getcross(point a,point b,point c,point d,int &err)
{
    double s1=fabs((b-a)/(c-a)),s2=fabs((b-a)/(d-a));
    point ans={c.x+(d.x-c.x)*s1/(s1+s2),c.y+(d.y-c.y)*s1/(s1+s2)};
    if(sgn(s1+s2)==0)
        err=1;
    else
        err=0;
    return ans;
}

int useless[50011];
double area[50011],ans[50011];
int main()
{
    int n,m,i,j;
    freopen("t.in","r",stdin);
    scanf("%d",&n);
    for(i=0;i<n;++i)
        scanf("%lf%lf",&pol[i].x,&pol[i].y);
    for(i=0;i<n;++i)
        if(sgn((pol[(i+2)%n]-pol[i])/(pol[(i+1)%n]-pol[i]))==0)
            useless[(i+1)%n]=1;
    for(i=0,j=0;i<n;++i)
        if(!useless[i])
            pol[j++]=pol[i];
    n=j;
    
    double ss=0;
    for(i=2;i<n;++i)
        ss+=(pol[i-1]-pol[0])/(pol[i]-pol[0]);
    if(sgn(ss)<0)
        for(i=0;i<n/2;++i)
            swap(pol[i],pol[n-i-1]);
    pol[n]=pol[0];
    
    scanf("%d",&m);
    
    for(i=0;i<m;++i)
    {
        scanf("%lf%lf%lf%lf",&query[i].a.x,&query[i].a.y,&query[i].b.x,&query[i].b.y);
        
        while(fabs(query[i].a.x)<10000&&fabs(query[i].a.y)<10000)
            query[i].a=query[i].a+query[i].a-query[i].b;
        while(fabs(query[i].b.x)<10000&&fabs(query[i].b.y)<10000)
            query[i].b=query[i].b+query[i].b-query[i].a;
        
        if(sgn((query[i].b-query[i].a)/(pol[0]-query[i].a))<0)
            swap(query[i].a,query[i].b);
        query[i].at=atan2(query[i].b.y-query[i].a.y,query[i].b.x-query[i].a.x);
        query[i].wh=i;
    }
    sort(query,query+m);
    
    for(i=1;i<n;++i)
        area[i]=area[i-1]+(pol[i-1]-pol[0])/(pol[i]-pol[0]);
    area[n]=area[n-1];
    point p0=pol[0];
    for(i=0,j=0;i<m;++i)
    {
        for(;!(sgn((query[i].b-query[i].a)/(pol[j]-pol[j==0?n-1:j-1]))<=0&&sgn((query[i].b-query[i].a)/(pol[j+1]-pol[j]))>0);j=(j+1)%n);
        double p1=(query[i].b-query[i].a)/(pol[j]-pol[j==0?n-1:j-1]),p2=(query[i].b-query[i].a)/(pol[j+1]-pol[j]),pp=(query[i].b-query[i].a)/(pol[j]-query[i].a);
        int l=erfen1(0,j,query[i]),r=erfen2(j,n-1,query[i]);
        if(l==-1||r==-1)
        {
            ans[query[i].wh]=0;
            continue;
        }
        int e1,e2;
        point c1=getcross(query[i].a,query[i].b,pol[l],pol[l+1],e1),
              c2=getcross(query[i].a,query[i].b,pol[r],pol[r+1],e2);
        if(e1||e2)
        {
            ans[query[i].wh]=0;
            continue;
        }
        ans[query[i].wh]=(c1-p0)/(c2-p0)+(pol[l]-p0)/(c1-p0)+(c2-p0)/(pol[r+1]-p0)+area[l]+area[n]-area[r+1];
        if(ans[query[i].wh]<0)
            int xy=0;
        if(area[n]-ans[query[i].wh]<ans[query[i].wh])
            ans[query[i].wh]=area[n]-ans[query[i].wh];
    }
    for(i=0;i<m;++i)
        printf("%.2lf\n",ans[i]/2.0);
    return 0;
}
