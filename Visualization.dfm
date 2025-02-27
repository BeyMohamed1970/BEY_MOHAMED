object Visualization: TVisualization
  Left = 100
  Top = 100
  BorderIcons = []
  BorderStyle = bsDialog
  Caption = 
    'Adaptive Triangulation of 3D Point Clouds for Machining Sculptur' +
    'ed Surfaces'
  ClientHeight = 568
  ClientWidth = 542
  Color = clBtnFace
  Font.Charset = DEFAULT_CHARSET
  Font.Color = clWindowText
  Font.Height = -11
  Font.Name = 'Tahoma'
  Font.Style = []
  OldCreateOrder = False
  PopupMenu = PopupMenu1
  Position = poDesigned
  OnCreate = FormCreate
  OnMouseDown = FormMouseDown
  OnMouseMove = FormMouseMove
  OnMouseUp = FormMouseUp
  OnShow = FormShow
  PixelsPerInch = 96
  TextHeight = 13
  object PopupMenu1: TPopupMenu
    Left = 240
    Top = 120
    object Selection1: TMenuItem
      Caption = '&Selection'
      Checked = True
      Visible = False
    end
    object N1: TMenuItem
      Caption = '-'
    end
    object Vue3D1: TMenuItem
      Caption = '3D Vue '
      OnClick = Vue3D1Click
    end
    object Zoom1: TMenuItem
      Caption = '&Zoom'
      OnClick = Zoom1Click
    end
    object ZoomRgion1: TMenuItem
      Caption = 'Zoom area'
      OnClick = ZoomRgion1Click
    end
    object ZoomAll1: TMenuItem
      Caption = 'Zoom All'
      OnClick = ZoomAll1Click
    end
    object Rotation1: TMenuItem
      Caption = 'Rotation'
      object suivantX1: TMenuItem
        Caption = 'X'
        OnClick = suivantX1Click
      end
      object suivantY1: TMenuItem
        Caption = 'Y'
        OnClick = suivantY1Click
      end
      object suivantZ1: TMenuItem
        Caption = 'Z'
        OnClick = suivantZ1Click
      end
      object rotation3D1: TMenuItem
        Caption = 'XY'
        OnClick = rotation3D1Click
      end
      object XZ2: TMenuItem
        Caption = 'XZ'
        OnClick = XZ2Click
      end
      object YZ2: TMenuItem
        Caption = 'YZ'
        OnClick = YZ2Click
      end
    end
    object Projection1: TMenuItem
      Caption = 'Projection'
      object XY1: TMenuItem
        Caption = 'XY'
        OnClick = XY1Click
      end
      object XZ1: TMenuItem
        Caption = 'XZ'
        OnClick = XZ1Click
      end
      object YZ1: TMenuItem
        Caption = 'YZ'
        OnClick = YZ1Click
      end
    end
    object Translation1: TMenuItem
      Caption = 'Translation'
      OnClick = Translation1Click
    end
    object N3: TMenuItem
      Caption = '-'
    end
    object N2: TMenuItem
      Caption = '-'
    end
    object Volumedevisualisation1: TMenuItem
      Caption = 'Volume de visualisation'
      Visible = False
    end
    object Rglagedelalumire1: TMenuItem
      Caption = 'Rendering parameters'
      OnClick = Rglagedelalumire1Click
    end
    object N4: TMenuItem
      Caption = '-'
    end
  end
end
