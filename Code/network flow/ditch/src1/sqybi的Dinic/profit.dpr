{
NOI 2007; 最大获利; profit
- sqybi’s code
- 最小切割最大流
- Dinic
}
//for my winsty
program profit_sqybi;
  const
    fin ='profit.in';
    fout ='profit.out';
    nn = 5000;
    mm = 50000;
    tt = nn + mm + 2;
    ee = mm * 3 + nn;

  var
    n, m, i, s, t, r, x, y, z, edgeNum: longint;
    adj, next, c, f: array[-ee..ee]of longint;
    head, dist, place: array[1..tt]of longint;
  function min(x, y: longint): longint; 
    begin
      if x < y then
        min := x
      else
        min := y;
    end;

  procedure addEdge(x, y, z: longint); 
    begin
      inc(edgeNum);
      adj[edgeNum] := y;
      next[edgeNum] := head[x];
      head[x] := edgeNum;
      c[edgeNum] := z;
      f[edgeNum] := 0;
      adj[-edgeNum] := x;
      next[-edgeNum] := head[y];
      head[y] := -edgeNum;
      c[-edgeNum] := 0;
      f[-edgeNum] := 0;
    end;

  function bfs: boolean; 
    var
      now, temp, qs, qe: longint;
      q: array[1..tt]of longint;
      v: array[1..tt]of boolean;
    begin
      fillchar(dist, sizeof(dist), 0);
      qs := 1;
      qe := 1;
      q[1] := s;
      fillchar(v, sizeof(v), false);
      v[1] := true;
      while qs <= qe do begin
        now := q[qs];
        temp := head[now];
        while temp <> 0 do begin
          if (not v[adj[temp]]) and (f[temp] < c[temp]) then begin
            v[adj[temp]] := true;
            inc(qe);
            q[qe] := adj[temp];
            dist[adj[temp]] := dist[now] + 1;
          end;
          temp := next[temp];
        end;
        inc(qs);
      end;
      bfs := dist[t] <> 0;
    end;

  function dfs(x, d: longint): longint; 
    var
      delta, temp, r: longint;
    begin
      if x = t then begin
        dfs := d;
        exit;
      end;
      temp := place[x];
      delta := 0;
      while temp <> 0 do begin
        if (dist[adj[temp]] = dist[x] + 1) and (f[temp] < c[temp]) then begin
          r := dfs(adj[temp], min(c[temp]-f[temp], d-delta));
          f[temp] := f[temp] + r;
          f[-temp] := -f[temp];
          delta := delta + r;
          if delta = d then break;
        end;
        temp := next[temp];
      end;
      place[x] := temp;
      dfs := delta;
    end;

  begin
    assign(input, fin);
    assign(output, fout);
    reset(input);
    rewrite(output);

    readln(n, m);
    s := 1;
    t := m + n + 2;
    for i:=1 to n do begin
      read(x);
      addEdge(m+1+i, t, x);
    end;
    readln;
    r := 0;
    for i:=1 to m do begin
      readln(x, y, z);
      r := r + z;
      addEdge(s, i+1, z);
      addEdge(i+1, m+1+x, maxlongint);
      addEdge(i+1, m+1+y, maxlongint);
    end;

    while bfs do begin
      place := head;
      r := r - dfs(s, maxlongint);
    end;

    writeln(r);

    close(input);
    close(output);
  end.