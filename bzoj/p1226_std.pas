program SDOI_2009_Dining;
var f:array[0..1001,0..(1 shl 8)-1,-8..7]of longint;
    t,b:array[1..1000]of longint;
    inf,ans,Max_Anger,n,c,i,j,k,l:longint;

function min(a,b:longint):longint;
begin
  if a<b then exit(a);
  exit(b);
end;

begin
assign(input, 't.in'); reset(input);
  readln(c);
  while c>0 do
    begin
      dec(c);
      readln(n);
      fillchar(t,sizeof(t),0);
      fillchar(b,sizeof(b),0);
      fillchar(f,sizeof(f),$7f);
      inf:=f[0,0,0];
      for i:=1 to n do readln(t[i],b[i]);
      f[1,1<<8-1,-1]:=0;
      for i:=1 to n do
        for j:=(1<<8)-1 downto 0 do
          for k:=-8 to 7 do
            if f[i,j,k]<inf then
              begin
                if (j and 1=0)then
                  f[i+1,(j>>1)or(1<<7),k-1]:=f[i,j,k]
                else
                  begin
                    Max_Anger:=inf;
                    for l:=0 to 7 do
                      if j and (1<<l)<>0 then
                        begin
                          if i+l>Max_Anger then break;
                          Max_Anger:=min(Max_Anger,i+l+b[i+l]);
                          if i+k<=0 then f[i,j and not(1<<l),l]:=min(f[i,j and not(1<<l),l],0)
                            else f[i,j and not(1<<l),l]:=min(f[i,j and not(1<<l),l],f[i,j,k]+(t[i+k] xor t[i+l]));
                        end;
                  end;
              end;
      ans:=maxlongint;
      for i:=-8 to -1 do
        ans:=min(ans,f[n+1,(1<<8)-1,i]);
      writeln(ans);
    end;
  readln;readln;
end.

