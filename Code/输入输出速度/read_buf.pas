var
  n,x,i,t1:longint;
  buf:array [0..10005] of longint;
  begin
  assign(input,'1.in');reset(input);
  assign(output,'read_buf.out');rewrite(output);
  settextbuf(input,buf);
  randomize;t1:=randseed;
  read(n);
  for i:=1 to n do read(x);
  randomize;
  writeln('time=',randseed-t1);
  close(input);close(output);
  end.


