#include<iostream>
#include<cstring>
#include<cstdio>

using namespace std;
#define N 1010
int array[N],n;

int digit_sum(long long x)
{
    int i = 0;
    while(x != 0)
    {
        i = i + x % 10;
        x = x / 10;
    }
    return i;
}

int main()
{
	freopen("t.in", "r", stdin);
    int i,j,k;
    int cases,ans;
    scanf("%d",&cases);
    while(cases--)
    {
        scanf("%d",&n);
        for(i = 1; i <= n; i++)
            scanf("%d",&array[i]);
        ans = array[n];
        for(i = n-1; i >= 1; i--)
        {
            ans = digit_sum(((long long)ans+1)*array[i]);
            while(ans >= 10) ans = digit_sum(ans);
        }
        printf("%d\n",ans);
    }
    return 0;
}
