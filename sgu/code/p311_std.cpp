#include <vector>
#include <algorithm>
#include <utility>
#include <iostream>
#include <cstdio>
#include <cmath>
#include <cstdlib>
#include <cstring>
#include <time.h>
#define rep(i,n) for(int i=0;i<n;i++)
#define pb push_back
#define Debug(x) cout<<#x<<"="<<x<<endl;
#define For(i,l,r) for(int i=l;i<=r;i++)
#define tr(e,x) for(typeof(x.begin()) e=x.begin();e!=x.end();e++)
#define printTime cout<<"Time:"<<pre-clock()<<endl;pre=clock();
const int inf=~0U>>1,maxc=1<<20;
using namespace std;
typedef long long ll;
char cmd[100];
#define scan(t)\
{\
    char pt;\
    while(pt=getchar(),pt<'0'||pt>'9');\
    t=pt-'0';\
    while(pt=getchar(),pt>='0'&&pt<='9')t=t*10+pt-'0';\
}
bool Mark[1<<21];
ll sum[1<<21]={},num[1<<21]={};
void set(int t)
{
    sum[t]=sum[t*2]+sum[t*2+1];
    num[t]=num[t*2]+num[t*2+1];
}
void MarkIt(int t)
{
    sum[t]=num[t]=0;
    Mark[t]=true;
}
void PushDown(int t)
{
    if(Mark[t])
        MarkIt(t*2),MarkIt(t*2+1);
    Mark[t]=false;
}
void Update(int t,ll c)
{
    int i,l,r;
    for(i=1,l=0,r=maxc;i<maxc;)
    {
        PushDown(i);i<<=1;
        int m=l+r>>1;
        if(t>=m)i++,l=m;
        else r=m;
    }
    i=t+maxc;sum[i]+=t*c;num[i]+=c;
    for(i>>=1;i;i>>=1)set(i);
}
ll get(int n)
{
    if(num[1]<n)return -1;
    ll ret=0;int i;
    for(i=1;i<maxc;)
    {
        PushDown(i);i<<=1;
        if(num[i]>=n)continue;
        ret+=sum[i];n-=num[i];i++;
    }
    return ll(n)*(i-maxc)+ret;
}
void clear(int n)
{
    int i;
    for(i=1;i<maxc;)
    {
        PushDown(i);i<<=1;
        if(num[i]>=n)continue;
        n-=num[i];MarkIt(i);i++;
    }
    Update(i-maxc,-n);
}
int main()
{
    freopen("t.in","r",stdin);
    int n;ll c;
    while(scanf("%s",cmd)==1)
    {
        scan(n);scan(c);
        if(cmd[0]=='A')Update(c,n);
        else
        {
            ll tmp=get(n);
            if(tmp==-1||tmp>c)
                puts("UNHAPPY");
            else
                puts("HAPPY"),clear(n);
        }
    }
}



