var
  i,n,x,y,t,i1,j:longint;
  begin
  randomize;
  assign(output,'1.in');rewrite(output);
  //t:=random(20)+1;
  t:=20;
  writeln(t);
  for i1:=1 to t do
  begin
  n:=10000;
  writeln(n);
  writeln(1,' ',2,' ',random(100000));
  for i:=3 to n do
    begin
    j:=i-random(5)-1;
    if (j<1) then j:=1;
    j:=2;
    writeln(i,' ',j,' ',raNDOM(100000));
    end;
  for i:=1 to 10000 do
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

    writeln('CHANGE ',{random(n-1)+}1,' ',random(100000));
    end
    end;
    WRITELN('DONE');
  end;
  close(output);
  end.
