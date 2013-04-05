#include <cstdio>
#include <cassert>
#include <cstring>
#include <string>
using namespace std;

typedef long long ll;
const int kLMax = 10010;
const int kCMax = 1010;
const int kDx[4] = {-1, 1, 0, 0},
	  kDy[4] = {0, 0, -1, 1};
const int LEFT[4] = {2, 3, 1, 0}, RIGHT[4] = {3, 2, 0, 1};

int n, m;
int nArg[26];
char arg[26][2];
char opr[26][kLMax];
char cmd[kCMax];
int nCmd;
char maze[55][55];
char str[kLMax];
bool vis[55][55];
pair<int, int> ans[55*55];
int nAns = 0;

void doit(char ch, char arg0 = 0, char arg1 = 0) {
#define GAO(X) (X==arg[ch-'a'][0]?arg0:(X==arg[ch-'a'][1]?arg1:X))
	int k = ch-'a';
	int len = strlen(opr[k]);
	for ( int i = 0; i < len; i ++ ) {
		char cur = opr[k][i];
		if ( cur == 'L' || cur == 'R' || cur == 'C' ) 
			cmd[nCmd++] = cur;
		else if ( cur == arg[k][0] || cur == arg[k][1] )
			cmd[nCmd++] = GAO(cur);
		else {
			assert('a' <= cur && cur <= 'z');
			if ( nArg[cur-'a'] == 0 ) {
				doit(cur);
				i+=2;
			} else if ( nArg[cur-'a'] == 1 ) {
				doit(cur, GAO(opr[k][i+2]));
				i+=3;
			} else {
				assert(nArg[cur-'a']==2);
				doit(cur, GAO(opr[k][i+2]), GAO(opr[k][i+4]));
				i+=5;
			}
		}
	}
}

int main() {
	freopen("t.in", "r", stdin);
	scanf("%d%d", &n, &m);
	for ( int i = 0; i < n; i ++ ) 
		scanf("%s", maze[i]);
	char ch;
	int len = 0;
	while ( scanf("%c", &ch) != EOF ) {
		if ( isalpha(ch) || ch == '(' || ch == ')'
		  || ch == '{' || ch == '}' || ch == ',' )
			str[len++] = ch;
	}
	for ( int i = 0; i < len; i ++ ) {
		assert('a' <= str[i] && str[i] <= 'z');
		char ch = str[i];
		int j;
		for ( j = i+2; str[j] != ')'; j ++ );
		if ( j-i == 2 ) 
			nArg[ch-'a'] = 0;
		else if ( j-i == 3 ) {
			nArg[ch-'a'] = 1;
			arg[ch-'a'][0] = str[j-1];
		} else {
			assert(j-i==5);
			nArg[ch-'a'] = 2;
			arg[ch-'a'][0] = str[j-3];
			arg[ch-'a'][1] = str[j-1];
		}
		assert(str[j+1]=='{');
		for ( i = j; str[i] != '}'; i ++ );
		//j+2->i-1
		strncpy(opr[ch-'a'], str+j+2, (i-1)-(j+2)+1);
	}
	doit('m');

	int stx, sty;
	for ( int i = 0; i < n; i ++ )
		for ( int j = 0; j < m; j ++ )
			if ( maze[i][j] == 'R' ) 
				stx = i, sty = j;
	int dir = 0;
	for ( int i = 0; i < nCmd; i ++ ) {
		if ( cmd[i] == 'L' ) 
			dir = LEFT[dir];
		else if ( cmd[i] == 'R' )
			dir = RIGHT[dir];
		else {
			int nx = stx+kDx[dir],
				ny = sty+kDy[dir];
			if ( !(0 <= nx && nx < n 
						&& 0 <= ny && ny < m) )
				continue;
			if ( !vis[nx][ny] && maze[nx][ny] == '*' )
				ans[nAns++] = make_pair(nx, ny);
			vis[nx][ny] = true;
			stx = nx, sty = ny;
		}
	}
	printf("%d\n", nAns);
	for ( int i = 0; i < nAns; i ++ )
		printf("%d %d\n", ans[i].first+1, ans[i].second+1);
}
