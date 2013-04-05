program p1077_naked;
type
	Tsquare=array[1..3,1..3] of longint;
	Tqele=record
		ele:Tsquare;
		x,y,parent,option:longint;
	end;
const
	MAP:array[1..4] of char =('u','l','d','r');
	o:array[1..4,1..2] of longint = ((-1,0),(0,-1),(1,0),(0,1));
	TARGET:Tsquare = ((1,2,3),(4,5,6),(7,8,9));

var
	i,j,open,closed:longint; 
	u,v,st:Tqele;
	ch:char;
	q:array[1..362880] of Tqele;
	fac:array[1..9] of longint;
	hash:array[1..362880] of longint;

function equal(a,b:Tsquare):boolean;
var
	i,j:longint;
begin
for i:=1 to 3 do
	for j:=1 to 3 do
		if a[i,j]<>b[i,j] then exit(false);
exit(true);
end;

procedure swap(var a,b:longint);
var
	c:longint;
begin
c:=a;
a:=b;
b:=c;
end;

function cantor(x:Tsquare):longint;
var
	i,j,k,t:longint;
	ans:longint;
	a:array[1..9] of longint;
begin
	ans:=0;
	for i:=1 to 3 do
		for j:=1 to 3 do begin
			k:=(i-1)*3+j;
			a[k]:=x[i,j];
		end;
	for i:=1 to 9 do begin
		t:=0;
		for j:=1 to i-1 do
			if a[j]<a[j] then inc(t);
		ans:=ans+(a[i]-1-t)*fac[9-i];
	end;
	exit(ans+1);
end;

procedure mark(x:Tsquare;i:longint);
begin
hash[cantor(x)]:=i;
end;


procedure print(x:Tqele);
begin
if x.parent<>0 then
	begin
	print(q[x.parent]);
	write(MAP[x.option]);
	end;
end;

function find(x:Tsquare):longint;
begin
	exit(hash[cantor(x)]);
end;

begin
assign(input,'t.in'); reset(input);
assign(output,'t.out'); rewrite(output);
fac[1]:=1;
for i:=2 to 9 do
	fac[i]:=fac[i-1]*i;
for i:=1 to 3 do
	for j:=1 to 3 do
		begin
		read(ch);
		while not((ch>'0')and(ch<'9')or(ch='x')) do read(ch);
		if ch='x' then 
			begin
			st.x:=i; st.y:=j;
			st.ele[i,j]:=9
			end
		else
			st.ele[i,j]:=ord(ch)-ord('0');
		end;
open:=0; closed:=0;
inc(closed); 
q[closed]:=st;
mark(st.ele,1);
while open<>closed do
	begin
	inc(open);
	u:=q[open];
	if equal(u.ele,TARGET) then
		begin
		print(u);
		close(input); close(output);
		halt;
		end;
	for i:=1 to 4 do
		if (u.x+o[i,1]>0)and(u.x+o[i,1]<4)and(u.y+o[i,2]>0)and(u.y+o[i,2]<4) then
				begin
				v.parent:=open;
				v.x:=u.x+o[i,1];
				v.y:=u.y+o[i,2];
				v.option:=i;
				v.ele:=u.ele;
				swap(v.ele[v.x,v.y],v.ele[u.x,u.y]);
				if find(v.ele)>0 then continue;
				inc(closed);
				q[closed]:=v;
				mark(v.ele,closed);
				end;
					
	end;
write('unsolvable');
close(input); close(output);
end.	
