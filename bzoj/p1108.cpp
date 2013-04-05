#include <cstdio>
int n, a, b;
long long res;
int main(){
	scanf("%d", &n);
	for(int i = 0; i < n; i ++){
		scanf("%d%d", &a, &b);
		res += b - a;
	}
	for(int i = 0; i < n; i ++){
		scanf("%d%d", &a, &b);
		res += a - b;
	}
	printf("%lld\n", res);
}
