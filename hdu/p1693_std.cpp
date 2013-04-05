#include <iostream>
#include <cstdio>
using namespace std;
typedef long long LL;
LL dp[12][12][1<<12];
long hash[12][12];

int main()
{
	freopen("t.in", "r", stdin);
    long T;
    long b=1;
    scanf("%ld",&T);
    while (T--)
    {
        long i,j,k,m,n;
        scanf("%ld %ld",&m,&n);
        for (i=1;i<=m;++i)
        {
            for (j=1;j<=n;++j)
            {
                scanf("%ld",&hash[i][j]);
            }
        }

        dp[0][n][0]=1;

        for (i=1;i<=m;++i)
        {
            long len=1<<n;
            for (j=0;j<len;++j)
            {
                dp[i][0][j<<1]=dp[i-1][n][j];
            }

            
            for (j=1;j<=n;++j)
            {
                len=(1<<n<<1);
                for(k=0;k<len;++k)
                {
                    long p=1<<j;
                    long q=p>>1;
                    
                    bool x=p&k;
                    bool y=q&k;

                    if (hash[i][j])
                    {
                        dp[i][j][k]=dp[i][j-1][k^p^q];
                        if (x!=y)
                        {
                            dp[i][j][k]+=dp[i][j-1][k];
                        }
                    }
                    else
                    {
                        if (x==0&&y==0)
                        {
                            dp[i][j][k]=dp[i][j-1][k];
                        }
                        else
                        {
                            dp[i][j][k]=0;
                        }
                    }
                }
            }
        }
        printf("Case %ld: There are %lld ways to eat the trees.\n",b++,dp[m][n][0]);

    }
    return 0;
}
