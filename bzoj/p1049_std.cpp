#include <iostream>
#include <cstring>
#include <cstdlib>
#include <cstdio>
#include <cmath>

using namespace std;

const int maxn=35555;
const int oo=1000000000;

int a[maxn],d[maxn];
int f[maxn],g[maxn];
int last[maxn],next[maxn],sum[maxn];
int n;
void init()
{
    scanf("%d",&n);
    int t=oo;
    for (int i=1;i<=n;i++)
    {
        scanf("%d",a+i);
        a[i]-=i;
        t=min(t,a[i]);
        a[n+1]=max(a[i],a[n+1]);
        d[i]=oo;
        last[i]=-1;
    }
    d[++n]=oo;
    for (int i=1;i<=n;i++) a[i]-=t;
    last[n]=-1;
    next[0]=-1;
}

int getmaxf(int lim,int R)
{
    int L=0,mid;
    while (L<R)
    {
        mid=(L+R+1)/2;
        if (d[mid]<=lim) L=mid;
        else R=mid-1;
    }
    return L;
}

void solve()
{
    for (int i=1;i<=n;i++)
    {
        int len=getmaxf(a[i],i-1);
        f[i]=len+1;
        d[len+1]=min(d[len+1],a[i]);
        next[i]=last[f[i]];
        last[f[i]]=i;
        int ming=oo;
        for (int j=last[len];j!=-1;j=next[j])
        if (a[j]<=a[i])
        {
            for (int k=i;k>j;--k)
            sum[k]=sum[k+1]+abs(a[k]-a[i]);
            int tmp=0;
            for (int k=j;k<i;k++)
            {
                tmp+=abs(a[k]-a[j]);
                ming=min(ming,g[j]+sum[k+1]+tmp);
            }
        }
        g[i]=ming;
    }
    cout<<n-f[n]<<endl<<g[n]<<endl;
}

int main()
{
    freopen("t.in","r",stdin);
    init();
    solve();
    return 0;
}
