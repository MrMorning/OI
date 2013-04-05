#include <cstdio>

int main() {
	freopen("t.in", "r", stdin);
	int s, t;
	scanf("%d%d", &s, &t);
	if ( t - s <= 0 )
		printf("0\n");
	else if ( t - s < 5 * 60 )
		printf("1\n");
	else if ( t - s < 15 * 60 )
		printf("2\n");
	else if ( t - s < 30 * 60 )
		printf("3\n");
	else 
		printf("4\n");
}
