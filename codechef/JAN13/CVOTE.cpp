#include <cstdio>
#include <map>
#include <cstring>
#include <iostream>
#define foreach(I, C) for(__typeof(C.begin()) I = (C.begin()); I != C.end(); I++)
using namespace std;

map<string, int> cntName, cntCount;
map<string, string> belong;
int n, m;
pair<string, int> ans1, ans2;

int main() {
	freopen("t.in", "r", stdin);
	ios::sync_with_stdio(false);
	cin >> n >> m;
	for ( int i = 0; i < n; i ++ ) {
		string name, country;
		cin >> name >> country;
		cntName[name] = 0;
		cntCount[country] = 0;
		belong[name] = country;
	}
	while ( m -- ) {
		string name;
		cin >> name;
		cntName[name]++;
		cntCount[belong[name]]++;
	}
	foreach(it, cntName) {
		if ( it->second > ans1.second || (it->second == ans1.second
					&& it->first < ans1.first) )
			ans1 = *it;
	}
	foreach(it, cntCount) {
		if ( it->second > ans2.second || (it->second == ans2.second
					&& it->first < ans2.first) )
			ans2 = *it;
	}
	printf("%s\n%s\n", ans2.first.c_str(), ans1.first.c_str());
}
