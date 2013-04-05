#include <cstdio>
#include <vector>
#include <cstring>
#define FOREACH(I, C) for(__typeof((C).begin()) I = (C).begin(); I != (C).end(); I ++)
using namespace std;
bool done[22][22];
int memo[22][22];
vector<pair<int, int> > adj[26];
int over[26];
char str[22];

int dp(int i, int j) {
	if ( done[i][j] )
		return memo[i][j];
	done[i][j] = true;
	int &res = memo[i][j] = 0;
	if ( i == j ) {
		for ( int z = 0; z < 26; z ++ )
			if ( over[z] & (1 << (str[i] - 'a')) )
				res |= 1 << z;
	} else {
		for ( int z = 0; z < 26; z ++ ) {
			FOREACH(it, adj[z]) {
				bool found = false;
				for ( int k = i; k < j; k ++ ) 
					if ( dp(i, k) & (1 << it->first) )
						if ( dp(k + 1, j) & (1 << it->second) ) {
							found = true;
							break;
						}
				if ( found ) {
					res |= 1 << z;
					break;
				}
			}
		}
	}

	return res;
}

int main() {
	freopen("t.in", "r", stdin);
	int n1, n2;

	scanf("%d %d\n", &n1, &n2);
	for ( int i = 0; i < n1; i ++ ) {
		char s, t;
		scanf("%c->%c\n", &s, &t);
		over[s - 'A'] |= 1 << (t - 'a');
	}
	for ( int i = 0; i < n2; i ++ ) {
		char s, t1, t2;
		scanf("%c->%c%c\n", &s, &t1, &t2);
		adj[s - 'A'].push_back(make_pair(t1 - 'A', t2 - 'A'));
	}

	while ( scanf("%s\n", str) != EOF ) {
		memset(done, 0, sizeof(done));
		printf("%s\n", (dp(0, strlen(str) - 1) & (1 << ('S' - 'A'))) ? "YES" : "NO");
	}
}
