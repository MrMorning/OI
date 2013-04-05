#include <cstdio>
#include <algorithm>
#include <string>
#include <iostream>
using namespace std;
string str1, str2;

int main() {
	cin >> str1 >> str2;
	string ts(str2.size(), 0);
	str1 = ts + str1 + ts;
	int ans = 0x3f3f3f3f;
	for ( int i = 0; i < (int)str1.size() - (int)str2.size() + 1; i ++ ) {
		string ts2 = str1.substr(i, str2.size());
		int cnt = 0;
		for ( int j = 0; j < (int)ts2.size(); j ++ )
			cnt += ts2[j] != str2[j];
		ans = min(ans, cnt);
	}
	cout << ans;
}
