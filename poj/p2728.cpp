#include <cstdio>
#include <cmath>
#include <cassert>
#include <algorithm>
using namespace std;

const int V_MAX = 1100;
const double oo = 1000000000;

#define ABS(x) ((x) < 0 ? -(x) : (x))
#define SQR(x) ((x) * (x))

struct Village
{
	int x, y, z;
	Village(){}
	Village(int _x, int _y, int _z):
		x(_x), y(_y), z(_z){}
} vil[V_MAX];

int vilNum, edgeCnt;
double dist[V_MAX];
bool used[V_MAX];

#define GET_WEIGHT(u, v) 

double calcG(double lamda)
{
	double res = 0;
	for(int i = 0; i < vilNum; i ++)
		dist[i] = oo, used[i] = false;
	dist[0] = 0;

	for(int i = 0; i < vilNum; i ++)
	{
		int k = -1;
		double minDist = oo;
		for(int j = 0; j < vilNum; j ++)
			if(!used[j] && dist[j] < minDist)
				minDist = dist[j], k = j;
		assert(k != -1);
		used[k] = true;
		res += minDist;
		for(int j = 0; j < vilNum; j ++)
			if(!used[j])
				dist[j] = min(dist[j], ABS(vil[j].z - vil[k].z) - lamda * sqrt(SQR(vil[j].x - vil[k].x) + SQR(vil[j].y - vil[k].y)));
	}
	return res;
}

int main()
{
	freopen("t.in", "r", stdin);
	while(1)
	{
		scanf("%d", &vilNum);
		if(vilNum == 0)
			break;
		for(int i = 0; i < vilNum; i ++)
			scanf("%d%d%d", &vil[i].x, &vil[i].y, &vil[i].z);
		double lb = 0, rb = 1000;
		for(double mid = (lb + rb) / 2; fabs(rb - lb) > 0.0001; mid = (lb + rb) / 2)
		{
			if(calcG(mid) < 0)
				rb = mid;
			else
				lb = mid;
		}
		printf("%.3lf\n", lb);
	}
}
