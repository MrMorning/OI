program p1064;
var
N,K,i:longint;
len:array[1..10000] of int64;
totalLen,currentLen,prelen:int64;
tmp:longint;
x:real;

procedure search(l,r:longint);
begin
currentLen:=(l+r) div 2;
if currentlen=prelen then
            begin
                writeln(currentlen/100:0:2);
                exit;
                end;
tmp:=0;
for i:=1 to N do
	tmp:=tmp+len[i] div currentLen;
if tmp<K then
	search(l,currentLen)
else
        begin
        prelen:=currentlen;
	search(currentLen,r);
        end;
end;

begin
readln(N,K);
totalLen:=0;
for i:=1 to N do
	begin
	readln(x);
        len[i]:=round(x*100);
	totalLen:=totalLen+len[i];
	end;
search(0,totalLen);

end.
