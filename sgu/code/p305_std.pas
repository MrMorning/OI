program SGU305;
//   Accept.
{$I-,S-,Q-,R-}

const
  inf = 't.in';
  ouf = '';
  maxn = 500;
  modes = 10417;

type integer = longint;

var a, b, x, num, tow, next: array[1 .. maxn] of integer;
    hash: array[0 .. modes] of integer;
    visit: array[0 .. maxn] of boolean;
    n, m, tot: integer;

procedure prepare;
var i: integer;
begin
  read(n, m);
  for i := 1 to n do read(a[i], b[i]);
end;

function get(u: integer): integer;
var r, tmp: integer;
begin
  r := (u - u div modes + modes) mod modes;
  tmp := hash[r];
  while tmp <> 0 do begin
    if num[tmp] = u then begin
      get := tmp;
      exit;
    end;
    tmp := next[tmp];
  end;
  tot := tot + 1;
  num[tot] := u; next[tot] := hash[r];
  hash[r] := tot; get := tot;
end;

function find(i: integer): boolean;
var u, k: integer;
begin
  find := false;
  if a[i] = 0 then begin
    k := b[i];
    if (k < 1) or (k > m) then exit
  end else if a[i] > 0 then begin
    k := - b[i] div a[i] - 1;
    while a[i] * k + b[i] < 1 do k := k + 1;
    if k < 0 then k := 0;
  end else begin
    k := (m - b[i]) div a[i] - 1;
    while a[i] * k + b[i] > m do k := k + 1;
    if k < 0 then k := 0;
  end;
  while (a[i] * k + b[i] > 0) and (a[i] * k + b[i] <= m) do begin
    u := get(a[i] * k + b[i]);
    if not visit[u] then begin
      visit[u] := true;
      if (tow[u] = 0) or find(tow[u]) then begin
        tow[u] := i;
        x[i] := u;
        find := true; exit;
      end;
    end;
    if a[i] = 0 then break else k := k + 1;
  end;
end;

procedure main;
var i, u, k, cnt: integer;
begin
  fillchar(x, sizeof(x), 0);
  fillchar(num, sizeof(num), 0);
  fillchar(tow, sizeof(tow), 0);
  fillchar(hash, sizeof(hash), 0);
  fillchar(next, sizeof(next), 0);
  tot := 0;
cnt := 0;
  for i := 1 to n do if x[i] = 0 then begin
    fillchar(visit, sizeof(visit), false);
cnt := cnt + ord(find(i));
  end; k := 0;
  for i := 1 to n do if x[i] = 0 then
    repeat
      k := k + 1;
      u := get(k);
      if tow[u] = 0 then begin
        tow[u] := i;
        x[i] := u;
      end;
    until x[i] > 0;
  //for i := 1 to n do write(num[x[i]], ' '); writeln;
	writeln(cnt);
end;

begin
  assign(input, inf); assign(output, ouf);
  reset(input); rewrite(output);
  while not seekeof do begin
    prepare;
    main;
  end;
  close(input); close(output);
end.
