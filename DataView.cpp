//---------------------------------------------------------------------------

#include <vcl.h>
#pragma hdrstop

#include "DataView.h"
#include "Main.h"
//---------------------------------------------------------------------------
#pragma package(smart_init)
#pragma resource "*.dfm"
TfrmDataView *frmDataView;
//---------------------------------------------------------------------------
__fastcall TfrmDataView::TfrmDataView(TComponent* Owner)
        : TForm(Owner)
{
}
//---------------------------------------------------------------------------
void __fastcall TfrmDataView::FormClose(TObject *Sender,
      TCloseAction &Action)
{
	Action = caFree;                
}
//---------------------------------------------------------------------------
void __fastcall TfrmDataView::FormShow(TObject *Sender)
{

  long lx = frmMain->fData->getCountColumn();
  long ly = frmMain->fData->getCountRecord();
  sg->ColCount = lx+1;
  sg->RowCount = ly+1;
  sg->Cells[0][0] = "¹";
  for (long x = 0; x < lx; x++)
   sg->Cells[x+1][0] = frmMain->fData->getColumnName(x);

  for (long y = 0; y < ly; y++){
   sg->Cells[0][y+1] = IntToStr(y+1);
   for (long x = 0; x < lx; x++){
    sg->Cells[x+1][y+1] = FormatFloat("0.00000",frmMain->fData->getData(x,y));
   }
  }
}
//---------------------------------------------------------------------------
