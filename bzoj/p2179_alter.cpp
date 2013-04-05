#include <cstdio>
#include <cmath>
#include <cstring>
typedef double val_t;

const int kLenMax = 1 << 21;
const val_t PI = acos(-1);

struct Complex {
	val_t re, mi;
	Complex(){}
	Complex(val_t _re, val_t _mi):
		re(_re), mi(_mi){}
};

Complex operator+ (const Complex &a, const Complex &b) {
	return Complex(a.re + b.re, a.mi + b.mi);
}

Complex operator* (const Complex &a, const Complex &b) {
	return Complex(a.re * b.re - a.mi * b.mi, a.re * b.mi + a.mi * b.re);
}

Complex coef[kLenMax], res[kLenMax], x1[kLenMax], x2[kLenMax], tmp[kLenMax];
int ans[kLenMax];

void fft(int delta, int step, int size, int flag) {
	if ( size == 1 ) { res[delta] = coef[delta]; return; }
	fft(delta, step * 2, size / 2, flag);
	fft(delta + step, step * 2, size / 2, flag);
	Complex acc(1, 0), pri(cos(flag * 2 * PI / size), sin(flag * 2 * PI / size));
	for ( int i = 0; i < size / 2; i ++, acc = acc * pri ) 
		tmp[delta + i * step] = res[delta + i * step * 2] + acc * res[delta + step + i * step * 2];
	for ( int i = size / 2; i < size; i ++, acc = acc * pri ) 
		tmp[delta + i * step] = res[delta + (i - size / 2) * step * 2] + acc * res[delta + step + (i - size / 2) * step * 2];
	for ( int i = 0; i < size; i ++ ) res[delta + i * step] = tmp[delta + i * step];
}
char s1[kLenMax + 5], s2[kLenMax + 5];
int main() {
	freopen("t.in", "r", stdin);
//	freopen("t.out", "w", stdout);

	int n;
	scanf("%d", &n);
	int l = 1;
	while ( l < n ) l <<= 1;
	scanf("%s%s", s1, s2);
	for ( int i = 0; i < n; i ++ ) {
		x1[i].re = s1[n - i - 1] - '0';
		x2[i].re = s2[n - i - 1] - '0';
	}
	memcpy(coef, x1, sizeof(coef));
	fft(0, 1, l, 1);
	memcpy(x1, res, sizeof(res));
	memcpy(coef, x2, sizeof(coef));
	fft(0, 1, l, 1);
	memcpy(x2, res, sizeof(res));
	for ( int i = 0; i < l; i ++ )
		x1[i] = x1[i] * x2[i];
	memcpy(coef, x1, sizeof(coef));
	fft(0, 1, l, -1);
	memcpy(x1, res, sizeof(res));
	for ( int i = 0; i < l; i ++ )
		ans[i] = (int)(x1[i].re / l + 0.5);
	for ( int i = 0; i < l; i ++ ) {
		ans[i + 1] += ans[i] / 10;
		ans[i] %= 10;
	}
	int m = l;
	while ( m && ans[m - 1] == 0 ) m --;
	if ( m == 0 ) puts("0");
	else for ( int i = m - 1; i >= 0; i -- )
		printf("%d ", ans[i]);
}
