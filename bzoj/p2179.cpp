#include <cstdio>
#include <algorithm>
#include <cmath>
using namespace std;
const int N_MAX = 1 << 17;
const double PI = acos(-1);
 
struct Complex {
    double re, im;
    Complex(double _re = 0.0, double _im = 0.0):
        re(_re), im(_im){}
};
 
Complex operator + (const Complex &a, const Complex &b) {
    return Complex(a.re + b.re, a.im + b.im);
}
Complex operator - (const Complex &a, const Complex &b) {
    return Complex(a.re - b.re, a.im - b.im);
}
Complex operator * (const Complex &a, const Complex &b) {
    return Complex(a.re * b.re - a.im * b.im, a.re * b.im + a.im * b.re);
}
void brc(Complex *y, int l) {
    register int i, j, k;
    for ( i = 1, j = l / 2; i < l - 1; i ++ ) {
        if ( i < j ) swap(y[i], y[j]);
        k = l / 2;
        while ( j >= k ) {
            j -= k;
            k /= 2;
        }
        if ( j < k ) j += k;
    }
}
void fft(Complex *y, int l, double f) {
    register int h, i, j, k;
    Complex u, t;
    brc(y, l);
    for ( h = 2; h <= l; h <<= 1 ) {
        Complex wn(cos(f * 2 * PI / h), sin(f * 2 * PI / h));
        for ( j = 0; j < l; j += h ) {
            Complex w(1, 0);
            for ( k = j; k < j + h / 2; k ++ ) {
                u = y[k], t = w * y[k + h / 2];
                y[k] = u + t;
                y[k + h / 2] = u - t;
                w = w * wn;
            }
        }
    }
    if ( f == -1 )
        for ( i = 0; i < l; i ++ ) 
            y[i].re /= l;
}
char s1[N_MAX], s2[N_MAX];
Complex x1[N_MAX], x2[N_MAX];
int res[N_MAX];
int main() {
	freopen("t.in", "r", stdin);
    int n, l;
 
    scanf("%d", &n);
    l = 1;
    while ( l < n * 2 ) l <<= 1;
    scanf("%s%s", s1, s2);
    for ( int i = 0; i < n; i ++ ) {
        x1[i].re = s1[n - i - 1] - '0';
        x2[i].re = s2[n - i - 1] - '0';
    }
    fft(x1, l, 1);
    fft(x2, l, 1);
    for ( int i = 0; i < l; i ++ )
        x1[i] = x1[i] * x2[i];
    fft(x1, l, -1);
    for ( int i = 0; i < l; i ++ )
        res[i] = (int)(x1[i].re + 0.5);
    for ( int i = 0; i < l; i ++ ) {
        res[i + 1] += res[i] / 10;
        res[i] %= 10;
    }
    int m = l;
    while ( m && res[m - 1] == 0 )
        m --;
    if ( m == 0 )
        puts("0");
    else
        for ( int i = m - 1; i >= 0; i -- )
            printf("%d", res[i]);
}
