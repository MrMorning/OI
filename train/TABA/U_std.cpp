#include<cstdio>
#include<cmath>
#include<cstring>
#include<string>
#include<iostream>
#include<queue>
#include<stack>
#include<map>
#include<set>
#include<cstdlib>
#include<algorithm>
#include<ctime>
#define Maxn 10000010
#define Maxnum 10000010
#define lim 130706
using namespace std;

string s;
map<char, int> gid;
int p[20], ans, tot, cnt, np;
long long d[Maxn], num;
long long pa[800010], ti[800010], c[800010];
int nc;
bool vis[12], pri[Maxnum];

long long  gcd(long long a, long long b)
{
    if (a%b == 0) return b;
    else return gcd(b, a%b);
}
inline long long calc()
{
    long long ret = 0;
    for (int i=0; i<s.length(); i++)
        ret = ret*10 + p[gid[s[i]]-1];
    return ret;
}

void dfs(int dep)
{
    if (num == 1 || cnt > lim) return;
    if (dep >= tot)
    {
        cnt++;
        if (num == -1) num = calc();
        else num = gcd(num, calc());
        return;
    }
    else
    {
        if (dep&1)
        {
                for (int i=9; i>=0; i--)
        if (!vis[i])
        {
            if ((i == 0 && dep == 0) || (dep==tot-1 && i == 0)) continue;         
            vis[i] = true;
            p[dep] = i;
            dfs(dep+1);
           vis[i] = false;
        }          
        }
        else
        for (int i=0; i<=9; i++)
        if (!vis[i])
        {
            if ((i == 0 && dep == 0) || (dep==tot-1 && i == 0)) continue;          
            vis[i] = true;
            p[dep] = i;
            dfs(dep+1);         
            vis[i] = false;
        }
    }
}
void init()
{
     np = 0;
     memset(pri, true, sizeof(pri));
     for (long long i=2; i<=10000000; i++)
     if (pri[i])
     {
        pa[np++] = i;
        for (long long j=i*i; j<=10000000; j+=i) pri[j] = false;
     }  
     }
void work(long long m)
{
     nc = 0;
     int tmp = 0;
     for (int i=0; i<np; i++)
     {
         if (pa[i] > m) break;
         if (m % pa[i] == 0)
         {
               tmp = 0;
               while (m % pa[i] == 0)
               {
                  m/=pa[i];
                  tmp++;                     
               }
               ti[nc] = tmp;
               c[nc++] = pa[i];   
         }
     }
     if (m != 1) ti[nc] = 1, c[nc++] = m;
     return;
     }
void make(int idx, long long sum) 
{ 
     if (idx >= nc)
     {
         d[ans++] = sum;
         return;             
     }
     make(idx+1, sum); 
     long long st = 1;
     for (int i=1; i<=ti[idx]; i++) 
     {
         st *= c[idx];
         make(idx+1, sum * st);
     } 
     return;  
     }
int main()
{
	freopen("t.in", "r", stdin);
    ios::sync_with_stdio(false);
    int T, ca=0;
    cin >>T;
    init();
    while (T--)
    {
        cin >>s;
        gid.clear();
        tot = cnt = 0;
        for (int i=0; i<s.length(); i++)
          if (gid.find(s[i]) == gid.end()) gid[s[i]] = ++tot;
        num = -1;
        memset(vis, false, sizeof(vis));
        dfs(0);
        cout <<"Case "<<++ca<<":";
        ans = 0;
        work(num);
        make(0, 1);
        sort(d, d+ans);
        for (int j=0; j<ans; j++) cout <<" "<<d[j];
        cout <<endl;
    }
  
    return 0;
}

