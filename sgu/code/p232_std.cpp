#include <vector>
#include <algorithm>
#include <utility>
#include <iostream>
#include <cstdio>
#include <cmath>
#include <cstdlib>
#define rep(i,n) for(int i=0;i<n;i++)
#define pb push_back
const int inf=~0U>>1,maxn=150000+1;
using namespace std;
int A[maxn],n;
typedef long long ll;
int gcd(int a,int b){return b?gcd(b,a%b):a;}
int get(ll i){return A[i%n];}
int main()
{
    freopen("t.in","r",stdin);
    char c;int k,d,l;cin>>n>>k;k%=n;d=gcd(k,n),l=n/d;
    scanf("\n");rep(i,n)scanf("%c",&c),A[i]=c-'0';
    int m=-1;
    rep(a,d)
    {
        int i=0,j=1;ll t=0;
        while(i<l&&j<l&&t<l)
        {
            int A=get(a+(i+t)*k),B=get(a+(j+t)*k);
            if(A==B)t++;
            else
            {
                if(A<B){i+=t+1;t=0;}
                else{j+=t+1;t=0;}
                if(i==j)j++;
            }
        }
        t=a+min(i,j)*ll(k);t%=n;bool c;
        if(m<0)c=true;
        else rep(i,l)
        {
            int A=get(t+ll(i)*k),B=get(m+ll(i)*k);
            if(A<B){c=false;break;}
            if(A>B){c=true;break;}
        }
        if(c)m=t;
    }
    rep(i,n)printf("%d",get(m+ll(i)*k));
    printf("\n");
}

