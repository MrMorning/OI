program p1191;
var
f:array[0..15,1..9,1..9,1..9,1..9] of longint;
sum:array[0..8,0..8] of longint;
w:array[1..8,1..8] of longint;
n,i,j,k,x1,x2,y1,y2,a,b:longint;

function min(a,b,c:longint):longint;
begin
min:=maxlongint;
if a<min then min:=a;
if b<min then min:=b;
if c<min then min:=c;
end;

function s(x1,y1,x2,y2:longint):longint;
begin
exit(sqr(sum[x2,y2]-sum[x2,y1-1]-sum[x1-1,y2]+sum[x1-1,y1-1]));
end;

begin
readln(n);
for i:=1 to 8 do
	for j:=1 to 8 do
		read(w[i,j]);
for k:=1 to n do
	for x1:=1 to 9 do
		for y1:=1 to 9 do
			for x2:=1 to 9 do
				for y2:=1 to 9 do
					f[k,x1,y1,x2,y2]:=10000000;
for i:=1 to 8 do
	for j:=1 to 8 do
		sum[i,j]:=sum[i,j-1]+sum[i-1,j]-sum[i-1,j-1]+w[i,j];
for x1:=1 to 8 do
        for y1:=1 to 8 do
	        for x2:=1 to 8 do
		        for y2:=1 to 8 do
					f[0,x1,y1,x2,y2]:=s(x1,y1,x2,y2);
for k:=1 to n do
	for x1:=1 to 8 do
		for y1:=1 to 8 do
			for x2:=1 to 8 do
				for y2:=1 to 8 do
					begin
					for a:=x1 to x2 do
						f[k,x1,y1,x2,y2]:=min
						(f[k,x1,y1,x2,y2],
							f[k-1,x1,y1,a,y2]+s(a+1,y1,x2,y2),
							f[k-1,a+1,y1,x2,y2]+s(x1,y1,a,y2));
					for b:=y1 to y2 do
						f[k,x1,y1,x2,y2]:=min
						(f[k,x1,y1,x2,y2],
							f[k-1,x1,y1,x2,b]+s(x1,b+1,x2,y2),
							f[k-1,x1,b+1,x2,y2]+s(x1,y1,x2,b));
                                        if f[k,x1,y1,x2,y2]<>10000000 then
                                        end;
writeln(sqrt(abs(f[n-1,1,1,8,8]/n-sqr(sum[8,8]/n))):0:3);
end.
