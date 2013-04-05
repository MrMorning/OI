#include <cstdio>
#include <vector>
#include <cmath>
using namespace std;
#define SQR(x) ((x) * (x))
const double EPS = 10e-8;

struct Point
{
	double x, y, z;
	Point(){}
	Point(double _x, double _y, double _z):
		x(_x), y(_y), z(_z){}
};

struct Circle
{
	Point c;
	double r;
} circ[50];

double dist(const Point &p1, const Point &p2)
{
	return sqrt(SQR(p1.x - p2.x) + SQR(p1.y - p2.y) + SQR(p1.z - p2.z));
}

Point operator+ (const Point &p1, const Point &p2)
{
	return Point(p1.x + p2.x, p1.y + p2.y, p1.z + p2.z);
}

Point operator- (const Point &p1, const Point &p2)
{
	return Point(p1.x - p2.x, p1.y - p2.y, p1.z - p2.z);
}

Point operator* (const double k, const Point &p)
{
	return Point(p.x * k, p.y * k, p.z * k);
}

double dot(const Point &p1, const Point &p2)
{
	return p1.x * p2.x + p1.y * p2.y + p1.z * p2.z;
}

void getIntersection(const Point &p1, const Point &p2, const Circle &circ, vector<Point> &output)
{
	Point delta = p2 - p1;
	double a = SQR(delta.x) + SQR(delta.y) + SQR(delta.z), 
		   b = 2 * (delta.x * (p1.x - circ.c.x) + delta.y * (p1.y - circ.c.y) + delta.z * (p1.z - circ.c.z)), 
		   c = -SQR(circ.r) + SQR(p1.x - circ.c.x) + SQR(p1.y - circ.c.y) + SQR(p1.z - circ.c.z);
	if(b * b - 4 * a * c < 0)
		return;
	if(fabs(c) < EPS)
		return;
	double tmp = sqrt(b * b - 4 * a * c);
	double res1 = (tmp - b) / (2 * a),
		   res2 = (- tmp - b) / (2 * a);
	if(res1 > 0)
		output.push_back(p1 + res1 * delta);
	if(res2 > 0)
		output.push_back(p1 + res2 * delta);
}

Point getReflection(const Point &p1, const Point &p2, const Circle &circ)
{
	Point alpha = p2 - p1, 
		  beta = p2 - circ.c;
	double k = (2 * dot(alpha, beta) / dot(beta, beta));
	return p2 + alpha - k * beta;
}

int main()
{
	freopen("t.in", "r", stdin);
	int nc;
	scanf("%d", &nc);
	for(int i = 0; i < nc; i ++)
		scanf("%lf%lf%lf%lf", &circ[i].c.x, &circ[i].c.y, &circ[i].c.z, &circ[i].r);
	Point p1, p2;
	scanf("%lf%lf%lf%lf%lf%lf", &p1.x, &p1.y, &p1.z, &p2.x, &p2.y, &p2.z);
	for(int cnt = 0; cnt < 11; cnt ++)
	{
		static vector<Point> vp;
		Point bp;
		int bc;
		bool deepin = false;
		for(int i = 0; i < nc; i ++)
		{
			vp.clear();
			getIntersection(p1, p2, circ[i], vp);
			if(vp.size())
			{
				for(int j = 0; j < (int)vp.size(); j ++)
					if(deepin == false)
						deepin = true, bp = vp[j], bc = i;
					else if(dist(bp, p1) > dist(vp[j], p1))
						bp = vp[j], bc = i;
			}
		}
		if(!deepin)
			break;
		if(cnt == 10)
		{
			printf("etc.");
			return 0;
		}
		printf("%d ", bc + 1);

		p2 = getReflection(p1, bp, circ[bc]);
		p1 = bp;
	}
}
