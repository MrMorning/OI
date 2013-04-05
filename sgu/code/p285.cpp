#include <cstdio>
#include <cstring>
#include <cassert>
const int des[12][2] = {
	{6, 0}, {6, 1}, {6, 2}, {6, 3}, {6, 4}, {6, 5},
	{5, 6}, {4, 6}, {3, 6}, {2, 6}, {1, 6}, {0, 6}
};
double f[8][8][1 << 13];
double prob[13];
int nNet;
int log2[1 << 13];
double solve(int tar) {
	int upperlim = 1 << 13;
	memset(f, 0, sizeof(f));
	for ( int s = 0; s < upperlim; s ++ )
		f[des[tar][0]][des[tar][1]][s] = 1.0;
	for ( int i = des[tar][0]; i >= 0; i -- )
		for ( int j = des[tar][1]; j >= 0; j -- ) 
			if ( i != 6 && j != 6 ) {
				for ( int s = 1; s < upperlim; s ++ ) {
					f[i][j][s] = 0;
					int tmp = s;
					int pre = log2[tmp] - 13;
					while ( tmp ) {
						int k = tmp & -tmp;
						int w = log2[k];
						double cur = prob[w] * f[i + 1][j][s - k] + (1 - prob[w]) * f[i][j + 1][s - k];
						cur = cur * (w - pre)/ 13;
						f[i][j][s] += cur;
						pre = w;
						tmp -= k;
					}
				}
			}
	return f[0][0][upperlim - 1];
}
int main() {
	for ( int i = 0; i < 13; i ++ )
		log2[1 << i] = i;
	for ( int i = 1; i < (1 << 13); i ++ )
		if ( !log2[i] )
			log2[i] = log2[i - 1];
	scanf("%d", &nNet);
	for ( int i = 0; i < 12; i ++ )
		scanf("%lf", &prob[i]);
	prob[12] = 0;
	for ( int i = 0; i < nNet; i ++ ) {
		double tmp;
		scanf("%lf", &tmp);
		prob[12] += tmp;
	}
	if ( nNet )
		prob[12] /= nNet;
	for ( int i = 0; i < 12; i ++ ) 
		printf("%.3lf\n", solve(i));
}
