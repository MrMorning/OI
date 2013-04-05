 
program {POI2007}Hong_Shui_pow;
const dx:array[1..4]of integer=(1,0,-1,0);
      dy:array[1..4]of integer=(0,1,0,-1);
var m,n,i,j,max,nx,ny,nowx,nowy:integer;
    size,size2,ans:longint;
    h,w:array[0..1000,0..1000]of integer;
    need:array[1..1000,1..1000]of boolean;
    en,en2:array[1..1000]of longint;
    pre,pre2:array[1..1000000]of longint;
    x,y,x2,y2:array[1..1000000]of integer;
//=====================================================================
procedure ins(num,xx,yy:longint);
begin
  inc(size);
  x[size]:=xx;
  y[size]:=yy;
  pre[size]:=en[num];
  en[num]:=size;
end;
//=====================================================================
procedure ins2(num,xx,yy:longint);
begin
  inc(size2);
  x2[size2]:=xx;
  y2[size2]:=yy;
  pre2[size2]:=en2[num];
  en2[num]:=size2;
end;
//=====================================================================
procedure init;
begin
  readln(m,n);
  for i:=1 to m do
    for j:=1 to n do
      begin
        read(h[i,j]);
        if h[i,j]>0 then
          begin
            ins(h[i,j],i,j);
            need[i,j]:=true;
          end
        else h[i,j]:=-h[i,j];
      end;
  for i:=1000 downto 1 do
    if en[i]>0 then
      begin
        max:=i;
        break;
      end;
end;
//=====================================================================
begin
assign(input, 't.in'); reset(input);
  init;
  fillchar(w,sizeof(w),$FF);
  for i:=1 to max do
    repeat
      if en2[i]>0 then
        begin
          nowx:=x2[en2[i]];nowy:=y2[en2[i]];
          en2[i]:=pre2[en2[i]];
          for j:=1 to 4 do
            begin
              nx:=nowx+dx[j];ny:=nowy+dy[j];
              if (nx>0) and (nx<=m) and (ny>0) and (ny<=n) and (w[nx,ny]=-1)then
                begin
                  if h[nx,ny]>w[nowx,nowy] then w[nx,ny]:=h[nx,ny]
                  else w[nx,ny]:=w[nowx,nowy];
                  ins2(w[nx,ny],nx,ny);
                end;
            end;
        end
      else if en[i]>0 then
        begin
          nowx:=x[en[i]];nowy:=y[en[i]];
          en[i]:=pre[en[i]];
          if w[nowx,nowy]<>-1 then continue;
          inc(ans);
          w[nowx,nowy]:=h[nowx,nowy];
          for j:=1 to 4 do
            begin
              nx:=nowx+dx[j];ny:=nowy+dy[j];
              if (nx>0) and (nx<=m) and (ny>0) and (ny<=n) and (w[nx,ny]=-1)then
                begin
                  if h[nx,ny]>w[nowx,nowy] then w[nx,ny]:=h[nx,ny]
                  else w[nx,ny]:=w[nowx,nowy];
                  ins2(w[nx,ny],nx,ny);
                end;
            end;
        end
      else break;
    until false;
  writeln(ans);
end.
