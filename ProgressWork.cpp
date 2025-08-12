//---------------------------------------------------------------------------

#include <vcl.h>
#pragma hdrstop

#include "ProgressWork.h"
//---------------------------------------------------------------------------
#pragma package(smart_init)
#pragma link "CGAUGES"
#pragma resource "*.dfm"
TfrmProgressWork *frmProgressWork;
//---------------------------------------------------------------------------
__fastcall TfrmProgressWork::TfrmProgressWork(TComponent* Owner)
        : TForm(Owner)
{
}
//---------------------------------------------------------------------------
