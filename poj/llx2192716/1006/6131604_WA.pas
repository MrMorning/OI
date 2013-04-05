program p1006;
var
n,a,b,c,start,d:longint;
b1,b2,b3:boolean;
begin
n:=0;
while not eof do
        begin
        readln(a,b,c,start);
        if (a=-1)and(b=-1)and(c=-1)and(d=-1) then
                break;
        inc(n);
        for d:=start+1 to 50000 do
                begin
                b1:=((d-a)mod 23) = 0;
                b2:=((d-b)mod 28) = 0;
                b3:=((d-c)mod 33) = 0;
                if b1 and b2 and b3 then
                        begin
                        writeln('Case ',n,': the next triple peak occurs in ',d-start,' days.');
                        break;
                        end;
                end;
        end;
end.
