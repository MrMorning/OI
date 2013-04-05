/**************************************************************
    Problem: 2179
    User: jiakai
    Language: C++
    Result: Accepted
    Time:2944 ms
    Memory:17832 kb
****************************************************************/
 
#include <cmath>
#include <cstdio>
#include <cstdlib>
#include <cstring>
#include <algorithm>
#include <complex>
 
using namespace std;
 
namespace {
    typedef complex<double> Complex;
    const int kMaxN = 1 << 17;
    const double kPi = acos(-1.0);
    int n, m, ans[kMaxN];
    Complex a[kMaxN], b[kMaxN], c[kMaxN];
    Complex fft_a[kMaxN], fft_b[kMaxN], fft_c[kMaxN];
    Complex w[kMaxN][2];
 
    namespace read_data {
        char buf[kMaxN];
 
        void Read(Complex *des) {
            scanf("%s", buf);
            for (int i = 0; i < n; ++ i)
                des[n - i - 1] = buf[i] - '0';
        }
 
        void Main() {
            scanf("%d", &n);
            Read(a), Read(b);
        }
    }
 
    namespace get_roots {
        void Main() {
            m = 1;
            while (m < (n << 1)) m <<= 1;
            double e = 2.0 * kPi / m;
            for (int i = 0; i < m; ++ i) {
                w[i][0] = Complex(cos(e * i), sin(e * i));
                w[i][1] = 1.0 / w[i][0];
            }
        }
    }
 
    namespace calc_mul {
        void FFT(Complex *src, Complex *des, int len, int step, int sign) {
            if (len == 1) {
                des[0] = src[0];
                return;
            }
 
            Complex *lpos = des, *rpos = des + len / 2;
            FFT(src, lpos, len / 2, step * 2, sign);
            FFT(src + step, rpos, len / 2, step * 2, sign);
 
            int t_step = m / len;
            for (int i = 0, j = 0; i * 2 < len; ++ i, j += t_step) {
                Complex tl = lpos[i] + w[j][sign] * rpos[i];
                Complex tr = lpos[i] - w[j][sign] * rpos[i];
                lpos[i] = tl, rpos[i] = tr;
            }
        }
 
        void Main() {
            FFT(a, fft_a, m, 1, 0);
            FFT(b, fft_b, m, 1, 0);
            for (int i = 0; i < m; ++ i) fft_c[i] = fft_a[i] * fft_b[i];
            FFT(fft_c, c, m, 1, 1);
            double e = 1.0 / m;
            for (int i = 0; i < m; ++ i) {
                c[i] *= e;
                ans[i] = (int)(floor(c[i].real() + 0.5));
            }
            for (int i = 0; i < m - 1; ++ i) {
                ans[i + 1] += ans[i] / 10;
                ans[i] %= 10;
            }
            int len = m;
            while (!ans[len - 1]) -- len;
            for (int i = len - 1; i >= 0; -- i) printf("%d", ans[i]);
            printf("\n");
        }
    }
 
    void Solve() {
        read_data::Main();
        get_roots::Main();
        calc_mul::Main();
    }
}
 
int main() {
	freopen("t.in", "r", stdin);
    ::Solve();
    return 0;
}
