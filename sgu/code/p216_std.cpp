#include <cstdio>
#include <cstdlib>

using namespace std ;

const int MAX_NODE= 10010; 

int pre[MAX_NODE << 1], node[MAX_NODE << 1], last[MAX_NODE], tot; 
int N, B;

int capital[MAX_NODE], tab[MAX_NODE];
int res_tot;

inline void push_edge(int s, int t)
{
    tot ++ ;
    node[tot]= t;
    pre[tot]= last[s]; 
    last[s]= tot;
}

int construct(int node_now, int node_pre)
{
    int pos_pre= last[node_now];
    int tmp= 0;
    
    for(int pos(last[node_now]); pos; pos= pre[pos])
    {
        int node_ext= node[pos];
        
        if(node_ext == node_pre)
            continue;
        tmp+= construct(node_ext, node_now);
        if(tmp >= B)
        {
            ++ res_tot;
            for(; pos_pre != pos; pos_pre= pre[pos_pre])
            {
                int node_ext2= node[pos_pre];
                if(!tab[node_ext2] && node_ext2 != node_pre)
                    tab[node_ext2]= res_tot;
            }
            if(!tab[node_ext])
                tab[node_ext]= res_tot;
            capital[res_tot]= node_now;
            tmp= 0;
        }
    }
    if(tmp == B - 1)
    {
        ++ res_tot;
        tab[node_now]= res_tot;
        capital[res_tot]= node_now;
        return 0;
    }
    return tmp + 1;
}

void replenish(int node_now, int node_pre)
{
    for(int pos(last[node_now]); pos; pos= pre[pos])
    {
        int node_ext= node[pos];
        if(node_ext == node_pre)
            continue;
        if(tab[node_ext])
        {
            tab[1]= tab[node_ext];
            break;
        }
        replenish(node_ext, node_now);
        if(tab[1])
            break;
    }
}

void print(int node_now, int node_pre, int tab_now)
{
    for(int pos(last[node_now]); pos; pos= pre[pos])
    {
        int node_ext= node[pos];
        if(node_ext == node_pre)
            continue;
        if(!tab[node_ext])
        {
            tab[node_ext]= tab_now;
            print(node_ext, node_now, tab_now);
        }else
            print(node_ext, node_now, tab[node_ext]);
        
    }
}

void print_solution()
{
    print(1, 0, tab[1]);
    printf("%d\n", res_tot);
    for(int i(1); i<= N; ++ i)
        printf("%d ", tab[i]);
    printf("\n");
    for(int i(1); i<= res_tot; ++ i)
        printf("%d ", capital[i]);
    printf("\n");
}

int main()
{
    freopen("t.in", "r", stdin);
     
    scanf("%d%d", &N, &B);
    for(int i(1); i< N; ++ i)
    {
        int s, t;
        scanf("%d%d", &s, &t);
        push_edge(s, t);
        push_edge(t, s);
    }
    if(N < B)
    {
        printf("0\n");
        return 0;
    }
    int not_all_filled= construct(1, 0);
    
    if(not_all_filled)
        replenish(1, 0);
    
    print_solution();
    return 0 ;
}
