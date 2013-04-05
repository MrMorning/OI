#include<cstdio>
#include<cstring>
struct Thash{
      static const long MAXH = 4000007;
      long h[MAXH];
      long data[MAXH];
      inline void clear() {memset(h, 0xff, sizeof(h));}
      inline long& operator [] (long k)
      {
         long i;
         for (i=k%MAXH; (h[i]>=0)&&(h[i]!=k); ++i);
         if (h[i] < 0) {h[i]=k; data[i]=-1;}
         return data[i];
      }
};
struct Tstack{
      static const long MAXS = 2000010;
      long s[MAXS];
      long *top;
      inline void clear() {top=s;}
      inline bool empty() {return top==s;}
      inline void push(long k) {*(++top)=k;}
      inline long pop() {return *(top--);}
};
long min(long a, long b)
{
   return a>b ? b : a;
}
const long MAXN = 8;
const long exp4[] = {0, 0x00000003, 0x0000000C, 0x00000030, 0x000000C0,
                        0x00000300, 0x00000C00, 0x00003000, 0x0000C000,
                        0x00030000, 0x000C0000, 0x00300000, 0x00C00000,
                        0x03000000, 0x0C000000, 0x30000000, 0xC0000000};
inline long getbit(long a, long b)
{
   return (a & exp4[b]) >> (b + b - 2);
}
inline long putbit(long a, long b, long c)
{
   return a - (a & exp4[b]) + (c << (b + b - 2));
}
void add(Thash &f, Thash &g, Tstack &s, long a, long b, long c)
{
   if (f[a] == -1)
   {
      s.push(a);
      f[a] = b;
      g[a] = c;
   }
   else
   {
      if (b < f[a])
      {
         f[a] = b;
         g[a] = c;
      }
      else
      if (b == f[a]) g[a] = g[a] + c;
   } 
}
long n;
long map[MAXN*2][MAXN*4];
long len[MAXN*2];
Thash f[2];
Thash g[2];
Tstack s[2];
void init()
{
   long i, j;
   for (i=1; i<=n; ++i)
     len[i] = n + i - 1;
   for (i=1; i<=n; ++i)
     len[i+n] = n + n - i;     
   for (i=1; i<=n; ++i)
   for (j=1; j<=len[i]*2+1; ++j)
      scanf("%ld", &map[i][j]);
   for (i=n+1; i<=2*n; ++i)
   for (j=0; j<len[i]*2+1; ++j)
      scanf("%ld", &map[i][j]);
}
inline void deal1(long i, long j, long k, long left, long up, long last, long now, long value, long count)
{
   long tmp = map[i][j*2];
   if (tmp == 4)
   {
      if ((left == 0) && (up == 0)) add(f[now], g[now], s[now], k, value, count);
   }
   else if (tmp == 0)
   {
      if ((left == 0) && (up == 0)) add(f[now], g[now], s[now], k, value, count);
      else if ((left == 0) || (up == 0)) add(f[now], g[now], s[now], putbit(k, j+1, left+up), value+1, count);
      else if (left == up) add(f[now], g[now], s[now], putbit(k, j+1, 0), value+1, count);
   }
   else
   {
      if ((left == 0) && (up == 0)) add(f[now], g[now], s[now], putbit(k, j+1, tmp), value+1, count);
      else if (((left == 0) || (up == 0)) && (left + up == tmp))
      {
         add(f[now], g[now], s[now], putbit(k, j+1, 0), value+1, count);
      }
   }
}
void solve()
{
   long now = 1;
   long last = 0;
   s[0].clear();
   s[0].push(0);
   f[0].clear();
   f[0][0] = 0;
   g[0][0] = 1;
   long i, j, k, t, tmp, left, up, count;
   for (i=1; i<=2*n; ++i)
   {
      if (i > n)
      {
         s[now].clear();
         f[now].clear();
         g[now].clear();
         while (!s[last].empty())
         {
            k = s[last].pop();
            t = f[last][k];
            count = g[last][k];
            k = k >> 2;
            up = getbit(k, 1);
            tmp = map[i][0];
            if (tmp == 4)
            {
               if (up == 0) add(f[now], g[now], s[now], k, t, count);
            }
            else if (tmp == 0)
            {
               if (up == 0) add(f[now], g[now],  s[now], k, t, count);
               else add(f[now], g[now],  s[now], k, t+1, count);
            }
            else
            {
               if (up == 0) add(f[now], g[now],  s[now], putbit(k, 1, tmp), t+1, count);
               else if (up == tmp) add(f[now], g[now],  s[now], putbit(k, 1, 0), t+1, count);
            }
         }
         now ^= 1;
         last ^= 1;
      }
      for (j=1; j<=len[i]; ++j)
      {
         s[now].clear();
         f[now].clear();
         g[now].clear();
         tmp = map[i][j*2-1];
         while (!s[last].empty())
         {
            k = s[last].pop();
            t = f[last][k];
            count = g[last][k];
            left = getbit(k, j);
            up = getbit(k, j+1);
            if (tmp == 4)
            {
               if (left == 0) deal1(i, j, k, 0, up, last, now, t, count);
            }
            else if (tmp == 0)
            {
               if (left == 0)
               {
                  deal1(i, j, k, 0, up, last, now, t, count);
                  deal1(i, j, putbit(k, j, 1), 1, up, last, now, t+1, count);
                  deal1(i, j, putbit(k, j, 2), 2, up, last, now, t+1, count);
                  deal1(i, j, putbit(k, j, 3), 3, up, last, now, t+1, count);
               }
               else
               {
                  deal1(i, j, k, 0, up, last, now, t+1, count);
                  deal1(i, j, putbit(k, j, 0), left, up, last, now, t+1, count);
               }
            }
            else
            {
               if (left == 0)
               {
                  deal1(i, j, k, tmp, up, last, now, t+1, count);
                  deal1(i, j, putbit(k, j, tmp), 0, up, last, now, t+1, count);
               }
               else if (left == tmp)
               {
                  deal1(i, j, putbit(k, j, 0), 0, up, last, now, t+1, count);
               }
            }
         }
         now ^= 1;
         last ^= 1;
      }
      j = len[i] + 1;
      if (i<=n)
      {
         s[now].clear();
         f[now].clear();
         g[now].clear();
         tmp = map[i][j*2-1];
         while (!s[last].empty())
         {
            k = s[last].pop();
            t = f[last][k];
            count = g[last][k];
            left = getbit(k, j);
            if (tmp == 4)
            {
               if (left == 0) add(f[now], g[now],  s[now], (k << 2), t, count);
            }
            else if (tmp == 0)
            {
               if (left == 0) add(f[now], g[now],  s[now], (k << 2), t, count);
               else add(f[now], g[now],  s[now], (k << 2), t+1, count);
            }
            else
            {
               if (left == 0) add(f[now], g[now],  s[now], (putbit(k, j, tmp) << 2), t+1, count);
               else if (left == tmp) add(f[now], g[now],  s[now], (putbit(k, j, 0) << 2), t+1, count);
            }
         }
         now ^= 1;
         last ^= 1;
      }
      else
      {
         s[now].clear();
         f[now].clear();
         g[now].clear();
         j = len[i] + 1;
         while (!s[last].empty())
         {
            k = s[last].pop();
            if (getbit(k, j) == 0) add(f[now], g[now],  s[now], (k << 2), f[last][k], g[last][k]);
         }
         now ^= 1;
         last ^= 1;
      }
   }
   if (f[last][0] == -1) printf("-1 -1\n");
   else printf("%ld %ld\n", f[last][0] - 3, g[last][0]);
}
int main()
{
	freopen("t.in", "r", stdin);
   while (scanf("%ld", &n) != EOF)
   {
      init();
      solve();
   }
   return 0;
}
