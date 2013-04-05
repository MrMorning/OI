#include <iostream>
#include <cstdio>
using namespace std;

#define nMAX 65535*2
enum Mark{ COV, DISCOV, UNKNOWN };

typedef struct Node{
	int l, r; // 区间
	Mark mc;     // 区间属性，全覆盖，全未覆盖，半覆盖
	bool flag;   // 本区间是否取反
	bool bf;     // flag使能开关,表示以下的子区间的取反全无效
	Node *lc, *rc;
}Node, *Tree;

Node nd[2*nMAX+10];
int nIndex;
Tree T;

bool cover[nMAX+10];
int l, r;
char cl, cr;
char opt;

Tree create(int l, int r)
{
	Tree T = &nd[nIndex++];
	T->l = l;
	T->r = r;
	T->mc = DISCOV;
	T->flag = false;
	T->bf = false;
	if( l == r )
		T->lc = T->rc = NULL;
	else{
		int mid = ( l + r ) >> 1;
		T->lc = create(l, mid);
		T->rc = create(mid+1, r);
	}
	return T;
}

void inverse(Tree T, int l, int r)
{
	if( r < l ) return;
	if( l == T->l && r == T->r ){
		T->flag = !T->flag;
	}
	else{
		int mid = ( T->l + T->r ) >> 1;
		if( T->bf ){
			T->lc->flag = T->rc->flag = false;
			T->lc->bf = T->rc->bf = true;
			T->bf = false;
		}
		if( r <= mid ){
			inverse(T->lc, l, r);
		}
		else if( l > mid ){
			inverse(T->rc, l, r);
		}
		else{
			inverse(T->lc, l, mid);
			inverse(T->rc, mid+1, r);
		}
	}
}

void insert(Tree T, int l, int r, Mark mark, int nFlag)
{
	if( r < l ) return;
	if( l == T->l && r == T->r ){
		T->mc = mark;
		if( nFlag % 2 == 0 )
			T->flag = false;
		else T->flag = true;
		T->bf = true;
	}
	else{
		if( T->mc != UNKNOWN ){
			T->lc->mc = T->rc->mc = T->mc;
		}
		if( T->bf ){
			T->lc->flag = T->rc->flag = false;
			T->lc->bf = T->rc->bf = true;
			T->bf = false;
		}
		nFlag += (int)T->flag;

		int mid = ( T->l + T->r ) >> 1;
		if( r <= mid ){
			insert(T->lc, l, r, mark, nFlag);
		}
		else if( l > mid ){
			insert(T->rc, l, r, mark, nFlag);
		}
		else{
			insert(T->lc, l, mid, mark, nFlag);
			insert(T->rc, mid+1, r, mark, nFlag);
		}
		if(T->lc->mc == T->rc->mc && T->lc->mc != UNKNOWN)
			T->mc = T->lc->mc;
		else
			T->mc = UNKNOWN;
	}
}

void query(Tree T)
{
	if( T->l == T->r ){
		if( ( T->mc == COV && T->flag == false ) ||
				( T->mc == DISCOV && T->flag == true ) )
		{ cover[T->l] = true; }
	}
	else{
		if( T->mc != UNKNOWN ){
			T->lc->mc = T->rc->mc = T->mc;
		}
		if( T->bf ){
			T->lc->flag = T->rc->flag = false;
			T->lc->bf = T->rc->bf = true;
			T->bf = false;
		}
		if( T->flag ){
			T->lc->flag = !T->lc->flag;
			T->rc->flag = !T->rc->flag;
		}
		query(T->lc);
		query(T->rc);
	}
}

void putSolution(Tree T)
{
	query(T);
	int i=0, nIntv=0;
	while(i<=nMAX){
		while(i<=nMAX && !cover[i]) i++;
		if( i==nMAX+1 ) break;
		if( nIntv != 0 ) printf(" ");
		if( i%2 == 0)
			printf("[%d,", i>>1);
		else printf("(%d,", (i-1)>>1);
		while(i<=nMAX && cover[i]) i++;
		i--;
		if( i%2 == 0)
			printf("%d]", i>>1);
		else printf("%d)", (i+1)>>1);
		nIntv++;
		i++;
		if(i==nMAX+1) break;
	}
	if(nIntv==0) printf("empty set");
	printf("\n");
}

int main()
{
	freopen("t.in", "r", stdin);
	nIndex = 0;
	T = create(0, nMAX);
	while( scanf("%c %c%d,%d%c", &opt, &cl, &l, &r, &cr) == 5 )
	{
		getchar();
		l *= 2;
		r *= 2;
		if( cl == '(' ) l++;
		if( cr == ')' ) r--;
		if( l > r ) continue;
		switch(opt)
		{
			case 'U': // S <- S并T
				insert(T, l, r, COV, 0);
				break;
			case 'D': // S <- S－T
				insert(T, l, r, DISCOV, 0);
				break;
			case 'S': // S <- (S－T)并(T－S)
				inverse(T, l, r);
				break;
			case 'C': // S <- T－S
				insert(T, 0, l-1, DISCOV, 0);
				insert(T, r+1, nMAX, DISCOV, 0);
				inverse(T, l, r);
				break;
			case 'I': // S <- S交T
				insert(T, 0, l-1, DISCOV, 0);
				insert(T, r+1, nMAX, DISCOV, 0);
				break;
		}
	}
	putSolution(T);
	return 0;
}
