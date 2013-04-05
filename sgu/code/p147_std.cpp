#include <cstdio>
#include <cstdlib>
#include <ctime>
#include <algorithm>

using namespace std ;

const int INF= 0x7fffffff;

struct NODE {int x, y;};

NODE b, w, bw;
int N, Step, Ans= INF;

int main()
{
    freopen("t.in", "r", stdin);
    scanf("%d%d%d%d%d%d%d", &N, &b.x, &b.y, &w.x, &w.y, &bw.x, &bw.y);
    if(abs(w.y - b.y) > abs(w.x - b.x))
    {
        swap(b.x, b.y); swap(w.x, w.y); swap(bw.x, bw.y);
    }
    if(b.x > w.x)swap(b, w);
    if(w.x - b.x <= 1){printf("NO\n0\n");return 0;}
    if(w.x - b.x == 2){printf("NO\n1\n");return 0;}
    if(w.x - b.x == 3){printf("NO\n2\n");return 0;}
    
    int Up_x= b.x, Down_x= w.x, Up_y1= b.y, Up_y2= b.y, Down_y1= w.y, Down_y2= w.y;
    
    while(Up_x + 1 < Down_x)
    {
        ++Up_x;
        --Up_y1;
        ++Up_y2;
    }
    
    int Mid= (w.x - b.x) >> 1; Mid -- ;
    int Left, Right;
    Step= 0;
    for(int i(0); i< Mid; ++ i)
    {
        ++Step;
        --Down_x; --Down_y1; ++Down_y2;
        Left= max(max(Down_y1, 1), max(Up_y1, 1));
        Right= min(min(Down_y2, N), min(Up_y2, N));
        //if(Step == 31)
        //printf("%d %d %d\n", Down_x, Left, Right);
        int t1= bw.y + Step, t2= bw.y - Step;
        if((abs(Down_x - bw.x) == Step && ((bw.y >= Left && bw.y <= Right) || (abs(Left - bw.y) <= Step) || (abs(Right - bw.y) <= Step))) 
         || (((Left <= t1 && t1 <= Right) || (Left <= t2 && t2 <= Right)) && abs(bw.x-Down_x) <= Step))
        {
            if(Step < Ans)Ans= Step;
        }
        --Up_x; ++Up_y1; --Up_y2;
    }
    
    Up_x= b.x, Down_x= w.x, Up_y1= b.y, Up_y2= b.y, Down_y1= w.y, Down_y2= w.y;
    
    while(Up_x + 1 < Down_x)
    {
        --Down_x;
        --Down_y1;
        ++Down_y2;
    }
    
    Step= 0;
    for(int i(0); i< Mid; ++ i)
    {
        ++Step;
        ++Up_x; --Up_y1; ++Up_y2;
        Left= max(max(Down_y1, 1), max(Up_y1, 1));
        Right= min(min(Down_y2, N), min(Up_y2, N));
        //printf("%d %d %d\n", Up_x, Left, Right);
        int t1= bw.y + Step, t2= bw.y - Step;
        if((abs(Up_x - bw.x) == Step && ((bw.y >= Left && bw.y <= Right) || (abs(Left - bw.y) <= Step) || (abs(Right - bw.y) <= Step)))
          || (((Left <= t1 && t1 <= Right) || (Left <= t2 && t2 <= Right)) && abs(bw.x-Up_x) <= Step))
        {
            if(Step < Ans)Ans= Step;
        }
        ++Down_x; ++Down_y1; --Down_y2;
    }
    if(Ans == INF)
        printf("NO\n%d\n", w.x - b.x - 1);//(((w.x - b.x) & 1) ? 0 : 1));
    else
        printf("YES\n%d\n", Ans);

    return 0 ;
}
