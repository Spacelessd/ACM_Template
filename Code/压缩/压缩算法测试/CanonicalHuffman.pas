//
//范式哈夫曼编码算法的实现
//作者：叶叶　2010年7月5日
//
//本文件版权由叶叶拥有，保留所有权利。
//本文件中的代码是免费程序，无需任何授权或许可即可用于个人和商业目的。使用者一切后果自负。
//
//如果你转载了本文件中的代码，请注明代码出处和代码作者；
//如果你修改了本文件中的代码，请注明修改位置和修改作者；
//
//本文件是论文《范式哈夫曼算法的分析与实现》的配套程序。
//本文件最早在http://programbbs.com/bbs/上发布。
//

unit CanonicalHuffman;

interface

uses
    MemoryBuffer;

const
    //限制编码位长，程序中用Cardinal类型保存编码，长度限制32位
    CH_MAXLENGTH = 32;

type
    //符号类型，根据需要可以修改为Word或Byte
    TCHSymbol = Integer;

    //范式哈夫曼编码器
    TCHEncode = class
    private
        FContent : Integer; //符号信息量
        FBuf : array of Cardinal; //缓冲区，长度为FContent*2

        FHeapCount : Integer; //堆中元素个数
        FMaxBitLen : Integer; //实际最大编码位长

        FOutBuf : PMBBuffer; //输出缓冲区

        FEncode : TCHEncode; //编码器，用以码表二次压缩

        procedure HeapInsert(Id : Cardinal);
        procedure HeapDelete;
        procedure LengthLimited;
    public
        Freq : PMBCardinalAry; //频度表

        constructor Create;
        destructor Destroy; override;

        //编码操作
        procedure InitEncode(OutBuf : PMBBuffer; Content : Integer);
        procedure AllocCode;
        procedure SaveBitLenG;
        procedure SaveBitLenH;
        procedure Encode(Symbol : TCHSymbol);
        procedure FinishEncode;
    end;

    //范式哈夫曼解码器
    TCHDecode = class
    private
        FContent : Integer; //符号信息量
        FSymList : array of TCHSymbol; //经过排序的符号列表，长度为FContent

        FMaxBitLen : Integer; //实际最大编码位长

        FFirstCode : array [1..CH_MAXLENGTH] of Cardinal; //每个位长的首编码
        FSymCount : array [1..CH_MAXLENGTH] of Integer; //每个位长的符号数
        FSymIndex : array [1..CH_MAXLENGTH] of Integer; //每个位长对应的符号在FSymList中开始的位置

        FFastLen : Integer; //快表位长
        FFastSymList : array of TCHSymbol; //快表符号列表，长度为1 shl FFastLen
        FFastBitLen : array of Byte; //快表位长列表，长度为1 shl FFastLen

        FInBuf : PMBBuffer; //输入缓冲区

        FDecode : TCHDecode; //解码器，用以码表二次解压缩

        procedure Construct;
    public
        constructor Create;
        destructor Destroy; override;

        //解码操作
        procedure InitDecode(InBuf : PMBBuffer; Content : Integer; FastLen : Integer);
        procedure LoadBitLenG;
        procedure LoadBitLenH;
        function Decode: TCHSymbol;
        procedure FinishDecode;
    end;

    //范式哈夫曼编解码器，对TCHEncode和TCHDecode的简单封装
    TCHCoding = class
    private
        FEncode : TCHEncode; //编码器
        FDecode : TCHDecode; //解码器
    public
        constructor Create;
        destructor Destroy; override;

        function Encode(var InBuf,OutBuf : TMBBuffer; Size : Integer): Integer;
        function Decode(var InBuf,OutBuf : TMBBuffer): Integer;

        function Encode16(var InBuf,OutBuf : TMBBuffer; Size : Integer): Integer;
        function Decode16(var InBuf,OutBuf : TMBBuffer): Integer;
    end;


implementation

{TCHEncode} //范式哈夫曼编码器

//新建范式哈夫曼编码器。
constructor TCHEncode.Create;
begin
    self.FContent:=0;
    SetLength(self.FBuf,0);

    self.FEncode:=nil;

    self.Freq:=nil;
end;

//销毁范式哈夫曼编码器。
destructor TCHEncode.Destroy;
begin
    SetLength(self.FBuf,0);
    if self.FEncode<>nil then self.FEncode.Free;
end;

//将指定频度插入堆，以频度为关键字的最小堆，堆和频度都保存在FBuf中，
//Id是频度在FBuf中的索引，频度位于FBuf的右边，
//插入后索引将保存到堆中，索引位于FBuf的左边，
//Id：频度的索引。
procedure TCHEncode.HeapInsert(Id : Cardinal);
var
    Parent,Child : Integer;
begin
    //空堆
    if self.FHeapCount=0 then
    begin
        self.FBuf[0]:=Id;
        Inc(self.FHeapCount);
        exit;
    end;

    //插入频度
    Child:=self.FHeapCount;
    Parent:=((Child+1) shr 1)-1;
    while self.FBuf[self.FBuf[Parent]]>self.FBuf[Id] do
    begin
        self.FBuf[Child]:=self.FBuf[Parent];
        Child:=Parent;
        if Parent=0 then break;
        Parent:=((Parent+1) shr 1)-1;
    end;
    self.FBuf[Child]:=Id;
    Inc(self.FHeapCount);
end;

//从堆中删除一个频度，删除频度的相关索引移动到当前堆的末尾。
procedure TCHEncode.HeapDelete;
var
    Id : Cardinal;
    Parent,Child : Integer;
begin
    Id:=self.FBuf[0];
    Dec(self.FHeapCount);

    //删除频度
    Parent:=0;
    Child:=1;
    while Child<=self.FHeapCount do
    begin
        if (Child<self.FHeapCount) and
           (self.FBuf[self.FBuf[Child]]>
            self.FBuf[self.FBuf[Child+1]]) then Inc(Child);

        if self.FBuf[self.FBuf[Child]]>=
           self.FBuf[self.FBuf[self.FHeapCount]] then break;

        self.FBuf[Parent]:=self.FBuf[Child];
        Parent:=Child;
        Child:=((Child+1) shl 1)-1;
    end;
    self.FBuf[Parent]:=self.FBuf[self.FHeapCount];
    self.FBuf[self.FHeapCount]:=Id;
end;

//限制编码位长，当计算的编码位长大于限制位长时，
//该函数负责对位长进行重新整理，使其符合限制位长的大小，
//调用该函数前必需将编码位长保存在FBuf[FContent..FContent*2-1]中，
//函数运行时会用FBuf的前半部份保存排序索引数据。
procedure TCHEncode.LengthLimited;
var
    Num : array of Integer;
    i,SymCount,Id,Sum,t : Integer;
    Val1,Val2 : Cardinal;
begin
    //基数排序，以位长作为第一关键字，符号值作为第二关键字，
    //从小到大排序，排序后的索引保存到FBuf[0..FContent-1]中
    SetLength(Num,self.FMaxBitLen+1);

    SymCount:=0; //实际出现的符号数
    for i:=self.FContent to (self.FContent*2)-1 do
    begin
        if self.FBuf[i]<>0 then
        begin
            Inc(Num[self.FBuf[i]]); Inc(SymCount);
        end;
    end;

    Sum:=0;
    for i:=1 to self.FMaxBitLen do
    begin
        t:=Num[i]; Num[i]:=Sum; Inc(Sum,t);
    end;

    for i:=self.FContent to (self.FContent*2)-1 do
    begin
        if self.FBuf[i]<>0 then
        begin
            self.FBuf[Num[self.FBuf[i]]]:=i;
            Inc(Num[self.FBuf[i]]);
        end;
    end;

    SetLength(Num,0); //排序完成

    //重新调整编码位长
    Id:=SymCount-1;
    repeat
        {//严重溢出，无法调整（可能性极低）
        if self.FBuf[self.FBuf[0]]>=CH_MAXLENGTH then
        begin
            raise Exception.Create('位长溢出，无法分配编码！');
        end;//}

        //向前查找小于限制位长的位长
        for i:=Id downto 0 do
        begin
            if self.FBuf[self.FBuf[i]]<CH_MAXLENGTH then
            begin
                Id:=i; break;
            end;
        end;

        //调整
        Inc(self.FBuf[self.FBuf[Id]]);
        Val1:=self.FBuf[self.FBuf[SymCount-1]]-1;

        for i:=SymCount-3 downto Id do
        begin
            Val2:=self.FBuf[self.FBuf[i]];
            if Val1>=Val2 then
            begin
                self.FBuf[self.FBuf[i+2]]:=Val1;
                break;
            end;
            self.FBuf[self.FBuf[i+2]]:=Val2;
        end;
        for i:=i downto Id do
        begin
            self.FBuf[self.FBuf[i+1]]:=self.FBuf[self.FBuf[i]];
        end;

        Inc(Id); //从调整的新位置开始

        self.FMaxBitLen:=self.FBuf[self.FBuf[SymCount-1]];

    until self.FMaxBitLen<=CH_MAXLENGTH;

    //完成
end;

//初始化编码器，并将编码器与指定输出缓冲区绑定，
//OutBuf：输出缓冲区；
//Content：符号信息量。
procedure TCHEncode.InitEncode(OutBuf : PMBBuffer; Content : Integer);
var
    i : Integer;
begin
    self.FOutBuf:=OutBuf;

    //分配缓冲区
    if Content>self.FContent then SetLength(self.FBuf,Content*2);
    self.FContent:=Content;

    //频度清零
    self.Freq:=@(self.FBuf[self.FContent]);
    for i:=0 to self.FContent-1 do self.Freq[i]:=0;
end;

//计算符号的编码位长，分配编码，同时计算最大编码位长FMaxBitLen，
//调用该函数前必需将符号频度保存在Freq中，
//（注：Freq指向缓冲区FBuf[FContent..FContent*2-1]），
//函数运行时会用FBuf的前半部份保存临时数据，
//函数结束后分配的编码保存到FBuf[0..FContent-1]中，
//编码位长保存到FBuf[FContent..FContent*2-1]中，
//原有的频度数据将会被替换掉。
procedure TCHEncode.AllocCode;
var
    i : Integer;
    Id0,Id1,Id2 : Cardinal;
    Code,t : Cardinal;
    Num : array [1..CH_MAXLENGTH] of Cardinal;
begin
    self.Freq:=nil; //保护数据

    //频度插入堆中，堆数据保存到FBuf[0..FContent-1]中
    self.FHeapCount:=0;
    for i:=self.FContent to (self.FContent*2)-1 do
    begin
        if self.FBuf[i]<>0 then self.HeapInsert(i);
    end;

    //只出现一种符号
    if self.FHeapCount=1 then
    begin
        self.FBuf[self.FBuf[0]]:=1;
        self.FBuf[self.FBuf[0]-Cardinal(self.FContent)]:=0;
        self.FMaxBitLen:=1;
        exit;
    end;

    //多余部份清零
    for i:=self.FHeapCount to self.FContent-1 do self.FBuf[i]:=0;

    //排序整理
    repeat
        //从堆中取出两个频度
        Id0:=self.FHeapCount-1;
        self.HeapDelete;
        self.HeapDelete;

        //合并频度
        Id1:=self.FBuf[Id0];
        Id2:=self.FBuf[Id0-1];
        self.FBuf[Id0]:=self.FBuf[Id1]+self.FBuf[Id2];

        //建立关系
        self.FBuf[Id1]:=Id0;
        self.FBuf[Id2]:=Id0;

        //重新插入堆
        self.HeapInsert(Id0);

    until self.FHeapCount=1;

    //计算位长，数据保存到FBuf[FContent..FConten*2-1]中
    self.FMaxBitLen:=0;
    self.FBuf[1]:=0;
    for i:=2 to (self.FContent*2)-1 do
    begin
        if self.FBuf[i]<>0 then
        begin
            self.FBuf[i]:=self.FBuf[self.FBuf[i]]+1;
            if self.FBuf[i]>Cardinal(self.FMaxBitLen) then
            begin
                self.FMaxBitLen:=self.FBuf[i];
            end;
        end;
    end;

    //位长溢出
    if self.FMaxBitLen>CH_MAXLENGTH then self.LengthLimited;

    //计算同组序号，数据保存到FBuf[0..FContent-1]中
    for i:=1 to self.FMaxBitLen do Num[i]:=0;

    for i:=self.FContent to (self.FContent*2)-1 do
    begin
        if self.FBuf[i]<>0 then
        begin
            self.FBuf[i-self.FContent]:=Num[self.FBuf[i]];
            Inc(Num[self.FBuf[i]]);
        end;
    end;

    //计算首编码
    Code:=0;
    for i:=1 to self.FMaxBitLen do
    begin
        t:=Num[i]; Num[i]:=Code; Code:=(Code+t) shl 1;
    end;

    //分配编码，数据保存到FBuf[0..FContent-1]中
    for i:=0 to self.FContent-1 do
    begin
        Inc(self.FBuf[i],Num[self.FBuf[i+self.FContent]]);
    end;

    //完成
end;

//利用指数哥伦布算法对码表进行压缩并写入到缓冲区FOutBuf中，
//缓冲区不足时扩展缓冲区，
//根据FOutBuf.Offset确定写入位置，写入后修改FOutBuf.Offset，
//调用该函数前要先确保已经调用过AllocCode分配编码。
procedure TCHEncode.SaveBitLenG;
var
    Id,n : Integer;
begin
    //写入最大位长
    MBEncodeEG(self.FOutBuf^,self.FMaxBitLen);

    //写入位长数据
    Id:=self.FContent;
    while Id<(self.FContent*2) do
    begin
        if self.FBuf[Id]=0 then
        begin
            //计算为0的位长数据个数
            n:=Id; Inc(Id);
            while (Id<(self.FContent*2)) and (self.FBuf[Id]=0) do Inc(Id);
            n:=Id-n;

            //写入数据
            MBEncodeEG(self.FOutBuf^,0);
            MBEncodeEG(self.FOutBuf^,n);
        end
        else
        begin
            //写入不为0的位长数据
            MBEncodeEG(self.FOutBuf^,Cardinal(self.FMaxBitLen)-self.FBuf[Id]+1);
            Inc(Id);
        end;
    end;

    //完成
end;

//利用哈夫曼算法对码表进行压缩并写入到缓冲区FOutBuf中，
//缓冲区不足时扩展缓冲区，
//根据FOutBuf.Offset确定写入位置，写入后修改FOutBuf.Offset，
//调用该函数前要先确保已经调用过AllocCode分配编码。
procedure TCHEncode.SaveBitLenH;
var
    Id,n : Integer;
begin
    //写入最大位长
    MBEncodeEG(self.FOutBuf^,self.FMaxBitLen);

    //建立编码器
    if self.FEncode=nil then self.FEncode:=TCHEncode.Create;
    self.FEncode.InitEncode(self.FOutBuf,self.FMaxBitLen+1);

    //统计频度
    Id:=self.FContent;
    while Id<(self.FContent*2) do
    begin
        if self.FBuf[Id]=0 then
        begin
            Inc(self.FEncode.Freq[0]); //重复的0只统计1次
            Inc(Id);

            //跳过重复为0的位长数据
            while (Id<(self.FContent*2)) and (self.FBuf[Id]=0) do Inc(Id);
        end
        else
        begin
            //不为0的位长数据
            Inc(self.FEncode.Freq[self.FBuf[Id]]);
            Inc(Id);
        end;
    end;

    //分配编码并保存码表
    self.FEncode.AllocCode;
    self.FEncode.SaveBitLenG;

    //编码
    Id:=self.FContent;
    while Id<(self.FContent*2) do
    begin
        if self.FBuf[Id]=0 then
        begin
            //写入数据
            self.FEncode.Encode(0);

            //计算为0的位长数据个数并写入
            n:=Id; Inc(Id);
            while (Id<(self.FContent*2)) and (self.FBuf[Id]=0) do Inc(Id);
            n:=Id-n;

            MBEncodeEG(self.FOutBuf^,n);
        end
        else
        begin
            //写入不为0的位长数据
            self.FEncode.Encode(self.FBuf[Id]);
            Inc(Id);
        end;
    end;
    self.FEncode.FinishEncode;

    //完成
end;

//编码一个符号并写入到缓冲区FOutBuf中，
//根据FOutBuf.Offset确定写入位置，写入后修改FOutBuf.Offset，
//Symbol：符号。
procedure TCHEncode.Encode(Symbol : TCHSymbol);
begin
    MBWriteBit(
        self.FOutBuf^,
        self.FBuf[Symbol],
        self.FBuf[Symbol+self.FContent]);
end;

//结束编码，进行收尾操作。
procedure TCHEncode.FinishEncode;
begin
    self.FOutBuf:=nil;
end;

{TCHDecode} //范式哈夫曼解码器

//新建范式哈夫曼解码器。
constructor TCHDecode.Create;
begin
    self.FContent:=0;
    SetLength(self.FSymList,0);

    self.FFastLen:=0;
    SetLength(self.FFastSymList,0);
    SetLength(self.FFastBitLen,0);

    self.FDecode:=nil;
end;

//销毁范式哈夫曼解码器。
destructor TCHDecode.Destroy;
begin
    SetLength(self.FSymList,0);
    SetLength(self.FFastSymList,0);
    SetLength(self.FFastBitLen,0);

    if self.FDecode<>nil then self.FDecode.Free;
end;

//初始化解码器，并将解码器与指定输入缓冲区绑定，
//InBuf：输入缓冲区；
//Content：符号信息量
//FastLen：快表位长。
procedure TCHDecode.InitDecode(InBuf : PMBBuffer; Content : Integer; FastLen : Integer);
begin
    self.FInBuf:=InBuf;

    //分配缓冲区
    if Content>self.FContent then SetLength(self.FSymList,Content);
    self.FContent:=Content;

    self.FFastLen:=FastLen;
end;

//构建解码所需的各种数据表，
//调用该函数前必需将编码位长保存在FSymList中。
procedure TCHDecode.Construct;
var
    i,t,l,m,Sum : Integer;
    Id1,Id2,Sym1,Sym2 : Integer;
    Flag : array of Cardinal;
    Code : Cardinal;
begin
    //基数排序，以位长作为第一关键字，符号值作为第二关键字，
    //排序索引保存到FSymList中，原位长数据将会被替换，
    //同时统计每个位长的符号数，保存到FSymCount中
    for i:=1 to self.FMaxBitLen do self.FSymCount[i]:=0;

    for i:=0 to self.FContent-1 do
    begin
        if self.FSymList[i]<>0 then Inc(self.FSymCount[self.FSymList[i]]);
    end;

    Sum:=0;
    for i:=1 to self.FMaxBitLen do
    begin
        self.FSymIndex[i]:=Sum;
        Inc(Sum,self.FSymCount[i]);
    end;

    for i:=0 to self.FContent-1 do
    begin
        t:=self.FSymList[i];
        if t<>0 then
        begin
            self.FSymList[i]:=self.FSymIndex[t]+1; //+1避免现出0
            Inc(self.FSymIndex[t]);
        end;
    end;

    //按排序索引整理符号，
    //经过排序的符号保存到FSymList中，原排序索引将会被替换
    t:=(self.FContent+31) shr 5;
    SetLength(Flag,t);

    for i:=0 to self.FContent-1 do
    begin
        if (self.FSymList[i]=0) or
           ((Flag[i shr 5] and (1 shl (i and 31)))<>0) then continue;

        //调整位置
        Sym2:=i;
        Id2:=self.FSymList[i];
        self.FSymList[i]:=0;
        repeat
            Sym1:=Sym2;
            Id1:=Id2-1;

            Sym2:=Id1;
            Id2:=self.FSymList[Id1];

            self.FSymList[Id1]:=Sym1;
            Flag[Id1 shr 5]:=Flag[Id1 shr 5] or (1 shl (Id1 and 31));

        until Id2=0;
    end;

    SetLength(Flag,0);

    //计算首编码FFirstCode和符号索引FSymIndex
    Code:=0;
    Sum:=0;
    for i:=1 to self.FMaxBitLen do
    begin
        self.FFirstCode[i]:=Code;
        Code:=(Code+Cardinal(self.FSymCount[i])) shl 1;

        self.FSymIndex[i]:=Sum;
        Inc(Sum,self.FSymCount[i]);
    end;

    //计算快表
    if self.FFastLen=0 then exit;
    if self.FFastLen>self.FMaxBitLen then self.FFastLen:=self.FMaxBitLen;
    if (1 shl self.FFastLen)>Length(self.FFastSymList) then
    begin
        SetLength(self.FFastSymList,1 shl self.fFastLen);
        SetLength(self.FFastBitLen,1 shl self.fFastLen);
    end;

    //编码位长小于快表位长的情况
    Id1:=0;
    for i:=1 to self.FFastLen-1 do
    begin
        t:=(1 shl (self.FFastLen-i))-1;

        for l:=0 to self.FSymCount[i]-1 do
        begin
            Sym1:=self.FSymList[self.FSymIndex[i]+l];

            for m:=0 to t do
            begin
                self.FFastSymList[Id1]:=Sym1;
                self.FFastBitLen[Id1]:=i;
                Inc(Id1);
            end;
        end;
    end;

    //编码位长等于快表位长的情况
    for l:=0 to self.FSymCount[self.FFastLen]-1 do
    begin
        self.FFastSymList[Id1]:=self.FSymList[self.FSymIndex[self.FFastLen]+l];
        self.FFastBitLen[Id1]:=self.FFastLen;
        Inc(Id1);
    end;

    //编码位长大于快表位长的情况
    for i:=self.FFastLen+1 to self.FMaxBitLen do
    begin
        t:=i-self.FFastLen;

        for l:=0 to self.FSymCount[i]-1 do
        begin
            if Id1=Integer((self.FFirstCode[i]+Cardinal(l)) shr t) then
            begin
                self.FFastSymList[Id1]:=0; //符号不确定
                self.FFastBitLen[Id1]:=i;
                Inc(Id1);
            end;
        end;
    end;

    //完成
end;

//利用指数哥伦布算法从FInBuf中读取经过压缩的码表，
//缓冲区中的压缩码表必需是使用TCHEncode.SaveBitLenG保存的，
//根据FInBuf.Offset确定读取位置，读取后修改FInBuf.Offset，
//导入码表后该函数会调用Construct构建解码表。
procedure TCHDecode.LoadBitLenG;
var
    Id,n,i : Integer;
begin
    //读取最大位长
    self.FMaxBitLen:=MBDecodeEG(self.FInBuf^);

    //读取位长数据
    Id:=0;
    while Id<self.FContent do
    begin
        n:=MBDecodeEG(self.FInBuf^);
        if n=0 then
        begin
            //为0的位长数据
            n:=MBDecodeEG(self.FInBuf^);
            for i:=1 to n do
            begin
                self.FSymList[Id]:=0; Inc(Id);
            end;
        end
        else
        begin
            //不为0的位长数据
            self.FSymList[Id]:=self.FMaxBitLen-n+1;
            Inc(Id);
        end;
    end;

    //构建解码表
    self.Construct;

    //完成
end;

//利用哈夫曼算法从FInBuf中读取经过压缩的码表，
//缓冲区中的压缩码表必需是使用TCHEncode.SaveBitLenH保存的，
//根据FInBuf.Offset确定读取位置，读取后修改FInBuf.Offset，
//导入码表后该函数会调用Construct构建解码表。
procedure TCHDecode.LoadBitLenH;
var
    Id,i,n : Integer;
begin
    //读取最大位长
    self.FMaxBitLen:=MBDecodeEG(self.FInBuf^);

    //建立编码器
    if self.FDecode=nil then self.FDecode:=TCHDecode.Create;
    self.FDecode.InitDecode(self.FInBuf,self.FMaxBitLen+1,8);
    self.FDecode.LoadBitLenG;

    //读取位长数据
    Id:=0;
    while Id<self.FContent do
    begin
        n:=self.FDecode.Decode;
        if n=0 then
        begin
            //为0的位长数据
            n:=MBDecodeEG(self.FInBuf^);
            for i:=1 to n do
            begin
                self.FSymList[Id]:=0; Inc(Id);
            end;
        end
        else
        begin
            //不为0的位长数据
            self.FSymList[Id]:=n;
            Inc(Id);
        end;
    end;
    self.FDecode.FinishDecode;

    //构建解码表
    self.Construct;

    //完成
end;

//从缓冲区FInBuf中解码出一个符号，并返回，
//根据FInBuf.Offset确定读取位置，读取后修改FInBuf.Offset。
function TCHDecode.Decode: TCHSymbol;
var
    Code : Cardinal;
    LastOff,Id,Num : Integer;
begin
    Result:=0;

    with self.FInBuf^ do
    begin
        if DataType<>dtBit then MBSetType(self.FInBuf^,dtBit);
        LastOff:=Offset;
    end;

    //一次性读取32位数据
    Code:=MBReadBit(self.FInBuf^,32);

    //查找快表
    if self.FFastLen=0 then Id:=1
    else
    begin
        Id:=Code shr (32-self.FFastLen);

        if self.FFastBitLen[Id]<=self.FFastLen then
        begin
            //直接命中
            Result:=self.FFastSymList[Id];
            self.FInBuf.Offset:=LastOff+self.FFastBitLen[Id];
            exit;
        end
        else
        begin
            //没有命中
            Id:=self.FFastBitLen[Id];
        end;
    end;

    //解码
    for Id:=Id to self.FMaxBitLen do
    begin
        if self.FSymCount[Id]<>0 then
        begin
            Num:=(Code shr (32-Id))-self.FFirstCode[Id];

            if Num<self.FSymCount[Id] then
            begin
                Result:=self.FSymList[self.FSymIndex[Id]+Num];
                break;
            end;
        end;
    end;

    //更新位置
    self.FInBuf.Offset:=LastOff+Id;

    //完成
end;

//结束解码，进行收尾操作。
procedure TCHDecode.FinishDecode;
begin
    self.FInBuf:=nil;
end;

{TCHCoding} //范式哈夫曼编解码器，对TCHEncode和TCHDecode的简单封装

//新建范式哈夫曼编解码器。
constructor TCHCoding.Create;
begin
    self.FEncode:=nil;
    self.FDecode:=nil;
end;

//销毁范式哈夫曼编解码器。
destructor TCHCoding.Destroy;
begin
    if self.FEncode<>nil then self.FEncode.Free;
    if self.FDecode<>nil then self.FDecode.Free;
end;

//从缓冲区InBuf中读取Size长度的数据进行压缩并保存到缓冲区OutBuf中，
//返回写入到缓冲区OutBuf中数据的大小（字节），
//缓冲区OutBuf不足时扩展缓冲区，
//根据InBuf.Offset确定读取位置，读取后修改InBuf.Offset，
//根据OutBuf.Offset确定写入位置，写入后修改OutBuf.Offset，
//InBuf：输入缓冲区；
//OutBuf：输出缓冲区；
//Size：数据大小（字节）。
function TCHCoding.Encode(var InBuf,OutBuf : TMBBuffer; Size : Integer): Integer;
var
    i,ReadSize,NeedSize,LastOff : Integer;
    Dest : PMBByteAry;
begin
    with InBuf do
    begin
        if DataType<>dtByte then MBSetType(InBuf,dtByte);

        //判断可读长度
        ReadSize:=BufSize-Offset;
        if ReadSize<=0 then
        begin
            Result:=0; exit;
        end;
        if ReadSize>Size then ReadSize:=Size;

        //计算并更新位置
        Dest:=@(Mem8[Offset]);
        Inc(Offset,ReadSize);
    end;

    with OutBuf do
    begin
        if DataType<>dtByte then MBSetType(OutBuf,dtByte);

        //扩展缓冲区
        NeedSize:=Offset+ReadSize;
        if NeedSize>BufSize then MBReAlloc(OutBuf,NeedSize);

        LastOff:=Offset;
    end;

    //建立编码器（8位符号）
    if self.FEncode=nil then self.FEncode:=TCHEncode.Create;
    self.FEncode.InitEncode(@OutBuf,$100);

    //保存数据长度
    MBWrite(OutBuf,ReadSize,SizeOf(Integer));

    //统计概率
    for i:=0 to ReadSize-1 do Inc(self.FEncode.Freq[Dest[i]]);

    //分配编码并保存码表
    self.FEncode.AllocCode;
    self.FEncode.SaveBitLenH;

    //编码
    for i:=0 to ReadSize-1 do self.FEncode.Encode(Dest[i]);
    self.FEncode.FinishEncode;

    //计算写入长度
    MBSetType(OutBuf,dtByte);
    Result:=OutBuf.Offset-LastOff;

    //完成
end;

//从缓冲区InBuf中读取数据进行解压缩并保存到缓冲区OutBuf中，
//返回写入到缓冲区OutBuf中数据的大小（字节），
//缓冲区OutBuf不足时扩展缓冲区，
//缓冲区InBuf中的压缩数据必需是使用TCHCoding.Encode保存的，
//根据InBuf.Offset确定读取位置，读取后修改InBuf.Offset，
//根据OutBuf.Offset确定写入位置，写入后修改OutBuf.Offset，
//InBuf：输入缓冲区；
//OutBuf：输出缓冲区。
function TCHCoding.Decode(var InBuf,OutBuf : TMBBuffer): Integer;
var
    i,NeedSize : Integer;
    Sour : PMBByteAry;
begin
    //提取原数据长度
    MBRead(InBuf,Result,SizeOf(Integer));
    if Result<=0 then
    begin
        Result:=0; exit;
    end;

    with OutBuf do
    begin
        if DataType<>dtByte then MBSetType(OutBuf,dtByte);

        //扩展缓冲区
        NeedSize:=Offset+Result;
        if NeedSize>BufSize then MBReAlloc(OutBuf,NeedSize);

        //计算并更新位置
        Sour:=@(Mem8[Offset]);
        Offset:=NeedSize;
    end;

    //建立解码器（8位符号）
    if self.FDecode=nil then self.FDecode:=TCHDecode.Create;
    self.FDecode.InitDecode(@InBuf,$100,8); //使用8位快表

    //导入码表
    self.FDecode.LoadBitLenH; //H方案

    //解码
    for i:=0 to Result-1 do Sour[i]:=self.FDecode.Decode;
    self.FDecode.FinishDecode;

    //完成
end;

//从缓冲区InBuf中读取Size长度的数据进行压缩并保存到缓冲区OutBuf中，
//返回写入到缓冲区OutBuf中数据的大小（字节），
//缓冲区OutBuf不足时扩展缓冲区，
//根据InBuf.Offset确定读取位置，读取后修改InBuf.Offset，
//根据OutBuf.Offset确定写入位置，写入后修改OutBuf.Offset，
//与TCHCoding.Encode不同的是本函数每次压缩两个字节（16位）的符号，
//InBuf：输入缓冲区；
//OutBuf：输出缓冲区；
//Size：数据大小（字节）。
function TCHCoding.Encode16(var InBuf,OutBuf : TMBBuffer; Size : Integer): Integer;
var
    i,ReadSize,NeedSize,LastOff : Integer;
    Dest : PMBWordAry;
begin
    with InBuf do
    begin
        if DataType<>dtByte then MBSetType(InBuf,dtByte);

        //判断可读长度
        ReadSize:=BufSize-Offset;
        if ReadSize<=0 then
        begin
            Result:=0; exit;
        end;
        if ReadSize>Size then ReadSize:=Size;

        //计算并更新位置
        Dest:=@(Mem8[Offset]);
        Inc(Offset,ReadSize);
    end;

    with OutBuf do
    begin
        if DataType<>dtByte then MBSetType(OutBuf,dtByte);

        //扩展缓冲区
        NeedSize:=Offset+ReadSize;
        if NeedSize>BufSize then MBReAlloc(OutBuf,NeedSize);

        LastOff:=Offset;
    end;

    //建立编码器（16位符号）
    if self.FEncode=nil then self.FEncode:=TCHEncode.Create;
    self.FEncode.InitEncode(@OutBuf,$10000);

    //保存数据长度
    MBWrite(OutBuf,ReadSize,SizeOf(Integer));
    ReadSize:=(ReadSize+1) shr 1;

    //统计概率
    for i:=0 to ReadSize-1 do Inc(self.FEncode.Freq[Dest[i]]);

    //分配编码并保存码表
    self.FEncode.AllocCode;
    self.FEncode.SaveBitLenH;

    //编码
    for i:=0 to ReadSize-1 do self.FEncode.Encode(Dest[i]);
    self.FEncode.FinishEncode;

    //计算写入长度
    MBSetType(OutBuf,dtByte);
    Result:=OutBuf.Offset-LastOff;

    //完成
end;

//从缓冲区InBuf中读取数据进行解压缩并保存到缓冲区OutBuf中，
//返回写入到缓冲区OutBuf中数据的大小（字节），
//缓冲区OutBuf不足时扩展缓冲区，
//缓冲区InBuf中的压缩数据必需是使用TCHCoding.Encode16保存的，
//根据InBuf.Offset确定读取位置，读取后修改InBuf.Offset，
//根据OutBuf.Offset确定写入位置，写入后修改OutBuf.Offset，
//与TCHCoding.Decode不同的是本函数每次解压缩两个字节（16位）的符号，
//InBuf：输入缓冲区；
//OutBuf：输出缓冲区。
function TCHCoding.Decode16(var InBuf,OutBuf : TMBBuffer): Integer;
var
    i,NeedSize : Integer;
    Sour : PMBWordAry;
begin
    //提取原数据长度
    MBRead(InBuf,Result,SizeOf(Integer));
    if Result<=0 then
    begin
        Result:=0; exit;
    end;

    with OutBuf do
    begin
        if DataType<>dtByte then MBSetType(OutBuf,dtByte);

        //扩展缓冲区
        NeedSize:=Offset+Result;
        if NeedSize>BufSize then MBReAlloc(OutBuf,NeedSize);

        //计算并更新位置
        Sour:=@(Mem8[Offset]);
        Offset:=NeedSize;
    end;

    //建立解码器（16位符号）
    if self.FDecode=nil then self.FDecode:=TCHDecode.Create;
    self.FDecode.InitDecode(@InBuf,$10000,8); //使用8位快表

    //导入码表
    self.FDecode.LoadBitLenH; //H方案

    //解码
    for i:=0 to ((Result+1) shr 1)-1 do Sour[i]:=self.FDecode.Decode;
    self.FDecode.FinishDecode;

    //完成
end;

//单元结束
end.

