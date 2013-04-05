#include <cstdio>
#include <cstring>
#include <algorithm>

#define RESET 1

const int N_ELE_MAX = 110000;
const int INFINITY = 0x3f3f3f3f;

struct 
{
	int x, y, z;
	char type[2];
} cmd[N_ELE_MAX];
int data[N_ELE_MAX], n_data, n_cmd;

namespace solve_p
{

	struct Tag
	{
		int acc, best;
		Tag()
		{
			acc = best = 0;
		}
	};

	struct Info
	{
		int now_max, past_max;
		bool e;
		Info(){e = false; now_max = past_max = -INFINITY;}
	};

	Info operator+ (const Info &a, const Info &b)
	{
		if(! a.e) return b;
		if(! b.e) return a;
		Info ret;
		ret.e = true;
		ret.now_max = std::max(a.now_max, b.now_max);
		ret.past_max = std::max(a.past_max, b.past_max);
		return ret;
	}

	struct Node
	{
		int l, r;
		Info info;
		Tag tag;
		bool marked;
		Node()
		{
			l = r = marked = 0;
		}
	} node[N_ELE_MAX * 4];

	void update(int i)
	{
		node[i].info = node[i * 2].info + node[i * 2 + 1].info;
	}

	void mark(int i, int val, int type)
	{
		if(type == RESET)
		{
			node[i].tag.acc = 0;
			node[i].info.now_max = 0;
		}
		node[i].tag.acc += val;
		node[i].tag.best = std::max(node[i].tag.best, node[i].tag.acc);
		node[i].info.now_max += val;
		node[i].info.past_max = std::max(node[i].info.past_max, node[i].info.now_max);
		node[i].marked = true;
	}

	void pass(int i, int p)
	{
		node[i].tag.best = std::max(node[i].tag.best, node[i].tag.acc + node[p].tag.best);
		node[i].tag.acc += node[p].tag.acc;
		node[i].info.past_max = std::max(node[i].info.past_max, node[i].info.now_max + node[p].tag.best);
		node[i].info.now_max += node[p].tag.acc;
		node[i].marked = true;
	}

	void push_down(int i)
	{
		if(node[i].marked)
		{
			pass(i * 2, i);
			pass(i * 2 + 1, i);

			node[i].tag.best = node[i].tag.acc = node[i].marked = 0;
		}
	}

	void build(int i, int l, int r)
	{
		node[i].l = l, node[i].r = r;
		node[i].info.e = true;
		if(l == r)
		{
			node[i].info.now_max = node[i].info.past_max = data[l];
			return;
		}
		build(i * 2, l, (l + r) / 2);
		build(i * 2 + 1, (l + r) / 2 + 1, r);
		update(i);
	}

	void change(int i, int l, int r, int val, int type)
	{
		if(node[i].l > r || node[i].r < l)
			return;
		if(l <= node[i].l && node[i].r <= r)
		{
			mark(i, val, type);
			return;
		}
		push_down(i);
		change(i * 2, l, r, val, type);
		change(i * 2 + 1, l, r, val, type);
		update(i);
	}

	Info ask(int i, int l, int r)
	{
		if(node[i].l > r || node[i].r < l)
			return Info();
		if(l <= node[i].l && node[i].r <= r)
			return node[i].info;
		push_down(i);
		Info ret = ask(i * 2, l, r) + ask(i * 2 + 1, l, r);
		update(i);
		return ret;
	}

	void main()
	{
		build(1, 1, n_data);
		for(int i = 1; i <= n_cmd; i ++)
		{
			int x = cmd[i].x, y = cmd[i].y, z = cmd[i].z;
			if(cmd[i].type[0] == 'Q')
				printf("%d\n", ask(1, x, y).now_max);
			else if(cmd[i].type[0] == 'A')
				printf("%d\n", ask(1, x, y).past_max);
			else
			{
				if(cmd[i].type[0] == 'P')
					change(1, x, y, z,! RESET);
				else
					change(1, x, y, z, RESET);
			}
		}
	}
}

namespace solve_force
{
	int past[N_ELE_MAX];
	void main()
	{
		memcpy(past, data, sizeof(data));
		for(int i = 1; i <= n_cmd; i ++)
		{
			int x = cmd[i].x, y = cmd[i].y, z = cmd[i].z;
			if(cmd[i].type[0] == 'Q')
			{
				int ret = -INFINITY;
				for(int i = x; i <= y; i ++)
					ret = std::max(ret, data[i]);
				printf("%d\n", ret);
			}
			else if(cmd[i].type[0] == 'A')
			{
				int ret = -INFINITY;
				for(int i = x; i <= y; i ++)
					ret = std::max(ret, past[i]);
				printf("%d\n", ret);
			}
			else
			{
				if(cmd[i].type[0] == 'P')
					for(int i = x; i <= y; i ++)
					{
						data[i] += z;
						past[i] = std::max(past[i], data[i]);
					}
				else
					for(int i = x; i <= y; i ++)
					{
						data[i] = z;
						past[i] = std::max(past[i], data[i]);
					}
			}
		}
	}
}

namespace solve_q
{
	struct Tag
	{
		int acc, new_val;
		bool reset;
		Tag()
		{
			new_val = acc = 0;
			reset = false;
		}
	};

	Tag operator+ (const Tag &a, const Tag &b)
	{
		Tag ret = a;
		if(b.reset)
		{
			ret.new_val = b.new_val, ret.reset = true;
			ret.acc = 0;
		}
		ret.acc += b.acc;
		return ret;
	}

	struct Info
	{
		int now_max;
		bool e;
		void append(Tag tag)
		{
			if(tag.reset)
				now_max = tag.new_val;
			now_max += tag.acc;
		}
		Info(){e = false;}
	};

	Info operator+ (const Info &a, const Info &b)
	{
		if(! a.e) return b;
		if(! b.e) return a;
		Info ret;
		ret.e = true;
		ret.now_max = std::max(a.now_max, b.now_max);
		return ret;
	}

	struct Node
	{
		int l, r;
		Info info;
		Tag tag;
		Node()
		{
			l = r = 0;
			info.now_max = -INFINITY;
		}
	} node[N_ELE_MAX * 4];

	void update(int i)
	{
		node[i].info = node[i * 2].info + node[i * 2 + 1].info;
	}

	void mark(int i, const Tag &tag)
	{
		node[i].tag = node[i].tag + tag;
		node[i].info.append(tag);
	}

	void push_down(int i)
	{
		mark(i * 2, node[i].tag);
		mark(i * 2 + 1, node[i].tag);
		node[i].tag = Tag();
	}

	void build(int i, int l, int r)
	{
		node[i].l = l, node[i].r = r;
		node[i].info.e = true;
		if(l == r)
		{
			node[i].info.now_max = data[l];
			return;
		}
		build(i * 2, l, (l + r) / 2);
		build(i * 2 + 1, (l + r) / 2 + 1, r);
		update(i);
	}

	void change(int i, int l, int r, int val, int type)
	{
		if(node[i].l > r || node[i].r < l)
			return;
		if(l <= node[i].l && node[i].r <= r)
		{
			Tag tag;
			if(type == RESET)
				tag.new_val = val, tag.reset = true;
			else
				tag.acc = val, tag.reset = false;
			mark(i, tag);
			return;
		}
		push_down(i);
		change(i * 2, l, r, val, type);
		change(i * 2 + 1, l, r, val, type);
		update(i);
	}

	Info ask(int i, int l, int r)
	{
		if(node[i].l > r || node[i].r < l)
			return Info();
		if(l <= node[i].l && node[i].r <= r)
			return node[i].info;
		push_down(i);
		Info ret = ask(i * 2, l, r) + ask(i * 2 + 1, l, r);
		update(i);
		return ret;
	}

	void main()
	{
		build(1, 1, n_data);
		for(int i = 1; i <= n_cmd; i ++)
		{
			int x = cmd[i].x, y = cmd[i].y, z = cmd[i].z;
			if(cmd[i].type[0] == 'Q')
				printf("%d\n", ask(1, x, y).now_max);
			else
			{
				if(cmd[i].type[0] == 'P')
					change(1, x, y, z,! RESET);
				else
					change(1, x, y, z, RESET);
			}
		}
	}
}

int appear[256];
int main()
{
	freopen("t.in", "r", stdin);
	scanf("%d", &n_data);
	for(int i = 1; i <= n_data; i ++)
		scanf("%d", &data[i]);
	scanf("%d", &n_cmd);
	for(int i = 1; i <= n_cmd; i ++)
	{
		scanf("%s%d%d", cmd[i].type, &cmd[i].x, &cmd[i].y);
		if(cmd[i].type[0] == 'P' || cmd[i].type[0] == 'C')
			scanf("%d", &cmd[i].z);
		appear[cmd[i].type[0]] = true;
	}
	if(n_data <= 1000)
		solve_force::main();
	else if(appear['C'] == 0)
		solve_p::main();
	else
		solve_q::main();
}
