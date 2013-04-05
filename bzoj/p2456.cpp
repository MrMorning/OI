#include <cstdio>
int n, m, x, t;
int main(){
	freopen("t.in", "r", stdin);
	scanf("%d", &n);
	while(n --){
		scanf("%d", &x);
		if(x == m)
			t ++;
		else if(t == 0)
			m = x;
		else
			t --;
	}
	printf("%d\n", m);
}
