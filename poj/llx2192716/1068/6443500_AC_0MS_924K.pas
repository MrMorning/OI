program pku1068;
var
k,i:longint;
procedure doit;
var
i,j,a,b,t,times,top,n,len:longint;
ans:array[1..20] of integer;
stack:array[1..20] of integer;
S:string;
begin
readln(n);
s:='';
a:=0;
for i:=1 to n do
    begin
    read(b);
    t:=b-a;
    for j:=1 to t do
        s:=s+'(';
    s:=s+')';
    a:=b;
    end;
top:=0;
len:=0;
for i:=1 to length(s) do
    begin
    if s[i]='(' then
       begin
       inc(top);
       stack[top]:=i;
       end
    else
        begin
        times:=0;
        for j:=stack[top] to i do
            if s[j]='(' then inc(times);
        inc(len);
        ans[len]:=times;
        dec(top);
        end;
    end;
write(ans[1]);
for i:=2 to n do write(' ',ans[i]);
writeln;

end;

begin
readln(k);
for i:=1 to k do
    doit;
end.
