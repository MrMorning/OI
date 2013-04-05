#include <cstdio>
#include <cassert>
#include <algorithm>
using namespace std;
typedef long long ll;
const int N_MAX = 100010;
const int oo = 0x3f3f3f3f;
struct Point
{
	int x, y;
	Point(){}
	Point(int _x, int _y):
		x(_x), y(_y){}
} vtx[N_MAX];
int arr[2][N_MAX], nArr[2];
int nVtx, nBmb, nLim;

inline bool operator== (const Point &p1, const Point &p2)
{
	return p1.x == p2.x && p1.y == p2.y;
}

inline Point operator- (const Point &p1, const Point &p2)
{
	return Point(p1.x - p2.x, p1.y - p2.y);
}

inline ll cross(const Point &p1, const Point &p2)
{
	return (ll)p1.x * p2.y - (ll)p1.y * p2.x;
}

inline bool sameSign(ll a, ll b)
{
	return (a >= 0 && b >= 0) || (a <= 0 && b <= 0);
}

inline bool intersect(const Point &p1, const Point &p2, const Point &q1, const Point &q2)
{
	if(min(p1.x, p2.x) > max(q1.x, q2.x) || min(p1.y, p2.y) > max(q1.y, q2.y))
		return false;
	if(min(q1.x, q2.x) > max(p1.x, p2.x) || min(q1.y, q2.y) > max(p1.y, p2.y))
		return false;
	return sameSign(cross(q1 - p1, p2 - p1), cross(p2 - p1, q2 - p1))
		&& sameSign(cross(p1 - q1, q2 - q1), cross(q2 - q1, p2 - q1));
}

inline bool onLine(const Point &p, const Point &q1, const Point &q2)
{
	if(cross(q1 - p, q2 - p) != 0)
		return false;
	if(q1.x != q2.x)
		return min(q1.x, q2.x) <= p.x && p.x <= max(q1.x, q2.x);
	else
		return min(q1.y, q2.y) <= p.y && p.y <= max(q1.y, q2.y);
}

int main()
{
	freopen("t.in", "r", stdin);
	scanf("%d%d%d", &nVtx, &nBmb, &nLim);
	int vtxLeft = -1, vtxRight = -1;
	for(int i = 0; i < nVtx; i ++)
	{
		scanf("%d%d", &vtx[i].x, &vtx[i].y);
		if(vtxLeft == -1 || vtx[vtxLeft].x > vtx[i].x)
			vtxLeft = i;
		if(vtxRight == -1 || vtx[vtxRight].x < vtx[i].x)
			vtxRight = i;
	}
	for(int i = vtxLeft; i != vtxRight; i = (i + 1) % nVtx)
		arr[0][nArr[0] ++] = i;
	arr[0][nArr[0] ++] = vtxRight;
	for(int i = vtxRight; i != vtxLeft; i = (i + 1) % nVtx)
		arr[1][nArr[1] ++] = i;
	arr[1][nArr[1] ++] = vtxLeft;

	for(int t = 0; t < 2; t ++)
	{
		bool flag = false;
		for(int i = 0; i < nArr[t] - 1; i ++)
			if(vtx[arr[t][i]].x > vtx[arr[t][i + 1]].x)
			{
				flag = true;
				break;
			}
		if(flag)
			for(int i = 0; i < nArr[t] / 2; i ++)
				swap(arr[t][i], arr[t][nArr[t] - i - 1]);
	}

	for(int t = 0; t < 2; t ++)
		for(int i = 0; i < nArr[t] - 1; i ++)
			assert(vtx[arr[t][i]].x <= vtx[arr[t][i + 1]].x);

	int hitCnt = 0;
	while(nBmb --)
	{
		Point curBmb, faraway;
		scanf("%d%d", &curBmb.x, &curBmb.y);

		if(curBmb.x < vtx[vtxLeft].x || curBmb.x > vtx[vtxRight].x)
			continue;
		faraway.x = curBmb.x, faraway.y = oo;

		int cnt = 0;
		for(int t = 0; t < 2; t ++)
		{
			int lb = 0, rb = nArr[t] - 1;
			for(int mid = (lb + rb) >> 1; lb < rb - 1; mid = (lb + rb) >> 1)
				if(vtx[arr[t][mid]].x <= curBmb.x)
					lb = mid;
				else
					rb = mid;
			assert(vtx[arr[t][lb]].x <= curBmb.x && curBmb.x <= vtx[arr[t][lb + 1]].x);
			if(onLine(curBmb, vtx[arr[t][lb]], vtx[arr[t][lb + 1]]))
			{
				cnt = 1;
				break;
			}
			if(intersect(curBmb, faraway, vtx[arr[t][lb]], vtx[arr[t][lb + 1]]))
				cnt ++;
		}
		if(cnt == 1)
			hitCnt ++;
	}
	if(hitCnt >= nLim)
		printf("YES\n");
	else
		printf("NO\n");
//	printf("%d\n", hitCnt);
}
