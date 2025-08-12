//---------------------------------------------------------------------------

#include <vcl.h>
#pragma hdrstop

#include "SettingsFile.h"
#include "Main.h"
//---------------------------------------------------------------------------
#pragma package(smart_init)
#pragma link "dxCntner"
#pragma link "dxInspct"
#pragma resource "*.dfm"
TfrmSettingsFile *frmSettingsFile;
//---------------------------------------------------------------------------
__fastcall TfrmSettingsFile::TfrmSettingsFile(TComponent* Owner)
        : TForm(Owner)
{
}
//---------------------------------------------------------------------------
void __fastcall TfrmSettingsFile::FormShow(TObject *Sender)
{
 long lColumn = frmMain->fData->getCountColumn();
 dxIFile->Text = frmMain->fData->getFileName();
 dxIColumn->Text = IntToStr(lColumn);
 dxIRow->Text = IntToStr(frmMain->fData->getCountRecord());
 sg->Cells[0][0] = "Название";
 sg->Cells[1][0] = "Min";
 sg->Cells[2][0] = "Max";
 sg->RowCount = lColumn+1;
 for (long i = 0; i < lColumn; i++){
   sg->Cells[0][i+1] = frmMain->fData->getColumnName(i);
   sg->Cells[1][i+1] = FormatFloat("0.00000",frmMain->fData->getMin(i));
   sg->Cells[2][i+1] = FormatFloat("0.00000",frmMain->fData->getMax(i));
 }
}
//---------------------------------------------------------------------------
void __fastcall TfrmSettingsFile::FormClose(TObject *Sender,
      TCloseAction &Action)
{
	Action = caFree;
}
//---------------------------------------------------------------------------
