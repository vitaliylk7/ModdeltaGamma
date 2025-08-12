object frmSettingsFile: TfrmSettingsFile
  Left = 192
  Top = 124
  Width = 544
  Height = 375
  Caption = 'Параметры файла'
  Color = clBtnFace
  Font.Charset = DEFAULT_CHARSET
  Font.Color = clWindowText
  Font.Height = -10
  Font.Name = 'MS Sans Serif'
  Font.Style = []
  FormStyle = fsMDIChild
  OldCreateOrder = False
  Position = poDefault
  Visible = True
  OnClose = FormClose
  OnShow = FormShow
  PixelsPerInch = 96
  TextHeight = 13
  object sg: TStringGrid
    Left = 0
    Top = 66
    Width = 536
    Height = 275
    Align = alClient
    Color = clInfoBk
    ColCount = 3
    DefaultColWidth = 100
    DefaultRowHeight = 20
    Options = [goFixedVertLine, goFixedHorzLine, goVertLine, goHorzLine, goRangeSelect, goColSizing]
    TabOrder = 0
  end
  object dxInspector1: TdxInspector
    Left = 0
    Top = 0
    Width = 536
    Height = 66
    Align = alTop
    TabOrder = 1
    DividerPos = 184
    Data = {
      420000000300000008000000000000000700000064784946696C650800000000
      00000009000000647849436F6C756D6E08000000000000000600000064784952
      6F7700000000}
    object dxIRow: TdxInspectorTextRow
      Caption = 'Количество строк'
      ReadOnly = True
    end
    object dxIFile: TdxInspectorTextRow
      Caption = 'Название файла'
      ReadOnly = True
    end
    object dxIColumn: TdxInspectorTextRow
      Caption = 'Количество признаков'
      ReadOnly = True
    end
  end
end
