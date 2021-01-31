program pair_heap;
const
        full_size = 1001;
type
        href=word;
        node = record
                key:integer;
                p,n,ch:href;
        end;
var
  a:array[0..full_size] of node;
        tmp:array[0..full_size] of integer;
        size,root:integer;function merge(x,y:href):integer;
begin
        if (a[x].key <= a[y].key) then begin
                a[y].p := x;             a[y].n := a[x].ch;
                a[a[y].n].p := y;
                a[x].ch := y;            a[x].p := 0;
                a[x].n := 0;
                exit(x);
        end else begin
                a[x].p := y;             a[x].n := a[y].ch;
                a[a[x].n].p := y;
                a[y].ch := x;            a[y].p := 0;
                a[y].n := 0;
                exit(y);
        end
end;procedure Push(x:integer);
begin
        if (size = 0) then begin
                 root := 1;
                 size := 1;
                 a[size].key := x;
                 a[size].p := 0;
                 a[size].n := 0;
                 a[size].ch := 0;
        end else begin
           size := size + 1;
                 a[size].key := x;
                 a[size].ch := 0;
                 root := Merge(root, size);
        end;
end;
function min:integer;
begin
  exit(a[root].key);
end;function combine(x:integer):integer;
var cur,n:integer;
begin
   if a[x].n=0 then exit(x);
         n:=0;
         while x<>0 do begin
           n:=n+1;
                 tmp[n]:=x;
                 a[a[x].p].n:=0;
                 x:=a[x].n
         end;
   cur:=1;
         while cur+1<=n do begin
           tmp[cur]:=merge(tmp[cur],tmp[cur+1]);
                 cur:=cur+2;
         end;
         if not odd(n) then cur:=cur-2;
         while cur>1 do begin
            tmp[cur-2]:=merge(tmp[cur-2],tmp[cur]);
                        cur:=cur-2;
         end;
         exit(tmp[1]);
end;procedure DelMin;
var
         newroot:integer;
begin
   if root<=0 then exit;
         newroot:=0;
         if a[Root].ch > 0 then
                NewRoot := Combine(a[root].ch);   Dec(size);       Root := NewRoot;end;
function popmin:integer;
var m:integer;
begin
   m:=min;
         delmin;
         exit(m);
end;begin
   root:=0;
         size:=0;
         push(3);
         push(1);
         push(2);
         writeln(popmin);
         writeln(popmin);
         writeln(min);
end.
