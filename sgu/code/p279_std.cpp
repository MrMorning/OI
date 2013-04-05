#include<cstdio>
#include<algorithm>
#include<queue>
#include<stack>
#include<cstdlib>
#include<cstring>
#include<vector>
using namespace std;

const int MAX=2000+10;
int a[MAX],ans[MAX],n,h1[MAX],h2[MAX];

int main()
{
    #ifndef ONLINE_JUDGE
    freopen("t.in","r",stdin);
    #endif
    int i,j,k,m;
    scanf("%d",&n);
    for(i=1;i<=n;++i)
        scanf("%d ",&a[i]);
    h1[n+1]=10*n;
    for(i=1;i<=2*n;++i)
    {
        for(j=1;j<=n;++j)
            if(!a[j] && !h1[j])
                break;
        if(j!=n+1)
        {
            ans[i]=j;
            h1[j]=i;
            for(k=1;k<j;++k)
                if(!h1[k])--a[k];
        }else
        {
            m=n+1;
            for(j=1;j<=n;++j)
                if(h1[j] && !h2[j])
                    if(h1[j]<h1[m])m=j;
            j=m;
            if(j==n+1)
            {
                printf("NO\n");
                return 0;
            }
            ans[i]=-j;
            h2[j]=1;
            for(k=j+1;k<=n;++k)
                if(!h1[k])--a[k];
        }
    }
    printf("YES\n");
    for(i=2*n;i>=1;--i)
        printf("%d ",ans[i]);
    printf("\n");
}
