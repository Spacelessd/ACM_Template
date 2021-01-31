{$M 100000000}
var
  i,j,n,m,l,x,y,tt,i1,z,num,max,ans,tmp1:longint;
  next,v,c,start,son,maxcost,deep,ll,rr:array[0..200010]of longint;
  root,costfa,fa,tmp,e:array[0..200010]of longint;
  p:array[0..200010]of boolean;
  ro:longint;
  ch:char;

  procedure depdfs(x,y:longint);
  var
    i:longint;
    begin
    //writeln(x,' ',y,' ',v[1],' ',e[v[1]]);
    deep[x]:=y;
    p[x]:=true;
    i:=v[x];
    while i<>0 do
      begin
      if (p[e[i]]=false) then begin
        depdfs(e[i],y+1);
        end;
      i:=next[i];
      end;
    end;

  procedure kdfs(from,x,y:longint);
  var
    i:longint;
    begin
    fa[x]:=from;costfa[x]:=y;
    if son[root[from]]<max then begin
      inc(son[root[from]]);
      root[x]:=root[from];
      end
      else begin
        inc(num);
        start[num]:=x;
        son[x]:=1;
        root[x]:=x;
        end;
    p[x]:=true;
    i:=v[x];
    while i<>0 do
      begin
      if p[e[i]]=false then begin
        kdfs(x,e[i],i);
        end;
      i:=next[i];
      end;
    end;


  procedure cdfs(x:longint);
  var
    i:longint;
    begin
    if root[x]=x then maxcost[x]:=-100000000
      else begin
      if c[costfa[x]]>maxcost[fa[x]] then maxcost[x]:=c[costfa[x]]
        else maxcost[x]:=maxcost[fa[x]];
      end;
    p[x]:=true;
    i:=v[x];
    inc(tmp1);
    tmp[tmp1]:=x;
    while i<>0 do
      begin
      if (p[e[i]]=false)and(root[e[i]]=ro) then begin
        cdfs(e[i]);
        end;
      i:=next[i];
      end;
    end;

  begin
        assign(input,'c:\1.in');reset(input);
        assign(output,'c:\1.out');rewrite(output);
  readln(tt);
  for i1:=1 to tt do
  begin
  readln(n);
  l:=0;num:=0;max:=trunc(sqrt(n))+1;
//max:=50;
  fillchar(e,sizeof(e),0);
  fillchar(next,sizeof(next),0);
  fillchar(v,sizeof(v),0);
  fillchar(c,sizeof(c),0);
  fillchar(start,sizeof(start),0);
  fillchar(root,sizeof(root),0);
  fillchar(son,sizeof(son),0);
  fillchar(maxcost,sizeof(maxcost),0);
  fillchar(fa,sizeof(fa),0);
  fillchar(costfa,sizeof(costfa),0);
  fillchar(deep,sizeof(deep),0);

  for i:=1 to n-1 do
    begin
    readln(x,y,z);
    ll[i]:=x;rr[i]:=y;
    inc(l);
    e[l]:=y;c[l]:=z;
    next[l]:=v[x];
    v[x]:=l;

    inc(l);
    e[l]:=x;c[l]:=z;
    next[l]:=v[y];
    v[y]:=l;
    end;
  son[0]:=100000000;
  c[0]:=-100000000;
  kdfs(0,1,0);
  fillchar(p,sizeof(p),0);
  depdfs(1,1);
  fillchar(p,sizeof(p),0);

  for i:=1 to num do
    begin
    ro:=start[i];
    cdfs(start[i]);
    for j:=1 to tmp1 do p[tmp[j]]:=false;
    tmp1:=0;
    end;
  //writeln(deep[3]);
  while true do
    begin
    read(ch);
    if ch='D' then begin
      readln;
      break;
      end;
    if ch='Q' then begin
      for i:=1 to 4 do read(ch);
      readln(x,y);
      ans:=-100000000;
      while root[x]<>root[y] do
        begin
        if deep[root[x]]>deep[root[y]] then begin
          if maxcost[x]>ans then ans:=maxcost[x];
          x:=root[x];
          if c[costfa[x]]>ans then ans:=c[costfa[x]];
          x:=fa[x];
          end
          else begin
          if maxcost[y]>ans then ans:=maxcost[y];
          y:=root[y];
          if c[costfa[y]]>ans then ans:=c[costfa[y]];
          y:=fa[y];
          end;
        end;
        while x<>y do
          begin
          //writeln(x,' ',y,' ',fa[x],' ',deep[3],' ',deep[1]);  if y=0 then while true do;
          if deep[x]>deep[y] then begin
            if c[costfa[x]]>ans then ans:=c[costfa[x]];
            x:=fa[x];
            end
            else begin
            if c[costfa[y]]>ans then ans:=c[costfa[y]];
            y:=fa[y];
            end;
          end;
        writeln(ans);
      end
      else begin
      //writeln('*');
      for i:=1 to 5 do read(ch);
      readln(x,y);
      c[x*2-1]:=y;c[x*2]:=y;
      if deep[ll[x]]<=deep[rr[x]] then begin
      ro:=root[ll[x]];
cdfs(root[ll[x]]);
      for j:=1 to tmp1 do p[tmp[j]]:=false;
      tmp1:=0;
end
else begin
ro:=root[rr[x]];
      cdfs(root[rr[x]]);
      for j:=1 to tmp1 do p[tmp[j]]:=false;
      tmp1:=0;
end;
      end

    end;
  end;

        close(input);close(output);
  end.

