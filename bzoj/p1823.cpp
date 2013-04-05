#include <cstdio>
#include <cstring>
#include <algorithm>
using namespace std;

const int V_MAX = 200, E_MAX = 2000;

struct Edge
{
	int to;
	Edge *next;
};

struct Stack
{
        int cnt, stk[V_MAX];
        Stack(){cnt = 0;}
        int top(){return stk[cnt - 1];}
        void pop(){cnt --;}
        void push(int x){stk[cnt ++] = x;}
};
 
int n_edge, n_scc, top;
Edge edge[E_MAX], *begin[V_MAX], *trace[E_MAX];
int dfn[V_MAX], belong[V_MAX];
int low[V_MAX], vtx[V_MAX];
Stack stk;
bool in_stk[V_MAX];
 
void add_edge(int u, int v)
{
        Edge *e = &edge[n_edge ++];
        e->to = v, e->next = begin[u];
        begin[u] = e;
}
 
 
void pop_stack(int u)
{
        if(low[u] == dfn[u])
        {
                while(1)
                {
                        int v = stk.top();
                        stk.pop(), in_stk[v] = false;
                        belong[v] = n_scc;
                        if(v == u)
                                break;
                }
                n_scc ++;
        }
        top --;
}
 
void push_stack(int u)
{
        static int idx = 0;
        low[u] = dfn[u] = idx ++;
        stk.push(u), in_stk[u] = true;
        trace[top] = begin[u];
        vtx[top] = u;
        top ++;
}
 
void tarjan(int st)
{
        top = 0;
        push_stack(st);
        while(top)
        {
                Edge *&e = trace[top - 1];
                if(!e)
                {
                        int v = vtx[top - 1];
                        pop_stack(v);
                        if(top)
                        {
                                int u = vtx[top - 1];
                                low[u] = min(low[u], low[v]);
                        }
                        continue;
                }
 
                int u = vtx[top - 1], v = e->to;
                if(dfn[v] == -1)
                        push_stack(v);
                else if(in_stk[v])
                        low[u] = min(low[u], dfn[v]);
                e = e->next;
        }
}

void solve()
{
#define H(x) (x)
#define M(x) ((x) + n)
	int n, m;
	scanf("%d %d\n", &n, &m);
	memset(begin, 0, sizeof(Edge*) * 2 * n);
	n_edge = n_scc = 0;
	while(m --)
	{
		char s1, s2;
		int t1, t2;
		scanf("%c%d %c%d\n", &s1, &t1, &s2, &t2);
		t1 --, t2 --;
		if(s1 == 'm' && s2 == 'm')
			add_edge(H(t1), M(t2)), add_edge(H(t2), M(t1));
		else if(s1 == 'm' && s2 == 'h')
			add_edge(H(t1), H(t2)), add_edge(M(t2), M(t1));
		else if(s1 == 'h' && s2 == 'm')
			add_edge(M(t1), M(t2)), add_edge(H(t2), H(t1));
		else
			add_edge(M(t1), H(t2)), add_edge(M(t2), H(t1));
	}
	memset(dfn, -1, sizeof(int) * 2 * n);
	for(int u = 0; u < 2 * n; u ++)
		if(dfn[u] == -1)
			tarjan(u);
	for(int u = 0; u < n; u ++)
		if(belong[u] == belong[u + n])
		{
			printf("BAD\n");
			return;
		}
	printf("GOOD\n");
}

int main()
{
	freopen("t.in", "r", stdin);
	int n_test;
	scanf("%d\n", &n_test);
	while(n_test --)
		solve();
}
