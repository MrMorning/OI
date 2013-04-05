/**************************************************************
    Problem: 2259
    User: theo
    Language: C++
    Result: Accepted
    Time:850 ms
    Memory:8820 kb
****************************************************************/
 
#include <cstdio>
#include <cctype>
#include <algorithm>
 
const int maxn = 1000007;
struct H
{
    int v, g;
    bool operator<(const H& z) const
    {
    return v > z.v;
    }
};
H h[maxn];
int hs;
 
const H& second()
{
    if (hs == 2)
    return h[1];
    else
    return std::max(h[1], h[2]);
}
 
void getint(int& x)
{
    int c;
    while (!isdigit(c = getchar()))
    ;
    x = c - '0';
    while (isdigit(c = getchar()))
    x = x * 10 + c - '0';
}
 
int main()
{
	freopen("t.in", "r", stdin);
    int n;
    int ans = 0;
    getint(n);
    int z = ~0u >> 2;
    for (int i = 1, x; i <= n; ++i)
    {
    getint(x);
    h[hs].v = ans - (h[hs].g = -i - x);
    std::push_heap(h, h + ++hs);
    while (hs > 0 && h[0].g >= -i)
    {
        std::pop_heap(h, h + hs--);
        z = std::min(z, h[hs].v + h[hs].g + h[hs].g);
    }
    ans = z + i;
    if (hs > 0)
        ans = std::min(ans, h[0].v - i);
    }
    printf("%d\n", ans);
}
