program Project1;

uses
  Forms,
  Unit1 in 'Unit1.pas' {Form1},
  MemoryBuffer in 'MemoryBuffer.pas',
  CanonicalHuffman in 'CanonicalHuffman.pas',
  RangeCoding in 'RangeCoding.pas',
  ArithmeticCoding in 'ArithmeticCoding.pas';

{$R *.res}

begin
  Application.Initialize;
  Application.CreateForm(TForm1, Form1);
  Application.Run;
end.

