//---------------------------------------------------------------------
#include <vcl.h>
#pragma hdrstop

#include "ChooseVisualApproximation.h"
//--------------------------------------------------------------------- 
#pragma resource "*.dfm"
TfrmChooseVisualApproximation *frmChooseVisualApproximation;
//---------------------------------------------------------------------
__fastcall TfrmChooseVisualApproximation::TfrmChooseVisualApproximation(TComponent* AOwner)
	: TForm(AOwner)
{
}
//---------------------------------------------------------------------
void __fastcall TfrmChooseVisualApproximation::FormShow(TObject *Sender)
{
  bOk = false;
}
//---------------------------------------------------------------------------
void __fastcall TfrmChooseVisualApproximation::OKBtnClick(TObject *Sender)
{
  bOk = true;
}
//---------------------------------------------------------------------------
void __fastcall TfrmChooseVisualApproximation::CancelBtnClick(
      TObject *Sender)
{
  bOk = false;
}
//---------------------------------------------------------------------------


