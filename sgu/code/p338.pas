program lf;
const
   lim=1e-9;
var
   x      : longint;
   g      : array[0..27,0..27] of double;
   a      : array[0..27] of double;
   f,h    : array[0..27,-1..27,-1..27] of double;
   profit : array[0..27,0..27] of longint;

procedure init;
begin
   readln(x);
end; { init }

procedure prepare;
var
   i,j : longint;
begin
   for i:=0 to 27 do
      for j:=0 to 27 do
         if (i<=21) and ((j>21) or (i>j)) then
            profit[i][j]:=1
         else
            profit[i][j]:=-1;
end; { prepare }

procedure solve;
var
   sum     : double;
   i,j,k,l : longint;
begin
   for i:=27 downto 0 do
      for j:=27 downto 0 do
      begin
         g[i][j]:=profit[i][j]*x;
         if j<=21 then
         begin
            sum:=0;
            for k:=1 to 6 do
               sum:=sum+g[i][j+k]/6;
            if sum<=g[i][j]+lim then g[i][j]:=sum;
         end;
      end;
   //the third person makes the decison
   for i:=27 downto 0 do
      for j:=27 downto 0 do
         for k:=27 downto 0 do
         begin
            h[i][j][k]:=profit[i][k]*x+profit[j][k];
            f[i][j][k]:=profit[j][k];
            if k<=21 then
            begin
               sum:=0;
               for l:=1 to 6 do
                  sum:=sum+h[i][j][k+l]/6;
               if sum<=h[i][j][k]+lim then
               begin
                  h[i][j][k]:=sum;
                  f[i][j][k]:=0;
                  for l:=1 to 6 do
                     f[i][j][k]:=f[i][j][k]+f[i][j][k+l]/6;
               end;
            end;
         end;
//the second person makes the decison
for i:=27 downto 0 do
     for j:=27 downto 0 do
     begin
        f[i][j][-1]:=f[i][j][0];
        if j<=21 then
        begin
           sum:=0;
           for k:=1 to 6 do
              sum:=sum+f[i][j+k][-1]/6;
           if sum>=f[i][j][-1] then f[i][j][-1]:=sum;
        end;
     end;
//the first person makes the decison
for i:=27 downto 0 do
begin
     a[i]:=g[i][0];
     f[i][-1][-1]:=f[i][0][-1];
     if i<=21 then
     begin
        sum:=0;
        for j:=1 to 6 do
           sum:=sum+a[i+j]/6;
        if sum>=a[i]-lim then
        begin
           a[i]:=sum;
           f[i][-1][-1]:=0;
           for j:=1 to 6 do
              f[i][-1][-1]:=f[i][-1][-1]+f[i+j][-1][-1]/6;
        end;
     end;
end;
	for i:=1 to 21 do
	 	for j:=1 to 21 do
			for k:=1 to 21 do 
		begin
			write(i);
			write(', ');
			write(j);
			write(', ');
			write(k);
			write(' = ');
				writeln(f[i][j][k]:0:6);
				end
{writeln((f[0][-1][-1]+1)/2:0:6);}
end; { solve }

begin
	assign(input, 't.in'); reset(input);
	assign(output, 't2.out'); rewrite(output);
   init;
   prepare;
   solve;
end.
