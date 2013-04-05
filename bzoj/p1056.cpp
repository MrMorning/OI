#include <cstdio>
#include <cstdlib>
#include <cstring>
#include <cassert>
#include <vector>
#include <algorithm>
using namespace std;
typedef pair<int, int> pair_t;
const int MOD_NUM = 1000003;
const int HASH_NUM = 100007;
const int N_MAX = 500010;
const int INF = 0x3f3f3f3f;
struct Name
{
	char str[11];
	Name(){}
	Name(const char *_str)
	{
		for(int i = 0; i < (int)strlen(_str); i ++)
			str[i] = _str[i];
		str[strlen(_str)] = 0;
	}
	bool equal(const Name &x)
	{
		if(strlen(str) != strlen(x.str))
			return false;
		for(int i = 0; i < (int)strlen(str); i ++)
			if(str[i] != x.str[i])
				return false;
		return true;
	}
	int get_hash();
};
struct Node
{
	Node *ch[2];
	pair_t key;
	int fix, size;
	Name name;
} node_pool[N_MAX], *null, *root, *hash[MOD_NUM];

int Name::get_hash()
{
	int res = 0;
	for(int i = 0; i < (int)strlen(str); i ++)
		res = (res * HASH_NUM + str[i] - 'A') % MOD_NUM;
	while(1)
	{
		if(hash[res] == NULL || equal(hash[res]->name))
			break;
		res = (res + 1 % MOD_NUM);
	}
	return res;
}

void update(Node *x)
{
	x->size = x->ch[0]->size + x->ch[1]->size + 1;
}

Node *alloc(pair_t _key, Name _name)
{
	static int free_pos = 0;
	Node *x = &node_pool[free_pos ++];
	x->key = _key, x->name = _name;
	x->size = 1, x->fix = (rand() * rand()) % INF;
	x->ch[0] = x->ch[1] = null;
	return x;
}

void rotate(Node *&x, int dir)
{
	Node *y = x->ch[!dir];
	x->ch[!dir] = y->ch[dir];
	y->ch[dir] = x;
	update(x), update(y);
	x = y;
}

void insert(Node *&now, Node *x)
{
	if(now == null)
		now = x;
	else
	{
		int t = x->key > now->key;
		insert(now->ch[t], x);
		if(now->ch[t]->fix > now->fix)
			rotate(now, !t);
		else
			update(now);
	}
}

void dispose(Node *&now)
{
	if(now->ch[0] == null && now->ch[1] == null)
		now = null;
	else
	{
		int t = now->ch[0]->fix < now->ch[1]->fix;
		rotate(now, !t);
		dispose(now->ch[!t]);
		update(now);
	}
}

void remove(Node *&now, pair_t key)
{
	if(now->key == key)
		dispose(now);
	else
	{
		int t = now->key < key;
		remove(now->ch[t], key);
		update(now);
	}
}

int rank(Node *now, pair_t key)
{
	if(now->key == key)
		return now->ch[0]->size + 1;
	if(now->key < key)
		return now->ch[0]->size + 1 + rank(now->ch[1], key);
	else
		return rank(now->ch[0], key);
}

void find(Node *now, int a, int b, vector<Node*> &buf)
{
	if(a > b)
		return;
	int k = now->ch[0]->size + 1;
	if(a > k)
		find(now->ch[1], a - k, b - k, buf);
	else if(k > b)
		find(now->ch[0], a, b, buf);
	else
	{
		find(now->ch[0], a, k - 1, buf);
		buf.push_back(now);
		find(now->ch[1], 1, b - k, buf);
	}
}

vector<Node*> vnp;
int n_cmd, cnt = 0;
int main()
{
	freopen("t.in", "r", stdin);
	null = alloc(make_pair(0, 0), "");
	null->fix = -INF;
	null->size = 0;
	root = alloc(make_pair(-INF, -INF), "CSIMSTU");
	root->fix = INF;

	scanf("%d", &n_cmd);
	for(int i = 0, s, k; i < n_cmd; i ++)
	{
		char cmd[20], tmp[20];
		cmd[0] = tmp[0] = 0;
		scanf("%s", cmd);
		if(cmd[0] == '+')
		{
			sscanf(cmd, "+%s", tmp);
			scanf("%d", &s);
			Name name(tmp);
			int h = name.get_hash();
			if(hash[h] != NULL)
			{
				remove(root, hash[h]->key);
				cnt --;
			}
			Node *x = alloc(make_pair(s, n_cmd - i), name);
			hash[h] = x;
			insert(root, x);
			cnt ++;
		}
		else
		{
			if('0' <= cmd[1] && cmd[1] <= '9')
			{
				sscanf(cmd, "?%d", &k);
				vnp.clear();
				find(root, max(2, cnt + 2 - k - 9), cnt + 2 - k, vnp);
				for(int i = (int)vnp.size() - 1; i >= 0; i --)
					printf("%s ", vnp[i]->name.str);
				printf("\n");
			}
			else
			{
				sscanf(cmd, "?%s", tmp);
				Name name(tmp);
				printf("%d\n", cnt + 2 - rank(root, hash[name.get_hash()]->key));
			}
		}
	}
}
