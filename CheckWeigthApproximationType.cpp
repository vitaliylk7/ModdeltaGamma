//---------------------------------------------------------------------
#include <vcl.h>
#pragma hdrstop

#include "CheckWeigthApproximationType.h"
//---------------------------------------------------------------------
#pragma resource "*.dfm"
TfrmCheckWeigthApproximationType *frmCheckWeigthApproximationType;
//--------------------------------------------------------------------- 
__fastcall TfrmCheckWeigthApproximationType::TfrmCheckWeigthApproximationType(TComponent* AOwner)
	: TForm(AOwner)
{
}
//---------------------------------------------------------------------
void __fastcall TfrmCheckWeigthApproximationType::FormClose(
      TObject *Sender, TCloseAction &Action)
{
	Action = caFree;                
}
//---------------------------------------------------------------------------



