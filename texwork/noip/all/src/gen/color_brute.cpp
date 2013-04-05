#include <cstdio>
int n, p, res;
bool fine(int x){
	for(int i = 0; i < n; i ++)
		if((x & (1 << i)) && (x & (1 << ((i + p) % n))))
			return false;
	return true;
}
int main(){
	freopen("color.in", "r", stdin);
	freopen("color.out", "w", stdout);
	scanf("%d%d", &n, &p);
	for(int x = 0; x < (1 << n); x ++)
		if(fine(x))
			res ++;
	printf("%d\n", res);
}
