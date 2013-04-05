#include <cstdio>
#include <cstdlib>
#include <cstring>
#define MIN(a, b) ((a) < (b) ? (a) : (b))
const int N_LEN_MAX = 2 * 1024 * 1024 + 10;
const int BLOCK_SIZE = 20000;
const int N_BLOCK_MAX = N_LEN_MAX / BLOCK_SIZE + 100;
struct Block
{
	char data[BLOCK_SIZE];
	int size;
   	Block *next;
	void fill(int _size, Block *_next, char str[])
	{
		size = _size, next = _next;
		memcpy(data, str, _size);
	}
};
Block blk_pool[N_BLOCK_MAX], *free_stack[N_BLOCK_MAX], *head;
int free_top, blk_idx;

Block *alloc_blk()
{
	if(free_top)
		return free_stack[-- free_top];
	else
		return &blk_pool[blk_idx ++];
}

void delete_blk(Block *b)
{
	free_stack[free_top ++] = b;
}

Block *find_blk(int &p)
{
	Block *b;
	for(b = head; b != NULL && p > b->size; p -= b->size, b = b->next);
	return b;
}

void split_blk(Block *b, int l)//[a, b] -> [a, a + l - 1] + [a + l, b]
{
	if(l == 0 || l == b->size)
		return;
	Block *t = alloc_blk();
	t->fill(b->size - l, b->next, b->data + l);
	b->size = l, b->next = t;
}
void maintain_blk(Block *b)//start at b
{
	for(; b != NULL; b = b->next)
		for(Block *t = b->next; t != NULL && b->size + t->size <= BLOCK_SIZE; t = b->next)
		{
			memcpy(b->data + b->size, t->data, t->size);
			b->size += t->size;
			b->next = t->next;
			delete_blk(t);
		}
}
void insert(int pos, int len, char str[])
{
	Block *b = find_blk(pos);
	split_blk(b, pos);
	int i = 0;
	while(1)
	{
		int new_size = MIN(len - i, BLOCK_SIZE);
		if(new_size <= 0)
			break;
		Block *t = alloc_blk();
		t->fill(new_size, b->next, str + i);
		b->next = t, b = t;
		i += new_size;
	}
	maintain_blk(b);
}
void erase(int p, int n)
{
	Block *b, *e;
	b = find_blk(p);
	split_blk(b, p);
	for(e = b->next; e != NULL && n > e->size; e = e->next)
		n -= e->size;
	split_blk(e, n);
	e = e->next;
	for(Block *t = b->next; t != e; t = t->next)
		delete_blk(t);
	b->next = e;
	maintain_blk(b);
}
void get(int p, int n, char str[])
{
	Block *b, *t;
	b = find_blk(p);
	int i = MIN(n, b->size - p);
	memcpy(str, b->data + p, i);
	for(t = b->next; t != NULL && i + t->size <= n; i += t->size, t = t->next)
		memcpy(str + i, t->data, t->size);
	if(n - i && t != NULL)
		memcpy(str + i, t->data, n - i);
	str[n] = '\0';
}
char str[N_LEN_MAX];
int main()
{
	freopen("t.in", "r", stdin);
	freopen("t.out", "w", stdout);
	str[0] = '?';
	head = alloc_blk();
	head->fill(1, NULL, str);
	int n_cmd;
	scanf("%d", &n_cmd);
	int n, k, cur = 1;
	while(n_cmd --)
	{
		char cmd[10];
		scanf("%s", cmd);
		switch(cmd[0])
		{
			case 'M':
				scanf("%d", &k);
				cur = k + 1;
				break;
			case 'I':
				scanf("%d", &n);
				for(int i = 0; i < n; i ++)
				{
					char ch;
					scanf("%c", &ch);
					str[i] = ch;
					if(ch < 32 || ch > 126)
						-- i;
				}
				insert(cur, n, str);
				break;
			case 'D':
				scanf("%d", &n);
				erase(cur, n);
				break;
			case 'G':
				scanf("%d", &n);
				get(cur, n, str);
				printf("%s\n", str);
				break;
			case 'P':
				-- cur;
				break;
			case 'N':
				++ cur;
				break;
		}
	}
}
