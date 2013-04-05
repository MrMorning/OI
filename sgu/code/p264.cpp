#include <cstdio>
#include <iostream>
#include <string>
#include <queue>
#include <map>
using namespace std;
int N;
string manName[888], womanName[888];
string manPrefer[888][888], womanPrefer[888][888];
int mlove[888][888], wlove[888][888];
int wife[888], husband[888];
queue<int> Q;
map<string, int> manId, womanId;

int main() {
	ios::sync_with_stdio(false);
	cin >> N;
	for ( int i = 1; i <= N; i ++ ) {
		cin >> manName[i];
		manId[manName[i]] = i;
		for ( int j = 1; j <= N; j ++ ) 
			cin >> manPrefer[i][j];
	}
	for ( int i = 1; i <= N; i ++ ) {
		cin >> womanName[i];
		womanId[womanName[i]] = i;
		for ( int j = 1; j <= N; j ++ ) 
			cin >> womanPrefer[i][j];
	}

	for ( int i = 1; i <= N; i ++ )
		for ( int j = 1; j <= N; j ++ )
			mlove[i][j] = womanId[manPrefer[i][j]];

	for ( int i = 1; i <= N; i ++ )
		for ( int j = 1; j <= N; j ++ )
			wlove[i][manId[womanPrefer[i][j]]] = N - j + 1;


	for ( int i = 1; i <= N; i ++ )
		Q.push(i);
	while ( !Q.empty() ) {
		int man = Q.front(); Q.pop();
		for ( int i = 1; i <= N; i ++ ) {
			if ( mlove[man][i] != 0 ) {
				int woman = mlove[man][i];
				mlove[man][i] = 0;
				int pre = husband[woman];
				if ( pre == 0 ) {
					wife[man] = woman;
					husband[woman] = man;
					break;
				} else {
					if ( wlove[woman][man] > wlove[woman][pre] ) {
						Q.push(pre);
						wife[man] = woman;
						husband[woman] = man;
						break;
					}
				}
			}
		}
	}

	cout << "YES\n";
	for ( int i = 1; i <= N; i ++ ) 
		cout << manName[i] << ' ' << womanName[wife[i]] << '\n'; 
}
