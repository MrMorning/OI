#include <cstdio>
#include <cmath>
#include <algorithm>
using namespace std;
int prime[111], nPrime;
bool notprime[111];

void initPrime() {
	for ( int x = 2; x <= 100; x ++ )
		if ( !notprime[x] ) {
			prime[nPrime++] = x;
			for ( int y = x+x; y <= 100; y += x )
				notprime[y] = true;
		}
}

int check2(int b, int d) {
	int res = 0;
	for ( int i = 0; i < nPrime; i ++ ) 
		if ( d % prime[i] == 0 ) {
			if ( b % prime[i] != 0 ) return 0;
			int cntb = 0, cntd = 0;
			int tmp = b;
			while ( tmp % prime[i] == 0 ) 
				cntb++, tmp /= prime[i];
			tmp = d;
			while ( tmp % prime[i] == 0 )
				cntd++, tmp /= prime[i];
			res = max(res, (int)ceil((double)cntd/cntb));
		}
	return res;
}

bool check3(int b, int d) {
	return b % d == 1;
}

bool check11(int b, int d) {
	return b % d == d-1;
}

bool check6(int b, int d) {
	bool res = true;
	for ( int i = 0; i < nPrime; i ++ ) 
		if ( d % prime[i] == 0 ) {
			int tmp = d, cnt = 0;
			while ( tmp % prime[i] == 0 )
				cnt++, tmp /= prime[i];
			res &= check2(b, d/tmp) || check3(b, d/tmp) || check11(b, d/tmp);
		}
	return res;
}

int main() {
	freopen("t.in", "r", stdin);
	initPrime();
	int b, d;
	scanf("%d%d", &b, &d);
	if ( check2(b, d) )
		printf("2-type\n%d\n", check2(b,d));
	else if ( check3(b, d) )
		printf("3-type\n");
	else if ( check11(b, d) )
		printf("11-type\n");
	else if ( check6(b, d) )
		printf("6-type\n");
	else
		printf("7-type\n");
}
