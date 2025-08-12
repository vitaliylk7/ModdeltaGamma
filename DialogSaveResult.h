//----------------------------------------------------------------------------
#ifndef DialogSaveResultH
#define DialogSaveResultH
//----------------------------------------------------------------------------
#include <vcl\System.hpp>
#include <vcl\Windows.hpp>
#include <vcl\SysUtils.hpp>
#include <vcl\Classes.hpp>
#include <vcl\Graphics.hpp>
#include <vcl\StdCtrls.hpp>
#include <vcl\Forms.hpp>
#include <vcl\Controls.hpp>
#include <vcl\Buttons.hpp>
#include <vcl\ExtCtrls.hpp>
#include <CheckLst.hpp>
//----------------------------------------------------------------------------
class TfrmDialogSaveResult : public TForm
{
__published:        
	TButton *OKBtn;
	TButton *CancelBtn;
        TCheckListBox *CheckListBox1;
        TLabel *Label1;
private:
public:
	virtual __fastcall TfrmDialogSaveResult(TComponent* AOwner);
};
//----------------------------------------------------------------------------
extern PACKAGE TfrmDialogSaveResult *frmDialogSaveResult;
//----------------------------------------------------------------------------
#endif    
