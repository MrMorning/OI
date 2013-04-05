#include <iostream>
#include <cstdlib>
#include <cstdio>
#include <cstring>
#include <string>
using namespace std;

const int MAX_N = 20010;

struct In
{     
	int left;
	int right;
}str[8*MAX_N];

struct Node
{
	int left;
	int right;
	int mid;
	int color;      
}node[8*MAX_N];
int d[8*MAX_N];
bool boo[10000003];
int hash[10000003];

int cmp( const void *a , const void *b ){
	return *(int *)a-*(int *)b;
}

void B_Tree( int left , int right , int num ){            //建树
	node[num].left = left;
	node[num].right = right;
	node[num].mid = (left+right)/2;
	node[num].color = 0;
	if( left + 1 != right ){
		B_Tree( left , node[num].mid , 2*num );
		B_Tree( node[num].mid , right , 2*num+1 );   
	}
}

void insert( int left , int right , int num , int &sum ){   //插入
	if( node[num].color >= node[num].right - node[num].left ){  //区间是否全部被覆盖
		return ;   
	}
	if( left == node[num].left && right == node[num].right ){
		sum++;
		node[num].color = node[num].right - node[num].left;
		return ;
	}
	if( right <= node[num].mid ){
		insert(left, right, 2*num , sum );
	}else if( left >= node[num].mid ){
		insert( left , right , 2*num+1 , sum );     
	}else{
		insert( left , node[num].mid , 2*num , sum );
		insert( node[num].mid , right , 2*num+1 , sum );    
	}
	node[num].color = node[2*num].color + node[2*num+1].color; //根节点等于它左右子树的和
}

int main()
{   
	int cas , n , i , j ,m;
	freopen("t.in", "r", stdin);
	scanf("%d",&cas);
	memset( boo , false , sizeof(boo) );
	while( cas-- ){
		scanf("%d",&n);
		m = 0;
		for( i = 1 ; i <= n ; i++ ){
			scanf("%d%d",&str[i].left,&str[i].right);
			str[i].right++;
			if( !boo[str[i].left] ){
				d[m++] = str[i].left;
				boo[str[i].left] = true;
			}
			if( !boo[str[i].right] ){
				d[m++] = str[i].right; 
				boo[str[i].right] = true;
			}
		}   
		qsort( d , m , sizeof(d[0]) , cmp );
		j = 1;
		for( i = 0 ; i < m ; i++ ){     //离散化过程
			boo[d[i]] = false;
			hash[d[i]] = j++;
		}
		int sum = 0;
		B_Tree( 1 , j , 1 );
		for( i = n ; i >= 1 ; i-- ){
			int k = 0;
			insert( hash[str[i].left] , hash[str[i].right] , 1 , k );
			if( k > 0 ){
				sum++;
			}
		}
		printf("%d\n",sum);
	}
	return 0;   
}
