//----------------------------------------------------------------------------
#ifndef DialogSetMinMaxH
#define DialogSetMinMaxH
//----------------------------------------------------------------------------
#include <vcl\ExtCtrls.hpp>
#include <vcl\Buttons.hpp>
#include <vcl\StdCtrls.hpp>
#include <vcl\Controls.hpp>
#include <vcl\Forms.hpp>
#include <vcl\Graphics.hpp>
#include <vcl\Classes.hpp>
#include <vcl\SysUtils.hpp>
#include <vcl\Windows.hpp>
#include <vcl\System.hpp>
//----------------------------------------------------------------------------
class TfrmDialogSetMinMax : public TForm
{
__published:
	TButton *OKBtn;
	TButton *CancelBtn;
	TEdit *Min;
	TLabel *Label1;
	TLabel *Label2;
	TEdit *Max;
	void __fastcall FormClose(TObject *Sender, TCloseAction &Action);
private:
public:
	virtual __fastcall TfrmDialogSetMinMax(TComponent* AOwner,
  	String Caption_);
};
//----------------------------------------------------------------------------
extern PACKAGE TfrmDialogSetMinMax *frmDialogSetMinMax;
//----------------------------------------------------------------------------
#endif    
