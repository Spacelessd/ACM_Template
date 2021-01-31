type node=record
      f,lc,rc,key:longint;
      fix:extended;
     end;
 
var a:array[1..100000]of node;
    n,m,root:longint;
 
function search(x,k:longint):longint;
 begin
  if k=0 then exit(0);
  if a[k].key=x then exit(k);
  if a[k].key>x then exit(search(x,a[k].lc));
  if a[k].key<x then exit(search(x,a[k].rc));
 end;
 
procedure rotate_left(var k:longint);
 var y:longint;
 begin
  y:=a[k].rc;
  a[k].rc:=a[y].lc;
  if a[y].lc>0 then a[a[y].lc].f:=k;
  a[y].f:=a[k].f;
  if a[k].f=0
   then root:=y
   else if k=a[a[k].f].lc
    then y:=a[a[k].f].lc
    else y:=a[a[k].f].rc;
  k:=a[y].lc;
  a[k].f:=y;
 end;
 
procedure rotate_right(var k:longint);
 var y:longint;
 begin
  y:=a[k].lc;
  a[k].lc:=a[y].rc;
  if a[y].rc>0 then a[a[y].rc].f:=k;
  a[y].f:=a[k].f;
  if a[k].f=0
   then root:=y
   else if k=a[a[k].f].lc
    then y:=a[a[k].f].lc
    else y:=a[a[k].f].rc;
  k:=a[y].rc;
  a[k].f:=y;
 end;
 
procedure insert(x,k:longint);
 var tmp:longint;
 begin
  if a[k].key>x then
   begin
    if a[k].lc=0 then
     begin
      inc(n);
      a[n].f:=k;
      a[n].key:=x;
      randomize;
      a[n].fix:=random;
      a[k].lc:=n;
	  tmp:=a[n].f;
      if a[n].fix<a[tmp].fix then rotate_right(tmp);
	  a[n].f:=tmp;
     end
    else insert(x,a[k].lc);
   end;
  if a[k].key<x then
   begin
    if a[k].rc=0 then
     begin
      inc(n);
      a[n].f:=k;
      a[n].key:=x;
      randomize;
      a[n].fix:=random;
      a[k].rc:=n;
	  tmp:=a[n].f;
      if a[n].fix<a[tmp].fix then rotate_left(tmp);
	  a[n].f:=tmp;
     end
    else insert(x,a[k].rc);
  end;
 end;
 
procedure remove(k:longint);
 begin
  while (a[k].lc>0)or(a[k].rc>0) do
   begin
    if a[k].lc=0 then
     begin 
      rotate_left(k);
      continue;
     end;
   if a[k].rc=0 then
    begin
     rotate_right(k);
     continue;
    end;
   if a[a[k].lc].fix>a[a[k].rc].fix
    then rotate_left(k)
    else rotate_right(k);
  end;
  if a[a[k].f].lc=k
   then a[a[k].f].lc:=0
   else a[a[k].f].rc:=0;
 end;
 
procedure init;
 var i,x,o:longint;
 begin
  fillchar(a,sizeof(a),0);
  readln(o,m);
  read(x);
  a[1].key:=x;
  n:=1;
  root:=1;
  for i:=2 to o do
   begin
    read(x);
    insert(x,root);
   end;
  readln;
 end;
 
procedure main;
 var i,p,q:longint;
     ch,space:char;
 begin
  for i:=1 to m do
   begin
    read(ch);
    read(space);
    readln(p);
    case ch of
     'I':insert(p,root);
     'S':begin
          q:=search(p,root);
          if q=0 then writeln('NO') else writeln('YES');
         end;
     'D':begin
          q:=search(p,root);
          remove(q);
         end; 
    end;
   end;
 end;
 
begin
 init;
 main;
end.