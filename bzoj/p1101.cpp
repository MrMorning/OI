// {{{ Boilerplate Code <--------------------------------------------------

#include <algorithm>
#include <cmath>
#include <cstdio>
#include <cstdlib>
#include <cstring>
#include <string>
#include <iostream>
#include <map>
#include <set>
#include <vector>
#include <queue>
#include <cassert>

#define FOR(I, A, B)	for(int I = (A); I < (B); I ++)
#define REP(I, N)	FOR(I,0,N)
#define FOREACH(I, C) 	for(__typeof((C).begin()) I = (C).begin(); I != (C).end(); I ++)

using namespace std;

// }}}

inline int nextInt(){
	char ch = getchar();
	while(!isdigit(ch))
		ch = getchar();
	int x = 0;
	while(isdigit(ch))
		x = x * 10 + ch - '0', ch = getchar();
	return x;
}

const int VALUE_MAX = 51000;

vector<int> prime;
bool notprime[VALUE_MAX + 1];
int coef[VALUE_MAX + 1], coefsum[VALUE_MAX + 1];

void init(){
	coef[1] = 1;
	for(int x = 2; x <= VALUE_MAX; x ++){
		if(!notprime[x]){
			coef[x] = -1;
			prime.push_back(x);
		}
		for(int i = 0, lim = VALUE_MAX / x; prime[i]  <= lim; i ++){
			int y = prime[i] * x;
			notprime[y] = true;
			if(x % prime[i] == 0){
				coef[y] = 0;
				break;
			}
			coef[y] = -coef[x];
		}
	}

	for(int x = 1; x <= VALUE_MAX; x ++)
		coefsum[x] = coefsum[x - 1] + coef[x];
}

vector<int> calc(int a){
	static vector<int> memo[VALUE_MAX + 1];
	static bool done[VALUE_MAX + 1];
	if(done[a])
		return memo[a];
	done[a] = true;
	int bound = (int)sqrt(a);
	vector<int> &res = memo[a];
	for(int x = 1; x <= bound; x ++)
		res.push_back(x);
	for(int k = a / (bound + 1); k >= 1; k --){
		int tmp;
		if(a % (k + 1) == 0)
			tmp = a / (k + 1) + 1;
		else
			tmp = (int)ceil((double)a / (k + 1));
		res.push_back(tmp);
	}
	return res;
}

int main(){
	freopen("t.in", "r", stdin);
	freopen("t.out", "w", stdout);
	init();
	int TST;
	scanf("%d", &TST);
	while(TST --){
		int ans = 0;
		int a, b, d;
		a = nextInt();
		b = nextInt();
		d = nextInt();
		a /= d, b /= d;
		vector<int> V1 = calc(a),
			V2 = calc(b);
		vector<int> res(V1.size() + V2.size());
		merge(V1.begin(), V1.end(), V2.begin(), V2.end(), res.begin());
		res.resize(unique(res.begin(), res.end()) - res.begin());
		while(res.size() && res.back() > min(a, b))
			res.pop_back();
		res.push_back(min(a, b) + 1);
		for(int i = 1; i < (int)res.size(); i ++){
			int x = res[i - 1];
			int tmp = (a / x) * (b / x);
			ans += tmp * (coefsum[res[i] - 1] - coefsum[x - 1]);
		}
		printf("%d\n", ans);
	}
}
