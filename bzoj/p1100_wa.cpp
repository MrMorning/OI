#include <cstdio>
#include <algorithm>
#include <cmath>
typedef long long int64;
using namespace std;
 
const int MAXN = 111111;
const long double EPS = 10e-8;
const long double PI = acos(0) * 2;
 
struct Point{
    int64 x, y;
    Point(){}
    Point(int64 _x, int64 _y):
        x(_x), y(_y){}
} p[MAXN];
 
int64 disD[MAXN];
long double disA[MAXN];
int str[4 * MAXN], pat[2 * MAXN];
int fail[2 * MAXN];
 
Point operator- (const Point &p1, const Point &p2){
    return Point(p1.x - p2.x, p1.y - p2.y);
}
 
int64 dot(const Point &p1, const Point &p2){
    return p1.x * p2.x + p1.y * p2.y;
}
 
int64 cross(const Point &p1, const Point &p2){
    return p1.x * p2.y - p1.y * p2.x;
}
 
long double cosagl(const Point &p1, const Point &p2){
    int64 tmp = dot(p1, p2);
    return (long double)tmp / (sqrt(dot(p1, p1)) * sqrt(dot(p2, p2)));
}
 
bool cmpLf(const long double &a, const long double &b){
    return fabs(a - b) < EPS ? true : false;
}
 
void solve(){
    int n;
    int ndisA = 0, ndisD = 0;
    scanf("%d", &n);
    for(int i = 0; i < n; i ++)
        scanf("%lld%lld", &p[i].x, &p[i].y);
    p[n] = p[0], p[n + 1] = p[1];
    for(int i = 0; i < n; i ++){
        int64 d = dot(p[i + 1] - p[i], p[i + 1] - p[i]);
        disD[ndisD ++] = d;
        disA[ndisA ++] = acos(cosagl(p[i] - p[i + 1], p[i + 2] - p[i + 1]));
        if(cross(p[i] - p[i + 1], p[i + 2] - p[i + 1]) < 0)
            disA[ndisA - 1] += PI;
    }
    sort(disD, disD + ndisD);
    ndisD = unique(disD, disD + ndisD) - disD;
    sort(disA, disA + ndisA);
    ndisA = unique(disA, disA + ndisA, cmpLf) - disA;
 
    for(int i = 0; i < n; i ++){
        int64 d = dot(p[i + 1] - p[i], p[i + 1] - p[i]);
        {
            int lb = 0, rb = ndisD;
            for(int mid = (lb + rb) >> 1; lb < rb - 1; mid = (lb + rb) >> 1)
                if(disD[mid] <= d)
                    lb = mid;
                else
                    rb = mid;
            str[i * 2] = lb;
        }
        long double a = acos(cosagl(p[i] - p[i + 1], p[i + 2] - p[i + 1]));
        if(cross(p[i] - p[i + 1], p[i + 2] - p[i + 1]) < 0)
            a += PI;
        {
            int lb = 0, rb = ndisA;
            for(int mid = (lb + rb) >> 1; lb < rb - 1; mid = (lb + rb) >> 1)
                if(disA[mid] < a || cmpLf(disA[mid], a))
                    lb = mid;
                else
                    rb = mid;
            str[i * 2 + 1] = lb + ndisD;
        }
    }
 
    for(int i = 0; i < 2 * n; i ++)
        pat[i] = str[2 * n - i - 1];
    for(int i = 2 * n; i < 4 * n - 1; i ++)
        str[i] = str[i - 2 * n];
 
    int nstr = 4 * n - 1, npat = 2 * n;
    fail[0] = -1;
    for(int i = 1; i < npat; i ++){
        int t = fail[i - 1];
        while(t != -1 && str[t + 1] != str[i])
            t = fail[t];
        if(str[t + 1] == str[i])
            t ++;
        fail[i] = t;
    }
     
    int ans = 0;
    for(int i = 0, j = -1; i < nstr; i ++){
        while(j != -1 && pat[j + 1] != str[i])
            j = fail[j];
        if(str[i] == pat[j + 1])
            j ++;
        if(j == npat - 1)
            ans ++;
    }
 
    printf("%d\n", ans);
}
 
int main(){
	freopen("t.in", "r", stdin);
    int TST;
    scanf("%d", &TST);
    while(TST --)
        solve();
}
