object frmViewApproximationLevels: TfrmViewApproximationLevels
  Left = 192
  Top = 124
  Width = 544
  Height = 375
  Caption = 'frmViewApproximationLevels'
  Color = clBtnFace
  Font.Charset = DEFAULT_CHARSET
  Font.Color = clWindowText
  Font.Height = -13
  Font.Name = 'MS Sans Serif'
  Font.Style = []
  FormStyle = fsMDIChild
  OldCreateOrder = False
  Position = poDefault
  Visible = True
  OnClose = FormClose
  OnShow = FormShow
  PixelsPerInch = 120
  TextHeight = 16
  object sg: TStringGrid
    Left = 0
    Top = 25
    Width = 536
    Height = 317
    Align = alClient
    Color = clInfoBk
    ColCount = 10
    DefaultRowHeight = 20
    RowCount = 2
    Options = [goFixedVertLine, goFixedHorzLine, goVertLine, goHorzLine, goRangeSelect, goColSizing]
    TabOrder = 0
  end
  object dxI: TdxInspector
    Left = 0
    Top = 0
    Width = 536
    Height = 25
    Align = alTop
    TabOrder = 1
    DividerPos = 184
    Data = {1A00000001000000080000000000000006000000647849526F7700000000}
    object dxIRow: TdxInspectorTextRow
      Caption = 'Колличество строк'
      ReadOnly = True
    end
  end
end
