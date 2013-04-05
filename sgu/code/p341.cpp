#include<iostream>
#include <cstdio>
#include<string>
#include<vector>
#include<map>
using namespace std;

const int NOT=0,AND=1,NAND=2,OR=3,NOR=4,DFF=5,INPUT=6;
int kind[10011],input[10011],output[10011];

vector <int> g[10011];
int deg[10011],top[10011],value[10011],last_value[10011];

map <string,int> names;
int n;
int get_name(string a)
{
    if(!names[a])
        names[a]=++n;
    return names[a];
}

string opt;
int main()
{
    int i,j;
    freopen("t.in","r",stdin);
    int ilen=0,ilen2=0,olen=0;
    while(1)
    {
        getline(cin,opt);
        if(opt=="INPUT VALUES")
            break;
        if(opt[0]=='#'||opt.size()==0)
            continue;
        if(opt.substr(0,6)=="INPUT(")
        {
            top[ilen++]=get_name(opt.substr(6,opt.size()-7));
            input[ilen2++]=top[ilen-1];
            kind[top[ilen-1]]=INPUT;
            continue;
        }
        if(opt.substr(0,7)=="OUTPUT(")
        {
            output[olen++]=get_name(opt.substr(7,opt.size()-8));
            continue;
        }
        
        int now=get_name(opt.substr(0,opt.find(" ")));
        int pos1=opt.find("=")+2,pos2=opt.find("(");
        string door=opt.substr(pos1,pos2-pos1);
        if(door=="NOT")
            kind[now]=NOT;
        if(door=="AND")
            kind[now]=AND;
        if(door=="NAND")
            kind[now]=NAND;
        if(door=="OR")
            kind[now]=OR;
        if(door=="NOR")
            kind[now]=NOR;
        if(door=="DFF")
        {
            kind[now]=DFF;
            top[ilen++]=now;
            deg[now]=1000000000;
        }
        
        string var;
        for(j=opt.find("(")+1;opt[j]!=')';)
        {
            for(;opt[j]!=','&&opt[j]!=')';++j)
                var.push_back(opt[j]);
            int vname=get_name(var);
            var.clear();
            g[vname].push_back(now);
            deg[now]++;
            if(opt[j]!=')')
                j+=2;
        }
    }
    
    for(int fr=0,to=ilen-1;fr<=to;++fr)
    {
        i=top[fr];
        for(vector <int> :: iterator j=g[i].begin();j!=g[i].end();++j)
        {
            deg[*j]--;
            if(deg[*j]==0)
                top[++to]=*j;
        }
    }
    
    while(cin>>opt)
    {
        for(i=1;i<=n;++i)
            if(kind[i]!=DFF)
                if(kind[i]!=AND&&kind[i]!=NAND)
                    value[i]=0;
                else
                    value[i]=1;
            else
                last_value[i]=value[i];
        for(i=0;i<opt.size();++i)
            value[input[i]]=opt[i]-'0';
        for(i=0;i<n;++i)
        {
            int now=top[i];
            if(kind[now]==NOT||kind[now]==NOR||kind[now]==NAND)
                value[now]=!value[now];
            int nv=kind[now]==DFF?last_value[now]:value[now];
            for(vector <int> :: iterator j=g[now].begin();j!=g[now].end();++j)
                switch(kind[*j])
                {
                    case AND: case NAND:
                        value[*j]&=nv;
                        break;
                    case OR: case NOR:
                        value[*j]|=nv;
                        break;
                    case NOT: case DFF:
                        value[*j]=nv;
                        break;
                }
        }
        for(i=0;i<olen;++i)
            if(kind[output[i]]!=DFF)
                cout<<value[output[i]];
            else
                cout<<last_value[output[i]];
        cout<<endl;
    }
    return 0;
}
