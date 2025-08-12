//----------------------------------------------------------------------------
#ifndef CheckTypeProcessH
#define CheckTypeProcessH
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
class TfrmCheckTypeProcess : public TForm
{
__published:
	TButton *OKBtn;
	TButton *CancelBtn;
        TRadioGroup *rgTypeModel;
        void __fastcall FormClose(TObject *Sender, TCloseAction &Action);
private:
public:
	virtual __fastcall TfrmCheckTypeProcess(TComponent* AOwner);
};
//----------------------------------------------------------------------------
extern PACKAGE TfrmCheckTypeProcess *frmCheckTypeProcess;
//----------------------------------------------------------------------------
#endif    
