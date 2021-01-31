const d = 4;
var x: array[1..200000, 0..17 - d] of longint;
  ra: array[0..255] of longint;
  l2, w: array[0..200000] of longint;
  i, j, k, n, q, rec, tt: longint;
  ch: char;
  s: ansistring;

procedure cal(j, k: longint);
begin
  for j := j to k do
    x[w[i], j] := x[w[i], j - 1] * ra[j] xor x[w[i + 1 shl (j - 1)], j - 1];
end;
begin
  readln(n, q);
  for i := 0 to 255 do
    ra[i] := random(int64(1) shl 32);
  for i := 1 to n do begin
    read(ch);
    x[i, 0] := ra[ord(ch)];
    w[i] := i;
  end;
  readln;
  l2[0] := -1;
  for i := 1 to 200000 do
    l2[i] := l2[i - 1] + ord(i and (i xor (i - 1)) = i);
  for i := n downto 1 do
    cal(1, l2[n - i + 1] - d);
  tt := n;
  for q := 1 to q do begin
    read(ch);
    case ch of
      'L': begin
          readln(i, j);
          rec := i;
          for k := l2[n] downto 0 do
            while ((k = 0) or (k <= l2[n - i + 1] - d) and (k <= l2[n - j + 1] - d)) and
              (i <= n) and (j <= n) and (x[w[i], k] = x[w[j], k]) do begin
              inc(i, 1 shl k);
              inc(j, 1 shl k);
            end;
          writeln(i - rec);
        end;
      'A': begin
          readln(k, ch, s);
          move(w[k], w[k + length(s)], (n - k + 1) * sizeof(w[k]));
          inc(n, length(s));
          for i := k + length(s) - 1 downto k do begin
            inc(tt);
            w[i] := tt;
            x[w[i], 0] := ra[ord(s[i - k + 1])];
            cal(1, l2[n - i + 1] - d);
          end;
          for i := k - 1 downto 1 do
            if l2[k - i] < l2[n - length(s) - i + 1] - d then
              cal(l2[k - i] + 1, l2[n - i + 1] - d)
            else
              cal(l2[n - length(s) - i + 1] - d + 1, l2[n - i + 1] - d);
        end;
      'C': begin
          readln(j, k, ch, s);
          for i := k downto j do begin
            x[w[i], 0] := ra[ord(s[i - j + 1])];
            cal(1, l2[n - i + 1] - d);
          end;
          for i := j - 1 downto 1 do
            cal(l2[j - i] + 1, l2[n - i + 1] - d);
        end;
      'D': begin
          readln(j, k);
          move(w[k + 1], w[j], (n - k) * sizeof(w[k]));
          dec(n, k - j + 1);
          for i := j - 1 downto 1 do
            cal(l2[j - i] + 1, l2[n - i + 1] - d);
        end;
    end;
  end;
end.


