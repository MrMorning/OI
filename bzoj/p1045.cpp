#include <cstdio>
#include <algorithm>
#define ABS(x) ((x)<0?(-(x)):(x))
typedef long long ll;

const int BUFFER_LEN = 1024 * 1024 * 5;
static char buffer[BUFFER_LEN];
char *ptr = buffer, *buf_end = ptr + 1;
#define PTR_NEXT() \
{ \
	ptr ++; \
	if (ptr == buf_end) \
	{ \
		ptr = buffer; \
		buf_end = buffer + fread(buffer, 1, BUFFER_LEN, stdin); \
	} \
}
#define READ_INT(_x_) \
{ \
	while ((*ptr < '0' || *ptr > '9') && *ptr != '-') \
	PTR_NEXT(); \
	bool _nega_ = false; \
	if (*ptr == '-') \
	{ \
		_nega_ = true; \
		PTR_NEXT(); \
	} \
	int register _n_ = 0; \
	while (*ptr >= '0' && *ptr <= '9') \
	{ \
		_n_ = _n_ * 10 + *ptr - '0'; \
		PTR_NEXT(); \
	} \
	if (_nega_) \
	_n_ = - _n_; \
	(_x_) = (_n_); \
}

const int MAXN = 1000001;
int n, a[MAXN];
ll sum, f[MAXN], ans;
ll select(int l, int r, int k)
{
	int pos = rand() % (r - l + 1) + l;
	ll tmp = f[pos]; f[pos] = f[l]; f[l] = tmp;
	int i = l, j = r;
	while(i < j)
	{
		while(f[j] > tmp && i < j) -- j;
		if(i < j) f[i ++] = f[j];
		while(f[i] < tmp && i < j) ++ i;
		if(i < j) f[j --] = f[i];
	}
	f[i] = tmp;
	if(k == i) return tmp;
	else if(k < i) return select(l, i - 1, k);
	else return select(i + 1, r, k);
}
int main()
{
	READ_INT(n);
	if(n == 1) printf("0\n");
	else
	{
		for(int i = 1; i <= n; i ++)
		{
			READ_INT(a[i]);
			sum += a[i];
		}
		ll avg = sum / n;
		for(int i = 1; i <= n; i ++)
			a[i] -= avg, f[i] = f[i - 1] + a[i];
		int tmp = select(1, n, n / 2 + 1);
		for(int i = 1; i <= n; i ++)
			ans += ABS(f[i] - tmp);
		printf("%lld\n", ans);
	}
}
