#include <vector>
#include <algorithm>
#include <utility>
#include <iostream>
#include <cstdio>
#include <cmath>
#include <cstdlib>
#define rep(i,n) for(int i=0;i<n;i++)
#define pb push_back
const int inf=~0U>>1,maxd=12;
using namespace std;
typedef long long ll;
ll Count[maxd][10]={},C;
int N[maxd],n;
void PreDo()
{
    rep(j,10)Count[1][j]=1;
    for(int i=2;i<maxd;i++)
    {
        rep(j,10)
        {
            Count[i][j]=0;
            rep(k,10)if(abs(k-j)>=2)Count[i][j]+=Count[i-1][k];
        }
    }
}
void Dfs(int p,int l)
{
    int t=N[p];
    if(p==0)
    {
        rep(j,t+1)if(abs(j-l)>=2)C++;
        return;
    }
    rep(i,t)
    {
        if(abs(i-l)>=2)
        {
            if(p==n-1&&i==0)
            {
                rep(j,p)rep(k,9)C+=Count[j+1][k+1];
            }
            else
            {
                C+=Count[p+1][i];
            }
        }
    }
    if(abs(t-l)>=2)Dfs(p-1,t);
}
ll Cal(ll A)
{
    if(!A)return 0;
    for(n=0;A;A/=10,n++)N[n]=A%10;
    C=0;Dfs(n-1,20);
    return C;
}
int main()
{
    freopen("t.in","r",stdin);
    PreDo();
    ll a,b;cin>>a>>b;
    cout<<Cal(b)-Cal(a-1)<<endl;
}



