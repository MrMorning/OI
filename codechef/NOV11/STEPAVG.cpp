#include <cstdio>
#include <algorithm>
#include <cstdlib>
#include <cmath>
using namespace std;
const int N_MAX = 1111;

const double INIT_TEMP = 30;
const double FINAL_TEMP = 10e-2;
const double FREEEZE_COEF = 0.99;
const int MARCOLF_LENGTH = 32;

int curState[N_MAX][2];

int N, K;
int weight[N_MAX];

double eval(){
	static double tmp[2 * N_MAX];
	for(int i = 0; i < N; i ++)
		tmp[i] = weight[i];
	for(int i = 0; i < N - 1; i ++){
		int a = curState[i][0], b = curState[i][1];
		tmp[N + i] = (tmp[a] + tmp[b]) / 2;
	}
	return fabs(K - tmp[N + N - 2]);
}

void solve(){
	scanf("%d%d", &N, &K);
	for(int i = 0; i < N; i ++)
		scanf("%d", &weight[i]);
	for(int i = 0; i < N - 1; i ++)
		curState[i][0] = i * 2, curState[i][1] = i * 2 + 1;
	double curEnergy = eval();
	for(double curTemp = INIT_TEMP; curTemp > FINAL_TEMP; curTemp *= FREEEZE_COEF)
		for(int rep = 0; rep < MARCOLF_LENGTH; rep ++){

			int i = rand() % (N - 1), j = rand() % 2;
			int x = curState[i][j];
			int lb = max(0, x + 1 - N), rb = i, len = rb - lb + 1;
			if(len < 1)
				continue;
			int n = rand() % len + lb, m = rand() % 2;
			swap(curState[i][j], curState[n][m]);

			double nextEnergy = eval();
			if(nextEnergy < curEnergy || exp((curEnergy - nextEnergy) / curTemp) > (double)rand() / RAND_MAX)
				curEnergy = nextEnergy;
			else
				swap(curState[i][j], curState[n][m]);
//			printf("%.4lf\n", curEnergy);
		}
	for(int i = 0; i < N - 1; i ++)
		printf("%d %d\n", curState[i][0] + 1, curState[i][1] + 1);
//	fprintf(stderr, "%.4lf\n", curEnergy);
}

int main(){
	freopen("t.in", "r", stdin);
	int T;
	scanf("%d", &T);
	while(T --)
		solve();
}
