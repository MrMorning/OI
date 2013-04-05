/*
 * $Date: Mon Oct 31 20:24:36 2011 +0800
 * $Author: csimstu
 * $Source: Ural 1519 Formula I
 * $Method: Plug DP
 */
#include <cstdio>
#include <cstring>
#include <vector>
#include <cassert>

using namespace std;

typedef int mask_t;
typedef pair<mask_t, int> hash_t;
typedef long long int64;

#ifdef unix 
#define INT64_FMT "%lld"
#else
#define INT64_FMT "%I64d"
#endif

const int N_MASK_MAX = 150000;
const int WIDTH_MAX = 12;

struct HashTable{
#define MOD 10007
	vector<hash_t> ele[MOD];
	int &operator[] (int i){
		int code = i % MOD;
		int n = ele[code].size();
		for(int j = 0; j < n; j ++)
			if(ele[code][j].first == i)
				return ele[code][j].second;
		ele[code].push_back(make_pair(i, -1));
		return ele[code][n].second;
	}
} toId;
mask_t toMask[N_MASK_MAX];

int nRow, nCol;
int maskCnt;
int64 f[2][N_MASK_MAX];
bool fine[WIDTH_MAX][WIDTH_MAX];

int getBit(mask_t x, int k){
	return (x >> (2 * k)) & 3;
}

void modifyBit(mask_t &x, int k, int newVal){
	mask_t remain = x & ((1 << (k << 1)) - 1);
	x >>= (k + 1) << 1;
	x <<= 2;
	x += newVal;
	x <<= k << 1;
	x += remain;
}

void dfs(mask_t x, int i, int remain){
	if(remain < 0)
		return;
	if(i == nCol + 1){
		if(remain == 0){
			toMask[maskCnt] = x;
			toId[x] = maskCnt;
			maskCnt ++;
		}
		return;
	}
	dfs(x, i + 1, remain);
	dfs(x | (1 << (i << 1)), i + 1, remain + 1);
	dfs(x | (2 << (i << 1)), i + 1, remain - 1);
}

int findNextMatch(mask_t s, int i){
	int top = 1;
	for(int j = i + 1; ; j ++){
		if(getBit(s, j) == 1)
			top ++;
		else if(getBit(s, j) == 2)
			top --;
		if(top == 0)
			return j;
	}
}

int findPrevMatch(mask_t s, int i){
	int top = 1;
	for(int j = i - 1; ; j --){
		if(getBit(s, j) == 1)
			top --;
		else if(getBit(s, j) == 2)
			top ++;
		if(top == 0)
			return j;
	}
}

int main(){
	scanf("%d%d", &nRow, &nCol);

	for(int i = 0; i < nRow; i ++){
		static char str[20];
		scanf("%s", str);
		for(int j = 0; j < nCol; j ++)
			fine[i][j] = str[j] == '.';
	}

	int lastX, lastY;

	for(lastX = nRow - 1, lastY = nCol - 1; 
			lastX >= 0 && !fine[lastX][lastY];
			lastY ? lastY -- : (lastX --, lastY = nCol - 1));

	dfs(0, 0, 0);
	int cur = 0;
	f[cur][0] = 1;
	for(int i = 0; i < nRow; i ++, cur ^= 1){
		for(int j = 0; j < nCol; j ++, cur ^= 1){
			memset(f[!cur], 0, sizeof(f[cur]));
			for(int k = 0; k < maskCnt; k ++){
				if(f[cur][k]){
					int s = toMask[k];
					int lBit = getBit(s, j),
						uBit = getBit(s, j + 1);
					if(!fine[i][j]){
						if(lBit == 0 && uBit == 0)
							f[!cur][k] += f[cur][k];
					}
					else{
						if(lBit == 0 && uBit == 0){/*{{{*/
							int newS = s;
							modifyBit(newS, j, 1);
							modifyBit(newS, j + 1, 2);
							f[!cur][toId[newS]] += f[cur][k];
						}	/*}}}*/
						else if(lBit == 0 && uBit == 1){/*{{{*/
							f[!cur][k] += f[cur][k];
							int newS = s;
							modifyBit(newS, j, 1);
							modifyBit(newS, j + 1, 0);
							f[!cur][toId[newS]] += f[cur][k];
						}/*}}}*/
						else if(lBit == 0 && uBit == 2){/*{{{*/
							f[!cur][k] += f[cur][k];
							int newS = s;
							modifyBit(newS, j, 2);
							modifyBit(newS, j + 1, 0);
							f[!cur][toId[newS]] += f[cur][k];
						}/*}}}*/
						else if(lBit == 1 && uBit == 0){/*{{{*/
							f[!cur][k] += f[cur][k];
							int newS = s;
							modifyBit(newS, j, 0);
							modifyBit(newS, j + 1, 1);
							f[!cur][toId[newS]] += f[cur][k];
						}/*}}}*/
						else if(lBit == 1 && uBit == 1){/*{{{*/
							int p = findNextMatch(s, j + 1);
							int newS = s;
							modifyBit(newS, j, 0);
							modifyBit(newS, j + 1, 0);
							modifyBit(newS, p, 1);
							f[!cur][toId[newS]] += f[cur][k];
						}/*}}}*/
						else if(lBit == 1 && uBit == 2){/*{{{*/
							if(i == lastX && j == lastY){
								printf(INT64_FMT "\n", f[cur][k]);
								return 0;
							}
						}/*}}}*/
						else if(lBit == 2 && uBit == 0){/*{{{*/
							f[!cur][k] += f[cur][k];
							int newS = s;
							modifyBit(newS, j, 0);
							modifyBit(newS, j + 1, 2);
							f[!cur][toId[newS]] += f[cur][k];
						}/*}}}*/
						else if(lBit == 2 && uBit == 1){/*{{{*/
							int newS = s;
							modifyBit(newS, j, 0);
							modifyBit(newS, j + 1, 0);
							f[!cur][toId[newS]] += f[cur][k];
						}/*}}}*/
						else{/*{{{*/
							int p = findPrevMatch(s, j);
							int newS = s;
							modifyBit(newS, j, 0);
							modifyBit(newS, j + 1, 0);
							modifyBit(newS, p, 2);
							f[!cur][toId[newS]] += f[cur][k];
						}/*}}}*/
					}
				}
			}
		}
		memset(f[!cur], 0, sizeof(f[cur]));
		for(int k = 0; k < maskCnt; k ++)
			if(f[cur][k]){
				int s = toMask[k];
				if(getBit(s, nCol) != 0)
					continue;
				int newS = s;
				newS <<= 2;
				newS &= (1 << ((nCol + 1) << 1)) - 1;
				f[!cur][toId[newS]] += f[cur][k];
			}
	}
	printf("0\n");
}
