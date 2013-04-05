#include<stdio.h>
#include<math.h>
#include<algorithm>
#include<string.h>
using namespace std;
 
const double pi=3.1415926535897932384626;
int sgn(double a)
{
        if(fabs(a)<1e-12)
                return 0;
        if(a<0)
                return -1;
        return 1;
}
 
struct point
{
        double x,y;
        friend point operator + (point a,point b)
        {
                return (point){a.x+b.x,a.y+b.y};
        }
        friend point operator - (point a,point b)
        {
                return (point){a.x-b.x,a.y-b.y};
        }
        friend double operator / (point a,point b)
        {
                return a.x*b.y-a.y*b.x;
        }
        friend bool operator < (point a,point b)
        {
                if(!sgn(a.x-b.x))
                        return sgn(a.y-b.y)<0;
                return sgn(a.x-b.x)<0;
        }
        friend bool operator == (point a,point b)
        {
                return !sgn(a.x-b.x)&&!sgn(a.y-b.y);
        }
}line[51][51];
bool cmp_atan(point a,point b)
{
        return atan2(a.y,a.x)<atan2(b.y,b.x);
}
 
double cha(point a,point b,point c)
{
        return (b-a)/(c-a);
}
 
struct fl
{
        double a,b,c;
}data[51];
double areas[51],r;
int slen,line_len[51],n,n2;
 
int line_hash[51][51];
void go(int,int);
double arc_area(point p1,point p2)
{
        double angle=atan2(p2.y,p2.x)-atan2(p1.y,p1.x);
        if(sgn(angle)<0)        angle+=pi*2;
        return r*r*angle-r*r*sin(angle);
}
 
point edge_p[51];
void solve_area()
{
        int i,j;
        //Circle X Line
        for(i=0;i<n;++i)
        {
                line_len[i]=2;
                fl now=data[i];
                if(sgn(now.a)!=0)
                {
                        double  a=now.b*now.b/now.a/now.a+1,
                                        b=2*now.b*now.c/now.a/now.a,
                                        c=now.c*now.c/now.a/now.a-r*r,
                                        delta=sqrt(b*b-4.0*a*c),
                                        y0=(-b+delta)/2.0/a,y1=(-b-delta)/2.0/a,
                                        x0=(-now.c-now.b*y0)/now.a,x1=(-now.c-now.b*y1)/now.a;
                        line[i][0]=(point){x0,y0};
                        line[i][1]=(point){x1,y1};
                }
                else
                {
                        double y=-now.c/now.b,x=sqrt(r*r-y*y);
                        line[i][0]=(point){x,y};
                        line[i][1]=(point){-x,y};
                }
                edge_p[i*2]=line[i][0];
                edge_p[i*2+1]=line[i][1];
        }
        
        //Line X Line
        for(i=0;i<n;++i)
                for(j=i+1;j<n;++j)
                {
                        fl now1=data[i],now2=data[j];
                        double chu=now1.a*now2.b-now1.b*now2.a;
                        if(sgn(chu)==0)
                                continue;
                        double  x=(-now1.c*now2.b+now1.b*now2.c)/chu,
                                        y=(-now1.a*now2.c+now1.c*now2.a)/chu;
                        if(sgn(x*x+y*y-r*r)>=0)
                                continue;
                        line[i][line_len[i]++]=(point){x,y};
                        line[j][line_len[j]++]=(point){x,y};
                }
        
        for(i=0;i<n;++i)
        {
                sort(line[i],line[i]+line_len[i]);
                int k=0;
                for(j=0;j<line_len[i];++j)
                        if(!j||!(line[i][j]==line[i][j-1]))
                                line[i][k++]=line[i][j];
                line_len[i]=k;
                line_len[i+n]=line_len[i];
                for(j=0;j<line_len[i];++j)
                        line[i+n][line_len[i]-j-1]=line[i][j];
        }
        
        sort(edge_p,edge_p+n*2,cmp_atan);
        edge_p[n*2]=edge_p[0];
        n2=n*2;
        for(i=0;i<n*2;++i)
                if(!(edge_p[i]==edge_p[i+1]))
                {
                        line_len[n2]=2;
                        line[n2][0]=edge_p[i];
                        line[n2++][1]=edge_p[i+1];
                        for(j=0;j<n*2;++j)
                                for(int k=0;k<line_len[j]-1;++k)
                                        if(line[n2-1][0]==line[j][k+1]&&line[n2-1][1]==line[j][k])
                                        {
                                                line_hash[n2-1][0]++;
                                                line_hash[j][k]++;
                                                areas[slen++]=arc_area(line[n2-1][0],line[n2-1][1])/2.0;
                                        }
                }
        
        for(i=0;i<n*2;++i)
                for(j=0;j<line_len[i]-1;++j)
                        go(i,j);
}
 
point pol[51];
void go(int i,int j)
{
        if(line_hash[i][j])
                return;
        int k,l,plen=1,lastk=i;
        pol[0]=line[i][j];
        pol[1]=line[i][j+1];
        line_hash[i][j]=1;
        double sum=0;
        while(1)
        {
                point dir=pol[plen-1]-pol[plen];
                double last_ang=atan2(dir.y,dir.x),best_ang=1000;
                int bestk=-1,bestl=-1;
                for(k=0;k<n2;++k)
                        for(l=0;l<line_len[k]-1;++l)
                        {
                                point now1=line[k][l],now2=line[k][l+1];
                                if(now1==pol[plen])
                                {
                                        double now_ang=last_ang-atan2(now2.y-now1.y,now2.x-now1.x);
                                        if(sgn(now_ang)<0)      now_ang+=pi*2;
                                        if(sgn(now_ang-best_ang)<0&&sgn(now_ang)&&sgn(now_ang-pi))
                                        {
                                                best_ang=now_ang;
                                                bestk=k;
                                                bestl=l;
                                        }
                                }
                        }
                lastk=bestk;
                line_hash[bestk][bestl]++;
                pol[++plen]=line[bestk][bestl+1];
                if(bestk>=n*2)
                        sum+=arc_area(pol[plen-1],pol[plen]);
                if(!sgn(pol[plen].y-line[i][j].y)&&!sgn(pol[plen].x-line[i][j].x))
                        break;
        }
        for(i=2;i<=plen;++i)
                sum+=cha(pol[0],pol[i-1],pol[i]);
        if(sgn(sum))
                areas[slen++]=sum/2.0;
}
 
double f[177147];
int dfsed[177147],mi3[12]={1,3,9,27,81,243,729,2187,6561,19683,59049,177147};
double dfs(int i)
{
        if(dfsed[i])
                return f[i];
        dfsed[i]=1;
        int unrar[13],j,ps=0;
        double s1=0,s2=0;
        memset(unrar,0,sizeof(unrar));
        for(j=0;j<slen;++j)
        {
                unrar[j]=i/mi3[j]%3;
                if(unrar[j]==0)
                        ps=1;
                if(unrar[j]==1)
                        s1+=areas[j];
                if(unrar[j]==2)
                        s2+=areas[j];
        }
        if(ps==0)
        {
                f[i]=0;
                return 0;
        }
        
        if(sgn(s1-s2)<=0)
        {
                f[i]=-1;
                for(j=0;j<slen;++j)
                        if(!unrar[j])
                        {
                                double now=dfs(i+mi3[j])+areas[j];
                                if(now>f[i])
                                        f[i]=now;
                        }
        }
        else
        {
                f[i]=1e+30;
                for(j=0;j<slen;++j)
                        if(!unrar[j])
                        {
                                double now=dfs(i+mi3[j]*2);
                                if(now<f[i])
                                        f[i]=now;
                        }
        }
        return f[i];
}
 
int useless[21];
int main()
{
        int i,j;
        freopen("t.in","r",stdin);
        //freopen("output.txt","w",stdout);
        scanf("%d%lf",&n,&r);
        for(i=0;i<n;++i)
        {
                scanf("%lf%lf%lf",&data[i].a,&data[i].b,&data[i].c);
                if(sgn(data[i].c))
                {
                        data[i].a/=data[i].c;
                        data[i].b/=data[i].c;
                        data[i].c=1;
                }
        }
        solve_area();
        double ans=dfs(0);
        printf("%.4lf %.4lf\n",ans,pi*r*r-ans);
        return 0;
}
 
