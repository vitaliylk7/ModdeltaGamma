//---------------------------------------------------------------------------
#include <vcl.h>
#pragma hdrstop
#include "ViewApproximationLevels.h"
//---------------------------------------------------------------------------
#pragma package(smart_init)
#pragma link "dxCntner"
#pragma link "dxInspct"
#pragma resource "*.dfm"
TfrmViewApproximationLevels *frmViewApproximationLevels;
//---------------------------------------------------------------------------
__fastcall TfrmViewApproximationLevels::TfrmViewApproximationLevels(TComponent* Owner, long TypeView, String NameView, const WeigthApproximationLevelsProcess* WeigthApproximationProcess_)
        : TForm(Owner)
{
  _WeigthApproximationProcess = WeigthApproximationProcess_;
  _type = TypeView;
  _NameView = NameView;
}
//---------------------------------------------------------------------------
void __fastcall TfrmViewApproximationLevels::FormClose(TObject *Sender,
      TCloseAction &Action)
{
	Action = caFree;
}
//---------------------------------------------------------------------------// Показать данные весовой аппроксимации
void TfrmViewApproximationLevels::ViewApproximation()
{
  Caption = _NameView;
  objData _objNet;
  long CountRow;
  long CountColumnAprox;
  int tmpT;

  CountRow = _WeigthApproximationProcess->getCountRows();
  CountColumnAprox = _WeigthApproximationProcess->getCountColumns();
  dxIRow->Text = IntToStr(CountRow);

  sg->ColCount = 5 + CountColumnAprox;
  sg->RowCount = CountRow + 1;
  sg->Cells[0][0] = "№";
  sg->Cells[1][0] = "x";
  sg->Cells[2][0] = "y";
  sg->Cells[3][0] = "z";
  sg->Cells[4][0] = "Norma";
  long sgColumn = 5;
  String s;
  for (long i = 0; i < CountColumnAprox; i++){
    s = _WeigthApproximationProcess->getColumnName(i);
    sg->Cells[sgColumn][0] = s;
    sgColumn++;
  }

  for (long i = 0; i < CountRow; i++){
   _objNet = _WeigthApproximationProcess->getXYZ(i);
   sg->Cells[0][i+1] = IntToStr(i+1);
   sg->Cells[1][i+1] = FormatFloat("0.00",_objNet.x);
   sg->Cells[2][i+1] = FormatFloat("0.00",_objNet.y);
   sg->Cells[3][i+1] = FormatFloat("0.00",_objNet.z);
   sg->Cells[4][i+1] = FormatFloat("0.00",_WeigthApproximationProcess->getNorma(i));
   long sgColumn = 5;
   for (long x = 0; x < CountColumnAprox; x++){
     sg->Cells[sgColumn][i+1] = FormatFloat("0.00",_WeigthApproximationProcess->getT(x,i));
     sgColumn++;
   }
  }
}
//---------------------------------------------------------------------------
// Показать данные стандарта
//---------------------------------------------------------------------------
void TfrmViewApproximationLevels::ViewStandart()
{

  Caption = _NameView;
  objData _objDataStandart;
  long CountRow;
  long CountColumnAprox;
  int tmpT;

  CountRow = _WeigthApproximationProcess->getStandartCountRows();
  CountColumnAprox = _WeigthApproximationProcess->getStandartCountColumns();
  dxIRow->Text = IntToStr(CountRow);

  sg->ColCount = 5 + CountColumnAprox;
  sg->RowCount = CountRow + 1;
  sg->Cells[0][0] = "№";
  sg->Cells[1][0] = "x";
  sg->Cells[2][0] = "y";
  sg->Cells[3][0] = "z";
  sg->Cells[4][0] = "Norma";
  long sgColumn = 5;
  String s;
  for (long i = 0; i < CountColumnAprox; i++){
    s = _WeigthApproximationProcess->getStandartColumnName(i);
    sg->Cells[sgColumn][0] = s;
    sgColumn++;
  }

  for (long i = 0; i < CountRow; i++){
   _objDataStandart = _WeigthApproximationProcess->getStandartXYZ(i);
   sg->Cells[0][i+1] = IntToStr(i+1);
   sg->Cells[1][i+1] = FormatFloat("0.00",_objDataStandart.x);
   sg->Cells[2][i+1] = FormatFloat("0.00",_objDataStandart.y);
   sg->Cells[3][i+1] = FormatFloat("0.00",_objDataStandart.z);
   sg->Cells[4][i+1] = FormatFloat("0.00",_WeigthApproximationProcess->getStandartNorma(i));
   long sgColumn = 5;
   for (long x = 0; x < CountColumnAprox; x++){
     sg->Cells[sgColumn][i+1] = FormatFloat("0.00",_WeigthApproximationProcess->getStandartT(x,i));
     sgColumn++;
   }
  }
}
//---------------------------------------------------------------------------
void __fastcall TfrmViewApproximationLevels::FormShow(TObject *Sender)
{
  if (0 == _type)
    ViewApproximation();
  else
  if (1 == _type)
    ViewStandart();

}
//---------------------------------------------------------------------------

