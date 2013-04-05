#include <iostream>
#include <cstdio>
#include <memory.h>
using namespace std;
const int maxn = 100002;
const int maxe = 500002;
struct node
{
    int v,w;
    int next;
}edge[maxe << 1];
int head[maxn],ans[maxn],father[maxn],val[maxn];
int m,n,idx,black,white;

void init()
{
    memset(head,-1,sizeof(head));
    memset(ans,-1,sizeof(ans));
    memset(val,-1,sizeof(val));
    for(int i=1;i<=n;i++)
    {
        father[i] = i;
    }
    idx = 0;
    return;
}

void addedge(int u,int v,int w,int ww)
{
    edge[idx].v = v;
    edge[idx].w = w;
    edge[idx].next = head[u];
    head[u] = idx++;

    edge[idx].v = u;
    edge[idx].w = ww;
    edge[idx].next = head[v];
    head[v] = idx++;
    return;
}

void read()
{
    int u,v,w,ww;
    for(int i=0;i<m;i++)
    {
        scanf("%d %d %d %d",&u,&v,&w,&ww);
        addedge(u,v,w,ww);
    }
    return;
}

bool dfs(int fa,int st,int color)
{
    father[st] = fa;
    if(ans[st] == -1)
    {
        ans[st] = color;
        if(color == 0) black++;
        else white++;
    }
    else
    {
        return (ans[st] == color);
    }
    for(int i=head[st];i != -1;i=edge[i].next)
    {
        if(edge[i].w == edge[i^1].w)
        {
            if(dfs(fa,edge[i].v , color^1) == false) return false;
        }
        else
        {
            if(dfs(fa,edge[i].v , color) == false) return false;
        }
    }
    return true;
}

void out()
{
    puts("YES");
    int cnt = 0;
    for(int i=1;i<=n;i++)
    {
        if(ans[i] == val[father[i]])
        {
            cnt++;
        }
    }
    printf("%d\n",cnt);
    bool flag = false;
    for(int i=1;i<=n;i++)
    {
        if(ans[i] == val[father[i]])
        {
            if(flag) printf(" ");
            printf("%d",i);
            flag = true;
        }
    }
    if(cnt) puts("");
    return;
}

void solve()
{
    bool flag = true;
    for(int i=1;i<=n;i++)
    {
        if(ans[i] == -1)
        {
            black = white = 0;
            if(dfs(i , i , 0) == false)
            {
                flag = false;
                break;
            }
            val[i] = (black <= white) ? 0 : 1;
        }
    }
    if(flag == false) puts("NO");
    else out();
    return;
}

int main()
{
	freopen("t.in", "r", stdin);
    while(~scanf("%d %d",&n,&m))
    {
        init();
        read();
        solve();
    }
    return 0;
}
