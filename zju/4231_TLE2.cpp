#include <cassert>
#include <cstdio>
#include <vector>
#include <cstring>

using namespace std;

typedef int mask_t;
typedef pair<mask_t, int> hash_t;
typedef long long int64;
#ifdef unix
#define INT64_FMT "%lld"
#else
#define INT64_FMT "%I64d"
#endif
const int N_MASK_MAX = 2200000;

int nrow, ncol, nobs;
bool isObs[11][11];
int64 f[2][N_MASK_MAX];

int getBit(mask_t s, int x){
	return (s & (1 << x)) > 0;
}

void modBit(mask_t &s, int x, int newVal){
	if(getBit(s, x) == newVal)
		return;	
	s ^= 1 << x;
}

void work(){
	ncol = 8;
	memset(isObs, 0, sizeof(isObs));
	while(nobs --){
		static char str[4];
		scanf("%s", str);
		isObs[str[0] - 'A'][str[1] - 'A'] = true;
	}
	int cur = 0;
	memset(f[cur], 0, sizeof(f[cur]));
	f[cur][0] = 1;
	for(int j = 0; j < 8; j ++, cur ^= 1){
		for(int i = nrow - 1; i >= 0; i --, cur ^= 1){
			memset(f[!cur], 0, sizeof(f[cur]));
			for(int k = 0; k < N_MASK_MAX; k ++)
				if(f[cur][k]){
					int s = k;
					int pa = 2 * (nrow - i - 1),
						pb = 2 * (nrow - i - 1) + 1,
						pc = 2 * (nrow - i - 1) + 2;
					int a = getBit(s, pa),
						b = getBit(s, pb),
						c = getBit(s, pc);
					if(a + b + c == 3)
						continue;
					assert(a + b + c < 3);
					if(isObs[i][j]){
						if(a + b + c == 0){
							f[!cur][k] += f[cur][k];
						}
						continue;
					}
					if(a + b + c == 0){/*{{{*/
						int newS = s;
						modBit(newS, pa, 1);
						modBit(newS, pb, 1);
						f[!cur][newS] += f[cur][k];
						newS = s;
						modBit(newS, pa, 1);
						modBit(newS, pc, 1);
						f[!cur][newS] += f[cur][k];
						newS = s;
						modBit(newS, pb, 1);
						modBit(newS, pc, 1);
						f[!cur][newS] += f[cur][k];
					}/*}}}*/
					else if(a + b + c == 1){/*{{{*/
						int newS = s;
						modBit(newS, pa, 0);
						modBit(newS, pb, 0);
						modBit(newS, pc, 0);

						modBit(newS, pa, 1);
						f[!cur][newS] += f[cur][k];
						modBit(newS, pa, 0);

						modBit(newS, pb, 1);
						f[!cur][newS] += f[cur][k];
						modBit(newS, pb, 0);

						modBit(newS, pc, 1);
						f[!cur][newS] += f[cur][k];
						modBit(newS, pc, 0);
					}/*}}}*/
					else{/*{{{*/
						int newS = s;
						modBit(newS, pa, 0);
						modBit(newS, pb, 0);
						modBit(newS, pc, 0);
						
						f[!cur][newS] += f[cur][k];
					}/*}}}*/
				}
		}
		memset(f[!cur], 0, sizeof(f[cur]));
		if(!(j & 1)){
			for(int k = 0; k < N_MASK_MAX; k ++)
				if(f[cur][k]){
					int s = k;
					if(getBit(s, 0) == 0 && getBit(s, 2 * nrow) == 0)
						f[!cur][k] += f[cur][k];
				}
		}
		else{
			for(int k = 0; k < N_MASK_MAX; k ++)
				if(f[cur][k]){
					int s = k;
					if(getBit(s, 2 * nrow) == 0 && getBit(s, 2 * nrow - 1) == 0){
						f[!cur][s << 2] += f[cur][k];
					}
				}
		}
	}
	printf(INT64_FMT "\n", f[cur][0]);
}

int main(){
	freopen("t.in", "r", stdin);
	while(scanf("%d%d", &nrow, &nobs) != EOF){
		work();
	}
}
