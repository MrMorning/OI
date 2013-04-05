type
	Request=record
		fr,en,id:longint;
	end;
	SGnode=record
		left,right,mid:longint;
		tag,mtag,nowtag,maxtag:longint;
	end;
var
	Rq:array[0..100010] of Request;
	hash:array[-100010..100010] of longint;
	a:array[0..262144] of SGnode;
	d,ans:array[0..100010] of longint;
	n,TotalQueries,i,now:longint;

function max2(x,y:longint):longint inline;
begin if x>y then exit(x) else exit(y);end;

procedure Spread(i:longint) inline;
begin with a[i] do
begin if left=right then exit;

	if a[i*2].tag+mtag>a[i*2].mtag then a[i*2].mtag:=a[i*2].tag+mtag;
	inc(a[i*2].tag,tag);
	if a[i*2].nowtag+mtag>a[i*2].maxtag then a[i*2].maxtag:=a[i*2].nowtag+mtag;
	inc(a[i*2].nowtag,tag);

	if a[i*2+1].tag+mtag>a[i*2+1].mtag then a[i*2+1].mtag:=a[i*2+1].tag+mtag;
	inc(a[i*2+1].tag,tag);
	if a[i*2+1].nowtag+mtag>a[i*2+1].maxtag then a[i*2+1].maxtag:=a[i*2+1].nowtag+mtag;
	inc(a[i*2+1].nowtag,tag);
	tag:=0;
	mtag:=0;
end;
end;

procedure Serere(i,bg,ed,dt:longint);
begin with a[i] do
begin if (bg<=left)and(right<=ed) then
begin if left<>right then
begin inc(tag,dt);
	if tag>mtag then mtag:=tag;
end;
if nowtag+dt>maxtag then maxtag:=nowtag+dt;
inc(nowtag,dt);
exit;
end;
Spread(i);
if bg<=mid then Serere(i*2,bg,ed,dt);
if ed>mid then Serere(i*2+1,bg,ed,dt);
nowtag:=max2(a[i*2].nowtag,a[i*2+1].nowtag);
maxtag:=max2(a[i*2].maxtag,a[i*2+1].maxtag);
end;
end;

procedure Build(i,bg,ed:longint);
begin with a[i] do
begin left:=bg;
	right:=ed;
	mid:=(bg+ed) shr 1;
	tag:=0;
	mtag:=0;
	nowtag:=-maxlongint;
	maxtag:=-maxlongint;
	if left=right then exit;
	Build(i*2,bg,mid);
	Build(i*2+1,mid+1,ed);
end;
  end;

function Query(i,bg,ed:longint):longint;
var x1,x2:longint;
begin with a[i] do
begin if (bg<=left)and(right<=ed) then exit(maxtag);
	Spread(i);
	if ed<=mid then exit(Query(i*2,bg,ed));
	if bg>mid then exit(Query(i*2+1,bg,ed));
	x1:=Query(i*2,bg,ed);
	x2:=Query(i*2+1,bg,ed);
	exit(max2(x1,x2));
end;
  end;

procedure Qsort(l,r:longint);
var i,j,x:longint;
	y:Request;
begin i:=l;
	j:=r;
	x:=Rq[(l+r) shr 1].en;
	repeat
		while (Rq[i].en<x) do inc(i);
		while x<Rq[j].en do dec(j);
		if not(i>j) then
		begin y:=Rq[i];
			Rq[i]:=Rq[j];
			Rq[j]:=y;
			inc(i);
			dec(j);
		end;
	until i>j;
	if l<j then Qsort(l,j);
	if i<r then Qsort(i,r);
end;

begin
	assign(input,'t.in'); reset(input);
	fillchar(hash,sizeof(hash),0);
	readln(n);
	for i:=1 to n do read(d[i]);
		readln(TotalQueries);
		for i:=1 to TotalQueries do
		begin readln(Rq[i].fr,Rq[i].en);
			Rq[i].id:=i;
		end;

		Qsort(1,TotalQueries);

		Build(1,1,n);

		now:=1;
		for i:=1 to n do
		begin Serere(1,i,i,maxlongint);
			Serere(1,hash[d[i]]+1,i,d[i]);
			hash[d[i]]:=i;
			while (now<=TotalQueries) and (Rq[now].en=i) do
begin ans[Rq[now].id]:=max2(Query(1,Rq[now].fr,Rq[now].en),0);
	inc(now);
end;
if now>TotalQueries then break;
end;
for i:=1 to TotalQueries do writeln(ans[i]);
end.

