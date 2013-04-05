Program p1002;

Const
  MaxNodeNum = 2 * 10000000 - 1;
Type
  TNode = Record
    times: Longint;
    Data: String;
  End;
Var
  Node: Array[1..MaxNodeNum] Of TNode;
  N, i, printtimes: Longint;
  s, phonenum: String;
  NodeNum: Longint;

Function find(s : String; root : Longint): Boolean;
  Begin
    If root > NodeNum Then
      Exit(FALSE);
    If Node[root].Data = '' Then
      Exit(FALSE);
    With Node[root] Do
      Begin
        If Data = s Then
          Begin
            Inc(times);
            Exit(TRUE);
          End
        Else
          Begin
            If s < Data Then
              Exit(find(s, 2 * root))
            Else
              Exit(find(s, 2 * root + 1));
          End;
      End;
  End;

Procedure Insert(s : String; root : Longint);
  Begin
    If root > NodeNum Then
      Exit;
    With Node[root] Do
      If Data = '' Then
        Begin
          Data := s;
          Inc(times);
        End
    Else
      Begin
        If s < Data Then
          Insert(s, root * 2)
        Else
          Insert(s, root * 2 + 1);
      End;
  End;

Procedure Print(root : Longint);
  Begin
    If root > NodeNum Then
      Exit;
    With Node[root] Do
      If Data = '' Then
          Exit
    Else If times = 1 Then
      Begin
        Print(root * 2);
        Print(root * 2 + 1);
      End
    Else
      Begin
        Print(root * 2);
        Writeln(Copy(Data, 1, 3), '-', Copy(Data, 4, 4), ' ', times);
        Inc(printtimes);
        Print(root * 2 + 1);
      End;
  End;

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

Begin
    Readln(N);
    NodeNum := N * 2 - 1;
    For i := 1 To N Do
      Begin
        Readln(s);
        phonenum := convert(s);
        If NOT find(phonenum, 1) Then
          Insert(phonenum, 1);
      End;
    printtimes := 0;
    Print(1);
    If printtimes = 0 Then
      Writeln('No duplicates.');
  End.
