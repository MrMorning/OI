#include <cstdio>
#include <algorithm>
#include <iostream>
#include <string>
#include <cassert>
using namespace std;
int n;
int parent[27], cnt[27];
char specialChar;
int find(int x) {
	return parent[x] == x ? x : parent[x] = find(parent[x]);
}
void merge(int x, int y) {
	int p = find(x), q = find(y);
	assert(p != q);
	parent[p] = q;
	cnt[q] += cnt[p];
}
string doSwap(string &src, int pos, int len) {
	string res;
	for ( int i = (pos + 1) % (n + 1), tmp = (len == n ? len - 1 : len); 
			tmp; tmp --, i = (i + 1) % (n + 1)) 
		res += src[i];
	swap(src[pos], src[(pos + len) % (n + 1)]);
	return res;
}
string work(string src, string des) {
	for ( int i = 0; i < n + 1; i ++ ) {
		parent[i] = i;
		cnt[i] = 1;
	}
	for ( int i = 0; i < n + 1; i ++ ) 
		if ( find(src[i] - 'A') == src[i] - 'A' ) {
			if ( find(src[i] - 'A') != find(des[i] - 'A') )
				merge(src[i] - 'A', des[i] - 'A');
		}
	string res;
	while ( src != des ) {
		int t;
		for ( t = 0; t < n + 1; t ++ ) 
			if ( src[t] == specialChar )
				break;
		for ( int k = (t + 1) % (n + 1), cost = 1; 
				k != t; k = (k + 1) % (n + 1), cost ++ ) {
			if ( find(src[k] - 'A') != find(src[t] - 'A') ) {
				if ( cnt[find(src[k] - 'A')] == 1 )
					continue;
				merge(src[k] - 'A', src[t] - 'A');
				res += doSwap(src, t, cost);
				break;
			} else if ( (int)des.find(src[k]) == t ) {
				res += doSwap(src, t, cost);
				break;
			}
		}
	}
	for ( int term = src.find(specialChar), 
			i = (term + 1) % (n + 1); i != term; i = (i + 1) % (n + 1) )
		res += src[i];
	return res;
}

string solve(string src, string des) {
	string ans;
	for ( int i = 0; i < n + 1; i ++ ) {
		string tstr = work(src, des);
		if ( i == 0 || tstr.size() < ans.size() ) 
			ans = tstr;
		des = des.substr(1, n) + des[0];
	}
	return ans;
}

int main() {
	scanf("%d", &n);
	string str1, str2;
	cin >> str1 >> str2;
	specialChar = (char)('A' + n);
	str1 += specialChar, str2 += specialChar;
	string ans1 = solve(str1, str2),
		ans2 = solve(str2, str1);
	cout << (ans1.size() < ans2.size() ? ans1 : ans2);
}
