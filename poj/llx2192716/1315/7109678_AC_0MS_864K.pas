program pku1315;
var
maxn,k,t,i,j:integer;
ch:char;
a:array[1..4,1..4] of integer;
b:array[1..5] of boolean;

procedure search(i,j,n:integer);
begin
if i>k then
	begin
	if n>maxn then maxn:=n;
	exit;
	end
else
if j>k then
        search(i+1,1,n)
else
begin
fillchar(b,sizeof(b),true);
t:=i;
while (t>1)and (a[t,j]=0) do dec(t);
if a[t,j]=2 then b[1]:=false;
t:=i;
while (t<k)and (a[t,j]=0) do inc(t);
if a[t,j]=2 then b[2]:=false;

t:=j;
while (t>1)and (a[i,t]=0) do dec(t);
if a[i,t]=2 then b[3]:=false;
t:=j;
while (t<k)and (a[i,t]=0) do inc(t);
if a[i,t]=2 then b[4]:=false;

for t:=1 to 4 do
	b[5]:=b[5]and b[t];

if (b[5])and(a[i,j]=0) then
	begin
	a[i,j]:=2;
	search(i,j+1,n+1);
	a[i,j]:=0;
	end;
search(i,j+1,n);
end;
end;

procedure main;
begin
search(1,1,0);
writeln(maxn);
end;

begin
while true do
	begin
	readln(k);
	if k=0 then
		begin
		halt;
		end
	else
		begin
                maxn:=0;
		fillchar(a,sizeof(a),0);
		for i:=1 to k do
			begin
			for j:=1 to k do
				begin
				read(ch);
				if ch='X' then
					a[i,j]:=1;
				end;
			readln;
			end;
		main;
		end;
	end;
end.
