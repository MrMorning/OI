program p1042;
var
n,h,originH:integer;
originF,f,d,t,a,maxA:array[1..25] of longint;
x,i,u,stop,max,fish,maxfish:longint;
ans,ts:string;
begin
while not eof do
	begin
	readln(n);
	if n=0 then break;
	readln(h);
	h:=h*12;
	for i:=1 to n do
		read(f[i]);
	for i:=1 to n do
		read(d[i]);
	for i:=1 to n-1 do
		begin
		read(x);
		t[i+1]:=t[i]+x;
		end;
	originF:=f;
	originH:=h;
	maxfish:=-maxlongint;
	for stop:=1 to n do
		begin
		h:=originH-t[stop];
                if h<=0 then continue;
		fish:=0;
		fillchar(a,sizeof(a),0);
		f:=originF;
		while h>0 do
			begin
			max:=f[1];
                        u:=1;
			for i:=2 to stop do
				if f[i]>max then
					begin
					max:=f[i];
					u:=i;
					end;
                        if f[u]>0 then
                                begin
				fish:=fish+f[u];
                                if f[u]-d[u]<0 then
                                        f[u]:=0
                                else
				        f[u]:=f[u]-d[u];
				inc(a[u]);
                                end
                        else
      			      inc(a[1]);
                        dec(h);
			end;
		if fish>maxfish then
			begin
			maxfish:=fish;
			maxA:=a;
			end;
		end;
        ans:='';
	for i:=1 to N do
		//if maxA[i]<>0 then
                        begin
                        str(maxA[i]*5,ts);
						ans:=ans+' '+ts+',';
                        end;
	delete(ans,1,1);
	delete(ans,length(ans),1);
	writeln(ans);
	writeln('Number of fish expected: ',maxfish);
        writeln;
	end;
end.
