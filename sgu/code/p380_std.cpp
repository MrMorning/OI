#include<cstdio>
#include<cstdlib>
#include<iostream>
#include<algorithm>

using namespace std;

const int MAX_N=100000;

int n;
int h[MAX_N+1];

int main(int argc, char** argv)
{
	freopen("t.in", "r", stdin);
    while(scanf("%d",&n)!=EOF)
    {
        for(int i=0;i<n;++i)
            scanf("%d",&h[i]);
        int l,r;
        int lMax=0,lMin=0,rMax=0,rMin=0;
        for(l=0,r=n-1;l<r;)
        {
            lMax=max(lMax,h[l]);
            lMin=min(lMin,h[l]);

            rMax=max(rMax,h[r]);
            rMin=min(rMin,h[r]);

            if(lMin<=rMin && rMax<=lMax)
                --r;
            else if(rMin<=lMin && lMax<=rMax)
                ++l;
            else
                break;
        }
        if(l==r)
            printf("YES");
        else
            printf("NO");
    }
    return (EXIT_SUCCESS);
}
