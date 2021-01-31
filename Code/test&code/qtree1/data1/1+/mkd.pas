var
  i,n,x,y,t,i1,max:longint;
  begin
  randomize;
  assign(output,'1.in');rewrite(output);
  //t:=random(20)+1;
  max:=10;
  t:=1;
  writeln(t);
  for i1:=1 to t do
  begin
  n:=max;
  writeln(n);
  for i:=2 to n do writeln(i,' ',random(i-1)+1,' ',raNDOM(10));
  for i:=1 to max do
    begin
    if random(2)=1 then begin
    x:=random(n)+1;
    y:=random(n)+1;
    while x=y do
      begin
      x:=random(n)+1;
      y:=random(n)+1;
      end;
    writeln('QUERY ',x,' ',y);
    end
    else begin

    writeln('CHANGE ',random(n-1)+1,' ',random(10));
    end
    end;
    WRITELN('DONE');
  end;
  close(output);
  end.
