#include <cstdio>
#include <cstdlib>
using namespace std;
//最远曼哈顿距离 
double a[100000][5];
const double INF=2000000000;
int n;
inline double max(double x,double y){return x>y?x:y;}
inline double min(double x,double y){return x<y?x:y;} 
int main()
{
	freopen("t.in", "r", stdin);
    int i,j,k;
    double mmin,mmax,ans,sum;
    while(scanf("%d",&n)!=EOF)
    {
          for(i=0;i<n;i++)
          for(j=0;j<5;j++)scanf("%lf",&a[i][j]);
          
          ans=0;
          for(i=0;i<32;i++)
          {
              mmin=INF;
              mmax=-INF;
              for(j=0;j<n;j++)
              {
                  sum=0;            
                  for(k=0;k<5;k++)
                  {
                      if(i&(1<<k))sum+=a[j][k];
                      else sum-=a[j][k];            
                      }
                  mmin=min(mmin,sum);
                  mmax=max(mmax,sum);                
                  }
              ans=max(ans,mmax-mmin);                 
              }                    
          printf("%.2lf\n",ans);    
          }
    return 0;
    }
