var
  i:longint;
  begin
  assign(output,'1.out');rewrite(output);
  for i:=1 to 255 do write(chr(i));
  close(output);
  end.




