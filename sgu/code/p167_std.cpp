#include <iostream>
#include <fstream>
#include <math.h>
#include <bitset>
#include <vector>

using namespace std;

const int oo = 1000000000;

struct Trec{
    int l, r, p, q;
    inline void edit(const int& a, const int& b, const int& c, const int& d)
    {
        l = a;
        r = b;
        p = c;
        q = d;
    }
};

int n, m, o;
int g[16][16];
int sum[16][16];

void init()
{
    cin >> n >> m >> o;
    for (int i=1; i<=n; i++)
        for (int j=1; j<=m; j++)
        {
            cin >> g[i][j];
            sum[i][j] = sum[i][j-1] + g[i][j];
        }
}

int f[16][16][16][226][2][2];
int ans=-oo;
Trec rec[16][16][16][226][2][2];

void getans(int i, int l, int r, int o, int p, int q)
{
    Trec &rc = rec[i][l][r][o][p][q];
    if (rc.l != -1)
        getans(i-1, rc.l, rc.r, o-(r-l+1), rc.p, rc.q);
    for (int j=l; j<=r; j++)
        cout << i << ' ' << j << endl;
}

void work()
{
    for (int i=0; i<=n; i++)
        for (int l=1; l<=m; l++)
            for (int r=1; r<=m; r++)
                for (int s=0; s<=o; s++)
                    for (int p=0; p<=1; p++)
                        for (int q=0; q<=1; q++)
                            f[i][l][r][s][p][q] = -oo;
    for (int i=1; i<=n; i++)
    {
        for (int l=1; l<=m; l++)
            for (int r=l; r<=m; r++)
                for (int k=r-l+1; k<=o; k++)
                {
                    if (k == (r-l+1))
                    {
                        f[i][l][r][k][0][0] = sum[i][r] - sum[i][l-1];
                        rec[i][l][r][k][0][0].l = -1;
                        continue;
                    }
                    for (int l_=1; l_<=m; l_++)
                        for (int r_=l_; r_<=m; r_++)
                        {

if (l <= l_ && r_ <= r)
{
    if (f[i-1][l_][r_][k-(r-l+1)][0][0]+sum[i][r]-sum[i][l-1] > f[i][l][r][k][0][0])
    {
        f[i][l][r][k][0][0] = f[i-1][l_][r_][k-(r-l+1)][0][0]+sum[i][r]-sum[i][l-1];
        rec[i][l][r][k][0][0].edit(l_, r_, 0, 0);
    }
}
if (l <= l_ && l_ <= r && r <= r_)
{
    for (int p=0; p<=0; p++)
        for (int q=0; q<=1; q++)
            if (f[i-1][l_][r_][k-(r-l+1)][p][q]+sum[i][r]-sum[i][l-1] > f[i][l][r][k][0][1])
            {
                f[i][l][r][k][0][1] = f[i-1][l_][r_][k-(r-l+1)][p][q]+sum[i][r]-sum[i][l-1];
                rec[i][l][r][k][0][1].edit(l_, r_, p, q);
            }
}
if (l_ <= l && l <= r_ && r_ <= r)
{
    for (int p=0; p<=1; p++)
        for (int q=0; q<=0; q++)
            if (f[i-1][l_][r_][k-(r-l+1)][p][q]+sum[i][r]-sum[i][l-1] > f[i][l][r][k][1][0])
            {
                f[i][l][r][k][1][0] = f[i-1][l_][r_][k-(r-l+1)][p][q]+sum[i][r]-sum[i][l-1];
                rec[i][l][r][k][1][0].edit(l_, r_, p, q);
            }
}
if (l_ <= l && r <= r_)
{
    for (int p=0; p<=1; p++)
        for (int q=0; q<=1; q++)
            if (f[i-1][l_][r_][k-(r-l+1)][p][q]+sum[i][r]-sum[i][l-1] > f[i][l][r][k][1][1])
            {
                f[i][l][r][k][1][1] = f[i-1][l_][r_][k-(r-l+1)][p][q]+sum[i][r]-sum[i][l-1];
                rec[i][l][r][k][1][1].edit(l_, r_, p, q);
            }
}
                        }

                }
    }
    int ai, al, ar, ap, aq;
    for (int i=1; i<=n; i++)
        for (int l=1; l<=m; l++)
            for (int r=l; r<=m; r++)
                for (int p=0; p<=1; p++)
                    for (int q=0; q<=1; q++)
                        if (f[i][l][r][o][p][q] > ans)
                        {
                            ans = f[i][l][r][o][p][q];
                            ai = i;
                            al = l;
                            ar = r;
                            ap = p;
                            aq = q;
                        }
    cout << "Oil : " << ans << endl;
    //getans(ai, al, ar, o, ap, aq);
}

int main()
{
	freopen("t.in", "r", stdin);
    init();
    work();
    return 0;
}
