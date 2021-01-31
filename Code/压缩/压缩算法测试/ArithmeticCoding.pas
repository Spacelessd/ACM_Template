//
//算术编码算法的实现
//作者：叶叶　2010年8月30日
//
//本文件仅供算法研究使用。本文件中实现的算法如具有版权的，由版权所有人拥有。
//
//本文件是论文《区间编码算法的分析与实现》的配套程序。
//本文件最早在http://programbbs.com/bbs/上发布。
//

unit ArithmeticCoding;

interface

uses
    MemoryBuffer;

const
    //符号容量，必需是2的次方数
    AC_SYMBOL_NO = 256;

    //结束符
    AC_EOM = AC_SYMBOL_NO;

    //编码位长
    AC_CODE_BITS = 31;

    //区间的最大范围
    AC_TOP = Cardinal(1 shl AC_CODE_BITS);

    //最大范围的二分之一
    AC_HALF = AC_TOP shr 1;

    //最大范围的四分之一
    AC_QUAR = AC_HALF shr 1;

    //最大频度，不能超过$FFFF，因为频度表用Word保存数据
    AC_MAX_FREQ = $FFFF;

type
    //符号类型，必需与AC_SYMBOL_NO相对应
    TACSymbol = Integer;

    //算术编码核心编解码器，不包含建模部份
    PACCoder = ^TACCoder;
    TACCoder = class
    private
        FLow : Cardinal; //当前区间的下沿
        FRange : Cardinal; //当前区间范围
        FFollow : Integer; //延迟位长度

        FValue : Cardinal; //解码时输入的编码值

        FBuf : PMBBuffer; //输入或输出缓冲区
    public
        constructor Create;
        destructor Destroy; override;

        //编码操作
        procedure InitEncode(OutBuf : PMBBuffer);
        procedure Encode(CumFreq,Freq,Total : Cardinal);
        procedure FinishEncode;

        //解码操作
        procedure InitDecode(InBuf : PMBBuffer);
        function DecodeTarget(Total : Cardinal): Cardinal;
        procedure Decode(CumFreq,Freq : Cardinal);
        procedure FinishDecode;
    end;

    //统计模型（0阶）
    TACModel = class
    private
        FTotal : Cardinal; //频度总计
        FTree : array [0..AC_SYMBOL_NO] of Word; //BIT树，计算累积频度

        FCoder : PACCoder; //编解码器

        procedure GetFreq(Symbol : TACSymbol; var CumFreq,Freq : Cardinal);
        procedure IncFreq(Symbol : TACSymbol);
        function FindEstFreq(EstFreq : Cardinal): TACSymbol;
    public
        constructor Create;
        destructor Destroy; override;

        //模型操作
        procedure InitModel(Coder : PACCoder);
        procedure Encode(Symbol : TACSymbol);
        function Decode: TACSymbol;
        procedure FinishModel;
    end;

    //算术编码编解码器，对TACCoder和TACModel的简单封装
    TACCoding = class
    private
        FCoder : TACCoder; //编解码器
        FModel : TACModel; //模型
    public
        constructor Create;
        destructor Destroy; override;

        function Encode(var InBuf,OutBuf : TMBBuffer; Size : Integer): Integer;
        function Decode(var InBuf,OutBuf : TMBBuffer): Integer;
    end;

implementation

{TACCoder} //算术编码核心编解码器，不包含建模部份

//新建算术编码核心编解码器。
constructor TACCoder.Create;
begin
end;

//销毁算术编码核心编解码器。
destructor TACCoder.Destroy;
begin
end;

//初始化编码器，并将编码器与指定的输出缓冲区绑定，
//OutBuf：缓冲区。
procedure TACCoder.InitEncode(OutBuf : PMBBuffer);
begin
    self.FBuf:=OutBuf;
    self.FLow:=0;
    self.FRange:=AC_TOP;
    self.FFollow:=0;
end;

//利用区间编码算法对一个符号进行编码并写入到Buf中，
//根据Buf.Offset确定保存位置，保存后修改Buf.Offset和Buf.DataSize，
//CumFreq：累积频度；
//Freq：频度；
//Total：频度总计。
procedure TACCoder.Encode(CumFreq,Freq,Total : Cardinal);
var
    High,Check,Bit : Cardinal;
    i : Integer;
begin
    //区间计算
    self.FRange:=self.FRange div Total;
    Inc(self.FLow,CumFreq*self.FRange);
    High:=self.FLow+(Freq*self.FRange)-1;

    //调整区间
    while True do
    begin
        Check:=High xor self.FLow;

        if (Check and AC_HALF)=0 then
        begin
            //区间位于上半区或下半区
            Bit:=(High shr (AC_CODE_BITS-1)) and 1;
            MBSetBit(self.FBuf^,Bit);

            if self.FFollow<>0 then
            begin
                if Bit=0 then Bit:=1
                else          Bit:=0;

                for i:=1 to self.FFollow do MBSetBit(self.FBuf^,Bit);
                self.FFollow:=0;
            end;
        end
        else if ((Check and AC_QUAR)<>0) and
                ((High and AC_QUAR)=0) then
        begin
            //区间位于中间区
            Inc(self.FFollow);
            Dec(High,AC_QUAR);
            Dec(self.FLow,AC_QUAR);
        end
        else break;

        //扩展区间
        High:=((High shl 1)+1) and (AC_TOP-1);
        self.FLow:=(self.FLow shl 1) and (AC_TOP-1);
    end;

    self.FRange:=High-self.FLow+1;

    //完成
end;

//结束编码，进行收尾操作，
//本函数不会在数据末尾添加AC_EOM结束符。
procedure TACCoder.FinishEncode;
var
    i : Integer;
begin
    //输出剩余编码
    Inc(self.FFollow);

    if self.FLow<AC_QUAR then
    begin
        MBSetBit(self.FBuf^,0);
        for i:=1 to self.FFollow do MBSetBit(self.FBuf^,1);
    end
    else
    begin
        MBSetBit(self.FBuf^,1);
        for i:=1 to self.FFollow do MBSetBit(self.FBuf^,0);
    end;

    self.FFollow:=0;

    self.FBuf:=nil;

    //完成
end;

//初始化解码器，并将解码器与指定的输入缓冲区绑定，
//InBuf：缓冲区。
procedure TACCoder.InitDecode(InBuf : PMBBuffer);
begin
    //初始化
    self.FBuf:=InBuf;
    self.FLow:=0;
    self.FRange:=AC_TOP;

    //读入编码
    self.FValue:=MBReadBit(self.FBuf^,AC_CODE_BITS);

    //完成
end;

//根据当前的区间，按照指定的Total计算出估计累积频度，并返回，
//Total：总计频度。
function TACCoder.DecodeTarget(Total : Cardinal): Cardinal;
begin
    self.FRange:=self.FRange div Total;
    Result:=(self.FValue-self.FLow) div self.FRange;
end;

//按照指定的频度数据调整当前区间，根据需要从缓冲区中读入数据，
//在调用本函数之前必需先调用DecodeTarget函数，
//根据FBuf.Offset确定读取位置，读取后修改FBuf.Offset，
//CumFreq：累积频度；
//Freq：频度。
procedure TACCoder.Decode(CumFreq,Freq : Cardinal);
var
    High,Check : Cardinal;
begin
    //区间计算
    Inc(self.FLow,CumFreq*self.FRange);
    High:=self.FLow+(Freq*self.FRange)-1;

    //调整区间
    while True do
    begin
        Check:=High xor self.FLow;

        if (Check and AC_HALF)=0 then
        begin
            //区间位于上半区或下半区
        end
        else if ((Check and AC_QUAR)<>0) and
                ((High and AC_QUAR)=0) then
        begin
            //区间位于中间区
            Dec(High,AC_QUAR);
            Dec(self.FLow,AC_QUAR);
            Dec(self.FValue,AC_QUAR);
        end
        else break;

        //扩展区间
        High:=((High shl 1)+1) and (AC_TOP-1);
        self.FLow:=(self.FLow shl 1) and (AC_TOP-1);
        self.FValue:=((self.FValue shl 1) or MBGetBit(self.FBuf^)) and (AC_TOP-1);
    end;

    self.FRange:=High-self.FLow+1;

    //完成
end;

//结束编码，进行收尾操作。
procedure TACCoder.FinishDecode;
begin
    self.FBuf:=nil;
end;

{TACModel} //统计模型（0阶）

//新建统计模型。
constructor TACModel.Create;
begin
    self.FCoder:=nil;
end;

//销毁统计模型。
destructor TACModel.Destroy;
begin
end;

//获取指定符号的累积频度和频度，
//Symbol：符号值；
//CumFreq：符号的累积频度；
//Freq：符号的频度。
procedure TACModel.GetFreq(Symbol : TACSymbol; var CumFreq,Freq : Cardinal);
var
    Id,Parent : Integer;
    Sum : Cardinal;
begin
    //排除符号0
    if Symbol=0 then
    begin
        CumFreq:=0;
        Freq:=self.FTree[0];
        exit;
    end;

    //统计累积频度和频度
    Id:=Symbol;
    Parent:=Id-(Id and -Id);
    Dec(Id);
    Sum:=0;

    while Id<>Parent do
    begin
        Inc(Sum,self.FTree[Id]);
        Dec(Id,Id and -Id);
    end;
    Freq:=self.FTree[Symbol]-Sum;

    while Id>0 do
    begin
        Inc(Sum,self.FTree[Id]);
        Dec(Id,Id and -Id);
    end;
    CumFreq:=self.FTree[0]+Sum;

    //完成
end;

//增加指定符号的频度，当总频度大于限制值时则削减频度，
//Symbol：符号值。
procedure TACModel.IncFreq(Symbol : TACSymbol);
var
    i,Id,Parent : Integer;
    Freq,NewFreq : Cardinal;
begin
    if self.FTotal=AC_MAX_FREQ then
    begin
        //削减频度
        self.FTree[0]:=(self.FTree[0]+1) shr 1;
        self.FTotal:=self.FTree[0];
        for i:=1 to AC_SYMBOL_NO do
        begin
            //统计频度
            Id:=i;
            Freq:=self.FTree[Id];
            Parent:=Id-(Id and -Id);
            Dec(Id);
            while Id<>Parent do
            begin
                Dec(Freq,self.FTree[Id]);
                Dec(Id,Id and -Id);
            end;

            //计算差值
            NewFreq:=(Freq+1) shr 1;
            Inc(self.FTotal,NewFreq);
            Dec(Freq,NewFreq);
            if Freq=0 then continue;

            //更新频度
            Id:=i;
            repeat
                Dec(self.FTree[Id],Freq);
                Inc(Id,Id and -Id);
            until Id>AC_SYMBOL_NO;
        end;
    end;

    //更新频度
    if Symbol=0 then Inc(self.FTree[0])
    else
    begin
        repeat
            Inc(self.FTree[Symbol]);
            Inc(Symbol,Symbol and -Symbol);
        until Symbol>AC_SYMBOL_NO;
    end;
    Inc(self.FTotal);

    //完成
end;

//查找指定的估算频度，返回对应的符号，
//EstFreq：估算频度值。
function TACModel.FindEstFreq(EstFreq : Cardinal): TACSymbol;
var
    Mask,Id : Integer;
begin
    //排除符号0和结束符
    if EstFreq<self.FTree[0] then
    begin
        Result:=0; exit;
    end;
    Dec(EstFreq,self.FTree[0]);
    if EstFreq>=self.FTree[AC_SYMBOL_NO] then
    begin
        Result:=AC_EOM; exit;
    end;

    //查找
    Result:=0;
    Mask:=AC_SYMBOL_NO shr 1;
    while Mask<>0 do
    begin
        Id:=Result+Mask;
        if EstFreq>=self.FTree[Id] then
        begin
            Result:=Id;
            Dec(EstFreq,self.FTree[Id]);
        end;
        Mask:=Mask shr 1;
    end;
    Inc(Result);

    //完成
end;

//初始化模型，并将模型与指定的核心编解码器绑定，
//Coder：核心编解码器。
procedure TACModel.InitModel(Coder : PACCoder);
var
    i,Id : Integer;
begin
    self.FCoder:=Coder;

    //初始化频度，初始时每个符号的频度都为1
    self.FTree[0]:=1;

    for i:=1 to AC_SYMBOL_NO do self.FTree[i]:=0;
    for i:=1 to AC_SYMBOL_NO do
    begin
        Id:=i;
        repeat
            Inc(self.FTree[Id]);
            Inc(Id,Id and -Id);
        until Id>AC_SYMBOL_NO;
    end;
    self.FTotal:=AC_SYMBOL_NO+1;

    //完成
end;

//利用区间编码算法对一个符号进行编码并写入到Buf中，
//根据Buf.Offset确定保存位置，保存后修改Buf.Offset和Buf.DataSize，
//Symbol：符号值。
procedure TACModel.Encode(Symbol : TACSymbol);
var
    CumFreq,Freq : Cardinal;
begin
    //统计频度
    self.GetFreq(Symbol,CumFreq,Freq);

    //编码
    self.FCoder.Encode(CumFreq,Freq,self.FTotal);

    //更新频度
    self.IncFreq(Symbol);

    //完成
end;

//利用区间编码算法对从Buf中解码出一个符号，并返回，
//根据Buf.Offset确定读取位置，读取后修改Buf.Offset，
function TACModel.Decode: TACSymbol;
var
    CumFreq,Freq : Cardinal;
begin
    //查找估算频度
    Result:=self.FindEstFreq(
        self.FCoder.DecodeTarget(self.FTotal));

    //统计频度
    self.GetFreq(Result,CumFreq,Freq);

    //调整区间
    self.FCoder.Decode(CumFreq,Freq);

    //更新频度
    self.IncFreq(Result);

    //完成
end;

//结束操作，进行收尾操作。
procedure TACModel.FinishModel;
begin
    self.FCoder:=nil;
end;

{TACCoding} //算术编码编解码器，对TACCoder和TACModel的简单封装

//新建算术编码编解码器。
constructor TACCoding.Create;
begin
    self.FCoder:=TACCoder.Create;
    self.FModel:=TACModel.Create;
end;

//销毁算术编码编解码器。
destructor TACCoding.Destroy;
begin
    self.FCoder.Free;
    self.FModel.Free;
end;

//从缓冲区InBuf中读取Size长度的数据进行压缩并保存到缓冲区OutBuf中，
//返回写入到缓冲区OutBuf中数据的大小（字节），
//缓冲区OutBuf不足时扩展缓冲区，
//根据InBuf.Offset确定读取位置，读取后修改InBuf.Offset，
//根据OutBuf.Offset确定写入位置，写入后修改OutBuf.Offset，
//InBuf：输入缓冲区；
//OutBuf：输出缓冲区；
//Size：数据大小（字节）。
function TACCoding.Encode(var InBuf,OutBuf : TMBBuffer; Size : Integer): Integer;
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

    //初始化
    self.FCoder.InitEncode(@OutBuf);
    self.FModel.InitModel(@(self.FCoder));

    //保存数据长度
    MBWrite(OutBuf,ReadSize,SizeOf(Integer));

    //编码
    for i:=0 to ReadSize-1 do self.FModel.Encode(Dest[i]);

    //结束编码
    self.FModel.FinishModel;
    self.FCoder.FinishEncode;

    //计算写入长度
    MBSetType(OutBuf,dtByte);
    Result:=OutBuf.Offset-LastOff;

    //完成
end;

//从缓冲区InBuf中读取数据进行解压缩并保存到缓冲区OutBuf中，
//返回写入到缓冲区OutBuf中数据的大小（字节），
//缓冲区OutBuf不足时扩展缓冲区，
//缓冲区InBuf中的压缩数据必需是使用TACCoding.Encode保存的，
//根据InBuf.Offset确定读取位置，读取后修改InBuf.Offset，
//根据OutBuf.Offset确定写入位置，写入后修改OutBuf.Offset，
//InBuf：输入缓冲区；
//OutBuf：输出缓冲区。
function TACCoding.Decode(var InBuf,OutBuf : TMBBuffer): Integer;
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

    //初始化
    self.FCoder.InitDecode(@InBuf);
    self.FModel.InitModel(@(self.FCoder));

    //解码
    for i:=0 to Result-1 do Sour[i]:=self.FModel.Decode;

    //结束解码
    self.FModel.FinishModel;
    self.FCoder.FinishDecode;

    //完成
end;

//单元结束
end.

