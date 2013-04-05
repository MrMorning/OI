program p1011;

var
  totalLength,groupNum, groupLength: Longint;
  sticksNum, i: Longint;
  Length, group: array[0..10000] of Longint;
  used: array[0..10000] of Boolean;
  b:boolean;

procedure doit;
  function search(k, currentLength : Longint): Boolean;
    var
      i: Integer;
    begin
      if k = groupNum + 1 then
        Exit(True);
      for i := 1 to sticksNum do
        if (NOT used[i]) then
        begin
		  if (length[i]=length[i-1])and(not used[i-1]) then
			continue;
		  if (currentLength + Length[i] > groupLength) then
			continue;
		  if (currentLength + Length[i] = groupLength) then
			begin
			used[i]:=true;
                        b:=search(k + 1, 0);
                        used[i]:=false;
                        exit(b);
			end;
          if (currentLength + Length[i] < groupLength) then
          begin
            used[i] := True;
            if search(k, currentLength + Length[i]) then
              Exit(True);
            used[i] := False;
          end;
        end;
      Exit(False);
    end;
  begin
    for groupNum := totalLength downto 1 do
      if totalLength MOD groupNum = 0 then
        begin
        fillchar(used,sizeof(used),false);
          groupLength := totalLength DIV groupNum;
          if search(1, 0) then
            begin
              Writeln(groupLength);
              Exit;
            end;
        end;
  end;

procedure qsort;

  procedure Sort(l, r : Longint);
    var
      i, j, x, y: Longint;
    begin
      i := l;
      j := r;
      x := Length[sticksNum - (l + r) DIV 2 + 1];
      repeat
        while Length[sticksNum - i + 1] < x do
          Inc(i);
        while x < Length[sticksNum - j + 1] do
          Dec(j);
        if NOT (i > j) then
        begin
          y := Length[sticksNum - i + 1];
          Length[sticksNum - i + 1] := Length[sticksNum - j + 1];
          Length[sticksNum - j + 1] := y;
          Inc(i);
          j := j - 1;
        end;
      until i > j;
      if l < j then
        Sort(l, j);
      if i < r then
        Sort(i, r);
    end;
  begin
    Sort(1, sticksNum);
  end;


begin
    while NOT Eof do
      begin
        Readln(sticksNum);
        if sticksNum = 0 then
          Break
        else
          begin
            totalLength := 0;
            FillChar(Length, SizeOf(Length), 0);
            FillChar(group, SizeOf(group), 0);
            FillChar(used, SizeOf(used), False);
            for i := 1 to sticksNum do
              begin
                Read(Length[i]);
                totalLength := totalLength + Length[i];
              end;
            qsort;
            doit;
          end;
      end;
  end.
