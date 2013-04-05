#include<stdio.h>
long long a[20];  
long long b[20]; 
//定理：n个结点能形成的二叉树总数为 卡特兰数 C(2n,n)/(n+1) 或者由递推公式Ci+1=2*(2*i+1)/(i+2)*Ci 
//设计figure(n)，n代表这棵树整体的偏移量
//分别算出其左右子树各自的偏移量，递归求解即可
//由于先递归左儿子，输出顺序与题意相符
void figure(int n) 
{       
    int t,i,j;  
    if(n==1){printf("X");return;}     
    j=0;
    while(true) if(b[++j]>=n) break;         
    n=n-b[j-1];//j代表有几个结点，n此时代表在这些结点下的序号    
    for(i=0;i<j;i++)   
    {          
        t=a[i]*a[j-1-i];    
        if(t>=n)  break;           
        else n=n-t;   
    }     
    if(i!=0)    //i是此时左子树挂的节点数
    {        
        printf("(");  
        figure(b[i-1]+1+(n-1)/a[j-1-i]);//初始的时刻，只需要增加1，左子树的偏移量就增加1，而之后的部分，需要右子树变换a[j-i-1]次，左子树的偏移量才增加1  
        printf(")");
    }    
    printf("X");  
    if(i!=j-1)    
    {        
        printf("(");  
        figure(b[j-2-i]+1+(n-1)%a[j-1-i]);   
        printf(")");   
    }   
}        
int main()  
{      
	freopen("t.in", "r", stdin);
    int n;   
    int i,j;     
    a[0]=1;     
    a[1]=1;       
    b[1]=1;     
    b[0]=0;     
    for(i=2;i<20;i++) 
    {        
        a[i]=2*(2*(i-1)+1)*a[i-1]/(i+1) ;//卡特兰数递推公式
        b[i]=b[i-1]+a[i];   
    }    
    while(scanf("%d",&n)&&n)   
    {      
        figure(n);   
        printf("\n");   
    }       
    return 0;  
}  
