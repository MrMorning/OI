#include <cstdio>
#include <iostream>
#define CEIL_DIV(a, b) ((a) % (b) == 0 ? (a) / (b) : (a) / (b) + 1)
using namespace std;
typedef long long ll;
ll POW[16];
struct Stuff {
	int pos;
   	int sum;
} stuff[10000000];
int memo[10000], memo2[10000];
int A, D, N, X;

int calcDig(int x) {
	int tmp = x;
	int res = 0;
	while ( tmp ) {
		if ( tmp % 10 == X )
			res ++;
		tmp /= 10;
	}
	return res;
}
int calcDig2(int x) {
	int res = 0;
	for ( int i = 0; i < 7; i ++ )
		res += (x / POW[i] % 10) == X;
	return res;
}

int getDig(int x) {
	return memo[x % POW[4]] + memo[x / POW[4]];
}

int getLongDig(ll x) {
	return getDig(x % POW[8]) + getDig(x / POW[8]);
}

int getDig2(int x) {
	return memo2[x % POW[4]] + memo2[x / POW[4]];
}
int main() {
	freopen("t.in", "r", stdin);
	POW[0] = 1;
	for ( int i = 1; i < 16; i ++ )
		POW[i] = POW[i - 1] * 10;

	cin >> A >> D >> N >> X;
	
	for ( int x = 0; x < 10000; x ++ ) {
		memo[x] = calcDig(x);
		memo2[x] = calcDig2(x);
	}

	int start = A % POW[7];
	stuff[start].pos = 0, stuff[start].sum = getDig2(start);
	int cur = start, lastStuff;
	while ( 1 ) {
		int pre = cur;
		cur = (cur + D) % POW[7];
		if ( cur == start ) {
			lastStuff = pre;
			break;
		}
		stuff[cur].pos = stuff[pre].pos + 1;
		stuff[cur].sum = stuff[pre].sum + getDig2(cur);
	}
	ll last = A + (ll)D * N;

	ll ans = 0, lastTail = A % POW[7];
	for ( int head = A / POW[7], tail = A % POW[7], final = last / POW[7]; head != final; head ++ ) {
		int more = CEIL_DIV(POW[7] - tail, D);
		ans += more * getDig(head);
		int next = (tail + more * D - D) % POW[7];
		int tmp;
		if ( stuff[next].pos >= stuff[tail].pos ) 
			tmp = stuff[next].sum - stuff[tail].sum + getDig2(tail);
		else
			tmp = stuff[lastStuff].sum - (stuff[tail].sum - stuff[next].sum) + getDig2(tail);
		ans += tmp;
		tail = (next + D) % POW[7];
		lastTail = tail;
	}

	for ( ll x = last / POW[7] * POW[7] + lastTail; x <= last; x += D )
		ans += getLongDig(x);
	cout << ans;
}
