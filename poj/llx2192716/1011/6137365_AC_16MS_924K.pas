program p1011;
var
sticksNum,groupsNum,totalLength,groupLength:longint;
stickLength:array[1..100] of longint;
used:array[1..100] of boolean;
i:longint;
OK:boolean;

procedure rebuild(x:longint);
var
i:longint;
	procedure search(x,currentLength,pre:longint);
        var
        i:longint;
	begin
	if OK then exit;
	if currentLength=groupLength then
		begin
		rebuild(x+1);
		exit;
		end;
	if pre+1>sticksNum then exit;
	for i:=pre+1 to sticksNum do
		if not used[i] then
			if (stickLength[i]+currentLength<=groupLength) then
				begin
				{if (stickLength[i]=stickLength[i-1])and(not used[i-1])
                                        then continue;}
				used[i]:=true;
				search(x,stickLength[i]+currentLength,i);
				used[i]:=false;
				if OK then exit;
				if (stickLength[i]+currentLength=groupLength) then exit;
				end;
	end;
begin
if x>groupsNum then
	begin
	OK:=true;
	writeln(groupLength);
	exit;
	end;

i:=1;
while used[i] do inc(i);
used[i]:=true;
search(x,stickLength[i],i);
used[i]:=false;
end;

procedure qsort;

    procedure sort(l,r: longint);
      var
         i,j,x,y: longint;
      begin
         i:=l;
         j:=r;
         x:=stickLength[(l+r) div 2];
         repeat
           while stickLength[i]>x do
            inc(i);
           while x>stickLength[j] do
            dec(j);
           if not(i>j) then
             begin
                y:=stickLength[i];
                stickLength[i]:=stickLength[j];
                stickLength[j]:=y;
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
       sort(1,sticksNum);
    end;

begin
while not eof do
	begin
	readln(sticksNum);
	if sticksNum=0 then break;
	totalLength:=0;
	OK:=false;
	for i:=1 to sticksNum do
		begin
		read(stickLength[i]);
		inc(totalLength,stickLength[i]);
		end;
        qsort;
        for i:=stickLength[1] to totalLength do
		if (totalLength mod i =0) then
			begin
			groupLength:=i;
			groupsNum:=totalLength div groupLength;
			fillchar(used,sizeof(used),false);
			rebuild(1);
                        if OK
                                then break;
			end;
	end;
end.
