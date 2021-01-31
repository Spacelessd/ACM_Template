  const
    maxn=15000;
  type
    pnode=^node;
    node=record
      data:longint;
      size:longint;
      lch,rch:pnode;
    end;
    SizeBalancedTree=class(TObject)
      private
        root,null:pnode;
        procedure lrotate(var x:pnode);
        procedure rrotate(var x:pnode);
        procedure maintain(var t:pnode;const flag:boolean);
        procedure TreeInsert(var t:pnode;v:longint);
        function TreeDelete(var t:pnode;v:longint):longint;
        function TreeSelect(var t:pnode;k:longint):longint;
        function TreeFind(var t:pnode;v:longint):boolean;
        function TreeRank(var t:pnode;v:longint):longint;
        function TreeSucc(var t:pnode;v:longint):longint;
        function TreePred(var t:pnode;v:longint):longint;
      public
        constructor Create;
        procedure insert(v:longint);
        function delete(v:longint):longint;
        function select(k:longint):longint;
        function find(v:longint):boolean;
        function rank(v:longint):longint;
        function succ(v:longint):longint;
        function pred(v:longint):longint;
    end;
  var
    tree:SizeBalancedTree;
    x,y,ans:array[0..maxn]of longint;
    n,i:longint;
  constructor SizeBalancedTree.Create;
    begin
      new(null);
      null^.data:=0;
      null^.size:=0;
      null^.lch:=null;
      null^.rch:=null;
      root:=null;
    end;
  procedure SizeBalancedTree.lrotate(var x:pnode);
    var
      y:pnode;
    begin
      y:=x^.rch;
      x^.rch:=y^.lch;
      y^.lch:=x;
      y^.size:=x^.size;
      x^.size:=x^.lch^.size+x^.rch^.size+1;
      x:=y;
    end;
  procedure SizeBalancedTree.rrotate(var x:pnode);
    var
      y:pnode;
    begin
      y:=x^.lch;
      x^.lch:=y^.rch;
      y^.rch:=x;
      y^.size:=x^.size;
      x^.size:=x^.lch^.size+x^.rch^.size+1;
      x:=y;
    end;
  procedure SizeBalancedTree.maintain(var t:pnode;const flag:boolean);
    begin
      if t=null
        then exit;
      if not flag
        then if t^.lch^.lch^.size>t^.rch^.size
          then rrotate(t)
          else if t^.lch^.rch^.size>t^.rch^.size
            then begin
              lrotate(t^.lch);
              rrotate(t);
            end
            else exit
        else if t^.rch^.rch^.size>t^.lch^.size
          then lrotate(t)
          else if t^.rch^.lch^.size>t^.lch^.size
            then begin
              rrotate(t^.rch);
              lrotate(t);
            end
            else exit;
      maintain(t^.lch,false);
      maintain(t^.rch,true);
      maintain(t,false);
      maintain(t,true);
    end;
  procedure SizeBalancedTree.TreeInsert(var t:pnode;v:longint);
    begin
      if t=null
        then begin
          new(t);
          t^.data:=v;
          t^.size:=1;
          t^.lch:=null;
          t^.rch:=null;
        end
        else begin
          inc(t^.size);
          if v<t^.data
            then TreeInsert(t^.lch,v)
            else TreeInsert(t^.rch,v);
          maintain(t,v>=t^.data);
        end;
    end;
  function SizeBalancedTree.TreeDelete(var t:pnode;v:longint):longint;
    var
      tmp:pnode;
    begin
      if t=null
        then exit;
      dec(t^.size);
      if(v=t^.data)or((v<t^.data)and(t^.lch=null))or((v>t^.data)and(t^.rch=null))
        then begin
          TreeDelete:=t^.data;
          if(t^.lch=null)or(t^.rch=null)
            then begin
              if t^.lch=null
                then begin
                  tmp:=t;
                  t:=tmp^.rch;
                  dispose(tmp);
                end;
              if t^.rch=null
                then begin
                  tmp:=t;
                  t:=tmp^.lch;
                  dispose(tmp);
                end;
            end
            else t^.data:=TreeDelete(t^.lch,t^.data+1);
        end
        else if v<t^.data
          then TreeDelete:=TreeDelete(t^.lch,v)
          else TreeDelete:=TreeDelete(t^.rch,v);
    end;
  function SizeBalancedTree.TreeSelect(var t:pnode;k:longint):longint;
    begin
      if k=t^.lch^.size+1
        then begin
          TreeSelect:=t^.data;
          exit;
        end;
      if k<=t^.lch^.size
        then TreeSelect:=TreeSelect(t^.lch,k)
        else TreeSelect:=TreeSelect(t^.rch,k-1-t^.lch^.size);
    end;
  function SizeBalancedTree.TreeFind(var t:pnode;v:longint):boolean;
    begin
      if t=null
        then begin
          TreeFind:=false;
          exit;
        end;
      if v<t^.data
        then TreeFind:=TreeFind(t^.lch,v)
        else TreeFind:=(v=t^.data)or TreeFind(t^.rch,v);
    end;
  function SizeBalancedTree.TreeRank(var t:pnode;v:longint):longint;
    begin
      if t=null
        then begin
          TreeRank:=1;
          exit;
        end;
      if v<t^.data
        then TreeRank:=TreeRank(t^.lch,v)
        else TreeRank:=t^.lch^.size+1+TreeRank(t^.rch,v);
    end;
  function SizeBalancedTree.TreeSucc(var t:pnode;v:longint):longint;
    var
      tmp:longint;
    begin
      if t=null
        then begin
          TreeSucc:=v;
          exit;
        end;
      if v>=t^.data
        then TreeSucc:=TreeSucc(t^.rch,v)
        else begin
          tmp:=TreeSucc(t^.lch,v);
          if tmp=v
            then tmp:=t^.data;
          TreeSucc:=tmp;
        end;
    end;
  function SizeBalancedTree.TreePred(var t:pnode;v:longint):longint;
    var
      tmp:longint;
    begin
      if t=null
        then begin
          TreePred:=v;
          exit;
        end;
      if v<=t^.data
        then TreePred:=TreePred(t^.lch,v)
        else begin
          tmp:=TreePred(t^.rch,v);
          if tmp=v
            then tmp:=t^.data;
          TreePred:=tmp;
        end;
    end;
  procedure SizeBalancedTree.insert(v:longint);
    begin
      TreeInsert(root,v);
    end;
  function SizeBalancedTree.delete(v:longint):longint;
    begin
      delete:=TreeDelete(root,v);
    end;
  function SizeBalancedTree.select(k:longint):longint;
    begin
      select:=TreeSelect(root,k);
    end;
  function SizeBalancedTree.find(v:longint):boolean;
    begin
      find:=TreeFind(root,v);
    end;
  function SizeBalancedTree.rank(v:longint):longint;
    begin
      rank:=TreeRank(root,v);
    end;
  function SizeBalancedTree.succ(v:longint):longint;
    begin
      succ:=TreeSucc(root,v);
    end;
  function SizeBalancedTree.pred(v:longint):longint;
    begin
      pred:=TreePred(root,v);
    end;
  procedure swap(var a,b:longint);
    var
      c:longint;
    begin
      c:=a;
      a:=b;
      b:=c;
    end;
  procedure qsort(m,n:longint);
    var
      i,j:longint;
    begin
      if(m+1=n)and((x[m]>x[n])or((x[m]=x[n])and(y[m]>y[n])))
        then begin
          swap(x[m],x[n]);
          swap(y[m],y[n]);
          exit;
        end;
      if m<n
        then begin
          i:=m-1;
          j:=random(n-m)+m;
          swap(x[j],x[n]);
          swap(y[j],y[n]);
          for j:=m to n-1 do
            if(x[j]<x[n])or(((x[j]=x[n])and(y[j]<y[n])))
              then begin
                inc(i);
                swap(x[i],x[j]);
                swap(y[i],y[j]);
              end;
          swap(x[i+1],x[n]);
          swap(y[i+1],y[n]);
          qsort(m,i);
          qsort(i+2,n);
        end;
    end;
  begin
    //assign(input,'1.in');reset(input);
    //assign(output,'1.out');rewrite(output);
    readln(n);
    for i:=1 to n do
      readln(x[i],y[i]);
    randomize;
    qsort(1,n);
    tree:=SizeBalancedTree.Create;
    for i:=1 to n do
      begin
        ans[i]:=tree.rank(y[i]);
        tree.insert(y[i]);
      end;
    fillchar(x,sizeof(x),0);
    for i:=1 to n do
      inc(x[ans[i]]);
    for i:=1 to n do
      writeln(x[i]);
    close(input);
    close(output);
  end.


