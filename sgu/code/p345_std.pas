{
 Author:wzx961008
 Problem:sgu 345-Revolution
 Verdict:Accepted
 Language:PASCAL
 Run Time:0.765s
 Submission Date:26.08.11 08:25
}
{$MODE Delphi}
uses math;
const error=1e-8; maxn=50000; oo=1e10;
type point=record x,y:extended; end;
var pt,convex:array[1..maxn+1]of point;
    sum:array[1..maxn+1]of extended;
    fs:array[1..maxn*2+2]of point;
    n,m,top:longint;
    s:extended;
    origin:point;
procedure swap(var p1,p2:point);
var t:point;
begin
 t:=p1; p1:=p2; p2:=t;
end;
function cross(p11,p12,p21,p22:point):extended;
var x1,y1,x2,y2:extended;
begin
 x1:=p12.x-p11.x;
 y1:=p12.y-p11.y;
 x2:=p22.x-p21.x;
 y2:=p22.y-p21.y;
 cross:=x1*y2-x2*y1;
end;
function dist(p1,p2:point):extended;
begin
 dist:=sqrt(sqr(p1.x-p2.x)+sqr(p1.y-p2.y));
end;
procedure qsort_polar_angle(l,r:longint);
var i,j:longint;
    m:point;
    crs1,crs2,dstm:extended;
begin
 i:=l; j:=r; m:=pt[l+random(r-l)];
 repeat
  dstm:=dist(pt[1],m);
  repeat
   crs1:=cross(pt[1],m,pt[1],pt[i]);
   if not((crs1<-error)or((abs(crs1)<error)and(dstm>dist(pt[1],pt[i])))) then break;
   inc(i);
  until false;
  repeat
   crs2:=cross(pt[1],pt[j],pt[1],m);
   if not((crs2<-error)or((abs(crs2)<error)and(dist(pt[1],pt[j])>dstm))) then break;
   dec(j);
  until false;
  if i<=j then begin
   swap(pt[i],pt[j]);
   inc(i); dec(j);
  end;
 until i>j;
 if l<j then qsort_polar_angle(l,j);
 if i<r then qsort_polar_angle(i,r);
end;
procedure get_point;
var i:longint;
begin
 readln(n);
 for i:=1 to n do begin
  readln(pt[i].x,pt[i].y);
  if (pt[i].y<pt[1].y)or((abs(pt[i].y-pt[1].y)<error)and(pt[i].x<pt[1].x)) then swap(pt[1],pt[i]);
 end;
end;
procedure get_convex;
var p,i:longint;
begin
 for i:=1 to n do begin
  inc(top); convex[top]:=pt[i];
  if top>2 then begin
   p:=top-1;
   while (p>1)and(sign(cross(convex[p-1],convex[p],convex[p],convex[top]))<=0) do dec(p);
   top:=p+1; convex[top]:=pt[i];
  end;
 end;
end;
function qd(p:point):longint;
begin
 if (p.x>0)and(p.y>=0) then begin qd:=1; exit; end;
 if (p.x<=0)and(p.y>0) then begin qd:=2; exit; end;
 if (p.x<0)and(p.y<=0) then begin qd:=3; exit; end;
 if (p.x>=0)and(p.y<0) then begin qd:=4; exit; end;
end;
function smler_pa(p11,p12,p21,p22:point):boolean;
var vc1,vc2:point;
    qd1,qd2:longint;
begin
 vc1.x:=p12.x-p11.x; vc1.y:=p12.y-p11.y;
 vc2.x:=p22.x-p21.x; vc2.y:=p22.y-p21.y;
 qd1:=qd(vc1); qd2:=qd(vc2);
 if qd1<>qd2 then begin smler_pa:=qd1<qd2; exit; end;
 smler_pa:=cross(p11,p12,p21,p22)>=0;
end;
procedure init;
var i:longint;
begin
 get_point;
 randomize;
 qsort_polar_angle(2,n);
 get_convex;
 for i:=1 to top do begin
  fs[i]:=convex[i];
  fs[i+top]:=convex[i];
 end;
 sum[1]:=0;
 for i:=2 to top do sum[i]:=sum[i-1]+cross(origin,convex[i-1],origin,convex[i]);
 s:=sum[top]+cross(origin,convex[top],origin,convex[1]);
end;
function itst(p1,p2:point; a,b,c:extended; var ip:point):boolean;
var aa,bb,cc,tmp:extended;
begin
 itst:=false;
 if sign((a*p1.x+b*p1.y+c)*(a*p2.x+b*p2.y+c))<=0 then begin
  itst:=true;
  aa:=p1.y-p2.y; bb:=p2.x-p1.x; cc:=p1.x*p2.y-p2.x*p1.y;
  tmp:=bb*a-b*aa; if sign(tmp)=0 then begin itst:=false; exit; end;
  ip.x:=(b*cc-c*bb)/tmp;
  ip.y:=(c*aa-a*cc)/tmp;
 end;
end;
procedure main;
var i,fp1n,fp2n,cp1n,cp2n,i1s1,i1s2,i2s1,i2s2,tmp:longint;
    p1,p2,ip,ip1,ip2:point;
    a,b,c,s1:extended;
    b1,b2,bb:boolean;
function next(x:longint):longint;
begin
 if x=top then next:=1 else next:=x+1;
end;
function last(x:longint):longint;
begin
 if x=1 then last:=top else last:=x-1;
end;
function check(p1,p2:point):boolean;
begin
 check:=(abs(p1.x-p2.x)<error)and(abs(p1.y-p2.y)<error);
end;
function binary_search(p1,p2:point):longint;
var l,r,m:longint;
    b1,b2:boolean;
    vec:point;
begin
 vec.x:=p2.x-p1.x; vec.y:=p2.y-p1.y;
 if (cross(origin,vec,convex[top],convex[1])<=0)and(cross(origin,vec,convex[1],convex[2])>=0) then begin binary_search:=1; exit; end;
 if (cross(origin,vec,convex[top-1],convex[top])<=0)and(cross(origin,vec,convex[top],convex[1])>=0) then begin binary_search:=top; exit; end;
 l:=1; r:=top;
 while true do begin
  m:=(l+r) shr 1;
  b1:=smler_pa(convex[m-1],convex[m],origin,vec);
  b2:=smler_pa(origin,vec,convex[m],convex[m+1]);
  if (b1)and(b2) then begin binary_search:=m; exit; end;
  if (b1)and(not(b2)) then l:=m;
  if (not(b1))and(b2) then r:=m;
 end;
end;
function trinary_search(l,r:longint):longint;
var ll,rr,t1,t2,t,ret:longint;
    fd1,fd2,fd3,min:extended;
begin
 ll:=l; rr:=r;
 if r<l then rr:=rr+top;
 while true do begin
  t:=(rr-ll) div 3; t1:=ll+t; t2:=rr-t;
  fd1:=abs(a*fs[t1].x+b*fs[t1].y+c);
  fd2:=abs(a*fs[t2].x+b*fs[t2].y+c);
  if rr-ll<=2 then begin
   min:=oo;
   if rr-ll=2 then begin
    fd3:=abs(a*fs[ll+1].x+b*fs[ll+1].y+c);
    if fd3<min then begin
     min:=fd3; ret:=ll+1;
    end;
   end;
   if fd1<min then begin
    min:=fd1; ret:=ll;
   end;
   if fd2<min then begin
    min:=fd2; ret:=rr;
   end;
   trinary_search:=ret; exit;
  end;
  if fd1<fd2 then rr:=t2 else ll:=t1;
 end;
end;
begin
 readln(m);
 for i:=1 to m do begin
  readln(p1.x,p1.y,p2.x,p2.y);
  a:=p1.y-p2.y; b:=p2.x-p1.x; c:=p1.x*p2.y-p2.x*p1.y;
  fp1n:=binary_search(p1,p2);
  fp2n:=binary_search(p2,p1);
  cp1n:=trinary_search(fp1n,fp2n); if cp1n>top then cp1n:=cp1n-top;
  cp2n:=trinary_search(fp2n,fp1n); if cp2n>top then cp2n:=cp2n-top;
  b1:=true; b2:=true;
  if itst(convex[last(cp1n)],convex[cp1n],a,b,c,ip) then begin
   ip1:=ip; b1:=false; i1s1:=last(cp1n); i1s2:=cp1n;
  end;
  if itst(convex[cp1n],convex[next(cp1n)],a,b,c,ip) then begin
   if b1 then begin ip1:=ip; b1:=false; i1s1:=cp1n; i1s2:=next(cp1n); end;
   if not(check(ip1,ip))and(not(b1)) then begin
    ip2:=ip; b2:=false; i2s1:=cp1n; i2s2:=next(cp1n);
   end;
  end;
  if itst(convex[last(cp2n)],convex[cp2n],a,b,c,ip) then begin
   if b1 then begin ip1:=ip; b1:=false; i1s1:=last(cp2n); i1s2:=cp2n; end;
   if not(check(ip1,ip))and(not(b1)) then begin
    ip2:=ip; b2:=false; i2s1:=last(cp2n); i2s2:=cp2n;
   end;
  end;
  if itst(convex[cp2n],convex[next(cp2n)],a,b,c,ip) then begin
   if b1 then begin ip1:=ip; b1:=false; i1s1:=cp2n; i1s2:=next(cp2n); end;
   if not(check(ip1,ip))and(not(b1)) then begin
    ip2:=ip; b2:=false; i2s1:=cp2n; i2s2:=next(cp2n);
   end;
  end;
  if (b1)or(b2) then begin writeln('0.00'); continue; end;
  if i1s1>i1s2 then begin tmp:=i1s1; i1s1:=i1s2; i1s2:=tmp; end;
  if i2s1>i2s2 then begin tmp:=i2s1; i2s1:=i2s2; i2s2:=tmp; end;
  bb:=true;
  if ((i1s1=1)and(i1s2=top))and(bb) then begin s1:=sum[i2s1]+(cross(origin,convex[i2s1],origin,ip2)+cross(origin,ip2,origin,ip1)+cross(origin,ip1,origin,convex[1])); bb:=false; end;
  if ((i2s1=1)and(i2s2=top))and(bb) then begin s1:=sum[i1s1]+(cross(origin,convex[i1s1],origin,ip1)+cross(origin,ip1,origin,ip2)+cross(origin,ip2,origin,convex[1])); bb:=false; end;
  if (i1s2<=i2s1)and(bb) then begin s1:=(sum[i2s1]-sum[i1s2])+(cross(origin,convex[i2s1],origin,ip2)+cross(origin,ip2,origin,ip1)+cross(origin,ip1,origin,convex[i1s2])); bb:=false; end;
  if (i2s2<=i1s1)and(bb) then begin s1:=(sum[i1s1]-sum[i2s2])+(cross(origin,convex[i1s1],origin,ip1)+cross(origin,ip1,origin,ip2)+cross(origin,ip2,origin,convex[i2s2])); bb:=false; end;
  writeln(min(s-s1,s1)/2:0:0);
 end;
end;
begin
	assign(input, 't.in'); reset(input);
 init;
 main;
end.
