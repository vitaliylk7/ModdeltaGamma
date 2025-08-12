//---------------------------------------------------------------------
#include <vcl.h>
#pragma hdrstop

#include "CheckTypeProcess.h"
//---------------------------------------------------------------------
#pragma resource "*.dfm"
TfrmCheckTypeProcess *frmCheckTypeProcess;
//--------------------------------------------------------------------- 
__fastcall TfrmCheckTypeProcess::TfrmCheckTypeProcess(TComponent* AOwner)
	: TForm(AOwner)
{
}
//---------------------------------------------------------------------

void __fastcall TfrmCheckTypeProcess::FormClose(TObject *Sender,
      TCloseAction &Action)
{
	Action = caFree;        
}
//---------------------------------------------------------------------------

