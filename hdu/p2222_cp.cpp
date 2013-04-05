#include <cstdio>
#include <cstring>
const int MAXN = 2000000;
const int MAXZ = 26;
struct node_t
{
	node_t *next[MAXZ], *fail;
	int k;
};
node_t trie[MAXN], *queue[MAXN];
int nNode;

node_t *allocNode()
{
	memset(trie + nNode, 0, sizeof(node_t));
	return &trie[nNode ++];
}

node_t *initRoot()
{
	nNode = 0;
	node_t *root = allocNode();
	for(int a = 0; a < MAXZ; a ++)
		root->next[a] = root;
	return root;
}

void insert(node_t *root, char *s)
{
	node_t *u = root;
	int ch = *s - 'a';
	if(root->next[ch] == root)
		root->next[ch] = allocNode();
	while(*s)
	{
		ch = *s - 'a';
		if(u->next[ch] == NULL)
			u->next[ch] = allocNode();
		u = u->next[ch];
		s ++;
	}
	(u->k) ++;
}

void buildAC(node_t *root)
{
	root->fail = NULL;
	int head = 0, tail = 0;
	for(int a = 0; a < MAXZ; a ++)
	{
		node_t *u = root->next[a];
		if(u != root)
			u->fail = root, queue[tail ++] = u;
	}

	for(; head != tail; head ++)
	{
		node_t *u = queue[head], *v;
		for(int a = 0; a < 26; a ++)
			if((v = u->next[a]) != NULL)
			{
				queue[tail ++] = v;
				node_t *w = u->fail;
				while(w->next[a] == NULL)
					w = w->fail;
				v->fail = w->next[a];
			}
	}
}

int query(node_t *root, char *s)
{
	node_t *u = root;
	int cnt = 0;
	while(*s)
	{
		int ch = *s - 'a';
		while(u->next[ch] == NULL)
			u = u->fail;
		u = u->next[ch];
		node_t *v = u;
		while(v != root && v->k != -1)
		{
			cnt += v->k;
			v->k = -1;
			v = v->fail;
		}
		s ++;
	}
	return cnt;
}

void solve()
{
	int nPtrn;
	scanf("%d\n", &nPtrn);
	node_t *root = initRoot();
	for(int i = 0; i < nPtrn; i ++)
	{
		char ptrn[50];
		gets(ptrn);
		insert(root, ptrn);
	}
	buildAC(root);
	char s[1000000];
	gets(s);
	printf("%d\n", query(root, s));
}

int main()
{
	freopen("t.in", "r", stdin);
	int nTest;
	scanf("%d\n", &nTest);
	while(nTest --)
		solve();
}
