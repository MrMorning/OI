program pku1007;
type
TData=record
adj:longint;
s:string;
end;

var
a:array[1..100] of TData;
n,m,i,j,t,k:longint;

procedure qsort;

    procedure sort(l,r: longint);
      var
         i,j: longint;
         x,y: TData;
      begin
         i:=l;
         j:=r;
         x:=a[(l+r) div 2];
         repeat
           while a[i].adj<x.adj do
            inc(i);
           while x.adj<a[j].adj do
            dec(j);
           if not(i>j) then
             begin
                y:=a[i];
                a[i]:=a[j];
                a[j]:=y;
                inc(i);
                j:=j-1;
             end;
         until i>j;
         if l<j then
           sort(l,j);
         if i<r then
           sort(i,r);
      end;

    begin
       sort(1,m);
    end;
begin
readln(n,m);
for i:=1 to m do
    with a[i] do
    begin
    readln(s);
    t:=0;
    for j:=1 to length(s) do
        begin
        for k:=j+1 to length(s) do
              begin
              if s[j]>s[k] then
                 inc(t)
              end;
        end;
    adj:=t;
    end;
qsort;
for i:=1 to m do
    writeln(a[i].s);
end.
