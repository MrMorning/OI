program p1002;

var
  phonenum: string;
  words_Num: Longint;
  words, originalwords: array[1..50000] of string;
  i, j, u: Longint;
  f, g: array[0..100] of Longint;

procedure convert(var s : string);
  var
    ch: Char;
    ts: string;
    i: Longint;
  begin
    ts := '';
    for i := 1 to Length(s) do
      begin
        case s[i] of
          'i', 'j':
            ch := '1';
          'a', 'b', 'c':
            ch := '2';
          'd', 'e', 'f':
            ch := '3';
          'g', 'h':
            ch := '4';
          'k', 'l':
            ch := '5';
          'm', 'n':
            ch := '6';
          'p', 'r', 's':
            ch := '7';
          't', 'u', 'v':
            ch := '8';
          'w', 'x', 'y':
            ch := '9';
          'o', 'q', 'z':
            ch := '0';
          end;
        ts := ts + ch;
      end;
    s := ts;
  end;

procedure Print(i : Longint);
  begin
    if i = 0 then 
      Exit;
    Print(i - Length(words[g[i]]));
    if i - Length(words[g[i]]) = 0 then
      Write(originalwords[g[i]])
    else
      Write(' ', originalwords[g[i]]);
  end;

begin

    while NOT Eof do
      begin
        for i := 1 to 100 do
          f[i] := 50000;
        Readln(phonenum);
        if phonenum = '-1' then 
          Break;
        Readln(words_Num);
        for i := 1 to words_Num do
          begin
            Readln(words[i]);
            originalwords[i] := words[i];
            convert(words[i]);
          end;
        for i := 1 to Length(phonenum) do
          begin
            for j := 1 to words_Num do
              begin
                u := i - Length(words[j]);
                if u < 0 then 
                  Continue;
                if words[j] = Copy(phonenum, u + 1, Length(words[j])) then
                  if (f[u] + 1) < f[i] then
                    begin
                      f[i] := f[u] + 1;
                      g[i] := j;
                    end;
              end;
          end;
        if f[Length(phonenum)] = 50000 then 
          Writeln('No solution.')
        else
          begin
            Print(Length(phonenum));
            Writeln;
          end;
      end;
  end.
