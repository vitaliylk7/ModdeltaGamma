//---------------------------------------------------------------------------

#include <vcl.h>
#pragma hdrstop

#include "DialogRegClassMinW.h"
//---------------------------------------------------------------------------
#pragma package(smart_init)
#pragma resource "*.dfm"
TfrmDialogRegClassMinW *frmDialogRegClassMinW;
//---------------------------------------------------------------------------
__fastcall TfrmDialogRegClassMinW::TfrmDialogRegClassMinW(TComponent* Owner)
  : TForm(Owner)
{
  ClassMinW = 0;
}
//---------------------------------------------------------------------------
// Добавить справочную информацию
//---------------------------------------------------------------------------
void __fastcall TfrmDialogRegClassMinW::Add(String Class, float Min, float Max)
{
  if (sg->Cells[0][1] != "")
  {
    ++sg->RowCount;
    this->ClassMinW = Min;
  }

  int Rec = sg->RowCount - 1;
  sg->Cells[0][Rec] = Class;
  sg->Cells[1][Rec] = FormatFloat("0.0000", Min);
  sg->Cells[2][Rec] = FormatFloat("0.0000", Max);

  if (ClassMinW > Min)
    this->ClassMinW = Min;
}
//---------------------------------------------------------------------------
void __fastcall TfrmDialogRegClassMinW::FormCreate(TObject *Sender)
{
  sg->ColCount = 3;
  sg->RowCount = 2;
  sg->FixedCols = 1;
  sg->FixedRows = 1;
  sg->Cells[0][0] = "Класс";
  sg->Cells[1][0] = "Min (сетка)";
  sg->Cells[2][0] = "Max (сетка)";
}
//---------------------------------------------------------------------------
void __fastcall TfrmDialogRegClassMinW::SetClassMinW(float value)
{
  if(_ClassMinW != value) {
    _ClassMinW = value;
  }
}
//---------------------------------------------------------------------------
float __fastcall TfrmDialogRegClassMinW::GetClassMinW()
{
  return _ClassMinW;
}
//---------------------------------------------------------------------------
void __fastcall TfrmDialogRegClassMinW::OkClick(TObject *Sender)
{
  try
  {
    ClassMinW = StrToFloat(edMinW->Text);
    this->Close();
  }
  catch(...)
  {
    ShowMessage("Значение Min W имеет не допустимое значение");
  }
}
//---------------------------------------------------------------------------


void __fastcall TfrmDialogRegClassMinW::FormShow(TObject *Sender)
{
  edMinW->Text = FormatFloat("0.0000", ClassMinW);
}
//---------------------------------------------------------------------------

