#include <cstdio>
#include <cmath>
#include <cstring>
#include <iostream>
#include <algorithm>
#include <iomanip>
using namespace std;

#define IDLE 4
const double INIT_TEMP = 1000;
const double FINAL_TEMP = 10e-2;
const double MARCOLF_LENGTH = 5000;
const double FREEZE = 0.998;
const int REBORN_TIMES = 5;

const int offset[4][2] = {{-1, 0}, {0, -1}, {0, 1}, {1, 0}};
int stra[40][40], bestStra[40][40];
int ansEnergy = 0;
int n, m;

double eval()
{
	int res = 0;
	for(int i = 0; i < n; i ++)
		for(int j = 0; j < m; j ++)
		{
			bool flag = false;
			int t = stra[i][j];
			if(t == IDLE)
				continue;
			for(int d = 0; d < 4; d ++)
			{
				int ni = i + offset[d][0],
					nj = j + offset[d][1];
				if(0 <= ni && ni < n)
					if(0 <= nj && nj < m)
						if(stra[ni][nj] != IDLE && stra[ni][nj] == 3 - d)
						{
							flag = true;
							break;
						}
			}
			res += !flag;
		}
	return res;
}

int main()
{
	freopen("t.in", "w", stdout);
	for(n = 1; n <= 40; n ++)
		for(m = n; n * m <= 40; m ++)
		{
			fprintf(stderr, "%d %d\n", n, m);
			//cin >> n >> m;
			ansEnergy = 0;
			for(int i = 0; i < n; i ++)
				for(int j = 0; j < m; j ++)
					stra[i][j] = IDLE;
			int curEnergy = eval();
			for(int rep = 0; rep < REBORN_TIMES; rep ++)
				for(double curTemp = INIT_TEMP; curTemp > FINAL_TEMP; curTemp *= FREEZE)
					for(int len = 0; len < MARCOLF_LENGTH; len ++)
					{
						if(curEnergy > ansEnergy)
							ansEnergy = curEnergy;

						int u = rand() % n, v = rand() % m;
						int d = rand() % 5, bck = stra[u][v];
						if(d != IDLE)
						{
							int nu = u + offset[d][0],
								nv = v + offset[d][1];
							if(!(0 <= nu && nu < n && 0 <= nv && nv < m))
								d = IDLE;
						}
						stra[u][v] = d;

						double newEnergy = eval();
						if(newEnergy > curEnergy || exp((double)(newEnergy - curEnergy) / curTemp) > (double)rand() / RAND_MAX)
							curEnergy = newEnergy;
						else
							stra[u][v] = bck;
					}
			printf("%d %d %d\n", n, m, ansEnergy);
		}
}
