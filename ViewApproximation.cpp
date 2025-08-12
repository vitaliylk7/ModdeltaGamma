//---------------------------------------------------------------------------
#include <vcl.h>
#pragma hdrstop
#include "ViewApproximation.h"
//---------------------------------------------------------------------------
#pragma package(smart_init)
#pragma link "dxCntner"
#pragma link "dxInspct"
#pragma resource "*.dfm"
TfrmViewApproximation *frmViewApproximation;
//---------------------------------------------------------------------------
__fastcall TfrmViewApproximation::TfrmViewApproximation(TComponent* Owner,
    long TypeView, String Caption, const ProcessWA *ProcessWA_)
     : TForm(Owner)
{
  _NameView = Caption;
  _ProcessWA = ProcessWA_;
  _type = TypeView;
}
//---------------------------------------------------------------------------
// Конструктор
//---------------------------------------------------------------------------
__fastcall TfrmViewApproximation::TfrmViewApproximation(TComponent* Owner,
  long TypeView, String Caption, const listProcessWA listProcessWA_)
    : TForm(Owner)
{
  _listProcessWA = listProcessWA_;
  _NameView = Caption;
  _type = TypeView;
}
//---------------------------------------------------------------------------
void __fastcall TfrmViewApproximation::FormClose(TObject *Sender,
      TCloseAction &Action)
{
	Action = caFree;
}
//---------------------------------------------------------------------------
// Показать данные вес. аппр. на исходные точки в таблице
//---------------------------------------------------------------------------
void TfrmViewApproximation::ViewStandart() {
  Caption = _NameView;
  objData _objDataStandart;
  long CountRow;
  long CountColumn;
  int tmpT;
  const ProcessWA* processWA = *_listProcessWA.begin();
  int countBetaSteps = _listProcessWA.size();

  CountRow = processWA->getStCountRec();
  CountColumn = processWA->getStCountCol();
  dxIRow->Text = IntToStr(CountRow);
  //                                кол-во колоно для каждого значения бета
  sg->ColCount = 5 + (CountColumn * 3 * countBetaSteps) + countBetaSteps;
  sg->RowCount = CountRow + 1;
  sg->Cells[0][0] = "№";
  sg->Cells[1][0] = "x";
  sg->Cells[2][0] = "y";
  sg->Cells[3][0] = "z";
  long sgCountColumn = sg->ColCount;
  String s;

  int col = 4;
  for (iterProcessWA _iterProcessWA = _listProcessWA.begin();
      _iterProcessWA != _listProcessWA.end();  ++_iterProcessWA)
  {
    processWA = *_iterProcessWA;
    sg->Cells[col][0] = "W (beta:"
      + FormatFloat("0.00",processWA->getBeta()) + ")";
    ++col;
    for (int colCharacters = 0; colCharacters < CountColumn; ++col,
      ++colCharacters)
    {
      s = processWA->getStNameCol(colCharacters);
      sg->Cells[col][0] = s;
      ++col;
      sg->Cells[col][0] = "T (" + s + ")";
      ++col;
      sg->Cells[col][0] = "d (" + s + ")";
      ++col;
      sg->Cells[col][0] = "e (" + s + ")";
    }
  }


  for (int rec = 0; rec < CountRow; ++rec)
  {
    _objDataStandart = processWA->getStXYZ(rec);
    sg->Cells[0][rec + 1] = IntToStr(rec + 1);
    sg->Cells[1][rec + 1] = FormatFloat("0.00000",_objDataStandart.x);
    sg->Cells[2][rec + 1] = FormatFloat("0.00000",_objDataStandart.y);
    sg->Cells[3][rec + 1] = FormatFloat("0.00000",_objDataStandart.z);

    int sgCurrentCol = 4;
    for (iterProcessWA _iterProcessWA = _listProcessWA.begin();
      _iterProcessWA != _listProcessWA.end();  ++_iterProcessWA)
    {
      processWA = *_iterProcessWA;
      // W
      sg->Cells[sgCurrentCol][rec + 1] =
        FormatFloat("0.00000",processWA->getStW(rec));
      ++sgCurrentCol;
      for (long col = 0; col < CountColumn; ++col) {
        // Real value
        sg->Cells[sgCurrentCol][rec + 1] =
          FormatFloat("0.00000",processWA->getRealValue(col, rec));
        ++sgCurrentCol;
        // T
        sg->Cells[sgCurrentCol][rec + 1] =
          FormatFloat("0.00000",processWA->getStT(col, rec));
        ++sgCurrentCol;
        // D
        sg->Cells[sgCurrentCol][rec + 1] =
          FormatFloat("0.00000",processWA->getD(col, rec));
        ++sgCurrentCol;
        // E
        sg->Cells[sgCurrentCol][rec + 1] =
          FormatFloat("0.00000",processWA->getE(col, rec));
        ++sgCurrentCol;
      }
    }
  }
}
//---------------------------------------------------------------------------
void __fastcall TfrmViewApproximation::FormShow(TObject *Sender)
{
   ViewStandart();
}
//---------------------------------------------------------------------------

