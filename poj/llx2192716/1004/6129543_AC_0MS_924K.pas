Program p1004;

Var 
  sum, x: Real;
  i: Integer;
Begin 
    For i := 1 To 12 Do 
      Begin 
        Readln(x);
        sum := sum + x;
      End;
    Writeln('$', (sum / 12): 0: 2);
End.