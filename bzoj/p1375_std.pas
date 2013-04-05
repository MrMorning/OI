    program p1375;  
      
    const inf=maxlongint shr 2;  
          maxn=200;  
          maxe=2000;  
      
 type rec=record  
                x,y,data:longint;  
          end;  
   
 var ans,tc,n,m,s,t,tot:longint;  
     bian:Array[0..maxe]of record  
                                   d:array[1..2]of longint;  
                                   x,y,next:longint;  
                           end;  
     w:array[0..100*20000]of rec;  
     mincost,first:array[0..maxn]of longint;  
     p:array[0..100,0..20000]of longint;  
     v:Array[0..100,0..20000]of boolean;  
   
 procedure connect(a,b,w,c:longint);  
 begin  
      inc(tot);  
      with  bian[tot] do  
      begin  
           x:=a;  
           y:=b;  
           d[1]:=w;  
           d[2]:=c;  
           next:=first[x];  
           first[x]:=tot;  
      end;  
 end;  
   
 procedure init;  
 var i,a,b,w,c:longint;  
 begin  
      readln(n,m,s,t);  
      for i:=1 to m do  
      begin  
           readln(a,b,w,c);  
           connect(a,b,w,c);  
           connecT(b,a,w,c);  
           tc:=c+tc;  
      end;  
      if tc>10000 then tc:=10000;  
 end;  
   
 procedure up(i:longint);  
 var tmp:rec;  
     j:longint;  
 begin  
      tmp:=w[i];  
      while i>1 do  
      begin  
           j:=i div 2;  
           if (w[j].data>tmp.data)or((w[j].data=tmp.data)and(w[j].y>tmp.y)) then  
           begin  
                w[i]:=w[j];  
                p[w[i].x,w[i].y]:=i;  
                i:=j;  
           end  
           else break;  
      end;  
      w[i]:=tmp; p[w[i].x,w[i].y]:=i;  
 end;  
   
   
 procedure down(i:longint);  
 var tmp:rec;  
     j:longint;  
 begin  
      tmp:=w[i];  
      j:=i*2;  
      while j<=tot do  
      begin  
           if j<tot THEN  
           IF (w[j].data>w[j+1].data)or ((w[j].data=w[j+1].data)and(w[j].y>w[j+1].y)) then inc(j);  
           if ((w[j].data<tmp.data)or((w[j].data=tmp.data)and(w[j].y<tmp.y))) then  
           begin  
                w[i]:=w[j];  
                p[w[i].x,w[i].y]:=i;  
                i:=j;  
                j:=j*2;  
           end  
           else break;  
      end;  
      w[i]:=tmp; p[w[i].x,w[i].y]:=i;  
 end;  
   
   
 procedure main;  
 var x,i,k,j,xx,yy,key:longint;  
 begin  
      for i:=1 to n do mincost[i]:=inf;  
      mincost[s]:=inf;  
      tot:=1;  
      p[s,0]:=1;  
      w[1].data:=0;  
      w[1].x:=s;  
      w[1].y:=0;  
   
      repeat  
            if w[1].data=inf then break;  
            if w[1].y<mincost[w[1].x] then  
            begin  
                 mincost[w[1].x]:=w[1].y;  
                 if w[1].x=t then  inc(ans)  
                 else  
                 begin  
                      k:=first[w[1].x];  
                      xx:=w[1].x; yy:=w[1].y;key:=w[1].data;  
                      while k<>0 do with bian[k] do  
                      begin  
                           if (p[y,yy+d[2]]=0) then  
                           begin  
                                inc(tot);  
                                p[y,yy+d[2]]:=tot;  
                                w[tot].x:=y;  
                                w[tot].y:=yy+d[2];  
                                w[tot].data:=inf;  
                           end;  
                           if ((key+d[1]<w[p[y,yy+d[2]]].data)and(not v[y,yy+d[2]])) then  
                           begin  
                                w[p[y,yy+d[2]]].data:=key+d[1];  
                                up(p[y,yy+d[2]]);  
                           end;  
                           k:=next;  
                      end;  
                 end;  
            end;  
            w[1].data:=inf;  
            v[w[1].x,w[1].y]:=true;  
            down(1);  
      until 1=2;  
      writeln(ans);  
 end;  
   
 begin  
	 assign(input, 't.in'); reset(input);
      init;  
      main;  
 end.  


