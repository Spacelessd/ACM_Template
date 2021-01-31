{$inline on}
var
  n,x,i,t1,len:longint;
  fin:file;
  a:array[0..100*1024*1024] of byte;
  p:^byte;
  s:int64;
  procedure read_int(var x:longint);inline;
    begin
    x:=0;
    while (p^<>0)and((p^<48)or(p^>57)) do inc(p);
    while (p^>=48)and(p^<=57) do
      begin
      x:=x*10+p^-48;inc(p);
      end;
    end;
  begin
  randomize;t1:=randseed;
  for i:=1 to 1 do
    begin
    assign(fin,'1.in');reset(fin,1);
    blockread(fin,a,sizeof(a),len);
    close(fin);
    end;
  assign(output,'blockread.out');rewrite(output);
  p:=a;s:=0;read_int(n); writeln('n=',n);
  for i:=1 to n do
    begin
    read_int(x);
    s:=s+x;
    //writeln(x);
    end;
  writeln('s=',s);
  randomize;
  writeln('time=',randseed-t1);
  close(output);
  end.


