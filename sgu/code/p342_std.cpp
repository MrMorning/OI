#include <cmath>
#include <cstdio>
#include <string>
#include <cstring>
#include <cstdlib>
#include <iostream>
#include <algorithm>
using namespace std;

const int    maxN    = 100000;
int            N;
int            B;
int            a        [maxN];
int            c        [maxN];
long long    f        [maxN][2];
int            tmp        [maxN];

void Init()
{
    char ch;
    int now(0);
    while ((ch = getchar()) != '\n'){
        a[++ now] = ch - '0';
    }
    scanf("%ld", &B);
    
    if (B == 1) {
        for(int i = 1; i <= now; ++ i) printf("%ld", a[i]);
        puts("");
        exit(0);
    }
    
    a[0] = now;
    N = now;
    for(int i = 1; i <= N / 2; ++ i) swap(a[i], a[N + 1 - i]);
}

void Solve()
{
    int now(0), top(0);
    while (a[0] != 0) {
        now = 0;
        for(int i = a[0]; i > 0; -- i) {
            now = now * 10 + a[i];
            a[i] = now / B;
            now = now % B;
        }
        c[++ top] = now;
        while (! a[a[0]] && a[0]) -- a[0];
    }
    
    f[1][0] = c[1];
    f[1][1] = B - c[1];
    for(int i = 2; i <= top;  ++ i) {
        f[i][0] = min(f[i - 1][0], f[i - 1][1] + 1) + c[i];
        f[i][1] = min(f[i - 1][0] + B - c[i], f[i - 1][1] + B - (c[i] + 1));
    }
    
    cout << min(f[top][0], f[top][1] + 1) << endl;
}

int main()
{
	freopen("t.in", "r", stdin);
    Init();
    Solve();

    return 0;
}
