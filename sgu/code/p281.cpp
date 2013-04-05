#include <cstdio>
#include <iostream>
#include <string>
#include <algorithm>
#include <vector>
#include <set>
using namespace std;
string rate1[50010], rate2[50010];
int N;
vector<string> buff;
set<string> strSet;
int main() {
	ios::sync_with_stdio(false);
	cin >> N;
	for ( int i = 1; i <= N; i ++ ) 
		cin >> rate1[i];
	for ( int i = 1; i <= N; i ++ ) 
		cin >> rate2[i];

	for ( int i = 1; i <= N; i ++ ) {
		set<string>::iterator it = strSet.find(rate1[i]);
		if ( it != strSet.end() ) {
			buff.push_back(*it);
			strSet.erase(it);
		} else
			strSet.insert(rate1[i]);
		it = strSet.find(rate2[i]);
		if ( it != strSet.end() ) {
			buff.push_back(*it);
			strSet.erase(it);
		} else
			strSet.insert(rate2[i]);

		if ( !strSet.size() ) {
			sort(buff.begin(), buff.end());
			for ( vector<string>::iterator it = buff.begin();
					it != buff.end(); it ++ )
				cout << *it << '\n';
			buff.clear();
		}
	}
}
