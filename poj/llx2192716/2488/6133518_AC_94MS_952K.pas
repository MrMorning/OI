program p2488;
const
rule:array[1..8,1..2] of integer = ((-1,-2),(1,-2),(-2,-1),(2,-1),(-2,1),(2,1),(-1,2),(1,2));
var
N,i,p,q:longint;

procedure doit(p,q,testIndex:longint);
var
maxStep,i,j:longint;
find:boolean;
visited:array[1..32,1..32] of boolean;
ts:string;
path:ansistring;

	procedure dfs(x,y,steps:longint);
        var
        i,newX,newY:longint;
	begin
	if find then exit;
	visited[x,y]:=true;
        str(x,ts);
	path:=path+chr(ord('A')+y-1)+ts;
        if steps=maxStep then
		begin
		writeln(path);
		find:=true;
		exit;
		end;
	for i:=1 to 8 do
		begin
		newX:=x+rule[i,1];
		newY:=y+rule[i,2];
		if not((newX>=1)and(newX<=p)and(newY>=1)and(newY<=q)and not visited[newX,newY]) then continue;
		dfs(newX,newY,steps+1);
		end;
	visited[x,y]:=false;
	delete(path,length(path)-1,2);
	end;
begin
writeln('Scenario #',testIndex,':');
maxStep:=p*q;
find:=false;
for i:=1 to q do
	for j:=1 to p do
		begin
		fillchar(visited,sizeof(visited),false);
		path:='';
		dfs(j,i,1);
                if find then begin writeln; exit; end;
		end;
if not find then
        begin
        writeln('impossible');
        writeln;
        end;
end;
begin
readln(N);
for i:=1 to N do
	begin
	readln(p,q);
	doit(p,q,i);
	end;
end.
