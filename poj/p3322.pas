program p3322;
const
	OPPOSITE:array[1..4] of integer = (2,1,4,3);
	offset:array[1..4,1..2] of integer = ((-1,0),(1,0),(0,-1),(0,1));
	delta:array[1..4,1..4,1..2] of integer =
	(((-2,0),(1,0),(0,-1),(0,1)),
	((-1,0),(2,0),(0,-1),(0,1)),
	((-1,0),(1,0),(0,-2),(0,1)),
	((-1,0),(1,0),(0,-1),(0,2)));
type
	Tqele=record
		dir,x,y,dep:integer;
	end;
var
	r,c:integer;
	map:array[1..500,1..500] of integer;
	tarx,tary:integer;
	closed,open:longint;
	q:array[1..2000000] of Tqele;
	hash:array[1..500,1..500,0..4] of boolean;

function illegal(ele:Tqele):boolean;
begin
with ele do
if dir=0 then
	exit(map[x,y]<>2)
else
	exit((map[x,y]=0)or(map[x+offset[dir,1],y+offset[dir,2]]=0));
end;

procedure mark(x:Tqele);
begin
with x do
	if dir=0 then 
		hash[x,y,0]:=true
	else
		begin
		hash[x,y,dir]:=true;
		hash[x+offset[dir,1],y+offset[dir,2],OPPOSITE[dir]]:=true;
		end;
end;

function find(x:Tqele):boolean;
begin
with x do
	exit(hash[x,y,dir]);
end;

procedure enqueue(x:Tqele);
begin
closed:=closed mod 2000000 +1;
q[closed]:=x;
mark(q[closed]);
end;
	
function dequeue:Tqele;
begin
open:=open mod 2000000 +1;
exit(q[open]);
end;

procedure init;
var
	i,j:integer;
	a:array[1..500,1..500] of char;
	findX:boolean;
begin
fillchar(hash,sizeof(hash),false);
fillchar(q,sizeof(q),0);
readln(r,c);
if (r=0)and(c=0) then halt;
for i:=1 to r do
	begin
	for j:=1 to c do
		read(a[i,j]);
	readln;
	end;
findX:=false;
for i:=1 to r do
	for j:=1 to c do
		case a[i,j] of
			'X':	begin
				if not findX then 
					begin
					findX:=true;
					q[1].x:=i; q[1].y:=j;
					if a[i+1,j]='X' then
						q[1].dir:=2;
					if a[i,j+1]='X' then
						q[1].dir:=4;
					end;
				map[i,j]:=2;
				end;
			'O':	begin
				tarx:=i;
				tary:=j;
				map[i,j]:=2;
				end;
			'#':	map[i,j]:=0;
			'E':	map[i,j]:=1;
			'.':	map[i,j]:=2;
		end;
			
end;

procedure doit;
var
	i:integer;
	u,v:Tqele;
begin
closed:=1; open:=0;
mark(q[1]);
q[1].dep:=0;
while closed<>open do
	begin
	u:=dequeue;
	if (u.dir=0)and(u.x=tarx)and(u.y=tary) then
		begin
		writeln(u.dep);
		exit;
		end;
	if u.dir=0 then
		begin
		for i:=1 to 4 do
			begin
			v.dir:=i;
			v.x:=u.x+offset[i,1];
			v.y:=u.y+offset[i,2];
			if find(v) then continue;
			v.dep:=u.dep+1;
			if illegal(v) then continue;
			enqueue(v);
			end;
		end
	else
		begin
		v.dep:=u.dep+1;	
   		for i:=1 to 4 do
			begin
			if (u.dir=i)or(u.dir=OPPOSITE[i]) then
				v.dir:=0
			else
				v.dir:=u.dir;
			v.x:=u.x+delta[u.dir,i,1];
			v.y:=u.y+delta[u.dir,i,2];
			if (not illegal(v))and(not find(v)) then
				enqueue(v);
			end;	
		end;
	end;
writeln('Impossible');
end;


begin
assign(input,'t.in'); reset(input);
assign(output,'t.out'); rewrite(output);
while true do
	begin
	init;
	doit;
	end;
close(input); close(output);
end.
