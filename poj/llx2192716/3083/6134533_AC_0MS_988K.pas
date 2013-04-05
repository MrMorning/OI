program p3083;
const
offset:array[1..4,1..2] of longint = ((0,1),(-1,0),(0,-1),(1,0));
opposite:array[1..4] of longint = (3,4,1,2);
var
N,k,i,j,height,width:longint;
maze:array[0..40,0..40] of boolean;
ch:char;
startX,startY,endX,endY,nextX,nextY,startFace,u:longint;
finish:boolean;

function turn(indication,face:longint):longint;
begin
if indication=1 then
	exit(face mod 4 +1)
else
	if face=1 then exit(4)
	 else exit(face-1);
end;

procedure DFS(x,y,preface,steps,indication:longint);
begin
if finish then exit;
if (x=endX)and(y=endY) then
	begin
	write(steps,' ');
	finish:=true;
	exit;
	end;
u:=turn(indication,preface);
while not maze[x+offset[u,1],y+offset[u,2]] do
	u:=turn(3-indication,u);
DFS(x+offset[u,1],y+offset[u,2],u,steps+1,indication)
end;

procedure BFS;
type
TSquare=record
	x,y,dist:longint;
	end;
var
Q:array[1..1000] of TSquare;
head,tail:longint;
visited:array[1..60,1..60] of boolean;
u,v:TSquare;
begin
fillchar(Q,sizeof(Q),0);
fillchar(visited,sizeof(visited),false);
head:=0;
tail:=1;
u.x:=startX;
u.y:=startY;
u.dist:=1;
Q[tail]:=u;
visited[u.x,u.y]:=true;
while tail<>head do
	begin
	head:=head mod 1000 +1;
	v:=Q[head];
	for i:=1 to 4 do
		begin
		if maze[v.x+offset[i,1],v.y+offset[i,2]] and not visited[v.x+offset[i,1],v.y+offset[i,2]] then
			begin
			tail:=tail mod 1000 +1;
			Q[tail].x:=v.x+offset[i,1];
			Q[tail].y:=v.y+offset[i,2];
			Q[tail].dist:=v.dist+1;
			visited[v.x+offset[i,1],v.y+offset[i,2]]:=true;
			if (Q[tail].x=endX)and(Q[tail].y=endY) then
				begin
				writeln(Q[tail].dist);
				exit;
				end;
			end;
		end;
	end;
end;

begin
readln(N);
for k:=1 to N do
	begin
	readln(width,height);
	{for i:=1 to height do
		for j:=1 to width do
			maze[i,j]:=true;}
	fillchar(maze,sizeof(maze),true);
	for i:=1 to height do
		begin
		for j:=1 to width do
			begin
			read(ch);
			if ch='#' then
				maze[i,j]:=false;
			if ch='S' then
				begin
				startX:=i;
				startY:=j;
				if i=1 then
					begin
					startFace:=4;
					maze[0,j]:=false;
					end
				else
                                if i=height then
					begin
					startFace:=2;
					maze[height+1,j]:=false;
					end
                                else
				if j=1 then
					begin
					startFace:=1;
					maze[i,0]:=false;
					end
				else
					begin
					startFace:=3;
					maze[i,width+1]:=false;
					end;
			end;
			if ch='E' then
				begin
				endX:=i;
				endY:=j;
				end;
			end;
		readln;
		end;
        finish:=false;
	DFS(startX,startY,startFace,1,1);
        finish:=false;
	DFS(startX,startY,startFace,1,2);
	BFS;
	end;
end.


