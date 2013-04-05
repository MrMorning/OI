type
	tnode=array[1..4,1..4] of boolean;
	node=record
		l,r,ls,rs:longint;
		e:array[1..2] of boolean;
		f:tnode;
	end;
var
	total,r1,c1,r2,c2,m:longint;
	left,right,map:tnode;
	t:array[0..200001] of node;
	flag:boolean;
procedure init;
begin
	assign(input, 't.in');
	reset(input);
end;

procedure terminate;
begin
	close(input);
	close(output);
end;
procedure initialize(var a:tnode);
begin
	fillchar(a,sizeof(a),0);
	a[1,1]:=true;a[2,2]:=true;a[3,3]:=true;a[4,4]:=true;
end;

procedure buildtree(l,r:longint);
var
	mid,i:longint;
begin
	inc(total);
	t[total].l:=l;t[total].r:=r;
	with t[total] do
begin
	f[1,1]:=true;f[2,2]:=true;f[3,3]:=true;f[4,4]:=true;
end;
if l=r then
begin
	t[total].f[1,3]:=true;
	t[total].f[3,1]:=true;
	t[total].f[2,4]:=true;
	t[total].f[4,2]:=true;
	t[total].e[1]:=true;
	t[total].e[2]:=true;
	exit;
end;
mid:=(l+r) shr 1;i:=total;
t[i].ls:=total+1;buildtree(l,mid);
t[i].rs:=total+1;buildtree(mid+1,r);
end;

procedure readdata;
begin
	fillchar(t,sizeof(t),0);
	readln(m);
	total:=0;
	buildtree(1,m);
end;

procedure update(k:longint;var map,left,right:tnode);
var
	i,j,x:longint;
begin
	map[1,2]:=left[1,2];map[2,1]:=map[1,2];
	map[3,4]:=right[3,4];map[4,3]:=map[3,4];

	for x:=1 to 2 do
		if t[k].e[x] then
			for i:=1 to 2 do
				for j:=3 to 4 do
					if (i<>x+2) and (x<>j) then
						if left[i,x+2] and right[x,j] then
						begin
							map[i,j]:=true;
							map[j,i]:=true;
						end;
						if (not map[1,2]) and (right[1,2] and t[k].e[1] and t[k].e[2] and left[1,3] and left[4,2]) then
						begin
							map[1,2]:=true;map[2,1]:=true;
						end;
						if (not map[3,4]) and (left[3,4] and t[k].e[1] and t[k].e[2] and right[3,1] and right[2,4]) then
						begin
							map[3,4]:=true;map[4,3]:=true;
						end;
					end;//根据左区间和右区间确定整个大区间……

procedure insert(k:longint);
var
	i,j,x,mid:longint;

begin
	if (c1=c2) and (t[k].l=t[k].r) then
	begin
		for i:=1 to 4 do
			for j:=1 to 4 do t[k].f[i,j]:=flag;
				t[k].f[1,3]:=true;t[k].f[3,1]:=true;
				t[k].f[2,4]:=true;t[k].f[4,2]:=true;
				exit;
			end;

			mid:=(t[k].l+t[k].r) shr 1;
			if c1>mid then insert(t[k].rs)
		else if c2<=mid then insert(t[k].ls)
	else begin
		if r1=1 then t[k].e[1]:=flag else t[k].e[2]:=flag;
	end;
	initialize(t[k].f);
	update(k,t[k].f,t[t[k].ls].f,t[t[k].rs].f);
end;

procedure swap(var a,b:longint);
var
	t:longint;
begin
	t:=a;a:=b;b:=t;
end;

procedure ask(var map:tnode;k,ll,rr:longint);
var
	i,j,x,mid:longint;
	left,right:tnode;
begin
	if (t[k].l=ll) and (t[k].r=rr) then
	begin
		map:=t[k].f;
		exit;
	end;
	mid:=(t[k].l+t[k].r) shr 1;
	if rr<=mid then
	begin
		ask(map,t[k].ls,ll,rr);
		exit;
	end
else if ll>mid then
begin
	ask(map,t[k].rs,ll,rr);
	exit;
end;

initialize(left);initialize(right);
ask(left,t[k].ls,ll,mid);
ask(right,t[k].rs,mid+1,rr);
update(k,map,left,right);
end;

function find:boolean;
var
	i,j,k:longint;
begin
	if c1>c2 then begin swap(c1,c2); swap(r1,r2); end;
	initialize(map);
	initialize(left);
	initialize(right);
	ask(left,1,1,c1);
	ask(map,1,c1,c2);
	ask(right,1,c2,m);

	if not map[1,2] then
	begin
		map[1,2]:=left[3,4];map[2,1]:=left[3,4];
	end;
	if not map[3,4] then
	begin
		map[3,4]:=right[1,2];map[4,3]:=right[1,2];
	end;

	for k:=1 to 4 do
		for i:=1 to 4 do
			for j:=1 to 4 do
				if (i<>j) and (j<>k) and (k<>i) then
					if map[i,k] and map[k,j] then map[i,j]:=true;
					if r1=1 then i:=1 else i:=2;
					if r2=1 then j:=3 else j:=4;
					exit(map[i,j]);
				end;

procedure main;
var
	f:boolean;
	i:longint;
	a:char;
begin
	while true do
begin
	read(a);
	case a of
		'O':begin
		for i:=1 to 4 do read(a);
			readln(r1,c1,r2,c2);
			if c1>c2 then swap(c1,c2);
			flag:=true;
			insert(1);
		end;
		'C':begin
		for i:=1 to 5 do read(a);
			readln(r1,c1,r2,c2);
			if c1>c2 then swap(c1,c2);
			flag:=false;
			insert(1);
		end;
		'A':begin
		for i:=1 to 3 do read(a);
			readln(r1,c1,r2,c2);
			f:=find;
			if f=true then writeln('Y')
		else writeln('N');
		end;
		'E':break;
	end;
end;
end;

begin
	init;
	readdata;
	main;
	terminate;
end.

