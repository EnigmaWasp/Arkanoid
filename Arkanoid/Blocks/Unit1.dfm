object Form1: TForm1
  Left = 263
  Top = 153
  BorderIcons = [biSystemMenu, biMinimize]
  BorderStyle = bsSingle
  Caption = 'Цвета'
  ClientHeight = 500
  ClientWidth = 300
  Color = clBtnFace
  Font.Charset = DEFAULT_CHARSET
  Font.Color = clWindowText
  Font.Height = -11
  Font.Name = 'MS Sans Serif'
  Font.Style = []
  OldCreateOrder = False
  PopupMenu = PopupMenu1
  OnKeyDown = FormKeyDown
  OnKeyUp = FormKeyUp
  PixelsPerInch = 96
  TextHeight = 13
  object Timer1: TTimer
    Interval = 300
    OnTimer = Timer1Timer
    Left = 275
  end
  object PopupMenu1: TPopupMenu
    Left = 245
    object N1: TMenuItem
      Caption = 'Новая'
      OnClick = N1Click
    end
  end
end
