//---------------------------------------------------------------------------

#ifndef ReportTextH
#define ReportTextH
//---------------------------------------------------------------------------
#include <Classes.hpp>
#include <Controls.hpp>
#include <StdCtrls.hpp>
#include <Forms.hpp>
#include <ExtCtrls.hpp>
#include <ComCtrls.hpp>
#include "SHDocVw_OCX.h"
#include <OleCtrls.hpp>
//---------------------------------------------------------------------------
class TfrmReportText : public TForm
{
__published:	// IDE-managed Components
  TCppWebBrowser *Browser;
	void __fastcall FormClose(TObject *Sender, TCloseAction &Action);
private:	// User declarations

public:		// User declarations
	__fastcall TfrmReportText(TComponent* Owner, const String Caption_,
  	const TStrings *html);
};
//---------------------------------------------------------------------------
extern PACKAGE TfrmReportText *frmReportText;
//---------------------------------------------------------------------------
#endif
