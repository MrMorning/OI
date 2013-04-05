#include <cstdio>
#include <algorithm>
using namespace std;
const int a[5] = {1, 3, 4, 6, 9};

int main() {
	for ( int i = 0; i < 10; i ++ )
		printf("%d\n", upper_bound(a,a+5,i)-a);
}
