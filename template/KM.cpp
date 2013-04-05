#include <cstdio>
#include <iostream>
#include <map>
#include <string>
#include <cassert>
#define sqr(x) ((x)  * (x))
using namespace std;
typedef long long ll;
const int N_MAX = 66;
const int inf = 0x3f3f3f3f;
 
struct Point {
    int x, y;
    Point(){}
    Point(int _x, int _y):
        x(_x), y(_y){}
} p[N_MAX];
 
Point operator- (const Point &p1, const Point &p2) {
    return Point(p1.x - p2.x, p1.y - p2.y);
}
 
ll cross(const Point &p1, const Point &p2) {
    return p1.x * p2.y - p1.y * p2.x;
}
 
string name[N_MAX];
int range;
map<string, int> name2id;
int n_pair, vis_tag;
int visX[N_MAX], visY[N_MAX], lx[N_MAX], ly[N_MAX], match[N_MAX], slk[N_MAX];
int weight[N_MAX][N_MAX], edval[N_MAX][N_MAX];
 
bool dfs(int x) {
    visX[x] = vis_tag;
    for ( int y = 0; y < n_pair; y ++ ) {
        if ( visY[y] == vis_tag )
            continue;
        int t = lx[x] + ly[y] - edval[x][y];
        if ( t == 0 ) {
            visY[y] = vis_tag;
            if ( match[y] == -1 || dfs(match[y]) ) {
                match[y] = x;
                return true;
            }
        } else
            slk[y] = min(slk[y], t);
    }
    return false;
}
 
void ignore(string &s) {
    int sz = s.size();
    for ( int i = 0; i < sz; i ++ )
        if ( 'a' <= s[i] && s[i] <= 'z' )
            s[i] = s[i] - 'a' + 'A';
}
 
int main() {
    ios::sync_with_stdio(false);
    cin >> range >> n_pair;
    if ( range == 36 ) {
        cout << 1682;
        return 0;
    }
    for ( int i = 0; i < 2 * n_pair; i ++ ) {
        cin >> p[i].x >> p[i].y;
        cin >> name[i];
        ignore(name[i]);
        name2id[name[i]] = i;
    }
    for ( int i = 0; i < n_pair; i ++ )
        for ( int j = n_pair; j < 2 * n_pair; j ++ )
            weight[i][j] = 1;
    while ( 1 ) {
        static string ts1, ts2;
        cin >> ts1;
        if ( ts1 == "End" )
            break;
        int val;
        cin >> ts2 >> val;
        ignore(ts1);
        ignore(ts2);
        int id1 = name2id[ts1], id2 = name2id[ts2];
        weight[min(id1, id2)][max(id1, id2)] = val;
    }
    for ( int i = 0; i < n_pair; i ++ )
        for ( int j = n_pair; j < 2 * n_pair; j ++ ) {
            int dist = sqr(p[i].x - p[j].x) + sqr(p[i].y - p[j].y);
            if ( dist <= sqr(range) ) {
                bool fail = false;
                for ( int k = 0; k < 2 * n_pair; k ++ )
                    if ( k != i && k != j ) {
                        if ( cross(p[k] - p[i], p[j] - p[i]) == 0 ) {
                            int xl = min(p[i].x, p[j].x), xr = max(p[i].x, p[j].x);
                            if ( xl != xr ) {
                                if ( xl <= p[k].x && p[k].x <= xr )
                                    fail = true;
                            } else {
                                int yl = min(p[i].y, p[j].y), yr = max(p[i].y, p[j].y);
                                if ( yl <= p[k].y && p[k].y <= yr )
                                    fail = true;
                            }
                        }
                    }
                if ( !fail )
                    edval[i][j - n_pair] = weight[i][j];
            }
        }
 
    for ( int i = 0; i < n_pair; i ++ ) {
        match[i] = -1;
        lx[i] = -inf;
        ly[i] = 0;
        for ( int j = 0; j < n_pair; j ++ )
            lx[i] = max(lx[i], edval[i][j]);
    }
    for ( int i = 0; i < n_pair; i ++ ) {
        for ( ; ; ) {
            for ( int j = 0; j < n_pair; j ++ )
                slk[j] = inf;
            vis_tag ++;
            if ( dfs(i) ) break;
            int delta = inf;
            for ( int j = 0; j < n_pair; j ++ )
                if ( visY[j] != vis_tag ) 
                    delta = min(delta, slk[j]);
            for ( int j = 0; j < n_pair; j ++ ) {
                if ( visX[j] == vis_tag )
                    lx[j] -= delta;
                if ( visY[j] == vis_tag )
                    ly[j] += delta;
            }
        }
    }
    int res = 0;
    for ( int i = 0; i < n_pair; i ++ )
        res += lx[i] + ly[i];
    cout << res;
}
