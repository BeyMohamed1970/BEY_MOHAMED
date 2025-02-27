object Rendering: TRendering
  Left = 1003
  Top = 63
  Anchors = []
  BorderIcons = [biSystemMenu]
  BorderStyle = bsDialog
  Caption = 'Rendering parameters'
  ClientHeight = 465
  ClientWidth = 330
  Color = clBtnFace
  Font.Charset = DEFAULT_CHARSET
  Font.Color = clWindowText
  Font.Height = -11
  Font.Name = 'MS Sans Serif'
  Font.Style = []
  FormStyle = fsStayOnTop
  OldCreateOrder = False
  OnClose = FormClose
  OnShow = FormShow
  PixelsPerInch = 96
  TextHeight = 13
  object Label12: TLabel
    Left = 464
    Top = 321
    Width = 132
    Height = 13
    Caption = 'Distance par rapport au brut'
    Font.Charset = DEFAULT_CHARSET
    Font.Color = clWindowText
    Font.Height = -11
    Font.Name = 'MS Sans Serif'
    Font.Style = []
    ParentFont = False
  end
  object GroupBox1: TGroupBox
    Left = 8
    Top = 31
    Width = 157
    Height = 161
    Caption = 'Lighting'
    Font.Charset = DEFAULT_CHARSET
    Font.Color = clWindowText
    Font.Height = -11
    Font.Name = 'MS Sans Serif'
    Font.Style = [fsBold]
    ParentFont = False
    TabOrder = 0
    object Label4: TLabel
      Left = 43
      Top = 21
      Width = 38
      Height = 13
      Caption = 'Ambient'
      Font.Charset = DEFAULT_CHARSET
      Font.Color = clWindowText
      Font.Height = -11
      Font.Name = 'MS Sans Serif'
      Font.Style = []
      ParentFont = False
    end
    object Label5: TLabel
      Left = 48
      Top = 65
      Width = 33
      Height = 13
      Caption = 'Diffuse'
      Font.Charset = DEFAULT_CHARSET
      Font.Color = clWindowText
      Font.Height = -11
      Font.Name = 'MS Sans Serif'
      Font.Style = []
      ParentFont = False
    end
    object Label6: TLabel
      Left = 40
      Top = 113
      Width = 42
      Height = 13
      Caption = 'Specular'
      Font.Charset = DEFAULT_CHARSET
      Font.Color = clWindowText
      Font.Height = -11
      Font.Name = 'MS Sans Serif'
      Font.Style = []
      ParentFont = False
    end
    object P1: TLabel
      Left = 128
      Top = 40
      Width = 6
      Height = 13
      Caption = '7'
      Font.Charset = DEFAULT_CHARSET
      Font.Color = clWindowText
      Font.Height = -11
      Font.Name = 'MS Sans Serif'
      Font.Style = []
      ParentFont = False
    end
    object P2: TLabel
      Left = 128
      Top = 83
      Width = 12
      Height = 13
      Caption = '20'
      Font.Charset = DEFAULT_CHARSET
      Font.Color = clWindowText
      Font.Height = -11
      Font.Name = 'MS Sans Serif'
      Font.Style = []
      ParentFont = False
    end
    object P3: TLabel
      Left = 128
      Top = 137
      Width = 18
      Height = 13
      Caption = '100'
      Font.Charset = DEFAULT_CHARSET
      Font.Color = clWindowText
      Font.Height = -11
      Font.Name = 'MS Sans Serif'
      Font.Style = []
      ParentFont = False
    end
    object EA: TTrackBar
      Left = 8
      Top = 35
      Width = 113
      Height = 21
      Max = 100
      ParentShowHint = False
      PageSize = 1
      Position = 7
      PositionToolTip = ptTop
      ShowHint = True
      TabOrder = 0
      TickMarks = tmTopLeft
      TickStyle = tsNone
      OnChange = EAChange
    end
    object ES: TTrackBar
      Left = 9
      Top = 132
      Width = 113
      Height = 21
      Max = 100
      ParentShowHint = False
      PageSize = 1
      Position = 100
      PositionToolTip = ptTop
      ShowHint = True
      TabOrder = 1
      TickMarks = tmTopLeft
      TickStyle = tsNone
      OnChange = ESChange
    end
    object ED: TTrackBar
      Left = 8
      Top = 79
      Width = 113
      Height = 21
      Max = 100
      ParentShowHint = False
      PageSize = 1
      Position = 20
      PositionToolTip = ptTop
      ShowHint = True
      TabOrder = 2
      TickMarks = tmTopLeft
      TickStyle = tsNone
      OnChange = EDChange
    end
  end
  object GroupBox2: TGroupBox
    Left = 168
    Top = 31
    Width = 153
    Height = 161
    Caption = 'Light position'
    Font.Charset = DEFAULT_CHARSET
    Font.Color = clWindowText
    Font.Height = -11
    Font.Name = 'MS Sans Serif'
    Font.Style = [fsBold]
    ParentFont = False
    TabOrder = 1
    object Label1: TLabel
      Left = 64
      Top = 21
      Width = 7
      Height = 13
      Caption = 'X'
      Font.Charset = DEFAULT_CHARSET
      Font.Color = clWindowText
      Font.Height = -11
      Font.Name = 'MS Sans Serif'
      Font.Style = []
      ParentFont = False
    end
    object Label2: TLabel
      Left = 64
      Top = 65
      Width = 7
      Height = 13
      Caption = 'Y'
      Font.Charset = DEFAULT_CHARSET
      Font.Color = clWindowText
      Font.Height = -11
      Font.Name = 'MS Sans Serif'
      Font.Style = []
      ParentFont = False
    end
    object Label3: TLabel
      Left = 64
      Top = 113
      Width = 7
      Height = 13
      Caption = 'Z'
      Font.Charset = DEFAULT_CHARSET
      Font.Color = clWindowText
      Font.Height = -11
      Font.Name = 'MS Sans Serif'
      Font.Style = []
      ParentFont = False
    end
    object P4: TLabel
      Left = 119
      Top = 40
      Width = 6
      Height = 13
      Caption = '0'
      Font.Charset = DEFAULT_CHARSET
      Font.Color = clWindowText
      Font.Height = -11
      Font.Name = 'MS Sans Serif'
      Font.Style = []
      ParentFont = False
    end
    object P5: TLabel
      Left = 119
      Top = 83
      Width = 6
      Height = 13
      Caption = '0'
      Font.Charset = DEFAULT_CHARSET
      Font.Color = clWindowText
      Font.Height = -11
      Font.Name = 'MS Sans Serif'
      Font.Style = []
      ParentFont = False
    end
    object P6: TLabel
      Left = 119
      Top = 132
      Width = 24
      Height = 13
      Caption = '2500'
      Font.Charset = DEFAULT_CHARSET
      Font.Color = clWindowText
      Font.Height = -11
      Font.Name = 'MS Sans Serif'
      Font.Style = []
      ParentFont = False
    end
    object X: TTrackBar
      Left = 1
      Top = 35
      Width = 114
      Height = 21
      Max = 5000
      Min = -5000
      ParentShowHint = False
      PageSize = 1
      PositionToolTip = ptTop
      ShowHint = True
      TabOrder = 0
      TickMarks = tmTopLeft
      TickStyle = tsNone
      OnChange = XChange
    end
    object Y: TTrackBar
      Left = 1
      Top = 79
      Width = 114
      Height = 21
      Max = 5000
      Min = -5000
      ParentShowHint = False
      PageSize = 1
      PositionToolTip = ptTop
      ShowHint = True
      TabOrder = 1
      TickMarks = tmTopLeft
      TickStyle = tsNone
      OnChange = YChange
    end
    object Z: TTrackBar
      Left = 1
      Top = 127
      Width = 114
      Height = 21
      Max = 5000
      Min = -5000
      ParentShowHint = False
      PageSize = 1
      Position = 2500
      PositionToolTip = ptTop
      ShowHint = True
      TabOrder = 2
      TickMarks = tmTopLeft
      TickStyle = tsNone
      OnChange = ZChange
    end
  end
  object GroupBox3: TGroupBox
    Left = 8
    Top = 210
    Width = 313
    Height = 139
    Caption = 'Material'
    Font.Charset = DEFAULT_CHARSET
    Font.Color = clWindowText
    Font.Height = -11
    Font.Name = 'MS Sans Serif'
    Font.Style = [fsBold]
    ParentFont = False
    TabOrder = 2
    object Label7: TLabel
      Left = 204
      Top = 29
      Width = 27
      Height = 13
      Caption = 'Shine'
      Font.Charset = DEFAULT_CHARSET
      Font.Color = clWindowText
      Font.Height = -11
      Font.Name = 'MS Sans Serif'
      Font.Style = []
      ParentFont = False
    end
    object Label8: TLabel
      Left = 203
      Top = 78
      Width = 41
      Height = 13
      Caption = 'Emission'
      Font.Charset = DEFAULT_CHARSET
      Font.Color = clWindowText
      Font.Height = -11
      Font.Name = 'MS Sans Serif'
      Font.Style = []
      ParentFont = False
    end
    object Label9: TLabel
      Left = 49
      Top = 19
      Width = 38
      Height = 13
      Caption = 'Ambient'
      Font.Charset = DEFAULT_CHARSET
      Font.Color = clWindowText
      Font.Height = -11
      Font.Name = 'MS Sans Serif'
      Font.Style = []
      ParentFont = False
    end
    object Label10: TLabel
      Left = 49
      Top = 59
      Width = 33
      Height = 13
      Caption = 'Diffuse'
      Font.Charset = DEFAULT_CHARSET
      Font.Color = clWindowText
      Font.Height = -11
      Font.Name = 'MS Sans Serif'
      Font.Style = []
      ParentFont = False
    end
    object Label11: TLabel
      Left = 49
      Top = 99
      Width = 42
      Height = 13
      Caption = 'Specular'
      Font.Charset = DEFAULT_CHARSET
      Font.Color = clWindowText
      Font.Height = -11
      Font.Name = 'MS Sans Serif'
      Font.Style = []
      ParentFont = False
    end
    object P7: TLabel
      Left = 129
      Top = 35
      Width = 6
      Height = 13
      Caption = '0'
      Font.Charset = DEFAULT_CHARSET
      Font.Color = clWindowText
      Font.Height = -11
      Font.Name = 'MS Sans Serif'
      Font.Style = []
      ParentFont = False
    end
    object P8: TLabel
      Left = 129
      Top = 75
      Width = 6
      Height = 13
      Caption = '0'
      Font.Charset = DEFAULT_CHARSET
      Font.Color = clWindowText
      Font.Height = -11
      Font.Name = 'MS Sans Serif'
      Font.Style = []
      ParentFont = False
    end
    object P9: TLabel
      Left = 129
      Top = 115
      Width = 12
      Height = 13
      Caption = '30'
      Font.Charset = DEFAULT_CHARSET
      Font.Color = clWindowText
      Font.Height = -11
      Font.Name = 'MS Sans Serif'
      Font.Style = []
      ParentFont = False
    end
    object P10: TLabel
      Left = 288
      Top = 48
      Width = 12
      Height = 13
      Caption = '50'
      Font.Charset = DEFAULT_CHARSET
      Font.Color = clWindowText
      Font.Height = -11
      Font.Name = 'MS Sans Serif'
      Font.Style = []
      ParentFont = False
    end
    object P11: TLabel
      Left = 288
      Top = 96
      Width = 6
      Height = 13
      Caption = '0'
      Font.Charset = DEFAULT_CHARSET
      Font.Color = clWindowText
      Font.Height = -11
      Font.Name = 'MS Sans Serif'
      Font.Style = []
      ParentFont = False
    end
    object MD: TTrackBar
      Left = 9
      Top = 71
      Width = 113
      Height = 21
      Max = 100
      ParentShowHint = False
      PageSize = 1
      PositionToolTip = ptTop
      ShowHint = True
      TabOrder = 0
      TickMarks = tmTopLeft
      TickStyle = tsNone
      OnChange = MDChange
    end
    object MS: TTrackBar
      Left = 9
      Top = 111
      Width = 113
      Height = 21
      Max = 100
      ParentShowHint = False
      PageSize = 1
      Position = 30
      PositionToolTip = ptTop
      ShowHint = True
      TabOrder = 1
      TickMarks = tmTopLeft
      TickStyle = tsNone
      OnChange = MSChange
    end
    object ME: TTrackBar
      Left = 168
      Top = 92
      Width = 113
      Height = 21
      Max = 100
      ParentShowHint = False
      PageSize = 1
      PositionToolTip = ptTop
      ShowHint = True
      TabOrder = 2
      TickMarks = tmTopLeft
      TickStyle = tsNone
      OnChange = MEChange
    end
    object MB: TTrackBar
      Left = 168
      Top = 44
      Width = 113
      Height = 21
      Max = 100
      ParentShowHint = False
      PageSize = 1
      Position = 50
      PositionToolTip = ptTop
      ShowHint = True
      TabOrder = 3
      TickMarks = tmTopLeft
      TickStyle = tsNone
      OnChange = MBChange
    end
    object MA: TTrackBar
      Left = 9
      Top = 31
      Width = 113
      Height = 21
      Max = 100
      ParentShowHint = False
      PageSize = 1
      PositionToolTip = ptTop
      ShowHint = True
      TabOrder = 4
      TickMarks = tmTopLeft
      TickStyle = tsNone
      OnChange = MAChange
    end
  end
  object CheckBox1: TCheckBox
    Left = 11
    Top = 8
    Width = 177
    Height = 17
    Caption = 'Visualize the light source'
    TabOrder = 3
    OnClick = CheckBox1Click
  end
  object GroupBox4: TGroupBox
    Left = 56
    Top = 362
    Width = 219
    Height = 97
    Caption = 'Activation of lights'
    Font.Charset = DEFAULT_CHARSET
    Font.Color = clWindowText
    Font.Height = -11
    Font.Name = 'MS Sans Serif'
    Font.Style = [fsBold]
    ParentFont = False
    TabOrder = 4
    object CheckBox2: TCheckBox
      Left = 28
      Top = 24
      Width = 97
      Height = 17
      Caption = 'Light 1 (+X)'
      Checked = True
      Font.Charset = DEFAULT_CHARSET
      Font.Color = clWindowText
      Font.Height = -11
      Font.Name = 'MS Sans Serif'
      Font.Style = []
      ParentFont = False
      State = cbChecked
      TabOrder = 0
      OnClick = CheckBox1Click
    end
    object CheckBox6: TCheckBox
      Left = 135
      Top = 48
      Width = 97
      Height = 17
      Caption = 'Light 4  (+Y)'
      Checked = True
      Font.Charset = DEFAULT_CHARSET
      Font.Color = clWindowText
      Font.Height = -11
      Font.Name = 'MS Sans Serif'
      Font.Style = []
      ParentFont = False
      State = cbChecked
      TabOrder = 1
      OnClick = CheckBox1Click
    end
    object CheckBox5: TCheckBox
      Left = 28
      Top = 71
      Width = 97
      Height = 17
      Caption = 'Light 5 (-Z)'
      Font.Charset = DEFAULT_CHARSET
      Font.Color = clWindowText
      Font.Height = -11
      Font.Name = 'MS Sans Serif'
      Font.Style = []
      ParentFont = False
      TabOrder = 2
      OnClick = CheckBox1Click
    end
    object CheckBox3: TCheckBox
      Left = 135
      Top = 25
      Width = 97
      Height = 17
      Caption = 'Light 2 (-X)'
      Font.Charset = DEFAULT_CHARSET
      Font.Color = clWindowText
      Font.Height = -11
      Font.Name = 'MS Sans Serif'
      Font.Style = []
      ParentFont = False
      TabOrder = 3
      OnClick = CheckBox1Click
    end
    object CheckBox4: TCheckBox
      Left = 28
      Top = 48
      Width = 97
      Height = 17
      Caption = 'Light 3 (-Y)'
      Font.Charset = DEFAULT_CHARSET
      Font.Color = clWindowText
      Font.Height = -11
      Font.Name = 'MS Sans Serif'
      Font.Style = []
      ParentFont = False
      TabOrder = 4
      OnClick = CheckBox1Click
    end
    object CheckBox7: TCheckBox
      Left = 135
      Top = 72
      Width = 79
      Height = 17
      Caption = 'Light 6 (+Z)'
      Checked = True
      Font.Charset = DEFAULT_CHARSET
      Font.Color = clWindowText
      Font.Height = -11
      Font.Name = 'MS Sans Serif'
      Font.Style = []
      ParentFont = False
      State = cbChecked
      TabOrder = 5
      OnClick = CheckBox1Click
    end
  end
  object Button2: TButton
    Left = 533
    Top = 139
    Width = 111
    Height = 25
    Caption = 'Centrer la lumi'#232're'
    TabOrder = 5
    OnClick = Button2Click
  end
  object GroupBox5: TGroupBox
    Left = 533
    Top = 186
    Width = 234
    Height = 78
    Caption = 'Mat'#233'riau des surfaces'
    Font.Charset = DEFAULT_CHARSET
    Font.Color = clWindowText
    Font.Height = -11
    Font.Name = 'MS Sans Serif'
    Font.Style = [fsBold]
    ParentFont = False
    TabOrder = 6
    object Label13: TLabel
      Left = 51
      Top = 24
      Width = 41
      Height = 13
      Caption = 'Mat'#233'riau'
      Font.Charset = DEFAULT_CHARSET
      Font.Color = clWindowText
      Font.Height = -11
      Font.Name = 'MS Sans Serif'
      Font.Style = []
      ParentFont = False
    end
    object ComboBox1: TComboBox
      Left = 103
      Top = 20
      Width = 109
      Height = 21
      Style = csDropDownList
      Font.Charset = DEFAULT_CHARSET
      Font.Color = clWindowText
      Font.Height = -11
      Font.Name = 'MS Sans Serif'
      Font.Style = []
      ItemIndex = 0
      ParentFont = False
      TabOrder = 0
      Text = 'Plastique noir'
      Items.Strings = (
        'Plastique noir'
        'Cuivre'
        'Bronze'
        'Chrome'
        'Cuivre rouge'
        'Or'
        #201'tain'
        'Argent'
        'Argent brillant')
    end
    object Button3: TButton
      Left = 58
      Top = 48
      Width = 119
      Height = 25
      Caption = 'Choisir le mat'#233'riau'
      TabOrder = 1
      OnClick = Button3Click
    end
  end
  object Edit1: TEdit
    Left = 616
    Top = 318
    Width = 59
    Height = 21
    Font.Charset = DEFAULT_CHARSET
    Font.Color = clWindowText
    Font.Height = -11
    Font.Name = 'MS Sans Serif'
    Font.Style = []
    NumbersOnly = True
    ParentFont = False
    TabOrder = 7
    Text = '5000'
  end
  object Button1: TButton
    Left = 544
    Top = 348
    Width = 119
    Height = 25
    Caption = 'Valider la distance'
    TabOrder = 8
    OnClick = Button1Click
  end
end
