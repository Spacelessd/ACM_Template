var
  n,x,i,t1,len:longint;
  fin,fout:file;
  a:array[0..100*1024*1024] of byte;
  begin
  randomize;t1:=randseed;
  for i:=1 to 10 do
    begin
    assign(fin,'1.in');reset(fin,1);
    blockread(fin,a,sizeof(a),len);
    close(fin);
    end;
  randomize;
  assign(output,'block_read.out');rewrite(output);
  writeln('time=',randseed-t1);
  close(output);

  randomize;t1:=randseed;
  for i:=1 to 1 do
    begin
    assign(fout,'1.out');rewrite(fout,1);
    blockwrite(fout,a,len,len);
    close(fout);
    end;
  randomize;
  assign(output,'block_write.out');rewrite(output);
  writeln('time=',randseed-t1);
  close(output);
  end.


