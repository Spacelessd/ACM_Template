const
  maxN = 13;
  base = 13;
  prim = 199991;
  maxH = 4000000;

type
  TArr = array [1..maxN] of longint;

  PData = ^TData;
  TData = record
    v: TArr;
    prev: PData;
    sum,dep: longint;
  end;

  PHash = ^THash;
  THash = record
    v: TArr;
    next: PHash;
    dep: longint;
  end;

var
  hash: array [0..prim] of PHash;
  heap: array [1..maxH] of PData;
  seq: array [1..maxN] of longint;
  sa,sb: array [1..maxN*maxN] of longint;
  htop,n,m,nAvg,avg,sum: longint;

function getCost(var v: TArr): longint;
var
  i: longint;
begin
  getCost:=0;
  for i:=1 to n do
    if v[i]<>i then
      inc(getCost);
end;

function getHash(var v: TArr): longint;
var
  i: longint;
begin
  getHash:=0;
  for i:=1 to n do
    getHash:=(getHash*base+v[i]) mod prim;
end;

function hashIns(var v: TArr;dep: longint): boolean;
var
  p: PHash;
  flag: boolean;
  hv,i,tot: longint;
begin
  hv:=getHash(v);
  p:=hash[hv];tot:=0;
  while p<>nil do
  begin
    inc(tot);
    flag:=true;
    for i:=1 to n do
      if v[i]<>p^.v[i] then
      begin
        flag:=false;
        break;
      end;
    if flag then
      if p^.dep<=dep then
        exit(false)
      else begin
        p^.dep:=dep;
        exit(true);
      end
    else
      p:=p^.next;
  end;
  inc(avg,tot);
  inc(nAvg);
  new(p);
  p^.v:=v;
  p^.next:=hash[hv];
  hash[hv]:=p;
  exit(true);
end;

procedure heapIns(p: PData);
var
  now: longint;
begin
  inc(htop);
  now:=htop;
  while now<>1 do
    if heap[now div 2]^.sum>p^.sum then
    begin
      heap[now]:=heap[now div 2];
      now:=now div 2;
    end
    else
      break;
  heap[now]:=p;
end;

procedure heapDel;
var
  p: PData;
  now,min: longint;
begin
  p:=heap[htop];
  dec(htop);now:=1;
  while now*2<=htop do
  begin
    min:=now*2;
    if (min+1<=htop) and (heap[min+1]^.sum<heap[min]^.sum) then
      inc(min);
    if heap[min]^.sum<p^.sum then
    begin
      heap[now]:=heap[min];
      now:=min;
    end
    else
      break;
  end;
  heap[now]:=p;
end;

function make(var v: TArr;dep: longint;prev: PData): PData;
var
  p: PData;
  cst: longint;
begin
  new(p);
  make:=p;
  p^.v:=v;
  p^.dep:=dep;
  cst:=getCost(v);
  if cst=0 then
  begin
    writeln(dep);
    close(input);
    close(output);
    halt;
  end;
  p^.sum:=getCost(v)+dep;
  p^.prev:=prev;
  exit(p);
end;

procedure swap(var a,b: longint);
var
  t: longint;
begin
  t:=a;
  a:=b;
  b:=t;
end;

var
  p: PData;
  i: longint;
begin
  //assign(input,'1.in');reset(input);
  //assign(output,'1.out');rewrite(output);
  readln(n,m);
  for i:=1 to n do
    read(seq[i]);
  for i:=1 to m do
    readln(sa[i],sb[i]);

  heapIns(make(seq,0,nil));
  while htop<>0 do
  begin
    p:=heap[1];heapDel;
    for i:=1 to m do
    begin
      swap(p^.v[sa[i]],p^.v[sb[i]]);
      if hashIns(p^.v,p^.dep+1) then
      begin
        inc(sum);
        heapIns(make(p^.v,p^.dep+1,p));
      end;
      swap(p^.v[sa[i]],p^.v[sb[i]]);
    end;
  end;
end.


