program CQF_LCP;
var x: array[1..500000, 0..18] of int64;
  l2: array[0..500000] of longint;
  ra: array[0..255] of int64;
  a, b, rec, q, i, j, n: longint;
  ch: char;
begin
  for i := 0 to 255 do
    ra[i] := random(int64(1) shl 32) shl 32 + random(int64(1) shl 32);
  readln(n);
  l2[0] := -1;
  for i := 1 to n do
    l2[i] := l2[i - 1] + ord(i and (i xor (i - 1)) = i);
  for i := 1 to n do begin
    read(ch);
    x[i, 0] := ra[ord(ch)];
  end;
  for i := n downto 1 do
    for j := 1 to l2[n + 1 - i] do
      x[i, j] := x[i, j - 1] * ra[j] xor x[i + 1 shl (j - 1), j - 1];
  readln(q);
  for q := 1 to q do begin
    readln(a, b);
    rec := a;
    for j := l2[n] downto 0 do
      if (a + 1 shl j - 1 <= n) and (b + 1 shl j - 1 <= n) and (x[a, j] = x[b, j]) then begin
        inc(a, 1 shl j);
        inc(b, 1 shl j);
      end;
    writeln(a - rec);
  end;
end.


