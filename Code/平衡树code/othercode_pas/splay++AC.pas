{$inline on}
{$M 1000000000}
type
  splaya=record
    l,r,key,size,p,min,sum,delta:int64;
    end;
var
  a:array[0..1000000]of splaya;
  stack,num,c:array[0..500000]of int64;
  root,n,j,q,x,y,z,ll,s1:int64;
  i:longint;
  ch:char;


  procedure out(y,x:int64);
    begin
    if x=0 then exit;
    out(x,a[x].l);
    //writeln(y,' ',x,' ',a[x].key,' ',a[x].delta,' ',a[x].sum);
    write(a[x].key,' ');
    out(x,a[x].r);
    end;


  procedure update1(x,z:int64);inline;  //节点x加z
    begin
      inc(a[x].sum,a[x].size*z);
      a[x].key:=a[x].key+z;
      a[x].min:=a[x].min+z;
      inc(a[x].delta,z);
    end;
    
  procedure update(x:int64);inline;  //每次旋转完更新节点的两个域
    begin
    a[x].size:=a[a[x].l].size+a[a[x].r].size+1;
    a[x].sum:=a[a[x].l].sum+a[a[x].r].sum+a[x].key;
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


  procedure down(root,x:int64); //从root开始向下推标签,直到x
  var
    y:int64;
    i:longint;
    begin
    if x=0 then exit;
    s1:=0;
    y:=x;
    repeat
      inc(s1);
      stack[s1]:=y;
      if y=root then break;
      y:=a[y].p;
    until false;

    for i:=s1 downto 1 do
      begin
      x:=stack[i];
      update1(a[x].l,a[x].delta);
      update1(a[x].r,a[x].delta);
      a[x].delta:=0;
      end;
    end;



procedure rightrotate(x:int64);inline;  //右旋
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

procedure leftrotate(x:int64);inline;  //左旋
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

procedure splay(var root:int64;x:int64);  //核心操作:单旋splay
var
  tmp:int64;
  begin
  if x=0 then exit;
  down(root,x);
  tmp:=a[root].p;
	while a[x].p<>tmp do
		if a[a[x].p].l=x then rightrotate(x)
			else leftrotate(x);
  update(x);
  root:=x;
  end;


function fsmall(t,x:int64):int64;inline;  //找值小于x的最大节点
begin
        down(root,t);
        fsmall:=0;
        while t<>0 do
        begin
        down(t,t);
        if a[t].key>=x then t:=a[t].l
                else begin
                  if (fsmall=0)or(a[fsmall].key<=a[t].key) then fsmall:=t;
                  t:=a[t].r;
                  end;
        end;
        splay(root,fsmall);
end;

function fbig(t,x:int64):int64;inline;  //找值大于x的最小节点
begin
        down(root,t);
        fbig:=0;
        while t<>0 do
        begin
        down(t,t);
        if a[t].key<=x then t:=a[t].r
                else begin
                  if (fbig=0)or(a[fbig].key>=a[t].key) then fbig:=t;
                  t:=a[t].l;
                  end;
        end;
        splay(root,fbig);
end;

function find(t,x:int64):int64;inline;  //找值为x的节点
begin
        down(root,t);
        find:=0;
        while t<>0 do
        begin
        down(t,t);
        if x=a[t].key then exit(t)
            else if x<a[t].key then t:=a[t].l
                else t:=a[t].r
        end;
        //splay(root,t);
        exit(t);
end;

function getmin(var root:int64):int64;inline;  //最小节点
var
	t:int64;
begin
	t:=root;
	while a[t].l<>0 do
		t:=a[t].l;
        splay(root,t);
	exit(t);
end;

function getmax(var root:int64):int64;inline;  //最大节点
var
	t:int64;
begin
	t:=root;
	while a[t].r<>0 do
		t:=a[t].r;
        splay(root,t);
	exit(t);
end;


  function join(x,y:int64):int64;inline;  //合并 (x.key<=y.key)
  var
    i:int64;
    begin
    if x=0 then exit(y);
    if y=0 then exit(x);
    i:=getmin(y);
    a[y].p:=0;
    splay(y,i);
    a[y].l:=x;
    a[x].p:=y;
    exit(y);
    end;


  procedure delete(var root:int64;x:int64);inline;//删除
    begin
    splay(root,x);
    root:=join(a[root].l,a[root].r);
    end;
  
  
  function big(x,y:int64):boolean;inline;
    begin
    if a[x].key>=a[y].key then big:=true
      else big:=false;
    end;
    
    
  procedure insert(var root:int64;z:int64);//插入
  var
    x,y:int64;
    begin
    y:=0;
    x:=root;
    while x<>0 do
      begin
      y:=x;
      down(x,x);
      if big(x,z) then x:=a[x].l
        else x:=a[x].r;
      end;
    a[z].p:=y;
    if y=0 then root:=z
      else if big(y,z) then a[y].l:=z
        else a[y].r:=z;
    splay(root,z);
    end;


function findkth(var root:int64;k:int64):int64;inline;  //找第k大的节点
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
  
  function select(var root:int64;x:int64):int64;//求节点序号
    begin
    splay(root,x);
    exit(a[a[root].l].size);
    end;

  function pred(var root:int64;x:int64):int64;//求节点前驱
    begin
    splay(root,x);
    exit(getmax(a[root].l));
    end;
  
  function succ(var root:int64;x:int64):int64;//求节点后继
    begin
    splay(root,x);
    exit(getmin(a[root].r));
    end;
    

  procedure qsort(l,r:longint);
      var
         i,j,x1,y1:longint;
      begin
         i:=l;
         j:=r;
         x1:=a[(l+r) div 2].key;
         repeat
           while a[i].key<x1 do
            inc(i);
           while x1<a[j].key do
            dec(j);
           if not(i>j) then
             begin
                num[c[i]]:=j;
                num[c[j]]:=i;

                y1:=c[i];
                c[i]:=c[j];
                c[j]:=y1;

                y1:=a[i].key;
                a[i].key:=a[j].key;
                a[j].key:=y1;
                inc(i);
                j:=j-1;
             end;
         until i>j;
         if l<j then
           qsort(l,j);
         if i<r then
           qsort(i,r);
      end;

  begin
  //assign(input,'q.in'); reset(input);
  //assign(output,'q.out'); rewrite(output);
  a[1].key:=-1000000000000;
  root:=0;
  readln(n,q);
  for i:=2 to n+1 do read(a[i].key);
  for i:=1 to n do num[i]:=i+1;
  for i:=2 to n+1 do c[i]:=i-1;
  readln;
  qsort(2,n+1);
  a[n+2].key:=1000000000000;
  build(1,n+2);
  root:=(1+n+2)shr 1;

  for i:=1 to q do
    begin
    readln(j,x);
    if j=1 then begin
      delete(root,num[x]);
      inc(a[num[x]].key);
      a[num[x]].l:=0;
      a[num[x]].r:=0;
      a[num[x]].p:=0;
      a[num[x]].size:=1;
      insert(root,num[x]);
      end;
    if j=2 then begin
      y:=fsmall(root,x);
      splay(root,y);
      writeln(a[a[root].r].size-1);
      end;
    if j=3 then begin
      y:=fsmall(root,x);
      splay(root,y);
      splay(a[root].r,n+2);
      update1(a[a[root].r].l,-1);
      update(a[root].r);
      update(root);
      end;
    end;

  close(input); close(output);
  end.


