//---------------------------------------------------------------------------

#include <vcl.h>
#pragma hdrstop

#include "MainDataModul.h"
//---------------------------------------------------------------------------
#pragma package(smart_init)
#pragma resource "*.dfm"
TdmGlobal *dmGlobal;
//---------------------------------------------------------------------------
__fastcall TdmGlobal::TdmGlobal(TComponent* Owner)
        : TDataModule(Owner)
{
}
//---------------------------------------------------------------------------
