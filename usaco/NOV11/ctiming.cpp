#include <cstdio>
int D, H, M;
int main(){
	freopen("ctiming.in", "r", stdin);
	freopen("ctiming.out", "w", stdout);
	scanf("%d%d%d", &D, &H, &M);
	int curD = 11, curH = 11, curM = 11;
	int cnt = 0;
	while(curD != 15){
		if(curD == D && curH == H && curM == M){
			printf("%d\n", cnt);
			return 0;
		}
		cnt ++;
		if(curM == 59){
			if(curH == 23)
				curD ++, curH = curM = 0;
			else
				curH ++, curM = 0;
		}
		else curM ++;
	}
	printf("-1\n");
}
