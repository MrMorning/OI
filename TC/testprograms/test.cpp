#include <cstdio>
#include <algorithm>
using namespace std;

int main() {
	for ( int n = 1; n <= 13; n ++ )
		for ( int m = 1; m <= 13; m ++ )
			if ( min(13, n * m) > n + m ) 
				printf("%d %d\n", n, m);
}
