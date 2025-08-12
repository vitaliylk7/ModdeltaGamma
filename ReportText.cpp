//---------------------------------------------------------------------------
#include <vcl.h>
#include <dir.h>
#pragma hdrstop
#include "ReportText.h"
#include "Utils.h"
//---------------------------------------------------------------------------
#pragma package(smart_init)
#pragma link "SHDocVw_OCX"
#pragma resource "*.dfm"
TfrmReportText *frmReportText;
//---------------------------------------------------------------------------
__fastcall TfrmReportText::TfrmReportText(TComponent* Owner, const String Caption_,
  	const TStrings *html)
	: TForm(Owner)
{
	this->Caption = Caption_;
  char buffer[MAXPATH];
  getcwd(buffer, MAXPATH);
  String s = buffer;

  TVariant URL = s + "\\temp.html";
  html->SaveToFile(URL);
  Browser->Navigate(URL);
}
//---------------------------------------------------------------------------
void __fastcall TfrmReportText::FormClose(TObject *Sender,
      TCloseAction &Action)
{
	Action = caFree;
}


