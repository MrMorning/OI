#include <cmath>
#include <cstdio>
#include <string>
#include <cstring>
#include <cstdlib>
#include <iostream>
#include <algorithm>
using namespace std;

const int    d        [4][2] = {{-1, 0}, {1, 0}, {0, -1}, {0, 1}};
int            X, Y, cx, cy, tx, ty;
char         ch[10];
int            ans(0);

void Work1()
{
    int ans(0), tmp;
    if (ch[0] == 'C') cy += (ty - cy) / (abs(ty - cy)), ans = 1;
    if (cy == ty) {
        printf("1\n");
        exit(0);
    }
    
    tmp = abs(ty - cy);
    if (cy > ty) {
        ans += (ty - 1) * 2;
        if (tmp & 1) ans += tmp * 2 - 1;
        else ans += tmp * 2 - 2;
    } else {
        ans += (Y - ty) * 2;
        if (tmp & 1) ans += tmp * 2 - 1;
        else ans += tmp * 2 - 2;
    }
    cout << ans << endl;
    exit(0);
}

void Work2()
{
    int ans(0);
    if (ch[0] == 'C') cx += (tx - cx) / (abs(tx - cx)), ans = 1;
    if (cx == tx) {
        printf("1\n");
        exit(0);
    }
    
    int tmp = abs(cx - tx);
    if (cx > tx) {
        ans += (tx - 1) * 2;
        if (tmp & 1) ans += tmp * 2 - 1;
        else ans += tmp * 2 - 2;
    } else {
        ans += (X - tx) * 2;
        if (tmp & 1) ans += tmp * 2 - 1;
        else ans += tmp * 2 - 2;
    }
    cout << ans << endl;
    exit(0);
}

int    Get(int cx, int cy)
{
    int ans(0), tmp;
    int    c [4] = {0};
    int Dx = abs(cx - tx);
    int Dy = abs(cy - ty);
    if (Dx == Dy) {
        if (tx < cx) {
            if (ty < cy) c[0] = 1;
            else c[1] = 1;
        } else {
            if (ty < cy) c[2] = 1;
            else c[3] = 1;
        }
    } else if (Dx < Dy) {
        if (ty < cy) c[0] = c[2] = 1;
            else c[1] = c[3] = 1;
    } else {
        if (tx < cx) c[0] = c[1] = 1;
            else c[2] = c[3] = 1;
    }
    
    if (c[0]) {
        tmp = abs(cx - 1) + abs(cy - 1);
        ans = max(ans, tmp * 2 - 2);
    }
    if (c[1]) {
        tmp = abs(cx - 1) + abs(cy - Y);
        ans = max(ans, tmp * 2 - 2);
    }
    if (c[2]) {
        tmp = abs(cx - X) + abs(cy - 1);
        ans = max(ans, tmp * 2 - 2);
    }
    if (c[3]) {
        tmp = abs(cx - X) + abs(cy - Y);
        ans = max(ans, tmp * 2 - 2);
    }
    return ans;
}

void Solve()
{
    int    tmp;
    freopen("t.in", "r", stdin);
    cin >> X >> Y >> cx >> cy >> tx >> ty;
    scanf("%s", ch);
    if (X == 1) Work1();
    if (Y == 1) Work2();
    
    tmp = abs(cx - tx) + abs(cy - ty);
    if ((tmp & 1) && ch[0] == 'T' || (!(tmp & 1)) && ch[0] == 'C') {
        printf("0\n");
        exit(0);
    }
    
    int px, py;
    if (ch[0] == 'T') ans = Get(cx, cy);
    else {
        if (abs(cx - tx) + abs(cy - ty) == 1) ans = 1;
        else
        ans = 2000000000;
        for (int c = 0; c < 4; ++ c) {
            px = cx + d[c][0];
            py = cy + d[c][1];
            if (px > 0 && px <= X && py > 0 && py <= Y)
                ans = min(ans, Get(px, py) + 1);
        }
    }
    cout << ans << endl;
    //system("pause");
}

int main()
{
    Solve();

    return 0;
}
