program p2411;
var
f:array[0..11,0..2047] of int64;
ok:array[0..2047,0..2047] of boolean;
i,j,k,s,m,n:longint;

procedure test(step,now:integer);
begin
if step=m+1 then
	begin
	ok[s,now]:=true;
	exit;
	end;
if (s shr (m-step) and 1)=1 then test(step+1,now)
else
	begin
	if (step<=m-1)and(((s shr (m-step-1)) and 1)=0) then test(step+2,now);
	test(step+1,now or (1 shl (m-step)));
	end;

end;

begin
while not eof do
	begin
	readln(n,m);
	if n+m=0 then break;
	if odd(n)and(odd(m)) then
		begin
		writeln(0);
		continue;
		end;
	fillchar(f,sizeof(f),0);
	fillchar(ok,sizeof(ok),false);
	for s:=0 to (1 shl m -1) do
		test(1,0);
	f[0,0]:=1;
	for i:=1 to n do
		for j:=0 to (1 shl m -1) do
			for k:=0 to (1 shl m -1) do
				if ok[j,k] then inc(f[i,k],f[i-1,j]);
	writeln(f[n,0]);
	end;
end.
