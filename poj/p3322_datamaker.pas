program p3322datamaker;
const
	o:array[1..4,1..2] of integer = ((1,0),(-1,0),(0,1),(0,-1));
var
	a:array[1..500,1..500] of char;
	i,j,h,w,XNum,ENum,tNum,X1x,X1y,X2x,X2y,Ox,Oy,tx,ty,t:longint;
procedure main;
begin
fillchar(a,sizeof(a),'.');
h:=random(498)+3;
w:=random(498)+3;
writeln(h,' ',w);
for i:=1 to h do
	begin
	a[i,1]:='#';
	a[i,w]:='#';
	end;
for i:=1 to w do
	begin
	a[1,i]:='#';
	a[h,i]:='#';
	end;
XNum:=random(1)+1;
X1x:=random(h-2)+1;
X1y:=random(w-2)+1;
a[X1x,X1y]:='X';
if XNum=1 then
	begin
	t:=random(4)+1;
	X2x:=X1x+o[t,1];
	X2y:=X1y+o[t,2];
	if (a[X2x,X2y]='.') then
		a[X2x,X2y]:='X';
	end;
Ox:=random(h-2)+1;
Oy:=random(w-2)+1;
if (a[Ox,Oy]='.') then
	a[Ox,Oy]:='O';
ENum:=random((h-1)*(w-1) div 3)+1;
for i:=1 to ENum do
	begin
	tx:=random(h)+1; ty:=random(w)+1;
	if a[tx,ty]='.' then
		a[tx,ty]:='E';
	end;
for i:=1 to h do
	begin
	for j:=1 to w do
		write(a[i,j]);
	writeln;
	end;
end;
begin
randomize;
assign(output,'t.in'); rewrite(output);
for tNum:=1 to 50 do
	main;
writeln(0,' ',0);
end.
