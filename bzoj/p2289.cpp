#include <cstdio>
#include <cstdlib>
#include <string>
#include <cmath>
#include <ctime>
typedef long long bignum_t;

using std::pair;

const int N_CIRCLE_MAX = 100000;
const int RAND_TIMES = 500;

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

struct Point
{
	double x, y;
	Point(double _x = 0, double _y = 0):
		x(_x), y(_y){}
};

pair<Point, int> circle[N_CIRCLE_MAX];
int n_circle;

inline double dist(const Point &p1, const Point &p2)
{
	return sqrt((p1.x - p2.x) * (p1.x - p2.x) + (p1.y - p2.y) * (p1.y - p2.y));
}

inline double frand(int r)
{
	int digit = rand() % r;
	double deci = (double)rand() / RAND_MAX;
	return deci + digit;
}

bool check(const Point &p)
{
	for(int i = 0; i < n_circle; i ++)
		if(dist(circle[i].first, p) > circle[i].second)
			return false;
	return true;
}

bool solve()
{
	pair<Point, int> &min_c = circle[0];
	for(int i = 1; i < n_circle; i ++)
		if(circle[i].second < min_c.second)
			min_c = circle[i];
	for(int i = 0; i < RAND_TIMES; i ++)
	{
		double x = frand(min_c.second);
		double y = frand(min_c.second);
		int x_flag = rand() % 2 * 2 - 1;
		int y_flag = rand() % 2 * 2 - 1;
		if(check(Point(min_c.first.x + x * x_flag, min_c.first.y + y * y_flag)))
			return true;
	}
	return false;
}

int main()
{
	freopen("t.in", "r", stdin);
	freopen("t.out", "w", stdout);
	srand(42);
	READ_INT(n_circle);
	for(int i = 0, x, y, r; i < n_circle; i ++)
	{
		READ_INT(x);
		READ_INT(y);
		READ_INT(r);
		circle[i].first = Point(x, y);
		circle[i].second = r;
	}
	if(solve())
		printf("YES\n");
	else
		printf("NO\n");
}

