var
  tmp,t,k,n,q,i,j,z,x,y,x1,y1,x2,y2:longint;
procedure swap(var x,y:longint);
begin
  tmp:=x; x:=y; y:=tmp;
end;
begin
  assign(output,'1.in'); rewrite(output);
  randomize;
  t:=1; writeln(t);
  for k:=1 to t do
   begin
    n:=2; q:=2; writeln(n,' ',q);
    for i:=1 to n do
      begin
        for j:=1 to n do write(chr(random(26)+65));
        writeln;
      end;
    for i:=1 to q do
      begin
         z:=random(2);
         if z=1 then
           begin
             x1:=random(n); y1:=random(n);
             x2:=random(n); y2:=random(n);
             if (x1>x2) then swap(x1,x2);
             if (y1>y2) then swap(y1,y2);
             writeln(z,' ',x1,' ',y1,' ',x2,' ',y2);
             continue;
           end;
         write(z,' ',random(2),' ',random(n),' ');
         for j:=1 to n do write(chr(random(26)+65));
         writeln;
      end;
    end;
  close(output);
end.
