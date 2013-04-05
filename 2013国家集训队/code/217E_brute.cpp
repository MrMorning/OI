#include <cstdio>
#include <cassert>
#include <cstring>
const int kLenMax = 3000010;
const int kSegMax = 15005;
struct Segment {
	int st, sz;
	Segment(){}
	Segment(int _st, int _sz):
		st(_st), sz(_sz){}
} seg[kSegMax];
int nSeg;
int pos[kSegMax];

void recalcPos() {
	int curPos = 0;
	for ( int i = 1; i <= nSeg; i ++ ) {
		pos[i] = curPos+1;
		curPos += seg[i].sz;
	}
}

void insert(int p, Segment newSeg) {
	memmove(seg+p+2, seg+p+1, sizeof(Segment)*(nSeg-p));
	seg[p+1] = newSeg;
	nSeg++;
}

void add(int p, int val, int lim) {
	for ( int i = p+1; i <= nSeg; i ++ )
		if ( seg[i].st > lim )
			seg[i].st += val;
}

char str[kLenMax], res[kLenMax];

int main() {
	int n, des;
	freopen("t.in", "r", stdin);
	scanf("%s", str+1);
	scanf("%d", &des);
	scanf("%d", &n);
	seg[++nSeg] = Segment(1, strlen(str+1));
	for ( int i = 0; i < n; i ++ ) {
		int l, r;
		scanf("%d%d", &l, &r);
		if ( r >= des ) continue;
		recalcPos();
		int p = 0;
		for ( p = 1; p <= nSeg; p ++ )
			if ( pos[p] <= r && pos[p]+seg[p].sz-1 >= r ) 
				break;
		if ( r < pos[p]+seg[p].sz-1 ) {
			int nsz = r-pos[p]+1;
			insert(p, Segment(seg[p].st+(seg[p].st==pos[p]?nsz:nsz*2), seg[p].sz-nsz));
			seg[p].sz = nsz; 
		}
		insert(p, Segment(l+1, (r-l+1)/2));
		insert(p+1, Segment(l, (r-l+2)/2));
		add(p+2, r-l+1, r);
	}
	recalcPos();
	int nRes = 0;
	for ( int i = 1, ptr = 0; i <= nSeg; i ++ ) {
		if ( seg[i].st == pos[i] ) {
			for ( int t = 0; nRes < des && t < seg[i].sz; t ++ )
				res[++nRes] = str[++ptr];
		} else {
			for ( int t = 0; nRes < des && t < seg[i].sz; t ++ )
				res[++nRes] = res[seg[i].st+t*2];
		}
	}
	printf("%s", res+1);
}
