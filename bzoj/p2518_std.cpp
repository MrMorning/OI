#include <cstdio>
#include <cstdlib>
#include <cstring>
#include <algorithm>
#include <iostream>
using namespace std;
const int MAXN = 200001;
struct Trep{
	int data[4];
	int & operator [] (int k) { return data[k]; }
	Trep() { for (int i = 0; i < 4; i++) data[i] = i; }
	Trep operator + (Trep A) const
	{
		Trep ret;
		for (int i = 0; i < 4; i++) ret[i] = A[data[i]];
		return ret;
	}
} now;
int ret;
char s[MAXN];
struct Tsgt{
	int num[MAXN * 4][4]; Trep rep[MAXN * 4];
	void make(int idx, char ch)
	{
		memset(num[idx], 0, sizeof(num[idx]));
		switch(ch){
			case 'L' : rep[idx][0] = 3; rep[idx][1]= 0; rep[idx][2]= 2; rep[idx][3]= 1; num[idx][1] = 1; break;
			case 'R' : rep[idx][0] = 3; rep[idx][1]= 1; rep[idx][2]= 0; rep[idx][3]= 2; num[idx][2] = 1; break;
			case 'B' : rep[idx][0] = 3; rep[idx][1]= 2; rep[idx][2]= 1; rep[idx][3]= 0; num[idx][3] = 1; break;
		}
	}
	void update(int idx)
	{
		rep[idx] = rep[idx * 2] + rep[idx * 2 + 1];
		for (int i = 0; i < 4; i++) num[idx][i] = num[idx * 2][i];
		for (int i = 0; i < 4; i++) num[idx][i] += num[idx * 2 + 1][rep[idx * 2][i]]; 
	}
	void build(int idx, int l, int r)
	{
		int m = l + r >> 1;
		if (l == r) make(idx, s[l]);
		else{
			int m = l + r >> 1;
			build(idx * 2, l, m);
			build(idx * 2 + 1, m + 1, r);
			update(idx);
		}
	}
	void change(int idx, int l, int r, int x)
	{
		if (l == r) make(idx, s[l]);
		else{
			int m = l + r >> 1;
			if (x <= m) change(idx * 2, l, m, x); else change(idx * 2 + 1, m + 1, r, x);
			update(idx);
		}
	}
	void query(int idx, int l, int r, int ll, int rr)
	{
		if (ll > rr) return;
		if (ll <= l && rr >= r){
			ret += num[idx][now[0]]; 
			now = now + rep[idx];
			return;
		}
		int m = l + r >> 1;
		if (ll > m) now = now + rep[idx * 2];
		if (ll <= m) query(idx * 2, l, m, ll, rr);
		if (rr > m) query(idx * 2 + 1, m + 1, r, ll, rr);
	}
} sgt;
int n;
int main()
{
	freopen("t.in", "r", stdin);
//	freopen("t.out", "w", stdout);
	scanf("%d", &n);
	scanf("%s", s);
	sgt.build(1, 0, n - 1);
	int Q; scanf("%d", &Q);
	while(Q--){
		int op; int l, r, x; char ch; scanf("%d", &op);
		switch(op){
			case 0 : scanf("%d %c", &x, &ch); --x; s[x] = ch; sgt.change(1, 0, n - 1, x); break;     
			case 1 : scanf("%d %d", &l, &r); ret = 0; 
					 Trep temp; now = temp;
					 if (l == 1) ++ret, ++l;
					 sgt.query(1, 0, n - 1, l - 2, r - 2);
					 printf("%d\n", ret);
		}
	}
}
