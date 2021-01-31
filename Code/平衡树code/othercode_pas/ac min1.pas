{$M 1000000000}
type
  splaya=record
    l,r,key,size,p,min:int64;
    end;
var
  a:array[0..1000000]of splaya;
  root,n,j,q,x,y,z,ll:int64;
  i:longint;
  ch:char;
  procedure update(x:int64);//每次旋转完更新节点的两个域
    begin
    a[x].size:=a[a[x].l].size+a[a[x].r].size+1;
    a[x].min:=a[x].key;
    if a[a[x].l].min<a[x].min then a[x].min:=a[a[x].l].min;
    if a[a[x].r].min<a[x].min then a[x].min:=a[a[x].r].min;
    
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
	update(x);
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
	update(x);
end;

procedure splay(var root:int64;x:int64);
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

  
  begin
  assign(input,'min1.in'); reset(input);
  assign(output,'min1.out'); rewrite(output);
  a[0].min:=10000000000;
  a[1].key:=-1000000000000;
  a[1].min:=1000000000;
  root:=0;
  readln(n,q);
  for i:=2 to n+1 do read(a[i].key);
  readln;
  a[n+2].key:=1000000000000;
  a[n+2].min:=10000000000;
  build(1,n+2);
  root:=(1+n+2)shr 1;
  
  
  
  
  for i:=1 to q do
    begin 
    read(j,x,y);
    if j=1 then begin
    inc(x);inc(y);
    splay(root,x-1);
    splay(a[root].r,y+1);
    writeln(a[a[a[root].r].l].min);
    end
    else begin
    inc(x);
    a[x].key:=y;
    j:=x;
    while j<>0 do
      begin
      update(j);
      j:=a[j].p;
      end;
    end;
    end;

  close(input); close(output);
  end.
  