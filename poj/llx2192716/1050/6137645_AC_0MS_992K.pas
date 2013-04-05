program p1050;
type
T1DArray=array[1..100] of longint;
T2DArray=array[1..100,1..100] of longint;
var
i,j,N:longint;
a:T2DArray;

function DP_1D(a:T1DArray):longint;
var
sum,max:longint;
begin
max:=-maxlongint;
sum:=0;
for i:=1 to N do
	begin
	if sum>0 then
		sum:=sum+a[i]
	else
		sum:=a[i];
	if sum>max then max:=sum;
	end;
exit(max);
end;

function DP_2D(a:T2DArray):longint;
var
a1D:T1DArray;
max,sum:longint;
i,j,k:longint;
begin
max:=-maxlongint;
for i:=1 to N do
        begin
        fillchar(a1D,sizeof(a1D),0);
	for j:=i to N do
		begin
		for k:=1 to N do
			a1D[k]:=a1D[k]+a[j,k];
		sum:=DP_1D(a1D);
		if sum>max then max:=sum;
		end;
        end;
exit(max);
end;

begin
readln(N);
for i:=1 to N do
	for j:=1 to N do
		read(a[i,j]);
writeln(DP_2D(a));

end.
