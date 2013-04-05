#include <cstdio>
#include <cstring>
#include <algorithm>
#include <cstdlib>
#include <ctime>
using namespace std;

int main() {
	srand(time(NULL));
	freopen("t.in", "w", stdout);
	char str[] = "aabbccddeeddggdcacd\0";
	int len = strlen(str);
	random_shuffle(str, str + len);
	for ( int i = 0; i < len; i ++ )
		printf("%c", str[i] - 'a' + 'A');
}
