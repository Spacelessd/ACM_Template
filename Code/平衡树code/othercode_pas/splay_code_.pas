type
	splaytree=record
		l,r,p,key,size:longint;
	end;

var
	tree:array [1..maxn] of splaytree;

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

procedure insert(var t:longint; k,p:longint);
begin
	if t=0 then
	begin
		t:=k;
		tree[k].p:=p;
		tree[k].l:=0;	tree[k].r:=0;
		tree[k].size:=1;
		exit;
	end;
	if tree[k].key<tree[t].key then insert(tree[t].l,k,t)
		else insert(tree[t].r,k,t);
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

begin



end.
