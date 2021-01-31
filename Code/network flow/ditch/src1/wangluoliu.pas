program wangluoliu;                 {p-!!!}
  const
    maxn=100;   maxmax=999999999;
  var
    c,f:array[1..maxn,1..maxn]of longint;
    n,sq,tq:longint;

  procedure init;       {c,f,n,sq,tq,}
    var i,x,m,y,z:longint;
    begin
      readln(n,m,sq,tq);
      fillchar(f,sizeof(f),0);
      fillchar(c,sizeof(c),0);
      for i:=1 to m do
        begin
          readln(x,y,z);
          c[x,y]:=z;
        end;
    end;

  procedure ford;    {q,p,d,a}
    var
      p,q,d:array[1..maxn]of longint;
      b:array[1..maxn]of boolean;
      i,h,j,t:longint;
      boo:boolean;
    begin
      repeat
        fillchar(b,sizeof(b),false);
{d[]}   fillchar(p,sizeof(p),0);
        d[sq]:=maxmax;
        h:=1;     t:=1;  b[sq]:=true;   q[1]:=sq;
        while (h<=t)and(p[tq]=0) do
          begin
            i:=q[h];
            for j:=1 to n do
            if not b[j] then
            begin
              boo:=false;
              if (c[i,j]>0)and(f[i,j]<c[i,j])
                then begin d[j]:=c[i,j]-f[i,j];boo:=true;end else
              if (c[j,i]>0)and(f[j,i]>0)
                then begin d[j]:=f[j,i];boo:=true;end;
              if boo then begin
                            if d[j]>d[i] then d[j]:=d[i];
                            p[j]:=i;
                            inc(t);
                            q[t]:=j;
                            b[j]:=true;
                          end;
            end;
            inc(h);
          end;

        j:=tq;
        while p[j]<>0 do
        begin
          i:=p[j];
          f[i,j]:=f[i,j]+d[tq];
          f[j,i]:=-f[i,j];                  // ?????
          j:=i;
        end;
      until p[tq]=0;
    end;

  procedure answer;
    var i,j,tot:longint;
    begin
      tot:=0;
      for i:=1 to n do
      if f[sq,i]>0 then
        tot:=tot+f[sq,i];
      writeln(tot);
      writeln;
      tot:=0;
      for i:=1 to n do
        if f[i,tq]>0 then
        tot:=tot+f[i,tq];
      writeln(tot);
      for i:=1 to n do
        begin
        for j:=1 to n do
          write(f[i,j]:4);
        writeln;
        end;
    end;

  begin
    init;
    ford;
    answer;
  end.