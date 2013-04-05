Program integer;

Var
n,t2,t3               :       Longint;
ans                   :       Array [0..1600] of Longint;

Procedure Init;
begin
    readln(n);
end;

Procedure Mul(num:Longint);
var
    a                   :       Longint;

begin
    for a:=1 to 1500 do ans[a]:=ans[a]*num;
    for a:=1 to 1500 do
      begin
        ans[a+1]:=ans[a+1]+ans[a] Div 10000;
        ans[a]:=ans[a] Mod 10000;
      end;
end;

Procedure Main;
begin
    ans[1]:=1;
    while True do
      begin
        if n=4 then begin mul(2);mul(2);inc(t2,2);break;end;
        if n=2 then begin mul(2);inc(t2);break;end;
        if n=0 then break;
        mul(3);inc(t3);
        dec(n,3);
      end;
end;

Procedure Print;
var
    a,p,k,b,l           :       Longint;
begin
    p:=trunc((t3*ln(3)/ln(10))+(t2*ln(2)/ln(10)))+1;
    writeln(p);
    k:=1600;
    while ans[k]=0 do dec(k);
    write(ans[k]);
    l:=0;
    inc(l,trunc(ln(ans[k])/ln(10)+1));
    for a:=k-1 downto 1 do
      begin
        if l+4>100
          then
            begin
              if l=97 then begin write(ans[a] Div 1000);ans[a]:=ans[a] Mod 1000;write(ans[a] Div 100);ans[a]:=ans[a] Mod 1000;write(ans[a] Div 10);break;end;
              if l=98 then begin write(ans[a] Div 1000);ans[a]:=ans[a] Mod 1000;write(ans[a] Div 100);break;end;
              if l=99 then begin write(ans[a] Div 1000);break;end;
              if l=100 then break;
            end;
        for b:=1 to 4-(trunc(ln(ans[a])/ln(10))+1) do write(0);
        write(ans[a]);
        inc(l,4);
      end;
    writeln;
end;

Begin
Init;
Main;
Print;
End.
