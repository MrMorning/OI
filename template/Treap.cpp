#include <cstdio>
#include <cstdlib>

const int N_MAX = 100000;

namespace bst{
	struct Node{
		int val, fix, cnt;
		int size;
		Node *ch[2];
	};

	Node nodePool[N_MAX * 30];
	int freePos = 0;

	Node *alloc(int val);
	void update(Node *x);
	void rotate(Node *&x, int c);
	void insert(Node *&x, int valNew);
	void remove(Node *&x, int valOld);
	void dispose(Node *&x);
	int countBiggerThan(Node *x, int valStd);
}


bst::Node *bst::alloc(int val){
	Node *x = &nodePool[freePos ++];
	x->val = val;
	x->fix = rand() * rand();
	x->cnt = x->size = 1;
	x->ch[0] = x->ch[1] = NULL;
	return x;
}

void bst::update(Node *x){
#define SIZE(x) ((x) == NULL ? 0 : (x)->size)
	x->size = SIZE(x->ch[0]) + x->cnt + SIZE(x->ch[1]);
}

void bst::rotate(Node *&x, int c){
	Node *y = x->ch[c];
	x->ch[c] = y->ch[!c];
	y->ch[!c] = x;
	update(x); update(y);
	x = y;
}

void bst::insert(Node *&x, int valNew){
	if(x == NULL)
		x = alloc(valNew);
	else if(x->val == valNew)
		x->size ++, x->cnt ++;
	else{
		int t = valNew > x->val;
		insert(x->ch[t], valNew);
		if(x->ch[t]->fix > x->fix)
			rotate(x, t);
		else
			update(x);
	}
}

void bst::remove(Node *&x, int valOld){
	if(x->val == valOld){
		if(x->cnt > 1)
			x->cnt --, update(x);
		else
			dispose(x);
	}
	else{
		int t = valOld > x->val;
		remove(x->ch[t], valOld);
		update(x);
	}
}

void bst::dispose(Node *&x){
	if(x->ch[0] == NULL && x->ch[1] == NULL){
		x = NULL;
		return;
	}
	else if(x->ch[0] == NULL)
		x = x->ch[1];
	else if(x->ch[1] == NULL)
		x = x->ch[0];
	else{
		int t = x->ch[0]->fix > x->ch[1]->fix;
		rotate(x, t);
		dispose(x->ch[!t]);
	}
	update(x);
}

int bst::countBiggerThan(Node *x, int valStd){
	if(x == NULL)
		return 0;
	if(x->val <= valStd)
		return countBiggerThan(x->ch[1], valStd);
	else 
		return SIZE(x->ch[1]) + x->cnt + countBiggerThan(x->ch[0], valStd);
}

int main(){
}
