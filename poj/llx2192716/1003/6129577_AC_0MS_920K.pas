Program p1003;

Var 
  x, y: Real;
  t: Longint;
Begin 
    While NOT Eof Do 
      Begin 
        Readln(x);
        If Abs(x - 0.00) < 0.001 Then 
          Break;
        y := 0;
        t := 1;
        While y < x Do 
          Begin 
            Inc(t);
            y := y + 1 / t;
          End;
        Writeln(t - 1, ' card(s)');
      End;
  End.