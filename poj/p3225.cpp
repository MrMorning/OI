#include <cstdio>
#include <cstdlib>
#include <cstring>
#include <algorithm>

using std::sort;

const int MAXN = 1 << 17;
const int UPPERLIM = (1 << 17) - 1;

struct Node
{
	int l, r, val;//val = 0,1, -1--- multi colors
	int tag;//tag = 0 -- all 0; 1 -- all 1; 2 -- reverse; -1 -- undef
} node[MAXN << 4];

struct Interval
{
	int st, en;
	bool operator< (const Interval &x)const
	{
		return en < x.en;
	}
} interval[MAXN];
int interval_num = 0;

void Update(int i)
{
	if(node[i * 2].val == node[i * 2 + 1].val)
		node[i].val = node[i * 2].val;
	else
		node[i].val = -1;
}

void Build(int i, int l, int r)
{
	node[i].l = l, node[i].r = r;
	node[i].val = node[i].tag = -1;
	if(l == r) 
		return;
	Build(i * 2, l, (l + r)/2);
	Build(i * 2 + 1, (l + r)/2 + 1, r);
}

void Mark(int i, int c)
{
	if(c == 2)
	{
		if(node[i].val != -1)
			node[i].val ^= 1;
		if(node[i].tag == -1)
			node[i].tag = 2;
		else if(node[i].tag == 2)
			node[i].tag = -1;
		else
			node[i].tag ^= 1;
	}
	else
		node[i].val = node[i].tag = c;
}

void Push_Down(int i)
{
	if(node[i].tag != -1)
	{
		Mark(i * 2, node[i].tag), Mark(i * 2 + 1, node[i].tag);
		node[i].tag = -1;
	}
}

void Change(int i, int l, int r, int a, int b, int c)
{
	if(l > b || r < a) return;
	if(a <= l && r <= b)
	{
		Mark(i, c);
		return;
	}
	Push_Down(i);
	Change(i * 2, l, (l + r) >> 1, a, b, c);
	Change(i * 2 + 1, ((l + r) >> 1) + 1, r, a, b, c);
	Update(i);
}

void Push_All(int i, int l, int r)
{
	if(l == r) return;
	Push_Down(i);
	Push_All(i * 2, l, (l + r) / 2);
	Push_All(i * 2 + 1, (l + r) / 2 + 1, r);
}
void debug()
{

	for(int i = 1; i <= 2 * UPPERLIM + 1; i ++)
		if(node[i].val != -1 || node[i].tag != -1)
		printf("NODE: %d, l: %d, r: %d, val: %d , tag: %d\n", i, node[i].l, node[i].r, node[i].val, node[i].tag);
	printf("\n");
}

int main()
{
	freopen("t.in", "r", stdin);
	Build(1, 0, UPPERLIM);
	Change(1, 0, UPPERLIM, 0, UPPERLIM, 0);
	while(! feof(stdin))
	{
		char cmd, ch_a, ch_b;
		int a, b;
		scanf("%c %c%d,%d%c\n", &cmd, &ch_a, &a, &b, &ch_b);
		if(ch_a == '[') a = a * 2;
		else a = a * 2 + 1;
		if(ch_b == ']') b = b * 2;
		else b = b * 2 - 1;
		switch(cmd)
		{
			case 'U': 
				Change(1, 0, UPPERLIM, a, b, 1);
				break;
			case 'I':
				if(a > 0)
					Change(1, 0, UPPERLIM, 0, a - 1, 0);
				if(b < UPPERLIM)
					Change(1, 0, UPPERLIM, b + 1, UPPERLIM, 0);
				break;
			case 'C':
				if(a > 0)
					Change(1, 0, UPPERLIM, 0, a - 1, 0);
				if(b < UPPERLIM)
					Change(1, 0, UPPERLIM, b + 1, UPPERLIM, 0);
				Change(1, 0, UPPERLIM, a, b, 2);
				break;
			case 'D':
				Change(1, 0, UPPERLIM, a, b, 0);
				break;
			case 'S':
				Change(1, 0, UPPERLIM, a, b, 2);
				break;
		}
	}
	Push_All(1, 0, UPPERLIM);
	for(int i = UPPERLIM + 1; i <= 2 * UPPERLIM + 1; i ++)
	{
		if(node[i].val == 1)
		{
			int j = i;
			while(node[j + 1].val == 1) j ++;
			interval[++ interval_num].st = i - UPPERLIM - 1;
			interval[interval_num].en = j - UPPERLIM - 1;
			i = j;
		}
	}
	if(interval_num == 0)
		printf("empty set");
	else
	{
		sort(interval + 1, interval + 1 + interval_num);
		for(int i = 1; i <= interval_num; i ++)
		{
			Interval &tmp = interval[i];
			if(tmp.st & 1)
				printf("(%d", (tmp.st - 1) / 2);
			else
				printf("[%d", tmp.st / 2);
			printf(",");
			if(tmp.en & 1)
				printf("%d)", (tmp.en + 1) / 2);
			else
				printf("%d]", tmp.en / 2);
			printf(" ");
		}
	}
	printf("\n");
}
