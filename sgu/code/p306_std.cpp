#include <cstdio>
#include <cstdlib>
#include <vector>

using namespace std;

int N;
int std_idx;

void init()
{
    freopen("t.in", "r", stdin);
    freopen("t.out", "w", stdout);
    scanf("%d", &N);
}

void print_set(vector<int> &x)
{
    printf("%d", x[0]);
    for(int i(1), size(x.size()); i < size; ++ i)
        printf("+%d", x[i]);
}

void print_tab(int x)
{
    for(int i(0); i < x; ++ i)
        printf("  ");
}

void divide_set(vector<int> &x, vector<int> son[3])
{
    int n = x.size();
    int k = n / 3;
    for(int i(0); i < 3; ++ i)
        for(int j(0); j < k; ++ j)
            son[i].push_back(x[i * k + j]);
    if(n % 3 == 1)
        son[2].push_back(x[n - 1]);
    if(n % 3 == 2)
        son[0].push_back(x[n - 2]),
        son[1].push_back(x[n - 1]);;
}

void solve_1_set(vector<int> , int);

void solve_2_set(vector<int> a, vector<int> b, int depth)
{
    if(a.size() == 1 && b.size() == 1)
    {
        print_tab(depth);
        printf("weigh %d vs %d\n", a[0], std_idx);
        print_tab(depth);
        printf("case >:\n");
        print_tab(depth);
        printf("  fake %d\n", a[0]);
        print_tab(depth);
        printf("case =:\n");
        print_tab(depth);
        printf("  fake %d\n", b[0]);
        print_tab(depth);
        printf("end\n");
        return;
    }
    if(a.size() == 2 && !b.size())
    {
        print_tab(depth);
        printf("weigh %d vs %d\n", a[0], a[1]);
        print_tab(depth);
        printf("case >:\n");
        print_tab(depth);
        printf("  fake %d\n", a[0]);
        print_tab(depth);
        printf("case <:\n");
        print_tab(depth);
        printf("  fake %d\n", a[1]);
        print_tab(depth);
        printf("end\n");
        return;
    }
    if(!a.size() && b.size() == 2)
    {
        print_tab(depth);
        printf("weigh %d vs %d\n", b[0], b[1]);
        print_tab(depth);
        printf("case >:\n");
        print_tab(depth);
        printf("  fake %d\n", b[1]);
        printf("case <:\n");
        print_tab(depth);
        printf("  fake %d\n", b[0]);
        print_tab(depth);
        printf("end\n");
        return;
    }
    if(!b.size())
    {
        solve_1_set(a, depth);
        return ;
    }
    if(!a.size())
    {
        solve_1_set(b, depth);
        return ;
    }
    vector<int> sonA[3], sonB[3];

    divide_set(a, sonA);
    divide_set(b, sonB);
    if(a.size() % 3 == 1 && b.size() % 3 == 1)
    {
        sonB[0].push_back(*(sonB[2].end() - 1));
        sonB[2].pop_back();
        sonB[1].push_back(*(sonB[2].end() - 1));
        sonB[2].pop_back();
    }

    print_tab(depth);
    printf("weigh ");
    if(sonA[0].size() > 0)
    {
        print_set(sonA[0]);
        if(sonB[0].size() > 0)
            printf("+");
    }
    if(sonB[0].size() > 0)
        print_set(sonB[0]);
    printf(" vs ");
    if(sonA[1].size() > 0)
    {
        print_set(sonA[1]);
        if(sonB[1].size() > 0)
            printf("+");
    }
    if(sonB[0].size() > 0)
        print_set(sonB[1]);
    printf("\n");
    print_tab(depth);
    printf("case <:\n");
    solve_2_set(sonA[1], sonB[0], depth + 1);
    print_tab(depth);
    if(sonA[2].size() || sonB[2].size())
    {
        printf("case =:\n");
        solve_2_set(sonA[2], sonB[2], depth + 1);
    }
    print_tab(depth);
    printf("case >:\n");
    solve_2_set(sonA[0], sonB[1], depth + 1);
    print_tab(depth);
    printf("end\n");
}

void solve_1_set(vector<int> x, int depth)
{
    if(x.size() == 1)
    {
        print_tab(depth);
        printf("fake %d\n", x[0]);
        return;
    }
    if(x.size() == 2)
    {
        print_tab(depth);
        printf("weigh %d vs %d\n", std_idx, x[0]);
        print_tab(depth);
        printf("case <:\n");
        print_tab(depth);
        printf("  fake %d\n", x[0]);
        print_tab(depth);
        printf("case =:\n");
        print_tab(depth);
        printf("  fake %d\n", x[1]);
        print_tab(depth);
        printf("case >:\n");
        print_tab(depth);
        printf("  fake %d\n", x[0]);
        print_tab(depth);
        printf("end\n");
        return;
    }
    vector<int> son[3];
    int n = x.size();
    int k = n / 3;
    for(int i(0); i < 3; ++ i)
        for(int j(0); j < k; ++ j)
            son[i].push_back(x[i * k + j]);
    if(n % 3 >= 1)
    {
        son[0].push_back(std_idx);
        son[1].push_back(x[n - 1]);
    }
    if(n % 3 == 2)
        son[2].push_back(x[n - 2]);
    print_tab(depth);
    printf("weigh ");
    print_set(son[0]);
    printf(" vs ");
    print_set(son[1]);
    printf("\n");

    if(n % 3 >= 1)
        son[0].pop_back();

    print_tab(depth);
    printf("case <:\n");
    solve_2_set(son[1], son[0], depth + 1);
    print_tab(depth);
    printf("case =:\n");
    solve_1_set(son[2], depth + 1);
    print_tab(depth);
    printf("case >:\n");
    solve_2_set(son[0], son[1], depth + 1);
    print_tab(depth);
    printf("end\n");
}

void solve()
{
    int ans = 0, temp = 1;
    for(; temp < N * 2; temp *= 3, ++ ans);
    printf("need %d weighings\n", ans);
    vector<int> set[3];
    for(int i(0); i < 3; ++ i)
        for(int j(1); j <= N / 3; ++ j)
            set[i].push_back(j + i * (N / 3));
    if(N % 3 == 1)
        set[2].push_back(N);
    if(N % 3 == 2)
        set[0].push_back(N - 1),
        set[1].push_back(N);

    printf("weigh ");
    print_set(set[0]);
    printf(" vs ");
    print_set(set[1]);
    printf("\n");

    printf("case <:\n");
    std_idx = set[2][0];
    solve_2_set(set[1], set[0], 1);

    printf("case =:\n");
    std_idx = set[0][0];
    solve_1_set(set[2], 1);

    printf("case >:\n");
    std_idx = set[2][0];
    solve_2_set(set[0], set[1], 1);
    printf("end\n");
}

int main()
{
    init();
    solve();
    return 0;
}
