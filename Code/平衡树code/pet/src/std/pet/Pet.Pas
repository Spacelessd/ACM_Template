{$r-,s-,q-}

const
  inf='pet.in';
  ouf='pet.out';
  mask=1 shl 12-1;
  maxk=10005;
  base=1000000;
var
  bill,key :array[0..maxk] of longint;
  v :array[0..maxk] of integer;
  ran :array[0..mask] of longint;
  next :array[0..maxk,0..1] of integer;
  b,n,sum,min,d,i :longint;
  sign,a,t,k,head,u,fu,tail :integer;

procedure rotate(var x :integer; a :byte);
var tmp :integer;
begin
  tmp:=next[x,a];
  next[x,a]:=next[tmp,1-a];
  next[tmp,1-a]:=x;
  x:=tmp;
end;

procedure insert(var x :integer; k :integer);
var a :byte;
begin
  a:=ord(b>key[x]);
  if next[x,a]=0 then next[x,a]:=k else insert(next[x,a],k);
  if bill[next[x,a]]<bill[x] then rotate(x,a);
end;

procedure shift(var x :integer);
var a :byte;
begin
  a:=ord(next[x,0]>next[x,1]);
  if bill[x]<bill[next[x,a]] then exit;
  rotate(x,a);
  shift(next[x,1-a]);
end;

procedure trade(var x :integer; y :integer);
var tmp :integer;
    a :byte;
begin
  d:=abs(key[x]-b);
  if (d<min)or(d=min)and(key[x]-b<0) then begin
    min:=d; u:=x; fu:=y;
  end;
  a:=ord(b>=key[x]);
  if next[x,a]=0 then begin
    key[u]:=key[x];
    bill[u]:=bill[x];
    tmp:=x;
    x:=next[x,1-a];
    if tmp<>u then
      if fu=0 then shift(head) else
      shift(next[fu,ord(u=next[fu,1])]);
    v[tail]:=tmp;
    dec(tail);
  end else trade(next[x,a],x);
end;

begin
  randomize;
  bill[0]:=maxlongint;
  for i:=0 to mask do
    ran[i]:=longint(random(maxint))*random(maxint);
  assign(input,inf); reset(input);
  readln(n);
  sign:=0; t:=0; tail:=0;
  for i:=1 to maxk do v[i]:=i;
  for i:=1 to n do begin
    read(a,b);
    if (t=0)or(a=sign) then begin
      inc(tail); k:=v[tail];
      key[k]:=b;
      bill[k]:=ran[i and mask];
      next[k,0]:=0;
      next[k,1]:=0;
      if t=0 then head:=k else insert(head,k);
      sign:=a; inc(t);
    end else begin
      min:=maxlongint;
      trade(head,0);
      sum:=(sum+min) mod base;
      dec(t);
    end;
  end;
  close(input);
  assign(output,ouf); rewrite(output);
  writeln(sum);
  close(output);
end.
