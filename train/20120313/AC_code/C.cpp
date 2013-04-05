#include <cstdio>
#include <cstring>
#include <string>
using namespace std;

int n_cmd;
string stk[10000];

int main() {
	scanf("%d", &n_cmd);
	int top = 0;
	stk[top ++] = string();
	while ( n_cmd -- ) {
		char type[10];
		scanf("%s", type);
		if ( type[0] == 'p' ) {
			for ( int i = 0; i < top; i ++ )
				printf("%s/", stk[i].c_str());
			puts("");
		} else {
			char dir[222];
			scanf("%s", dir);
			int st = 0;
			if ( dir[0] == '/' ) {
				top = 1;
				st = 1;
			}
			int sz = strlen(dir);
			string acc;
			for ( int i = st; i <= sz; i ++ ) {
				if ( i == sz || dir[i] == '/' ) {
					if ( acc == ".." ) 
						top --;
					else 
						stk[top ++] = acc;
					acc = "";
				} else
					acc += dir[i];
			}
		}
	}
}
