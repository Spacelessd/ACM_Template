//
//内存缓冲区管理
//作者：叶叶　2010年6月22日
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

unit MemoryBuffer;

interface

uses
    Classes, SysUtils;

type
    //Byte数组（8位）
    PMBByteAry = ^TMBByteAry;
    TMBByteAry = array [0..0] of Byte;

    //Word数组（16位）
    PMBWordAry = ^TMBWordAry;
    TMBWordAry = array [0..0] of Word;

    //Cardinal数组（32位）
    PMBCardinalAry = ^TMBCardinalAry;
    TMBCardinalAry = array [0..0] of Cardinal;

    //数据的单位类型
    TMBDataType = (
        dtByte, //以字节为单位
        dtBit   //以位为单位
    );

    //缓冲区
    PMBBuffer = ^TMBBuffer;
    TMBBuffer = record
        BufSize : Integer; //缓冲区大小（字节）
        IncSize : Integer; //缓冲区每次扩展大小（字节），必需是大于等于4的2的次方数
        DataType : TMBDataType; //数据的单位类型
        Offset : Integer; //当前访问位置（位或字节），单位根据DataType的设置而不同
        case Byte of
            1 : (Mem   : Pointer); //内存指针
            2 : (Mem8  : PMBByteAry); //Byte数组指针
            3 : (Mem32 : PMBCardinalAry); //Cardinal数组指针
    end;

    //缓冲区管理
    procedure MBInit   (var Buf : TMBBuffer; ABufSize : Integer = 0; AIncSize : Integer = 1024; ADataType : TMBDataType = dtByte);
    procedure MBReAlloc(var Buf : TMBBuffer; NewSize : Integer);
    procedure MBFree   (var Buf : TMBBuffer);
    procedure MBSetType(var Buf : TMBBuffer; NewType : TMBDataType);

    //导入导出
    function MBLoadFromFile  (var Buf : TMBBuffer; const FileName : string): Integer;
    function MBSaveToFile    (const Buf : TMBBuffer; Size : Integer; const FileName : string): Integer;
    function MBLoadFromStream(var Buf : TMBBuffer; Stream : TStream): Integer;
    function MBSaveToStream  (const Buf : TMBBuffer; Size : Integer; Stream : TStream): Integer;

    //数据读写
    procedure MBWrite   (var Buf : TMBBuffer; const Data; Size : Integer);
    procedure MBRead    (var Buf : TMBBuffer; var Data; Size : Integer);
    procedure MBWriteBit(var Buf : TMBBuffer; Data : Cardinal; Size : Integer);
    function  MBReadBit (var Buf : TMBBuffer; Size : Integer): Cardinal;
    procedure MBSetBit  (var Buf : TMBBuffer; Bit : Cardinal);
    function  MBGetBit  (var Buf : TMBBuffer): Cardinal;

    //0阶指数哥伦布编码
    procedure MBEncodeEG(var Buf : TMBBuffer;  Num : Cardinal);
    function  MBDecodeEG(var Buf : TMBBuffer): Cardinal;

implementation

{缓冲区管理}

//初始化缓冲区Buf，并根据需要分配内存，设置初始值，
//Buf：缓冲区；
//ABufSize：缓冲区初始时的大小（字节）；
//AIncSize：缓冲区每次扩展大小（字节）；
//ADataType：数据的单位类型。
procedure MBInit(var Buf : TMBBuffer; ABufSize,AIncSize : Integer; ADataType : TMBDataType);
begin
    with Buf do
    begin
        //确认每次扩展大小
        IncSize:=4;
        while IncSize<AIncSize do IncSize:=IncSize shl 1;

        //分配内存
        BufSize:=(ABufSize+(IncSize-1)) and (not (IncSize-1));
        if BufSize=0 then Mem:=nil
        else              GetMem(Mem,BufSize);

        //设置
        DataType:=ADataType;
        Offset:=0;

        //完成
    end;
end;

//重新分配缓冲区Buf的内存，
//Buf：缓冲区；
//NewSize：新的缓冲区大小（字节）。
procedure MBReAlloc(var Buf : TMBBuffer; NewSize : Integer);
begin
    with Buf do
    begin
        NewSize:=(NewSize+(IncSize-1)) and (not (IncSize-1));
        if NewSize=BufSize then exit;
        ReallocMem(Mem,NewSize);
        BufSize:=NewSize;
    end;
end;

//释放缓冲区Buf所占用的内存，
//Buf：缓冲区。
procedure MBFree(var Buf : TMBBuffer);
begin
    with Buf do
    begin
        if Mem<>nil then FreeMem(Mem);
        Mem:=nil;
        BufSize:=0;
    end;
end;

//设置缓冲区Buf的访问单位，对Buf.Offset进行重新换算，
//Buf：缓冲区；
//NewType：新的单位类型。
procedure MBSetType(var Buf : TMBBuffer; NewType : TMBDataType);
begin
    with Buf do
    begin
        if NewType=DataType then exit;

        //换算
        case NewType of
            dtByte : Offset:=((Offset+31) and (not 31)) shr 3;
            dtBit  : Offset:=((Offset+ 3) and (not  3)) shl 3;
        end;

        //更新
        DataType:=NewType;
    end;
end;

{导入导出}

//从指定文件中导入数据到缓冲区Buf中，缓冲区不足时扩展缓冲区，
//返回导入到缓冲区中数据的大小（字节），
//Buf：缓冲区；
//FileName：文件名。
function MBLoadFromFile(var Buf : TMBBuffer; const FileName : string): Integer;
var
    Stream : TStream;
begin
    Stream:=TFileStream.Create(FileName,fmOpenRead);
    try
        Result:=MBLoadFromStream(Buf,Stream);
    finally
        Stream.Free;
    end;
end;

//将缓冲区Buf中的指定长度的数据保存到指定文件中，
//返回写入到文件中数据的大小（字节），
//根据Size确定缓冲区中数据的大小，
//Buf：缓冲区；
//Size：数据大小（字节）；
//FileName：文件名。
function MBSaveToFile(const Buf : TMBBuffer; Size : Integer; const FileName : string): Integer;
var
    Stream : TStream;
begin
    Stream:=TFileStream.Create(FileName,fmCreate);
    try
        Result:=MBSaveToStream(Buf,Size,Stream);
    finally
        Stream.Free;
    end;
end;

//从指定数据流中导入数据到缓冲区Buf中，缓冲区不足时扩展缓冲区，
//返回导入到缓冲区中数据的大小（字节），
//Buf：缓冲区；
//Stream：数据流。
function MBLoadFromStream(var Buf : TMBBuffer; Stream : TStream): Integer;
begin
    with Buf do
    begin
        Result:=Stream.Size-Stream.Position;
        if Result>BufSize then MBReAlloc(Buf,Result);
        Result:=Stream.Read(Mem^,Result);
    end;
end;

//将缓冲区Buf中的指定长度的数据保存到指定数据流中，
//返回写入到数据流中数据的大小（字节），
//根据Size确定缓冲区中数据的大小，
//Buf：缓冲区；
//Size：数据大小（字节）；
//Stream：数据流。
function MBSaveToStream(const Buf : TMBBuffer; Size : Integer; Stream : TStream): Integer;
begin
    with Buf do
    begin
        if Size>BufSize then Size:=BufSize;
        Result:=Stream.Write(Mem^,Size);
    end;
end;

{数据读写}

//将Data中的数据写入到缓冲区Buf中，缓冲区不足时扩展缓冲区，
//根据Buf.Offset确定写入位置，写入后修改Buf.Offset，
//Buf：缓冲区；
//Data：数据
//Size：数据长度（字节）。
procedure MBWrite(var Buf : TMBBuffer; const Data; Size : Integer);
var
    NeedSize : Integer;
begin
    if Size<=0 then exit;

    with Buf do
    begin
        if DataType<>dtByte then MBSetType(Buf,dtByte);

        //扩展缓冲区
        NeedSize:=Offset+Size;
        if NeedSize>BufSize then MBReAlloc(Buf,NeedSize);

        //拷贝数据
        Move(Data,Mem8[Offset],Size);

        //更新位置
        Offset:=NeedSize;

        //完成
    end;
end;

//从缓冲区Buf中读取指定长度的数据到Data中，
//根据Buf.Offset确定读取位置，读取后修改Buf.Offset，
//Buf：缓冲区；
//Data：数据
//Size：数据长度（字节）。
procedure MBRead(var Buf : TMBBuffer; var Data; Size : Integer);
var
    ReadSize : Integer;
begin
    if Size<=0 then exit;

    with Buf do
    begin
        if DataType<>dtByte then MBSetType(Buf,dtByte);

        //判断可读长度
        ReadSize:=BufSize-Offset;
        if ReadSize<=0 then exit;
        if ReadSize>Size then ReadSize:=Size;

        //拷贝数据
        Move(Mem8[Offset],Data,ReadSize);

        //更新位置
        Inc(Offset,ReadSize);

        //完成
    end;
end;

//将Data低Size个位写入缓冲区Buf中，缓冲区不足时扩展缓冲区，
//根据Buf.Offset确定写入位置，写入后修改Buf.Offset，
//Buf：缓冲区；
//Data：数据
//Size：数据长度（位）（1至32范围内）。
procedure MBWriteBit(var Buf : TMBBuffer; Data : Cardinal; Size : Integer);
var
    Dest : PCardinal;
    NeedSize,Hi,Lo : Integer;
begin
    if Size<=0 then exit;
    if Size>32 then Size:=32;

    with Buf do
    begin
        if DataType<>dtBit then MBSetType(Buf,dtBit);

        //扩展缓冲区
        NeedSize:=((Offset+Size+31) and (not 31)) shr 3;
        if NeedSize>BufSize then MBReAlloc(Buf,NeedSize);

        //计算并更新位置
        Dest:=@(Mem32[Offset shr 5]);
        Hi:=Offset and 31;
        Lo:=32-Hi;
        Inc(Offset,Size);
    end;

    //拷贝位数据（以Cardinal为单位，从高位向低位写入。）
    Data:=Data shl (32-Size);
    Dest^:=(Dest^ and (not ($FFFFFFFF shr Hi))) or (Data shr Hi);
    if Size>Lo then
    begin
        Inc(Dest); Dest^:=Data shl Lo;
    end;

    //完成
end;

//从缓冲区Buf中读取Size个位并返回，
//假设缓冲区中所有的数据都为二进制1，
//数据足够时读取4位时，返回低位为0..01111，
//数据不足时读取4位时，返回低位为0..01100，
//根据Buf.Offset确定读取位置，读取后修改Buf.Offset，
//Buf：缓冲区；
//Size：数据长度（位）（1至32范围内）。
function MBReadBit(var Buf : TMBBuffer; Size : Integer): Cardinal;
var
    Sour : PCardinal;
    ReadSize,Hi,Lo : Integer;
begin
    Result:=0;
    if Size<=0 then exit;
    if Size>32 then Size:=32;

    with Buf do
    begin
        if DataType<>dtBit then MBSetType(Buf,dtBit);

        //判断可读位长
        ReadSize:=(BufSize shl 3)-Offset;
        if ReadSize<=0 then exit;
        if ReadSize>Size then ReadSize:=Size;

        //计算并更新位置
        Sour:=@(Mem32[Offset shr 5]);
        Hi:=Offset and 31;
        Lo:=32-Hi;
        Inc(Offset,ReadSize);
    end;

    //拷贝位数据（以Cardinal为单位，从高位向低位读取。）
    Result:=Sour^ shl Hi;
    if ReadSize>Lo then
    begin
        Inc(Sour); Result:=Result or (Sour^ shr Lo);
    end;
    Result:=Result shr (32-ReadSize);

    //数据不足，左移补齐
    if ReadSize<Size then Result:=Result shl (Size-ReadSize);

    //完成
end;

//向缓冲区Buf中写入一个位，Bit为0时写入0，Bit不为0时写入1，
//缓冲区不足时扩展缓冲区，
//根据Buf.Offset确定写入位置，写入后修改Buf.Offset，
//Buf：缓冲区；
//Bit：位数据。
procedure MBSetBit(var Buf : TMBBuffer; Bit : Cardinal);
var
    Dest : PCardinal;
    NeedSize : Integer;
    Mask : Cardinal;
begin
    with Buf do
    begin
        if DataType<>dtBit then MBSetType(Buf,dtBit);

        //扩展缓冲区
        NeedSize:=((Offset+1+31) and (not 31)) shr 3;
        if NeedSize>BufSize then MBReAlloc(Buf,NeedSize);

        //计算并更新位置
        Dest:=@(Mem32[Offset shr 5]);
        Mask:=$80000000 shr (Offset and 31);
        Inc(Offset);
    end;

    //设置位（以Cardinal为单位，从高位向低位写入。）
    if Bit=0 then Dest^:=Dest^ and (not Mask)
    else          Dest^:=Dest^ or  Mask;

    //完成
end;

//从缓冲区Buf中读取一个位，该位为0返回0，该位为1返回1，
//根据Buf.Offset确定读取位置，读取后修改Buf.Offset，
//Buf：缓冲区。
function MBGetBit(var Buf : TMBBuffer): Cardinal;
var
    ReadSize : Integer;
begin
    with Buf do
    begin
        if DataType<>dtBit then MBSetType(Buf,dtBit);

        //判断可读位长
        ReadSize:=(BufSize shl 3)-Offset;
        if ReadSize<1 then
        begin
            Result:=0; exit;
        end;

        //读取位（以Cardinal为单位，从高位向低位读取。）
        Result:=(Mem32[Offset shr 5] shr (32-(Offset and 31)-1)) and 1;

        //更新位置
        Inc(Offset);

        //完成
    end;
end;

{0阶指数哥伦布编码}

//使用指数哥伦布算法对一个数值数据进行压缩并写入到缓冲区Buf中，
//缓冲区不足时扩展缓冲区，
//根据Buf.Offset确定写入位置，写入后修改Buf.Offset，
//Buf：缓冲区；
//Num：数值数据。
procedure MBEncodeEG(var Buf : TMBBuffer;  Num : Cardinal);
var
    Dest : PCardinal;
    N : Cardinal;
    BitLen,NeedSize,Len,Hi,Lo : Integer;
begin
    if Num=0 then
    begin
        MBSetBit(Buf,1); exit;
    end;

    Inc(Num);

    //计算前缀位长
    BitLen:=1;
    N:=$FFFFFFFC;
    while (N and Num)<>0 do
    begin
        Inc(BitLen); N:=N shl 1;
    end;

    with Buf do
    begin
        if DataType<>dtBit then MBSetType(Buf,dtBit);

        //扩展缓冲区
        Len:=(BitLen shl 1)+1; //总位长
        NeedSize:=((Offset+Len+31) and (not 31)) shr 3;
        if NeedSize>BufSize then MBReAlloc(Buf,NeedSize);

        //计算并更新位置
        Dest:=@(Mem32[Offset shr 5]);
        Hi:=Offset and 31;
        Lo:=32-Hi;
        Inc(Offset,Len);
    end;

    //写入前缀BitLen个0（以Cardinal为单位，从高位向低位写入。）
    Dest^:=Dest^ and (not ($FFFFFFFF shr Hi));
    if BitLen>Lo then
    begin
        Inc(Dest); Dest^:=0;
    end;

    //写入后缀数据（以Cardinal为单位，从高位向低位写入。）
    Hi:=(Hi+BitLen) and 31;
    Lo:=32-Hi;
    if Hi=0 then Inc(Dest);

    Inc(BitLen);
    Num:=Num shl (32-BitLen);
    Dest^:=(Dest^ and (not ($FFFFFFFF shr Hi))) or (Num shr Hi);
    if BitLen>Lo then
    begin
        Inc(Dest); Dest^:=Num shl Lo;
    end;

    //完成
end;

//使用指数哥伦布算法从缓冲区中解压缩出一个数值数据，并返回，
//如果缓冲区中的数据不足以完成一次解码，则返回$FFFFFFFF，
//根据Buf.Offset确定读取位置，读取后修改Buf.Offset，
//Buf：缓冲区。
function MBDecodeEG(var Buf : TMBBuffer): Cardinal;
var
    Sour : PCardinal;
    N : Cardinal;
    ReadSize,Len,BitLen,Hi,Lo : Integer;
begin
    with Buf do
    begin
        if DataType<>dtBit then MBSetType(Buf,dtBit);

        //计算可读位长和位置
        ReadSize:=(BufSize shl 3)-Offset;
        if ReadSize<=0 then
        begin
            Result:=$FFFFFFFF; exit;
        end;
        Sour:=@(Mem32[Offset shr 5]);
        Hi:=Offset and 31;
    end;

    //计算前缀位长（以Cardinal为单位，从高位向低位读取。）
    BitLen:=0;
    N:=$80000000 shr Hi;
    while (BitLen<ReadSize) and ((Sour^ and N)=0) do
    begin
        Inc(BitLen);
        N:=N shr 1;
        if N=0 then
        begin
            Inc(Sour); N:=$80000000;
        end;
    end;

    //计算并更新位置
    Len:=(BitLen shl 1)+1;
    if ReadSize<Len then
    begin
        Result:=$FFFFFFFF; exit;
    end;

    Inc(Buf.Offset,Len);

    if BitLen=0 then
    begin
        Result:=0; exit;
    end;

    //读取后缀数据（以Cardinal为单位，从高位向低位读取。）
    Hi:=(Hi+BitLen) and 31;
    Lo:=32-Hi;

    Inc(BitLen);
    Result:=Sour^ shl Hi;
    if BitLen>Lo then
    begin
        Inc(Sour); Result:=Result or (Sour^ shr Lo);
    end;
    Result:=(Result shr (32-BitLen))-1;

    //完成
end;

//单元结束。
end.

