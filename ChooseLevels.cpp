//---------------------------------------------------------------------
#include <vcl.h>
#pragma hdrstop

#include "ChooseLevels.h"
//--------------------------------------------------------------------- 
#pragma resource "*.dfm"
TfrmChooseLevels *frmChooseLevels;
//---------------------------------------------------------------------
__fastcall TfrmChooseLevels::TfrmChooseLevels(TComponent* AOwner,
  	String Caption_)
	: TForm(AOwner)
{
	this->Caption = Caption_;
  CountLevels = 0;
}
//---------------------------------------------------------------------
void __fastcall TfrmChooseLevels::FormClose(TObject *Sender,
      TCloseAction &Action)
{
  Action = caFree;
}
//---------------------------------------------------------------------------
void __fastcall TfrmChooseLevels::SetCountLevels(int value)
{
	if(_CountLevels != value)
  {
		_CountLevels = value;
		CreateLevels();
	}
}
//---------------------------------------------------------------------------
int __fastcall TfrmChooseLevels::GetCountLevels()
{
        return _CountLevels;
}
//---------------------------------------------------------------------------
void TfrmChooseLevels::CreateLevels()
{
  ListBox->Clear();
  ListBox->Items->Add("Общий");
  for (int i = 0; i < _CountLevels; i++)
  {
    ListBox->Items->Add("Уровень " + IntToStr(i+1));
  }
}
