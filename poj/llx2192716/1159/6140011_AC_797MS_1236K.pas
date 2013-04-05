program p1159;
var
len:integer;
s:ansistring;
f,pref:array[0..5000] of integer;
i,j:integer;

function min(a,b:integer):integer;
begin
if a<b then exit(a)
else exit(b);
end;

begin
readln(len);
readln(s);
for i:=1 to len do
        pref[i]:=0;
for j:=2 to len do
        begin
        f[j]:=0;
        for i:=j-1 downto 1 do
                begin
		if s[i]=s[j] then
			f[i]:=pref[i+1]
		else
			f[i]:=min(f[i+1],pref[i])+1;
                end;
        pref:=f;
        end;
writeln(f[1]);
end.
