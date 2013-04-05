/**************************************************************
    Problem: 2120
    User: zxytim
    Language: C++
    Result: Accepted
    Time:616 ms
    Memory:9496 kb
****************************************************************/
 
/*
 * $File: color.cpp
 * $Date: Wed Mar 02 19:16:49 2011 +0800
 * $Author: Zhou Xinyu <zxytim@gmail.com>
 */
 
#define INPUT   "t.in"
#define OUTPUT  "t.out"
 
#include <cstdio>
#include <cstring>
#include <algorithm>
 
 
#ifdef DEBUG
#pragma message("Compiled in debug mode.")
#include <set>
using std::multiset;
#include <cassert>
#else
#define assert(cond) 
#endif
 
 
using std::sort;
 
namespace Solve
{
    const int N_INSTRUCTION_MAX = 10000,
          N_NUMBER_MAX = 10000,
          N_NUMBER_LOG_MAX = 14;
 
    const int N_COLOR_TREE_MAX = N_NUMBER_MAX + N_INSTRUCTION_MAX;
 
    typedef int Key_t;
    class Splay
    {
        private:
            class Node
            {
                public:
                    Node *ch[2], *par;
                    Key_t key;
                    int size;
            };
 
            static Node *NIL, NIL_INSTANCE;
 
            class Mem
            {
                private:
                    static const int N_MEM_MAX = N_COLOR_TREE_MAX + 
                        N_INSTRUCTION_MAX * 10 * N_NUMBER_LOG_MAX + 
                        N_NUMBER_LOG_MAX * N_NUMBER_MAX;
                    Mem(){};
                    ~Mem(){};
                    static Node mem[N_MEM_MAX];
                    static Node *freed[N_MEM_MAX];
                    static int nmem, nfreed;
                public:
                    static Node *alloc(Key_t key)
                    {
                        Node *ret;
                        if (nfreed)
                            ret = freed[-- nfreed];
                        else
                        {
                            assert(nmem < N_MEM_MAX);
                            ret = mem + (nmem ++);
                        }
                        ret->ch[0] = ret->ch[1] = ret->par = NIL;
                        ret->key = key;
                        ret->size = 1;
                        return ret;
                    }
 
                    static void free(Node *node)
                    {
                        freed[nfreed ++] = node;
                    }
 
                    static bool find_free(Node *node)
                    {
                        for (int i = 0; i < nfreed; i ++)
                            if (freed[i] == node)
                                return true;
                        return false;
                    }
            };
 
            Node *root;
#ifdef DEBUG
            multiset<Key_t> tree;
#endif
            void splay(Node *cur, Node *par0 = NIL);
 
            void rotate(Node *&node, bool dir)
            {
                Node *son = node->ch[!dir];
                assert(son != NIL);
                assert(son->par == node);
                (node->ch[!dir] = son->ch[dir])->par = node;
                son->par = node->par;
                (son->ch[dir] = node)->par = son;
                son->size = node->size;
                node->size = node->ch[0]->size + node->ch[1]->size + 1;
                node = son;
                check();
            }
 
            Node *&get_ref(Node *&node)
            {
#ifdef DEBUG
                if (node->par == NIL)
                    assert(node == root);
#endif
                return node->par == NIL ? root : node->par->ch[node == node->par->ch[1]];
            }
 
            Node *find_precursor(Node *&node);
            Node *find_successor(Node *&node);
            Node *find_node_by_key(Key_t key);
            static Node *do_build_tree(Key_t *seq, int left, int right);
 
            void do_check(Node *root)
            {
                if (root == NIL)
                    return;
                int size = 1;
                if (root->ch[0] != NIL)
                {
                    assert(root->ch[0]->key <= root->key);
                    assert(root->ch[0]->par == root);
                    do_check(root->ch[0]);
                    size += root->ch[0]->size;
                }
                if (root->ch[1] != NIL)
                {
                    assert(root->ch[1]->key >= root->key);
                    assert(root->ch[1]->par == root);
                    do_check(root->ch[1]);
                    size += root->ch[1]->size;
                }
                assert(size == root->size);
            }
            void check()
            {
#ifndef DEBUG
                return;
#endif
                assert(!Mem::find_free(root));
                if (root != NIL)
                {
                    assert(root->par == NIL);
                    do_check(root);
                }
            }
 
 
        public:
            static void global_init();
            void remove(Key_t key);
            void init();
            void insert(Key_t key);
            int get_nlet(Key_t key);
            void get_lt_gt_key(Key_t key, Key_t &lt, Key_t &gt);
            void update(Key_t orig, Key_t new_key);
            void build_tree(Key_t *seq, int n);
 
#ifdef DEBUG
            int size() { return root->size; }
            bool can_find(Key_t key)
            { 
                bool res0 = find_node_by_key(key) != NIL; 
                bool res1 = tree.find(key) != tree.end();
                assert(res0 == res1);
                assert(res0 == true);
            }
#endif
    };
 
    typedef Splay Tree;
 
    class Sgt
    {
        private:
            class Node
            {
                public:
                    Tree tree;
                    int left, right;
                    Node *chl, *chr;
            };
            class Mem
            {
                private:
                    Mem(){}
                    ~Mem(){}
                    static const int N_MEM_MAX = N_NUMBER_MAX * 2;
                    static int nmem;
                    static Node mem[N_MEM_MAX];
                public:
                    static Node *alloc()
                    {
                        assert(nmem < N_MEM_MAX);
                        Node *ret = mem + (nmem ++);
                        ret->chl = ret->chr = NULL;
                        return ret;
                    }
            };
            Node *root;
            Node *do_build_tree(Key_t *seq, int left, int right);
            int do_query(Node *root, int left, int right);
            void do_update(Node *root, int pos, int val);
        public:
            void build_tree(Key_t *seq, int n);
            int query(int left, int right);
            void replace(int pos, int col);
 
#ifdef DEBUG
            bool do_can_find(Node *root, int pos, Key_t key)
            {
                assert(root->tree.can_find(key));
                if (root->left == root->right)
                    return true;
                int mid = (root->left + root->right) >> 1;
                if (pos <= mid)
                    return do_can_find(root->chl, pos, key);
                else return do_can_find(root->chr, pos, key);
            }
 
            bool can_find(int pos ,Key_t key)
            {
                return do_can_find(root, pos, key);
            }
#endif
    };
 
    Sgt sgt;
 
    class Instruction
    {
        public:
            char type;
            int op0, op1;
    };
    Instruction instruction[N_INSTRUCTION_MAX];
 
    Key_t color[N_NUMBER_MAX];
 
    class Dscrt_t
    {
        public:
            int id, // id < n means numbers in original sequence, 
                // otherwise instructions
                val;
            bool operator < (const Dscrt_t &dscrt) const
            {
                return val < dscrt.val;
            }
    };
 
    int n, m;
 
    Tree color_tree[N_COLOR_TREE_MAX];
    int n_dist_color; // number of distinct number
 
    void discretize();
    void init_tree();
    void transform_seq();
    int seq_trans[N_NUMBER_MAX];
 
    void gen_seq_transed(Key_t *seq);
#ifdef DEBUG
    void check_seq()
    {
        static Key_t seq_new[N_NUMBER_MAX];
        gen_seq_transed(seq_new);
        for (int i = 0; i < n; i ++)
            assert(seq_trans[i] == seq_new[i]);
        for (int i = 0; i < n; i ++)
            assert(sgt.can_find(i, seq_trans[i]));
    }
 
    void check_color()
    {
        return;
        static int cnt_color[N_NUMBER_MAX];
        for (int i = 0; i < n_dist_color; i ++)
            cnt_color[i] = 0;
        for (int i = 0; i < n; i ++)
            cnt_color[color[i]] ++;
        for (int i = 0; i < n_dist_color; i ++)
            assert(cnt_color[i] == color_tree[i].size() - 2);
    }
 
    bool in_seq(Key_t key)
    {
        for (int i = 0; i < n; i ++)
            if (key == seq_trans[i])
                return true;
        return false;
    }
 
    bool is_ordered(int *a, int n)
    {
        for (int i = 1; i < n; i ++)
            assert(a[i] >= a[i - 1]);
        return true;
    }
 
#endif
    void deal_instructions(FILE *fout);
    void solve(FILE *fin, FILE *fout);
}
 
void Solve::solve(FILE *fin, FILE *fout)
{
 
    const int BUFFER_LEN = 1024 * 1024 * 5;
    static char buffer[BUFFER_LEN];
    char *ptr = buffer, *buf_end = ptr + 1;
#define PTR_NEXT() \
    { \
        ptr ++; \
        if (ptr == buf_end) \
        { \
            ptr = buffer; \
            buf_end = buffer + fread(buffer, 1, BUFFER_LEN, fin); \
        } \
    }
#define READ_INT(_x_) \
    { \
        while ((*ptr < '0' || *ptr > '9') && *ptr != '-') \
        PTR_NEXT(); \
        bool _nega_ = false; \
        if (*ptr == '-') \
        { \
            _nega_ = true; \
            PTR_NEXT(); \
        } \
        int register _n_ = 0; \
        while (*ptr >= '0' && *ptr <= '9') \
        { \
            _n_ = _n_ * 10 + *ptr - '0'; \
            PTR_NEXT(); \
        } \
        if (_nega_) \
        _n_ = - _n_; \
        (_x_) = (_n_); \
    }
#define READ_STR(_s_) \
    { \
        while ((*ptr < 'A' || *ptr > 'Z') && (*ptr < 'a' || *ptr > 'z')) \
        PTR_NEXT(); \
        char *_p_ = (_s_); \
        while ((*ptr >= 'A' && *ptr <= 'Z') || (*ptr >= 'a' && *ptr <= 'z')) \
        { \
            *(_p_ ++) = *ptr; \
            PTR_NEXT(); \
        } \
        *_p_ = 0; \
    }
    PTR_NEXT();
 
    READ_INT(n);
    READ_INT(m);
 
    for (int i = 0; i < n; i ++)
        READ_INT(color[i]);
 
    for (int i = 0; i < m; i ++)
    {
        Instruction &ins = instruction[i];
        static char cmd[2];
        READ_STR(cmd);
        ins.type = cmd[0];
        READ_INT(ins.op0);
        ins.op0 --;
        READ_INT(ins.op1);
        if (ins.type == 'Q')
            ins.op1 --;
    }
 
    discretize();
 
    init_tree();
 
    deal_instructions(fout);
#undef PTR_NEXT
#undef READ_INT
#undef READ_STR
}
 
void Solve::discretize()
{
    const int N_DSCRT_MAX = N_COLOR_TREE_MAX;
    static Dscrt_t disc[N_DSCRT_MAX];
    for (int i = 0; i < n; i ++)
    {
        disc[i].id = i;
        disc[i].val = color[i];
    }
 
    int ndisc = n;
    for (int i = 0; i < m; i ++)
        if (instruction[i].type == 'R')
        {
            disc[ndisc].id = i + n;
            disc[ndisc].val = instruction[i].op1;
            ndisc ++;
        }
 
    sort(disc, disc + ndisc);
 
    int prev = -1, id = -1;
    for (int i = 0; i < ndisc; i ++)
    {
        if (disc[i].val != prev)
            id ++;
        if (disc[i].id < n)
            color[disc[i].id] = id;
        else instruction[disc[i].id - n].op1 = id;
        prev = disc[i].val;
    }
    n_dist_color = id + 1;
}
 
void Solve::gen_seq_transed(Key_t *seq)
{
    static int pre_pos[N_COLOR_TREE_MAX];
    for (int i = 0; i < n_dist_color; i ++)
        pre_pos[i] = -1;
    for (int i = 0; i < n; i ++)
    {
        int c = color[i];
        seq[i] = pre_pos[c];
        pre_pos[c] = i;
    }
}
 
void Solve::init_tree()
{
    Tree::global_init();
    for (int i = 0; i < n_dist_color; i ++)
    {
        color_tree[i].init();
        color_tree[i].insert(-1);
        color_tree[i].insert(n);
    }
 
    static Key_t seq[N_NUMBER_MAX];
    gen_seq_transed(seq);
    for (int i = 0; i < n; i ++)
        color_tree[color[i]].insert(i);
    memcpy(seq_trans, seq, sizeof(Key_t) * n);
    sgt.build_tree(seq, n);
 
#ifdef DEBUG
    check_color();
    check_seq();
#endif
}
 
void Solve::deal_instructions(FILE *fout)
{
    for (int i = 0; i < m; i ++)
    {
#ifdef DEBUG
        if (i % 10 == 0)
            fprintf(stderr, "%d\n", i);
        check_seq();
#endif
        if (instruction[i].type == 'Q')
            fprintf(fout, "%d\n",
                    sgt.query(instruction[i].op0, instruction[i].op1));
        else
            sgt.replace(instruction[i].op0, instruction[i].op1);
    }
}
 
int Solve::Splay::get_nlet(Key_t key)
{
    int ret = 0;
    Node *cur = root, *par = NIL;
    while (cur != NIL)
    {
        par = cur;
        if (key >= cur->key)
        {
            ret += cur->ch[0]->size + 1;
            cur = cur->ch[1];
        }
        else cur = cur->ch[0];
    }
    splay(par);
 
    check();
    return ret;
}
 
Solve::Splay::Node *Solve::Splay::find_node_by_key(Key_t key)
{
    if (root == NIL)
        return NIL;
    Node *cur = root;
    while (cur->key != key && cur != NIL)
        cur = cur->ch[key > cur->key];
 
#ifdef DEGUB
    if (cur == NIL)
        assert(tree.find(key) == tree.end());
    else assert(*tree.find(key) == cur->key);
#endif
 
    return cur;
}
 
void Solve::Splay::remove(Key_t key)
{
    static int cnt = 0;
    cnt ++;
    if (cnt == 2)
        int adsf = 0;
    check();
    if (root->size == 1)
    {
#ifdef DEGUB
        assert(tree.size() == 1);
#endif
 
        assert(root->key == key);
        assert(root->ch[0] == root->ch[1] && root->ch[0] == NIL);
        Mem::free(root);
        root = NIL;
    }
    else
    {
        Node *node = find_node_by_key(key);
#ifdef DEBUG
        assert(tree.find(key) != tree.end());
#endif
        assert(node != NIL);
        Node *precursor = find_precursor(node),
             *successor = find_successor(node);
        splay(node);
        if (precursor != NIL)
            splay(precursor, node);
        if (successor != NIL)
            splay(successor, node);
        if (precursor == NIL)
        {
            Mem::free(node);
            (root = successor)->par = NIL;
        }
        else if (successor == NIL)
        {
            Mem::free(node);
            (root = precursor)->par = NIL;
        }
        else
        {
            splay(precursor);
            splay(successor, precursor);
            assert(precursor == root);
            assert(successor == precursor->ch[1]);
            check();
            assert(successor->ch[0] == node);
            Mem::free(successor->ch[0]);
            successor->ch[0] = NIL;
            successor->size --;
            precursor->size --;
            check();
        }
    }
    check();
#ifdef DEBUG
    tree.erase(tree.find(key));
    assert(tree.size() == root->size);
#endif
}
 
void Solve::Splay::update(Key_t orig, Key_t new_key)
{
#ifdef DEBUG
    assert(in_seq(orig));
    check_seq();
    assert(tree.size() == root->size);
    assert(tree.find(orig) != tree.end());
    assert(find_node_by_key(orig) != NIL);
#endif
    remove(orig);
    insert(new_key);
}
 
Solve::Splay::Node *Solve::Splay::do_build_tree(Key_t *seq, int left, int right)
{
    if (right < left)
        return NIL;
    int mid = (left + right) >> 1;
    Node *node = Mem::alloc(seq[mid]);
    (node->ch[0] = do_build_tree(seq, left, mid - 1))->par = node;
    (node->ch[1] = do_build_tree(seq, mid + 1, right))->par = node;
    node->size += node->ch[0]->size + node->ch[1]->size;
    return node;
}
 
void Solve::Splay::build_tree(Key_t *seq, int n)
{
    root = do_build_tree(seq, 0, n - 1);
#ifdef DEBUG
    for (int i = 0; i < n; i ++)
        tree.insert(seq[i]);
#endif
    check();
}
 
void Solve::Splay::get_lt_gt_key(Key_t key, Key_t &lt, Key_t &gt)
{
    Node *node = find_node_by_key(key);
#ifdef DEBUG
    if (node == NIL)
    {
        if (tree.find(key) == tree.end())
            throw "WTF?";
        assert(node != NIL);
    }
#endif
    lt = find_precursor(node)->key;
    gt = find_successor(node)->key;
#ifdef DEBUG
    multiset<Key_t>::iterator it = tree.find(key);
    assert(it != tree.end());
    assert(*(-- it) == lt);
    it ++, it ++;
    assert(*(it) == gt);
#endif
 
}
 
void Solve::Splay::global_init()
{
    NIL = &NIL_INSTANCE;
    NIL->ch[0] = NIL->ch[1] = NIL->par = NIL;
    NIL->size = 0;
}
 
Solve::Splay::Node *Solve::Splay::find_precursor(Node *&node)
{
    assert(node != NIL);
    splay(node);
    Node *prec = root->ch[0];
    while (prec->ch[1] != NIL)
        prec = prec->ch[1];
    if (prec != NIL)
        splay(prec);
    return prec;
}
 
Solve::Splay::Node *Solve::Splay::find_successor(Node *&node)
{
    assert(node != NIL);
    splay(node);
    Node *succ = root->ch[1];
    while (succ->ch[0] != NIL)
        succ = succ->ch[0];
    if (succ != NIL)
        splay(succ);
    return succ;
}
 
 
void Solve::Splay::init()
{
    root = NIL;
}
 
void Solve::Splay::insert(Key_t key)
{
    check();
    if (root == NIL)
        root = Mem::alloc(key);
    else
    {
        check();
        static int cnt = 0;
        cnt ++;
 
        Node *cur = root, *par = NIL;
        while (cur != NIL)
        {
            par = cur;
            cur->size ++;
            cur = cur->ch[key > cur->key];
        }
        cur = Mem::alloc(key);
        par->ch[key > par->key] = cur;
        cur->par = par;
        check();
        splay(cur);
        check();
    }
#ifdef DEBUG
    tree.insert(key);
#endif
    check();
    assert(tree.size() == root->size);
}
 
void Solve::Splay::splay(Node *cur, Node *par0)
{
    check();
    assert(cur != NIL);
    Node *par, *grandpar;
    while ((par = cur->par) != par0)
    {
        if ((grandpar = par->par) == par0)
            rotate(get_ref(par), cur == par->ch[0]);
        else
        {
            bool dcur = (cur == par->ch[1]),
                 dpar = (par == grandpar->ch[1]);
            assert(cur == par->ch[dcur]);
            assert(par == grandpar->ch[dpar]);
            assert(cur != NIL);
            assert(par != NIL);
            assert(grandpar != NIL);
 
            if (dcur != dpar)
            {
                rotate(get_ref(par), !dcur);
                rotate(get_ref(grandpar), !dpar);
            }
            else
            {
                rotate(get_ref(grandpar), !dpar);
                rotate(get_ref(par), !dcur);
            }
        }
    }
    check();
}
 
void Solve::Sgt::build_tree(Key_t *seq, int n)
{
    root = do_build_tree(seq, 0, n - 1);
}
 
Solve::Sgt::Node *Solve::Sgt::do_build_tree(Key_t *seq, int left, int right)
{
    Node *root = Mem::alloc();
    root->left = left, root->right = right;
    static Key_t tmp[N_NUMBER_MAX];
    int mid = (left + right) >> 1;
    if (left != right)
    {
        root->chl = do_build_tree(seq, left, mid);
        root->chr = do_build_tree(seq, mid + 1, right);
    }
    int p0 = left, p1 = mid + 1, cnt = 0;
    while (p0 <= mid && p1 <= right)
        if (seq[p0] < seq[p1])
            tmp[cnt ++] = seq[p0 ++];
        else tmp[cnt ++] = seq[p1 ++];
    while (p0 <= mid)
        tmp[cnt ++] = seq[p0 ++];
    while (p1 <= right)
        tmp[cnt ++] = seq[p1 ++];
 
    assert(cnt == right - left + 1);
    assert(is_ordered(tmp, cnt));
    memcpy(seq + left, tmp, sizeof(Key_t) * cnt);
    root->tree.build_tree(tmp, cnt);
    for (int i = left; i <= right; i ++)
        assert(root->tree.can_find(seq[i]));
    return root;
}
 
int Solve::Sgt::do_query(Node *root, int left, int right)
{
#ifdef DEBUG
    check_color();
#endif
    if (root->left >= left && root->right <= right)
        return root->tree.get_nlet(left - 1);
    int ret = 0, mid = (root->left + root->right) >> 1;
    if (left <= mid)
        ret += do_query(root->chl, left, right);
    if (mid < right)
        ret += do_query(root->chr, left, right);
#ifdef DEBUG
    check_color();
#endif
    return ret;
}
 
int Solve::Sgt::query(int left, int right)
{
#ifdef DEBUG
    check_color();
    check_seq();
    check_color();
    int ret = do_query(root, left, right);
    check_color();
    check_seq();
    return ret;
#else
    return do_query(root, left, right);
#endif
}
 
void Solve::Sgt::do_update(Node *root, int pos, int val)
{
    static int cnt = 0;
    cnt ++;
    root->tree.update(seq_trans[pos], val);
    if (root->left == root->right)
        return;
    int mid = (root->left + root->right) >> 1;
    if (pos <= mid)
        do_update(root->chl, pos, val);
    else do_update(root->chr, pos, val);
}
 
void Solve::Sgt::replace(int pos, int col)
{
#ifdef DEBUG
    check_seq();
    check_color();
#endif
    assert(col >= 0 && col < n_dist_color);
    int left, right;
    int c = color[pos];
    color_tree[c].get_lt_gt_key(pos, left, right);
    if (right != n)
    {
        do_update(root, right, left);
        seq_trans[right] = left;
    }
    color_tree[c].remove(pos);
 
    c = color[pos] = col;
    color_tree[c].insert(pos);
    color_tree[c].get_lt_gt_key(pos, left, right);
    if (right != n)
    {
        do_update(root, right, pos);
        seq_trans[right] = pos;
    }
    do_update(root, pos, left);
    seq_trans[pos] = left;
 
#ifdef DEBUG
    check_seq();
    check_color();
#endif
}
 
/* static variables */
Solve::Splay::Node *Solve::Splay::NIL, Solve::Splay::NIL_INSTANCE;
 
Solve::Splay::Node Solve::Splay::Mem::mem[N_MEM_MAX], 
    *Solve::Splay::Mem::freed[N_MEM_MAX];
int Solve::Splay::Mem::nmem, Solve::Splay::Mem::nfreed;
 
int Solve::Sgt::Mem::nmem;
Solve::Sgt::Node Solve::Sgt::Mem::mem[N_MEM_MAX];
 
 
int main()
{
#ifdef STDIO
    Solve::solve(stdin, stdout);
#else
    FILE *fin = fopen(INPUT, "r"),
         *fout = fopen(OUTPUT, "w");
    Solve::solve(fin, stdout);
    fclose(fin);
    fclose(fout);
#endif
}
