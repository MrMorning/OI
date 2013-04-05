#include <cstdio>
#include <cstring>
#include <cstdlib>
#include <ctime>

using namespace std ;

const int INF= 0x7fffffff;

struct INTERVAL {int l, r;};
struct NODE {INTERVAL itl; int pry, size; int cube; NODE *l, *r;};

inline bool operator ==(INTERVAL a, INTERVAL b)
        {return a.l == b.l && a.r == b.r;}
        
typedef NODE * TNODE;

NODE *head, *null;
int node_dat[1000100];
int tot_tower;  
char str_ans[500];

inline void update(TNODE &root){root->size= root->l->size + root->r->size + 1;}

inline void rotate_left(TNODE &root)
{
    TNODE tmp= root->l;
    root->l= tmp->r;
    tmp->r= root;
    update(root); update(tmp);
    root= tmp;
}

inline void rotate_right(TNODE &root)
{
    TNODE tmp= root->r;
    root->r= tmp->l ;
    tmp->l= root;
    update(root); update(tmp);
    root= tmp;
}

void node_insert(TNODE &root, INTERVAL &itl, int &cube)
{
    if(root == null)
    {
        root= new(NODE);
        root->itl= itl ;
        root->size= 1;
        root->cube= cube;
        root->pry= rand();
        root->l= root->r= null;
        return ;
    }
    if(itl.l < root->itl.l)
    {
        node_insert(root->l, itl, cube);
        if(root->l->pry < root->pry)
            rotate_left(root);
    }else
    {
        node_insert(root->r, itl, cube);
        if(root->r->pry < root->pry)
            rotate_right(root);
    }
    update(root);
}

void node_delete(TNODE &root, INTERVAL &itl)
{
    if(root->itl == itl)
    {
        if(root->l == null && root->r == null)
        {
            free(root);
            root= null;
            return ;
        }
        if(root->l->pry < root->r->pry)
        {
            rotate_left(root);
            node_delete(root->r, itl);
        }else
        {
            rotate_right(root);
            node_delete(root->l, itl);
        }
        update(root);
        return ;
    }
    if(itl.l < root->itl.l)
        node_delete(root->l, itl);
    else
        node_delete(root->r, itl);
    update(root);
}

void prog_init()
{
    srand(time(0));
    null= new(NODE);
    null->size= 0 ;
    null->pry= INF;
    head= null;
}

/*Operator Type Description*/
/*
    put        0
    tput    1
    towers    2
    cubes    3
    length    4
    tcubes    5
*/

TNODE find(TNODE &root, int val)
{
    if(root == null) return null;
    if(val < root->itl.l) return find(root->l, val);
    if(val > root->itl.r) return find(root->r, val);
    return root;
}

TNODE find_kth(TNODE &root, int k)
{
    int cache= root->l->size;
    if(cache >= k)return find_kth(root->l, k);
    if(cache + 1 >= k)return root;
    return find_kth(root->r, k - 1 - cache);
}

inline void hdl_put(int &pos, int cnt)
{
    if(node_dat[pos])
    {
        node_dat[pos]+= cnt;
        
        TNODE tmp= find(head, pos);
        tmp->cube+= cnt;
        return ;
    }
    node_dat[pos]+= cnt;
    if(node_dat[pos + 1] && node_dat[pos - 1])
    {
        TNODE tmp1= find(head, pos - 1), tmp2= find(head, pos + 1);
        INTERVAL tmp_itl= tmp2->itl;
        
        tmp1->cube+= cnt + tmp2->cube;
        tmp1->itl.r= tmp2->itl.r;
        node_delete(head, tmp_itl);
        -- tot_tower;
        return;
    }
    if(!node_dat[pos + 1] && !node_dat[pos - 1])
    {
        INTERVAL tmp_itl;
        tmp_itl.l= tmp_itl.r= pos;
        node_insert(head, tmp_itl, cnt);
        ++ tot_tower;
        return ;
    }                   
    if(node_dat[pos + 1])
    {
        TNODE tmp= find(head, pos + 1);
        tmp->itl.l --;
        tmp->cube+= cnt;
        return ;
    }
    if(node_dat[pos - 1])
    {
        TNODE tmp= find(head, pos - 1);
        tmp->itl.r ++;
        tmp->cube+= cnt;
        return ;
    }
}

inline void hdl_tput(int &pos_twr, int &pos_clm, int cnt)
{
    TNODE tmp= find_kth(head, pos_twr);
    tmp->cube += cnt;
    node_dat[tmp->itl.l + pos_clm - 1]+= cnt;
}

inline void hdl_towers()
{
    sprintf(str_ans, "%d towers", tot_tower);
    puts(str_ans);
}

inline void hdl_cubes(int &pos)
{
    TNODE tmp= find_kth(head, pos);
    sprintf(str_ans, "%d cubes in %dth tower", tmp->cube, pos);
    puts(str_ans);
}

inline void hdl_length(int &pos)
{
    TNODE tmp= find_kth(head, pos);
    sprintf(str_ans, "length of %dth tower is %d", pos, tmp->itl.r - tmp->itl.l + 1);
    puts(str_ans);
}

inline void hdl_tcubes(int &pos_twr, int &pos_clm)
{
    TNODE tmp= find_kth(head, pos_twr);
    sprintf(str_ans, "%d cubes in %dth column of %dth tower", node_dat[tmp->itl.l + pos_clm - 1], pos_clm, pos_twr);
    puts(str_ans);
}

inline void data_init()
{
    int opt_tot;
    
    scanf("%d\n", &opt_tot);
    while(opt_tot --)
    {
        char opt_str[500], str[10];
        int opt_num[3]= {0}; int type, num_tot;
    
        gets(opt_str);
        sscanf(opt_str, "%s", str);
        switch(str[0])
        {
            case'p':
                type= 0;
                num_tot= 2;
                break;
            case't':
                if(str[1] == 'p')
                    type= 1, num_tot= 3; else
                if(str[1] == 'o')
                    type= 2, num_tot= 0; else
                if(str[1] == 'c')
                    type= 5, num_tot= 2;
                break;
            case'c':
                type= 3; num_tot= 1;
                break;
            case'l':
                type= 4; num_tot= 1;
                break;
        }
        
        switch(num_tot)
        {
            case 1:
                sscanf(opt_str, "%s%d", str, &opt_num[0]);
                break;
            case 2:
                sscanf(opt_str, "%s%d%d", str, &opt_num[0], &opt_num[1]);
                break;
            case 3:
                sscanf(opt_str, "%s%d%d%d", str, &opt_num[0], &opt_num[1], &opt_num[2]);
                break;
        }
        switch(type)
        {
            case 0:
                hdl_put(opt_num[0], opt_num[1]);
                break;
            case 1:
                hdl_tput(opt_num[0], opt_num[1], opt_num[2]);
                break;
            case 2:
                hdl_towers();
                break;
            case 3:
                hdl_cubes(opt_num[0]);
                break;
            case 4:
                hdl_length(opt_num[0]);
                break;
            case 5:
                hdl_tcubes(opt_num[0], opt_num[1]);
                break;
        }
        
    }

}
 
int main()
{
	freopen("t.in", "r", stdin);
    prog_init();
    data_init();
    return 0 ;
}
