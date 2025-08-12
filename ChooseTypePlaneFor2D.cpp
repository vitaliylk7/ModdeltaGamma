//---------------------------------------------------------------------
#include <vcl.h>
#pragma hdrstop

#include "ChooseTypePlaneFor2D.h"
//--------------------------------------------------------------------- 
#pragma resource "*.dfm"
TfrmChooseTypePlaneFor2D *frmChooseTypePlaneFor2D;
//---------------------------------------------------------------------
__fastcall TfrmChooseTypePlaneFor2D::TfrmChooseTypePlaneFor2D(TComponent* AOwner)
	: TForm(AOwner)
{
}
//---------------------------------------------------------------------
void __fastcall TfrmChooseTypePlaneFor2D::FormClose(TObject *Sender,
      TCloseAction &Action)
{
	Action = caFree;
}
//---------------------------------------------------------------------------


