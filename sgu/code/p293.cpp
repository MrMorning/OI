#include <cstdio>
#include <cstring>
#include <cassert>
#include <algorithm>
using namespace std;
const int N_MAX = 4444;
struct QC {
	int cnt[2];
	char ch[2];
	char now[N_MAX];
	char des[N_MAX];
	int size;

	void clear() {
		ch[0] = 'Q', ch[1] = 'C';
		size = 0;
	}
	void genCnt() {
		cnt[0] = cnt[1] = 0;
		for ( int i = 1; i <= size; i ++ ) 
			cnt[now[i] == ch[1]] ++;
	}
	void makeDes() {
		genCnt();
		if ( cnt[0] < cnt[1] ) {
			swap(cnt[0], cnt[1]);
			swap(ch[0], ch[1]);
		}

		int mid = (size + 1) / 2;
		if ( cnt[0] & 1 ) {
			des[mid] = ch[0];
			cnt[0] --;
		} else {
			des[mid] = ch[1];
			cnt[1] --;
		}

		int delta = (cnt[0] - cnt[1]) / 2;
		for ( int d = 1; d <= delta; d ++ ) 
			des[mid + d] = des[mid - d] = ch[0];
		for ( int rep = 0; rep < 2; rep ++ ) {
			for ( int d = delta + 1; d <= size / 2; d ++ ) 
				des[mid + d] = des[mid - d] = ch[(d & 1) ^ rep];

			static int ptr[2][N_MAX], nPtr[2];
			nPtr[0] = nPtr[1] = 0;
			for ( int i = 1; i <= size; i ++ ) 
				if ( now[i] != des[i] ) {
					if ( now[i] == ch[0] )
						ptr[0][nPtr[0] ++] = i;
					else
						ptr[1][nPtr[1] ++] = i;
				}
			if ( !(nPtr[0] == nPtr[1] && nPtr[0] <= 2) )
				continue;
			for ( int t = nPtr[0]; t < 2; t ++ )
				printf("0 0\n");
			for ( int t = 0; t < nPtr[0]; t ++ ) {
				printf("%d %d\n", ptr[0][t], ptr[1][t]);
				swap(now[ptr[0][t]], now[ptr[1][t]]);
			}
//			fprintf(stderr, "%s\n", now + 1);
			return;
		}
		assert(0);
	}

	void insert(char a, char b) {
		now[++ size] = a, now[++ size] = b;
		makeDes();
	}
} qc;
int n;
char seq[N_MAX];
int main() {
	freopen("t.in", "r", stdin);

	scanf("%d", &n);
	scanf("%s", seq);
	qc.clear();
	qc.now[++ qc.size] = seq[0];
	puts("Qc\n0 0");
	for ( int i = 1; i < 2 * n - 1; i += 2 ) 
		qc.insert(seq[i], seq[i + 1]);
//	fprintf(stderr, "%s\n", qc.now + 1);
}
