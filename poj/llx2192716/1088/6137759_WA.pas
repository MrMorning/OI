program p1088;
const
offset:array[1..4,1..2] of longint = ((1,0),(-1,0),(0,1),(0,-1));
var
f,a:array[0..101,0..101] of longint;
i,j,ti,tj,maxHeight,R,C:longint;
ans:longint;

function search(i,j:longint):longint;
var
s:integer;
begin
if (i<1)or(i>R)or(j<1)or(j>C) then exit(-999999);
if f[i,j]<>-1 then exit(f[i,j]);
for s:=1 to 4 do
	if (a[i+offset[s,1],j+offset[s,2]]>a[i,j])and(search(i+offset[s,1],j+offset[s,2])+1>f[i,j]) then
		f[i,j]:=search(i+offset[s,1],j+offset[s,2])+1;
exit(f[i,j]);
end;

begin
readln(R,C);
maxHeight:=0;
for i:=1 to R do
	for j:=1 to C do
		begin
		read(a[i,j]);
		if a[i,j]>maxHeight then
			begin
			maxHeight:=a[i,j];
			ti:=i;
			tj:=j;
			end;
		f[i,j]:=-1;
		end;
f[ti,tj]:=0;
ans:=0;
for i:=1 to R do
	for j:=1 to C do
		begin
		if f[i,j]=-1 then
                        f[i,j]:=search(i,j);
		if f[i,j]>ans then
			ans:=f[i,j];
		end;
writeln(ans+1);
end.
