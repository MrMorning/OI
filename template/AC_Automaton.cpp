#include <queue>
#include <map>
#include <vector>
#include <string>

#define FOREACH(I, C) for(__typeof((C).begin()) I = (C).begin(); I != (C).end(); I ++)

using namespace std;

const int N_ALPHABET_MAX = 26;
const int N_NODE_MAX = 100000;

struct Node{
	Node *fail, *go[N_ALPHABET_MAX];	
	bool isPattern;
	int idx;
} *root;
Node nodePool[N_NODE_MAX];
int nodeCnt = 0;
map<char, int> convert;
int alphaNum;

Node *allocNode(){
	Node *x = nodePool + nodeCnt;
	x->idx = nodeCnt ++;
	return x;
}

void buildAC(const vector<string> pattern){
	static queue<Node*> Q;

	root = allocNode();
	FOREACH(s, pattern){
		Node *u = root;
		for(int i = 0; i < (int)s->length(); i ++){
			int ch = convert[(*s)[i]];
			if(u->go[ch] == NULL)
				u->go[ch] = allocNode();
			u = u->go[ch];
		}
		u->isPattern = true;
	}

	for(int a = 0; a < alphaNum; a ++)
		if(root->go[a]){
			root->go[a]->fail = root;
		   	Q.push(root->go[a]);
		}
		else
			root->go[a] = root;

	while(!Q.empty()){
		Node *u = Q.front(); Q.pop();
		for(int a = 0; a < alphaNum; a ++){
			if(u->go[a] == NULL)
				u->go[a] = u->fail->go[a];
			else{
				u->go[a]->fail = u->fail->go[a];
			   	u->go[a]->isPattern |= u->fail->go[a]->isPattern;
			   	Q.push(u->go[a]);
			}
		}
	}
}

int main(){
}
