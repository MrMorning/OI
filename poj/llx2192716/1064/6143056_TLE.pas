program p1064;
var
N,K,i:longint;
len:array[1..10000] of longint;
totalLen:longint;
currentLen,prelen:longint;
tmp:longint;
s:string;

procedure search(l,r:longint);
begin
currentLen:=(l+r) div 2;
tmp:=0;
for i:=1 to N do
	tmp:=tmp+len[i] div currentLen;
if tmp<K then
	search(l,currentLen)
else if tmp>K then
	search(currentLen,r)
else
	begin
        if currentlen=prelen then
                begin
                writeln(currentlen/100:0:2);
                exit;
                end
        else
                begin
                prelen:=currentlen;
                search(l+1,r+1);
                end;
	end;
end;

begin
readln(N,K);
totalLen:=0;
for i:=1 to N do
	begin
	readln(s);
	delete(s,pos('.',s),1);
	val(s,len[i]);
	totalLen:=totalLen+len[i];
	end;
search(0,totalLen);

end.
