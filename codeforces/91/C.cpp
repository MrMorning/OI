/*
 * $Date: Sat Oct 29 14:37:35 2011 +0800
 * $Author: csimstu
 * $Source: Codeforces Beta Round #91 Problem C
 * $Method: Generating the k-th n-permutation
 */
#include <cstdio>
#include <vector>
#include <algorithm>
#include <map>
using namespace std;
typedef long long ll;

vector<int> num;
map<int, bool> is_lucky;

int fac(int n){
	int res = 1;
	for(int x = 1; x <= n; x ++)
		res *= x;
	return res;
}
vector<int> get_permutation(int n, int k){
	vector<int> res(n);
	int x;
	int acc = 0;
	for(x = 1; x <= n; x ++){
		if(acc + fac(n - 1) >= k)
			break;
		acc += fac(n - 1);
	}
	res[0] = x;
	if(n == 1)
		return res;
	vector<int> tmp = get_permutation(n - 1, k - acc);
	for(int i = 0; i < n - 1; i ++)
		if(tmp[i] < x)
			res[i + 1] = tmp[i];
		else
			res[i + 1] = tmp[i] + 1;
	return res;
}

void generate(ll x){
	if(x > 1000000000)
		return;
	num.push_back((int)x);
	generate(x * 10 + 4);
	generate(x * 10 + 7);
}
int main(){
	generate(4LL);
	generate(7LL);
	sort(num.begin(), num.end());
	num.resize(unique(num.begin(), num.end()) - num.begin());
	for(int i = 0; i < (int)num.size(); i ++)
		is_lucky[num[i]] = true;
	int n, k;
	scanf("%d%d", &n, &k);
	if(k > fac(min(n, 13))){
		printf("-1\n");
		return 0;
	}
	int delta = 0;
	if(n > 13)
		delta = n - 13;
	int lb = 0, rb = (int)num.size();
	for(int mid = (lb + rb) >> 1; lb < rb - 1; mid = (lb + rb) >> 1)
		if(num[mid] <= delta)
			lb = mid;
		else
			rb = mid;
	int ans;
	if(num[lb] <= delta)
		ans = lb + 1;
	else
		ans = 0;

	vector<int> perm = get_permutation(n - delta, k);
	for(int x = delta + 1; x <= n; x ++)
		if(is_lucky.count(x) && is_lucky.count(delta + perm[x - delta - 1]))
			ans ++;
	printf("%d\n", ans);
}
