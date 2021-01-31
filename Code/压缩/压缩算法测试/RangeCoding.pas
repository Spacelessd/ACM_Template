//
//区间编码算法的实现
//作者：叶叶　2010年8月30日
//
//本文件版权由叶叶拥有，保留所有权利。
//本文件中的代码是免费程序，无需任何授权或许可即可用于个人和商业目的。使用者一切后果自负。
//
//如果你转载了本文件中的代码，请注明代码出处和代码作者；
//如果你修改了本文件中的代码，请注明修改位置和修改作者；
//
//本文件是论文《区间编码算法的分析与实现》的配套程序。
//本文件最早在http://programbbs.com/bbs/上发布。
//

unit RangeCoding;

interface

uses
    MemoryBuffer;

const
    //符号容量，必需是2的次方数
    RC_SYMBOL_NO = 256;

    //结束符
    RC_EOM = RC_SYMBOL_NO;

    //编码位长
    RC_CODE_BITS = 31;

    //低位移去位长
    RC_SHIFT_BITS = RC_CODE_BITS-8; //一次输出8个位

    //区间范围的最大值（Rmax）
    RC_MAX_RANGE = Cardinal(1 shl RC_CODE_BITS);

    //区间范围的最小值（Rmin）
    RC_MIN_RANGE = 1 shl RC_SHIFT_BITS;

    //最大频度，不能超过$FFFF，因为频度表用Word保存数据
    RC_MAX_FREQ = $FFFF;

type
    //符号类型，必需与RC_SYMBOL_NO相对应
    TRCSymbol = Integer;

    //区间编码核心编解码器，不包含建模部份
    PRCCoder = ^TRCCoder;
    TRCCoder = class
    private
        //区间：c,(d,n),[L",H"]
        FLow : Cardinal; //当前区间的下沿（L"）
        FRange : Cardinal; //当前区间范围（R）
        FDigits : Cardinal; //编码时用来保存延迟数字（d）；解码时用来保存输入编码（V）
        FFollow : Integer; //延迟数字长度（n）

        FBuf : PMBBuffer; //输入或输出缓冲区

        procedure OutputCode(Code : Cardinal);
        function InputCode: Cardinal;
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
    TRCModel = class
    private
        FTotal : Cardinal; //频度总计
        FTree : array [0..RC_SYMBOL_NO] of Word; //BIT结构，计算累积频度

        FCoder : PRCCoder; //编解码器

        procedure GetFreq(Symbol : TRCSymbol; var CumFreq,Freq : Cardinal);
        procedure IncFreq(Symbol : TRCSymbol);
        function FindEstFreq(EstFreq : Cardinal): TRCSymbol;
    public
        constructor Create;
        destructor Destroy; override;

        //模型操作
        procedure InitModel(Coder : PRCCoder);
        procedure Encode(Symbol : TRCSymbol);
        function Decode: TRCSymbol;
        procedure FinishModel;
    end;

    //区间编码编解码器，对TRCCoder和TRCModel的简单封装
    TRCCoding = class
    private
        FCoder : TRCCoder; //编解码器
        FModel : TRCModel; //模型
    public
        constructor Create;
        destructor Destroy; override;

        //编解码操作
        function Encode(var InBuf,OutBuf : TMBBuffer; Size : Integer): Integer;
        function Decode(var InBuf,OutBuf : TMBBuffer): Integer;
    end;

implementation

{TRCCoder} //区间编码核心编解码器，不包含建模部份

//新建区间编码核心编解码器。
constructor TRCCoder.Create;
begin
end;

//销毁区间编码核心编解码器。
destructor TRCCoder.Destroy;
begin
end;

//向FBuf输出一个字节的编码（8位），
//根据FBuf.Offset确定保存位置，保存后修改FBuf.Offset和FBuf.DataSize，
//Code：编码数据，低8位有效。
procedure TRCCoder.OutputCode(Code : Cardinal);
begin
    with self.FBuf^ do
    begin
        if DataType<>dtByte then MBSetType(self.FBuf^,dtByte);
        if (Offset+1)>BufSize then MBReAlloc(self.FBuf^,Offset+1);

        Mem8[Offset]:=Code;
        Inc(Offset);
    end;
end;

//从FBuf输入一个字节的编码（8位），并返回，
//根据FBuf.Offset确定读取位置，读取后修改FBuf.Offset，
function TRCCoder.InputCode: Cardinal;
begin
    with self.FBuf^ do
    begin
        if DataType<>dtByte then MBSetType(self.FBuf^,dtByte);

        if Offset>=BufSize then Result:=0
        else                    Result:=Mem8[Offset];
        
        Inc(Offset);
    end;
end;

//初始化编码器，并将编码器与指定的输出缓冲区绑定，
//OutBuf：缓冲区。
procedure TRCCoder.InitEncode(OutBuf : PMBBuffer);
begin
    self.FBuf:=OutBuf;
    self.FLow:=RC_MAX_RANGE;
    self.FRange:=RC_MAX_RANGE;
    self.FDigits:=0;
    self.FFollow:=0;
end;

//利用区间编码算法按照一个符号的频度信息进行编码并写入到FBuf中，
//根据FBuf.Offset确定保存位置，保存后修改FBuf.Offset和FBuf.DataSize，
//CumFreq：累积频度；
//Freq：频度；
//Total：频度总计。
procedure TRCCoder.Encode(CumFreq,Freq,Total : Cardinal);
var
    High : Cardinal;
    i : Integer;
begin
    //区间计算
    self.FRange:=self.FRange div Total;
    Inc(self.FLow,CumFreq*self.FRange);
    self.FRange:=Freq*self.FRange;

    //调整区间
    while self.FRange<=RC_MIN_RANGE do
    begin
        High:=self.FLow+self.FRange-1;

        //判断是否有延迟数字
        if self.FFollow<>0 then
        begin
            if High<=RC_MAX_RANGE then
            begin
                //趋向下沿
                self.OutputCode(self.FDigits);
                for i:=1 to self.FFollow-1 do self.OutputCode($FF);
                self.FFollow:=0;

                Inc(self.FLow,RC_MAX_RANGE);
            end
            else if self.FLow>=RC_MAX_RANGE then
            begin
                //趋向上沿
                self.OutputCode(self.FDigits+1);
                for i:=1 to self.FFollow-1 do self.OutputCode($00);
                self.FFollow:=0;
            end
            else
            begin
                //趋向未定
                Inc(self.FFollow);

                //扩展区间
                self.FLow:=(self.FLow shl 8) and (RC_MAX_RANGE-1);
                self.FRange:=self.FRange shl 8;

                continue;
            end;
        end;

        //判断最高位数字
        if ((self.FLow xor High) and ($FF shl RC_SHIFT_BITS))=0 then
        begin
            //出现不变数字
            self.OutputCode(self.FLow shr RC_SHIFT_BITS);
        end
        else
        begin
            //出现延迟数字
            Dec(self.FLow,RC_MAX_RANGE);
            self.FDigits:=self.FLow shr RC_SHIFT_BITS;
            self.FFollow:=1;
        end;

        //扩展区间
        self.FLow:=((self.FLow shl 8) and (RC_MAX_RANGE-1)) or
                   (self.FLow and RC_MAX_RANGE);
        self.FRange:=self.FRange shl 8;
    end;

    //完成
end;

//结束编码，进行收尾操作，
//本函数不会在数据末尾添加RC_EOM结束符。
procedure TRCCoder.FinishEncode;
var
    n : Integer;
begin
    //输出剩余延迟数字
    if self.FFollow<>0 then
    begin
        if self.FLow<RC_MAX_RANGE then
        begin
            //趋向下沿
            self.OutputCode(self.FDigits);
            for n:=1 to self.FFollow-1 do self.OutputCode($FF);
        end
        else
        begin
            //趋向上沿
            self.OutputCode(self.FDigits+1);
            for n:=1 to self.FFollow-1 do self.OutputCode($00);
        end;
    end;

    //输出剩余编码
    self.FLow:=self.FLow shl 1;
    n:=RC_CODE_BITS+1;
    repeat
        Dec(n,8);
        self.OutputCode(self.FLow shr n);
    until n<=0;

    self.FBuf:=nil;

    //完成
end;

//初始化解码器，并将解码器与指定的输入缓冲区绑定，
//InBuf：缓冲区。
procedure TRCCoder.InitDecode(InBuf : PMBBuffer);
var
    n : Integer;
begin
    //初始化
    self.FBuf:=InBuf;
    self.FLow:=0;
    self.FRange:=RC_MAX_RANGE;

    //读入编码
    self.FDigits:=0;

    n:=RC_CODE_BITS+1;
    repeat
        Dec(n,8);
        self.FDigits:=(self.FDigits shl 8) or self.InputCode;
    until n<=0;

    //完成
end;

//根据当前的区间，按照指定的Total计算出估计累积频度，并返回，
//Total：总计频度。
function TRCCoder.DecodeTarget(Total : Cardinal): Cardinal;
var
    Code : Cardinal;
begin
    Code:=self.FDigits shr 1;

    //计算估计累积频度
    self.FRange:=self.FRange div Total;
    if Code<self.FLow then
    begin
        Result:=(Code+RC_MAX_RANGE-self.FLow) div self.FRange;
    end
    else
    begin
        Result:=(Code-self.FLow) div self.FRange;
    end;

    //完成
end;

//按照指定的频度数据调整当前区间，根据需要从缓冲区FBuf中读入数据，
//在调用本函数之前必需先调用DecodeTarget函数，
//根据FBuf.Offset确定读取位置，读取后修改FBuf.Offset，
//CumFreq：累积频度；
//Freq：频度。
procedure TRCCoder.Decode(CumFreq,Freq : Cardinal);
begin
    //区间计算
    Inc(self.FLow,CumFreq*self.FRange);
    self.FRange:=Freq*self.FRange;

    //调整区间
    while self.FRange<=RC_MIN_RANGE do
    begin
        self.FLow:=(self.FLow shl 8) and (RC_MAX_RANGE-1);
        self.FRange:=self.FRange shl 8;
        self.FDigits:=(self.FDigits shl 8) or self.InputCode;
    end;

    //完成
end;

//结束编码，进行收尾操作。
procedure TRCCoder.FinishDecode;
begin
    self.FBuf:=nil;
end;

{TRCModel} //统计模型（0阶）

//新建统计模型。
constructor TRCModel.Create;
begin
    self.FCoder:=nil;
end;

//销毁统计模型。
destructor TRCModel.Destroy;
begin
end;

//获取指定符号的累积频度和频度，
//Symbol：符号值；
//CumFreq：符号的累积频度；
//Freq：符号的频度。
procedure TRCModel.GetFreq(Symbol : TRCSymbol; var CumFreq,Freq : Cardinal);
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
procedure TRCModel.IncFreq(Symbol : TRCSymbol);
var
    i,Id,Parent : Integer;
    Freq,NewFreq : Cardinal;
begin
    if self.FTotal=RC_MAX_FREQ then
    begin
        //削减频度
        self.FTree[0]:=(self.FTree[0]+1) shr 1;
        self.FTotal:=self.FTree[0];
        for i:=1 to RC_SYMBOL_NO do
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
            until Id>RC_SYMBOL_NO;
        end;
    end;

    //更新频度
    if Symbol=0 then Inc(self.FTree[0])
    else
    begin
        repeat
            Inc(self.FTree[Symbol]);
            Inc(Symbol,Symbol and -Symbol);
        until Symbol>RC_SYMBOL_NO;
    end;
    Inc(self.FTotal);

    //完成
end;

//查找指定的估算频度，返回对应的符号，
//EstFreq：估算频度值。
function TRCModel.FindEstFreq(EstFreq : Cardinal): TRCSymbol;
var
    Mask,Id : Integer;
begin
    //排除符号0和结束符
    if EstFreq<self.FTree[0] then
    begin
        Result:=0; exit;
    end;
    Dec(EstFreq,self.FTree[0]);
    if EstFreq>=self.FTree[RC_SYMBOL_NO] then
    begin
        Result:=RC_EOM; exit;
    end;

    //查找
    Result:=0;
    Mask:=RC_SYMBOL_NO shr 1;
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
procedure TRCModel.InitModel(Coder : PRCCoder);
var
    i,Id : Integer;
begin
    self.FCoder:=Coder;

    //初始化频度，初始时每个符号的频度都为1
    self.FTree[0]:=1;

    for i:=1 to RC_SYMBOL_NO do self.FTree[i]:=0;
    for i:=1 to RC_SYMBOL_NO do
    begin
        Id:=i;
        repeat
            Inc(self.FTree[Id]);
            Inc(Id,Id and -Id);
        until Id>RC_SYMBOL_NO;
    end;
    self.FTotal:=RC_SYMBOL_NO+1;

    //完成
end;

//利用区间编码算法对一个符号进行编码并写入到FBuf中，
//根据FBuf.Offset确定保存位置，保存后修改FBuf.Offset和FBuf.DataSize，
//Symbol：符号值。
procedure TRCModel.Encode(Symbol : TRCSymbol);
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

//利用区间编码算法对从FBuf中解码出一个符号，并返回，
//根据FBuf.Offset确定读取位置，读取后修改FBuf.Offset，
function TRCModel.Decode: TRCSymbol;
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
procedure TRCModel.FinishModel;
begin
    self.FCoder:=nil;
end;

{TRCCoding} //区间编码编解码器，对TRCCoder和TRCModel的简单封装

//新建区间编码编解码器。
constructor TRCCoding.Create;
begin
    self.FCoder:=TRCCoder.Create;
    self.FModel:=TRCModel.Create;
end;

//销毁区间编码编解码器。
destructor TRCCoding.Destroy;
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
function TRCCoding.Encode(var InBuf,OutBuf : TMBBuffer; Size : Integer): Integer;
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
//缓冲区InBuf中的压缩数据必需是使用TRCCoding.Encode保存的，
//根据InBuf.Offset确定读取位置，读取后修改InBuf.Offset，
//根据OutBuf.Offset确定写入位置，写入后修改OutBuf.Offset，
//InBuf：输入缓冲区；
//OutBuf：输出缓冲区。
function TRCCoding.Decode(var InBuf,OutBuf : TMBBuffer): Integer;
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
