object Form1: TForm1
  Left = 205
  Top = 128
  Width = 572
  Height = 413
  Caption = #21306#38388#32534#30721#31243#24207
  Color = clBtnFace
  Font.Charset = ANSI_CHARSET
  Font.Color = clWindowText
  Font.Height = -12
  Font.Name = #23435#20307
  Font.Style = []
  OldCreateOrder = False
  PrintScale = poNone
  Scaled = False
  PixelsPerInch = 96
  TextHeight = 12
  object Panel1: TPanel
    Left = 0
    Top = 0
    Width = 564
    Height = 137
    Align = alTop
    BevelInner = bvRaised
    BevelOuter = bvLowered
    TabOrder = 0
    object Edit1: TEdit
      Left = 8
      Top = 8
      Width = 545
      Height = 24
      Font.Charset = GB2312_CHARSET
      Font.Color = clWindowText
      Font.Height = -16
      Font.Name = 'Fixedsys'
      Font.Style = []
      ParentFont = False
      TabOrder = 0
      Text = #12288#36755#20837#25991#20214#25110#25991#20214#22841#12288#65288#21452#20987#27983#35272#65289
      OnDblClick = Edit1DblClick
    end
    object Edit2: TEdit
      Left = 8
      Top = 40
      Width = 545
      Height = 24
      Font.Charset = GB2312_CHARSET
      Font.Color = clWindowText
      Font.Height = -16
      Font.Name = 'Fixedsys'
      Font.Style = []
      ParentFont = False
      TabOrder = 1
      Text = #12288#36755#20986#25991#20214#25110#25991#20214#22841#12288#65288#21452#20987#27983#35272#65289
      OnDblClick = Edit2DblClick
    end
    object Button1: TButton
      Left = 8
      Top = 104
      Width = 75
      Height = 25
      Caption = #21387#32553
      TabOrder = 2
      OnClick = Button1Click
    end
    object ComboBox1: TComboBox
      Left = 8
      Top = 72
      Width = 545
      Height = 24
      Style = csDropDownList
      Font.Charset = GB2312_CHARSET
      Font.Color = clWindowText
      Font.Height = -16
      Font.Name = 'Fixedsys'
      Font.Style = []
      ItemHeight = 16
      ItemIndex = 1
      ParentFont = False
      TabOrder = 3
      Text = #21306#38388#32534#30721#31639#27861
      Items.Strings = (
        #33539#24335#21704#22827#26364#31639#27861#65288'8'#20301#31526#21495#65289
        #21306#38388#32534#30721#31639#27861
        #31639#26415#32534#30721#31639#27861)
    end
    object Button2: TButton
      Left = 88
      Top = 104
      Width = 75
      Height = 25
      Caption = #35299#21387#32553
      TabOrder = 4
      OnClick = Button2Click
    end
    object Button3: TButton
      Left = 168
      Top = 104
      Width = 75
      Height = 25
      Caption = #25991#20214#27604#36739
      TabOrder = 5
      OnClick = Button3Click
    end
    object Button4: TButton
      Left = 248
      Top = 104
      Width = 75
      Height = 25
      Caption = #25209#37327#27979#35797
      TabOrder = 6
      OnClick = Button4Click
    end
    object Button5: TButton
      Left = 328
      Top = 104
      Width = 75
      Height = 25
      Caption = #28165#31354#20449#24687
      TabOrder = 7
      OnClick = Button5Click
    end
  end
  object Memo1: TMemo
    Left = 0
    Top = 137
    Width = 564
    Height = 242
    Align = alClient
    Font.Charset = GB2312_CHARSET
    Font.Color = clWindowText
    Font.Height = -16
    Font.Name = 'Fixedsys'
    Font.Style = []
    Lines.Strings = (
      #20351#29992#35828#26126#65306
      ''
      #26412#31383#21475#20013#26377#20004#20010#21333#34892#25991#26412#26694#65292#20174#19978#21040#19979#20026'Edit1'#21644'Edit2'#65292#20197#21450#20854#23427#32452#20214#12290
      ''
      #8220#21387#32553#8221
      #22312'Edit1'#20013#36755#20837#35201#21387#32553#30340#25991#20214#21517#65292#22312'Edit2'#20013#36755#20837#35201#20445#23384#30340#25991#20214#21517#65292#22312
      'ComboBox1'#20013#36873#25321#21387#32553#31639#27861#65292#28982#21518#21333#20987#8220#21387#32553#8221#25353#38062#12290
      ''
      #8220#35299#21387#32553#8221
      #22312'Edit1'#20013#36755#20837#35201#35299#21387#32553#30340#25991#20214#21517#65292#22312'Edit2'#20013#36755#20837#35201#20445#23384#30340#25991#20214#21517#65292#22312
      'ComboBox1'#20013#36873#25321#35299#21387#32553#31639#27861#65292#28982#21518#21333#20987#8220#35299#21387#32553#8221#25353#38062#12290
      #27880#24847#65306#26412#31243#24207#19981#20250#39564#35777#25991#20214#30340#21512#27861#24615#65292#35299#21387#32553#26102#30340#25991#20214#19982#31639#27861#35201#21644#21387#32553#26102
      #30456#23545#24212#65292#21542#21017#20250#20986#29616#26080#27861#39044#27979#30340#21518#26524#12290
      ''
      #8220#25991#20214#27604#36739#8221
      #20998#21035#22312'Edit1'#21644'Edit2'#20013#36755#20837#35201#30456#20114#27604#36739#30340#25991#20214#21517#65292#28982#21518#21333#20987#8220#25991#20214#27604#36739#8221
      #25353#38062#12290
      ''
      #8220#25209#37327#27979#35797#8221
      #22312'Edit1'#20013#36755#20837#35201#35835#21462#25991#20214#30340#25991#20214#22841#21517#65292#22312'Edit2'#20013#36755#20837#35201#20445#23384#20020#26102#25991#20214#30340
      #25991#20214#22841#21517#65292#22312'ComboBox1'#20013#36873#25321#27979#35797#29992#31639#27861#65292#28982#21518#21333#20987#8220#25209#37327#27979#35797#8221#25353#38062#12290
      #27880#24847#65306#26412#31243#24207#23558'Edit1'#25351#23450#30340#25991#20214#22841#19979#30340#25152#26377#25991#20214#65292#26681#25454'Combo1'#20013#36873#25321#30340
      #31639#27861#65292#36827#34892#27979#35797#12290#27979#35797#26102#23558#25991#20214#21387#32553#21040#19968#20020#26102#25991#20214#20013#65292#20877#35299#21387#32553#21040#21478#19968#20020
      #26102#25991#20214#65292#26368#21518#27604#36739#32467#26524#12290#20004#20020#26102#25991#20214#20445#23384#21040'Edit2'#25351#23450#30340#25991#20214#22841#20013#12290#25152#26377
      #25991#20214#27979#35797#23436#25104#20043#21518#65292#32479#35745#24182#22312'Memo1'#20013#36755#20986#32467#26524#12290
      ''
      #8220#28165#31354#20449#24687#8221
      #28165#31354'Memo1'#20013#30340#20869#23481#12290
      ''
      '                                                            '#21494#21494
      '                                                   2010'#24180'8'#26376'30'#26085)
    ParentFont = False
    ScrollBars = ssBoth
    TabOrder = 1
  end
  object OpenDialog1: TOpenDialog
    Left = 328
  end
  object SaveDialog1: TSaveDialog
    Left = 360
  end
end
