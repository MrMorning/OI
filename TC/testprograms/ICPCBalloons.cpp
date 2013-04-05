#include <cstdio>
#include <vector>
#include <string>
#include <cstring>
typedef long long ll;
using namespace std;

class PastingPaintingDivOne {
	char bd[500][500];
	ll R[100], G[100], B[100];
	vector<long long> countColors(vector<string> clip, int T) {
		memset(bd, '.', sizeof(bd));
		int n = clip.size(), m = clip[0].size();
		R[0] = 0, G[0] = 0, B[0] = 0;
		ll ansR = -1, ansG, ansB;
		for ( int k = 1; k <= T; k ++ ) {
			R[k] = R[k-1], G[k] = G[k-1], B[k] = B[k-1];
			for ( int i = 0; i < n; i ++ )
				for ( int j = 0; j < m; j ++ )
					if ( clip[i][j] != '.' ) {
						if ( clip[i][j] == 'R' )
							R[k]++;
						else if (clip[i][j] == 'G' )
							G[k]++;
						else
							B[k]++;	
						if ( bd[k+i][k+j] == 'R' ) R[k]--;
						if ( bd[k+i][k+j] == 'G' ) G[k]--;
						if ( bd[k+i][k+j] == 'B' ) B[k]--;
					}
			if ( R[k]-R[k-1]==R[k-1]-R[k-2]
					&& G[k]-G[k-1]==G[k-1]-G[k-2]
					&& B[k]-B[k-1]==B[k-1]-B[k-2] ) {
				ansR = R[k] + (ll)(T-k)*(R[k]-R[k-1]);
				ansG = G[k] + (ll)(T-k)*(G[k]-G[k-1]);
				ansB = B[k] + (ll)(T-k)*(B[k]-B[k-1]);
				break;
			}
		}
		if ( ansR == -1 ) ansR = R[T], ansG = G[T], ansB = B[T];
		vector<ll> res;
		res.push_back(ansR);
		res.push_back(ansG);
		res.push_back(ansB);
		return res;
	}
};
