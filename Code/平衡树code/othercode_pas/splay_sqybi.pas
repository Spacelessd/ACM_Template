{
superbt
- sqybi's code
- Splay
}
//for my winsty
program superbt_sqybi;
const
    fin = 'superbt.in';
    fout = 'superbt.out';
    nn = 10000000;
    unable = 100000000;

type
    TSplayTree = object
      private
        root, nodeNum: longint;
        data, father: array[1..nn]of longint;
        size: array[0..nn]of longint;
        son: array[0..1, 1..nn]of longint;
        procedure updateSize(x: longint);
        procedure rotate(w, x: longint);
        procedure splay(x, y: longint);
        procedure addNode(x, y, z: longint);
        procedure insert(x: longint);
        function findPlace(x: longint): longint;
        function exist(x: longint): boolean;
        procedure delete(x: longint);
        function rank(x: longint): longint;
      public
        procedure init;
        procedure insertNum(x: longint);
        procedure deleteNum(x: longint);
        function askExist(x: longint): longint;
        function smallNum(x: longint): longint;
        procedure deleteNums(x: longint);
        function calSmall(x: longint): longint;
        function askMaxSmall(x: longint): longint;
        function askMinBig(x: longint): longint;
    end;

var
    op: char;
    k: longint;
    tree: TSplayTree;

//private functions
procedure TSplayTree.updateSize(x: longint);
    begin
      size[x] := size[son[0, x]] + size[son[1, x]] + 1;
    end;

procedure TSplayTree.rotate(w, x: longint); //w=0 means left rotate
    var
      y: longint;
    begin
      y := father[x];
      son[1-w, y] := son[w, x];
      if son[w, x] <> 0 then
        father[son[w, x]] := y;
      father[x] := father[y];
      if father[y] <> 0 then
        if y = son[0, father[y]] then
          son[0, father[y]] := x
        else
          son[1, father[y]] := x;
      son[w, x] := y;
      father[y] := x;
      updateSize(y);
      updateSize(x);
    end;

procedure TSplayTree.splay(x, y: longint);
    begin
      while father[x] <> y do begin
        if father[father[x]] = y then begin
          if x = son[0, father[x]] then
            rotate(1, x)
          else
            rotate(0, x);
        end
        else begin
          if father[x] = son[0, father[father[x]]] then begin
            if x = son[0, father[x]] then begin
              rotate(1, father[x]);
              rotate(1, x);
            end
            else begin
              rotate(0, x);
              rotate(1, x);
            end;
          end
          else begin
            if x = son[1, father[x]] then begin
              rotate(0, father[x]);
              rotate(0, x);
            end
            else begin
              rotate(1, x);
              rotate(0, x);
            end;
          end;
        end;
      end;
      if y = 0 then
        root := x;
    end;

procedure TSplayTree.addNode(x, y, z: longint);
    begin
      data[x] := z;
      father[x] := y;
      son[0, x] := 0;
      son[1, x] := 0;
      size[x] := 1;
    end;

procedure TSplayTree.insert(x: longint);
    var
      y: longint;
    begin
      if root = 0 then begin
        root := 1;
        nodeNum := 1;
        addNode(1, 0, x);
        exit;
      end;
      y := root;
      repeat
        inc(size[y]);
        if x < data[y] then begin
          if son[0, y] <> 0 then
            y := son[0, y]
          else begin
            inc(nodeNum);
            addNode(nodeNum, y, x);
            son[0, y] := nodeNum;
            y := nodeNum;
            break;
          end;
        end
        else begin
          if son[1, y] <> 0 then
            y := son[1, y]
          else begin
            inc(nodeNum);
            addNode(nodeNum, y, x);
            son[1, y] := nodeNum;
            y := nodeNum;
            break;
          end;
        end; 
      until false;
      splay(y, 0);
    end;

function TSplayTree.findPlace(x: longint): longint;
    var
      y: longint;
    begin
      y := root;
      repeat
        if data[y] = x then break;
        if x < data[y] then begin
          if son[0, y] = 0 then
            break
          else
            y := son[0, y];
        end
        else begin
          if son[1, y] = 0 then
            break
          else
            y := son[1, y];
        end;
      until false;
      findPlace := y;
      splay(y, 0);
    end;

function TSplayTree.exist(x: longint): boolean;
    var
      y: longint;
    begin
      y := root;
      while (y <> 0) and (data[y] <> x) do
        if x < data[y] then
          y := son[0, y]
        else
          y := son[1, y];
      exist := y <> 0;
      if y <> 0 then splay(y, 0);
    end;

procedure TSplayTree.delete(x: longint);
    var
      y, z: longint;
    begin
      y := findPlace(x);
      splay(y, 0);
      if son[0, y] = 0 then begin
        if son[1, y] = 0 then
          init
        else begin
          root := son[1, y];
          father[son[1, y]] := 0;
        end;
      end
      else begin
        z := son[0, y];
        while son[1, z] <> 0 do z := son[1, z];
        splay(z, y);
        son[1, z] := son[1, y];
        if son[1, y] <> 0 then father[son[1, y]] := z;
        father[z] := 0;
        root := z;
        updateSize(z);
      end;
    end;

function TSplayTree.rank(x: longint): longint;
    var
      y: longint;
    begin
      y := root;
      while true do begin
        if x <= size[son[0, y]] then
          y := son[0, y]
        else if x = size[son[0, y]] + 1 then
          break
        else begin
          x := x - size[son[0, y]] - 1;
          y := son[1, y];
        end;
      end;
      rank := data[y];
      splay(y, 0);
    end;

//public functions
procedure TSplayTree.init;
    begin
      root := 0;
      nodeNum := 0;
    end;

procedure TSplayTree.insertNum(x: longint);
    begin
      insert(x);
    end;

procedure TSplayTree.deleteNum(x: longint);
    begin
      if exist(x) then delete(x);
    end;

function TSplayTree.askExist(x: longint): longint;
    begin
      askExist := ord(exist(x));
    end;

function TSplayTree.smallNum(x: longint): longint;
    begin
      smallNum := rank(x);
    end;

procedure TSplayTree.deleteNums(x: longint);
    var
      y: longint;
    begin
      if root = 0 then exit;
      y := findPlace(x);
      splay(y, 0);
      son[1, y] := 0;
      updateSize(y);
      if data[y] >= x then
        if son[0, y] = 0 then
          init
        else begin
          root := son[0, y];
          father[son[0, y]] := 0;
        end;
    end;

function TSplayTree.calSmall(x: longint): longint;
    var
      y: longint;
    begin
      if root = 0 then begin
        calSmall := 0;
        exit;
      end;
      y := findPlace(x);
      splay(y, 0);
      calSmall := size[son[0, y]] + ord(data[y] <= x);
    end;

function TSplayTree.askMaxSmall(x: longint): longint;
    var
      y: longint;
    begin
      if root = 0 then begin
        askMaxSmall := 0;
        exit;
      end;
      y := findPlace(x);
      splay(y, 0);
      if data[y] > x then begin
        y := son[0, y];
        if y = 0 then begin
          askMaxSmall := 0;
          exit;
        end;
        while son[1, y] <> 0 do
          y := son[1, y];
      end;
      askMaxSmall := data[y];
    end;

function TSplayTree.askMinBig(x: longint): longint;
    var
      y: longint;
    begin
      if root = 0 then begin
        askMinBig := unable;
        exit;
      end;
      y := findPlace(x);
      splay(y, 0);
      if data[y] < x then begin
        y := son[1, y];
        if y = 0 then begin
          askMinBig := unable;
          exit;
        end;
        while son[0, y] <> 0 do
          y := son[0, y];
      end;
      askMinBig := data[y];
    end;

//main
begin
    assign(input, fin);
    assign(output, fout);
    reset(input);
    rewrite(output);

    tree.init;
    repeat
      read(op);
      if op = 'e' then break;
      case op of
        'i': //插入值为k的元素
          begin
            readln(k);
            tree.insertNum(k);
          end;
        'd': //删除值为k的元素
          begin
            readln(k);
            tree.deleteNum(k);
          end;
        'a': //询问k是否存在
          begin
            readln(k);
            writeln(tree.askExist(k));
          end;
        'r': //询问第k小元素
          begin
            readln(k);
            writeln(tree.smallNum(k));
          end;
        'D': //删除大于等于k的元素
          begin
            readln(k);
            tree.deleteNums(k);
          end;
        's': //询问小于等于k的元素个数
          begin
            readln(k);
            writeln(tree.calSmall(k));
          end;
        'l': //询问小于等于k的最大元素
          begin
            readln(k);
            writeln(tree.askMaxSmall(k));
          end;
        'u': //询问大于等于k的最小元素
          begin
            readln(k);
            writeln(tree.askMinBig(k));
          end;
      end;
    until false;

    close(input);
    close(output);
end.
