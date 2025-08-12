//---------------------------------------------------------------------
#include <vcl.h>
#pragma hdrstop

#include "DialogBackground.h"
//--------------------------------------------------------------------- 
#pragma resource "*.dfm"
//TfrmDialogAnisotropy *frmDialogBackground;
//---------------------------------------------------------------------
__fastcall TfrmDialogBackground::TfrmDialogBackground(TComponent* AOwner)
	: TForm(AOwner)
{
}
//---------------------------------------------------------------------
// Добавить признак
//---------------------------------------------------------------------
void TfrmDialogBackground::Add(String Name)
{

  if (sg->Cells[0][1] != "")
    ++sg->RowCount;

  int Rec = sg->RowCount - 1;
  sg->Cells[0][Rec] = Name;
  sg->Cells[1][Rec] = "0";
  sg->Cells[2][Rec] = "0";
}
//---------------------------------------------------------------------
// Получить значения анизотропии для признака
//---------------------------------------------------------------------
Background TfrmDialogBackground::getBackground(String Name)
{
  Background _Background;
  for (int i = 1; i < sg->RowCount; ++i)
  {
    if (sg->Cells[0][i] == Name)
    {
      _Background.T = StrToFloat(sg->Cells[1][i]);
      _Background.W = StrToFloat(sg->Cells[2][i]);
      break;
    }
  }

  return _Background;
}
//---------------------------------------------------------------------
void __fastcall TfrmDialogBackground::FormCreate(TObject *Sender)
{
  sg->ColCount = 3;
  sg->RowCount = 2;
  sg->FixedCols = 1;
  sg->FixedRows = 1;
  sg->Cells[0][0] = "Признак";
  sg->Cells[1][0] = "Значение";
  sg->Cells[2][0] = "Вес";
}
//---------------------------------------------------------------------------

void __fastcall TfrmDialogBackground::OKBtnClick(TObject *Sender)
{
  Close();  
}
//---------------------------------------------------------------------------

void __fastcall TfrmDialogBackground::CancelBtnClick(TObject *Sender)
{
  Close();  
}
//---------------------------------------------------------------------------

