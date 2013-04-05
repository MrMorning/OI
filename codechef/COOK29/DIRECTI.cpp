#include <cstdio>
#include <cstring>
#include <string>
#include <iostream>
using namespace std;
string str;
string stk[1111];
int top = 0;

int main() {
	freopen("t.in", "r", stdin);
	int TST;
	scanf("%d\n", &TST);
	while ( TST -- ) {
		int n;
		scanf("%d\n", &n);
		for ( int i = 0; i < n; i ++ ) {
			getline(cin, str);
			int t = 0;
			string k;
			if ( str[0] == 'B' ) t = 9, k = "";
			if ( str[0] == 'R' ) t = 9, k = "Left";
			if ( str[0] == 'L' ) t = 8, k = "Right";
			if ( k != "" )
				stk[top++] = k;
			stk[top++] = str.substr(t, (int)str.size()-t);
		}
		printf("Begin on %s\n", stk[top-1].c_str());
		top--;
		while ( top ) {
			printf("%s on %s\n", stk[top-1].c_str(), stk[top-2].c_str());
			top-=2;
		}
		puts("");
	}
}
