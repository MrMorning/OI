#include <cstdio>
#include <cstdlib>
#include <cstring>
#include <algorithm>
using namespace std;
const int kMaxN = 100000, kMaxM = kMaxN - 1, kInf = 0x3f3f3f3f;
int n, m, w[kMaxN];
int cnt, begin[kMaxN], end[kMaxM], next[kMaxM];
void AddEdge(int u, int v) {
    next[cnt] = begin[u];
    begin[u] = cnt;
    end[cnt ++] = v;
}
void InitGraph() {
    cnt = 0;
    memset(begin, -1, sizeof(begin));
}
int pre[kMaxN], sz[kMaxN], dep[kMaxN], hvst[kMaxN], jump[kMaxN], q[kMaxN], qh, qt, buf[kMaxN];
namespace heap {
    struct Node {
        int v, p, b, d;
        Node *son[2];
    };
    Node *NodeAlloc(int v, int p, int b) {
        Node *res = new Node;
        res->v = v, res->p = p, res->b = b, res->d = 0, res->son[0] = res->son[1] = NULL;
        return res;
    }
    Node *Merge(Node *u, Node *v) {
        // u->v < v->v
        if (u == NULL || v == NULL) return (u == NULL ? v : u);
        if (u->v > v->v) return Merge(v, u);
        u->son[1] = Merge(u->son[1], v);
        if (u->son[0] == NULL || u->son[0]->d < u->son[1]->d) swap(u->son[0], u->son[1]);
        u->d = (u->son[1] == NULL ? 0 : u->son[1]->d + 1);
        return u;
    }
    void Insert(Node * &des, int v, int p, int b) {
        des = Merge(des, NodeAlloc(v, p, b));
    }
    void Pop(Node * &des) {
        des = Merge(des->son[0], des->son[1]);
    }
    int Top(Node * &des) {
        while (des != NULL && w[des->p] != des->v) Pop(des);
        return (des == NULL ? -1 : des->p);
    }
}
namespace sgt {
    struct Node {
        int l, r, p, pp;
        heap::Node *q;
        Node *son[2];
        void update() {
            if (w[son[0]->p] < w[son[1]->p])
                p = son[0]->p;
            else
                p = son[1]->p;
            if (son[0]->pp == -1 || son[1]->pp == -1) pp = (son[0]->pp == -1 ? son[1]->pp : son[0]->pp);
            else if (w[son[0]->pp] < w[son[1]->pp]) pp = son[0]->pp; else pp = son[1]->pp;
        }
    };
}
sgt::Node *root[kMaxN];
sgt::Node *pos[kMaxN];
namespace sgt {
    Node *NodeAlloc(int l, int r, int p = -1, int pp = -1) {
        Node *res = new Node;
        res->l = l, res->r = r, res->p = p, res->pp = pp, res->q = NULL, res->son[0] = res->son[1] = NULL;
        return res;
    }
    Node *BuildTree(int l, int r, int *buf) {
        Node *res = NodeAlloc(l, r);
        if (l + 1 == r) {
            res->p = buf[dep[buf[0]] - l];
            pos[buf[dep[buf[0]] - l]] = res;
        }
        else {
            int mid = (l + r) >> 1;
            res->son[0] = BuildTree(l, mid, buf);
            res->son[1] = BuildTree(mid, r, buf);
            res->update();
        }
        return res;
    }
    int AskOnRange(int l, int r, Node *pos) {
        if (r <= pos->l || l >= pos->r) return -1;
        int a, b;
        if (l <= pos->l && r >= pos->r) {
            a = pos->p, b = pos->pp;
        }
        else {
            int mid = (pos->l + pos->r) >> 1;
            a = (l < mid ? AskOnRange(l, r, pos->son[0]) : -1);
            b = (r > mid ? AskOnRange(l, r, pos->son[1]) : -1);
        }
        if (a == -1 || b == -1) return (a == -1 ? b : a);
        return (w[a] < w[b] ? a : b);
    }
    void ChangeOnPoint(int x, int v, Node *pos) {
        if (pos->l + 1 == pos->r) {
            w[pos->p] = v;
            return;
        }
        int mid = (pos->l + pos->r) >> 1;
        if (x < mid)
            ChangeOnPoint(x, v, pos->son[0]);
        else
            ChangeOnPoint(x, v, pos->son[1]);
        pos->update();
    }
    void ChangeOnPointC(int x, int v, int p, int b, Node *pos) {
        if (pos->l + 1 == pos->r) {
            heap::Insert(pos->q, v, p, b);
            pos->pp = heap::Top(pos->q);
            return;
        }
        int mid = (pos->l + pos->r) >> 1;
        if (x < mid) ChangeOnPointC(x, v, p, b, pos->son[0]); else ChangeOnPointC(x, v, p, b, pos->son[1]);
        pos->update();
    }
}
void ChainSplit() {
    qh = qt = 0;
    q[qt ++] = 0;
    while (qh < qt) {
        int u = q[qh ++];
        for (int now = begin[u], v; now != -1; now = next[now]) {
            dep[v = end[now]] = dep[u] + 1;
            q[qt ++] = v;
        }
    }
    memset(sz, 0, sizeof(sz));
    memset(hvst, -1, sizeof(hvst));
    for (int i = n - 1; i >= 0; -- i) {
        int u = q[i];
        ++ sz[u];
        if (pre[u] != -1) {
            sz[pre[u]] += sz[u];
            if (hvst[pre[u]] == -1 || sz[hvst[pre[u]]] < sz[u])
                hvst[pre[u]] = u;
        }
    }
    memset(root, 0, sizeof(root));
    for (int i = n - 1; i >= 0; -- i) {
        int u = q[i];
        if (root[u]) continue;
        int t = 0;
        while (true) {
            buf[t ++] = u;
            if (pre[u] == -1 || hvst[pre[u]] != u) break;
            u = pre[u];
        }
        sgt::Node *tmp = sgt::BuildTree(dep[buf[t - 1]], dep[buf[0]] + 1, buf);
        for (int j = 0; j < t; ++ j) {
            root[buf[j]] = tmp;
            jump[buf[j]] = u;
        }
    }
    for (int i = n - 1; i >= 0; -- i) {
        int u = q[i];
        if (pre[u] != -1 && hvst[pre[u]] != u) {
            int a = sgt::AskOnRange(dep[u], n, root[u]);
            if (a != -1) sgt::ChangeOnPointC(dep[pre[u]], w[a], a, u, root[pre[u]]);
        }
    }
}
int Lca(int u, int v) {
    while (root[u] != root[v]) {
        int x = pre[jump[u]], y = pre[jump[v]];
        if (y != -1)
            if (x == -1 || dep[x] < dep[y]) swap(u, v), swap(x, y);
        u = x;
    }
    if (dep[u] > dep[v]) swap(u, v);
    return u;
}
bool IsAnc(int a, int b) {
    return (Lca(a, b) == a);
}
bool IsAncC(int a, int b) {
    while (b != -1) {
        b = pre[jump[b]];
        if (b == a) return true;
    }
    return false;
}
int AncC(int a, int b) {
    while (b != -1) {
        b = jump[b];
        if (root[pre[b]] == root[a]) break;
        b = pre[b];
    }
    return b;
}
int ToRootC(int u, int t) {
    int res = -1;
    while (u != -1) {
        int a = -1, b = -1;
        if (dep[u]) a = sgt::AskOnRange(0, dep[u], root[u]);
        b = sgt::AskOnRange(dep[u] + 1, n, root[u]);
        if (res == -1) res = a;
        else if (a != -1 && w[a] < w[res]) res = a;
        if (res == -1) res = b;
        else if (b != -1 && w[b] < w[res]) res = b;
        if (res == -1) res = u;
        else if (w[u] < w[res]) res = u;
        int pp = -1;
        while (pos[u]->q != NULL && (pos[u]->q->b == t || w[pos[u]->q->p] != pos[u]->q->v)) {
            if (pos[u]->q->b == t && pos[u]->q->v == w[pos[u]->q->p]) pp = pos[u]->q->p;
            Pop(pos[u]->q);
        }
        a = -1;
        if (pos[u]->q != NULL) a = pos[u]->q->p;
        if (res == -1) res = a;
        else if (a != -1 && w[a] < w[res]) res = a;
        if (pp != -1) heap::Insert(pos[u]->q, w[pp], pp, t);
        t = jump[u];
        u = pre[jump[u]];
    }
    return res;
}
int ToRoot(int u) {
    int res = -1;
    int a = sgt::AskOnRange(0, dep[u] + 1, root[u]);
    if (res == -1) res = a;
    else if (a != -1 && w[a] < w[res]) res = a;
    if (pre[jump[u]] != -1) {
        a = ToRootC(pre[jump[u]], jump[u]);
        if (res == -1) res = a;
        else if (a != -1 && w[a] < w[res]) res = a;
    }
    return res;
}
int main() {
    freopen("t.in", "r", stdin);
    scanf("%d%d", &n, &m);
    InitGraph();
    for (int i = 0; i < n; ++ i) {
        scanf("%d%d", &pre[i], &w[i]);
        -- pre[i];
        if (pre[i] >= 0) AddEdge(pre[i], i);
    }
    ChainSplit();
    int r = 0;
    while (m --) {
        static char cmd[2];
        static int x, y;
        scanf("%s%d", cmd, &x);
        -- x;
        if (cmd[0] == 'V') {
            scanf("%d", &y);
            sgt::ChangeOnPoint(dep[x], y, root[x]);
            while (x != -1) {
                x = jump[x];
                if (pre[x] != -1) {
                    int a = sgt::AskOnRange(dep[x], n, root[x]);
                    if (a != -1) sgt::ChangeOnPointC(dep[pre[x]], w[a], a, x, root[pre[x]]);
                }
                x = pre[x];
            }
        }
        else if (cmd[0] == 'E') {
            r = x;
        }
        else {
            int res;
            if (x == r) {
                int a = sgt::AskOnRange(0, n, root[0]);
                res = w[a];
            }
            else {
                if (IsAnc(x, r)) {
                    if (IsAncC(x, r))
                        res = w[ToRootC(x, AncC(x, r))];
                    else
                        res = w[ToRoot(x)];
                }
                else {
                    int a = sgt::AskOnRange(dep[x], n, root[x]);
                    res = w[a];
                }
            }
            printf("%d\n", res);
        }
    }
    return 0;
}
