#include <cstdio>
#include <algorithm>
using namespace std;
int n, m;
int main(){
	scanf("%d%d", &n, &m);
	if(n > m)
		swap(n, m);
	if(n == 1)
		printf("%d\n", m);
	else if(n == 2){
		if((m - 1) % 4 == 0)
			printf("%d\n", m + 1);
		else if((m - 1) % 4 == 1)
			printf("%d\n", m + 2);
		else if((m - 1) % 4 == 2)
			printf("%d\n", m + 1);
		else if((m - 1) % 4 == 3)
			printf("%d\n", m);
	}
	else if(n * m % 2 == 0)
		printf("%d\n", n * m / 2);
	else
		printf("%d\n", max(n * (m - 1) / 2 + n / 2 + 1, m * (n - 1) / 2 + m / 2 + 1));
}
