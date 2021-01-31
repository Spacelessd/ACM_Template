Type
	SplayTree=Record
		l,r,p,size,key:	LongInt;
		name:		String[10];
	End;

Var
	tree:						Array [0..400000] of SplayTree;
	trie:						Array [0..400000,'A'..'Z'] of Longint;
	nameid:						Array [1..400000] of Longint;
	n,i,j,tot,rank,top,score,pos,root,son,p:	LongInt;
	s:						String;
        opt,ch:						Char;
        t0:						Double;

Procedure LtoR(x:LongInt);
Var
	y,z:LongInt;
Begin
	y:=tree[x].p;
	z:=tree[y].p;
	If tree[z].l=y then tree[z].l:=x
	Else tree[z].r:=x;
	tree[x].p:=z;
	tree[y].p:=x;
	tree[y].l:=tree[x].r;
	tree[x].r:=y;
	tree[tree[y].l].p:=y;
        tree[y].size:=tree[tree[y].l].size+tree[tree[y].r].size+1;
End;

Procedure RtoL(x:LongInt);
Var
	y,z:LongInt;
Begin
	y:=tree[x].p;
	z:=tree[y].p;
	If tree[z].l=y then tree[z].l:=x
	Else tree[z].r:=x;
	tree[x].p:=z;
	tree[y].p:=x;
	tree[y].r:=tree[x].l;
	tree[x].l:=y;
	tree[tree[y].r].p:=y;
	tree[y].size:=tree[tree[y].l].size+tree[tree[y].r].size+1;
End;

Procedure Splay(Var root:LongInt; x:LongInt);
Var
	y,z:LongInt;
Begin
	While tree[x].p<>0 do
	Begin
		y:=tree[x].p;
		z:=tree[y].p;
		If z<>0 then
		Begin
			If tree[z].l=y then
			Begin
				If tree[y].l=x then
				Begin
					LtoR(y); LtoR(x);
				End
				Else Begin
					RtoL(x); LtoR(x);
				End;
			End
			Else Begin
				If tree[y].l=x then
				Begin
					LtoR(x); RtoL(x);
				End
				Else Begin
					RtoL(y); RtoL(x);
				End;
			End;
		End
		Else If tree[y].l=x then LtoR(x)
			Else RtoL(x);
	End;
        tree[x].size:=tree[tree[x].l].size+tree[tree[x].r].size+1;
	root:=x;
End;

Procedure Insert(Var t:LongInt; k,p:LongInt);
Begin
	If t=0 then
	Begin
		t:=k;
		tree[k].p:=p;
		tree[k].l:=0;	tree[k].r:=0;
		tree[k].size:=1;
		tree[k].key:=score;
                tree[k].name:=s;
		Splay(root,k);
		Exit;
	End;
        Inc(tree[t].size);
        If score>tree[t].key then Insert(tree[t].r,k,t)
        Else Insert(tree[t].l,k,t)
End;

Function FindKth(k:LongInt):LongInt;
Var
	t:LongInt;
Begin
	t:=root;
	While t<>0 do
	Begin
		If k=tree[tree[t].l].size+1 then Break;
		If k<=tree[tree[t].l].size then t:=tree[t].l
		Else Begin
                	k:=k-tree[tree[t].l].size-1;
			t:=tree[t].r;
		End;
	End;
	Splay(root,t);
	Exit(t);
End;

Procedure Delete(k:LongInt);
Var
	lson,rson:LongInt;
Begin
	Splay(root,k);
	lson:=tree[k].l;
	rson:=tree[k].r;
	tree[lson].p:=0; tree[rson].p:=0;
	tree[k].l:=0; tree[k].r:=0;
	If lson=0 then root:=rson
	Else Begin
		While tree[lson].r<>0 do lson:=tree[lson].r;
                Splay(root,lson);
		tree[lson].r:=rson;
		tree[rson].p:=lson;
	End;
End;

Function Findname:LongInt;
Var
	kk,ii:LongInt;
Begin
	kk:=0;
	For ii:=1 to Length(s) do
	If trie[kk,s[ii]]=0 then
	Begin
		Inc(top);
		trie[kk,s[ii]]:=top;
		kk:=top;
	End
	Else kk:=trie[kk,s[ii]];
	If nameid[kk]=0 then
	Begin
		Inc(tot);
		nameid[kk]:=tot;
		Exit(0);
	End
	Else Exit(nameid[kk]);
End;

Begin
	//Randomize; t0:=randseed;
	Assign(input,'E.in'); Reset(input);
	Assign(output,'E.out'); Rewrite(output);
        root:=0; tot:=0; top:=0;
	Readln(n);
	For i:=1 to n do
	Begin
		Read(opt);
		If opt='+' then
		Begin
			s:='';
			Read(ch);
			While ch<>' ' do
			Begin
				s:=s+ch;
                                Read(ch);
			End;
			Readln(score);
                        pos:=findname;
			If pos<>0 then
			Begin
				Delete(pos);
				Insert(root,pos,0);
			End
			Else Insert(root,tot,0);
		End
		Else Begin
			Readln(s);
			If (s[1]>='A') and (s[1]<='Z') then
			Begin
				pos:=findname;
				Splay(root,pos);
				Writeln(tree[tree[pos].r].size+1);
			End
			Else Begin
				Val(s,rank);
				If tot>=rank+10-1 then p:=10
				Else p:=tot-rank+1;
				pos:=FindKth(tot-rank+1);
				Splay(root,pos);
				Write(tree[root].name);
				For j:=2 to p do
				Begin
					son:=tree[root].l;
					While tree[son].r<>0 do son:=tree[son].r;
					Write(' ',tree[son].name);
					Splay(root,son);
				End;
                                Writeln;
			End;
		End;
	End;
	//Randomize; Writeln((randseed-t0)/1000:0:5);
End.

