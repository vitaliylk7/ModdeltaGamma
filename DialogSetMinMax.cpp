//---------------------------------------------------------------------
#include <vcl.h>
#pragma hdrstop

#include "DialogSetMinMax.h"
//---------------------------------------------------------------------
#pragma resource "*.dfm"
TfrmDialogSetMinMax *frmDialogSetMinMax;
//--------------------------------------------------------------------- 
__fastcall TfrmDialogSetMinMax::TfrmDialogSetMinMax(TComponent* AOwner,
  	String Caption_)	: TForm(AOwner)
{
	this->Caption = Caption_;
}
//---------------------------------------------------------------------
void __fastcall TfrmDialogSetMinMax::FormClose(TObject *Sender,
      TCloseAction &Action)
{
	if (Min->Text == "")
		Min->Text = "0";

	if (Max->Text == "")
		Max->Text = "0";

	Action = caFree;
}
//---------------------------------------------------------------------------

