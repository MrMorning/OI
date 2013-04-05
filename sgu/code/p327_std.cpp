#include <cmath>
#include <cstdio>
#include <string>
#include <cstring>
#include <cstdlib>
#include <iostream>
#include <algorithm>
using namespace std;

const int    maxN    = 20;
const int    maxS    = (1 << 14);
const int    INF        = 1000000000;
int            N;
int            S;
int            ans        = INF;
int            a1, a2;
int            tot;
int            f        [maxS][maxN][2];
int            g1        [maxS][maxN][2];
int            g2        [maxS][maxN][2];
int            p        [maxN][maxN][2][2];
char         a        [maxN][100];
bool        flag    [maxN];
int            len        [maxN];
int            to        [maxN];
int            back    [maxS];
int            out1    [maxN * 2];
int            out2    [maxN * 2];
char        bingo    [maxS];

bool Contain(int x, int y)
{
    for(int i = 0; i < len[y]; ++ i) {
        bool key = 1;
        for(int j = 0; j < len[x]; ++ j)
            if (a[y][i + j] == '\0' || a[y][i + j] != a[x][j]) {
                key = false;
                break;
            }
        if (key) return true;
    }
    
    for(int i = 0; i < len[y]; ++ i) {
        bool key = 1;
        for(int j = 0; j < len[x]; ++ j)
            if (i - j < 0 || a[y][i - j] != a[x][j]) {
                key = false;
                break;
            }
        if (key) return true;
    }
    
    return false;
}

void Match(int x, int y)
{
    char t1[100];
    char t2[100];
    for(int i = 0; i <= len[x]; ++ i) t1[i] = a[x][i];
    for(int i = 0; i <= len[y]; ++ i) t2[i] = a[y][i];
    
    p[x][y][0][0] = p[x][y][0][1] = len[x];
    for(int i = len[y] - 1; i >= 0; -- i) {
        bool key = true;
        for(int j = 0; j <= i; ++ j) {
            if (len[x] - 1 - j < 0 || t1[len[x] - 1 - j] != t2[i - j]) {
                key = false;
                break;
            }
        }
        if (key) {
            p[x][y][0][0] = len[x] - i - 1;
            break;
        }
    }
    for(int i = 0; i < len[y]; ++ i) {
        bool key = true;
        for(int j = 0; j <= len[y] - 1 - i; ++ j) {
            if (j > len[x] || t1[j] != t2[i + j]) {
                key = false;
                break;
            }
        }
        if (key) {
            p[x][y][0][1] = len[x] - len[y] + i;
            break;
        }
    }
    
    for(int i = 0; i < len[y]; ++ i) t2[i] = a[y][len[y] - 1 - i];
    p[x][y][1][0] = p[x][y][1][1] = len[x];
    
    for(int i = len[y] - 1; i >= 0; -- i) {
        bool key = true;
        for(int j = 0; j <= i; ++ j) {
            if (len[x] - 1 - j < 0 || t1[len[x] - 1 - j] != t2[i - j]) {
                key = false;
                break;
            }
        }
        if (key) {
            p[x][y][1][0] = len[x] - i - 1;
            break;
        }
    }
    for(int i = 0; i < len[y]; ++ i) {
        bool key = true;
        for(int j = 0; j <= len[y] - 1 - i; ++ j) {
            if (j > len[x] || t1[j] != t2[i + j]) {
                key = false;
                break;
            }
        }
        if (key) {
            p[x][y][1][1] = len[x] - len[y] + i;
            break;
        }
    }
}

void Init()
{
    scanf("%ld", &N);
    for(int i = 1; i <= N; ++ i) {
        scanf("%s", a[i]);
        len[i] =  strlen(a[i]);
    }
    
    for(int i = 1; i <= N; ++ i)
        for(int j = 1; j <= N; ++ j)
            if (! flag[j] && i != j && Contain(i, j)) {
                flag[i] = true;
                break;
            }
    
    int tot = 0;
    for(int i = 1; i <= N; ++ i)
        if (! flag[i]) {
            len[++ tot] = len[i];
            for(int j = 0; j <= len[i]; ++ j)
                a[tot][j] = a[i][j];
        }
    N = tot;
    
    for(int i = 1; i <= N; ++ i)
        for(int j = 1; j <= N; ++ j)
            Match(i, j);
    
    for(int i = 1; i <= N; ++ i) {
        to[i] = 1 << (i - 1);
        back[to[i]] = i;
    }
    S = (1 << N) - 1;
}

void DFS(int s, int v)
{
    if (f[s][v][0] >= 0) return;
    
    f[s][v][0] = f[s][v][1] = INF;
    
    int    tmp = s, ns = s - to[v];
    int k, u, opt;
    while (tmp) {
        k = tmp & (- tmp);
        
        if ((u = back[k]) != v) {
            DFS(ns, u);
            
            opt = f[ns][u][0] + p[v][u][0][0] * 2;
            if (opt < f[s][v][0]) {
                f[s][v][0] = opt;
                g1[s][v][0] = u;
                g2[s][v][0] = 0;
            }
            opt = f[ns][u][1] + p[v][u][1][0] * 2;
            if (opt < f[s][v][0]) {
                f[s][v][0] = opt;
                g1[s][v][0] = u;
                g2[s][v][0] = 1;
            }
            
            opt = f[ns][u][0] + p[v][u][1][1] * 2;
            if (opt < f[s][v][1]) {
                f[s][v][1] = opt;
                g1[s][v][1] = u;
                g2[s][v][1] = 0;
            }
            opt = f[ns][u][1] + p[v][u][0][1] * 2;
            if (opt < f[s][v][1]) {
                f[s][v][1] = opt;
                g1[s][v][1] = u;
                g2[s][v][1] = 1;
            }
        }
        
        tmp -= k;
    }
}

void output(int s, int v, int st)
{
    out1[++ tot] = v;
    out2[tot] = st;
    
    if (g1[s][v][st]) {
        int ns = s - to[v];
        int    t1 = g1[s][v][st];
        int t2 = g2[s][v][st];
        output(ns, t1, t2);
    }
}

void Solve()
{
    memset(f, -1, sizeof(f));
    for(int i = 1; i <= N; ++ i) {
        f[to[i]][i][0] = len[i] + p[i][i][1][0];
        f[to[i]][i][1] = len[i] + p[i][i][1][1];
    }
    
    for(int i = 1; i <= N; ++ i) {
        DFS(S, i);
        if (f[S][i][0] < ans) {
            ans = f[S][i][0];
            a1 = i;
            a2 = 0;    
        }
        if (f[S][i][1] < ans) {
            ans = f[S][i][1];
            a1 = i;
            a2 = 1;
        }
    }
    
    tot = 0;
    output(S, a1, a2);
    
    int now(0);
    if (out2[1])
        for(int i = len[out1[1]] - 1; i >= 0; -- i)
            bingo[now ++] = a[out1[1]][i];
    else
        for(int i = 0; i < len[out1[1]]; ++ i)
            bingo[now ++] = a[out1[1]][i];
    
    int x;
    for(int i = 2; i <= tot; ++ i) {
        if (out2[i]) {
            x = p[out1[i]][out1[i - 1]][out2[i - 1] ^ 1][0];
            for(int j = x - 1; j >= 0; -- j)
                bingo[now ++] = a[out1[i]][j];
        } else {
            x = p[out1[i]][out1[i - 1]][out2[i - 1]][1];
            for(int j = len[out1[i]] - x; j < len[out1[i]]; ++ j)
                bingo[now ++] = a[out1[i]][j];
        }
    }
    
    if (out2[tot])
        x = len[out1[tot]] - p[out1[tot]][out1[tot]][1][1];
    else
        x = len[out1[tot]] - p[out1[tot]][out1[tot]][1][0];
    
    x = now - x - 1;
    while (x >= 0) {
        bingo[now ++] = bingo[x];
        -- x;
    }
    
    bingo[now] = '\0';
	printf("%d\n", strlen(bingo));
    //printf("%s\n", bingo);
}

int main()
{
	freopen("t.in", "r", stdin);
    Init();
    Solve();

    return 0;
}
