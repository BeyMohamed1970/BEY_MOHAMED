object Point_Clouds_Import: TPoint_Clouds_Import
  Left = 895
  Top = 10
  BorderIcons = [biSystemMenu]
  BorderStyle = bsSingle
  Caption = 'Importing Point Clouds'
  ClientHeight = 412
  ClientWidth = 323
  Color = clGradientInactiveCaption
  Font.Charset = DEFAULT_CHARSET
  Font.Color = clWindowText
  Font.Height = -11
  Font.Name = 'MS Sans Serif'
  Font.Style = []
  Icon.Data = {
    0000010001002020040000000000E80200001600000028000000200000004000
    0000010004000000000000020000000000000000000000000000000000000000
    000000008000008000000080800080000000800080008080000080808000C0C0
    C0000000FF0000FF000000FFFF00FF000000FF00FF00FFFF0000FFFFFF007F8C
    8C8C8C8F848B8B8B8BF0778077807F888888888F484BB7B7B78888F888F87F8C
    8C8C8C8F848B8B8B8B80778077807F888888888F4848B8B747F888F888F87F8C
    8C8C8C8F84848B844780778077807F888888888F4848484744F888F888F87F8C
    8C8C8C8F848488474787778777877F888888888F4848484447F07780778007FC
    8C8C8C8F8484884744F888F888F807F88888888F4848484747FFFFFFFFFF07FC
    8C8C8C8F8484884447447744747707F88888888F4848484744448774840007FC
    8C8C8C8F8484884747447744840007F88888888F4848484447448774840007FC
    8C8C8C8F8484884744447744840007F88888888F4848484747448774840007FC
    8C8C8C8F8484884447447747480007F88888888F4848484444448774800007FC
    8C8C8C8F8484848444447748000007F88888888F4848484884448480000007FC
    8C8C8C8F8484848488444800000007F88888888F48484848800480000000007F
    8C8C8C8F84848484800480000000007F8888888F48484848800480000000007F
    8C8C8C8F84848484800480000000007F8888888F48484848800480000000007F
    8C8C8C8F84848484800000000000007F8888888F48484848800000000000007F
    8C8C8C8F84848484800000000000007FFF88888F484888888000000000000007
    77FFFFFF88880000070000000000000000777777000070000000000000000000
    0000000000000000000000000000000000000000000000000000000000008000
    0000800000008000000080000003800000038000000380000003800000038000
    0003800000078000000F8000001F8000003F8000027FC000027FC000027FC000
    027FC000027FC00003FFC00003FFC00003FFC00003FFE00003FFFC007FFF}
  OldCreateOrder = False
  Scaled = False
  OnClose = FormClose
  OnShow = FormShow
  PixelsPerInch = 96
  TextHeight = 13
  object Button1: TButton
    Left = 104
    Top = 5
    Width = 98
    Height = 25
    Caption = 'Lire les fichiers de points_OLD'
    Font.Charset = DEFAULT_CHARSET
    Font.Color = clWindowText
    Font.Height = -13
    Font.Name = 'MS Sans Serif'
    Font.Style = [fsBold]
    ParentFont = False
    TabOrder = 0
    Visible = False
    OnClick = Button1Click
  end
  object GroupBox5: TGroupBox
    Left = 9
    Top = 35
    Width = 304
    Height = 227
    Caption = 'Point cloud parameters'
    Font.Charset = DEFAULT_CHARSET
    Font.Color = clWindowText
    Font.Height = -13
    Font.Name = 'MS Sans Serif'
    Font.Style = [fsBold]
    ParentFont = False
    TabOrder = 1
    Visible = False
    object Label10: TLabel
      Left = 66
      Top = 24
      Width = 80
      Height = 13
      Caption = 'Number of points'
      Font.Charset = DEFAULT_CHARSET
      Font.Color = clWindowText
      Font.Height = -11
      Font.Name = 'MS Sans Serif'
      Font.Style = []
      ParentFont = False
    end
    object GroupBox4: TGroupBox
      Left = 36
      Top = 48
      Width = 231
      Height = 95
      Caption = 'Limits of the raw part'
      Font.Charset = DEFAULT_CHARSET
      Font.Color = clWindowText
      Font.Height = -13
      Font.Name = 'MS Sans Serif'
      Font.Style = [fsBold]
      ParentFont = False
      TabOrder = 0
      object Label4: TLabel
        Left = 132
        Top = 26
        Width = 26
        Height = 13
        Caption = 'Xmax'
        Font.Charset = DEFAULT_CHARSET
        Font.Color = clWindowText
        Font.Height = -11
        Font.Name = 'MS Sans Serif'
        Font.Style = []
        ParentFont = False
      end
      object Label1: TLabel
        Left = 8
        Top = 26
        Width = 23
        Height = 13
        Caption = 'Xmin'
        Font.Charset = DEFAULT_CHARSET
        Font.Color = clWindowText
        Font.Height = -11
        Font.Name = 'MS Sans Serif'
        Font.Style = []
        ParentFont = False
      end
      object Label2: TLabel
        Left = 8
        Top = 48
        Width = 23
        Height = 13
        Caption = 'Ymin'
        Font.Charset = DEFAULT_CHARSET
        Font.Color = clWindowText
        Font.Height = -11
        Font.Name = 'MS Sans Serif'
        Font.Style = []
        ParentFont = False
      end
      object Label5: TLabel
        Left = 132
        Top = 48
        Width = 26
        Height = 13
        Caption = 'Ymax'
        Font.Charset = DEFAULT_CHARSET
        Font.Color = clWindowText
        Font.Height = -11
        Font.Name = 'MS Sans Serif'
        Font.Style = []
        ParentFont = False
      end
      object Label3: TLabel
        Left = 8
        Top = 70
        Width = 23
        Height = 13
        Caption = 'Zmin'
        Font.Charset = DEFAULT_CHARSET
        Font.Color = clWindowText
        Font.Height = -11
        Font.Name = 'MS Sans Serif'
        Font.Style = []
        ParentFont = False
      end
      object Label6: TLabel
        Left = 132
        Top = 70
        Width = 26
        Height = 13
        Caption = 'Zmax'
        Font.Charset = DEFAULT_CHARSET
        Font.Color = clWindowText
        Font.Height = -11
        Font.Name = 'MS Sans Serif'
        Font.Style = []
        ParentFont = False
      end
      object Edit1: TEdit
        Left = 168
        Top = 20
        Width = 55
        Height = 24
        Font.Charset = DEFAULT_CHARSET
        Font.Color = clWindowText
        Font.Height = -13
        Font.Name = 'MS Sans Serif'
        Font.Style = [fsBold]
        ParentFont = False
        ReadOnly = True
        TabOrder = 0
      end
      object Edit4: TEdit
        Left = 45
        Top = 20
        Width = 57
        Height = 24
        Font.Charset = DEFAULT_CHARSET
        Font.Color = clWindowText
        Font.Height = -13
        Font.Name = 'MS Sans Serif'
        Font.Style = [fsBold]
        ParentFont = False
        ReadOnly = True
        TabOrder = 1
      end
      object Edit5: TEdit
        Left = 45
        Top = 42
        Width = 57
        Height = 24
        Font.Charset = DEFAULT_CHARSET
        Font.Color = clWindowText
        Font.Height = -13
        Font.Name = 'MS Sans Serif'
        Font.Style = [fsBold]
        ParentFont = False
        ReadOnly = True
        TabOrder = 2
      end
      object Edit2: TEdit
        Left = 168
        Top = 42
        Width = 55
        Height = 24
        Font.Charset = DEFAULT_CHARSET
        Font.Color = clWindowText
        Font.Height = -13
        Font.Name = 'MS Sans Serif'
        Font.Style = [fsBold]
        ParentFont = False
        ReadOnly = True
        TabOrder = 3
      end
      object Edit6: TEdit
        Left = 45
        Top = 64
        Width = 57
        Height = 24
        Font.Charset = DEFAULT_CHARSET
        Font.Color = clWindowText
        Font.Height = -13
        Font.Name = 'MS Sans Serif'
        Font.Style = [fsBold]
        ParentFont = False
        ReadOnly = True
        TabOrder = 4
      end
      object Edit3: TEdit
        Left = 168
        Top = 64
        Width = 55
        Height = 24
        Font.Charset = DEFAULT_CHARSET
        Font.Color = clWindowText
        Font.Height = -13
        Font.Name = 'MS Sans Serif'
        Font.Style = [fsBold]
        ParentFont = False
        ReadOnly = True
        TabOrder = 5
      end
    end
    object GroupBox3: TGroupBox
      Left = -3
      Top = 152
      Width = 309
      Height = 55
      Caption = 'Dimensions of the raw part (mm x mm x mm)'
      Font.Charset = DEFAULT_CHARSET
      Font.Color = clWindowText
      Font.Height = -13
      Font.Name = 'MS Sans Serif'
      Font.Style = [fsBold]
      ParentFont = False
      TabOrder = 1
      object Label7: TLabel
        Left = 11
        Top = 27
        Width = 33
        Height = 13
        Caption = 'Length'
        Font.Charset = DEFAULT_CHARSET
        Font.Color = clWindowText
        Font.Height = -11
        Font.Name = 'MS Sans Serif'
        Font.Style = []
        ParentFont = False
      end
      object Label8: TLabel
        Left = 121
        Top = 27
        Width = 28
        Height = 13
        Caption = 'Width'
        Font.Charset = DEFAULT_CHARSET
        Font.Color = clWindowText
        Font.Height = -11
        Font.Name = 'MS Sans Serif'
        Font.Style = []
        ParentFont = False
      end
      object Label9: TLabel
        Left = 216
        Top = 27
        Width = 31
        Height = 13
        Caption = 'Height'
        Font.Charset = DEFAULT_CHARSET
        Font.Color = clWindowText
        Font.Height = -11
        Font.Name = 'MS Sans Serif'
        Font.Style = []
        ParentFont = False
      end
      object Edit7: TEdit
        Left = 49
        Top = 21
        Width = 55
        Height = 24
        Font.Charset = DEFAULT_CHARSET
        Font.Color = clWindowText
        Font.Height = -13
        Font.Name = 'MS Sans Serif'
        Font.Style = [fsBold]
        ParentFont = False
        ReadOnly = True
        TabOrder = 0
      end
      object Edit8: TEdit
        Left = 155
        Top = 21
        Width = 53
        Height = 24
        Font.Charset = DEFAULT_CHARSET
        Font.Color = clWindowText
        Font.Height = -13
        Font.Name = 'MS Sans Serif'
        Font.Style = [fsBold]
        ParentFont = False
        ReadOnly = True
        TabOrder = 1
      end
      object Edit9: TEdit
        Left = 250
        Top = 21
        Width = 55
        Height = 24
        Font.Charset = DEFAULT_CHARSET
        Font.Color = clWindowText
        Font.Height = -13
        Font.Name = 'MS Sans Serif'
        Font.Style = [fsBold]
        ParentFont = False
        ReadOnly = True
        TabOrder = 2
      end
    end
    object Edit10: TEdit
      Left = 155
      Top = 20
      Width = 83
      Height = 24
      Font.Charset = DEFAULT_CHARSET
      Font.Color = clWindowText
      Font.Height = -13
      Font.Name = 'MS Sans Serif'
      Font.Style = [fsBold]
      ParentFont = False
      ReadOnly = True
      TabOrder = 2
    end
  end
  object GroupBox6: TGroupBox
    Left = 12
    Top = 268
    Width = 300
    Height = 96
    Caption = 'Visualization'
    Font.Charset = DEFAULT_CHARSET
    Font.Color = clWindowText
    Font.Height = -13
    Font.Name = 'MS Sans Serif'
    Font.Style = [fsBold]
    ParentFont = False
    TabOrder = 2
    Visible = False
    object ComboBox1: TComboBox
      Left = 243
      Top = 22
      Width = 43
      Height = 21
      Style = csDropDownList
      Font.Charset = DEFAULT_CHARSET
      Font.Color = clWindowText
      Font.Height = -11
      Font.Name = 'MS Sans Serif'
      Font.Style = []
      ItemIndex = 1
      ParentFont = False
      TabOrder = 0
      Text = '2'
      Items.Strings = (
        '1'
        '2'
        '3'
        '4'
        '5'
        '6'
        '7'
        '8'
        '9'
        '10')
    end
    object ComboBox3: TComboBox
      Left = 243
      Top = 53
      Width = 43
      Height = 21
      Style = csDropDownList
      Font.Charset = DEFAULT_CHARSET
      Font.Color = clWindowText
      Font.Height = -11
      Font.Name = 'MS Sans Serif'
      Font.Style = []
      ItemIndex = 2
      ParentFont = False
      TabOrder = 1
      Text = '3'
      Items.Strings = (
        '1'
        '2'
        '3'
        '4'
        '5'
        '6'
        '7'
        '8'
        '9'
        '10')
    end
    object CheckBox4: TCheckBox
      Left = 6
      Top = 25
      Width = 118
      Height = 17
      Caption = 'Points'
      Font.Charset = DEFAULT_CHARSET
      Font.Color = clWindowText
      Font.Height = -11
      Font.Name = 'MS Sans Serif'
      Font.Style = []
      ParentFont = False
      TabOrder = 2
      OnClick = CheckBox4Click
    end
    object CheckBox5: TCheckBox
      Left = 6
      Top = 58
      Width = 62
      Height = 17
      Caption = 'Raw part'
      Font.Charset = DEFAULT_CHARSET
      Font.Color = clWindowText
      Font.Height = -11
      Font.Name = 'MS Sans Serif'
      Font.Style = []
      ParentFont = False
      TabOrder = 3
      OnClick = CheckBox5Click
    end
    object GroupBox2: TGroupBox
      Left = 75
      Top = 48
      Width = 161
      Height = 41
      Caption = 'Modes'
      Font.Charset = DEFAULT_CHARSET
      Font.Color = clWindowText
      Font.Height = -11
      Font.Name = 'MS Sans Serif'
      Font.Style = [fsBold]
      ParentFont = False
      TabOrder = 4
      object RadioButton1: TRadioButton
        Left = 12
        Top = 17
        Width = 70
        Height = 17
        Caption = 'Wireframe'
        Checked = True
        Font.Charset = DEFAULT_CHARSET
        Font.Color = clWindowText
        Font.Height = -11
        Font.Name = 'MS Sans Serif'
        Font.Style = []
        ParentFont = False
        TabOrder = 0
        TabStop = True
      end
      object RadioButton2: TRadioButton
        Left = 89
        Top = 17
        Width = 70
        Height = 17
        Caption = 'Rendered'
        Font.Charset = DEFAULT_CHARSET
        Font.Color = clWindowText
        Font.Height = -11
        Font.Name = 'MS Sans Serif'
        Font.Style = []
        ParentFont = False
        TabOrder = 1
      end
    end
  end
  object Button3: TButton
    Left = 63
    Top = 370
    Width = 198
    Height = 25
    Caption = '1. Adaptive triangulation'
    Font.Charset = DEFAULT_CHARSET
    Font.Color = clWindowText
    Font.Height = -13
    Font.Name = 'MS Sans Serif'
    Font.Style = [fsBold]
    ParentFont = False
    TabOrder = 3
    OnClick = Button3Click
  end
  object GroupBox8: TGroupBox
    Left = 394
    Top = 174
    Width = 303
    Height = 84
    Caption = 'Inversion du nuage de points'
    Font.Charset = DEFAULT_CHARSET
    Font.Color = clWindowText
    Font.Height = -11
    Font.Name = 'MS Sans Serif'
    Font.Style = [fsBold]
    ParentFont = False
    TabOrder = 4
    Visible = False
    object Label11: TLabel
      Left = 20
      Top = 27
      Width = 159
      Height = 13
      Caption = 'Coordonn'#233'e Z du plan d'#39'inversion'
      Font.Charset = DEFAULT_CHARSET
      Font.Color = clWindowText
      Font.Height = -11
      Font.Name = 'MS Sans Serif'
      Font.Style = []
      ParentFont = False
    end
    object Edit13: TEdit
      Left = 186
      Top = 21
      Width = 65
      Height = 24
      Font.Charset = DEFAULT_CHARSET
      Font.Color = clWindowText
      Font.Height = -13
      Font.Name = 'MS Sans Serif'
      Font.Style = [fsBold]
      ParentFont = False
      TabOrder = 0
    end
    object Button5: TButton
      Left = 47
      Top = 53
      Width = 210
      Height = 25
      Caption = 'Inverser le nuage de points'
      Font.Charset = DEFAULT_CHARSET
      Font.Color = clWindowText
      Font.Height = -13
      Font.Name = 'MS Sans Serif'
      Font.Style = [fsBold]
      ParentFont = False
      TabOrder = 1
      OnClick = Button5Click
    end
  end
  object Button6: TButton
    Left = 62
    Top = 6
    Width = 198
    Height = 25
    Caption = '0. Import point clouds'
    Font.Charset = DEFAULT_CHARSET
    Font.Color = clWindowText
    Font.Height = -13
    Font.Name = 'MS Sans Serif'
    Font.Style = [fsBold]
    ParentFont = False
    TabOrder = 5
    OnClick = Button6Click
  end
  object SaveDialog1: TSaveDialog
    Filter = 'fichier texte (*.txt)|*.txt'
    Options = [ofOverwritePrompt, ofHideReadOnly, ofEnableSizing]
    Left = 443
    Top = 73
  end
  object OpenDialog2: TOpenDialog
    Filter = 'fichier texte (*.txt)|*.txt'
    Options = [ofHideReadOnly, ofAllowMultiSelect, ofEnableSizing]
    Left = 505
    Top = 121
  end
  object OpenDialog1: TOpenDialog
    DefaultExt = 'txt'
    Filter = 'Fichier texte (*.txt)|*.TXT'
    Options = [ofHideReadOnly, ofAllowMultiSelect, ofPathMustExist, ofFileMustExist, ofEnableSizing]
    Left = 11
    Top = 368
  end
end
