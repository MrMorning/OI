program p1160;
var
N,P,i,j,k,mid:longint;
a:array[1..300] of longint;
cost:array[1..300,1..300] of longint;
f:array[1..300,1..30] of longint;

procedure qsort;

    procedure sort(l,r: longint);
      var
         i,j,x,y: longint;
      begin
         i:=l;
         j:=r;
         x:=a[(l+r) div 2];
         repeat
           while a[i]<x do
            inc(i);
           while x<a[j] do
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
       sort(1,N);
    end;

function min(a,b:longint):longint;
begin
if a<b then
	exit(a)
else exit(b);
end;	

begin
readln(N,P);
for i:=1 to N do
	read(a[i]);
qsort;
for i:=1 to N do
	cost[i,i]:=0;
for i:=1 to N do
	for j:=i+1 to N do
		begin
		mid:=(i+j) div 2;
		if mid=(i+j-1) div 2 then
			cost[i,j]:=cost[i,j-1]+(a[j]-a[mid])
		else
			cost[i,j]:=cost[i,j-1]+(mid-i)*(a[mid]-a[mid-1])-(j-mid)*(a[mid]-a[mid-1])+a[j]-a[mid];
		end;
for i:=1 to 300 do
	for j:=1 to 30 do
		f[i,j]:=8888888;
for i:=1 to N do
	f[i,1]:=cost[1,i];
for i:=1 to N do
	for j:=2 to P do
		for k:=1 to i-1 do
			f[i,j]:=Min(f[i,j],f[k,j-1]+cost[k+1,i]);
writeln(f[N,P]);
end.
