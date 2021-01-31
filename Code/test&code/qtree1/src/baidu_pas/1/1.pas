{$M 100000000}
const
        maxn = 100010;
        maxm = 200010;
        inf = 1000000000;
type
        edgetype = record
                      v,w,id,next : longint;
                    end;
        qedgetype = record
                      v,id,next : longint;
                    end;
        nodetype = record
                      max : longint;
                    end;
var
        g,qg,size,maxson,link,cost,bel,locate,stand,fa,father,head : array[0..maxn] of longint;
        test,n,i,edge_tt,qedge_tt,bel_cnt,loc_cnt,x,y,z,q,ans : longint;
        node   : array[0..maxn*4] of nodetype;
        edge   : array[0..maxn*2] of edgetype;
        qedge : array[0..maxm*2] of qedgetype;
        opr    : array[0..maxm,1..3] of longint;
        lca_id : array[0..maxm] of longint;
        ch     : char;
        
procedure read_space;
var     ch : char;
begin
        repeat read(ch);until ch=' ';
end;

function max(a,b:longint):longint;
begin
        if a>b then exit(a) else exit(b);
end;

procedure add_edge(x,y,z,i:longint);
begin
        inc(edge_tt);
        with edge[edge_tt] do
        begin
                v:=y;w:=z;id:=i;next:=g[x];g[x]:=edge_tt;
        end;
end;

procedure add_qedge(x,y,i:longint);
begin
        inc(qedge_tt);
        with qedge[qedge_tt] do
        begin
                v:=y;id:=i;next:=qg[x];qg[x]:=qedge_tt;
        end;
end;

procedure buildtree(v,l,r:longint);
var     mid : longint;
begin
        if l=r then
        begin
                node[v].max:=cost[stand[l]];exit;
        end;
        mid:=(l+r)shr 1;
        buildtree(v shl 1,l,mid);
        buildtree(v shl 1+1,mid+1,r);
        node[v].max:=max(node[v shl 1].max,node[v shl 1+1].max);
end;

procedure change(v,l,r,p,w:longint);
var     mid : longint;
begin
        if (l=r) then
        begin
                node[v].max:=w;exit;
        end;
        mid:=(l+r)shr 1;
        if p<=mid then change(v shl 1,l,mid,p,w)
                  else change(v shl 1+1,mid+1,r,p,w);
        node[v].max:=max(node[v shl 1].max,node[v shl 1+1].max);
end;

function getmax(v,l,r,x,y:longint):longint;
var     mid : longint;
begin
        if (x>r)or(y<l) then exit(-inf);
        if (x<=l)and(r<=y) then exit(node[v].max);
        mid:=(l+r)shr 1;
        getmax:=max(getmax(v shl 1,l,mid,x,y),getmax(v shl 1+1,mid+1,r,x,y));
end;

procedure dfs(u,fa:longint);
var     p : longint;
begin
        size[u]:=1; maxson[u]:=0;
        p:=g[u];
        while p<>0 do with edge[p] do
        begin
                if (v<>fa) then
                begin
                        dfs(v,u);
                        father[v]:=u;
                        link[id]:=v;
                        cost[v]:=w;
                        inc(size[u],size[v]);
                        if size[v]>size[maxson[u]] then maxson[u]:=v;
                end;
                p:=next;
        end;
end;

procedure cut(u,fa:longint);
var     p : longint;
begin
        if u=0 then exit;
        inc(loc_cnt); locate[u]:=loc_cnt; stand[loc_cnt]:=u;
        if u=maxson[fa] then bel[u]:=bel[fa]
        else begin inc(bel_cnt);bel[u]:=bel_cnt;head[bel_cnt]:=u;end;
        
        cut(maxson[u],u);
        
        p:=g[u];
        while p<>0 do with edge[p] do
        begin
                if (bel[v]=0) then cut(v,u);
                p:=next;
        end;
end;

function getfa(u:longint):longint;
begin
        if fa[u]=u then exit(u);
        fa[u]:=getfa(fa[u]);
        exit(fa[u]);
end;

procedure lca(u:longint);
var     p : longint;
begin
        fa[u]:=u;
        
        p:=qg[u];
        while p<>0 do with qedge[p] do
        begin
                if fa[v]<>0 then lca_id[id]:=getfa(v);
                p:=next;
        end;
        
        p:=g[u];
        while p<>0 do with edge[p] do
        begin
                if fa[v]=0 then
                begin
                        lca(v);
                        fa[v]:=u;
                end;
                p:=next;
        end;
end;

procedure work(u,lca:longint);
var     tmp : longint;
begin
        while u<>lca do
        begin
                if (bel[u]=bel[lca]) then
                begin
                        tmp:=getmax(1,1,loc_cnt,locate[lca]+1,locate[u]);
                        if tmp>ans then ans:=tmp;
                        break;
                end;
                tmp:=getmax(1,1,loc_cnt,locate[head[bel[u]]],locate[u]);
                if tmp>ans then ans:=tmp;
                u:=father[head[bel[u]]];
        end;
end;

procedure query(x,y:longint);
begin
        if x=y then ans:=0 else
        begin
                ans:=-inf;
                work(x,lca_id[i]);
                work(y,lca_id[i]);
        end;
        writeln(ans);
end;

procedure solve;
begin
        // input tree
        readln(n);
        fillchar(g,sizeof(g),0);
        edge_tt:=0;
        for i:=1 to n-1 do
        begin
                readln(x,y,z);
                add_edge(x,y,z,i);
                add_edge(y,x,z,i);
        end;

        // make tree & cut
        fillchar(bel,sizeof(bel),0);
        loc_cnt:=0; bel_cnt:=0;
        dfs(1,0);
        cut(1,0);
        
        // build sgt
        cost[1]:=-inf;
        buildtree(1,1,loc_cnt);

        // input opr & compute lca
        fillchar(qg,sizeof(qg),0);
        qedge_tt:=0;
        q:=0;
        read(ch);
        while ch<>'D' do
        begin
                read_space;
                readln(x,y);
                inc(q);
                opr[q,1]:=x; opr[q,2]:=y; opr[q,3]:=ord(ch='C');
                if (ch='Q')and(x<>y) then
                begin
                        add_qedge(x,y,q);
                        add_qedge(y,x,q);
                end;
                read(ch);
        end;
        readln;
        fillchar(fa,sizeof(fa),0);
        lca(1);
        
        // work
        for i:=1 to q do
        begin
                x:=opr[i,1]; y:=opr[i,2];
                if opr[i,3]=1 then change(1,1,loc_cnt,locate[link[x]],y)
                              else query(x,y);
        end;
end;

begin
        assign(input,'1.in');reset(input);
        assign(output,'1.out');rewrite(output);
        readln(test);
        while test>0 do
        begin
                solve;
                dec(test);
        end;
        close(input);close(output);
end.
