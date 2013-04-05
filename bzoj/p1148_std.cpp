#define INPUT   "pendant.in"
#define OUTPUT  "pendant.out"
 
#include <cstdio>
 
namespace Solve
{
    typedef long long int Bignum;
#define BIGNUM_FMT "%lld"
    const int NSEG_MAX = 200005;
    struct Segment
    {
        Bignum tail, len;
        inline bool operator < (const Segment &n) const
        {return tail < n.tail || (tail == n.tail && len < n.len);}
    };
    Segment seg[NSEG_MAX];
    int nseg;
    void sort(int left, int right);
 
    namespace Heap
    {
        Bignum heap[NSEG_MAX];
        int size;
        void shift_up(int root);
        void shift_down(int root);
        inline Bignum get_max()
        {return heap[0];}
        void extract_max();
        void insert(Bignum val);
    }
 
    int work(Bignum &min_len);
 
    void solve(FILE *fin, FILE *fout);
}
 
void Solve::solve(FILE *fin, FILE *fout)
{
    fscanf(fin, "%d", &nseg);
    for (int i = 0; i < nseg; i ++)
    {
        Bignum c, w;
        fscanf(fin, BIGNUM_FMT BIGNUM_FMT, &c, &w);
        seg[i].len = w;
        seg[i].tail = c + w;
    }
    Bignum x;
    int n = work(x);
    fprintf(fout, "%d\n" BIGNUM_FMT "\n", n, x);
}
 
int Solve::work(Bignum &min_len)
{
    sort(0, nseg - 1);
    min_len = 0;
    int ans = 0;
    for (int i = 0; i < nseg; i ++)
    {
        if (min_len + seg[i].len <= seg[i].tail)
        {
            ans ++;
            min_len += seg[i].len;
            Heap::insert(seg[i].len);
        } else
        {
            Bignum m = Heap::get_max();
            if (seg[i].len < m)
            {
                min_len += seg[i].len - m;
                Heap::extract_max();
                Heap::insert(seg[i].len);
            }
        }
    }
    return ans;
}
 
void Solve::Heap::shift_up(int root)
{
    Bignum n0 = heap[root];
    while (root)
    {
        int par = (root - 1) >> 1;
        if (heap[par] > n0)
            break;
        heap[root] = heap[par];
        root = par;
    }
    heap[root] = n0;
}
 
void Solve::Heap::shift_down(int root)
{
    Bignum n0 = heap[root];
    while(1)
    {
        int register ch = (root << 1) + 1,
            ch1 = (root + 1) << 1;
        if (ch1 < size && heap[ch1] > heap[ch])
            ch = ch1;
        if (ch >= size || heap[ch] < n0)
        {
            heap[root] = n0;
            return;
        } else
        {
            heap[root] = heap[ch];
            root = ch;
        }
    }
}
 
void Solve::Heap::extract_max()
{
    heap[0] = heap[-- size];
    shift_down(0);
}
 
void Solve::Heap::insert(Bignum val)
{
    heap[size ++] = val;
    shift_up(size - 1);
}
 
void Solve::sort(int left, int right)
{
    if (left >= right)
        return;
    int register i = left, j = right;
    Segment mid = seg[(i + j) >> 1];
    while (i <= j)
    {
        while (seg[i] < mid)
            i ++;
        while (mid < seg[j])
            j --;
        if (i <= j)
        {
            Segment tmp = seg[i];
            seg[i] = seg[j];
            seg[j] = tmp;
            i ++;
            j --;
        }
    }
    sort(left, j);
    sort(i, right);
}
 
int main()
{
	freopen("t.in", "r", stdin);
    Solve::solve(stdin, stdout);
 
}
