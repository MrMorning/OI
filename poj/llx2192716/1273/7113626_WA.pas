program EdmondKarp;
const
maxn=200;
var
cap,flow:array[1..200,1..200] of longint;
a:array[1..200] of longint;
p,q:array[1..200] of integer;
vis:array[1..200] of boolean;
u,v,rear,front,i:integer;
maxf,N_edge,N_point,x,y,z:longint;

function min(a,b:longint):longint;
begin
if a>b then exit(b)
else exit(a);
end;

begin
fillchar(flow,sizeof(flow),0);
maxf:=0;
readln(N_edge,N_point);
for i:=1 to N_edge do
	begin
	readln(x,y,z);
	cap[x,y]:=z;
	end;

while true do
	begin
	fillchar(q,sizeof(q),0);
	front:=0; rear:=0;
	fillchar(vis,sizeof(vis),false);
	fillchar(a,sizeof(a),0);
	a[1]:=maxlongint;
	inc(rear); q[rear]:=1;
	vis[1]:=true;
	u:=1;
	while front<>rear do
		begin
		front:=front mod N_point +1; u:=q[front];
		for v:=1 to N_point do
			if (not vis[v])and(cap[u,v]>flow[u,v]) then
			begin
			vis[v]:=true;
			p[v]:=u; rear:=rear mod N_point +1; q[rear]:=v;
			a[v]:=min(a[u],cap[u,v]-flow[u,v]);
			end;
		end;
	if a[N_point]=0 then break;
	u:=N_point;
	while u<>1 do
		begin
		inc(flow[p[u],u],a[N_point]);
	        dec(flow[u,p[u]],a[N_point]);
		u:=p[u];
		end;
	inc(maxf,a[N_point]);
	end;

writeln(maxf);
end.
