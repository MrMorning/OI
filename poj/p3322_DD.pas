program p3322;
const
	OPPOSITE:array[1..4] of integer = (2,1,4,3);
	offset:array[1..4,1..2] of integer = ((-1,0),(1,0),(0,-1),(0,1));
	delta:array[1..4,1..4,1..2] of integer =
	(((-2,0),(1,0),(0,-1),(0,1)),
	((-1,0),(2,0),(0,-1),(0,1)),
	((-1,0),(1,0),(0,-2),(0,1)),
	((-1,0),(1,0),(0,-1),(0,2)));
	MAXDEPFRONT=20;
type
	Tqele=record
		dir,x,y,dep:integer;
	end;
var
	r,c:integer;
	map:array[1..500,1..500] of integer;
	tarx,tary:integer;
	closed_F,closed_B,open_F,open_B:longint;
	q_F,q_B:array[1..2000000] of Tqele;
	hash_F,hash_B:array[1..500,1..500,0..4] of longint;

function illegal(ele:Tqele):boolean;
begin
with ele do
if dir=0 then
	exit(map[x,y]<>2)
else
	exit((map[x,y]=0)or(map[x+offset[dir,1],y+offset[dir,2]]=0));
end;

procedure mark_F(i:longint);
begin
with q_F[i] do
	if dir=0 then 
		hash_F[x,y,0]:=i
	else
		begin
		hash_F[x,y,dir]:=i;
		hash_F[x+offset[dir,1],y+offset[dir,2],OPPOSITE[dir]]:=i;
		end;
end;

procedure mark_B(i:integer);
begin
with q_B[i] do
	if dir=0 then 
		hash_B[x,y,0]:=i
	else
		begin
		hash_B[x,y,dir]:=i;
		hash_B[x+offset[dir,1],y+offset[dir,2],OPPOSITE[dir]]:=i;
		end;
end;

function find_F(x:Tqele):longint;
begin
exit(hash_F[x.x,x.y,x.dir]);
end;

function find_B(x:Tqele):longint;
begin
exit(hash_B[x.x,x.y,x.dir]);
end;

procedure enqueue_F(x:Tqele);
begin
closed_F:=closed_F mod 2000000 +1;
q_F[closed_F]:=x;
mark_F(closed_F);
end;

procedure enqueue_B(x:Tqele);
begin
closed_B:=closed_B mod 2000000 +1;
q_B[closed_B]:=x;
mark_B(closed_B);
end;

function dequeue_F:Tqele;
begin
open_F:=open_F mod 2000000 +1;
exit(q_F[open_F]);
end;

function dequeue_B:Tqele;
begin
open_B:=open_B mod 2000000 +1;
exit(q_B[open_B]);
end;

procedure init;
var
	i,j:integer;
	a:array[1..500,1..500] of char;
	findX:boolean;
begin
fillchar(hash_F,sizeof(hash_F),0);
fillchar(hash_B,sizeof(hash_B),0);
fillchar(q_F,sizeof(q_F),0);
fillchar(q_B,sizeof(q_B),0);
readln(r,c);
if r=0 then halt;
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
					q_F[1].x:=i; q_F[1].y:=j;
					if a[i+1,j]='X' then
						q_F[1].dir:=2;
					if a[i,j+1]='X' then
						q_F[1].dir:=4;
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

procedure main;
var
	i:integer;
	u,v:Tqele;
begin
closed_F:=1; open_F:=0;
mark_F(1);
q_F[1].dep:=0;
while closed_F<>open_F do
	begin
	u:=dequeue_F;
	if u.dep>MAXDEPFRONT then break;
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
			v.dep:=u.dep+1;
			if illegal(v) then continue;
			if find_F(v)>0 then continue;
			enqueue_F(v);
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
			if (not illegal(v))and(find_F(v)=0) then
				enqueue_F(v);
			end;	
		end;
	end;



closed_B:=1; open_B:=0;
q_B[1].x:=tarx; q_B[1].y:=tary;
mark_B(1);
q_B[1].dep:=0;
while closed_B<>open_B do
	begin
	u:=dequeue_B;
	if find_F(u)>0 then
		begin
		writeln(u.dep+q_F[find_F(u)].dep);
		exit;
		end;
	if u.dir=0 then
		begin
		for i:=1 to 4 do
			begin
			v.dir:=i;
			v.x:=u.x+offset[i,1];
			v.y:=u.y+offset[i,2];
			v.dep:=u.dep+1;
			if illegal(v) and (find_B(v)>0) then continue;
			enqueue_B(v);
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
			if (not illegal(v))and(find_B(v)=0) then
				enqueue_B(v);
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
	main;
	end;
close(input); close(output);
end.
