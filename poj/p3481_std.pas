program pku3481;

type node=record l,r,key,code,prio:longint; end;
	var i,root,cnt,p1,p2,p3:longint;
		t:array[1..20000000] of node;

procedure rot_l(var x:longint);
var y:longint;
begin
	y:=t[x].r;
	t[x].r:=t[y].l;
	t[y].l:=x;
	x:=y;
end;

procedure rot_r(var x:longint);
var y:longint;
begin
	y:=t[x].l;
	t[x].l:=t[y].r;
	t[y].r:=x;
	x:=y;
end;

procedure insert(var i:longint; tkey, tcode:longint);
var lt,rt:longint;
begin
	if(i=-1)then
	begin
		inc(cnt); i:=cnt;
		t[i].l:=-1; t[i].r:=-1; t[i].key:=tkey; t[i].code:=tcode;
		t[i].prio:=random(maxlongint-100*100*10);
		exit;
	end;
	if(t[i].key=tkey)then exit;
	lt:=t[i].l; rt:=t[i].r;
	if(tkey>t[i].key)then
	begin
		insert(t[i].r,tkey,tcode);
		if(t[rt].prio > t[i].prio)then rot_l(i);
	end;
	if(tkey<t[i].key)then
	begin
		insert(t[i].l,tkey,tcode);
		if(t[lt].prio > t[i].prio)then rot_r(i);
	end;
end;

function findmax(var i:longint):longint;
begin
	if(t[i].r <> -1)then exit(findmax(t[i].r));
	findmax:=t[i].code;
	if(t[i].l <> -1)then i:=t[i].l else i:=-1;
end;

function findmin(var i:longint):longint;
begin
	if(t[i].l <> -1)then exit(findmin(t[i].l));
	findmin:=t[i].code;
	if(t[i].r <> -1)then i:=t[i].r else i:=-1;
end;

begin
	randomize;
	root:=-1;
	cnt:=0;

	while(true)do
begin
	assign(input,'t.in'); reset(input);
	read(p1);
	if(p1=0)then break;
	if(p1=1)then
	begin
		read(p2,p3);
		insert(root,p3,p2);
	end  //end for p1=1
else
begin
	if(root=-1)then begin writeln(0); continue; end;
	if(p1=2)then writeln(findmax(root));
	if(p1=3)then writeln(findmin(root));
end;//end for p1=2/3
end;
end.
