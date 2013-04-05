#include <iostream>
#include <cstring>
#include <cstdio>
#include <string>
#include <vector>
#include <queue>
#include <map>
#define FOREACH(it, c) for(__typeof((c).begin()) it = (c).begin(); it != (c).end(); it ++)
using namespace std;

const int ALPHABET_NUM_MAX = 50;
const int NODE_NUM_MAX = 200;
const int D_MAX = 100;

struct BigInt
{
        int num[D_MAX];
        int len;
		BigInt()
		{
			len = 0;
			memset(num, 0, sizeof(num));
		}
		BigInt(int x)
		{
			len = 0;
			memset(num, 0, sizeof(num));
			while(x)
				num[len ++] = x % 10, x /= 10;
		}
		void operator+= (const BigInt &x)
		{
			len = max(len, x.len);
			for(int i = 0; i < len; i ++)
				num[i] += x.num[i];
			for(int i = 0; i < len; i ++)
				num[i + 1] += num[i] / 10, num[i] %= 10;
			if(num[len])
				len ++;
		}
		BigInt mul(int k)
		{
			BigInt tmp = *this;
			for(int i = 0; i < len; i ++)
				tmp.num[i] *= k;
			for(int i = 0; i < D_MAX - 1; i ++)
				tmp.num[i + 1] += tmp.num[i] / 10, tmp.num[i] %= 10;
			for(int i = 0; i < D_MAX; i ++)
				if(tmp.num[i])
					tmp.len = i + 1;
			return tmp;
		}
		void output()
		{
			if(len == 0)
				printf("0\n");
			else
				for(int i = len - 1; i >= 0; i --)
					printf("%d", num[i]);
		}
};

struct Node
{
	Node *fail, *go[ALPHABET_NUM_MAX];	
	bool isPattern;
	int idx;
};
Node nodePool[NODE_NUM_MAX];
int nodeCnt = 0;
map<char, int> convert;
int alphaNum;

Node *allocNode()
{
	Node *x = &nodePool[nodeCnt ++];
	x->idx = nodeCnt - 1;
	return x;
}

void buildAC(const vector<string> pattern)
{
	Node *root = allocNode();
	FOREACH(s, pattern)
	{
		Node *u = root;
		for(int i = 0; i < (int)s->length(); u = u->go[convert[(*s)[i]]], i ++)
			if(u->go[convert[(*s)[i]]] == NULL)
				u->go[convert[(*s)[i]]] = allocNode();
		u->isPattern = true;
	}

	static queue<Node*> Q;
	for(int a = 0; a < alphaNum; a ++)
		if(root->go[a])
			root->go[a]->fail = root, Q.push(root->go[a]);
		else
			root->go[a] = root;

	while(!Q.empty())
	{
		Node *u = Q.front(); Q.pop();
		for(int a = 0; a < alphaNum; a ++)
		{
			if(u->go[a] == NULL)
				u->go[a] = u->fail->go[a];
			else
				u->go[a]->fail = u->fail->go[a], u->go[a]->isPattern |= u->fail->go[a]->isPattern, Q.push(u->go[a]);
		}
	}
}
vector<string> pattern;
int m, p;
int e[NODE_NUM_MAX][NODE_NUM_MAX];
BigInt f[51][NODE_NUM_MAX];

int main()
{
	freopen("t.in", "r", stdin);
	scanf("%d %d %d\n", &alphaNum, &m, &p);
	for(int i = 0; i < alphaNum; i ++)
	{
		char ch;
		scanf("%c", &ch);
		convert[ch] = i;
	}
	while(p --)
	{
		static string str;
		cin >> str;
		pattern.push_back(str);
	}
	buildAC(pattern);
	for(int i = 0; i < nodeCnt; i ++)
		for(int a = 0; a < alphaNum; a ++)
			if(nodePool[i].go[a])
				e[i][nodePool[i].go[a]->idx] ++;
	f[0][0] = 1;
	for(int i = 1; i <= m; i ++)
		for(int j = 0; j < nodeCnt; j ++)
		{
			Node *u = &nodePool[j];
			if(u->isPattern)
				continue;
			for(int k = 0; k < nodeCnt; k ++)
			{
				Node *v = &nodePool[k];
				if(v->isPattern)
					continue;
				if(e[v->idx][u->idx])
					f[i][j] += f[i - 1][k].mul(e[v->idx][u->idx]);
			}
		}
	BigInt ans(0);
	for(int j = 0; j < nodeCnt; j ++)
		if(!nodePool[j].isPattern)
			ans += f[m][j];
	ans.output();
}
