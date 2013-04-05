#include <cstdio>
#include <iostream>
#include <cstring>
using namespace std;

typedef long long ll;

#define GET(s, i) (((s)>>(i))&1)

bool done1[33][2][2], done2[33][2][2], done3[33][2][2];
ll memo1[33][2][2], memo2[33][2][2], memo3[33][2][2];
ll lim;
int n;

ll dp1(int, int, int);
ll dp2(int, int, int);
ll dp3(int, int, int);

ll dp1(int i, int s1, int s2) {
	if ( done1[i][s1][s2] ) return memo1[i][s1][s2];
	done1[i][s1][s2] = true;
	ll &ret = memo1[i][s1][s2] = 0;
	int hd = GET(lim, n-1-i), rr = GET(lim, i);

	if ( i*2+1 == n ) {
		//can't place one
		if ( !s1 ) ret = 1;
		else if ( s2 ) ret = hd != 0;
		else { //s1 && !s2
			ret = 1;
		}
	} else if ( i*2 == n ) {
		if ( s1 && s2 ) ret = 0;
		else ret ++;
	} else {
		//place two zeros
		ret += dp2(i+1, s1&&hd==0, 0>rr||(0==rr&&s2));
		//place a zero at head and a one at rear
		ret += dp3(i+1, s1&&hd==0, 1>rr||(1==rr&&s2));
	}
	return ret;
}

ll dp2(int i, int s1, int s2) {
	if ( done2[i][s1][s2] ) return memo2[i][s1][s2];
	done2[i][s1][s2] = true;
	ll &ret = memo2[i][s1][s2] = 0;
	int hd = GET(lim, n-1-i), rr = GET(lim, i);

	if ( i*2+1 == n ) {
		if ( !s1 ) ret = 2;
		else if ( s2 ) ret = hd != 0;
		else { //s1 && !s2
			ret = hd+1;
		}
	} else if ( i*2 == n ) {
		if ( s1 && s2 ) ret = 0;
		else ret ++;
	} else {
		//place two same digits
		for ( int x = 0; x <= (s1?hd:1); x ++ )
			ret += dp2(i+1, s1&&hd==x, x>rr||(x==rr&&s2));
		//place zero at head and a one at rear
		int ns1 = s1&&hd==0, ns2 = 1>rr||(1==rr&&s2);
		if ( !ns1 ) ret += 1LL<<(n-2*(i+1));
		else ret += ((lim>>(i+1))&((1LL<<(n-2*(i+1)))-1)) +1;
		if ( ns1 && ns2 ) ret--;
	}
	return ret;
}

ll dp3(int i, int s1, int s2) {
	if ( done3[i][s1][s2] ) return memo3[i][s1][s2];
	done3[i][s1][s2] = true;
	ll &ret = memo3[i][s1][s2] = 0;
	int hd = GET(lim, n-1-i), rr = GET(lim, i);

	if ( i*2+1 == n ) {
		//can't place one
		if ( !s1 ) ret = 1;
		else if ( s2 ) ret = hd != 0;
		else { //s1 && !s2
			ret = 1;
		}
	} else if ( i*2 == n ) {
		if ( s1 && s2 ) ret = 0;
		else ret ++;
	} else {
		//place a zero and an one
		ret += dp3(i+1, s1&&hd==0, 1>rr||(1==rr&&s2));
		if ( !s1 || hd==1 )
			ret += dp3(i+1, s1&&hd==1, 0>rr||(0==rr&&s2));

		//place two zeros
		int ns1 = s1&&hd==0, ns2 = 0>rr||(0==rr&&s2);
		if ( !ns1 ) ret += 1LL<<(n-2*(i+1));
		else ret += ((lim>>(i+1))&((1LL<<(n-2*(i+1)))-1)) +1;
		if ( ns1 && ns2 ) ret--;
	}
	return ret;
}

void output(ll x, int n) {
	for ( int i = 0; i < n; i ++ )
		cout << GET(x, n-i-1);
	cout << '\n';
}

ll work(ll LIM) {
	lim = LIM;
	memset(done1, 0, sizeof(done1));
	memset(done2, 0, sizeof(done2));
	memset(done3, 0, sizeof(done3));
	return dp1(0, 1, 0);
}

int main() {
	freopen("t.in", "r", stdin);
	ll rank;
	cin >> n >> rank;
	rank++;
	ll lb = 0, rb = (1LL << n)-1;
	for ( ll mid = (lb + rb) / 2; lb < rb - 1; mid = (lb + rb) / 2 ) {
		if ( work(mid) >= rank ) rb = mid;
		else lb = mid;
	}
	if ( work(rb) == rank ) output(rb, n);
	else printf("-1\n");
}
