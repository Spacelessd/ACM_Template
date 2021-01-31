var
   a:array[0..250,0..250] of longint;
   f:array[0..250,0..250,0..250] of longint;
   b,c,d:array[0..65000] of longint;
   pa,pb,pc,p,i,j,n,m,k,x1,y1,x2,y2,l,r,q,ii,ans2,ans1,ans,sss,sssss:longint;
   paa,pbb,pcc:array[0..3000]of int64;
function get(x,y,p:longint):longint;
begin
    get:=(paa[x mod pa +1]+pbb[x mod pb +1]+pcc[x mod pc +1]+paa[y mod pa +1]+pbb[y mod pb +1]+pcc[y mod pc +1]) mod p;
end;

procedure swap(var x,y:longint);
var t:longint;
begin
  t:=x; x:=y; y:=t;
end;

procedure sort(l,r: longint);
var
         i,j,x,y: longint;
begin
         i:=l;
         j:=r;
         x:=b[(l+r) div 2];
         repeat
           while b[i]<x do
            inc(i);
           while x<b[j] do
            dec(j);
           if not(i>j) then
             begin
                y:=b[i];	b[i]:=b[j];	b[j]:=y;
                y:=c[i];	c[i]:=c[j];
                c[j]:=y;	y:=d[i];	d[i]:=d[j];
                d[j]:=y;	inc(i);	j:=j-1;
             end;
         until i>j;
         if l<j then  sort(l,j);
         if i<r then           sort(i,r);
end;

begin
assign(input,'cheat.in'); reset(input);
  assign(output,'cheat.out'); rewrite(output);
   read(pa);
   for i:=1 to pa do read(paa[i]);
   read(pb);
   for i:=1 to pb do read(pbb[i]);
   read(pc);
   for i:=1 to pc do read(pcc[i]);
   read(n,m,p);
   for i:=1 to n do
   begin
      for j:=1 to m do
      begin
        a[i,j]:=get(i,j,p)+1;
        inc(b[0]);
        b[b[0]]:=a[i,j];
        c[b[0]]:=i;
        d[b[0]]:=j;
      end;
   end;
   sort(1,b[0]);
   for i:=1 to n do
     for j:=1 to m do
       for k:=0 to m-1 do
         begin
            if a[i,j]>b[k*n+1] then
            f[i,j,k]:=f[i-1,j,k]+f[i,j-1,k]-f[i-1,j-1,k]
            else f[i,j,k]:=f[i-1,j,k]+f[i,j-1,k]-f[i-1,j-1,k]+1;
         end;
   read(q);
   for ii:=1 to q do
   begin      
      x1:=get(ii,1,n)+1;
      y1:=get(ii,2,m)+1;
      x2:=get(ii,3,n)+1;
      y2:=get(ii,4,m)+1;
      l:=get(ii,5,p)+1;
      r:=get(ii,6,p)+1;
       if x1>x2 then swap(x1,x2);
       if y1>y2 then swap(y1,y2);
       if l>r then swap(l,r);
      for k:=0 to m-1 do
        if b[k*n+1]>r then break;
      if b[k*n+1]>r then dec(k);
      if k>=0 then
      begin
      ans2:=f[x2,y2,k]-f[x1-1,y2,k]-f[x2,y1-1,k]+f[x1-1,y1-1,k];
      sssss:=k*n;
      for i:=2 to n do
        if (b[sssss+i]<=r) then
        begin
           if b[sssss+1]<>b[sssss+i] then
           begin
           if (c[sssss+i]<=x2)and(d[sssss+i]<=y2)
           and (c[sssss+i]>=x1)and(d[sssss+i]>=y1) then inc(ans2);
           end;
        end
        else break;
      end
      else ans2:=0;
      for k:=0 to m-1 do
        if b[k*n+1]>l-1 then break;
      if b[k*n+1]>l-1 then dec(k);
      if k>=0 then
      begin
      ans1:=f[x2,y2,k]-f[x1-1,y2,k]-f[x2,y1-1,k]+f[x1-1,y1-1,k];
      sssss:=k*n;
      for i:=2 to n do
        if (b[sssss+i]<=l-1) then
        begin
           if b[sssss+1]<>b[sssss+i] then
           begin
           if (c[sssss+i]>=x1)and(d[sssss+i]>=y1) and
           (c[sssss+i]<=x2)and(d[sssss+i]<=y2)then inc(ans1);
           end;
        end
        else break;
      end
      else ans1:=0;
      ans:=ans2-ans1;
      sss:=sss xor ans;
   end;
   writeln(sss);
  close(input);
  close(output);
end.


