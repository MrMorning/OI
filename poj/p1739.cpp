#include <cstdio>
#include <cstring>
#include <vector>
#include <cassert>
using namespace std;

typedef pair<int, int> hash_t;

const int N_STATE_MAX = 20000;

int f[2][N_STATE_MAX];
int maskCnt;
int toMask[N_STATE_MAX];
bool fine[20][20];

struct HashTable{
	vector<hash_t> ele[4096];
	int &operator[] (int x){
		int code = x & 4095;
		int n = ele[code].size();
		for(int i = 0; i < n; i ++)
			if(ele[code][i].first == x)
				return ele[code][i].second;
		ele[code].push_back(make_pair(x, -1));
		return ele[code][n].second;
	}
} hash;

int rec(int s){
	if(hash[s] == -1){
		hash[s] = maskCnt;
		toMask[maskCnt] = s;
		maskCnt ++;
	}
	return hash[s];
}

int get(int s, int i){
	return (((s & (1 << (2 * i + 1))) > 0) << 1)
		| ((s & (1 << (2 * i))) > 0);
}

void mod(int &s, int i, int t){
	if(((s & (1 << (2 * i + 1))) > 0) != ((t & 2) >> 1))
		s ^= 1 << (2 * i + 1);
	if(((s & (1 << (2 * i))) > 0) != (t & 1))
		s ^= 1 << (2 * i);
}

int findNext(int s, int i){
	int top = 1;
	for(int j = i + 1; ; j ++){
		if(get(s, j) == 1)
			top ++;
		else if(get(s, j) == 2)
			top --;
		if(top == 0)
			return j;
	}
	assert(0);
}

int findPrev(int s, int i){
	int top = 1;
	for(int j = i - 1; ; j --){
		if(get(s, j) == 1)
			top --;
		else if(get(s, j) == 2)
			top ++;
		if(top == 0)
			return j;
	}
	assert(0);
}
int now;

void roll(){
	now ^= 1;
	memset(f[!now], 0, sizeof(f[now]));
}

void inc(int &x, int y){
	x = (x + y) % 10007;
}

int main(){
	freopen("t.in", "r", stdin);

	int nrow, ncol;

	scanf("%d%d", &nrow, &ncol);
	for(int i = 0; i < nrow; i ++){
		static char str[20];
		scanf("%s", str);
		for(int j = 0; j < ncol; j ++)
			fine[i][j] = str[j] == '.';
	}
	now = 0;
	int initS = 0;
	mod(initS, 1, 1);
	mod(initS, ncol + 1, 2);
	f[now][rec(initS)] = 1;
	for(int i = 0; i < nrow; i ++, roll()){
		for(int j = 0; j < ncol; j ++, roll())
			for(int k = 0, tot = maskCnt; k < tot; k ++)
				if(f[now][k]){
					int s = toMask[k];
					int a = get(s, j), b = get(s, j + 1);
					if(!fine[i][j]){/*{{{*/
						if(a == 0 && b == 0)
							inc(f[!now][k], f[now][k]);
					}/*}}}*/
					else{
						if(a == 0 && b == 0){/*{{{*/
					//		inc(f[!now][k], f[now][k]);
							int newS = s;
							mod(newS, j, 1);
							mod(newS, j + 1, 2);
							inc(f[!now][rec(newS)], f[now][k]);
						}/*}}}*/
						else if(a == 0 && b == 1){/*{{{*/
							inc(f[!now][k], f[now][k]);
							int newS = s;
							mod(newS, j, 1);
							mod(newS, j + 1, 0);
							inc(f[!now][rec(newS)], f[now][k]);
						}/*}}}*/
						else if(a == 1 && b == 0){/*{{{*/
							inc(f[!now][k], f[now][k]);
							int newS = s;
							mod(newS, j, 0);
							mod(newS, j + 1, 1);
							inc(f[!now][rec(newS)], f[now][k]);
						}/*}}}*/
						else if(a == 1 && b == 1){/*{{{*/
							int p = findNext(s, j + 1);
							int newS = s;
							mod(newS, j, 0);
							mod(newS, j + 1, 0);
							mod(newS, p, 1);
							inc(f[!now][rec(newS)], f[now][k]);
						}/*}}}*/
						else if(a == 1 && b == 2){/*{{{*/
							//do nothing
						}/*}}}*/
						else if(a == 2 && b == 1){/*{{{*/
							int newS = s;
							mod(newS, j, 0);
							mod(newS, j + 1, 0);
							inc(f[!now][rec(newS)], f[now][k]);
						}/*}}}*/
						else if(a == 0 && b == 2){
							inc(f[!now][k], f[now][k]);
							int newS = s;
							mod(newS, j, 2);
							mod(newS, j + 1, 0);
							inc(f[!now][rec(newS)], f[now][k]);
						}
						else if(a == 2 && b == 0){
							inc(f[!now][k], f[now][k]);
							int newS = s;
							mod(newS, j, 0);
							mod(newS, j + 1, 2);
							inc(f[!now][rec(newS)], f[now][k]);
						}
						else{// a == 2 && b == 2/*{{{*/
							assert(a == 2 && b == 2);
							int p = findPrev(s, j);
							int newS = s;
							mod(newS, j, 0);
							mod(newS, j + 1, 0);
							mod(newS, p, 2);
							inc(f[!now][rec(newS)], f[now][k]);
						}/*}}}*/
					}
				}
		for(int k = 0, tot = maskCnt; k < tot; k ++)
			if(f[now][k]){
				int s = toMask[k];
				if(get(s, ncol) == 0 && get(s, ncol + 1) == 2){
					int newS = s;
					mod(newS, ncol + 1, 0);
					newS <<= 2;
					mod(newS, ncol + 1, 2);
					inc(f[!now][rec(newS)], f[now][k]);
				}
			}
	}
	int finalS = 0;
	mod(finalS, ncol, 1);
	mod(finalS, ncol + 1, 2);
	printf("%d\n", f[now][rec(finalS)]);
}
