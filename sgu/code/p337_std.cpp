//暴力枚举，没意思

#include <cmath>
#include <cstdio>
#include <string>
#include <cstring>
#include <cstdlib>
#include <iostream>
#include <algorithm>
using namespace std;

const int    maxN    = 4000 + 10;
int            N;
int            K;
int            mm;
char        a        [maxN];
char        ans        [maxN];

void Init()
{
    scanf("%d", &K);
    scanf("%s", a);
    N = strlen(a);
    mm = (N - 1) / 2;
    for(int i = 0; i < N; ++ i) a[i + N] = a[i];
}

void Update(int t, int l)
{
    if (ans[0] == '\0') {
        for(int i = t; i < t + l; ++ i)
        ans[i - t] = a[i];
    } else {
        for(int i = t; i < t + l; ++ i)
            if (ans[i - t] != a[i]) {
                if (ans[i - t] > a[i]) {
                    for(int i = t; i < t + l; ++ i)
                        ans[i - t] = a[i];
                }
                break;
            }
    }
}

void print(int d)
{
    int    now(0);
    for(int i = 0; i < d; ++ i)
        now += (a[i] != a[i + d]);
    if (now <= K) Update(0, d * 2);
    for(int i = d; i < N + d; ++ i) {
        now -= (a[i] != a[i - d]);
        now += (a[i] != a[i + d]);
        if (now <= K) Update(i - d + 1, d * 2);
    }
    //cout << d << endl;
    cout << ans << endl;
    //system("pause");
    exit(0);
}

void Check(int d)
{
    int    now(0), key = 0;
    for(int i = 0; i < d; ++ i)
        now += (a[i] != a[i + d]);
    if (now <= K) key = 1;
    for(int i = d; i < N + d; ++ i) {
        now -= (a[i] != a[i - d]);
        now += (a[i] != a[i + d]);
        if (now <= K) key = 1;
    }
    if (key) print(d);
}

void Solve()
{
    for(int i = mm; i > 0; -- i)
        Check(i);
    printf("\n");
}

int main()
{
	freopen("t.in", "r", stdin);
    Init();
    Solve();

    return 0;
}
