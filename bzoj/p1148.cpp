#include <cstdio>
#include <algorithm>
#include <queue>
#include <iostream>
using namespace std;
typedef long long ll;
int n;
struct Pen {
	ll c, w;
} p[200010];

bool cmp_cw(const Pen &p1, const Pen &p2) {
	return p1.c + p1.w < p2.c + p2.w;
}

priority_queue<ll> PQ;

int main() {
	freopen("t.in", "r", stdin);
	scanf("%d", &n);
	for ( int i = 0; i < n; i ++ ) 
		scanf("%lld%lld", &p[i].c, &p[i].w);
	sort(p, p + n, cmp_cw);
	ll sumW = 0;
	int maxL = 0;
	for ( int i = 0; i < n; i ++ ) {
		if ( p[i].c >= sumW ) {
			sumW += p[i].w;
			maxL ++;
			PQ.push(p[i].w);
		} else {
			if ( p[i].w < PQ.top() ) {
				sumW += p[i].w - PQ.top();
				PQ.pop();
				PQ.push(p[i].w);
			}
		}
	}
	printf("%d\n%lld\n", maxL, sumW);
}
