#include<iostream>
#include<cstdio>
#include<cstring>
#include<algorithm>
using namespace std;
const int maxn=1100;
//一条线  每次取连续M个 SG函数
int sg[maxn],flag[maxn];
int calc_sg(int n,int m)
{
    for(int i=0;i<m;i++) sg[i]=0;
    for(int i=m;i<=n;i++)
    {
        memset(flag,0,sizeof(flag));
        for(int j=0;j+m<=i;j++)
        {
            flag[sg[j]^sg[i-j-m]]=1;
        }
        for(int j=0;;j++)
        {
            if(flag[j]==0)
            {
                sg[i]=j;break;
            }
        }
    }
}
int main()
{
	freopen("t.in", "r", stdin);
    int ci,pl=1;scanf("%d",&ci);
    while(ci--)
    {
        int n,m;scanf("%d%d",&n,&m);
        if(n<m)
        {
            printf("Case #%d: abcdxyzk\n",pl++);
            continue;
        }
        calc_sg(n-m,m);
        if(sg[n-m]==0) printf("Case #%d: aekdycoin\n",pl++);
        else printf("Case #%d: abcdxyzk\n",pl++);
    }
    return 0;
}
