program p1700;
var
a:array[1..1000] of longint;
T,i,j,n:longint;
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
       sort(1,n);
    end;

function search(n:longint):longint;
begin
if (n=1)or(n=2) then exit(a[n])
	else if n=3 then exit(a[1]+a[2]+a[3])
		else
			begin
			if (2*a[2]>a[1]+a[n-1]) then
				exit(2*a[1]+a[n-1]+a[n]+search(n-2))
			else
				exit(2*a[2]+a[1]+a[n]+search(n-2));
			end;
		
end;	

begin
	readln(n);
	for j:=1 to n do
		read(a[j]);
	qsort;
	writeln(search(n));
end.

