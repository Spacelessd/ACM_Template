var
  a,l,r,p,print:array[1..100000]of longint;
  i,n,root,j,p1,len:longint;
  procedure out(x:longint);
    begin
    if x=0 then exit;
    out(l[x]);
    inc(p1);
    print[p1]:=a[x];
    //write(a[x],' ');
    out(r[x]);
    end;
    
  function search(x,k:longint):longint;
  var
    i:longint;
    begin
    i:=x;
    while (i<>0)and(a[i]<>k)do
      if k<a[l[i]] then i:=l[i]
        else i:=r[i];
    exit(i);
    end;
  
  
  function fmin(x:longint):longint;
  var
    i:longint;
    begin
    i:=x;
    while (l[i]<>0)do i:=l[i];
    exit(i);
    end;
    
  function fmax(x:longint):longint;
  var
    i:longint;
    begin
    i:=x;
    while (r[i]<>0)do i:=r[i];
    exit(i);
    end; 
    
  function next(x:longint):longint;
  var
    y:longint;
    begin
    if r[x]<>0 then exit(fmin(r[x]));
    y:=p[x];
    while (y<>0)and(x=r[y])do 
      begin
      x:=y;
      y:=p[y];
      end;
    exit(y);
    end; 
    
  procedure insert(c,z:longint);
  var
    x,y:longint;
    begin
    l[z]:=0;r[z]:=0;a[z]:=c;
    y:=0;
    x:=root;
    while x<>0 do
      begin
      y:=x;
      if a[z]<a[x] then x:=l[x]
        else x:=r[x];
      end;
    p[z]:=y;
    if y=0 then root:=z
      else if a[z]<a[y] then l[y]:=z
        else r[y]:=z;
    end;
  
  
  procedure delete(z:longint);
  var
    x,y:longint;
    begin
    if (l[z]=0)or(r[z]=0) then y:=z
    else y:=next(z);
   
   if l[y]<>0 then x:=l[y]
     else x:=r[y];
   if x<>0 then p[x]:=p[y];
   if p[y]=0 then root:=x
     else if y=l[p[y]]then l[p[y]]:=x
       else r[p[y]]:=x;
   if y<>z then begin
     a[z]:=a[y];    
     p[z]:=p[y];
     l[z]:=l[y];
     r[z]:=r[y];
     end;
   end;
    
    
  begin
  readln(n);
  for i:=1 to n do
    begin
    read(j);
    insert(j,i);
    end;
  p1:=0;
  out(root);
  for i:=1 to p1-1 do write(print[i],' ');
  writeln(print[p1]);
  end.
  
  
  
  
  
  
  
  
  
  
  
  
  