#include <cstdio>
#include <cstdlib>
#include <cmath>
#include <algorithm>
using namespace std;
typedef long long ll;
int main(){
	freopen("game.in", "r", stdin);
	freopen("game.out", "w", stdout);
	int T;
	scanf("%d", &T);
	while(T --){
		int a, b, m;
		scanf("%d%d%d", &a, &b, &m);
		if(b >= m)
			printf("-1\n");
		else{
			bool suc = false;
			for(int t = 0; t <= min(a, m - 1); t ++)
				if((ll)ceil((double)((ll)t * 1000000000LL) / m) > (ll)floor((double)((ll)t * 1000000000LL + b) / m)){
					int tmp = t, cnt = t == 0;
					while(tmp)
						cnt ++, tmp /= 10;
					for(int i = 0; i < 9 - cnt; i ++)
						printf("0");
					printf("%d\n", t);
					suc = true;
					break;
				}
			if(suc)
				continue;
			printf("-1\n");
		}
	}
}
