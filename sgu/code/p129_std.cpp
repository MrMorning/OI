#include <iostream>
#include <algorithm>
#include <stdio.h>
#include <math.h>

using namespace std;

double abs(const double &x)
{
    if (x < 0)
        return -x;
    else
        return x;
}

struct dot{
    int x, y;
    inline dot(const int &a, const int &b){
        x = a;  y = b;
    }
    inline dot(){
        x = y = 0;
    }
};
    inline dot operator- (const dot &a, const dot &b){
        return dot(a.x-b.x, a.y-b.y);
    }
    inline long long crsmult(const dot &a, const dot &b){
        return (long long)a.x*b.y - (long long)b.x*a.y;
    }

dot g[500];
int n;

void init()
{
    cin >> n;
    for (int i=1; i<=n; i++)
        cin >> g[i].x >> g[i].y;
}

bool cmp(const dot &a, const dot &b)
{
    return (crsmult(a-g[1], b-g[1]) > 0);
}

void graham()
{
    int id = 1;
    for (int i=2; i<=n; i++)
        if (g[i].y < g[id].y || (g[i].y == g[id].y && g[i].x < g[id].x) )
            id = i;
    dot t = g[1];  g[1] = g[id];  g[id] = t;
    g[n+1] = g[1];
    sort(g+2, g+n+1, cmp);
    g[0] = g[n];
}

double work(dot p, dot q)
{
    double len = sqrt((p.x-q.x)*(p.x-q.x) + (p.y-q.y)*(p.y-q.y));
    double l1, l2, l3, l4, li;
    int cnto = 0, crsed = 0;
    bool cor = false;
    for (int i=1; i<=n; i++)
    {
        long long t1 = crsmult(g[i+1]-g[i], p-g[i]);
        long long t2 = crsmult(g[i+1]-g[i], q-g[i]);
        if (t1 == 0 && t2 == 0)
            return 0;
        if (t1 < 0 || t2 < 0)
            cnto ++;
        if ((t1<0 && t2>0) || (t1>0 && t2<0))
        {
            long long u1 = crsmult(q-p, g[i]-p);
            long long u2 = crsmult(q-p, g[i+1]-p);
            if (u1<=0 && u2>0 || u1>=0 && u2<0)
            {
                if (u1 == 0)
                {
                    long long b1 = crsmult(g[i]-g[i-1], p-g[i-1]);
                    long long b2 = crsmult(g[i]-g[i-1], q-g[i-1]);
                    if ( (t1<0 && b1>0 || t1>0 && b1<0) && (t2<0 && b2>0 || t2>0 && b2<0) )
                        cor = true;
                }
                long long s1 = abs(t1);
                long long s2 = abs(t2);
                l3 = len/(s1+s2)*s1;
                l4 = len/(s1+s2)*s2;
                if (crsed == 0)
                {
                    l1 = l3;  l2 = l4;
                    if (t1 > 0)
                        li = l1;
                    else
                        li = l2;
                }
                crsed ++;
            }
        }
    }
    if (crsed == 0)
        if (cnto == 0)
            return len;
        else
            return 0;
    if (crsed == 1)
        if (cor)
            return 0;
        else
            return li;
    if (crsed == 2)
        return abs(l1-l3);
}

int main()
{
    freopen("t.in", "r", stdin);
    //freopen("sgu129.out", "w", stdout);
    init();
    graham();
    int m;
    cin >> m;
    cout.precision(2);
    for (int i=1; i<=m; i++)
    {
        dot p, q;
        cin >> p.x >> p.y >> q.x >> q.y;
        cout << fixed << work(p, q) << endl;
    }
    return 0;
}
