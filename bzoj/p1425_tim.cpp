#define INPUT   "t.in"
#define OUTPUT  "t.out"
 
#include <cstdio>
#include <algorithm>
#include <cstring>
 
using std::sort;
 
namespace Solve
{
    typedef long long int Bignum_t;
 
    const int N_MAX = 100000,
          N_LOG_2 = 17,
          N_LOG_3 = 11,
          N_NODE_MAX = 101;
 
    const int MOD = 1000000001;
 
    int sum_of_valid_number[N_MAX + 1];
 
    int numbers[N_NODE_MAX + 1];
    int nnumbers;
    int num2id[N_MAX + 1];
 
    bool visited[N_LOG_2][N_LOG_3];
 
    void init();
    int depth[N_MAX + 1];
    int layer[N_NODE_MAX];
    int layer_full_cnt[N_LOG_2];
    int layer_cnt[N_LOG_2];
    void dfs(int num, int n2, int n3, int dep);
    int work(int n);
    void solve(FILE *fin, FILE *fout);
 
    int power_mod(int a, int b);
    int calc_answer(int id);
 
    int mask_pos[1 << N_LOG_3][N_LOG_3];
    int nmask_pos[1 << N_LOG_3];
}
 
void Solve::dfs(int num, int n2, int n3, int dep)
{
    if (num > N_MAX || visited[n2][n3])
        return;
    visited[n2][n3] = true;
    num2id[num] = nnumbers;
    depth[num] = dep;
    layer_full_cnt[dep] ++;
    numbers[nnumbers ++] = num;
    dfs(num * 2, n2 + 1, n3, dep + 1);
    dfs(num * 3, n2, n3 + 1, dep + 1);
}
 
int Solve::power_mod(int a, int b)
{
    if (b == 0)
        return 1;
    if (b == 1)
        return a;
    if (b == 2)
        return static_cast<Bignum_t>(a) * a % MOD;
    int ret = 1;
    while (b)
    {
        if (b & 1)
            ret = static_cast<Bignum_t>(ret) * a % MOD;
        a = static_cast<Bignum_t>(a) * a % MOD;
        b >>= 1;
    }
    return ret;
}
 
void Solve::init()
{
    for (int i = 1; i <= N_MAX; i ++)
        sum_of_valid_number[i] = 
            sum_of_valid_number[i - 1] + (i % 3 && i % 2);
 
    dfs(1, 0, 0, 0);
    sort(numbers, numbers + nnumbers);
    for (int i = 0; i < nnumbers; i ++)
        layer[i] = depth[numbers[i]];
    // init mask
    for (int i = 0, limit = (1 << N_LOG_3); i < limit; i ++)
        for (int j = 0; j < N_LOG_3; j ++)
            if ((i >> j) & 1)
                mask_pos[i][nmask_pos[i] ++] = j;
}
 
int Solve::calc_answer(int id)
{
    static int fval[N_NODE_MAX];
    int &ret = fval[id];
    if (ret)
        return ret;
 
    for (int i = 0; i <= id; i ++)
        layer_cnt[layer[i]] ++;
 
    static bool layer_is_valid[N_LOG_2];
    int nlayer = 1;
    layer_is_valid[0] = true;
    while (layer_cnt[nlayer])
    {
        layer_is_valid[nlayer] = 
            layer_is_valid[nlayer - 1]
            && layer_cnt[nlayer] == layer_full_cnt[nlayer];
        nlayer ++;
    }
 
    static int f[N_LOG_2][1 << N_LOG_3];
 
    static int g[N_LOG_2][1 << N_LOG_3];
    static bool g_done[N_LOG_2];
    g_done[0] = true;
    g[0][0] = g[0][1] = 1;
     
    int start_layer = 1;
    while (start_layer < nlayer 
            && layer_cnt[start_layer] == layer_full_cnt[start_layer]
            && g_done[start_layer])
        start_layer ++;
 
    memcpy(f[start_layer - 1], g[start_layer - 1], 
            sizeof(int) * (1 << layer_full_cnt[start_layer - 1]));
 
    for (int i = start_layer; i < nlayer; i ++)
    {
        int npos = layer_cnt[i], pnpos = layer_cnt[i - 1];
        for (int s = 0, limit = (1 << npos); s < limit; s ++)
        {
            int &val = f[i][s];
            val = 0;
            int prev_mask_available = s | (s >> 1);
            prev_mask_available = ~prev_mask_available;
            prev_mask_available &= (1 << pnpos) - 1;
 
            int nprev_mask_pos = nmask_pos[prev_mask_available];
            int register * prev_mask_pos = mask_pos[prev_mask_available];
 
            /* ------ */
            int register *fprev = f[i - 1];
            if (nprev_mask_pos == 0)
            {
                val = (val + fprev[0]) % MOD;
                continue;
            }
 
            static const int QUEUE_SIZE = N_MAX;
            static int queue_pos[QUEUE_SIZE],
                       queue_state[QUEUE_SIZE];
            queue_pos[0] = nprev_mask_pos - 1;
            queue_state[0] = 0;
            for (int register qh = 0, qt = 1; qh != qt; qh ++)
            {
                int register pos = queue_pos[qh],
                    state = queue_state[qh];
                if (pos == 0)
                {
                    val = (val + fprev[state]) % MOD;
                    val = (val + fprev[state | (1 << prev_mask_pos[0])]) % MOD;
                    continue;
                }
                queue_pos[qt] = pos - 1;
                queue_state[qt] = state;
                qt ++;
 
                queue_pos[qt] = pos - 1;
                queue_state[qt] = state | (1 << prev_mask_pos[pos]);
                qt ++;
            }
        }
        if (layer_is_valid[i] && !g_done[i])
        {
            g_done[i] = true;
            memcpy(g[i], f[i], sizeof(int) * (1 << npos));
        }
    }
 
    for (int i = 0, limit = (1 << layer_cnt[nlayer - 1]); i < limit; i ++)
        ret = (ret + f[nlayer - 1][i]) % MOD;
 
    while (nlayer --)
        layer_cnt[nlayer] = 0;
 
    return ret;
}
 
int Solve::work(int n)
{
    int ret = 1;
    numbers[nnumbers] = n + 1;
    for (int i = 0; i < nnumbers; i ++)
    {
        int num = numbers[i];
        if (num > n)
            break;
        int cnt = sum_of_valid_number[n / num]
            - sum_of_valid_number[n / numbers[i + 1]];
        ret = (static_cast<Bignum_t>(ret) * power_mod(calc_answer(i), cnt)) % MOD;
    }
    return ret;
}
 
void Solve::solve(FILE *fin, FILE *fout)
{
    init();
 
    int ncase;
    fscanf(fin, "%d", &ncase);
    while (ncase --)
    {
        int n;
        fscanf(fin, "%d", &n);
        fprintf(fout, "%d\n", work(n));
    }
}
 
int main()
{
#ifdef STDIO
    Solve::solve(stdin, stdout);
#else
    FILE *fin = fopen(INPUT, "r"),
         *fout = fopen(OUTPUT, "w");
    Solve::solve(fin, fout);
    fclose(fin);
    fclose(fout);
#endif
    return 0;
}

