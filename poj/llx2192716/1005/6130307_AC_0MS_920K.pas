program p1005;
var
i,N,ans:longint;
x,y:real;
begin
readln(N);
for i:=1 to N do
        begin
        readln(x,y);
        ans:=trunc((sqr(x)+sqr(y))*Pi/100)+1;
        writeln('Property ',i,': This property will begin eroding in year ',ans,'.');
        end;
writeln('END OF OUTPUT.');
end.
