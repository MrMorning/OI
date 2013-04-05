program p306;
var bj,i,n,pow  :longint;
procedure op(X:longint);
begin
     writeln('fake ',x);
end;
procedure prrt(a,b:longint);
var i:longint;
begin
          write(a);
          for i:=a+1 to b do write('+',i);
end;
procedure print(a,b,c,d:longint);
begin
     if a<=b then  prrt(a,b);
     if (c<=d) then
     begin
          if a<=b then write('+');
          prrt(c,d);
     end;
end;
procedure fj(l,r:longint;var a1,b1,a2,b2,a3,b3:longint);
var x:longint;
begin
     x:=(r-l+1) div 3;
     if (r-l+1) mod 3=2 then  inc(x);
     a1:=l;b1:=l+x-1;
     a2:=l+x;b2:=a2+x-1;
     a3:=a2+x;b3:=r;
end;
procedure space(x:longint);
begin
     for i:=1 to x*2 do write(' ');
end;
procedure dfs(now,l1,r1,l2,r2:longint);
var n1,n2,a1,a2,a3,b1,b2,b3,c1,c2,c3,d1,d2,d3: longint;
begin
     n1:=r1-l1+1;
     n2:=r2-l2+1;
     if n1+n2=1 then
     begin
          space(now);
          if l1=r1 then op(l1)
          else op(l2);
          exit;
     end;
     if n1+n2=2 then
     begin
          space(now);writeln('weigh ',l1,' vs ',bj);
          space(now);writeln('case <:');dfs(now+1,l1,r1,l1,r1-1);
          space(now);writeln('case =:');dfs(now+1,l2,r2,l2,r2-1);
          space(now);writeln('end');
          exit;
     end;
     fj(l1,r1,a1,b1,a2,b2,a3,b3);
     fj(l2,r2,c1,d1,c2,d2,c3,d3);
     if (n1 mod 3=1)and(n2 mod 3=1) then
     begin
          inc(d2);inc(c3);
          space(now);write('weigh ');
          prrt(a1,b1);write('+',bj,'+');prrt(c1,d1);write(' vs ');
          print(a2,b2,c2,d2);writeln;
     end
     else
     begin
          space(now);write('weigh ');
          print(a1,b1,c1,d1);write(' vs '); print(a2,b2,c2,d2);writeln;
     end;
     space(now);writeln('case <:');
     dfs(now+1,a1,b1,c2,d2);
     if (a3<=b3)or(c3<=d3) then
     begin
          space(now);writeln('case =:');
          dfs(now+1,a3,b3,c3,d3);
     end;
     space(now);writeln('case >:');
     dfs(now+1,a2,b2,c1,d1);
     space(now);writeln('end');
end;
procedure dfs2(now,l,r:longint);
var n,a1,a2,a3,b1,b2,b3:longint;
begin
     n:=r-l+1;
     if n=1 then
     begin
          space(now);op(l);  exit;
     end;
     if n=2 then
     begin
          space(now);writeln('weigh ',l,' vs ',bj);
          space(now);writeln('case <:');dfs2(now+1,l,l);
          space(now);writeln('case =:');dfs2(now+1,r,r);
          space(now);writeln('case >:');dfs2(now+1,l,l);
          space(now);writeln('end');
          exit;
     end;
     fj(l,r,a1,b1,a2,b2,a3,b3);
     if n mod 3=1 then
     begin
          inc(b2);inc(a3);
          space(now);write('weigh ');prrt(a1,b1);if a1<=b1 then write('+');write(bj);write(' vs ');prrt(a2,b2);writeln;
     end;
     if n mod 3=2 then
     begin
          dec(b2);dec(a3);
          space(now);write('weigh ');prrt(a1,b1);write(' vs ');prrt(a2,b2);if a2<=b2 then write('+');write(bj);writeln;
     end;
     if n mod 3=0 then
     begin
          space(now);write('weigh ');prrt(a1,b1);write(' vs ');prrt(a2,b2);writeln;
     end;                                //少了这句话。。囧
     space(now);writeln('case <:');
     dfs(now+1,a1,b1,a2,b2);
     space(now);writeln('case =:');
     dfs2(now+1,a3,b3);
     space(now);writeln('case >:');
     dfs(now+1,a2,b2,a1,b1);
     space(now);writeln('end');
end;
procedure main;
var a1,a2,a3,b1,b2,b3:longint;
begin
     fj(1,n,a1,b1,a2,b2,a3,b3);
     write('weigh ');prrt(a1,b1);write(' vs ');prrt(a2,b2);writeln;
     writeln('case <:');
     bj:=a3;
     dfs(1,a1,b1,a2,b2);
     writeln('case =:');
     bj:=a1;
     dfs2(1,a3,b3);
     writeln('case >:');
     bj:=a3;
     dfs(1,a2,b2,a1,b1);
     writeln('end');
end;
begin
     assign(input,'t.in');   reset(input);
     //assign(output,'t2.out'); rewrite(output);
     readln(n);
     pow:=1;
     for i:=1 to 100 do
     begin
          pow:=pow*3;
          if pow>=2*n+1 then break;
     end;
     writeln('need ',i,' weighings');
     //main;
end.

