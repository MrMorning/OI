program p2676;
const
c:array[1..9,1..9] of integer =
                   ((1,1,1,2,2,2,3,3,3),
                   (1,1,1,2,2,2,3,3,3),
                   (1,1,1,2,2,2,3,3,3),
                   (4,4,4,5,5,5,6,6,6),
                   (4,4,4,5,5,5,6,6,6),
                   (4,4,4,5,5,5,6,6,6),
                   (7,7,7,8,8,8,9,9,9),
                   (7,7,7,8,8,8,9,9,9),
                   (7,7,7,8,8,8,9,9,9));
var
a:array[1..9,1..9] of integer;
b,m,n:array[1..9] of set of 1..9;
ok:array[1..9,1..9] of boolean;
i,j,t,k,testnum:integer;
ch:char;
over:boolean;

procedure print;
var
i,j:integer;
begin
for i:=1 to 9 do
    begin
    for j:=1 to 9 do
        write(a[i,j]);
    writeln;
    end;
end;

procedure fill(x,y,t:integer);
begin
a[x,y]:=t;
ok[x,y]:=true;
b[c[x,y]]:=b[c[x,y]]+[t];
m[x]:=m[x]+[t];
n[y]:=n[y]+[t];
end;

procedure refill(x,y,t:integer);
begin
a[x,y]:=0;
ok[x,y]:=false;
b[c[x,y]]:=b[c[x,y]]-[t];
m[x]:=m[x]-[t];
n[y]:=n[y]-[t];
end;

procedure test(x,y:integer);
var
t:integer;
begin
if over then exit;
if x=0 then
   begin
   print;
   over:=true;
   exit;
   end
else
    if y=0 then
       test(x-1,9)
else
    if ok[x,y] then test(x,y-1)
else
    begin
    for t:=1 to 9 do
        if not((t in m[x])or(t in n[y])or(t in b[c[x,y]])) then
            begin
            fill(x,y,t);
            test(x,y-1);
            refill(x,y,t);
            end;
    end;
end;

begin
readln(testnum);
for k:=1 to testnum do
begin
over:=false;
fillchar(ok,sizeof(ok),false);
for i:=1 to 9 do
    begin
    b[i]:=[];
    m[i]:=[];
    n[i]:=[];
    end;
for i:=1 to 9 do
    begin
    for j:=1 to 9 do
        begin
        read(ch);
        val(ch,t);
        if t<>0 then fill(i,j,t);
        end;
    readln;
    end;
test(9,9);
end;

end.


