#include <cstdio>
#include <cstring>
#include <complex>
#include <cmath>
using namespace std;
typedef complex<double> complex_t;
const double kPi = acos(-1);
const int kLenMax = 1<<17;

complex_t res[kLenMax], tmp[kLenMax], coef[kLenMax], res1[kLenMax], res2[kLenMax];
int ans[kLenMax];
int num1[kLenMax], num2[kLenMax];
char str1[kLenMax], str2[kLenMax];

void fft(int delta, int step, int size, int flag) {
	if ( size == 1 ) {
		res[delta] = coef[delta]; 
		return;
	}
	fft(delta, step*2, size/2, flag);
	fft(delta+step, step*2, size/2, flag);
	complex_t acc(1, 0), pri(cos(flag*2*kPi/size), sin(flag*2*kPi/size));
	for ( int i = 0; i < size/2; i ++, acc = acc*pri ) 
		tmp[delta+i*step] = res[delta+i*step*2] + acc*res[delta+step+i*step*2];
	for ( int i = size/2; i < size; i ++, acc = acc*pri ) 
		tmp[delta+i*step] = res[delta+(i-size/2)*step*2] + acc*res[delta+step+(i-size/2)*step*2];
	for ( int i = 0; i < size; i ++ ) res[delta+i*step] = tmp[delta+i*step];
}

int main() {
	freopen("t.in", "r", stdin);
	scanf("%s%s", str1, str2);
	int n1 = strlen(str1), n2 = strlen(str2);
	for ( int i = 0; i < n1; i ++ )
		num1[i] = str1[n1-i-1]-'0';
	for ( int i = 0; i < n2; i ++ )
		num2[i] = str2[n2-i-1]-'0';
	int n;
	for ( int i = 0; ; i ++ ) {
		if ( (1<<i) >= n1 && (1<<i) >= n2) {
			n = 1<<i;
			break;
		}
	}
	n <<= 1;
	for ( int i = 0; i < n; i ++ ) coef[i] = num1[i];
	fft(0, 1, n, 1);
	memcpy(res1, res, sizeof(res));
	for ( int i = 0; i < n; i ++ ) coef[i] = num2[i];
	fft(0, 1, n, 1);
	memcpy(res2, res, sizeof(res));

	for ( int i = 0; i < n; i ++ ) coef[i] = res1[i] * res2[i];
	fft(0, 1, n, -1);

	for ( int i = 0; i < n; i ++ )
		ans[i] = (int)round(res[i].real()/n);
	for ( int i = 0; i < 2*n; i ++ )
		if ( ans[i] >= 10 ) {
			ans[i+1] += ans[i] / 10;
			ans[i] %= 10;
		}
	for ( int i = 2*n-1; i >= 0; i-- )
		if ( ans[i] > 0 ) {
			for ( int j = i; j >= 0; j -- )
				printf("%d", ans[j]);
			break;
		}
}
