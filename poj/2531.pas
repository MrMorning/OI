program poj2531;
var
used:array[1..20] of boolean;
tot,ans,i,j,N:longint;
w:array[1..20,1..20] of longint;
procedure init;
begin
readln(N);
for i:=1 to N do
	for j:=1 to N do
		read(w[i,j]);
ans:=0;
fillchar(used,sizeof(used),0);
end;

procedure search(k:integer);
begin
if k>N then
	begin
	tot:=0;
	for i:=1 to n do
		if used[i] then
		for j:=1 to n do
			if not used[j] then
				inc(tot,w[i,j]);
	if tot>ans then ans:=tot;
	exit;
	end;
search(k+1);
used[k]:=true;
search(k+1);
used[k]:=false;
end;

begin
assign(input,'t.in'); reset(input);
assign(output,'t.out'); rewrite(output);
init;
used[1]:=true;
search(2);
writeln(ans);
close(input); close(output);
end.
