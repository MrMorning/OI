/*
 * $Date: Wed Oct 19 10:41:48 2011 +0800
 * $Author: csimstu
 * $Source: School Regional Team Contest, Saratov, 2011 Problem J
 * $Method: 2D closest point pair
 */
#include <cstdio>
#include <cstring>
#include <algorithm>
#include <cmath>
#define SQR(x) ((x) * (x))
using namespace std;
const int N_MAX = 100010;
struct Point{
	int x, y, k[2];
	int getPosIdx(){
		if(!k[0] && !k[1])
			return 4;
		else if(!k[0] && k[1])
			return 2;
		else if(k[0] && !k[1])
			return 3;
		else
			return 1;
	}
	int getNegIdx(){
		if(!k[0] && !k[1])
			return 1;
		else if(!k[0] && k[1])
			return 3;
		else if(k[0] && !k[1])
			return 2;
		else
			return 4;
	}
} p[N_MAX];
int X[N_MAX];
struct Info{
	int i, j;
   	double len;
	Info(int _i, int _j, double _len):
		i(_i), j(_j), len(_len){}
	bool operator< (const Info &t) const{
		return len < t.len;
	}
};
int N;

bool cmpOnX(int a, int b){
	return p[a].x < p[b].x;
}

bool cmpOnY(int a, int b){
	return p[a].y < p[b].y;
}

Info getDist(int i, int j){
	return Info(i, j, sqrt(SQR(p[i].x - p[j].x) + SQR(p[i].y - p[j].y)));
}

Info solve(int l, int r){
	if(r - l + 1 <= 3){
		Info res(-1, -1, 10e100);
		for(int i = l; i <= r; i ++)
			for(int j = i + 1; j <= r; j ++)
				res = min(res, getDist(X[i], X[j]));
		return res;
	}
	int mid = (l + r) / 2;
	Info left = solve(l, mid), 
		 right = solve(mid + 1, r);
	double delta = 2 * min(left.len, right.len);
	static int tmp[N_MAX];
	int tmpCnt = 0;
	for(int i = l; i <= r; i ++)
		if(p[X[mid]].x - delta < p[X[i]].x && p[X[i]].x < p[X[mid]].x + delta)
			tmp[tmpCnt ++] = X[i];
	sort(tmp, tmp + tmpCnt, cmpOnY);
	Info res = min(left, right);
	for(int i = 0; i < tmpCnt - 1; i ++)
		for(int j = i + 1; j < tmpCnt && j - i + 1 <= 8; j ++)
			res = min(res, getDist(tmp[i], tmp[j]));
	return res;
}

int main(){
	freopen("input.txt", "r", stdin);
	freopen("output.txt", "w", stdout);
	scanf("%d", &N);
	for(int i = 1; i <= N; i ++){
		scanf("%d%d", &p[i].x, &p[i].y);
		p[i].k[0] = p[i].x < 0, p[i].k[1] = p[i].y < 0;
		p[i].x = abs(p[i].x), p[i].y = abs(p[i].y);
	}
	for(int i = 1; i <= N; i ++)
		X[i] = i;
	sort(X + 1, X + N + 1, cmpOnX);
	Info res = solve(1, N);
	printf("%d %d %d %d\n", res.i, p[res.i].getPosIdx(), res.j, p[res.j].getNegIdx());
}
