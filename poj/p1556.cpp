#include <stdlib.h>
#include <stdio.h>
#include <string.h>
#include <iostream>
#include <iomanip>
#include <cmath>
using namespace std;

class Vector
{
	public:
		double x,y;
		Vector(){};
		Vector(double xx,double yy):x(xx),y(yy){};
	Vector operator+(Vector &p2)
	{
		return Vector(x+p2.x,y+p2.y);
	}
	
	Vector operator-(Vector &p2)
	{
		return Vector(x-p2.x,y-p2.y);
	}	
};

double cross(const Vector &p1,const Vector &p2)
{
	return (p1.x*p2.y-p1.y*p2.x);
}


class LineSegment
{
	public:
		Vector p1,p2;
		LineSegment(){};
		LineSegment(Vector &pp1,Vector &pp2):p1(pp1),p2(pp2){};
		bool intersect(LineSegment&);
};
bool LineSegment::intersect(LineSegment &l2)//这里指规范相交
{
	Vector &q1=l2.p1;
	Vector &q2=l2.p2;
	//1.快速排斥实验
	if (!((max(p1.x,p2.x)>min(q1.x,q2.x))
		&&(max(p1.y,p2.y)>min(q1.y,q2.y))
		&&(max(q1.x,q2.x)>min(p1.x,p2.x))
		&&(max(q1.y,q2.y)>min(p1.y,p2.y))))
		return false;
	//2.跨立实验
	bool b1=(cross(q1-p1,p2-p1)*cross(p2-p1,q2-p1))>0;
	if (!b1) return false;
	bool b2=(cross(p1-q1,q2-q1)*cross(q2-q1,p2-q1))>0;
	return (b2);	
}

const int MAX_INT=100000;
const int MAX_VNUM=4*18+2;
const int MAX_WALLNUM=54;

int wallNum,cNum,vNum;
LineSegment wall[MAX_WALLNUM+1];
Vector v[MAX_VNUM+1];
double dist[MAX_VNUM+1][MAX_VNUM+1];

bool reachable(Vector &p1,Vector &p2)
{
	LineSegment l=LineSegment(p1,p2);
	for(int i=1;i<=wallNum;i++)
	{
		if (l.intersect(wall[i]))
			return false;
	}
	return true;
}

float calcDist(Vector &p1,Vector &p2)
{
	return sqrt((p1.x-p2.x)*(p1.x-p2.x)+(p1.y-p2.y)*(p1.y-p2.y));
}



void init()
{
	cin>>cNum;
	if (cNum==-1)
		exit(0);
	vNum=0;
	wallNum=0;
	v[++vNum]=Vector(0,5);
	Vector preV;
	for(int i=1;i<=cNum;i++)
	{
		double tmpX;
		cin>>tmpX;
		preV=Vector(tmpX,0);
		for(int j=1;j<=4;j++)
		{
			double tmpY;
			cin>>tmpY;
			v[++vNum]=Vector(tmpX,tmpY);
			if (j%2==1)
				wall[++wallNum]=LineSegment(preV,v[vNum]);
			else
				preV=v[vNum];
		}
		Vector lastV=Vector(tmpX,10);
		wall[++wallNum]=LineSegment(v[vNum],lastV);
	}
	v[++vNum]=Vector(10,5);
	for(int i=1;i<=vNum;i++)
		for(int j=1;j<=vNum;j++)
			dist[i][j]=reachable(v[i],v[j])?calcDist(v[i],v[j]):MAX_INT;
}

void solve()
{
	bool used[MAX_VNUM+1];
	double f[MAX_VNUM+1];
	memset(used,0,sizeof(used));
	for(int i=1;i<=vNum;i++)
		f[i]=dist[1][i];
	f[1]=0;
	used[1]=true;
	for(int i=1;i<=vNum-1;i++)
	{
		double minDist=0x7FFFFFFF;
		int u;
		for(int j=1;j<=vNum;j++)
			if ((!used[j])&&(f[j]<minDist))
			{
				u=j;
				minDist=f[j];
			}
		used[u]=true;
		for(int k=1;k<=vNum;k++)
		{
			if((!used[k])&&(f[k]>f[u]+dist[u][k]))
			{
				f[k]=f[u]+dist[u][k];
			}
		}
	}	
	cout<<setprecision(2)<<setiosflags(ios::fixed)<<f[vNum]<<endl;
}

int main()
{
	while (1)
	{
		init();
		solve();
	}
}
