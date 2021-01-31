const  
maxn=2000000;
var
  key,left,right,size:array[0..maxn]of longint;
  n,i,ll,j,q,t,x:longint;
procedure right_rotate(var t:longint);
var
  k:longint;
  begin
  k:=left[t];
  left[t]:=right[k];
  right[k]:=t;
  size[k]:=size[t];
  size[t]:=size[left[t]]+size[right[t]]+1;
  t:=k;
  end;

procedure left_rotate(var t:longint);
var
  k:longint;
  begin
  k:=right[t];
  right[t]:=left[k];
  left[k]:=t;
  size[k]:=size[t];
  size[t]:=size[left[t]]+size[right[t]]+1;
  t:=k;
  end;

procedure maintain(var t:longint;flag:boolean);
begin
                if flag=false then
                  if size[left[left[t]]]>size[right[t]] then right_rotate(t)
                  else
                    if size[right[left[t]]]>size[right[t]] then
                      begin
                        left_rotate(left[t]);
                        right_rotate(t);
                      end
                    else
                      exit
                else
                  if size[right[right[t]]]>size[left[t]] then left_rotate(t)
                  else
                    if size[left[right[t]]]>size[left[t]] then
                      begin
                        right_rotate(right[t]);
                        left_rotate(t);
                      end
                    else
                      exit;
                maintain(left[t],false);
                maintain(right[t],true);
                maintain(t,true);
                maintain(t,false);
end;

  
  
procedure insert(var t,v:longint);
  begin
  if t=0 then
                  begin
                    inc(ll);
                    t:=ll;
                    key[t]:=v;
                    size[t]:=1;
                    left[t]:=0;
                    right[t]:=0;
                  end
  else begin
  size[t]:=size[t]+1;
  if v<key[t] then insert(left[t],v)
    else insert(right[t],v);
  maintain(t,v>=key[t]);
  end;
  end;

procedure insert1(var t,v,l:longint);
  begin
  if t=0 then
                  begin
                    key[l]:=v;
                    size[l]:=1;
                    left[l]:=0;
                    right[l]:=0;
                  end
  else begin
  size[t]:=size[t]+1;
  if v<key[t] then insert1(left[t],v,l)
    else insert1(right[t],v,l);
  maintain(t,v>=key[t]);
  end;
  end;
  
  
function find(var t,v:longint):longint;
begin
                if t=0 then exit(0);
                if v<key[t] then find:=find(left[t],v)
                else begin
                if key[t]=v then find:=v
                else find:=find(right[t],v);
                end;
end;


function predd(var t,v:longint):longint;
begin
                if t=0 then exit(v);
                if v<=key[t] then predd:=predd(left[t],v)
                else
                  begin
                    predd:=predd(right[t],v);
                    if predd=v then predd:=key[t];
                  end;
end;

function succ(var t,v:longint):longint;
begin
                if t=0 then exit(v);
                if key[t]<=v then succ:=succ(right[t],v)
                else
                  begin
                    succ:=succ(left[t],v);
                    if succ=v then succ:=key[t];
                  end;
end;


Function Delete(var x:Longint;w:Longint):Longint; 
Begin 
  Dec(size[x]);
  If (w=key[x])or((w<key[x])and(left[x]=0)) 
   Or ((w>key[x]) And (right[x]=0)) Then Begin 
    Delete:= key[x]; 
    If (left[x]=0)Or(right[x]=0) Then 
      x:=left[x]+right[x] 
    Else 
      key[x]:=Delete(left[x],key[x]+1); 
  End 
  Else 
    If w<key[x] Then 
      Delete:=Delete(left[x],w) 
    Else 
      Delete:=Delete(right[x],w);
End; 



Function Select(Var x:Longint;w:Longint):Longint; 
Begin 
  If w=size[left[x]]+1 Then 
    Select:=key[x] 
  Else If w<=size[left[x]] Then 
    Select:=Select(left[x],w) 
  Else 
    Select:=Select(right[x],w-size[left[x]]-1); 
  end;  
    
  function rank(var t,v:longint):longint;inline;
begin
   if t=0 then
      exit(1);
   if v<=key[t] then
      rank:=rank(left[t],v)
   else
      rank:=size[left[t]]+1+rank(right[t],v);
end;
begin
  //assign(input,'1.in');reset(input);
  //assign(output,'1.out');rewrite(output);
  t:=0;
  readln(n,q);
  for i:=1 to n do
    begin
    readln(j);
    insert(t,j);
    end;
  for i:=1 to q do
    begin
    read(j,x);
    if j=1 then begin
      key[j]:=key[j]+1;
      insert1(t,key[j],j);
      end
      else
    if j=2 then begin
      inc(x);
      j:=predd(t,x);
      writeln(rank(t,x));
      
      end;
    end;
  //close(output);
end.