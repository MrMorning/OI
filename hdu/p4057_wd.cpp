#include <cstdio>
#include <cstdlib>
#include <cstring>
#include <queue>
#include <algorithm>
using namespace std;

const int MAX_N = 10, MAX_ST = 1 << MAX_N, MAX_L = 100, BUF_SIZE = 1024;
int n, l, w[MAX_N], totw[MAX_ST];
char buf[BUF_SIZE];

const int MAX_NODE_CNT = 1000, SON = 4;
struct node_t {
    int mask;
    node_t *son[SON], *fail;
} node[MAX_NODE_CNT + 1], *root, *ptr;

int idx[BUF_SIZE], upper, f[MAX_L + 1][MAX_NODE_CNT + 1];

node_t *node_alloc() {
    node_t *ret = ptr ++;
    ret -> mask = 0;
    ret -> fail = 0;
    memset(ret -> son, 0, sizeof(ret -> son));
    return ret;
}

node_t *ins(char *str) {
    node_t *pos = root;
    while (*str) {
        if (!pos -> son[idx[*str]]) pos -> son[idx[*str]] = node_alloc();
        pos = pos -> son[idx[*str]];
        str ++;
    }
    return pos;
}

void build() {
    static queue <node_t *> q;
    
    for (int i = 0; i < SON; i ++)
        if (root -> son[i]) {
            root -> son[i] -> fail = root;
            q.push(root -> son[i]);
        }
        else root -> son[i] = root;

    while (q.size()) {
        node_t *u = q.front();
        q.pop();
        
        for (int i = 0; i < SON; i ++)
            if (u -> son[i]) {
                u -> son[i] -> fail = u -> fail -> son[i];
                u -> son[i] -> mask |= u -> fail -> son[i] -> mask;
                q.push(u -> son[i]);
            }
            else u -> son[i] = u -> fail -> son[i];
    }
}

int main() {
	freopen("t.in", "r", stdin);
    idx['A'] = 0, idx['G'] = 1, idx['C'] = 2, idx['T'] = 3;

    while (scanf("%d%d", &n, &l) != EOF) {
        ptr = node;
        root = node_alloc();
        memset(totw, 0, sizeof(totw));
        
        upper = 1 << n;
        for (int i = 0; i < n; i ++) {
            scanf("%s%d", buf, &w[i]);
            if (strlen(buf) > l) continue;
            (ins(buf)) -> mask = 1 << i;
            for (int j = 0; j < upper; j ++)
                if ((1 << i) & j) totw[j] = totw[j ^ (1 << i)] + w[i];
        }
        build();
        
        memset(f, -1, sizeof(f));
        int b = ptr - node;
        f[0][0] = 0;
        for (int i = 0; i < l; i ++)
            for (int j = 0; j < b; j ++) if (f[i][j] >= 0) {
                node_t *u = node + j;
                
                for (int s = 0; s < SON; s ++) {
                    node_t *v = u -> son[s];
                    int vp = v - node, st = f[i][j] | v -> mask;

                    if (f[i + 1][vp] < 0) f[i + 1][vp] = st;
                    else if (totw[st] > totw[f[i + 1][vp]]) f[i + 1][vp] = st;
                }
            }

        int ans = -1;
        for (int i = 0; i < b; i ++)
            if (f[l][i] >= 0) ans = max(ans, totw[f[l][i]]);
        if (ans >= 0) printf("%d\n", ans);
        else printf("No Rabbit after 2012!\n");
    }

    return 0;
}

