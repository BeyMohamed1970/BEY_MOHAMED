object Adaptive_Triangulation: TAdaptive_Triangulation
  Left = 754
  Top = 0
  BorderIcons = [biSystemMenu]
  BorderStyle = bsSingle
  Caption = 'Adaptive Triangulation of Point Clouds'
  ClientHeight = 856
  ClientWidth = 449
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
  Position = poDesigned
  Scaled = False
  OnClose = FormClose
  OnShow = FormShow
  PixelsPerInch = 96
  TextHeight = 13
  object Label7: TLabel
    Left = 804
    Top = 990
    Width = 58
    Height = 13
    Caption = 'Poucentage'
    Visible = False
  end
  object Label13: TLabel
    Left = 895
    Top = 266
    Width = 112
    Height = 13
    Caption = 'densit'#233'_min pts/triangle'
    Visible = False
  end
  object Label20: TLabel
    Left = 1070
    Top = 902
    Width = 122
    Height = 13
    Caption = 'pourcentage de r'#233'duction'
    Visible = False
  end
  object Label17: TLabel
    Left = 1179
    Top = 645
    Width = 70
    Height = 13
    Caption = 'It'#233'ration d'#39'arr'#234't'
    Visible = False
  end
  object Label24: TLabel
    Left = 1178
    Top = 684
    Width = 66
    Height = 13
    Caption = 'Indice triangle'
    Visible = False
  end
  object Label18: TLabel
    Left = 1125
    Top = 729
    Width = 65
    Height = 13
    Caption = 'Nbre triangles'
    Visible = False
  end
  object Label12: TLabel
    Left = 1077
    Top = 538
    Width = 58
    Height = 13
    Caption = 'Poucentage'
    Visible = False
  end
  object Label36: TLabel
    Left = 875
    Top = 100
    Width = 47
    Height = 13
    Caption = 'Ecart max'
    Font.Charset = DEFAULT_CHARSET
    Font.Color = clWindowText
    Font.Height = -11
    Font.Name = 'MS Sans Serif'
    Font.Style = []
    ParentFont = False
  end
  object GroupBox11: TGroupBox
    Left = 1046
    Top = 383
    Width = 258
    Height = 41
    Caption = 'Modes de filtration/densit'#233
    Font.Charset = DEFAULT_CHARSET
    Font.Color = clWindowText
    Font.Height = -11
    Font.Name = 'MS Sans Serif'
    Font.Style = [fsBold]
    ParentFont = False
    TabOrder = 32
    Visible = False
    object RadioButton8: TRadioButton
      Left = 6
      Top = 18
      Width = 45
      Height = 17
      Caption = 'Seuil'
      Font.Charset = DEFAULT_CHARSET
      Font.Color = clWindowText
      Font.Height = -11
      Font.Name = 'MS Sans Serif'
      Font.Style = []
      ParentFont = False
      TabOrder = 0
    end
    object RadioButton9: TRadioButton
      Left = 68
      Top = 17
      Width = 134
      Height = 17
      Caption = 'deux points'
      Font.Charset = DEFAULT_CHARSET
      Font.Color = clWindowText
      Font.Height = -11
      Font.Name = 'MS Sans Serif'
      Font.Style = []
      ParentFont = False
      TabOrder = 1
    end
    object RadioButton10: TRadioButton
      Left = 149
      Top = 17
      Width = 106
      Height = 17
      Caption = 'un seul point nulle'
      Checked = True
      Font.Charset = DEFAULT_CHARSET
      Font.Color = clWindowText
      Font.Height = -11
      Font.Name = 'MS Sans Serif'
      Font.Style = []
      ParentFont = False
      TabOrder = 2
      TabStop = True
    end
  end
  object GroupBox1: TGroupBox
    Left = 5
    Top = 2
    Width = 440
    Height = 115
    Caption = 'Cell Creation'
    Font.Charset = DEFAULT_CHARSET
    Font.Color = clWindowText
    Font.Height = -13
    Font.Name = 'MS Sans Serif'
    Font.Style = [fsBold]
    ParentFont = False
    TabOrder = 0
    object Label2: TLabel
      Left = 10
      Top = 27
      Width = 133
      Height = 13
      Caption = 'Number of cells along X-axis'
      Font.Charset = DEFAULT_CHARSET
      Font.Color = clWindowText
      Font.Height = -11
      Font.Name = 'MS Sans Serif'
      Font.Style = []
      ParentFont = False
    end
    object Label3: TLabel
      Left = 228
      Top = 27
      Width = 133
      Height = 13
      Caption = 'Number of cells along Y-axis'
      Font.Charset = DEFAULT_CHARSET
      Font.Color = clWindowText
      Font.Height = -11
      Font.Name = 'MS Sans Serif'
      Font.Style = []
      ParentFont = False
    end
    object Edit2: TEdit
      Left = 367
      Top = 21
      Width = 63
      Height = 24
      Font.Charset = DEFAULT_CHARSET
      Font.Color = clWindowText
      Font.Height = -13
      Font.Name = 'MS Sans Serif'
      Font.Style = [fsBold]
      ParentFont = False
      TabOrder = 0
      Text = '100'
      OnKeyPress = Edit1KeyPress
    end
    object Edit1: TEdit
      Left = 149
      Top = 21
      Width = 63
      Height = 24
      Font.Charset = DEFAULT_CHARSET
      Font.Color = clWindowText
      Font.Height = -13
      Font.Name = 'MS Sans Serif'
      Font.Style = [fsBold]
      ParentFont = False
      TabOrder = 1
      Text = '200'
      OnKeyPress = Edit1KeyPress
    end
    object Button1: TButton
      Left = 124
      Top = 46
      Width = 192
      Height = 25
      Caption = '2. Create Cells'
      Font.Charset = DEFAULT_CHARSET
      Font.Color = clWindowText
      Font.Height = -13
      Font.Name = 'MS Sans Serif'
      Font.Style = [fsBold]
      ParentFont = False
      TabOrder = 2
      OnClick = Button1Click
    end
    object GroupBox2: TGroupBox
      Left = 65
      Top = 71
      Width = 309
      Height = 39
      Caption = 'Visualization'
      Font.Charset = DEFAULT_CHARSET
      Font.Color = clWindowText
      Font.Height = -13
      Font.Name = 'MS Sans Serif'
      Font.Style = [fsBold]
      ParentFont = False
      TabOrder = 3
      Visible = False
      object CheckBox1: TCheckBox
        Left = 30
        Top = 19
        Width = 73
        Height = 15
        Caption = 'Cell limits'
        Font.Charset = DEFAULT_CHARSET
        Font.Color = clWindowText
        Font.Height = -11
        Font.Name = 'MS Sans Serif'
        Font.Style = []
        ParentFont = False
        TabOrder = 0
        OnClick = CheckBox1Click
      end
      object CheckBox2: TCheckBox
        Left = 185
        Top = 18
        Width = 110
        Height = 17
        Caption = 'Cell points'
        Font.Charset = DEFAULT_CHARSET
        Font.Color = clWindowText
        Font.Height = -11
        Font.Name = 'MS Sans Serif'
        Font.Style = []
        ParentFont = False
        TabOrder = 1
        OnClick = CheckBox1Click
      end
      object ComboBox1: TComboBox
        Left = 97
        Top = 16
        Width = 43
        Height = 21
        Style = csDropDownList
        Font.Charset = DEFAULT_CHARSET
        Font.Color = clWindowText
        Font.Height = -11
        Font.Name = 'MS Sans Serif'
        Font.Style = []
        ItemIndex = 0
        ParentFont = False
        TabOrder = 2
        Text = '1'
        OnClick = CheckBox1Click
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
        Left = 253
        Top = 16
        Width = 43
        Height = 21
        Style = csDropDownList
        Font.Charset = DEFAULT_CHARSET
        Font.Color = clWindowText
        Font.Height = -11
        Font.Name = 'MS Sans Serif'
        Font.Style = []
        ItemIndex = 0
        ParentFont = False
        TabOrder = 3
        Text = '1'
        OnClick = CheckBox1Click
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
      object CheckBox54: TCheckBox
        Left = 12
        Top = 64
        Width = 174
        Height = 15
        Caption = 'Limites de cellules des sommets'
        Font.Charset = DEFAULT_CHARSET
        Font.Color = clWindowText
        Font.Height = -11
        Font.Name = 'MS Sans Serif'
        Font.Style = []
        ParentFont = False
        TabOrder = 4
        OnClick = CheckBox1Click
      end
      object ComboBox43: TComboBox
        Left = 195
        Top = 63
        Width = 43
        Height = 21
        Style = csDropDownList
        Font.Charset = DEFAULT_CHARSET
        Font.Color = clWindowText
        Font.Height = -11
        Font.Name = 'MS Sans Serif'
        Font.Style = []
        ItemIndex = 0
        ParentFont = False
        TabOrder = 5
        Text = '1'
        OnClick = CheckBox1Click
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
    end
  end
  object GroupBox3: TGroupBox
    Left = 778
    Top = 315
    Width = 262
    Height = 361
    Caption = 'Triangulation initiale'
    Font.Charset = DEFAULT_CHARSET
    Font.Color = clWindowText
    Font.Height = -11
    Font.Name = 'MS Sans Serif'
    Font.Style = [fsBold]
    ParentFont = False
    TabOrder = 1
    Visible = False
    object Label1: TLabel
      Left = 7
      Top = 20
      Width = 133
      Height = 13
      Caption = 'Nbre de segments suivant X'
      Font.Charset = DEFAULT_CHARSET
      Font.Color = clWindowText
      Font.Height = -11
      Font.Name = 'MS Sans Serif'
      Font.Style = []
      ParentFont = False
    end
    object Label4: TLabel
      Left = 7
      Top = 43
      Width = 133
      Height = 13
      Caption = 'Nbre de segments suivant Y'
      Font.Charset = DEFAULT_CHARSET
      Font.Color = clWindowText
      Font.Height = -11
      Font.Name = 'MS Sans Serif'
      Font.Style = []
      ParentFont = False
    end
    object Button2: TButton
      Left = -1
      Top = 63
      Width = 259
      Height = 25
      Caption = 'G'#233'n'#233'rer la premi'#232're triangulation'
      Font.Charset = DEFAULT_CHARSET
      Font.Color = clWindowText
      Font.Height = -13
      Font.Name = 'MS Sans Serif'
      Font.Style = [fsBold]
      ParentFont = False
      TabOrder = 0
      Visible = False
      OnClick = Button2Click
    end
    object Edit3: TEdit
      Left = 144
      Top = 14
      Width = 62
      Height = 24
      Font.Charset = DEFAULT_CHARSET
      Font.Color = clWindowText
      Font.Height = -13
      Font.Name = 'MS Sans Serif'
      Font.Style = [fsBold]
      ParentFont = False
      TabOrder = 1
      OnKeyPress = Edit3KeyPress
    end
    object Edit4: TEdit
      Left = 144
      Top = 37
      Width = 62
      Height = 24
      Font.Charset = DEFAULT_CHARSET
      Font.Color = clWindowText
      Font.Height = -13
      Font.Name = 'MS Sans Serif'
      Font.Style = [fsBold]
      ParentFont = False
      TabOrder = 2
      OnKeyPress = Edit3KeyPress
    end
    object CheckBox3: TCheckBox
      Left = 7
      Top = 90
      Width = 179
      Height = 17
      Caption = 'dessiner sommets des triangles '
      Font.Charset = DEFAULT_CHARSET
      Font.Color = clWindowText
      Font.Height = -11
      Font.Name = 'MS Sans Serif'
      Font.Style = []
      ParentFont = False
      TabOrder = 3
      OnClick = CheckBox1Click
    end
    object ComboBox2: TComboBox
      Left = 193
      Top = 88
      Width = 43
      Height = 21
      Style = csDropDownList
      Font.Charset = DEFAULT_CHARSET
      Font.Color = clWindowText
      Font.Height = -11
      Font.Name = 'MS Sans Serif'
      Font.Style = []
      ItemIndex = 0
      ParentFont = False
      TabOrder = 4
      Text = '1'
      OnClick = CheckBox1Click
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
    object CheckBox5: TCheckBox
      Left = 7
      Top = 110
      Width = 183
      Height = 18
      Caption = 'dessiner limite triangle'
      Font.Charset = DEFAULT_CHARSET
      Font.Color = clWindowText
      Font.Height = -11
      Font.Name = 'MS Sans Serif'
      Font.Style = []
      ParentFont = False
      TabOrder = 5
      OnClick = CheckBox1Click
    end
    object ComboBox5: TComboBox
      Left = 193
      Top = 109
      Width = 43
      Height = 21
      Style = csDropDownList
      Font.Charset = DEFAULT_CHARSET
      Font.Color = clWindowText
      Font.Height = -11
      Font.Name = 'MS Sans Serif'
      Font.Style = []
      ItemIndex = 0
      ParentFont = False
      TabOrder = 6
      Text = '1'
      OnClick = CheckBox1Click
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
    object CheckBox7: TCheckBox
      Left = 7
      Top = 131
      Width = 144
      Height = 18
      Caption = 'dessiner nuage de points'
      Font.Charset = DEFAULT_CHARSET
      Font.Color = clWindowText
      Font.Height = -11
      Font.Name = 'MS Sans Serif'
      Font.Style = []
      ParentFont = False
      TabOrder = 7
      OnClick = CheckBox1Click
    end
    object ComboBox7: TComboBox
      Left = 193
      Top = 130
      Width = 43
      Height = 21
      Style = csDropDownList
      Font.Charset = DEFAULT_CHARSET
      Font.Color = clWindowText
      Font.Height = -11
      Font.Name = 'MS Sans Serif'
      Font.Style = []
      ItemIndex = 0
      ParentFont = False
      TabOrder = 8
      Text = '1'
      OnClick = CheckBox1Click
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
    object GroupBox7: TGroupBox
      Left = 5
      Top = 151
      Width = 251
      Height = 205
      Caption = 'Dessin des triangles et points des triangles'
      TabOrder = 9
      object CheckBox6: TCheckBox
        Left = 6
        Top = 42
        Width = 187
        Height = 17
        Caption = 'Points des triangle'
        Font.Charset = DEFAULT_CHARSET
        Font.Color = clWindowText
        Font.Height = -11
        Font.Name = 'MS Sans Serif'
        Font.Style = []
        ParentFont = False
        TabOrder = 0
        OnClick = CheckBox1Click
      end
      object ComboBox6: TComboBox
        Left = 191
        Top = 40
        Width = 43
        Height = 21
        Style = csDropDownList
        Font.Charset = DEFAULT_CHARSET
        Font.Color = clWindowText
        Font.Height = -11
        Font.Name = 'MS Sans Serif'
        Font.Style = []
        ItemIndex = 0
        ParentFont = False
        TabOrder = 1
        Text = '1'
        OnClick = CheckBox1Click
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
      object GroupBox4: TGroupBox
        Left = 103
        Top = 171
        Width = 119
        Height = 30
        Font.Charset = DEFAULT_CHARSET
        Font.Color = clWindowText
        Font.Height = -11
        Font.Name = 'MS Sans Serif'
        Font.Style = []
        ParentFont = False
        TabOrder = 2
        object RadioButton1: TRadioButton
          Left = 11
          Top = 10
          Width = 50
          Height = 17
          Caption = 'Filaire'
          Checked = True
          TabOrder = 0
          TabStop = True
          OnClick = CheckBox1Click
        end
        object RadioButton2: TRadioButton
          Left = 59
          Top = 10
          Width = 58
          Height = 17
          Caption = 'Rendu'
          TabOrder = 1
          OnClick = CheckBox1Click
        end
      end
      object CheckBox9: TCheckBox
        Left = 6
        Top = 86
        Width = 188
        Height = 17
        Caption = 'Points des triangle non filtr'#233'es'
        Font.Charset = DEFAULT_CHARSET
        Font.Color = clWindowText
        Font.Height = -11
        Font.Name = 'MS Sans Serif'
        Font.Style = []
        ParentFont = False
        TabOrder = 3
        OnClick = CheckBox1Click
      end
      object ComboBox9: TComboBox
        Left = 191
        Top = 84
        Width = 43
        Height = 21
        Style = csDropDownList
        Font.Charset = DEFAULT_CHARSET
        Font.Color = clWindowText
        Font.Height = -11
        Font.Name = 'MS Sans Serif'
        Font.Style = []
        ItemIndex = 0
        ParentFont = False
        TabOrder = 4
        Text = '1'
        OnClick = CheckBox1Click
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
        Top = 20
        Width = 184
        Height = 17
        Caption = 'Triangles'
        Font.Charset = DEFAULT_CHARSET
        Font.Color = clWindowText
        Font.Height = -11
        Font.Name = 'MS Sans Serif'
        Font.Style = []
        ParentFont = False
        TabOrder = 5
        OnClick = CheckBox1Click
      end
      object ComboBox4: TComboBox
        Left = 191
        Top = 18
        Width = 43
        Height = 21
        Style = csDropDownList
        Font.Charset = DEFAULT_CHARSET
        Font.Color = clWindowText
        Font.Height = -11
        Font.Name = 'MS Sans Serif'
        Font.Style = []
        ItemIndex = 0
        ParentFont = False
        TabOrder = 6
        Text = '1'
        OnClick = CheckBox1Click
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
      object CheckBox10: TCheckBox
        Left = 6
        Top = 130
        Width = 187
        Height = 17
        Caption = 'Points des triangles filtr'#233's'
        Font.Charset = DEFAULT_CHARSET
        Font.Color = clWindowText
        Font.Height = -11
        Font.Name = 'MS Sans Serif'
        Font.Style = []
        ParentFont = False
        TabOrder = 7
        OnClick = CheckBox1Click
      end
      object ComboBox10: TComboBox
        Left = 191
        Top = 128
        Width = 43
        Height = 21
        Style = csDropDownList
        Font.Charset = DEFAULT_CHARSET
        Font.Color = clWindowText
        Font.Height = -11
        Font.Name = 'MS Sans Serif'
        Font.Style = []
        ItemIndex = 0
        ParentFont = False
        TabOrder = 8
        Text = '1'
        OnClick = CheckBox1Click
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
      object CheckBox11: TCheckBox
        Left = 7
        Top = 108
        Width = 170
        Height = 17
        Caption = 'Triangles filtr'#233's en 3D'
        Font.Charset = DEFAULT_CHARSET
        Font.Color = clWindowText
        Font.Height = -11
        Font.Name = 'MS Sans Serif'
        Font.Style = []
        ParentFont = False
        TabOrder = 9
        OnClick = CheckBox1Click
      end
      object ComboBox11: TComboBox
        Left = 191
        Top = 106
        Width = 43
        Height = 21
        Style = csDropDownList
        Font.Charset = DEFAULT_CHARSET
        Font.Color = clWindowText
        Font.Height = -11
        Font.Name = 'MS Sans Serif'
        Font.Style = []
        ItemIndex = 0
        ParentFont = False
        TabOrder = 10
        Text = '1'
        OnClick = CheckBox1Click
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
      object CheckBox8: TCheckBox
        Left = 6
        Top = 64
        Width = 192
        Height = 17
        Caption = 'Triangles non filtr'#233'es en 3D '
        Font.Charset = DEFAULT_CHARSET
        Font.Color = clWindowText
        Font.Height = -11
        Font.Name = 'MS Sans Serif'
        Font.Style = []
        ParentFont = False
        TabOrder = 11
        OnClick = CheckBox1Click
      end
      object ComboBox8: TComboBox
        Left = 191
        Top = 62
        Width = 43
        Height = 21
        Style = csDropDownList
        Font.Charset = DEFAULT_CHARSET
        Font.Color = clWindowText
        Font.Height = -11
        Font.Name = 'MS Sans Serif'
        Font.Style = []
        ItemIndex = 0
        ParentFont = False
        TabOrder = 12
        Text = '1'
        OnClick = CheckBox1Click
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
      object CheckBox12: TCheckBox
        Left = 6
        Top = 152
        Width = 144
        Height = 17
        Caption = 'Voisin d'#39'un triangle'
        Font.Charset = DEFAULT_CHARSET
        Font.Color = clWindowText
        Font.Height = -11
        Font.Name = 'MS Sans Serif'
        Font.Style = []
        ParentFont = False
        TabOrder = 13
        OnClick = CheckBox12Click
      end
      object ComboBox12: TComboBox
        Left = 191
        Top = 150
        Width = 43
        Height = 21
        Style = csDropDownList
        Font.Charset = DEFAULT_CHARSET
        Font.Color = clWindowText
        Font.Height = -11
        Font.Name = 'MS Sans Serif'
        Font.Style = []
        ParentFont = False
        TabOrder = 14
        OnClick = ComboBox12Click
        Items.Strings = (
          '')
      end
      object CheckBox13: TCheckBox
        Left = 6
        Top = 174
        Width = 60
        Height = 17
        Caption = 'brut min'
        Font.Charset = DEFAULT_CHARSET
        Font.Color = clWindowText
        Font.Height = -11
        Font.Name = 'MS Sans Serif'
        Font.Style = []
        ParentFont = False
        TabOrder = 15
        OnClick = CheckBox1Click
      end
    end
  end
  object GroupBox5: TGroupBox
    Left = 778
    Top = 679
    Width = 264
    Height = 148
    Caption = 'Ecarts de l'#39'approximation'
    Font.Charset = DEFAULT_CHARSET
    Font.Color = clWindowText
    Font.Height = -11
    Font.Name = 'MS Sans Serif'
    Font.Style = [fsBold]
    ParentFont = False
    TabOrder = 2
    Visible = False
    object Panel1: TPanel
      Left = 0
      Top = 67
      Width = 260
      Height = 77
      Caption = ' '
      TabOrder = 0
      object CheckBox45: TCheckBox
        Left = 108
        Top = 58
        Width = 149
        Height = 17
        Caption = 'Afficher triangulation calcul'
        Font.Charset = DEFAULT_CHARSET
        Font.Color = clWindowText
        Font.Height = -11
        Font.Name = 'MS Sans Serif'
        Font.Style = []
        ParentFont = False
        TabOrder = 0
        Visible = False
        OnClick = CheckBox1Click
      end
    end
    object Button3: TButton
      Left = 7
      Top = 116
      Width = 95
      Height = 25
      Caption = 'Adaptation'
      Font.Charset = DEFAULT_CHARSET
      Font.Color = clWindowText
      Font.Height = -13
      Font.Name = 'MS Sans Serif'
      Font.Style = [fsBold]
      ParentFont = False
      TabOrder = 1
      Visible = False
      OnClick = Button3Click
    end
  end
  object GroupBox6: TGroupBox
    Left = 778
    Top = 831
    Width = 262
    Height = 59
    Caption = 'Choix de la coordonn'#233'e Z des sommets '
    Font.Charset = DEFAULT_CHARSET
    Font.Color = clWindowText
    Font.Height = -11
    Font.Name = 'MS Sans Serif'
    Font.Style = [fsBold]
    ParentFont = False
    TabOrder = 3
    Visible = False
    object Panel2: TPanel
      Left = 8
      Top = 22
      Width = 249
      Height = 35
      Color = clGradientInactiveCaption
      TabOrder = 1
      object RadioButton3: TRadioButton
        Left = 3
        Top = 4
        Width = 75
        Height = 11
        Caption = 'z_pt_mini'
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
      object RadioButton4: TRadioButton
        Left = 84
        Top = 3
        Width = 74
        Height = 11
        Caption = 'z_pt_moy'
        Font.Charset = DEFAULT_CHARSET
        Font.Color = clWindowText
        Font.Height = -11
        Font.Name = 'MS Sans Serif'
        Font.Style = []
        ParentFont = False
        TabOrder = 1
      end
      object RadioButton5: TRadioButton
        Left = 157
        Top = 3
        Width = 76
        Height = 11
        Caption = 'z_pt_maxi'
        Font.Charset = DEFAULT_CHARSET
        Font.Color = clWindowText
        Font.Height = -11
        Font.Name = 'MS Sans Serif'
        Font.Style = []
        ParentFont = False
        TabOrder = 2
      end
      object Button4: TButton
        Left = 54
        Top = 16
        Width = 115
        Height = 16
        Caption = 'MAJ manuelle'
        TabOrder = 3
        OnClick = Button4Click
      end
    end
    object Button5: TButton
      Left = 11
      Top = -1
      Width = 240
      Height = 25
      Caption = 'Choisir la coordonn'#233'e Z optimale'
      Font.Charset = DEFAULT_CHARSET
      Font.Color = clWindowText
      Font.Height = -13
      Font.Name = 'MS Sans Serif'
      Font.Style = [fsBold]
      ParentFont = False
      TabOrder = 0
    end
  end
  object BitBtn1: TBitBtn
    Left = 800
    Top = 926
    Width = 221
    Height = 25
    Caption = 'Points stationnaires et r'#233'gions'
    Font.Charset = DEFAULT_CHARSET
    Font.Color = clWindowText
    Font.Height = -13
    Font.Name = 'MS Sans Serif'
    Font.Style = [fsBold]
    ParentFont = False
    TabOrder = 4
    Visible = False
  end
  object Button6: TButton
    Left = 790
    Top = 895
    Width = 245
    Height = 25
    Caption = 'G'#233'n'#233'rer un fichier STL'
    Font.Charset = DEFAULT_CHARSET
    Font.Color = clBlack
    Font.Height = -13
    Font.Name = 'MS Sans Serif'
    Font.Style = [fsBold]
    ParentFont = False
    TabOrder = 5
    Visible = False
    OnClick = Button6Click
  end
  object Button7: TButton
    Left = 952
    Top = 958
    Width = 75
    Height = 25
    Caption = 'Pts proches'
    Font.Charset = DEFAULT_CHARSET
    Font.Color = clWindowText
    Font.Height = -11
    Font.Name = 'MS Sans Serif'
    Font.Style = [fsBold]
    ParentFont = False
    TabOrder = 6
    Visible = False
    OnClick = Button7Click
  end
  object CheckBox14: TCheckBox
    Left = 777
    Top = 960
    Width = 93
    Height = 17
    Caption = 'R'#233'partition pts'
    Font.Charset = DEFAULT_CHARSET
    Font.Color = clWindowText
    Font.Height = -11
    Font.Name = 'MS Sans Serif'
    Font.Style = []
    ParentFont = False
    TabOrder = 7
    Visible = False
    OnClick = CheckBox1Click
  end
  object ComboBox13: TComboBox
    Left = 871
    Top = 958
    Width = 43
    Height = 21
    Style = csDropDownList
    Font.Charset = DEFAULT_CHARSET
    Font.Color = clWindowText
    Font.Height = -11
    Font.Name = 'MS Sans Serif'
    Font.Style = []
    ItemIndex = 0
    ParentFont = False
    TabOrder = 8
    Text = '1'
    Visible = False
    OnClick = CheckBox1Click
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
  object Button8: TButton
    Left = 952
    Top = 987
    Width = 75
    Height = 25
    Caption = 'Filtrer pts'
    Font.Charset = DEFAULT_CHARSET
    Font.Color = clWindowText
    Font.Height = -11
    Font.Name = 'MS Sans Serif'
    Font.Style = [fsBold]
    ParentFont = False
    TabOrder = 9
    Visible = False
    OnClick = Button8Click
  end
  object Edit7: TEdit
    Left = 874
    Top = 984
    Width = 63
    Height = 24
    Font.Charset = DEFAULT_CHARSET
    Font.Color = clWindowText
    Font.Height = -13
    Font.Name = 'MS Sans Serif'
    Font.Style = [fsBold]
    ParentFont = False
    TabOrder = 10
    Text = '50'
    Visible = False
  end
  object CheckBox15: TCheckBox
    Left = 1094
    Top = 968
    Width = 93
    Height = 17
    Caption = 'Centre cercle'
    Font.Charset = DEFAULT_CHARSET
    Font.Color = clWindowText
    Font.Height = -11
    Font.Name = 'MS Sans Serif'
    Font.Style = []
    ParentFont = False
    TabOrder = 11
    Visible = False
    OnClick = CheckBox1Click
  end
  object ComboBox14: TComboBox
    Left = 1211
    Top = 966
    Width = 43
    Height = 21
    Style = csDropDownList
    Font.Charset = DEFAULT_CHARSET
    Font.Color = clWindowText
    Font.Height = -11
    Font.Name = 'MS Sans Serif'
    Font.Style = []
    ItemIndex = 0
    ParentFont = False
    TabOrder = 12
    Text = '1'
    Visible = False
    OnClick = CheckBox1Click
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
  object CheckBox16: TCheckBox
    Left = 1094
    Top = 992
    Width = 93
    Height = 17
    Caption = 'Centre_Sommets'
    Font.Charset = DEFAULT_CHARSET
    Font.Color = clWindowText
    Font.Height = -11
    Font.Name = 'MS Sans Serif'
    Font.Style = []
    ParentFont = False
    TabOrder = 13
    Visible = False
    OnClick = CheckBox1Click
  end
  object ComboBox15: TComboBox
    Left = 1211
    Top = 990
    Width = 43
    Height = 21
    Style = csDropDownList
    Font.Charset = DEFAULT_CHARSET
    Font.Color = clWindowText
    Font.Height = -11
    Font.Name = 'MS Sans Serif'
    Font.Style = []
    ItemIndex = 0
    ParentFont = False
    TabOrder = 14
    Text = '1'
    Visible = False
    OnClick = CheckBox1Click
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
  object CheckBox17: TCheckBox
    Left = 1094
    Top = 1016
    Width = 121
    Height = 17
    Caption = 'Centre gravit'#233' triangle'
    Font.Charset = DEFAULT_CHARSET
    Font.Color = clWindowText
    Font.Height = -11
    Font.Name = 'MS Sans Serif'
    Font.Style = []
    ParentFont = False
    TabOrder = 15
    Visible = False
    OnClick = CheckBox1Click
  end
  object ComboBox16: TComboBox
    Left = 1211
    Top = 1014
    Width = 43
    Height = 21
    Style = csDropDownList
    Font.Charset = DEFAULT_CHARSET
    Font.Color = clWindowText
    Font.Height = -11
    Font.Name = 'MS Sans Serif'
    Font.Style = []
    ItemIndex = 0
    ParentFont = False
    TabOrder = 16
    Text = '1'
    Visible = False
    OnClick = CheckBox1Click
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
  object CheckBox18: TCheckBox
    Left = 1094
    Top = 1040
    Width = 121
    Height = 17
    Caption = 'Centre gravit'#233' pts triangle'
    Font.Charset = DEFAULT_CHARSET
    Font.Color = clWindowText
    Font.Height = -11
    Font.Name = 'MS Sans Serif'
    Font.Style = []
    ParentFont = False
    TabOrder = 17
    Visible = False
    OnClick = CheckBox1Click
  end
  object ComboBox17: TComboBox
    Left = 1211
    Top = 1038
    Width = 43
    Height = 21
    Style = csDropDownList
    Font.Charset = DEFAULT_CHARSET
    Font.Color = clWindowText
    Font.Height = -11
    Font.Name = 'MS Sans Serif'
    Font.Style = []
    ItemIndex = 0
    ParentFont = False
    TabOrder = 18
    Text = '1'
    Visible = False
    OnClick = CheckBox1Click
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
  object Button10: TButton
    Left = 495
    Top = 377
    Width = 284
    Height = 25
    Caption = 'Subdivision adaptative des triangles'
    Font.Charset = DEFAULT_CHARSET
    Font.Color = clWindowText
    Font.Height = -13
    Font.Name = 'MS Sans Serif'
    Font.Style = [fsBold]
    ParentFont = False
    TabOrder = 20
    Visible = False
    OnClick = Button10Click
  end
  object Button11: TButton
    Left = 1074
    Top = 775
    Width = 166
    Height = 25
    Caption = 'Filtrer triangles/dist min'
    Font.Charset = DEFAULT_CHARSET
    Font.Color = clWindowText
    Font.Height = -11
    Font.Name = 'MS Sans Serif'
    Font.Style = [fsBold]
    ParentFont = False
    TabOrder = 21
    Visible = False
    OnClick = Button11Click
  end
  object CheckBox32: TCheckBox
    Left = 1066
    Top = 805
    Width = 136
    Height = 17
    Caption = 'Centre cercle circonscrit'
    Font.Charset = DEFAULT_CHARSET
    Font.Color = clWindowText
    Font.Height = -11
    Font.Name = 'MS Sans Serif'
    Font.Style = []
    ParentFont = False
    TabOrder = 22
    Visible = False
    OnClick = CheckBox1Click
  end
  object ComboBox30: TComboBox
    Left = 1210
    Top = 803
    Width = 43
    Height = 21
    Style = csDropDownList
    Font.Charset = DEFAULT_CHARSET
    Font.Color = clWindowText
    Font.Height = -11
    Font.Name = 'MS Sans Serif'
    Font.Style = []
    ItemIndex = 0
    ParentFont = False
    TabOrder = 23
    Text = '1'
    Visible = False
    OnClick = CheckBox1Click
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
  object CheckBox33: TCheckBox
    Left = 1066
    Top = 824
    Width = 136
    Height = 17
    Caption = 'Centre cercle -Sommets'
    Font.Charset = DEFAULT_CHARSET
    Font.Color = clWindowText
    Font.Height = -11
    Font.Name = 'MS Sans Serif'
    Font.Style = []
    ParentFont = False
    TabOrder = 24
    Visible = False
    OnClick = CheckBox1Click
  end
  object ComboBox31: TComboBox
    Left = 1210
    Top = 822
    Width = 43
    Height = 21
    Style = csDropDownList
    Font.Charset = DEFAULT_CHARSET
    Font.Color = clWindowText
    Font.Height = -11
    Font.Name = 'MS Sans Serif'
    Font.Style = []
    ItemIndex = 0
    ParentFont = False
    TabOrder = 25
    Text = '1'
    Visible = False
    OnClick = CheckBox1Click
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
  object CheckBox34: TCheckBox
    Left = 1066
    Top = 845
    Width = 121
    Height = 17
    Caption = 'Centre gravit'#233' triangle'
    Font.Charset = DEFAULT_CHARSET
    Font.Color = clWindowText
    Font.Height = -11
    Font.Name = 'MS Sans Serif'
    Font.Style = []
    ParentFont = False
    TabOrder = 26
    Visible = False
    OnClick = CheckBox1Click
  end
  object ComboBox32: TComboBox
    Left = 1210
    Top = 843
    Width = 43
    Height = 21
    Style = csDropDownList
    Font.Charset = DEFAULT_CHARSET
    Font.Color = clWindowText
    Font.Height = -11
    Font.Name = 'MS Sans Serif'
    Font.Style = []
    ItemIndex = 0
    ParentFont = False
    TabOrder = 27
    Text = '1'
    Visible = False
    OnClick = CheckBox1Click
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
  object CheckBox35: TCheckBox
    Left = 1066
    Top = 869
    Width = 144
    Height = 17
    Caption = 'Centre gravit'#233' pts triangle'
    Font.Charset = DEFAULT_CHARSET
    Font.Color = clWindowText
    Font.Height = -11
    Font.Name = 'MS Sans Serif'
    Font.Style = []
    ParentFont = False
    TabOrder = 28
    Visible = False
    OnClick = CheckBox1Click
  end
  object ComboBox33: TComboBox
    Left = 1210
    Top = 865
    Width = 43
    Height = 21
    Style = csDropDownList
    Font.Charset = DEFAULT_CHARSET
    Font.Color = clWindowText
    Font.Height = -11
    Font.Name = 'MS Sans Serif'
    Font.Style = []
    ItemIndex = 0
    ParentFont = False
    TabOrder = 29
    Text = '1'
    Visible = False
    OnClick = CheckBox1Click
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
  object Button12: TButton
    Left = 897
    Top = 1028
    Width = 169
    Height = 25
    Caption = 'Subdiviser triangles'
    Font.Charset = DEFAULT_CHARSET
    Font.Color = clWindowText
    Font.Height = -13
    Font.Name = 'MS Sans Serif'
    Font.Style = [fsBold]
    ParentFont = False
    TabOrder = 30
    Visible = False
    OnClick = Button12Click
  end
  object Button13: TButton
    Left = 1074
    Top = 503
    Width = 109
    Height = 25
    Caption = 'Uniforme vers liste'
    TabOrder = 31
    Visible = False
    OnClick = Button13Click
  end
  object CheckBox36: TCheckBox
    Left = 1074
    Top = 557
    Width = 86
    Height = 17
    Caption = 'Pts '#233'loign'#233's'
    Font.Charset = DEFAULT_CHARSET
    Font.Color = clWindowText
    Font.Height = -11
    Font.Name = 'MS Sans Serif'
    Font.Style = []
    ParentFont = False
    TabOrder = 33
    Visible = False
    OnClick = CheckBox1Click
  end
  object ComboBox34: TComboBox
    Left = 1152
    Top = 555
    Width = 30
    Height = 21
    Style = csDropDownList
    Font.Charset = DEFAULT_CHARSET
    Font.Color = clWindowText
    Font.Height = -11
    Font.Name = 'MS Sans Serif'
    Font.Style = []
    ItemIndex = 0
    ParentFont = False
    TabOrder = 34
    Text = '1'
    Visible = False
    OnClick = CheckBox1Click
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
  object CheckBox37: TCheckBox
    Left = 1074
    Top = 578
    Width = 68
    Height = 17
    Caption = 'Pts proche'
    Font.Charset = DEFAULT_CHARSET
    Font.Color = clWindowText
    Font.Height = -11
    Font.Name = 'MS Sans Serif'
    Font.Style = []
    ParentFont = False
    TabOrder = 35
    Visible = False
    OnClick = CheckBox1Click
  end
  object ComboBox35: TComboBox
    Left = 1153
    Top = 578
    Width = 30
    Height = 21
    Style = csDropDownList
    Font.Charset = DEFAULT_CHARSET
    Font.Color = clWindowText
    Font.Height = -11
    Font.Name = 'MS Sans Serif'
    Font.Style = []
    ItemIndex = 0
    ParentFont = False
    TabOrder = 36
    Text = '1'
    Visible = False
    OnClick = CheckBox1Click
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
  object CheckBox38: TCheckBox
    Left = 1074
    Top = 600
    Width = 122
    Height = 17
    Caption = 'Segement inter'
    Font.Charset = DEFAULT_CHARSET
    Font.Color = clWindowText
    Font.Height = -11
    Font.Name = 'MS Sans Serif'
    Font.Style = []
    ParentFont = False
    TabOrder = 37
    Visible = False
    OnClick = CheckBox1Click
  end
  object ComboBox36: TComboBox
    Left = 1162
    Top = 596
    Width = 30
    Height = 21
    Style = csDropDownList
    Font.Charset = DEFAULT_CHARSET
    Font.Color = clWindowText
    Font.Height = -11
    Font.Name = 'MS Sans Serif'
    Font.Style = []
    ItemIndex = 0
    ParentFont = False
    TabOrder = 38
    Text = '1'
    Visible = False
    OnClick = CheckBox1Click
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
  object Button14: TButton
    Left = 1085
    Top = 612
    Width = 75
    Height = 25
    Caption = 'R'#233'partition'
    Font.Charset = DEFAULT_CHARSET
    Font.Color = clWindowText
    Font.Height = -11
    Font.Name = 'MS Sans Serif'
    Font.Style = [fsBold]
    ParentFont = False
    TabOrder = 39
    Visible = False
    OnClick = Button14Click
  end
  object Button16: TButton
    Left = 511
    Top = 408
    Width = 156
    Height = 25
    Caption = 'Sommets projet'#233's'
    Font.Charset = DEFAULT_CHARSET
    Font.Color = clWindowText
    Font.Height = -13
    Font.Name = 'MS Sans Serif'
    Font.Style = [fsBold]
    ParentFont = False
    TabOrder = 40
    Visible = False
    OnClick = Button16Click
  end
  object CheckBox39: TCheckBox
    Left = 507
    Top = 435
    Width = 116
    Height = 17
    Caption = 'Sommets projet'#233's'
    Font.Charset = DEFAULT_CHARSET
    Font.Color = clWindowText
    Font.Height = -11
    Font.Name = 'MS Sans Serif'
    Font.Style = []
    ParentFont = False
    TabOrder = 41
    Visible = False
    OnClick = CheckBox1Click
  end
  object ComboBox37: TComboBox
    Left = 616
    Top = 437
    Width = 43
    Height = 21
    Style = csDropDownList
    Font.Charset = DEFAULT_CHARSET
    Font.Color = clWindowText
    Font.Height = -11
    Font.Name = 'MS Sans Serif'
    Font.Style = []
    ItemIndex = 0
    ParentFont = False
    TabOrder = 42
    Text = '1'
    Visible = False
    OnClick = CheckBox1Click
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
  object GroupBox13: TGroupBox
    Left = 512
    Top = 454
    Width = 149
    Height = 33
    Caption = 'Coordonn'#233'e Z'
    Font.Charset = DEFAULT_CHARSET
    Font.Color = clWindowText
    Font.Height = -11
    Font.Name = 'MS Sans Serif'
    Font.Style = [fsBold]
    ParentFont = False
    TabOrder = 43
    Visible = False
    object RadioButton13: TRadioButton
      Left = 6
      Top = 14
      Width = 45
      Height = 17
      Caption = 'Max'
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
    object RadioButton14: TRadioButton
      Left = 60
      Top = 13
      Width = 40
      Height = 17
      Caption = 'Min'
      Font.Charset = DEFAULT_CHARSET
      Font.Color = clWindowText
      Font.Height = -11
      Font.Name = 'MS Sans Serif'
      Font.Style = []
      ParentFont = False
      TabOrder = 1
    end
    object RadioButton15: TRadioButton
      Left = 101
      Top = 13
      Width = 43
      Height = 17
      Caption = 'Moy'
      Font.Charset = DEFAULT_CHARSET
      Font.Color = clWindowText
      Font.Height = -11
      Font.Name = 'MS Sans Serif'
      Font.Style = []
      ParentFont = False
      TabOrder = 2
    end
  end
  object Button17: TButton
    Left = 500
    Top = 512
    Width = 187
    Height = 25
    Caption = 'Affecter les coordonn'#233'es'
    Font.Charset = DEFAULT_CHARSET
    Font.Color = clWindowText
    Font.Height = -13
    Font.Name = 'MS Sans Serif'
    Font.Style = [fsBold]
    ParentFont = False
    TabOrder = 44
    Visible = False
    OnClick = Button17Click
  end
  object Button19: TButton
    Left = 88
    Top = 826
    Width = 273
    Height = 25
    Caption = '7. Show triangulation results (optional)'
    Font.Charset = DEFAULT_CHARSET
    Font.Color = clWindowText
    Font.Height = -13
    Font.Name = 'MS Sans Serif'
    Font.Style = [fsBold]
    ParentFont = False
    TabOrder = 45
    OnClick = Button19Click
  end
  object Edit23: TEdit
    Left = 1198
    Top = 897
    Width = 44
    Height = 24
    Font.Charset = DEFAULT_CHARSET
    Font.Color = clWindowText
    Font.Height = -13
    Font.Name = 'MS Sans Serif'
    Font.Style = [fsBold]
    ParentFont = False
    TabOrder = 46
    Text = '50'
    Visible = False
  end
  object Button20: TButton
    Left = 135
    Top = 797
    Width = 178
    Height = 25
    Caption = '6. Generate STL file'
    Font.Charset = DEFAULT_CHARSET
    Font.Color = clWindowText
    Font.Height = -13
    Font.Name = 'MS Sans Serif'
    Font.Style = [fsBold]
    ParentFont = False
    TabOrder = 47
    OnClick = Button20Click
  end
  object GroupBox14: TGroupBox
    Left = 10
    Top = 562
    Width = 430
    Height = 233
    Caption = 'Filtering bad triangles'
    Font.Charset = DEFAULT_CHARSET
    Font.Color = clRed
    Font.Height = -13
    Font.Name = 'MS Sans Serif'
    Font.Style = [fsBold]
    ParentFont = False
    TabOrder = 49
    object Label26: TLabel
      Left = 61
      Top = 184
      Width = 41
      Height = 13
      Caption = 'Line size'
      Font.Charset = DEFAULT_CHARSET
      Font.Color = clBlack
      Font.Height = -11
      Font.Name = 'MS Sans Serif'
      Font.Style = []
      ParentFont = False
    end
    object Label27: TLabel
      Left = 256
      Top = 184
      Width = 45
      Height = 13
      Caption = 'Point size'
      Font.Charset = DEFAULT_CHARSET
      Font.Color = clBlack
      Font.Height = -11
      Font.Name = 'MS Sans Serif'
      Font.Style = []
      ParentFont = False
    end
    object Label14: TLabel
      Left = 10
      Top = 135
      Width = 78
      Height = 13
      Caption = 'Min area triangle'
      Font.Charset = DEFAULT_CHARSET
      Font.Color = clWindowText
      Font.Height = -11
      Font.Name = 'MS Sans Serif'
      Font.Style = []
      ParentFont = False
    end
    object Label15: TLabel
      Left = 270
      Top = 134
      Width = 68
      Height = 13
      Caption = 'Max limits ratio'
      Font.Charset = DEFAULT_CHARSET
      Font.Color = clWindowText
      Font.Height = -11
      Font.Name = 'MS Sans Serif'
      Font.Style = []
      ParentFont = False
    end
    object Label28: TLabel
      Left = 10
      Top = 160
      Width = 137
      Height = 13
      Caption = 'Min number of points/triangle'
      Font.Charset = DEFAULT_CHARSET
      Font.Color = clWindowText
      Font.Height = -11
      Font.Name = 'MS Sans Serif'
      Font.Style = []
      ParentFont = False
    end
    object Label29: TLabel
      Left = 270
      Top = 159
      Width = 66
      Height = 13
      Caption = 'Error min/Line'
      Font.Charset = DEFAULT_CHARSET
      Font.Color = clWindowText
      Font.Height = -11
      Font.Name = 'MS Sans Serif'
      Font.Style = []
      ParentFont = False
    end
    object Label30: TLabel
      Left = 76
      Top = 110
      Width = 86
      Height = 13
      Caption = 'Min height triangle'
      Font.Charset = DEFAULT_CHARSET
      Font.Color = clWindowText
      Font.Height = -11
      Font.Name = 'MS Sans Serif'
      Font.Style = []
      ParentFont = False
    end
    object Button15: TButton
      Left = 100
      Top = 205
      Width = 230
      Height = 25
      Caption = '5. Filter bad triangles (optional)'
      Font.Charset = DEFAULT_CHARSET
      Font.Color = clWindowText
      Font.Height = -13
      Font.Name = 'MS Sans Serif'
      Font.Style = [fsBold]
      ParentFont = False
      TabOrder = 0
      OnClick = Button15Click
    end
    object CheckBox40: TCheckBox
      Left = 8
      Top = 19
      Width = 158
      Height = 17
      Caption = 'area min triangle'
      Font.Charset = DEFAULT_CHARSET
      Font.Color = clWindowText
      Font.Height = -11
      Font.Name = 'MS Sans Serif'
      Font.Style = []
      ParentFont = False
      TabOrder = 1
    end
    object Edit22: TEdit
      Left = 190
      Top = 17
      Width = 60
      Height = 21
      Font.Charset = DEFAULT_CHARSET
      Font.Color = clWindowText
      Font.Height = -11
      Font.Name = 'MS Sans Serif'
      Font.Style = [fsBold]
      ParentFont = False
      TabOrder = 2
      Text = '0.1'
      OnChange = Edit22Change
    end
    object CheckBox41: TCheckBox
      Left = 8
      Top = 40
      Width = 189
      Height = 17
      Caption = 'Ratio Triangle_limit/Points_limit'
      Font.Charset = DEFAULT_CHARSET
      Font.Color = clWindowText
      Font.Height = -11
      Font.Name = 'MS Sans Serif'
      Font.Style = []
      ParentFont = False
      TabOrder = 3
    end
    object Edit24: TEdit
      Left = 190
      Top = 38
      Width = 60
      Height = 21
      Font.Charset = DEFAULT_CHARSET
      Font.Color = clWindowText
      Font.Height = -11
      Font.Name = 'MS Sans Serif'
      Font.Style = [fsBold]
      ParentFont = False
      TabOrder = 4
      Text = '3'
      OnChange = Edit24Change
    end
    object Edit26: TEdit
      Left = 190
      Top = 59
      Width = 60
      Height = 21
      Font.Charset = DEFAULT_CHARSET
      Font.Color = clWindowText
      Font.Height = -11
      Font.Name = 'MS Sans Serif'
      Font.Style = [fsBold]
      ParentFont = False
      TabOrder = 5
      Text = '10'
      OnChange = Edit26Change
    end
    object CheckBox46: TCheckBox
      Left = 8
      Top = 61
      Width = 174
      Height = 17
      Caption = 'Min number of points/triangle'
      Font.Charset = DEFAULT_CHARSET
      Font.Color = clWindowText
      Font.Height = -11
      Font.Name = 'MS Sans Serif'
      Font.Style = []
      ParentFont = False
      TabOrder = 6
    end
    object CheckBox48: TCheckBox
      Left = 275
      Top = 19
      Width = 150
      Height = 17
      Caption = 'Show associated triangles'
      Font.Charset = DEFAULT_CHARSET
      Font.Color = clWindowText
      Font.Height = -11
      Font.Name = 'MS Sans Serif'
      Font.Style = []
      ParentFont = False
      TabOrder = 7
      OnClick = CheckBox48Click
    end
    object CheckBox49: TCheckBox
      Left = 275
      Top = 40
      Width = 142
      Height = 17
      Caption = 'Show associated triangles'
      Font.Charset = DEFAULT_CHARSET
      Font.Color = clWindowText
      Font.Height = -11
      Font.Name = 'MS Sans Serif'
      Font.Style = []
      ParentFont = False
      TabOrder = 8
      OnClick = CheckBox49Click
    end
    object CheckBox50: TCheckBox
      Left = 275
      Top = 61
      Width = 147
      Height = 17
      Caption = 'Show associated triangles'
      Font.Charset = DEFAULT_CHARSET
      Font.Color = clWindowText
      Font.Height = -11
      Font.Name = 'MS Sans Serif'
      Font.Style = []
      ParentFont = False
      TabOrder = 9
      OnClick = CheckBox50Click
    end
    object ComboBox41: TComboBox
      Left = 119
      Top = 181
      Width = 43
      Height = 21
      Style = csDropDownList
      Font.Charset = DEFAULT_CHARSET
      Font.Color = clWindowText
      Font.Height = -11
      Font.Name = 'MS Sans Serif'
      Font.Style = []
      ItemIndex = 0
      ParentFont = False
      TabOrder = 10
      Text = '1'
      OnClick = CheckBox1Click
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
    object ComboBox42: TComboBox
      Left = 312
      Top = 181
      Width = 43
      Height = 21
      Style = csDropDownList
      Font.Charset = DEFAULT_CHARSET
      Font.Color = clWindowText
      Font.Height = -11
      Font.Name = 'MS Sans Serif'
      Font.Style = []
      ItemIndex = 0
      ParentFont = False
      TabOrder = 11
      Text = '1'
      OnClick = CheckBox1Click
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
    object CheckBox51: TCheckBox
      Left = 7
      Top = 82
      Width = 174
      Height = 17
      Caption = 'Error / Line'
      Font.Charset = DEFAULT_CHARSET
      Font.Color = clWindowText
      Font.Height = -11
      Font.Name = 'MS Sans Serif'
      Font.Style = []
      ParentFont = False
      TabOrder = 12
    end
    object Edit28: TEdit
      Left = 190
      Top = 80
      Width = 60
      Height = 21
      Font.Charset = DEFAULT_CHARSET
      Font.Color = clWindowText
      Font.Height = -11
      Font.Name = 'MS Sans Serif'
      Font.Style = [fsBold]
      ParentFont = False
      TabOrder = 13
      Text = '10'
      OnChange = Edit26Change
    end
    object CheckBox52: TCheckBox
      Left = 275
      Top = 82
      Width = 147
      Height = 17
      Caption = 'Show associated triangles'
      Font.Charset = DEFAULT_CHARSET
      Font.Color = clWindowText
      Font.Height = -11
      Font.Name = 'MS Sans Serif'
      Font.Style = []
      ParentFont = False
      TabOrder = 14
      OnClick = CheckBox52Click
    end
    object Edit13: TEdit
      Left = 153
      Top = 129
      Width = 70
      Height = 24
      Font.Charset = DEFAULT_CHARSET
      Font.Color = clRed
      Font.Height = -13
      Font.Name = 'MS Sans Serif'
      Font.Style = [fsBold]
      ParentFont = False
      ReadOnly = True
      TabOrder = 15
    end
    object Edit14: TEdit
      Left = 346
      Top = 129
      Width = 70
      Height = 24
      Font.Charset = DEFAULT_CHARSET
      Font.Color = clRed
      Font.Height = -13
      Font.Name = 'MS Sans Serif'
      Font.Style = [fsBold]
      ParentFont = False
      ReadOnly = True
      TabOrder = 16
    end
    object Edit29: TEdit
      Left = 153
      Top = 154
      Width = 70
      Height = 24
      Font.Charset = DEFAULT_CHARSET
      Font.Color = clRed
      Font.Height = -13
      Font.Name = 'MS Sans Serif'
      Font.Style = [fsBold]
      ParentFont = False
      ReadOnly = True
      TabOrder = 17
    end
    object Edit30: TEdit
      Left = 346
      Top = 154
      Width = 70
      Height = 24
      Font.Charset = DEFAULT_CHARSET
      Font.Color = clRed
      Font.Height = -13
      Font.Name = 'MS Sans Serif'
      Font.Style = [fsBold]
      ParentFont = False
      ReadOnly = True
      TabOrder = 18
    end
    object Edit31: TEdit
      Left = 182
      Top = 106
      Width = 70
      Height = 21
      Font.Charset = DEFAULT_CHARSET
      Font.Color = clBlack
      Font.Height = -11
      Font.Name = 'MS Sans Serif'
      Font.Style = [fsBold]
      ParentFont = False
      TabOrder = 19
      Text = '5'
    end
  end
  object Edit15: TEdit
    Left = 1181
    Top = 659
    Width = 62
    Height = 24
    Font.Charset = DEFAULT_CHARSET
    Font.Color = clWindowText
    Font.Height = -13
    Font.Name = 'MS Sans Serif'
    Font.Style = [fsBold]
    ParentFont = False
    TabOrder = 50
    Text = '9999999'
    Visible = False
    OnKeyPress = Edit3KeyPress
  end
  object Edit20: TEdit
    Left = 1193
    Top = 725
    Width = 62
    Height = 24
    Font.Charset = DEFAULT_CHARSET
    Font.Color = clRed
    Font.Height = -13
    Font.Name = 'MS Sans Serif'
    Font.Style = [fsBold]
    ParentFont = False
    TabOrder = 51
    Visible = False
    OnKeyPress = Edit3KeyPress
  end
  object CheckBox44: TCheckBox
    Left = 1091
    Top = 939
    Width = 169
    Height = 17
    Caption = 'Affichage pendant le calcul'
    Font.Charset = DEFAULT_CHARSET
    Font.Color = clWindowText
    Font.Height = -11
    Font.Name = 'MS Sans Serif'
    Font.Style = []
    ParentFont = False
    TabOrder = 52
    Visible = False
  end
  object Edit21: TEdit
    Left = 1179
    Top = 699
    Width = 62
    Height = 24
    Font.Charset = DEFAULT_CHARSET
    Font.Color = clRed
    Font.Height = -13
    Font.Name = 'MS Sans Serif'
    Font.Style = [fsBold]
    ParentFont = False
    ReadOnly = True
    TabOrder = 53
    Text = '1234567'
    Visible = False
    OnKeyPress = Edit3KeyPress
  end
  object CheckBox53: TCheckBox
    Left = 1092
    Top = 920
    Width = 131
    Height = 17
    Caption = 'suivi de la subdivision'
    Font.Charset = DEFAULT_CHARSET
    Font.Color = clWindowText
    Font.Height = -11
    Font.Name = 'MS Sans Serif'
    Font.Style = []
    ParentFont = False
    TabOrder = 54
    Visible = False
  end
  object Button21: TButton
    Left = 545
    Top = 191
    Width = 227
    Height = 25
    Caption = '5. Traiter les triangles fronti'#232'res'
    Font.Charset = DEFAULT_CHARSET
    Font.Color = clWindowText
    Font.Height = -13
    Font.Name = 'MS Sans Serif'
    Font.Style = [fsBold]
    ParentFont = False
    TabOrder = 55
    OnClick = Button21Click
  end
  object Edit12: TEdit
    Left = 1141
    Top = 533
    Width = 44
    Height = 24
    Font.Charset = DEFAULT_CHARSET
    Font.Color = clWindowText
    Font.Height = -13
    Font.Name = 'MS Sans Serif'
    Font.Style = [fsBold]
    ParentFont = False
    TabOrder = 56
    Text = '50'
    Visible = False
  end
  object Button22: TButton
    Left = 543
    Top = 570
    Width = 229
    Height = 25
    Caption = 'Couleur des triangles non filtr'#233's'
    Font.Charset = DEFAULT_CHARSET
    Font.Color = clWindowText
    Font.Height = -13
    Font.Name = 'MS Sans Serif'
    Font.Style = [fsBold]
    ParentFont = False
    TabOrder = 57
    OnClick = Button22Click
  end
  object GroupBox8: TGroupBox
    Left = 4
    Top = 177
    Width = 440
    Height = 384
    Caption = 'Triangulation approach'
    Font.Charset = DEFAULT_CHARSET
    Font.Color = clWindowText
    Font.Height = -13
    Font.Name = 'MS Sans Serif'
    Font.Style = [fsBold]
    ParentFont = False
    TabOrder = 19
    object Label8: TLabel
      Left = 8
      Top = 21
      Width = 157
      Height = 13
      Caption = 'Number of segments along X-axis'
      Font.Charset = DEFAULT_CHARSET
      Font.Color = clWindowText
      Font.Height = -11
      Font.Name = 'MS Sans Serif'
      Font.Style = []
      ParentFont = False
    end
    object Label10: TLabel
      Left = 227
      Top = 21
      Width = 157
      Height = 13
      Caption = 'Number of segments along Y-axis'
      Font.Charset = DEFAULT_CHARSET
      Font.Color = clWindowText
      Font.Height = -11
      Font.Name = 'MS Sans Serif'
      Font.Style = []
      ParentFont = False
    end
    object Edit9: TEdit
      Left = 170
      Top = 15
      Width = 45
      Height = 24
      Font.Charset = DEFAULT_CHARSET
      Font.Color = clWindowText
      Font.Height = -13
      Font.Name = 'MS Sans Serif'
      Font.Style = [fsBold]
      ParentFont = False
      TabOrder = 0
      Text = '20'
      OnKeyPress = Edit3KeyPress
    end
    object Edit10: TEdit
      Left = 390
      Top = 15
      Width = 45
      Height = 24
      Font.Charset = DEFAULT_CHARSET
      Font.Color = clWindowText
      Font.Height = -13
      Font.Name = 'MS Sans Serif'
      Font.Style = [fsBold]
      ParentFont = False
      TabOrder = 1
      Text = '10'
      OnKeyPress = Edit3KeyPress
    end
    object GroupBox9: TGroupBox
      Left = 5
      Top = 202
      Width = 430
      Height = 178
      Caption = 'Visualization'
      TabOrder = 2
      object CheckBox22: TCheckBox
        Left = 202
        Top = 41
        Width = 111
        Height = 17
        Caption = 'Triangle points'
        Font.Charset = DEFAULT_CHARSET
        Font.Color = clWindowText
        Font.Height = -11
        Font.Name = 'MS Sans Serif'
        Font.Style = []
        ParentFont = False
        TabOrder = 0
        OnClick = CheckBox1Click
      end
      object ComboBox21: TComboBox
        Left = 373
        Top = 39
        Width = 43
        Height = 21
        Style = csDropDownList
        Font.Charset = DEFAULT_CHARSET
        Font.Color = clWindowText
        Font.Height = -11
        Font.Name = 'MS Sans Serif'
        Font.Style = []
        ItemIndex = 0
        ParentFont = False
        TabOrder = 1
        Text = '1'
        OnClick = CheckBox1Click
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
      object CheckBox23: TCheckBox
        Left = 202
        Top = 64
        Width = 163
        Height = 17
        Caption = 'Points of non-filtered triangles'
        Font.Charset = DEFAULT_CHARSET
        Font.Color = clWindowText
        Font.Height = -11
        Font.Name = 'MS Sans Serif'
        Font.Style = []
        ParentFont = False
        TabOrder = 2
        OnClick = CheckBox1Click
      end
      object ComboBox22: TComboBox
        Left = 373
        Top = 62
        Width = 43
        Height = 21
        Style = csDropDownList
        Font.Charset = DEFAULT_CHARSET
        Font.Color = clWindowText
        Font.Height = -11
        Font.Name = 'MS Sans Serif'
        Font.Style = []
        ItemIndex = 0
        ParentFont = False
        TabOrder = 3
        Text = '1'
        OnClick = CheckBox1Click
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
      object CheckBox24: TCheckBox
        Left = 8
        Top = 41
        Width = 92
        Height = 17
        Caption = '2D triangles'
        Font.Charset = DEFAULT_CHARSET
        Font.Color = clWindowText
        Font.Height = -11
        Font.Name = 'MS Sans Serif'
        Font.Style = []
        ParentFont = False
        TabOrder = 4
        OnClick = CheckBox1Click
      end
      object ComboBox23: TComboBox
        Left = 147
        Top = 39
        Width = 43
        Height = 21
        Style = csDropDownList
        Font.Charset = DEFAULT_CHARSET
        Font.Color = clWindowText
        Font.Height = -11
        Font.Name = 'MS Sans Serif'
        Font.Style = []
        ItemIndex = 0
        ParentFont = False
        TabOrder = 5
        Text = '1'
        OnClick = CheckBox1Click
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
      object CheckBox25: TCheckBox
        Left = 202
        Top = 87
        Width = 165
        Height = 17
        Caption = 'Points of 2D filtered triangles'
        Font.Charset = DEFAULT_CHARSET
        Font.Color = clWindowText
        Font.Height = -11
        Font.Name = 'MS Sans Serif'
        Font.Style = []
        ParentFont = False
        TabOrder = 6
        OnClick = CheckBox1Click
      end
      object ComboBox24: TComboBox
        Left = 373
        Top = 85
        Width = 43
        Height = 21
        Style = csDropDownList
        Font.Charset = DEFAULT_CHARSET
        Font.Color = clWindowText
        Font.Height = -11
        Font.Name = 'MS Sans Serif'
        Font.Style = []
        ItemIndex = 0
        ParentFont = False
        TabOrder = 7
        Text = '1'
        OnClick = CheckBox1Click
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
      object CheckBox26: TCheckBox
        Left = 8
        Top = 87
        Width = 121
        Height = 17
        Caption = '2D filtered triangles'
        Font.Charset = DEFAULT_CHARSET
        Font.Color = clWindowText
        Font.Height = -11
        Font.Name = 'MS Sans Serif'
        Font.Style = []
        ParentFont = False
        TabOrder = 8
        OnClick = CheckBox1Click
      end
      object ComboBox25: TComboBox
        Left = 147
        Top = 85
        Width = 43
        Height = 21
        Style = csDropDownList
        Font.Charset = DEFAULT_CHARSET
        Font.Color = clWindowText
        Font.Height = -11
        Font.Name = 'MS Sans Serif'
        Font.Style = []
        ItemIndex = 0
        ParentFont = False
        TabOrder = 9
        Text = '1'
        OnClick = CheckBox1Click
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
      object CheckBox27: TCheckBox
        Left = 8
        Top = 64
        Width = 124
        Height = 17
        Caption = 'Non-filtered triangles'
        Font.Charset = DEFAULT_CHARSET
        Font.Color = clWindowText
        Font.Height = -11
        Font.Name = 'MS Sans Serif'
        Font.Style = []
        ParentFont = False
        TabOrder = 10
        OnClick = CheckBox1Click
      end
      object ComboBox26: TComboBox
        Left = 147
        Top = 62
        Width = 43
        Height = 21
        Style = csDropDownList
        Font.Charset = DEFAULT_CHARSET
        Font.Color = clWindowText
        Font.Height = -11
        Font.Name = 'MS Sans Serif'
        Font.Style = []
        ItemIndex = 0
        ParentFont = False
        TabOrder = 11
        Text = '1'
        OnClick = CheckBox1Click
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
      object CheckBox29: TCheckBox
        Left = 202
        Top = 19
        Width = 89
        Height = 17
        Caption = 'Raw part'
        Font.Charset = DEFAULT_CHARSET
        Font.Color = clWindowText
        Font.Height = -11
        Font.Name = 'MS Sans Serif'
        Font.Style = []
        ParentFont = False
        TabOrder = 12
        OnClick = CheckBox29Click
      end
      object CheckBox30: TCheckBox
        Left = 8
        Top = 112
        Width = 135
        Height = 17
        Caption = 'Point distribution/vertices'
        Font.Charset = DEFAULT_CHARSET
        Font.Color = clWindowText
        Font.Height = -11
        Font.Name = 'MS Sans Serif'
        Font.Style = []
        ParentFont = False
        TabOrder = 13
        OnClick = CheckBox1Click
      end
      object ComboBox28: TComboBox
        Left = 147
        Top = 110
        Width = 43
        Height = 21
        Style = csDropDownList
        Font.Charset = DEFAULT_CHARSET
        Font.Color = clWindowText
        Font.Height = -11
        Font.Name = 'MS Sans Serif'
        Font.Style = []
        ItemIndex = 0
        ParentFont = False
        TabOrder = 14
        Text = '1'
        OnClick = CheckBox1Click
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
      object CheckBox47: TCheckBox
        Left = 202
        Top = 112
        Width = 162
        Height = 17
        Caption = 'Point distribution/midpoints'
        Font.Charset = DEFAULT_CHARSET
        Font.Color = clWindowText
        Font.Height = -11
        Font.Name = 'MS Sans Serif'
        Font.Style = []
        ParentFont = False
        TabOrder = 15
        OnClick = CheckBox1Click
      end
      object ComboBox38: TComboBox
        Left = 373
        Top = 110
        Width = 43
        Height = 21
        Style = csDropDownList
        Font.Charset = DEFAULT_CHARSET
        Font.Color = clWindowText
        Font.Height = -11
        Font.Name = 'MS Sans Serif'
        Font.Style = []
        ItemIndex = 0
        ParentFont = False
        TabOrder = 16
        Text = '1'
        OnClick = CheckBox1Click
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
      object CheckBox21: TCheckBox
        Left = 8
        Top = 17
        Width = 101
        Height = 18
        Caption = 'Point clouds'
        Font.Charset = DEFAULT_CHARSET
        Font.Color = clWindowText
        Font.Height = -11
        Font.Name = 'MS Sans Serif'
        Font.Style = []
        ParentFont = False
        TabOrder = 17
        OnClick = CheckBox1Click
      end
      object ComboBox20: TComboBox
        Left = 147
        Top = 17
        Width = 43
        Height = 21
        Style = csDropDownList
        Font.Charset = DEFAULT_CHARSET
        Font.Color = clWindowText
        Font.Height = -11
        Font.Name = 'MS Sans Serif'
        Font.Style = []
        ItemIndex = 0
        ParentFont = False
        TabOrder = 18
        Text = '1'
        OnClick = CheckBox1Click
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
          '10'
          '20'
          '30'
          '40'
          '50')
      end
      object GroupBox10: TGroupBox
        Left = 119
        Top = 133
        Width = 192
        Height = 40
        Caption = 'Modes'
        Font.Charset = DEFAULT_CHARSET
        Font.Color = clWindowText
        Font.Height = -13
        Font.Name = 'MS Sans Serif'
        Font.Style = [fsBold]
        ParentFont = False
        TabOrder = 19
        object RadioButton6: TRadioButton
          Left = 40
          Top = 18
          Width = 72
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
          OnClick = CheckBox1Click
        end
        object RadioButton7: TRadioButton
          Left = 118
          Top = 19
          Width = 71
          Height = 17
          Caption = 'Rendered'
          Font.Charset = DEFAULT_CHARSET
          Font.Color = clWindowText
          Font.Height = -11
          Font.Name = 'MS Sans Serif'
          Font.Style = []
          ParentFont = False
          TabOrder = 1
          OnClick = CheckBox1Click
        end
      end
    end
    object Button9: TButton
      Left = 95
      Top = 41
      Width = 250
      Height = 25
      Caption = '3. Generate regular triangulation'
      Font.Charset = DEFAULT_CHARSET
      Font.Color = clWindowText
      Font.Height = -13
      Font.Name = 'MS Sans Serif'
      Font.Style = [fsBold]
      ParentFont = False
      TabOrder = 3
      OnClick = Button9Click
    end
    object GroupBox15: TGroupBox
      Left = 5
      Top = 72
      Width = 430
      Height = 50
      Caption = 'Adaptive subdivision parameters'
      Font.Charset = DEFAULT_CHARSET
      Font.Color = clWindowText
      Font.Height = -13
      Font.Name = 'MS Sans Serif'
      Font.Style = [fsBold]
      ParentFont = False
      TabOrder = 4
      object Label16: TLabel
        Left = 11
        Top = 25
        Width = 78
        Height = 13
        Caption = 'Area min triangle'
        Font.Charset = DEFAULT_CHARSET
        Font.Color = clWindowText
        Font.Height = -11
        Font.Name = 'MS Sans Serif'
        Font.Style = []
        ParentFont = False
      end
      object Label11: TLabel
        Left = 160
        Top = 25
        Width = 93
        Height = 13
        Caption = 'Subdivision percent'
        Font.Charset = DEFAULT_CHARSET
        Font.Color = clWindowText
        Font.Height = -11
        Font.Name = 'MS Sans Serif'
        Font.Style = []
        ParentFont = False
      end
      object Label25: TLabel
        Left = 103
        Top = 93
        Width = 45
        Height = 13
        Caption = 'Lseg_min'
        Font.Charset = DEFAULT_CHARSET
        Font.Color = clWindowText
        Font.Height = -11
        Font.Name = 'MS Sans Serif'
        Font.Style = []
        ParentFont = False
        Visible = False
      end
      object Label31: TLabel
        Left = 319
        Top = 24
        Width = 43
        Height = 13
        Caption = 'Precision'
        Font.Charset = DEFAULT_CHARSET
        Font.Color = clWindowText
        Font.Height = -11
        Font.Name = 'MS Sans Serif'
        Font.Style = []
        ParentFont = False
      end
      object Edit19: TEdit
        Left = 95
        Top = 19
        Width = 50
        Height = 24
        Font.Charset = DEFAULT_CHARSET
        Font.Color = clWindowText
        Font.Height = -13
        Font.Name = 'MS Sans Serif'
        Font.Style = [fsBold]
        ParentFont = False
        TabOrder = 0
        Text = '0.05'
      end
      object Edit11: TEdit
        Left = 260
        Top = 19
        Width = 50
        Height = 24
        Font.Charset = DEFAULT_CHARSET
        Font.Color = clWindowText
        Font.Height = -13
        Font.Name = 'MS Sans Serif'
        Font.Style = [fsBold]
        ParentFont = False
        TabOrder = 1
        Text = '30'
      end
      object Edit27: TEdit
        Left = 150
        Top = 88
        Width = 50
        Height = 24
        Font.Charset = DEFAULT_CHARSET
        Font.Color = clWindowText
        Font.Height = -13
        Font.Name = 'MS Sans Serif'
        Font.Style = [fsBold]
        ParentFont = False
        TabOrder = 2
        Text = '0.5'
        Visible = False
      end
      object Edit32: TEdit
        Left = 365
        Top = 19
        Width = 60
        Height = 24
        Font.Charset = DEFAULT_CHARSET
        Font.Color = clWindowText
        Font.Height = -13
        Font.Name = 'MS Sans Serif'
        Font.Style = [fsBold]
        ParentFont = False
        TabOrder = 3
        Text = '0.050000'
        OnKeyPress = Edit32KeyPress
      end
    end
    object Button18: TButton
      Left = 76
      Top = 123
      Width = 287
      Height = 25
      Caption = '4. Generate adaptive triangulation'
      DoubleBuffered = False
      Font.Charset = DEFAULT_CHARSET
      Font.Color = clBlack
      Font.Height = -13
      Font.Name = 'MS Sans Serif'
      Font.Style = [fsBold]
      ParentDoubleBuffered = False
      ParentFont = False
      TabOrder = 5
      OnClick = Button18Click
    end
    object GroupBox12: TGroupBox
      Left = 50
      Top = 151
      Width = 340
      Height = 50
      Caption = 'Errors point clouds/triangles '
      Font.Charset = DEFAULT_CHARSET
      Font.Color = clWindowText
      Font.Height = -13
      Font.Name = 'MS Sans Serif'
      Font.Style = [fsBold]
      ParentFont = False
      TabOrder = 6
      object Label32: TLabel
        Left = 22
        Top = 25
        Width = 44
        Height = 13
        Caption = 'Error min '
        Font.Charset = DEFAULT_CHARSET
        Font.Color = clWindowText
        Font.Height = -11
        Font.Name = 'MS Sans Serif'
        Font.Style = []
        ParentFont = False
      end
      object Label33: TLabel
        Left = 173
        Top = 25
        Width = 44
        Height = 13
        Caption = 'Error max'
        Font.Charset = DEFAULT_CHARSET
        Font.Color = clWindowText
        Font.Height = -11
        Font.Name = 'MS Sans Serif'
        Font.Style = []
        ParentFont = False
      end
      object Edit33: TEdit
        Left = 73
        Top = 19
        Width = 90
        Height = 24
        Font.Charset = DEFAULT_CHARSET
        Font.Color = clRed
        Font.Height = -13
        Font.Name = 'MS Sans Serif'
        Font.Style = [fsBold]
        ParentFont = False
        ReadOnly = True
        TabOrder = 0
      end
      object Edit34: TEdit
        Left = 226
        Top = 19
        Width = 90
        Height = 24
        Font.Charset = DEFAULT_CHARSET
        Font.Color = clRed
        Font.Height = -13
        Font.Name = 'MS Sans Serif'
        Font.Style = [fsBold]
        ParentFont = False
        ReadOnly = True
        TabOrder = 1
      end
    end
  end
  object GroupBox27: TGroupBox
    Left = 5
    Top = 120
    Width = 440
    Height = 48
    Caption = 'Processing time'
    Font.Charset = DEFAULT_CHARSET
    Font.Color = clWindowText
    Font.Height = -13
    Font.Name = 'MS Sans Serif'
    Font.Style = [fsBold]
    ParentFont = False
    TabOrder = 48
    object Label41: TLabel
      Left = 22
      Top = 25
      Width = 29
      Height = 13
      Caption = 'Days'
      Font.Charset = DEFAULT_CHARSET
      Font.Color = clWindowText
      Font.Height = -11
      Font.Name = 'MS Sans Serif'
      Font.Style = [fsBold]
      ParentFont = False
    end
    object Label42: TLabel
      Left = 117
      Top = 25
      Width = 34
      Height = 13
      Caption = 'Hours'
      Font.Charset = DEFAULT_CHARSET
      Font.Color = clWindowText
      Font.Height = -11
      Font.Name = 'MS Sans Serif'
      Font.Style = [fsBold]
      ParentFont = False
    end
    object Label43: TLabel
      Left = 217
      Top = 25
      Width = 45
      Height = 13
      Caption = 'Minutes'
      Font.Charset = DEFAULT_CHARSET
      Font.Color = clWindowText
      Font.Height = -11
      Font.Name = 'MS Sans Serif'
      Font.Style = [fsBold]
      ParentFont = False
    end
    object Label44: TLabel
      Left = 330
      Top = 25
      Width = 50
      Height = 13
      Caption = 'Seconds'
      Font.Charset = DEFAULT_CHARSET
      Font.Color = clWindowText
      Font.Height = -11
      Font.Name = 'MS Sans Serif'
      Font.Style = [fsBold]
      ParentFont = False
    end
    object Edit39: TEdit
      Left = 53
      Top = 19
      Width = 52
      Height = 24
      Font.Charset = DEFAULT_CHARSET
      Font.Color = clRed
      Font.Height = -13
      Font.Name = 'MS Sans Serif'
      Font.Style = [fsBold]
      ParentFont = False
      ReadOnly = True
      TabOrder = 0
    end
    object Edit40: TEdit
      Left = 154
      Top = 19
      Width = 52
      Height = 24
      Font.Charset = DEFAULT_CHARSET
      Font.Color = clRed
      Font.Height = -13
      Font.Name = 'MS Sans Serif'
      Font.Style = [fsBold]
      ParentFont = False
      ReadOnly = True
      TabOrder = 1
    end
    object Edit41: TEdit
      Left = 266
      Top = 19
      Width = 52
      Height = 24
      Font.Charset = DEFAULT_CHARSET
      Font.Color = clRed
      Font.Height = -13
      Font.Name = 'MS Sans Serif'
      Font.Style = [fsBold]
      ParentFont = False
      ReadOnly = True
      TabOrder = 2
    end
    object Edit42: TEdit
      Left = 382
      Top = 19
      Width = 52
      Height = 24
      Font.Charset = DEFAULT_CHARSET
      Font.Color = clRed
      Font.Height = -13
      Font.Name = 'MS Sans Serif'
      Font.Style = [fsBold]
      ParentFont = False
      ReadOnly = True
      TabOrder = 3
    end
  end
  object GroupBox17: TGroupBox
    Left = 589
    Top = 705
    Width = 416
    Height = 84
    Caption = 'G'#233'n'#233'ration incr'#233'mentale de la triangulation adaptative'
    Font.Charset = DEFAULT_CHARSET
    Font.Color = clWindowText
    Font.Height = -13
    Font.Name = 'MS Sans Serif'
    Font.Style = [fsBold]
    ParentFont = False
    TabOrder = 58
    object Label34: TLabel
      Left = 6
      Top = 23
      Width = 85
      Height = 13
      Caption = 'Nbre d'#39'incr'#233'ments'
      Font.Charset = DEFAULT_CHARSET
      Font.Color = clWindowText
      Font.Height = -11
      Font.Name = 'MS Sans Serif'
      Font.Style = []
      ParentFont = False
    end
    object Label35: TLabel
      Left = 255
      Top = 23
      Width = 78
      Height = 13
      Caption = 'Indice incr'#233'ment'
      Font.Charset = DEFAULT_CHARSET
      Font.Color = clWindowText
      Font.Height = -11
      Font.Name = 'MS Sans Serif'
      Font.Style = []
      ParentFont = False
    end
    object Edit35: TEdit
      Left = 174
      Top = 17
      Width = 70
      Height = 24
      Font.Charset = DEFAULT_CHARSET
      Font.Color = clRed
      Font.Height = -13
      Font.Name = 'MS Sans Serif'
      Font.Style = [fsBold]
      ParentFont = False
      TabOrder = 0
    end
    object Button23: TButton
      Left = 67
      Top = 59
      Width = 282
      Height = 25
      Caption = 'Triangulation adaptative progressive'
      Font.Charset = DEFAULT_CHARSET
      Font.Color = clWindowText
      Font.Height = -13
      Font.Name = 'MS Sans Serif'
      Font.Style = [fsBold]
      ParentFont = False
      TabOrder = 1
      OnClick = Button23Click
    end
    object Edit36: TEdit
      Left = 337
      Top = 17
      Width = 70
      Height = 24
      Font.Charset = DEFAULT_CHARSET
      Font.Color = clRed
      Font.Height = -13
      Font.Name = 'MS Sans Serif'
      Font.Style = [fsBold]
      NumbersOnly = True
      ParentFont = False
      ReadOnly = True
      TabOrder = 2
    end
    object RadioButton12: TRadioButton
      Left = 230
      Top = 41
      Width = 175
      Height = 17
      Caption = 'Subdivision r'#233'curssive de l'#39'erreur'
      Font.Charset = DEFAULT_CHARSET
      Font.Color = clWindowText
      Font.Height = -11
      Font.Name = 'MS Sans Serif'
      Font.Style = []
      ParentFont = False
      TabOrder = 3
      OnClick = RadioButton12Click
    end
    object RadioButton16: TRadioButton
      Left = 40
      Top = 41
      Width = 174
      Height = 17
      Caption = 'R'#233'duction constante de l'#39'erreur'
      Checked = True
      Font.Charset = DEFAULT_CHARSET
      Font.Color = clWindowText
      Font.Height = -11
      Font.Name = 'MS Sans Serif'
      Font.Style = []
      ParentFont = False
      TabOrder = 4
      TabStop = True
      OnClick = RadioButton16Click
    end
  end
  object Button24: TButton
    Left = 531
    Top = 254
    Width = 230
    Height = 25
    Caption = 'Filtrer les triangles sans voisins'
    Font.Charset = DEFAULT_CHARSET
    Font.Color = clWindowText
    Font.Height = -13
    Font.Name = 'MS Sans Serif'
    Font.Style = [fsBold]
    ParentFont = False
    TabOrder = 59
    OnClick = Button24Click
  end
  object Button25: TButton
    Left = 544
    Top = 609
    Width = 239
    Height = 25
    Caption = 'Couleur des points des triangles'
    Font.Charset = DEFAULT_CHARSET
    Font.Color = clWindowText
    Font.Height = -13
    Font.Name = 'MS Sans Serif'
    Font.Style = [fsBold]
    ParentFont = False
    TabOrder = 60
    OnClick = Button25Click
  end
  object CheckBox28: TCheckBox
    Left = 726
    Top = 71
    Width = 139
    Height = 17
    Caption = 'Param'#232'tres d'#39'un triangle'
    Font.Charset = DEFAULT_CHARSET
    Font.Color = clWindowText
    Font.Height = -11
    Font.Name = 'MS Sans Serif'
    Font.Style = []
    ParentFont = False
    TabOrder = 61
    OnClick = CheckBox28Click
  end
  object ComboBox27: TComboBox
    Left = 860
    Top = 69
    Width = 95
    Height = 21
    Style = csDropDownList
    Font.Charset = DEFAULT_CHARSET
    Font.Color = clWindowText
    Font.Height = -11
    Font.Name = 'MS Sans Serif'
    Font.Style = [fsBold]
    ParentFont = False
    TabOrder = 62
    OnClick = ComboBox27Click
    Items.Strings = (
      '')
  end
  object Edit37: TEdit
    Left = 926
    Top = 95
    Width = 68
    Height = 24
    Font.Charset = DEFAULT_CHARSET
    Font.Color = clRed
    Font.Height = -13
    Font.Name = 'MS Sans Serif'
    Font.Style = [fsBold]
    ParentFont = False
    ReadOnly = True
    TabOrder = 63
  end
  object GroupBox18: TGroupBox
    Left = 724
    Top = 91
    Width = 147
    Height = 66
    Caption = 'Affichage'
    Font.Charset = DEFAULT_CHARSET
    Font.Color = clWindowText
    Font.Height = -11
    Font.Name = 'MS Sans Serif'
    Font.Style = [fsBold]
    ParentFont = False
    TabOrder = 64
    object CheckBox19: TCheckBox
      Left = 62
      Top = 15
      Width = 63
      Height = 17
      Caption = 'Triangle'
      Font.Charset = DEFAULT_CHARSET
      Font.Color = clWindowText
      Font.Height = -11
      Font.Name = 'MS Sans Serif'
      Font.Style = []
      ParentFont = False
      TabOrder = 0
      OnClick = CheckBox1Click
    end
    object CheckBox20: TCheckBox
      Left = 7
      Top = 15
      Width = 54
      Height = 17
      Caption = 'Voisins'
      Font.Charset = DEFAULT_CHARSET
      Font.Color = clWindowText
      Font.Height = -11
      Font.Name = 'MS Sans Serif'
      Font.Style = []
      ParentFont = False
      TabOrder = 1
      OnClick = CheckBox1Click
    end
    object CheckBox31: TCheckBox
      Left = 7
      Top = 31
      Width = 53
      Height = 17
      Caption = 'Points'
      Font.Charset = DEFAULT_CHARSET
      Font.Color = clWindowText
      Font.Height = -11
      Font.Name = 'MS Sans Serif'
      Font.Style = []
      ParentFont = False
      TabOrder = 2
      OnClick = CheckBox1Click
    end
    object CheckBox55: TCheckBox
      Left = 62
      Top = 31
      Width = 88
      Height = 17
      Caption = 'Pt_Ecart_Max'
      Font.Charset = DEFAULT_CHARSET
      Font.Color = clWindowText
      Font.Height = -11
      Font.Name = 'MS Sans Serif'
      Font.Style = []
      ParentFont = False
      TabOrder = 3
      OnClick = CheckBox1Click
    end
    object CheckBox56: TCheckBox
      Left = 7
      Top = 47
      Width = 115
      Height = 17
      Caption = 'Normale Triangle'
      Font.Charset = DEFAULT_CHARSET
      Font.Color = clWindowText
      Font.Height = -11
      Font.Name = 'MS Sans Serif'
      Font.Style = []
      ParentFont = False
      TabOrder = 4
      OnClick = CheckBox1Click
    end
  end
  object GroupBox16: TGroupBox
    Left = 1013
    Top = 64
    Width = 121
    Height = 90
    Caption = 'Densit'#233's/Sommets'
    Font.Charset = DEFAULT_CHARSET
    Font.Color = clWindowText
    Font.Height = -11
    Font.Name = 'MS Sans Serif'
    Font.Style = [fsBold]
    ParentFont = False
    TabOrder = 65
    object Label21: TLabel
      Left = 27
      Top = 21
      Width = 16
      Height = 13
      Caption = 'S1'
    end
    object Label22: TLabel
      Left = 27
      Top = 45
      Width = 16
      Height = 13
      Caption = 'S2'
    end
    object Label23: TLabel
      Left = 27
      Top = 69
      Width = 16
      Height = 13
      Caption = 'S3'
    end
    object Edit16: TEdit
      Left = 49
      Top = 16
      Width = 60
      Height = 24
      Font.Charset = DEFAULT_CHARSET
      Font.Color = clRed
      Font.Height = -13
      Font.Name = 'MS Sans Serif'
      Font.Style = [fsBold]
      ParentFont = False
      ReadOnly = True
      TabOrder = 0
      OnKeyPress = Edit3KeyPress
    end
    object Edit17: TEdit
      Left = 49
      Top = 40
      Width = 60
      Height = 24
      Font.Charset = DEFAULT_CHARSET
      Font.Color = clRed
      Font.Height = -13
      Font.Name = 'MS Sans Serif'
      Font.Style = [fsBold]
      ParentFont = False
      ReadOnly = True
      TabOrder = 1
      OnKeyPress = Edit3KeyPress
    end
    object Edit18: TEdit
      Left = 49
      Top = 64
      Width = 60
      Height = 24
      Font.Charset = DEFAULT_CHARSET
      Font.Color = clRed
      Font.Height = -13
      Font.Name = 'MS Sans Serif'
      Font.Style = [fsBold]
      ParentFont = False
      ReadOnly = True
      TabOrder = 2
      OnKeyPress = Edit3KeyPress
    end
  end
  object CheckBox42: TCheckBox
    Left = 559
    Top = 24
    Width = 118
    Height = 17
    Caption = 'Triangles non pleins'
    Font.Charset = DEFAULT_CHARSET
    Font.Color = clWindowText
    Font.Height = -11
    Font.Name = 'MS Sans Serif'
    Font.Style = []
    ParentFont = False
    TabOrder = 66
    OnClick = CheckBox1Click
  end
  object ComboBox39: TComboBox
    Left = 694
    Top = 21
    Width = 43
    Height = 21
    Style = csDropDownList
    Font.Charset = DEFAULT_CHARSET
    Font.Color = clWindowText
    Font.Height = -11
    Font.Name = 'MS Sans Serif'
    Font.Style = []
    ItemIndex = 0
    ParentFont = False
    TabOrder = 67
    Text = '1'
    OnClick = CheckBox1Click
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
  object CheckBox43: TCheckBox
    Left = 746
    Top = 23
    Width = 181
    Height = 17
    Caption = 'Points des triangles non pleins'
    Font.Charset = DEFAULT_CHARSET
    Font.Color = clWindowText
    Font.Height = -11
    Font.Name = 'MS Sans Serif'
    Font.Style = []
    ParentFont = False
    TabOrder = 68
    OnClick = CheckBox1Click
  end
  object ComboBox40: TComboBox
    Left = 917
    Top = 21
    Width = 43
    Height = 21
    Style = csDropDownList
    Font.Charset = DEFAULT_CHARSET
    Font.Color = clWindowText
    Font.Height = -11
    Font.Name = 'MS Sans Serif'
    Font.Style = []
    ItemIndex = 0
    ParentFont = False
    TabOrder = 69
    Text = '1'
    OnClick = CheckBox1Click
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
  object SaveDialog1: TSaveDialog
    DefaultExt = 'BSP'
    Filter = 'Fichier STL (*.stl)| *.stl'
    InitialDir = 'Scene'
    Options = [ofOverwritePrompt, ofHideReadOnly, ofPathMustExist, ofFileMustExist, ofEnableSizing]
    Left = 12
    Top = 806
  end
  object ColorDialog1: TColorDialog
    Color = clFuchsia
    CustomColors.Strings = (
      'ColorA=FFFFFFFF'
      'ColorB=FFFFFFFF'
      'ColorC=FFFFFFFF'
      'ColorD=FFFFFFFF'
      'ColorE=FFFFFFFF'
      'ColorF=FFFFFFFF'
      'ColorG=FFFFFFFF'
      'ColorH=FFFFFFFF'
      'ColorI=FFFFFFFF'
      'ColorJ=FFFFFFFF'
      'ColorK=FFFFFFFF'
      'ColorL=FFFFFFFF'
      'ColorM=FFFFFFFF'
      'ColorN=FFFFFFFF'
      'ColorO=FFFFFFFF'
      'ColorP=FFFFFFFF')
    Left = 1150
    Top = 668
  end
end
