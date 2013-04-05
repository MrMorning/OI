program p1190_naked;
var
	ansS,N,M:longint;

procedure search(k:integer;preV,preS,preR,preH:longint);
var
hk,rk,curS,curV:longint;
begin
if k=1 then
	begin
	for rk:=M to trunc(sqrt(N)) do
		begin
		hk:=M;
		while (hk*rk*rk<=N) do
			begin
			search(2,hk*rk*rk,rk*rk+2*rk*hk,rk,hk);
			inc(hk);
			end;
		end;
	exit;
	end;		
if (k>M) then
	begin
	if preV=N then
		if preS<ansS then ansS:=preS;
	exit;
	end;
for rk:=(M-k+1) to (preR-1) do
	for hk:=(M-k+1) to (preH-1) do
		begin
		curV:=preV+rk*rk*hk;
		curS:=preS+2*rk*hk;
		if curV>N then break;
		if curS>ansS then break;
		search(k+1,curV,curS,rk,hk);
		end;

end;
begin
assign(input,'t.in'); reset(input);
assign(output,'t.out'); rewrite(output);
ansS:=maxlongint;
readln(N);
readln(M);
search(1,0,0,0,0);
if ansS=maxlongint then
	ansS:=0;
writeln(ansS);;
close(input); close(output);
end.
