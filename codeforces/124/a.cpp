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

#define FOREACH(I, C) 	for(__typeof((C).begin()) I = (C).begin(); I != (C).end(); I ++)

using namespace std;

typedef long long ll;

// }}}
char str[100010];
vector<int> vec[26];
int main(){
//	freopen("t.in", "r", stdin);
	scanf("%s", str);
	int n = strlen(str);
	for ( int i = 0; i < n; i ++ )
		vec[str[i] - 'a'].push_back(i);
	int cur = 0;
	while ( cur < n ) {
		for ( int x = 'z'; x >= 'a'; x -- ) {
			vector<int>::iterator it = lower_bound(vec[x-'a'].begin(),
					vec[x-'a'].end(), cur);
			if ( it == vec[x-'a'].end() )
				continue;
			for ( ; it != vec[x-'a'].end(); it++ )
				printf("%c", x);
			it--;
			cur=*it+1;
		}
	}
}
