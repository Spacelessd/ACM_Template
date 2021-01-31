program maxflow;
  const
    maxn=100;
    maxmax=maxint;
  var
    f,c     :array[1..maxn,1..maxn]of longint;
    n,tq,sq :longint;

  procedure init;  //c,f,n,tq,sq
    var
      u,v,p:longint;
    begin
      fillchar(f,sizeof(f),0);
      fillchar(c,sizeof(c),0);
      readln(n,sq,tq);
      while not eof do
      begin
        readln(u,v,p);
        c[u,v]:=p;
      end;
    end;

  procedure ford;
    var
      pr,q :array[1..maxn]of longint;
      ruq  :array[1..maxn]of boolean;
      i,j,d,t,h,k:longint;
    begin
      repeat
        fillchar(ruq,sizeof(ruq),false);  ruq[sq]:=true;
        fillchar(pr ,sizeof(pr) ,0);
        h:=1; t:=1; q[1]:=sq;
        while (h<=t)and(pr[tq]=0) do
        begin
          i:=q[h];
          for j:=1 to n do
          if not ruq[j] then
          if f[i,j]<c[i,j] then begin
                                  inc(t);
                                  q[t]:=j;
                                  ruq[j]:=true;
                                  pr[j]:=i;
                                end else
          if f[j,i]>0 then begin
                             inc(t);
                             q[t]:=j;
                             ruq[j]:=true;
                             pr[j]:=-i;
                           end;

          inc(h);
        end;
        if pr[tq]<>0 then
        begin
          d:=maxmax; j:=tq; i:=abs(pr[j]);
          while i<>0 do
          begin
            if pr[j]>0 then k:=c[i,j]-f[i,j]
                       else k:=f[j,i];
            if d>k then d:=k;
            j:=i; i:=abs(pr[j]);
          end;

          j:=tq; i:=abs(pr[j]);
          while i<>0 do
          begin
            if pr[j]>0 then f[i,j]:=f[i,j]+d
                       else f[j,i]:=f[j,i]-d;
            j:=i; i:=abs(pr[j]);
          end;
        end;
      until pr[tq]=0;
    end;

  procedure answer;
    var tot,i:longint;
    begin
      tot:=0;
      for i:=1 to n do
        if f[sq,i]>0 then tot:=tot+f[sq,i];
      writeln(tot);
    end;

  begin
    init;
    ford;
    answer;
  end.