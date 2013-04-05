program p1190;
const 
	MINV:array[1..13] of integer =
	(1,9,36,100,225,441,784,1296,2025,3025,4356,6084,8281);
	MINS:array[1..13] of integer =
	(2,10,28,60,110,182,280,408,570,770,1012,1300,1638);
var
	ansS,N,M:longint;

procedure search(k:integer;preV,preS,preR,preH:longint);
var
hk,rk,curS,curV:longint;
begin

if k=1 then
	begin
	for rk:=M to trunc(sqrt(N-MINV[M-1])) do
		begin
		hk:=M;
		while (hk*rk*rk<=(N-MINV[M-1])) do
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
if MINV[M-k+1]>(N-preV) then exit; 
if MINS[M-k+1]>(ansS-preS) then exit;
if (preS+2*(N-preV)/preR)>=ansS then exit;
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
if (M>13)or(N<MINV[M]) then ansS:=0
else
	begin
	search(1,0,0,0,0);
	if ansS=maxlongint then
		ansS:=0;
	end;
writeln(ansS);
close(input); close(output);
end.
