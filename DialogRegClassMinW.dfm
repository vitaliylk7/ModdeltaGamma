object frmDialogRegClassMinW: TfrmDialogRegClassMinW
  Left = 192
  Top = 107
  BorderStyle = bsDialog
  Caption = 'Границы неклассифицированной области'
  ClientHeight = 280
  ClientWidth = 311
  Color = clBtnFace
  Font.Charset = DEFAULT_CHARSET
  Font.Color = clWindowText
  Font.Height = -11
  Font.Name = 'MS Sans Serif'
  Font.Style = []
  OldCreateOrder = False
  OnCreate = FormCreate
  OnShow = FormShow
  PixelsPerInch = 96
  TextHeight = 13
  object Ok: TButton
    Left = 80
    Top = 248
    Width = 75
    Height = 25
    Caption = 'Ok'
    TabOrder = 0
    OnClick = OkClick
  end
  object sg: TStringGrid
    Left = 8
    Top = 64
    Width = 297
    Height = 177
    ColCount = 3
    RowCount = 2
    TabOrder = 1
  end
  object GroupBox1: TGroupBox
    Left = 8
    Top = 4
    Width = 297
    Height = 57
    Caption = 'Границы неклассифицированной области'
    TabOrder = 2
    object edMinW: TEdit
      Left = 104
      Top = 23
      Width = 89
      Height = 21
      Hint = 
        'Точка с весом меньшим, чем минимальный относиться к нулевому кла' +
        'ссу'
      ParentShowHint = False
      ShowHint = True
      TabOrder = 0
    end
  end
  object Button2: TButton
    Left = 160
    Top = 248
    Width = 75
    Height = 25
    Caption = 'Cansel'
    TabOrder = 3
  end
end
