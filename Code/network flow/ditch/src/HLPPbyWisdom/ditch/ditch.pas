const maxn=3010; inf='ditch.in'; ouf='ditch.out';
type list=record num:integer; a:array[1..maxn] of integer; end;
var n,m,max:longint;
    r:array[1..maxn,1..maxn] of longint;
    g:array[1..maxn,1..maxn] of integer;
    d,cur:Array[1..maxn] of integer;
    h:array[1..maxn] of integer;
    L:array[0..maxn*2-1] of list;
    e:array[1..maxn] of longint;
    Buf:Array[1..10000] of char;

procedure Init;
var i,j,a,b,w:longint;
begin
  Assign(Input,inf);
  SetTextBuf(Input,Buf);
  reset(Input);
  readln(m,n);
  fillchar(r,sizeof(r),0);
  for i := 1 to m do begin
    readln(a,b,w);
    Inc(r[a,b],w);
  end;
  Close(Input);
  for i := 1 to n do begin
    for j := i+1 to n do begin
      if (r[i][j]>0) or (r[j][i]>0) then begin
        Inc(d[i]); Inc(d[j]);
        g[i,d[i]] := j;  g[j,d[j]] := i;
      end;
    end;
  end;
  for i := 1 to n do cur[i] := 1;
  for i := 0 to 2*n-1 do L[i].num := 0;
end;

procedure Insert(level,x:integer);
begin
  with L[level] do begin
    Inc(num);
    a[num] := x;
  end;
end;

procedure Bfs;
const limit=maxn*2;
var p,q,i:integer;
    x:array[1..maxn] of integer;
begin
  for i := 1 to n do h[i] := limit;
  x[1] := n; h[n] := 0; q := 1; p := 0;
  repeat
    Inc(p);
    for i := 1 to d[x[p]] do begin
      if h[g[x[p],i]]=limit then begin
        Inc(q); x[q] := g[x[p],i];
        h[x[q]] := h[x[p]] + 1;
        if x[q]>1 then Insert(h[x[q]],x[q]);
      end;
    end;
  until p>=q;
  h[1] := n;
end;

procedure Push(a,b:integer);
var x:longint;
begin
  if r[a,b]>e[a] then x := e[a] else x := r[a,b];
  Dec(r[a,b],x); Inc(r[b,a],x);
  Dec(e[a],x);   Inc(e[b],x);
end;

procedure Relabel(a:integer);
var i,min:integer;
begin
  min := maxint;
  for i := 1 to d[a] do begin
    if (r[a,g[a,i]]>0) and (h[g[a,i]]<min) then min := h[g[a,i]];
  end;
  h[a] := min+1;
end;

function Check(a:integer):boolean;
begin
  Check := false;
  while e[a]>0 do begin
    if cur[a]>d[a] then begin
      Relabel(a);  Check := true; cur[a] := 1;
    end else begin
      if (r[a,g[a,cur[a]]]>0) and (h[a]=h[g[a,cur[a]]]+1) then Push(a,g[a,cur[a]])
        else Inc(cur[a]);
    end;
  end;
end;

procedure Update(level:integer);
var j,k:integer;
begin
  for j := level+1 to n do begin
    for k := 1 to L[j].num do begin
      L[n+1].a[L[n+1].num+k] := L[j].a[k];
      h[L[j].a[k]] := n+1;
    end;
    Inc(L[n+1].num,L[j].num);
    L[j].num := 0;
  end;
end;

procedure Flow;
var i,level:integer;
begin
  level := n;
  repeat
    Dec(level);
    with L[level] do begin
      for i := num downto 1 do begin
        if Check(a[i]) then begin
          if (level>0) and (num=1) then Update(level);
          Insert(h[a[i]],a[i]);
          level := h[a[i]];
          a[i] := a[num];  Dec(num);
          break;
        end;
      end;
    end;
  until level=0;
end;

procedure PreFlow;
var i,b:integer;
begin
  for i := 1 to d[1] do begin
    b := g[1,i];
    e[b] := r[1,b]; Dec(e[1],r[1,b]);
    r[b,1] := e[b];
    r[1,b] := 0;
  end;
end;

begin
  Init;
  Bfs;
  PreFlow;
  Flow;
  Assign(Output,ouf);
  rewrite(output);
  writeln(e[n]);
  Close(Output);
end.

