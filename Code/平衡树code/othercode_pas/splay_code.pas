type
	splaytree=record
		l,r,p,key,size:longint;
	end;

var
	tree:array [0..100000] of splaytree;
        root,i,j,n:longint;

procedure update(x:longint);
begin
	tree[x].size:=tree[tree[x].l].size+tree[tree[x].r].size+1;
end;

procedure rightrotate(x:longint);
var
	y,z:longint;
begin
	y:=tree[x].p;
	z:=tree[y].p;
	if tree[z].l=y then tree[z].l:=x
		else tree[z].r:=x;
	tree[x].p:=z;
	tree[y].p:=x;
	tree[y].l:=tree[x].r;
	tree[x].r:=y;
	tree[tree[y].l].p:=y;
	update(y);
end;

procedure leftrotate(x:longint);
var
	y,z:longint;
begin
	y:=tree[x].p;
	z:=tree[y].p;
	if tree[z].l=y then tree[z].l:=x
		else tree[z].r:=x;
	tree[x].p:=z;
	tree[y].p:=x;
	tree[y].r:=tree[x].l;
	tree[x].l:=y;
	tree[tree[y].r].p:=y;
	update(y);
end;

procedure splay(x:longint);

begin
	while tree[x].p<>0 do
		if tree[tree[x].p].l=x then rightrotate(x)
			else leftrotate(x);
	root:=x;
end;

 procedure insert(var root:longint;z:longint);
  var
    x,y:longint;
    begin
    y:=0;
    x:=root;
    while x<>0 do
      begin
      y:=x;
      if tree[z].key<tree[x].key then x:=tree[x].l
        else x:=tree[x].r;
      end;
    tree[z].p:=y;
    if y=0 then root:=z
      else if tree[z].key<tree[y].key then tree[y].l:=z
        else tree[y].r:=z;
    end;


function find(t,x:longint):longint;
begin
        while t<>0 do
        begin
                if x=tree[t].key then exit(t)
                else if x<tree[t].key then
                        t:=tree[t].l
                else t:=tree[t].r
        end;
        splay(x);
end;

procedure delete(var t:longint; k:longint);
var
	x,lson,rson:longint;
begin
	x:=find(t,k);
	splay(x);
	lson:=tree[x].l;
	rson:=tree[x].r;
	tree[lson].p:=0;	tree[rson].p:=0;
	tree[x].l:=0;	tree[x].r:=0;
	if lson=0 then root:=rson
	else begin
		while tree[lson].r<>0 do
			lson:=tree[lson].r;
		splay(lson);
		tree[lson].r:=rson;
		tree[rson].p:=lson;
	end;
end;

function getmin:longint;
var
	t:longint;
begin
	t:=root;
	while tree[t].l<>0 do
		t:=tree[t].l;
	exit(t);
end;

function getmax:longint;
var
	t:longint;
begin
	t:=root;
	while tree[t].r<>0 do
		t:=tree[t].r;
	exit(t);
end;

function findkth(k:longint):longint;
var
	t:longint;
begin
	t:=root;
	while t<>0 do
	begin
		if k=tree[tree[t].l].size+1 then break;
		if k<=tree[tree[t].l].size then t:=tree[t].l
			else begin
				t:=tree[t].r;
				k:=k-tree[tree[t].l].size-1
			end;
	end;
	splay(t);
	exit(t);
end;

procedure out(x:longint);
    begin
    if x=0 then exit;
    out(tree[x].l);
    write(tree[x].key,' ');
    out(tree[x].r);
    end;


begin
readln(n);
for i:=1 to n do 
  begin
  read(j);
  tree[i].key:=j;
  insert(root,i);
  //writeln(root);
  end;
out(root);


end.
