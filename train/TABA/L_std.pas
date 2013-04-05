const maxn=150001;
var
  b:array[1..maxn shl 1]of boolean;
  q,t:array[1..maxn shl 1]of longint;
  s:array[1..2,0..maxn shl 1]of longint;
  a:ARRAY[1..MAXN,1..2]OF LONGINT;
  n,k,m,p,n2,i,x,y,qu:longint;
  nn:array[1..2]of longint;
  ff:boolean;

procedure dgs(x:longint);
begin
  b[x]:=true;
  if b[t[x]] then
  begin
    if not((q[t[x]]<>0)or(t[x]=p)) then
      begin q[x]:=-100000000; exit; end;
    q[x]:=q[t[x]]+1;
    if (x<=n)and(q[x]>0) then
      inc(s[k,q[x]]);
    exit;
  end;
  dgs(t[x]);
  q[x]:=q[t[x]]+1;
  if (q[x]>0)and(x<=n) then
    inc(s[k,q[x]]);
end;

procedure dfs(x:longint);
begin
  if x=785 then
    x:=x;
  b[x]:=true;
  if b[t[x]] then
  begin
    if t[x]=p then
    begin
      inc(nn[k]);
      q[x]:=nn[k];
      if x<=n then
      inc(s[k,nn[k]]);
      ff:=true;
    end
    else begin
      ff:=false;
      q[x]:=-10000000;
    end;
    exit;
  end;
  dfs(t[x]);
  if ff then
  begin
    inc(nn[k]);
    q[x]:=nn[k];
    if x<=n then
      inc(s[k,nn[k]]);
  end else
    q[x]:=-10000000;
end;

procedure doxo(x,y:longint);
begin
  if a[x,1]=0 then
    a[x,1]:=y
  else if a[x,2]=0 then
    a[x,2]:=y;
end;

function doo(x,l:longint):longint;
begin
  if l>=1000000 then
  begin
    if x<=n2 then exit(x)
    else exit(n2+1);
  end;
  if x>n2 then
  begin
    x:=x mod l;
    x:=x+(n2-x)div l*l;
    exit(x);
  end
  else exit(x);
end;

procedure insert(x,y:longint);
begin
  t[x]:=y;
end;

begin
assign(input, 't.in'); reset(input);
  readln(n,m,p); n2:=n shl 1;  inc(p);
  for i:=1 to m do
  begin
    read(x,y);  inc(x); inc(y);
    doxo(x,y);
    doxo(y,x);
  end;
  for i:=1 to n do
  begin
    if (a[a[i,1],1]<>i)or(a[a[i,1],2]=0) then
      insert(i,a[i,1])
    else insert(i,a[i,1]+n);
    if a[i,2]<>0 then
    begin
      if (a[a[i,2],1]<>i)or(a[a[i,2],2]=0) then
        insert(i+n,a[i,2])
      else insert(i+n,a[i,2]+n);
    end;
  end;
  ff:=false;
  k:=1;
  b[p]:=true;
  dfs(t[p]);
  inc(nn[k]);
  q[p]:=0;
  for i:=1 to n do
  begin
    if not b[i] then
      dgs(i);
  end;
  if not ff then
  begin
    nn[k]:=10000000;
  end;
  s[1,0]:=1;
if t[p+n]<>0 then
begin
  ff:=false;
  fillchar(b,sizeof(b),false);
  fillchar(q,sizeof(q),0);
  k:=2;
  b[p+n]:=true;
  p:=p+n;
  dfs(t[p]);
  inc(nn[k]);
  q[p]:=0;
  for i:=1 to n do
  begin
    if not b[i] then dgs(i);
  end;
  if not ff then
  begin
    nn[k]:=10000000;
  end;
end else nn[2]:=100000000;
  for i:=nn[1] to n2 do
    s[1,i]:=s[1,i]+s[1,i-nn[1]];
  for i:=nn[2] to n2 do
    s[2,i]:=s[2,i]+s[2,i-nn[2]];
  qu:=doo(5,nn[1]);
  readln(qu);
  for i:=1 to qu do
  begin
    read(x);
    writeln(s[1,doo(x,nn[1])]+s[2,doo(x,nn[2])]);
  end;
end.

