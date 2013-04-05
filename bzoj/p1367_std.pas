Program seq;
Var dis,v,lc,rc,st,q:array[0..1000001] of longint;
    i,j,k,l,m,n:longint;
    ans:int64;
Procedure swap(var a,b:longint);var c:longint;
begin c:=a;a:=b;b:=c;end;
Function Merge(x,y:longint):longint;
Begin
  if (x=0) or (y=0) then exit(x+y);
  if v[x]<v[y] then swap(x,y);
  rc[x]:=merge(rc[x],y);
  if dis[rc[x]]>dis[lc[x]] then swap(rc[x],lc[x]);
  dis[x]:=dis[rc[x]]+1;
  exit(x);
end;
Begin
  assign(input, 't.in'); reset(input);
  dis[0]:=-1;
  readln(n);
  for i:=1 to n do
    begin
      read(v[i]);
      dec(v[i],i);
      inc(m);
      st[m]:=i;q[m]:=i;
      while (m>1) and (v[st[m]]<v[st[m-1]]) do
        begin
          st[m-1]:=merge(st[m],st[m-1]);
          dec(m);
          if odd(q[m+1]-q[m]) and odd(q[m]-q[m-1]) then
            st[m]:=merge(lc[st[m]],rc[st[m]]);
          q[m]:=q[m+1];
        end;
    end;
  for i:=1 to m do
    for j:=q[i-1]+1 to q[i] do
      ans:=ans+int64(abs(v[j]-v[st[i]]));
  writeln(ans);
end.
