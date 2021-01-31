const
maxn=2000000;
var
  key,left,right,size:array[0..maxn]of longint;
  n,i,ll,j:longint;
  
  
  q,w,ans,min,t,k:longint;
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
  
  
function find(var t,v:longint):boolean;
begin
                if t=0 then exit(false);
                if v<key[t] then find:=find(left[t],v)
                else find:=(key[t]=v)or find(right[t],v);
end;


function pred(var t,v:longint):longint;
begin
                if t=0 then exit(v);
                if v<=key[t] then pred:=pred(left[t],v)
                else
                  begin
                    pred:=pred(right[t],v);
                    if pred=v then pred:=key[t];
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
    
  
begin
  //assign(input,'1.in');reset(input);
  //assign(output,'1.out');rewrite(output);
                ll:=0;
                t:=0;
                size[0]:=0;
                readln(n);
                readln(w);
                insert(t,w);
                ans:=w;
                for i:=2 to n do
                  begin
                    readln(w);
                    if not(find(t,w)) then
                      begin
                        min:=abs(w-succ(t,w));
                        if min=0 then min:=maxlongint;
                        j:=abs(w-pred(t,w));
                        if j=0 then j:=maxlongint;
                        if j<min then min:=j;
                        ans:=ans+min;
                      end;
                    insert(t,w);
                  end;
                writeln(ans);
                //close(output);
end.