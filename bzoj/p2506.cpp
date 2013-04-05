#include <cstdio>
#include <algorithm>
#include <vector>
using namespace std;

const int LEN_MAX = 100010;
const int BLK_SIZE = 320;
const int VAL_MAX = 10000;
const int VAL_SQRT = 100;

int block[LEN_MAX / BLK_SIZE + 2][VAL_SQRT + 1][VAL_SQRT + 1];
vector<int> idx[VAL_MAX + 1];
int A[LEN_MAX];
int nblock, N, M;

int main(){
	freopen("t.in", "r", stdin);
	scanf("%d%d", &N, &M);
	int nblock = N / BLK_SIZE + 1;
	for(int i = 1; i <= N; i ++){
		scanf("%d", &A[i]);
		idx[A[i]].push_back(i);
	}
	for(int i = 0; i <= VAL_MAX; i ++)
		sort(idx[i].begin(), idx[i].end());
	for(int i = 1; i <= nblock; i ++){
		int lb = (i - 1) * BLK_SIZE + 1,
			rb = i * BLK_SIZE;
		for(int j = lb; j <= rb; j ++){
			int x = A[j];
			for(int k = 1; k <= VAL_SQRT; k ++)
				block[i][k][x % k] ++;
		}
	}

	while(M --){
		int l, r, p, k;
		scanf("%d%d%d%d", &l, &r, &p, &k);
		int res = 0;
		int t1 = (l - 1) / BLK_SIZE + 1,
			t2 = (r - 1) / BLK_SIZE + 1;
		if(t1 == t2){
			for(int i = l; i <= r; i ++)
				if(A[i] % p == k)
					res ++;
		}
		else{
			if(p <= VAL_SQRT){
				for(int i = l; i <= t1 * BLK_SIZE; i ++)
					if(A[i] % p == k)
						res ++;
				for(int i = (t2 - 1) * BLK_SIZE + 1; i <= r; i ++)
					if(A[i] % p == k)
						res ++;
				for(int i = t1 + 1; i <= t2 - 1; i ++)
					res += block[i][p][k];
			}
			else{
				for(int x = k; x <= VAL_MAX; x += p)
					if(idx[x].size()){
						int lb = -1, rb = idx[x].size() - 1;
						for(int mid = (lb + rb) >> 1; lb < rb - 1; mid = (lb + rb) >> 1){
							if(idx[x][mid] >= l)
								rb = mid;
							else
								lb = mid;
						}
						if(idx[x][rb] < l || idx[x][rb] > r)
							continue;
						int tmp = rb;
						lb = 0, rb = idx[x].size();
						for(int mid = (lb + rb) >> 1; lb < rb - 1; mid = (lb + rb) >> 1){
							if(idx[x][mid] <= r)
								lb = mid;
							else
								rb = mid;
						}
						res += lb - tmp + 1; 
					}
			}
		}
		printf("%d\n", res);
	}
}
