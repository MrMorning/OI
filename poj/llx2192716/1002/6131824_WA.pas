Program p1002;

Var
  a:array[1..100001] of string;
  N, i, printtimes: Longint;
  s, phonenum: String;

Function Map(c : Char): Char;
  Begin
    Case c Of
      'A'..'C':
        Exit('2');
      'D'..'F':
        Exit('3');
      'G'..'I':
        Exit('4');
      'J'..'L':
        Exit('5');
      'M'..'O':
        Exit('6');
      'P','R','S':
        Exit('7');
      'T'..'V':
        Exit('8');
      'W'..'Y':
        Exit('9');
      End;
  End;

Function convert(s : String): String;
  Var
    ts: String;
    i: Longint;
  Begin
    ts := '';
    For i := 1 To Length(s) Do
      If (s[i] >= '0') AND (s[i] <= '9') Then
          ts := ts + s[i]
    Else If (s[i] >= 'A') AND (s[i] <= 'Z') Then
      ts := ts + Map(s[i])
    Else If (s[i]>='a') AND (s[i]<='z') Then
        ts:=ts + Map(upcase(s[i]));
    Exit(ts);
  End;
procedure qsort;

    procedure sort(l,r: longint);
      var
         i,j: longint;
		 x,y:string;
      begin
         i:=l;
         j:=r;
         x:=a[(l+r) div 2];
         repeat
           while a[i]<x do
            inc(i);
           while x<a[j] do
            dec(j);
           if not(i>j) then
             begin
                y:=a[i];
                a[i]:=a[j];
                a[j]:=y;
                inc(i);
                j:=j-1;
             end;
         until i>j;
         if l<j then
           sort(l,j);
         if i<r then
           sort(i,r);
      end;

    begin
       sort(1,N);
    end;

procedure stat;
var
i,times:longint;
pre:string;
begin
pre:=a[1];
times:=1;
for i:=2 to N do
	begin
	if a[i]=pre then
		inc(times)
	else
		begin
		if times>1 then
			begin
			Writeln(Copy(pre, 1, 3), '-', Copy(pre, 4, 4), ' ', times);
			inc(printtimes);
			end;
		times:=1;
                pre:=a[i];
		end;
	end;
end;

Begin
    Readln(N);
    For i := 1 To N Do
      Begin
        Readln(s);
        phonenum := convert(s);
        a[i]:=phonenum;
      End;
    printtimes := 0;
    qsort;
	stat;
    If printtimes = 0 Then
      Writeln('No duplicates.');
  End.


