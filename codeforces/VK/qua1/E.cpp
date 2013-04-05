#include <cstdio>
#include <cstring>

const int inf = 0x3f3f3f3f;

int N, K;
int presum[86410];
int f[4010][4010];

struct Call {
	int be, la;
} call[4010];

void upd(int &x, int y) {
	if ( x > y )
		x = y;
}

bool check(int len) {
	for ( int st = 1; st <= 86400 - len + 1; st ++ ) {
		int en = st + len - 1;
		int cnt = presum[en] - presum[st - 1];
		if ( cnt > K )
			continue;

		int lb = 0, rb = N;
		for ( int mid = (lb + rb) / 2;
				lb < rb - 1; mid = (lb + rb) / 2 ) {
			if ( call[mid].be < st )
				lb = mid;
			else
				rb = mid;
		}

		if ( call[lb].be < st ) {
			int pos = lb;
			lb = -1, rb = K;
			for ( int mid = (lb + rb) / 2;
					lb < rb - 1; mid = (lb + rb) / 2 ) {
				if ( f[pos + 1][mid] < st )
					rb = mid;
				else
					lb = mid;
			}
			if (f[pos + 1][rb] < st && cnt + rb <= K )
				return true;
		} else
			if ( cnt <= K )
				return true;
	}
	return false;
}

int main() {
	//freopen("t.in", "r", stdin);
	scanf("%d%d", &N, &K);
	if ( N == 0 ) {
		printf("86400\n");
		return 0;
	}
	for ( int i = 0; i < N; i ++ ) {
		scanf("%d%d", &call[i].be, &call[i].la);
		presum[call[i].be] ++;
	}
	for ( int i = 1; i <= 86400; i ++ )
		presum[i] += presum[i - 1];
	memset(f, 0x3f, sizeof(f));
	f[0][0] = 0;
	for ( int i = 0; i <= N; i ++ )
		for ( int j = 0; j <= K; j ++ ) {
			if ( j > 0 )
				upd(f[i][j], f[i][j - 1]);
			if ( i == N )
				continue;
			if ( f[i][j] != inf ) {
				if ( f[i][j] >= call[i].be ) {
					upd(f[i + 1][j], f[i][j] + call[i].la);
					if ( j < K )
						upd(f[i + 1][j + 1], f[i][j]);
				} else {
					upd(f[i + 1][j], call[i].be + call[i].la - 1);
					if ( j < K )
						upd(f[i + 1][j + 1], f[i][j]);
				}
			}
		}
	int lb = 0, rb = 86400 + 1;
	for ( int mid = (lb + rb) / 2; lb < rb - 1;
			mid = (lb + rb) / 2 ) 
		if ( check(mid) )
			lb = mid;
		else
			rb = mid;
	printf("%d\n", lb);
}
