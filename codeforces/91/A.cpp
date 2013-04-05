/*
 * $Date: Sat Oct 29 14:35:25 2011 +0800
 * $Author: csimstu
 * $Source: Codeforces Beta Round #91 Problem A
 * $Method: ...
 */
#include <cstdio>
#include <vector>
#include <algorithm>
using namespace std;
typedef long long ll;
#ifdef unix
#define LL_FMT "%lld"
#else
#define LL_FMT "%I64d"
#endif
vector<ll> num;
void generate(ll x){
	if(x > 10000000000LL)
		return;
	num.push_back(x);
	generate(x * 10 + 4);
	generate(x * 10 + 7);
}
int main(){
	generate(4LL);
	generate(7LL);
	sort(num.begin(), num.end());
	num.resize(unique(num.begin(), num.end()) - num.begin());
	ll l, r;
	scanf(LL_FMT LL_FMT, &l, &r);
	int N = num.size(), st;
	for(st = 0; st < N && num[st] < l; st ++);
	if(st == N){
		printf("%d\n", 0);
		return 0;
	}
	ll res = 0;
	for(; st < N && num[st] <= r; st ++){
		res += (ll)(num[st] - l + 1) * num[st];
		l = num[st] + 1;
	}
	if(l <= r)
		res += (ll)(r - l + 1) * num[st];
	printf(LL_FMT "\n", res);
}
