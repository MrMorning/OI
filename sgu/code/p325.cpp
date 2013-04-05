#include <cstdio>
#include <cstring>
#include <vector>
using namespace std;
typedef long long ll;
#ifdef unix
#define LL_FMT "%lld"
#else
#define LL_FMT "%I64d"
#endif

const int N_MAX = 1000010;
vector<int> list[26];
char str[N_MAX];
int des[N_MAX];
int idt[N_MAX];
int match[N_MAX];
int len;

int sum(int i) {
	i += 2;
	int res = 0;
	for ( ; i; i -= i & -i )
		res += idt[i];
	return res;
}

void add(int i) {
	i += 2;
	for ( ; i < N_MAX; i += i & -i )
		idt[i] ++;
}

bool check() {
	int oddCnt = 0;
	for ( int z = 0; z < 26; z ++ )
		oddCnt += (list[z].size() & 1);
	if ( len & 1 ) 
		return oddCnt <= 1;
	else return oddCnt == 0;
}

int main() {
	freopen("t.in", "r", stdin);
	scanf("%s", str);
	len = strlen(str);
	for ( int i = 0; i < len; i ++ ) 
		list[str[i] - 'A'].push_back(i);
	if ( !check() ) {
		puts("-1");
		return 0;
	}
	for ( int z = 0; z < 26; z ++ ) {
		int sz = list[z].size();
		for ( int k = 0; k < sz; k ++ ) 
			match[list[z][k]] = list[z][sz - k - 1];
	}
	memset(des, -1, sizeof(des));
	for ( int i = 0, cnt = 0; i < len; i ++ ) 
		if ( des[i] == -1 ) {
			if ( match[i] == i ) 
				des[i] = len / 2;
			else {
				des[i] = cnt;
				des[match[i]] = len - cnt - 1;
				cnt ++;
			}
		}
	ll ans = 0;
	for ( int i = len - 1; i >= 0; i -- ) {
		ans += sum(des[i] - 1);
		add(des[i]);
	}
	printf(LL_FMT "\n", ans);
}
