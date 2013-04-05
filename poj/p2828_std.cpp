#include <iostream>
#include <cstdio>
using namespace std;

#define nMAX 200002

typedef struct Node{
	int l,r;
	int c;    // 表示要在区间[l,r]中插入的人数为c
	Node *lc, *rc;
}Node, *Tree;

Node nd[2*nMAX+10];
int nIndex;
int n;
int Val[nMAX], Pos[nMAX];
int Ans[nMAX];

Tree create(int l, int r)
{
	Tree T = &nd[nIndex++];
	T->l = l;
	T->r = r;
	T->c = r-l+1;
	if(l==r){
		T->lc = T->rc = NULL;
	}
	else{
		int mid = (l+r)>>1;
		T->lc = create(l, mid);
		T->rc = create(mid+1, r);
	}
	return T;
}

void insert(Tree T, int val, int pos)
{
	T->c--;
	if(T->l == T->r) {
		Ans[T->l] = val;
	}
	else{
		int mid = (T->l+T->r)>>1;
		if(pos<=T->lc->c)
			insert(T->lc, val, pos);
		else
			insert(T->rc, val, pos-T->lc->c);
	}
}

int main()
{
	freopen("t.in", "r", stdin);
	int i;
	while(scanf("%d", &n)!=EOF) {
		nIndex = 0;
		Tree T = create(0, n-1);
		for(i=0; i<n; i++)
			scanf("%d%d", &Pos[i], &Val[i]);
		for(i=n-1; i>=0; i--)
			insert(T, Val[i], Pos[i]+1);
		for(i=0; i<n; i++)
			printf("%d ", Ans[i]);
		printf("\n");
	}
	return 0;
}
