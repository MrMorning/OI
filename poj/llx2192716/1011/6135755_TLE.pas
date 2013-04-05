program p1011;
var
totalLength,groupNum,groupLength,average:longint;
N,i:longint;
length,group:array[1..10000] of longint;
possible:array[0..10000] of boolean;
procedure doit;
	function search(k:longint):boolean;
	var
	i:integer;
	begin
	if k=N+1 then exit(true);
	for i:=1 to groupNum do
		begin
        if (groupLength-group[i]<average)and(not possible[groupLength-group[i]]) then
			exit;
	              if groupLength-group[i]=length[k] then
			begin
			group[i]:=groupLength;
			if search(k+1) then exit(true);
			group[i]:=groupLength-length[k];
			break;
			end;
	    if (group[i]=0)and(length[k]<=groupLength) then
			begin
			group[i]:=length[k];
			if search(k+1) then exit(true);
			group[i]:=0;
			break;
			end;
		if (length[k]+group[i])<=groupLength then
			begin
			group[i]:=group[i]+length[k];
			if search(k+1) then exit(true);
			group[i]:=group[i]-length[k];
			end;
		end;
	exit(false);
	end;

begin
for groupNum:=totalLength downto 1 do
	if totalLength mod groupNum = 0 then
		begin
		groupLength:=totalLength div groupNum;
		if search(1) then
			begin
			writeln(groupLength);
			exit;
			end;
		end;
end;

procedure qsort;

    procedure sort(l,r: longint);
      var
         i,j,x,y: longint;
      begin
         i:=l;
         j:=r;
         x:=length[N-(l+r) div 2+1];
         repeat
           while length[N-i+1]<x do
            inc(i);
           while x<length[N-j+1] do
            dec(j);
           if not(i>j) then
             begin
                y:=length[N-i+1];
                length[N-i+1]:=length[N-j+1];
                length[N-j+1]:=y;
                inc(i);
                j:=j-1;
             end;
         until i>j;
         if l<j then
           sort(l,j);
         if i<r then
           sort(i,r);
      end;

    begin
       sort(1,N);
    end;

procedure makePossibleLengths;
	procedure try(k,sum:longint);
	begin
        if sum>average then
                exit;
	if k=N+1 then exit;
	possible[sum]:=true;
	try(k+1,length[k]+sum);
        try(k+1,sum);
	end;
begin
average:=totalLength div N;
try(1,0);
end;

begin
while not eof do
	begin
	readln(N);
	if N=0 then break
	else
		begin
		totalLength:=0;
		fillchar(length,sizeof(length),0);
		fillchar(group,sizeof(group),0);
		for i:=1 to N do
			begin
			read(length[i]);
			totalLength:=totalLength+length[i];
			end;
        qsort;
		makePossibleLengths;
		doit;
		end;
	end;
end.
