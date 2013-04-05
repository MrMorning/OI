#include <vector>
#include <list>
#include <map>
#include <set>
#include <deque>
#include <queue>
#include <stack>
#include <bitset>
#include <algorithm>
#include <functional>
#include <numeric>
#include <utility>
#include <sstream>
#include <iostream>
#include <iomanip>
#include <cstdio>
#include <cmath>
#include <cstdlib>
#include <cctype>
#include <string>
#include <cstring>
#include <ctime>
#include <string.h>

using namespace std;

typedef long long int64;
typedef unsigned long long uint64;
#define two(X) (1<<(X))
#define twoL(X) (((int64)(1))<<(X))
#define contain(S,X) (((S)&two(X))!=0)
#define containL(S,X) (((S)&twoL(X))!=0)
const double pi=acos(-1.0);
const double eps=1e-11;
template<class T> inline void checkmin(T &a,T b){if(b<a) a=b;}
template<class T> inline void checkmax(T &a,T b){if(b>a) a=b;}
template<class T> inline T sqr(T x){return x*x;}
typedef pair<int,int> ipair;
#define SIZE(A) ((int)A.size())
#define LENGTH(A) ((int)A.length())
#define MP(A,B) make_pair(A,B)
#define PB(X) push_back(X)

const int M=512;

bool visited[32][32];
double buffer[32][32][32];
double C[32][32];
double E[32][32][32][32],G[32][32];
double f[32][M];

void prepare(int n,int m,double x)
{
	int md=0;
	for (;n>0;n/=2) md++;
	for (int d=0;d<=md;d++,x*=2) 
	{
		memset(E[d],0,sizeof(E[d]));
		double cos_x_pw[32],sin_x_pw[32],h[32];
		double cos_x=cos(x),sin_x=sin(x);
		for (int i=0;i<32;i++)
		{
			sin_x_pw[i]=(i==0)?1:(sin_x_pw[i-1]*sin_x);
			cos_x_pw[i]=(i==0)?1:(cos_x_pw[i-1]*cos_x);
		}
		for (int k=0;k<=m;k++) 
		{
			for (int e=0;e<=k;e++) h[e]=cos_x_pw[e]*sin_x_pw[k-e];
			memset(G,0,sizeof(G));
			for (int d1=0;d1<=k;d1++) for (int d2=k-d1,e1=0;e1<=d1;e1++) for (int e2=0;e2<=d2;e2++)
			{
				int f2=e1+d2-e2;
				double t3=C[d1][e1]*C[d2][e2];
				if ((d2-e2)&1)
					G[d1][f2]-=t3*h[e1+e2];
				else
					G[d1][f2]+=t3*h[e1+e2];
			}
			for (int c1=0;c1<=m;c1++) 
			{			
				double *F=E[d][k][c1];
				for (int d1=max(0,k+c1-m);d1<=c1 && d1<=k;d1++)
				{
					double t1=C[c1][d1]*C[m-c1][k-d1],*F0=F+(c1-d1),*G0=G[d1];;
					for (int f2=0;f2<=k;f2++) F0[f2]+=G0[f2]*t1;
				}
			}
		}
	}
}
double* solve(int h,int n,int m,int d,double x)
{
	if (visited[d][h-n]) return buffer[d][h-n];
	visited[d][h-n]=true;
	double *ret=buffer[d][h-n];
	if (n==0)
	{
		for (int i=0;i<=m;i++) ret[i]=0;
		ret[0]=1;
		return ret;
	}
	for (int c_sin=0;c_sin<=m;c_sin++) ret[c_sin]=0;
	for (int k=0;k<=m;k++) if (k<=n && (n-k)%2==0)
	{
		double *tmp=solve(h/2,(n-k)/2,m,d+1,x+x);
		for (int x=0;x<=m;x++) 
		{
			double s=0,*factor=E[d][k][x];
			for (int y=0;y<=m;y++) s+=factor[y]*tmp[y];
			ret[x]+=s;
		}
	}
	return ret;
}

#ifdef _MSC_VER
map<ipair,double> M2;
double solve2(int n,int m,double x)
{
	if (m==1) return sin(x*n);
	if (M2.find(MP(n,m))!=M2.end()) return M2[MP(n,m)];
	double ret=0;
	for (int i=0;i<=n;i++) ret+=sin(x*i)*solve2(n-i,m-1,x);
	return M2[MP(n,m)]=ret;
}

uint64 rdtsc()
{
	__asm { rdtsc }
}
#endif

double get_c(int n,int m)
{
	double r=1;
	for (int i=1;i<=m;i++) r=r*(n+1-i)/i;
	return r;
}
void preprocess()
{
	double sf[M];
	for (int i=0;i<M;i++) sf[i]=sin((double)i/M*pi*2.0);
	memset(f,0,sizeof(f));
	for (int k=0;k<M;k++) f[1][k]=sf[k];
	for (int i=1;i+1<32;i++) 
	{
		double *f0=f[i],*f1=f[i+1];
		for (int k=0;k<M;k++) for (int p=0,t=k;p<M;p++,t=(t==M-1)?0:(t+1)) f1[t]+=f0[k]*sf[p];
		for (int k=0;k<M;k++) f1[k]/=M;
	}
}
int main()
{
	freopen("t.in", "r", stdin);
#ifdef _MSC_VER
	freopen("input.txt","r",stdin);
	uint64 time_used1=0,time_used2=0;
#endif
	memset(C,0,sizeof(C));
	for (int i=0;i<32;i++) for (int j=0;j<=i;j++) C[i][j]=(j==0)?1:(C[i-1][j-1]+C[i-1][j]);
	int n,m;
	double x;
	int testcase;
	preprocess();
	double start_time=(double)clock();
	scanf("%d",&testcase);
	for (int case_id=0;case_id<testcase;case_id++)
	{
		scanf("%d%d%lf",&m,&n,&x);
		if (fabs(x)<1e-6)
		{
			printf("%6e\n",0.0);
			continue;
		}
		if (n>10000000)
		{
			double y=fmod(x*n,pi+pi);
			int d=(int)(y/(pi+pi)*M+0.5);
			if (d<0) d=0;
			if (d>M-1) d=M-1;
			double ret=get_c(n-1,m-1)*f[m][d];
			printf("%6e\n",ret);
			continue;
		}
#ifdef _MSC_VER
		uint64 time1=rdtsc();
#endif
		prepare(n,m,x);
#ifdef _MSC_VER
		uint64 time2=rdtsc();
		time_used1+=time2-time1;
#endif
		memset(visited,false,sizeof(visited));
		double *ret=solve(n,n,m,0,x);
#ifdef _MSC_VER
		uint64 time3=rdtsc();
		time_used2+=time3-time2;
#endif
#ifdef _MSC_VER
		printf("%6e\n",ret[m]);
		double r1=ret[m];
		M2.clear();
		double r2=(n>=1000)?r1:solve2(n,m,x);
		if (fabs(r1-r2)>max(1.0,fabs(r2))*1e-5)
		{
			printf("ERROR %d %d %.2lf\n%.6lf\n%.6lf\n",n,m,x,r1,r2);
			return 0;
		}
		printf("PASSED...\n");
#else
		printf("%6e\n",ret[m]);
		double current_time=(double)clock();
		if (current_time-start_time>(double)CLOCKS_PER_SEC && case_id+1>=5)
			break;
#endif
	}
#ifdef _MSC_VER
	printf("DONE!\n");
	printf("T1 = %.3lf\n",(double)time_used1/1e9);
	printf("T2 = %.3lf\n",(double)time_used2/1e9);
#endif
	return 0;
}

