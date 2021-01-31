//
//区间编码主窗口
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

unit Unit1;

interface

uses
  Windows, Messages, SysUtils, Variants, Classes, Graphics, Controls, Forms,
  Dialogs, StdCtrls, ExtCtrls,

  MemoryBuffer, CanonicalHuffman, RangeCoding, ArithmeticCoding;

type
  TForm1 = class(TForm)
    Panel1: TPanel;
    Memo1: TMemo;
    Edit1: TEdit;
    Edit2: TEdit;
    OpenDialog1: TOpenDialog;
    SaveDialog1: TSaveDialog;
    Button1: TButton;
    ComboBox1: TComboBox;
    Button2: TButton;
    Button3: TButton;
    Button4: TButton;
    Button5: TButton;
    procedure Edit1DblClick(Sender: TObject);
    procedure Edit2DblClick(Sender: TObject);
    procedure Button1Click(Sender: TObject);
    procedure Button2Click(Sender: TObject);
    procedure Button3Click(Sender: TObject);
    procedure Button4Click(Sender: TObject);
    procedure Button5Click(Sender: TObject);
  private
    FHaveError : Boolean; //比较文件时，是否有错误
    FInSize : Integer; //输入数据大小
    FOutSize : Integer; //输出数据大小
    FTime : Cardinal; //耗时
  public
    procedure OutRadio;

    procedure PackCanHuf8;
    procedure UnpackCanHuf8;

    procedure PackRange;
    procedure UnpackRange;

    procedure PackArithmetic;
    procedure UnpackArithmetic;

  end;

var
  Form1: TForm1;

implementation

{$R *.dfm}

//浏览输入文件。
procedure TForm1.Edit1DblClick(Sender: TObject);
begin
    if self.OpenDialog1.Execute then
    begin
        self.Edit1.Text:=self.OpenDialog1.FileName;
    end;
end;

//浏览输出文件。
procedure TForm1.Edit2DblClick(Sender: TObject);
begin
    if self.SaveDialog1.Execute then
    begin
        self.Edit2.Text:=self.SaveDialog1.FileName;
    end;
end;

//压缩，
//根据当前的算法设置，调用相关的函数进行压缩操作，
//将Edit1对应的文件压缩保存到Edit2对应的文件中。
procedure TForm1.Button1Click(Sender: TObject);
begin
    case self.ComboBox1.ItemIndex of
        0 : self.PackCanHuf8;
        1 : self.PackRange;
        2 : self.PackArithmetic;
    end;
end;

//解压缩，
//根据当前的算法设置，调用相关的函数进行解压缩操作，
//将Edit1对应的文件解压缩保存到Edit2对应的文件中。
procedure TForm1.Button2Click(Sender: TObject);
begin
    case self.ComboBox1.ItemIndex of
        0 : self.UnpackCanHuf8;
        1 : self.UnpackRange;
        2 : self.UnpackArithmetic;
    end;
end;

//文件比较，
//将Edit1对应的文件和Edit2对应的文件进行比较，结果输出到Memo1中，
//比较结束后设置FHaveError。
procedure TForm1.Button3Click(Sender: TObject);
var
    s1,s2 : TFileStream;
    l1,l2,i : Integer;
    m1,m2 : Pointer;
    d1,d2 : PByte;
    b : Boolean;
begin
    self.FHaveError:=False;

    self.Memo1.Lines.Add('');
    self.Memo1.Lines.Add('比较文件：');
    self.Memo1.Lines.Add(self.Edit1.Text);
    self.Memo1.Lines.Add(self.Edit2.Text);
    s1:=TFileStream.Create(self.Edit1.Text,fmOpenRead);
    s2:=TFileStream.Create(self.Edit2.Text,fmOpenRead);
    l1:=s1.Size;
    l2:=s2.Size;

    if l1<>l2 then
    begin
        self.Memo1.Lines.Add(Format('长度%d与%d不一致，',[l1,l2]));
        self.FHaveError:=True;
        if l1>l2 then l1:=l2;
    end;

    GetMem(m1,l1); s1.Read(m1^,l1); s1.Free; d1:=m1;
    GetMem(m2,l1); s2.Read(m2^,l1); s2.Free; d2:=m2;

    b:=True;
    for i:=0 to l1-1 do
    begin
        if d1^<>d2^ then
        begin
            b:=False;
            self.FHaveError:=True;
            self.Memo1.Lines.Add(Format(
                '在%d位置不一致：$%.2x<>$%.2x。',
                [i,d1^,d2^]));
            break;
        end;
        Inc(d1); Inc(d2);
    end;
    if b then self.Memo1.Lines.Add(Format('长度%d字节，比较一致。',[l1]));
    
    FreeMem(m1);
    FreeMem(m2);
end;

//批量测试，
//将Edit1对应的文件夹下的所有文件，根据当前的算法设置，进行测试，
//将文件压缩到一临时文件中，再解压缩到另一临时文件，最后比较结果，
//所有文件测试完成之后，统计并在Memo1中输出结果。
procedure TForm1.Button4Click(Sender: TObject);
var
    Find : THandle;
    FindData : TWIN32FindData;

    DirName,OutDir,FileName,PackFile,DataFile,OutText,s : String;
    FileList : TStringList;
    b : Boolean;

    Infos : array of array [0..6] of String;
    InfoLen : array [0..6] of Integer;
    InCount,OutCount : Int64;

    i,n,l : Integer;
begin
    self.Button1.Enabled:=False;
    self.Button2.Enabled:=False;
    self.Button3.Enabled:=False;
    self.Button4.Enabled:=False;

    //确认文件夹
    DirName:=self.Edit1.Text;
    if DirName[Length(DirName)]<>'\' then DirName:=DirName+'\';
    if not DirectoryExists(DirName) then
    begin
        self.Memo1.Lines.Add('');
        self.Memo1.Lines.Add('以下文件夹没有找到：');
        self.Memo1.Lines.Add(DirName);
        self.Button1.Enabled:=True;
        self.Button2.Enabled:=True;
        self.Button3.Enabled:=True;
        self.Button4.Enabled:=True;
        exit;
    end;

    OutDir:=self.Edit2.Text;
    if OutDir[Length(OutDir)]<>'\' then OutDir:=OutDir+'\';
    if not DirectoryExists(OutDir) then
    begin
        self.Memo1.Lines.Add('');
        self.Memo1.Lines.Add('以下文件夹没有找到：');
        self.Memo1.Lines.Add(OutDir);
        self.Button1.Enabled:=True;
        self.Button2.Enabled:=True;
        self.Button3.Enabled:=True;
        self.Button4.Enabled:=True;
        exit;
    end;

    //查找文件
    FileName:=DirName+'*';

    self.Memo1.Lines.Add('');
    self.Memo1.Lines.Add('批量测试以下文件夹中的所有文件：');
    self.Memo1.Lines.Add(DirName);

    FileList:=TStringList.Create;

    Find:=FindFirstFile(PChar(FileName),FindData);
    b:=Find<>INVALID_HANDLE_VALUE;

    while b do
    begin
        if ((FindData.dwFileAttributes and FILE_ATTRIBUTE_DIRECTORY)=0) and
           (FindData.nFileSizeLow<>0) then
        begin
            //记录非空文件
            FileList.Add(FindData.cFileName);
        end;
        b:=FindNextFile(Find,FindData);
    end;

    Windows.FindClose(Find);

    if FileList.Count=0 then
    begin
        self.Memo1.Lines.Add('文件夹中没有找到文件，测试结束。');
        FileList.Free;
        self.Button1.Enabled:=True;
        self.Button2.Enabled:=True;
        self.Button3.Enabled:=True;
        self.Button4.Enabled:=True;
        exit;
    end
    else
    begin
        self.Memo1.Lines.Add('');
        self.Memo1.Lines.Add(Format('共有%d个文件，测试开始...',[FileList.Count]));
    end;

    //开始测试
    PackFile:=OutDir+'_Temp.pack'; //压缩后的文件
    DataFile:=OutDir+'_Temp.data'; //解压缩后的文件

    SetLength(Infos,FileList.Count);

    InCount:=0;
    OutCount:=0;

    for i:=0 to FileList.Count-1 do
    begin
        //文件名
        FileName:=FileList[i];
        Infos[i][0]:=FileName;

        //压缩
        self.Caption:='压缩测试：'+FileName;
        Application.Title:=self.Caption;

        self.Edit1.Text:=DirName+FileName;
        self.Edit2.Text:=PackFile;
        self.Button1Click(self);

        //输入大小
        Infos[i][1]:=Format('%dB',[self.FInSize]);
        Inc(InCount,self.FInSize);

        //输出大小
        Infos[i][2]:=Format('%dB',[self.FOutSize]);
        Inc(OutCount,self.FOutSize);

        //压缩率
        Infos[i][3]:=Format('%d％',[
            ((self.FInSize-self.FOutSize)*100) div self.FInSize]);

        //bpc
        Infos[i][4]:=Format('%1.3fbpc',[
            (self.FOutSize*8)/self.FInSize]);

        //编码时间
        Infos[i][5]:=Format('%dms',[self.FTime]);

        //解压缩
        self.Caption:='解压测试：'+FileName;
        Application.Title:=self.Caption;

        self.Edit1.Text:=PackFile;
        self.Edit2.Text:=DataFile;
        self.Button2Click(self);

        //文件比较
        self.Caption:='文件比较：'+FileName;
        Application.Title:=self.Caption;

        self.FHaveError:=False;

        self.Edit1.Text:=DirName+FileName;
        self.Edit2.Text:=DataFile;
        self.Button3Click(self);

        //解码时间
        if self.FHaveError then
        begin
            Infos[i][6]:='解码错误';
        end
        else
        begin
            Infos[i][6]:=Format('%dms',[self.FTime]);
        end;
    end;

    //整理数据
    for n:=0 to 6 do InfoLen[n]:=0;

    for i:=0 to FileList.Count-1 do
    begin
        for n:=0 to 6 do
        begin
            l:=Length(Infos[i][n]);
            if l>InfoLen[n] then InfoLen[n]:=l;
        end;
    end;

    for n:=1 to 6 do Inc(InfoLen[n]);

    //输出测试信息
    self.Memo1.Lines.Add('');
    self.Memo1.Lines.Add(self.ComboBox1.Text+'，批量测试结果如下：');
    self.Memo1.Lines.Add('');
    self.Memo1.Lines.Add('文件名 输入大小 输出大小 压缩率 bpc 编码耗时 解码耗时');
    self.Memo1.Lines.Add('');

    for i:=0 to FileList.Count-1 do
    begin
        OutText:=Infos[i][0];
        l:=Length(OutText);
        while l<InfoLen[0] do
        begin
            OutText:=OutText+' '; Inc(l);
        end;
        for n:=1 to 6 do
        begin
            s:=Infos[i][n];
            l:=Length(s);
            while l<InfoLen[n] do
            begin
                s:=' '+s; Inc(l);
            end;
            OutText:=OutText+s;
        end;

        self.Memo1.Lines.Add(OutText);
    end;

    //输入输出大小总计
    Infos[0][0]:='总计 ';
    Infos[1][0]:='     ';
    Infos[2][0]:='     ';

    Infos[0][1]:='输入大小：';
    Infos[1][1]:='输出大小：';
    Infos[2][1]:='压缩率：';

    Infos[0][2]:=Format('%dB',[InCount]);
    Infos[1][2]:=Format('%dB',[OutCount]);
    Infos[2][2]:=Format('%d％ %1.3fbpc',[
        ((InCount-OutCount)*100) div InCount,
        (OutCount*8)/InCount]);

    InfoLen[2]:=0;
    for i:=0 to 2 do
    begin
        l:=Length(Infos[i][2]);
        if l>InfoLen[2] then InfoLen[2]:=l;
    end;
    Inc(InfoLen[2]);

    self.Memo1.Lines.Add('');
    for i:=0 to 2 do
    begin
        s:=Infos[i][0];
        l:=Length(s);
        while l<InfoLen[0] do
        begin
            s:=s+' '; Inc(l);
        end;
        OutText:=s;

        s:=Infos[i][1];
        l:=Length(s);
        while l<InfoLen[1] do
        begin
            s:=s+' '; Inc(l);
        end;
        OutText:=OutText+s;

        s:=Infos[i][2];
        l:=Length(s);
        while l<InfoLen[2] do
        begin
            s:=' '+s; Inc(l);
        end;
        OutText:=OutText+s;

        self.Memo1.Lines.Add(OutText);
    end;

    self.Caption:='批量测试完成';
    Application.Title:=self.Caption;
    self.Edit1.Text:=DirName;
    self.Edit2.Text:=OutDir;

    self.Memo1.Lines.Add('');
    self.Memo1.Lines.Add('批量测试完成。');

    FileList.Free;
    self.Button1.Enabled:=True;
    self.Button2.Enabled:=True;
    self.Button3.Enabled:=True;
    self.Button4.Enabled:=True;

    //完成
end;

//清空信息。
procedure TForm1.Button5Click(Sender: TObject);
begin
    self.Memo1.Lines.Clear;
end;

//输出当前的压缩率。
procedure TForm1.OutRadio;
begin
    self.Memo1.Lines.Add(Format('操作完成，耗时：%d',[self.FTime]));
    self.Memo1.Lines.Add(Format('压缩前：%d 字节',[self.FInSize]));
    self.Memo1.Lines.Add(Format('压缩后：%d 字节',[self.FOutSize]));
    self.Memo1.Lines.Add(Format('压缩率：%d％ %1.3fbpc',[
        ((self.FInSize-self.FOutSize)*100) div self.FInSize,
        (self.FOutSize*8)/self.FInSize]));
end;

//范式哈夫曼算法（8位符号），
//将Edit1对应的文件压缩保存到Edit2对应的文件中，
//同时记录输入大小、输出大小、算法耗时。
procedure TForm1.PackCanHuf8;
var
    InFile,OutFile : String;
    InBuf,OutBuf : TMBBuffer;

    Coding : TCHCoding;
begin
    self.Memo1.Lines.Add('');
    self.Memo1.Lines.Add('使用范式哈夫曼算法压缩（8位符号）...');
    InFile:=self.Edit1.Text;
    OutFile:=self.Edit2.Text;
    self.Memo1.Lines.Add('从：'+InFile);
    self.Memo1.Lines.Add('到：'+OutFile);

    //建立缓冲区
    MBInit(InBuf);
    MBInit(OutBuf);

    self.FInSize:=MBLoadFromFile(InBuf,InFile);

    //建立编码器
    Coding:=TCHCoding.Create;

    //计时
    self.FTime:=GetTickCount;

    self.FOutSize:=Coding.Encode(InBuf,OutBuf,self.FInSize);

    //压缩完成
    self.FTime:=GetTickCount-self.FTime;

    Coding.Free;

    //保存数据
    MBSaveToFile(OutBuf,self.FOutSize,OutFile);

    MBFree(InBuf);
    MBFree(OutBuf);

    //计算比率
    self.OutRadio;

    //完成
end;

//范式哈夫曼算法（8位符号），
//将Edit1对应的文件解压缩保存到Edit2对应的文件中，
//同时记录算法耗时。
procedure TForm1.UnpackCanHuf8;
var
    InFile,OutFile : String;
    InBuf,OutBuf : TMBBuffer;

    Coding : TCHCoding;

    Size : Integer;
begin
    self.Memo1.Lines.Add('');
    self.Memo1.Lines.Add('使用范式哈夫曼算法解压缩（8位符号）...');
    InFile:=self.Edit1.Text;
    OutFile:=self.Edit2.Text;
    self.Memo1.Lines.Add('从：'+InFile);
    self.Memo1.Lines.Add('到：'+OutFile);

    //建立缓冲区
    MBInit(InBuf);
    MBInit(OutBuf);

    MBLoadFromFile(InBuf,InFile);

    //建立解码器
    Coding:=TCHCoding.Create;

    //计时
    self.FTime:=GetTickCount;

    Size:=Coding.Decode(InBuf,OutBuf);

    //解压缩完成
    self.FTime:=GetTickCount-self.FTime;

    Coding.Free;

    //保存数据
    MBSaveToFile(OutBuf,Size,OutFile);

    MBFree(InBuf);
    MBFree(OutBuf);

    //提示
    self.Memo1.Lines.Add(Format('操作完成，耗时：%d',[self.FTime]));

    //完成
end;

//区间编码算法，
//将Edit1对应的文件压缩保存到Edit2对应的文件中，
//同时记录输入大小、输出大小、算法耗时。
procedure TForm1.PackRange;
var
    InFile,OutFile : String;
    InBuf,OutBuf : TMBBuffer;

    Coding : TRCCoding;
begin
    self.Memo1.Lines.Add('');
    self.Memo1.Lines.Add('使用区间编码算法压缩...');
    InFile:=self.Edit1.Text;
    OutFile:=self.Edit2.Text;
    self.Memo1.Lines.Add('从：'+InFile);
    self.Memo1.Lines.Add('到：'+OutFile);

    //建立缓冲区
    MBInit(InBuf);
    MBInit(OutBuf);

    self.FInSize:=MBLoadFromFile(InBuf,InFile);

    //建立编码器
    Coding:=TRCCoding.Create;

    //计时
    self.FTime:=GetTickCount;

    self.FOutSize:=Coding.Encode(InBuf,OutBuf,self.FInSize);

    //压缩完成
    self.FTime:=GetTickCount-self.FTime;

    Coding.Free;

    //保存数据
    MBSaveToFile(OutBuf,self.FOutSize,OutFile);

    MBFree(InBuf);
    MBFree(OutBuf);

    //计算比率
    self.OutRadio;

    //完成
end;

//区间编码算法，
//将Edit1对应的文件解压缩保存到Edit2对应的文件中，
//同时记录算法耗时。
procedure TForm1.UnpackRange;
var
    InFile,OutFile : String;
    InBuf,OutBuf : TMBBuffer;

    Coding : TRCCoding;

    Size : Integer;
begin
    self.Memo1.Lines.Add('');
    self.Memo1.Lines.Add('使用区间编码算法解压缩...');
    InFile:=self.Edit1.Text;
    OutFile:=self.Edit2.Text;
    self.Memo1.Lines.Add('从：'+InFile);
    self.Memo1.Lines.Add('到：'+OutFile);

    //建立缓冲区
    MBInit(InBuf);
    MBInit(OutBuf);

    MBLoadFromFile(InBuf,InFile);

    //建立解码器
    Coding:=TRCCoding.Create;

    //计时
    self.FTime:=GetTickCount;

    Size:=Coding.Decode(InBuf,OutBuf);

    //解压缩完成
    self.FTime:=GetTickCount-self.FTime;

    Coding.Free;

    //保存数据
    MBSaveToFile(OutBuf,Size,OutFile);

    MBFree(InBuf);
    MBFree(OutBuf);

    //提示
    self.Memo1.Lines.Add(Format('操作完成，耗时：%d',[self.FTime]));

    //完成
end;

//算术编码算法，
//将Edit1对应的文件压缩保存到Edit2对应的文件中，
//同时记录输入大小、输出大小、算法耗时。
procedure TForm1.PackArithmetic;
var
    InFile,OutFile : String;
    InBuf,OutBuf : TMBBuffer;

    Coding : TACCoding;
begin
    self.Memo1.Lines.Add('');
    self.Memo1.Lines.Add('使用算术编码算法压缩...');
    InFile:=self.Edit1.Text;
    OutFile:=self.Edit2.Text;
    self.Memo1.Lines.Add('从：'+InFile);
    self.Memo1.Lines.Add('到：'+OutFile);

    //建立缓冲区
    MBInit(InBuf);
    MBInit(OutBuf);

    self.FInSize:=MBLoadFromFile(InBuf,InFile);

    //建立编码器
    Coding:=TACCoding.Create;

    //计时
    self.FTime:=GetTickCount;

    self.FOutSize:=Coding.Encode(InBuf,OutBuf,self.FInSize);

    //压缩完成
    self.FTime:=GetTickCount-self.FTime;

    Coding.Free;

    //保存数据
    MBSaveToFile(OutBuf,self.FOutSize,OutFile);

    MBFree(InBuf);
    MBFree(OutBuf);

    //计算比率
    self.OutRadio;

    //完成
end;

//算术编码算法，
//将Edit1对应的文件解压缩保存到Edit2对应的文件中，
//同时记录算法耗时。
procedure TForm1.UnpackArithmetic;
var
    InFile,OutFile : String;
    InBuf,OutBuf : TMBBuffer;

    Coding : TACCoding;

    Size : Integer;
begin
    self.Memo1.Lines.Add('');
    self.Memo1.Lines.Add('使用算术编码算法解压缩...');
    InFile:=self.Edit1.Text;
    OutFile:=self.Edit2.Text;
    self.Memo1.Lines.Add('从：'+InFile);
    self.Memo1.Lines.Add('到：'+OutFile);

    //建立缓冲区
    MBInit(InBuf);
    MBInit(OutBuf);

    MBLoadFromFile(InBuf,InFile);

    //建立解码器
    Coding:=TACCoding.Create;

    //计时
    self.FTime:=GetTickCount;

    Size:=Coding.Decode(InBuf,OutBuf);

    //解压缩完成
    self.FTime:=GetTickCount-self.FTime;

    Coding.Free;

    //保存数据
    MBSaveToFile(OutBuf,Size,OutFile);

    MBFree(InBuf);
    MBFree(OutBuf);

    //提示
    self.Memo1.Lines.Add(Format('操作完成，耗时：%d',[self.FTime]));

    //完成
end;

//单元结束
end.

