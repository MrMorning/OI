#include <cstdio>
#include <cstring>
#include <cassert>
char str[1000][10];
int main() {
	freopen("t.out", "r", stdin);
	for ( int i = 1; i <= 1000; i ++ )
		scanf("%s", str[i]);
	for ( int i = 2; i <= 1000; i ++ )
		if(strcmp(str[i], str[i - 1]) == 0)
			assert(0);
}
