#include <vector>
#include <list>
#include <map>
#include <set>
#include <queue>
#include <deque>
#include <stack>
#include <bitset>
#include <algorithm>
#include <functional>
#include <numeric>
#include <utility>
#include <sstream>
#include <iostream>
#include <iomanip>
#include <cstdio>
#include <cmath>
#include <cstdlib>
#include <ctime>
#include <cassert>
#include <cstring>
#define FOREACH(I, C) for(__typeof((C).begin()) I = (C).begin(); I != (C).end(); I++)

using namespace std;
typedef long long ll;

const double kInf = 1e100;
const double kEps = 1e-12;
const int kEdgeMax = 500000;
const int kVtxMax = 2000;
inline double sgn(double x) {
	if ( fabs(x) < kEps ) return 0;
	if ( x > 0 ) return 1;
	return -1;
}


struct Edge {
	double cap;
	int to;
	Edge *next, *inv;
} edge[kEdgeMax], *begin[kVtxMax];
int edgePtr=0;
int dist[kVtxMax];

Edge *makeEdge(int u, int v, double cap) {
	Edge *e = edge + edgePtr++;
	e->to = v, e->next = begin[u], e->cap = cap;
	return begin[u] = e;
}

void addEdge(int u, int v, double cap) {
	Edge *e1 = makeEdge(u, v, cap),
		 *e2 = makeEdge(v, u, 0);
	e1->inv = e2, e2->inv = e1;
}

bool relable(int src, int des, int nVtx) {
	static int Q[kVtxMax];
	memset(dist, -1, sizeof(int) * nVtx);
	dist[src] = 0;
	int qt = 0;
	Q[qt++] = src;
	for ( int qh = 0; qh < qt; qh ++ ) {
		int u = Q[qh];
		for ( Edge *e = begin[u]; e; e = e->next )
			if ( sgn(e->cap) ) {
				int v = e->to;
				if ( dist[v] != -1 )
					continue;
				dist[v] = dist[u] + 1;
				Q[qt++] = v;
			}
	}
	return dist[des]!=-1;
}

double findAug(int cur, int des, double flow) {
	if ( cur == des )
		return flow;
	double res = 0;
	Edge *e;
	for ( e = begin[cur]; e; e = e->next )
		if ( sgn(e->cap) ) {
			int v = e->to;
			if ( dist[v] == dist[cur] + 1 ) {
				double tmp = findAug(v, des, min(flow, e->cap));
				res += tmp;
				flow -= tmp;
				e->cap -= tmp;
				e->inv->cap += tmp;
				if ( !sgn(flow) )
					break;
			}
		}
	if ( !e )
		dist[cur] = -1;
	return res;
}

double dinic(int src, int des, int nVtx) {
	double res = 0;
	while ( relable(src, des, nVtx) ) 
		res += findAug(src, des, kInf);
	return res;
}

int nStar, nShip;

struct Point {
	double x, y;
	Point(){}
	Point(double _x, double _y):
		x(_x), y(_y){}
	double mod() {
		return sqrt(x*x+y*y);
	}
	Point unit() {
		return Point(x / mod(), y / mod());
	}
} star[22];

Point operator- (const Point &p1, const Point &p2) {
	return Point(p1.x - p2.x, p1.y - p2.y);
}

Point operator+ (const Point &p1, const Point &p2) {
	return Point(p1.x + p2.x, p1.y + p2.y);
}

Point operator* (const Point &p1, double k) {
	return Point(p1.x * k, p1.y * k);
}

struct Ship {
	Point st, en;
	double speed, rad, energy;
} ship[22];

int starIdx[22], shipIdx[22];

double solve();

class EllysDeathStars {
	public:
		double getMax(vector <string> stars, vector <string> ships) {
			nStar = stars.size(), nShip = ships.size();
			for ( int i = 0; i < nStar; i ++ ) {
				stringstream ss(stars[i]);
				ss >> star[i].x >> star[i].y;
			}
			for ( int i = 0; i < nShip; i ++ ) {
				stringstream ss(ships[i]);
				ss >> ship[i].st.x >> ship[i].st.y >> ship[i].en.x
					>> ship[i].en.y >> ship[i].speed >> ship[i].rad >> ship[i].energy;
			}
			return solve();
		}
};

vector<double> calcSplit(Point star, Ship ship) {
	Point dirSpd = (ship.en - ship.st).unit() * ship.speed;
	double lb = 0, rb = (ship.en - ship.st).mod() / ship.speed;
	while ( rb - lb > kEps ) {
		double lmid = lb + (rb - lb) / 3,
			   rmid = rb - (rb - lb) / 3;
		if ( (star - (ship.st + dirSpd * lmid)).mod()
				< (star - (ship.st + dirSpd * rmid)).mod() )
			rb = rmid;
		else
			lb = lmid;
	}
	double closestTime = lb;
	Point closestPoint = ship.st + dirSpd * lb;
	double closestDist = (star - closestPoint).mod();

	vector<double> res;

	if ( sgn(closestDist - ship.rad) <= 0 ) {
		if ( sgn(closestDist - ship.rad) == 0 )
			res.push_back(lb);
		else {
			double lb = 0, rb = closestTime;
			if ( sgn(lb - rb) != 0 ) {
				for ( double mid = (lb + rb) / 2; rb - lb > kEps; 
						mid = (lb + rb) / 2 ) 
					if ( (star - (ship.st + dirSpd * mid)).mod() < ship.rad )
						rb = mid;
					else
						lb = mid;
				res.push_back(lb);
			}
			lb = closestTime, rb = (ship.en - ship.st).mod() / ship.speed;
			if ( sgn(lb - rb) != 0 ) {
				for ( double mid = (lb + rb) / 2; rb - lb > kEps; 
						mid = (lb + rb) / 2 ) 
					if ( (star - (ship.st + dirSpd * mid)).mod() < ship.rad )
						lb = mid;
					else
						rb = mid;
				res.push_back(lb);
			}
		}
	}
	return res;
}

double solve() {
	int nVtx = 2;
	int src = nVtx - 2, des = nVtx - 1;
	for ( int i = 0; i < nStar; i ++ ) {
		starIdx[i] = nVtx++;
		addEdge(src, starIdx[i], kInf);
	}
	for ( int i = 0; i < nShip; i ++ ) {
		shipIdx[i] = nVtx++;
		addEdge(shipIdx[i], des, ship[i].energy);
	}

	for ( int i = 0; i < nStar; i ++ ) {
		static double ev[kVtxMax];
		int evCnt = 0;
		ev[evCnt++] = 0;
		for ( int j = 0; j < nShip; j ++ ) {
			vector<double> tmp = calcSplit(star[i], ship[j]);
			FOREACH(it, tmp)
				ev[evCnt++] = *it;
			ev[evCnt++] = (ship[j].en - ship[j].st).mod() / ship[j].speed;
		}
		sort(ev, ev + evCnt);
		evCnt = unique(ev, ev + evCnt) - ev;
		for ( int j = 0; j < evCnt-1; j ++ ) {
			int interIdx = nVtx++;
			addEdge(starIdx[i], interIdx, ev[j+1]-ev[j]);
			for ( int k = 0; k < nShip; k ++ ) {
				double stamp = (ev[j+1]+ev[j])/2;
				if ( sgn(stamp - ((ship[k].en - ship[k].st).mod() / ship[k].speed)) > 0 )
					continue;
				if ( sgn((star[i] - (ship[k].st + (ship[k].en - ship[k].st).unit() * ship[k].speed * stamp)).mod() - ship[k].rad) < 0 )
					addEdge(interIdx, shipIdx[k], kInf);
			}
		}
	}
	return dinic(src, des, nVtx);
}


// BEGIN KAWIGIEDIT TESTING
// Generated by KawigiEdit 2.1.4 (beta) modified by pivanof
bool KawigiEdit_RunTest(int testNum, vector <string> p0, vector <string> p1, bool hasAnswer, double p2) {
	cout << "Test " << testNum << ": [" << "{";
	for (int i = 0; int(p0.size()) > i; ++i) {
		if (i > 0) {
			cout << ",";
		}
		cout << "\"" << p0[i] << "\"";
	}
	cout << "}" << "," << "{";
	for (int i = 0; int(p1.size()) > i; ++i) {
		if (i > 0) {
			cout << ",";
		}
		cout << "\"" << p1[i] << "\"";
	}
	cout << "}";
	cout << "]" << endl;
	EllysDeathStars *obj;
	double answer;
	obj = new EllysDeathStars();
	clock_t startTime = clock();
	answer = obj->getMax(p0, p1);
	clock_t endTime = clock();
	delete obj;
	bool res;
	res = true;
	cout << "Time: " << double(endTime - startTime) / CLOCKS_PER_SEC << " seconds" << endl;
	if (hasAnswer) {
		cout << "Desired answer:" << endl;
		cout << "\t" << p2 << endl;
	}
	cout << "Your answer:" << endl;
	cout << "\t" << answer << endl;
	if (hasAnswer) {
		res = fabs(p2 - answer) <= 1e-9 * max(1.0, fabs(p2));
	}
	if (!res) {
		cout << "DOESN'T MATCH!!!!" << endl;
	} else if (double(endTime - startTime) / CLOCKS_PER_SEC >= 2) {
		cout << "FAIL the timeout" << endl;
		res = false;
	} else if (hasAnswer) {
		cout << "Match :-)" << endl;
	} else {
		cout << "OK, but is it right?" << endl;
	}
	cout << "" << endl;
	return res;
}
int main() {
	bool all_right;
	all_right = true;

	vector <string> p0;
	vector <string> p1;
	double p2;

	/*{
		// ----- test 0 -----
		string t0[] = {"2 2"};
		p0.assign(t0, t0 + sizeof(t0) / sizeof(t0[0]));
		string t1[] = {"1 1 5 3 2 1 2"};
		p1.assign(t1, t1 + sizeof(t1) / sizeof(t1[0]));
		p2 = 0.894427190999916;
		all_right = KawigiEdit_RunTest(0, p0, p1, true, p2) && all_right;
		// ------------------
	}

	{
		// ----- test 1 -----
		string t0[] = {"12 10","7 5"};
		p0.assign(t0, t0 + sizeof(t0) / sizeof(t0[0]));
		string t1[] = {"10 10 12 10 1 1 3","6 1 8 10 1 2 3","3 6 8 2 5 3 1","42 42 42 42 6 6 6"};
		p1.assign(t1, t1 + sizeof(t1) / sizeof(t1[0]));
		p2 = 4.983770744659944;
		all_right = KawigiEdit_RunTest(1, p0, p1, true, p2) && all_right;
		// ------------------
	}

	{
		// ----- test 2 -----
		string t0[] = {"5 77","60 50","10 46","22 97","87 69"};
		p0.assign(t0, t0 + sizeof(t0) / sizeof(t0[0]));
		string t1[] = {"42 17 66 11 5 7 13","10 10 20 20 3 3 3","13 15 18 9 4 1 2","99 71 63 81 19 4 60","27 34 56 43 11 3 12"};
		p1.assign(t1, t1 + sizeof(t1) / sizeof(t1[0]));
		p2 = 0.0;
		all_right = KawigiEdit_RunTest(2, p0, p1, true, p2) && all_right;
		// ------------------
	}*/

	{
		// ----- test 3 -----
		string t0[] = {"141 393","834 847","568 43","18 228","515 794","167 283","849 333","719 738","434 261","613 800","127 340","466 938","598 601"};
		p0.assign(t0, t0 + sizeof(t0) / sizeof(t0[0]));
		string t1[] = {"410 951 472 100 337 226 210","713 352 677 908 731 687 300","191 41 337 92 446 716 213","598 889 446 907 148 650 203","168 556 470 924 344 369 198","300 182 350 936 737 533 45","410 871 488 703 746 631 80","270 777 636 539 172 103 56","466 906 522 98 693 77 309","768 698 846 110 14 643 14","755 724 664 465 263 759 120"};
		p1.assign(t1, t1 + sizeof(t1) / sizeof(t1[0]));
		p2 = 31.965770956316362;
		all_right = KawigiEdit_RunTest(3, p0, p1, true, p2) && all_right;
		// ------------------
	}

	if (all_right) {
		cout << "You're a stud (at least on the example cases)!" << endl;
	} else {
		cout << "Some of the test cases had errors." << endl;
	}
	return 0;
}
// END KAWIGIEDIT TESTING

//Powered by KawigiEdit 2.1.4 (beta) modified by pivanof!
