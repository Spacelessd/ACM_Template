type
	Tnode		=record
		key,cnt,size,p,l,r	:longint;
	end;

	procedure Update(x:longint);
	begin
		tree[x].size:=tree[x].cnt;
		if tree[x].l<>0 then inc(tree[x].size,tree[tree[x].l].size);
		if tree[x].r<>0 then inc(tree[x].size,tree[tree[x].r].size);
	end;
	
	procedure Zig(x:longint);
	var
		y,z	:longint;
	begin
		y:=tree[x].p;
		z:=tree[y].p;
		tree[y].l:=tree[x].r;
		tree[tree[x].r].p:=y;
		tree[x].p:=z;
		if y=tree[z].l then tree[z].l:=x else tree[z].r:=x;
		tree[x].r:=y;
		tree[y].p:=x;
		Update(y);
	end;
	
	procedure Zag(x:longint);
	var
		y,z	:longint;
	begin
		y:=tree[x].p;
		z:=tree[y].p;
		tree[y].r:=tree[x].l;
		tree[tree[x].l].p:=y;
		tree[x].p:=z;
		if y=tree[z].l then tree[z].l:=x else tree[z].r:=x;
		tree[x].l:=y;
		tree[y].p:=x;
		Update(y);
	end;
	
	procedure Splay(var root:longint;x:longint);
        var
                y,z     :longint;
        begin
                while Tree[x].p<>0 do
                begin
                        y:=Tree[x].p;
                        z:=Tree[y].p;
                        if z=0 then
                        begin
                                if x=Tree[y].l then Zig(x) else Zag(x);
                        end
                        else
                        begin
                                if y=Tree[z].l then
                                begin
                                        if x=Tree[y].l then
                                        begin
                                                Zig(y);
                                                Zig(x);
                                        end
                                        else
                                        begin
                                                Zag(x);
                                                Zig(x);
                                        end;
                                end
                                else
                                begin
                                        if x=Tree[y].r then
                                        begin
                                                Zag(y);
                                                Zag(x);
                                        end
                                        else
                                        begin
                                                Zig(x);
                                                Zag(x);
                                        end;
                                end;
                        end;
                end;
                root:=x;
                Update(root);
        end;
	
	procedure Insert(var root:longint;key:longint);
	var
		p	:longint;
	begin
		if root=0 then
		begin
			inc(cnt);
			tree[cnt].key:=key;
			tree[cnt].cnt:=1;
			tree[cnt].size:=1;
			tree[cnt].p:=0;
			tree[cnt].l:=0;
			tree[cnt].r:=0;
			root:=cnt;
			exit;
		end;
		p:=root;
		while true do
		begin
			if key<tree[p].key then
			begin
				if tree[p].l=0 then break;
				p:=tree[p].l;
			end	else
			begin
				if tree[p].r=0 then break;
				p:=tree[p].r;
			end;
		end;
		inc(cnt);
		tree[cnt].key:=key;
		tree[cnt].cnt:=1;
		tree[cnt].size:=1;
		tree[cnt].p:=p;
		tree[cnt].l:=0;
		tree[cnt].r:=0;
		if key<tree[p].key then tree[p].l:=cnt else tree[p].r:=cnt;
		Splay(root,cnt);
	end;
	
	function Getpos(key:longint):longint;
	var
		p	:longint;
	begin
		p:=root;
		while true do
		begin
			if key=tree[p].key then exit(p);
			if key<tree[p].key then p:=tree[p].l else p:=tree[p].r;
		end;
	end;
	
	function Join(x,y:longint):longint;
	var
		p	:longint;
	begin
		if x=0 then exit(y);
		if y=0 then exit(x);
		p:=MaxPos(x);
		Splay(x,p);
		tree[p].r:=y;
		tree[y].p:=p;
		Update(p);
		exit(p);
	end;
	
	procedure Delete(key:longint);
	var
		p	:longint;
	begin
		p:=Getpos(key);
		Splay(root,p);
		tree[tree[root].l].p:=0;
		tree[tree[root].r].p:=0;
		root:=Join(tree[root].l,tree[root].r);
	end;
	
	function Kth(var root:longint;k:longint);
	var
		p	:longint;
	begin
		p:=root;
		repeat
			if k<=tree[tree[p].l].size then p:=tree[p].l else
			if k<=tree[tree[p].l].size+tree[p].cnt then break else
			begin
				k:=k-tree[tree[p].l].size-tree[p].cnt;
				p:=tree[p].r;
			end;
		until	false;
		Splay(root,p);
		exit(tree[p].key);
	end;
	