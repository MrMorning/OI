#include <cstdio>
#include <algorithm>
using namespace std;

const int REC_MAX = 1010;

struct Point {
	int x, y;
	Point(){}
	Point(int _x, int _y):
		x(_x), y(_y){}
	bool operator== (const Point &p) const {
		return x == p.x && y == p.y;
	}
};

Point operator- (const Point &p1, const Point &p2) {
	return Point(p1.x - p2.x, p1.y - p2.y);
}

int cross(const Point &p1, const Point &p2) {
	return p1.x * p2.y - p1.y * p2.x;
}

int dot(const Point &p1, const Point &p2) {
	return p1.x * p2.x + p1.y * p2.y;
}

struct Cake {
	Point p[4];
	Point candle[2], core;
	int area;
	void read() {
		for ( int i = 0; i < 4; i ++ ) {
			scanf("%d%d", &p[i].x, &p[i].y);
			p[i].x *= 2, p[i].y *= 2;
		}

		for ( int i = 1; i < 4; i ++ ) {
			swap(p[2], p[i]);
			if ( p[2].x + p[0].x == p[1].x + p[3].x
					&& p[2].y + p[0].y == p[1].y + p[3].y )
				break;
			swap(p[2], p[i]);
		}

		core.x = (p[0].x + p[2].x) / 2;
		core.y = (p[0].y + p[2].y) / 2;
			

		for ( int t = 0; t < 2; t ++ ) {
			scanf("%d%d", &candle[t].x, &candle[t].y);
			candle[t].x *= 2, candle[t].y *= 2;
		}

		area = 0;
		for ( int i = 0; i < 4; i ++ ) 
			area += cross(p[i], p[(i + 1) % 4]);
		area = abs(area) / 2;
	}

	bool canCut() {
		if ( candle[0] == core || candle[1] == core || candle[0] == candle[1] )
			return false;
		if ( cross(core - candle[0], candle[1] - candle[0]) != 0 )
			return true;
		if ( dot(candle[0] - core, candle[1] - core) > 0 )
			return false;
		else
			return true;
	}
} rec[REC_MAX];

bool compArea(const Cake &A, const Cake &B) {
	return A.area > B.area;
}

int main() {
	int nRec, nCho;

	scanf("%d%d", &nRec, &nCho);
	for ( int i = 0; i < nRec; i ++ )
		rec[i].read();
	sort(rec, rec + nRec, compArea);
	int balance = rec[nCho - 1].area;
	int sumArea = 0, succCnt = 0, failCnt = 0, greaterCnt = 0;
	for ( int i = 0; i < nRec; i ++ )
		if ( rec[i].area > balance ) {
			if ( rec[i].canCut() ) 
				sumArea += rec[i].area;
			greaterCnt ++;
		} else if ( rec[i].area == balance ) {
			if ( rec[i].canCut() )
				succCnt ++;
			else
				failCnt ++;
		}
	int optArea = sumArea + min(succCnt, nCho - greaterCnt) * balance;
	int pesArea = sumArea + max(0, nCho - greaterCnt - failCnt) * balance;
	printf("%.3lf %.3lf\n", (double)pesArea / 8, (double)optArea / 8);
}
