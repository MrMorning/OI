type pair=record
        l,r,rank,k:longint;
        s,m:int64;
        end;
var
        a:array[1..50000]of pair;
        b,c:array[1..50000]of longint;
        n,m,i,kuai,ans,l,r,gc,max1:longint;
        ge:int64;
function gcd(x,y:longint):longint;
        begin
                if y=0 then exit(x);
                exit(gcd(y,x mod y));
        end;
procedure kspx(x,y:longint);
        var i,j,k,k1,s1:longint;
        temp:pair;
        begin
                i:=x;
                j:=y;
                s1:=random(y-x+1)+x;
                k:=a[s1].k;
                k1:=a[s1].r;
                repeat
                        while(a[i].k<k)or((a[i].k=k)and(a[i].r<k1))do inc(i);
                        while(a[j].k>k)or((a[j].k=k)and(a[j].r>k1))do dec(j);
                        if i<=j then
                        begin
                                temp:=a[i];
                                a[i]:=a[j];
                                a[j]:=temp;
                                inc(i);
                                dec(j);
                        end;
                until i>j;
                if i<y then kspx(i,y);
                if j>x then kspx(x,j);
        end;
procedure kspx1(x,y:longint);
        var i,j,k:longint;
        temp:pair;
        begin
                i:=x;
                j:=y;
                k:=a[random(y-x+1)+x].rank;
                repeat
                        while(a[i].rank<k)do inc(i);
                        while(a[j].rank>k)do dec(j);
                        if i<=j then
                        begin
                                temp:=a[i];
                                a[i]:=a[j];
                                a[j]:=temp;
                                inc(i);
                                dec(j);
                        end;
                until i>j;
                if i<y then kspx1(i,y);
                if j>x then kspx1(x,j);
        end;
begin
assign(input, 't.in'); reset(input);
        readln(n,m);
        for i:=1 to n do
                read(b[i]);
        for i:=1 to m do
        begin
                readln(a[i].l,a[i].r);
                if a[i].r>max1 then max1:=a[i].r;
                a[i].rank:=i;
        end;
        kuai:=trunc(sqrt(max1));
        for i:=1 to m do
                a[i].k:=a[i].l div kuai;
        kspx(1,m);
        ans:=0;
        for i:=1 to n do
        begin
                ans:=ans+c[b[i]];
                inc(c[b[i]]);
        end;
        l:=1;
        r:=n;
        for i:=1 to m do
        begin
                while l<a[i].l do
                begin
                        ans:=ans-c[b[l]]+1;
                        dec(c[b[l]]);
                        inc(l);
                end;
                while r>a[i].r do
                begin
                        ans:=ans-c[b[r]]+1;
                        dec(c[b[r]]);
                        dec(r);
                end;
                while l>a[i].l do
                begin
                        dec(l);
                        ans:=ans+c[b[l]];
                        inc(c[b[l]]);
                end;
                while r<a[i].r do
                begin
                        inc(r);
                        ans:=ans+c[b[r]];
                        inc(c[b[r]]);
                end;
                a[i].s:=ans;
                ge:=a[i].r-a[i].l+1;
                a[i].m:=ge*(ge-1)shr 1;
        end;
        kspx1(1,m);
        for i:=1 to m do
        begin
                if a[i].s=0 then a[i].m:=1
                else
                begin
                        gc:=gcd(a[i].s,a[i].m);
                        a[i].s:=a[i].s div gc;
                        a[i].m:=a[i].m div gc;
                end;
                writeln(a[i].s,'/',a[i].m);
        end;
        readln;
end.
