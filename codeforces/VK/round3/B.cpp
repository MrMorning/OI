
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
const int N_MAX = 1000010;
int n1, n2, a1[N_MAX], appear[N_MAX], str[N_MAX * 2];
int res = 0;

int main(){
	freopen("t.in", "r", stdin);
	scanf("%d%d", &n1, &n2);
	for ( int i = 1; i <= n1; i ++ ) 
		scanf("%d", &a1[i]);
	for ( int i = 1; i <= n2; i ++ ) {
		int x;
		scanf("%d", &x);
		appear[x] = i;
	}
	for ( int i = 1; i <= n1; i ++ ) 
		str[i] = appear[a1[i]];
	for ( int i = n1 + 1; i <= 2 * n1; i ++ )
		str[i] = appear[a1[i - n1]];

	int j = 0;
	for ( int i = 1; i <= n1; i ++ ) 
		if ( str[i] != 0 ) {
			j = max(i, j);
			while ( j + 1 < i + n1 && str[j + 1] != 0 ) {
				if ( i == j ) 
					j ++;
				else {
					if ( str[i] > str[j] ) {
						if ( str[j + 1] > str[j] && str[j + 1] < str[i] )
							j ++;
						else
							break;
					} else {
						if ( str[j + 1] > str[j] )
							j ++;
						else if ( str[j + 1] < str[i] )
							j ++;
						else
							break;
					}
				}
			}
			res = max(res, j - i + 1);
		}
	printf("%d\n", res);
}
