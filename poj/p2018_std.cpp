#include<iostream>
#include <cstdio>
using namespace std;
int a[100001];//a[i]

double b[100001];//b[i]表示以第i个元素结尾的子段的最大平均值

int n[100001];//n[i]表示以第i个元素结尾的长度为F的子段和

int c[100001];//c[i]表示以第i个元素结尾的最大平均值子段的元素个数

int Max(int a,int b)
{
    return a>b?a:b;
}
int main()
{
	freopen("t.in", "r", stdin);
    int N,F;
    cin>>N>>F;
    int i;
    for(i=1;i<=N;++i)
        cin>>a[i];
    n[F]=0;
    for(i=1;i<=F;++i)
        n[F]+=a[i];
    for(i=F+1;i<=N;++i)
    {
        n[i]=(n[i-1]-a[i-F]+a[i]);
    }
    b[F]=(double)n[F]/F;
    c[F]=F;
    for(i=F+1;i<=N;++i)
    {
        double temp;
        temp=(b[i-1]*c[i-1]+a[i])/(c[i-1]+1);
        double temp2=(double)n[i]/F;
        if(temp>temp2)
        {
            b[i]=temp;
            c[i]=c[i-1]+1;
        }
        else
        {
            b[i]=temp2;
            c[i]=F;
        }
    }
    int iMax=0;
    double dMax=0;
    for(i=F;i<=N;++i)
    {
        if(dMax<b[i])
            dMax=b[i];
    }
    iMax=dMax*1000;
    cout<<iMax<<endl;
    return 0;
}
