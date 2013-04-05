program p1141;
var
s:ansistring;
f,g:array[1..100,1..100] of integer;
ch:array[1..100,1..100] of char;
i,j:integer;

function convert(ch:char):char;
begin
case ch of
	')': exit('(');
	']': exit('[');
	else
	exit(ch);
	end;
end;

function opp(ch:char):char;
begin
case ch of
	'(': exit(')');
	'[': exit(']');
	else
	exit(ch);
    end;
end;

function DP(i,j:integer):integer;
var
k:integer;
begin
if i=j then
	begin
	f[i,j]:=1;
	g[i,j]:=0;
	ch[i,j]:=convert(s[i]);
	exit(1);
	end;
if i>j then exit(0);
if f[i,j]<>9999 then
	exit(f[i,j]);
if ((s[i]='(') and (s[j]=')'))or((s[i]='[') and (s[j]=']')) then
	if f[i,j]>DP(i+1,j-1) then
		begin
		f[i,j]:=DP(i+1,j-1);
		g[i,j]:=-1;
		ch[i,j]:=convert(s[i]);
		end;
if (s[i]='(')or(s[i]='[') then
	if f[i,j]>(DP(i+1,j)+1) then
	begin
	f[i,j]:=DP(i+1,j)+1;
	g[i,j]:=-2;
	ch[i,j]:=s[i];
	end;
if (s[j]=')')or(s[j]=']') then
	if f[i,j]>(DP(i,j-1)+1) then
	begin
	f[i,j]:=DP(i,j-1)+1;
	g[i,j]:=-3;
	ch[i,j]:=convert(s[j]);
	end;
for k:=i to j do
	begin
	if (DP(i,k)+DP(k+1,j))<f[i,j] then
		begin
		f[i,j]:=DP(i,k)+DP(k+1,j);
		g[i,j]:=k;
		ch[i,j]:='+';
		end;
	end;
exit(f[i,j]);
end;

procedure print(i,j:integer);
begin
if i>j then
	exit;
case g[i,j] of
	0:	write(ch[i,j],opp(ch[i,j]));
	-1:	begin
		write(ch[i,j]);
		print(i+1,j-1);
		write(opp(ch[i,j]));
		end;
	-2: begin
		write(ch[i,j]);
		print(i+1,j);
		write(opp(ch[i,j]));
		end;
	-3: begin
		write(ch[i,j]);
		print(i,j-1);
		write(opp(ch[i,j]));
		end;
	else
		begin
		print(i,g[i,j]);
		print(g[i,j]+1,j);
		end;
	end;
end;

begin
readln(s);
for i:=1 to 100 do
        for j:=1 to 100 do
                f[i,j]:=9999;
DP(1,length(s));
print(1,length(s));
writeln;
end.
