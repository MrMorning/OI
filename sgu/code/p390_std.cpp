#include <iostream>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <algorithm>

using namespace std;
typedef long long __int64;

__int64 l, r;
int K;
__int64 dp[20][200][1000], mod[20][200][1000];
int s[20], t[20];
int test(__int64 l, __int64 r, int k)
{
    int sum = 0, ans = 0;
    for(__int64 i = l; i <= r; i++)
    {
        __int64 temp = i;
        for(int j = 0; j < 20; j++)
        {
            sum += temp%10;
            temp /= 10;
        }
        if(sum >= k)
        {
            sum = 0;
            ans++;
        }
    }
 //   cout << ans << endl;
    return ans;
}
int main()
{
    freopen("t.in", "r", stdin);
    scanf("%lld %lld %d", &l, &r, &K);
    if(r - l < 10)
    {
        printf("%d\n", test(l, r, K));
    }
    else
    {
        for(int i = 0; i < 200; i++)
        {
            for(int j = 0; j < K; j++)
            {
                if(i+j >= K)  dp[0][i][j] = 1;
                else          mod[0][i][j] = i + j;
            }
        }
        for(int i = 1; i < 20; i++)
        {
            for(int j = 0; j < 185; j++)
            {
                for(int k = 0, now; k < K; k++)
                {
                    now = k;
                    for(int l = 0; l < 10&&j + l ; l++)
                    {
                        dp[i][j][k] += dp[i-1][j+l][now];
                        now = mod[i-1][j+l][now];
                    }
                    mod[i][j][k] = now;
                }
            }
        }
        for(int i = 0; i < 20; i++)
        {
            s[i] = l%10;  l /= 10;
            t[i] = r%10;  r /= 10;
        }
        int now = 0, v_mod = 0, nbit = 0;
        __int64 ans = 0;
        for(int i = 0; i < 20; i++)  now += s[i];
        for(int i = 20; i >= 0; i--)  if(s[i] != t[i])  { nbit = i;  break; };
        for(int i = 0; i <= nbit; i++)
        {
            now -= s[i];
            int temp = now, tt = 10, ll = s[i];
            if(i == nbit)   tt = t[i];
            if(i > 0)  ll++;
            for(int k = ll; k < tt; k++)
            {
                ans  += dp[i][temp+k][v_mod];
                v_mod = mod[i][temp+k][v_mod];
            }
        }
        now = 0;
        for(int i = 20; i >= 0; i--)
        {
            now += t[i+1];
            if(i < nbit)
            {
                if(i > 0)
                {
                    for(int k = 0; k < t[i]; k++)
                    {
                        ans  += dp[i][now+k][v_mod];
                        v_mod = mod[i][now+k][v_mod];
                    }
                }
                else
                {
                    for(int k = 0; k <= t[i]; k++)
                    {
                        ans +=  dp[i][now+k][v_mod];
                        v_mod = mod[i][now+k][v_mod];
                    }
                }
            }
        }
        printf("%lld\n", ans);
    }
    return 0;
}
