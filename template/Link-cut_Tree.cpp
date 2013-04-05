#include <cctype>
#include <cstdio>
#include <cstdlib>
#include <cstring>
#include <algorithm>
using namespace std;
 
const int MAX_N = 200000;
int n, m;
 
#undef NULL
#define NULL node_t::nil
 
struct node_t{
    int sz;
    node_t *par, *son[2];
 
    node_t(){
        par = son[0] = son[1] = NULL;
    }
 
    static node_t nil_ins, *nil;
};
 
node_t node[MAX_N];
 
node_t node_t::nil_ins;
node_t *node_t::nil = &nil_ins;
 
void update(node_t *pos){
    pos -> sz = 1 + pos -> son[0] -> sz + pos -> son[1] -> sz;
}
 
void rot(node_t *pos, bool t){
    node_t *tptr = pos -> son[t], *tmp;
    pos -> son[t] = tptr -> son[!t];
    if ((tmp = tptr -> son[!t]) != NULL)
        tmp -> par = pos;
    tptr -> son[!t] = pos;
    if (((tmp = pos -> par) != NULL) && (tmp -> son[tmp -> son[1] == pos] == pos))
        tmp -> son[tmp -> son[1] == pos] = tptr;
    pos -> par = tptr;
    tptr -> par = tmp;
}
 
void splay(node_t *pos){
    node_t *ngra, *npar;
    bool d1, d2;
    while ((pos != NULL) && ((npar = pos -> par) != NULL) && (pos == npar -> son[0] || pos == npar -> son[1]))
    {
        ngra = npar -> par;
        if (ngra == NULL || npar != ngra -> son[ngra -> son[1] == npar])
            rot(npar, npar -> son[1] == pos), update(npar);
        else
        {
            if ((d1 = (ngra -> son[1] == npar)) == (d2 = (npar -> son[1] == pos)))
                rot(ngra, d1), rot(npar, d2);
            else
                rot(npar, d2), rot(ngra, d1);
            update(ngra), update(npar);
        }
    }
    update(pos);
}
 
node_t *access(node_t *pos){
    node_t *tptr = NULL;
    for ( ; pos != NULL; pos = pos -> par)
    {
        splay(pos);
        pos -> son[1] = tptr;
        update(tptr = pos);
    }
    return tptr;
}
 
void cut(int x){
    node_t *pos = node + x;
    access(pos);
    splay(pos);
    pos -> son[0] -> par = NULL;
    pos -> son[0] = NULL;
    update(pos);
}
 
void join(int x, int y){
    node_t *xp = node + x, *yp = node + y;
    access(xp);
    splay(xp);
    xp -> par = yp;
    access(xp);
}
 
int ask(int x){
    node_t *pos = node + x;
    access(pos);
    splay(pos);
    return pos -> son[0] -> sz + 1;
}
 
int main(){
}
