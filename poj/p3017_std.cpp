#include <cstdio>
#include <cstring>
using namespace std;
typedef long long lld;
const int maxn=101000;
const lld maxl=999999999999999;

inline lld Max(lld a,lld b){return a>b?a:b;}
inline lld Min(lld a,lld b){return a<b?a:b;}
lld f[maxn];
int g[maxn];
lld a[maxn];
lld m,n;
int dp()
{
int i,j;
lld maxt=a[1];
lld tot=a[1];
int p=1;
f[1]=a[1];
g[1]=1;

for (i=2;i<=n;i++)
{
   f[i]=maxl;
   tot+=a[i];
   while (tot>m) tot-=a[p++];
   if (a[i]<=maxt&&g[i-1]>=p)
   {
    f[i]=f[i-1];
    g[i]=g[i-1];
   }
   else
   {
    maxt=a[i];
    for (j=(g[i-1]>=p?g[i-1]:i);j>=p;j--)
    {
     maxt=Max(maxt,a[j]);
     g[i]=(f[i]>maxt+f[j-1]?j:g[i]);
     f[i]=Min(f[i],maxt+f[j-1]);
    }
    maxt=f[i]-f[g[i]-1];
   }
}
printf("%lld\n",f[n]);
return 0;
}
int main()
{
freopen("t.in","r",stdin);
scanf("%d%lld",&n,&m);
int i;
memset(a,0,sizeof(a));
for (i=1;i<=n;i++)
{
   scanf("%lld",&a[i]);
   if (a[i]>m)
   {
    printf("-1\n");
    return 0;
   }
}
dp();
return 0;
}

