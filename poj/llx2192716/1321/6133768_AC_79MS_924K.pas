program p1321;
var
n,k,i,j:longint;
ch:char;
map:array[1..8,1..8] of boolean;
count:longint;

procedure search(i,j,steps,barry:longint);
begin
if (i>n)or(j>n) then exit;

if j<n then search(i,j+1,steps,barry)
    else
        if (j=n)and(i<n) then search(i+1,1,steps,barry);

if  (map[i,j]=true)and((barry shr (n-j))and 1 =0) then
	begin
	inc(steps);
	if steps=k then
		begin
		inc(count);
		exit;
		end;
	search(i+1,1,steps,barry or(1 shl(n-j)));
        dec(steps);
	end;

end;

begin
while not seekeof do
	begin
	count:=0;
	readln(n,k);
        if n=-1 then break;
        for i:=1 to n do
		begin
		for j:=1 to n do
			begin
			read(ch);
			if ch='#' then map[i,j]:=true
			else map[i,j]:=false;
			end;
		readln;
		end;
	search(1,1,0,0);
	writeln(count);
	end;
end.
