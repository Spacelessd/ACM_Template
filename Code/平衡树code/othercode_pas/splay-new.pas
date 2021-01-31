{$M 1000000000}
type
  splaya=record
    l,r,key,size,p,sum,delta:int64;
    end;
var
  a:array[0..1000000]of splaya;
  root,n,j,q,x,y,z,ll:int64;
  i:longint;
  ch:char;
  procedure update(x:int64);//每次旋转完更新节点的两个域
    begin
    a[x].size:=a[a[x].l].size+a[a[x].r].size+1;
    a[x].sum:=a[a[x].l].sum+a[a[x].r].sum+a[x].key;
    
    end;
  
  procedure build(l,r:int64);//一开始先用递归建立伸展树,而不是一个个插入完再splay,这样省空间又省时间,不然有可能爆栈
  var
    mid,tmp:int64;
    begin
    mid:=(l+r)shr 1;
    if l<mid then begin
      build(l,mid-1);
      tmp:=(l+mid-1)shr 1;
      a[mid].l:=tmp;
      a[tmp].p:=mid;
      end;
      
    if r>mid then begin
      build(mid+1,r);
      tmp:=(mid+1+r)shr 1;
      a[mid].r:=tmp;
      a[tmp].p:=mid;
      end;
    update(mid);
    end;
    
  
  procedure clean(x,k:int64);//从x开始向下推标签,直到k
    begin
    repeat
    if a[x].delta<>0 then begin
      inc(a[a[x].l].delta,a[x].delta);
      inc(a[a[x].r].delta,a[x].delta);
      inc(a[a[x].l].sum,a[a[x].l].size*a[x].delta);
      inc(a[a[x].r].sum,a[a[x].r].size*a[x].delta);
      a[x].key:=a[x].key+a[x].delta;
      a[x].delta:=0;
      end;
    if x=k then exit;
    if {a[x].key>a[k].key}x>k then x:=a[x].l
      else x:=a[x].r;
    until false;
    end;
  
procedure rightrotate(x:int64);
var
	y,z:int64;
begin
	y:=a[x].p;
	z:=a[y].p;
	if a[z].l=y then a[z].l:=x
		else a[z].r:=x;
	a[x].p:=z;
	a[y].p:=x;
	a[y].l:=a[x].r;
	a[x].r:=y;
	a[a[y].l].p:=y;
	update(y);
end;

procedure leftrotate(x:int64);
var
	y,z:int64;
begin
	y:=a[x].p;
	z:=a[y].p;
	if a[z].l=y then a[z].l:=x
		else a[z].r:=x;
	a[x].p:=z;
	a[y].p:=x;
	a[y].r:=a[x].l;
	a[x].l:=y;
	a[a[y].r].p:=y;
	update(y);
end;

procedure splay(var root,x:int64);
var
tmp:int64;
begin
//writeln(a[root].p);
tmp:=a[root].p;
	while a[x].p<>tmp do
		if a[a[x].p].l=x then rightrotate(x)
			else leftrotate(x);
	root:=x;
end;

 procedure insert(var root:int64;z:int64);
  var
    x,y:int64;
    begin
    y:=0;
    x:=root;
    while x<>0 do
      begin
      y:=x;
      if a[z].key<a[x].key then x:=a[x].l
        else x:=a[x].r;
      end;
    a[z].p:=y;
    if y=0 then root:=z
      else if a[z].key<a[y].key then a[y].l:=z
        else a[y].r:=z;
    end;


function find(t,x:int64):int64;
begin
        while t<>0 do
        begin
                if x=a[t].key then exit(t)
                else if x<a[t].key then
                        t:=a[t].l
                else t:=a[t].r
        end;
        splay(root,x);
end;

procedure delete(var t:int64; k:int64);
var
	x,lson,rson:int64;
begin
	x:=find(t,k);
	splay(root,x);
	lson:=a[x].l;
	rson:=a[x].r;
	a[lson].p:=0;	a[rson].p:=0;
	a[x].l:=0;	a[x].r:=0;
	if lson=0 then root:=rson
	else begin
		while a[lson].r<>0 do
			lson:=a[lson].r;
		splay(root,lson);
		a[lson].r:=rson;
		a[rson].p:=lson;
	end;
end;

function getmin:int64;
var
	t:int64;
begin
	t:=root;
	while a[t].l<>0 do
		t:=a[t].l;
	exit(t);
end;

function getmax:int64;
var
	t:int64;
begin
	t:=root;
	while a[t].r<>0 do
		t:=a[t].r;
	exit(t);
end;

function findkth(k:int64):int64;
var
	t:int64;
begin
	t:=root;
	while t<>0 do
	begin
		if k=a[a[t].l].size+1 then break;
		if k<=a[a[t].l].size then t:=a[t].l
			else begin
				t:=a[t].r;
				k:=k-a[a[t].l].size-1
			end;
	end;
	splay(root,t);
	exit(t);
end;

procedure out(x:int64);
    begin
    if x=0 then exit;
    out(a[x].l);
    write(a[x].key,' ');
    out(a[x].r);
    end;




  
  procedure ask;  //询问l到r区间的数的和
  var
    s,t:int64;
    begin
    readln(s,t);
    t:=t+2;
    clean(root,s);clean(root,t); //先推标签。 
    splay(root,s);splay(a[s].r,t);
    writeln(a[a[t].l].sum); 
    end;

  
  procedure change;//把l到r区间的每一个数都加上某个给出的值
  var
    s,t,z:int64;
    begin
    readln(s,t,z);t:=t+2;
    clean(root,s);clean(root,t);
    splay(root,s);splay(a[s].r,t);
    inc(a[a[t].l].delta,z); //伸展完可以直接把标签打在根的右节点的左节点上。
    inc(a[a[t].l].sum,z*a[a[t].l].size); //打完标签要同时修改sum值。 
    end;
  
  begin
  //assign(input,'c:\1.in'); reset(input);
  //assign(output,'bst1.out'); rewrite(output);
  root:=0;
  readln(n,q);
  a[1].key:=-1000000000000;
  for i:=2 to n+1 do read(a[i].key);
  readln;
  a[n+2].key:=1000000000000;
  build(1,n+2);
  root:=(1+n+2)shr 1;
  
  
  
  
  for i:=1 to q do
    begin 
    read(ch);
    //while ch=' ' do read(ch);
    if ch='Q' then ask else change; 
    end;

  close(input); close(output);
  end.
  