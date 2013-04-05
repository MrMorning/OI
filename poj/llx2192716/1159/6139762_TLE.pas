program p1159;
var
len:integer;
s:ansistring;
f:array[1..5000,1..5000] of integer;
i,j:integer;

function min(a,b:integer):integer;
begin
if a<b then exit(a)
else exit(b);
end;

function dp(i,j:integer):integer;
begin
if i>j then
	exit(0);
if f[i,j]<>8888 then
	exit(f[i,j]);
if s[i]=s[j] then
	f[i,j]:=min(f[i,j],dp(i+1,j-1));
if s[i]<>s[j] then
	f[i,j]:=min(dp(i+1,j),dp(i,j-1))+1;
exit(f[i,j]);
end;

begin
readln(len);
for i:=1 to len do
	for j:=i to len do
		f[i,j]:=8888;
readln(s);
writeln(dp(1,len));
end.
