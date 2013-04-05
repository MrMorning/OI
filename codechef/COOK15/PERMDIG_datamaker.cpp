#include <cstdio>
#include <cstdlib>
int T, seed;
int main(){
	freopen("t.in", "w", stdout);
	scanf("%d%d", &T, &seed);
	srand(seed);
	printf("%d\n", T);
	while(T --){
		int base = rand() % 9 + 2;
		printf("%d\n", base);
		int len = 80 / base;
		for(int t = 0; t < 3; t ++){
			int k = rand() % len + 1;
			bool flag = false;
			for(int i = 0; i < k; i ++){
				int x = rand() % base;
				if(x == 0 && !flag)
					x = 1;
				if(x > 0)
					flag = false;
				printf("%d", x);
			}
			printf(" ");
		}
		puts("");
	}
}
