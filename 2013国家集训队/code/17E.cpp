#include <cstdio>
#include <cstring>
#include <cassert>
#include <iostream>
using namespace std;
typedef long long ll;

const int kNMax = 2000010;
const int kMod = 51123987;
int rad1[kNMax], rad2[kNMax];
char str[kNMax];
ll f1[kNMax], f2[kNMax], g1[kNMax], g2[kNMax], s2[kNMax];
int n;

void init1() {
	int p = -1;
	for ( int i = 0; i < n; i ++ ) {
		if ( p != -1 && p + rad1[p] > i ) 
			rad1[i] = min(rad1[2*p-i], rad1[p]-(p-(2*p-i)));
		else rad1[i] = 0;
		while ( i+rad1[i] < n && i-rad1[i] >= 0 && str[i+rad1[i]]==str[i-rad1[i]] ) rad1[i]++;
		if ( p == -1 || i+rad1[i] > p+rad1[p] )
			p = i;
		//[i-rad[i]+1, i+rad[i]-1]
		f1[i-rad1[i]+1]++, f1[i+1]--;
		f2[i]++, f2[i+rad1[i]]--;
	}
}

void init2() {
	int p = -1;
	for ( int i = 0; i < n; i ++ ) {
		if ( p != -1 && p + rad2[p] > i ) 
			rad2[i] = min(rad2[2*p-i], rad2[p]-(p-(2*p-i)));
		else rad2[i] = 0;
		while ( i+rad2[i]+1 < n && i-rad2[i] >= 0 && str[i+rad2[i]+1]==str[i-rad2[i]] ) rad2[i]++;
		if ( p == -1 || i+rad2[i] > p+rad2[p] )
			p = i;
		//[i-rad[i]+1, i+rad[i]]
		f1[i-rad2[i]+1]++, f1[i+1]--;
		f2[i+1]++, f2[i+rad2[i]+1]--;
	}
}


int main() {
	freopen("t.in", "r", stdin);
	scanf("%d", &n);
	scanf("%s", str);
	init1();
	init2();
	//check();
	g1[0] = f1[0], g2[0] = f2[0], s2[0] = g2[0];
	for ( int i = 1; i < n; i ++ ) {
		g1[i] = g1[i-1]+f1[i], g2[i] = g2[i-1]+f2[i];
		s2[i] = s2[i-1] + g2[i];
	}
	ll totpal = 0;
	for ( int i = 0; i < n; i ++ )
		totpal += rad1[i];
	for ( int i = 0; i < n-1; i ++ )
		totpal += rad2[i];
	ll ans = 0;
   	if ( totpal & 1 ) 
		ans = totpal % kMod * ((totpal-1) / 2 % kMod) % kMod;
	else
		ans = (totpal / 2) % kMod * ((totpal-1) % kMod) % kMod;
	for ( int i = 1; i < n; i ++ )
		ans = ((ans-s2[i-1]*g1[i])%kMod+kMod)%kMod;
	printf("%d\n", (int)ans);
}
