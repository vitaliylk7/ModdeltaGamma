//----------------------------------------------------------------------------
#ifndef ChooseTypePlaneFor2DH
#define ChooseTypePlaneFor2DH
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
//----------------------------------------------------------------------------
class TfrmChooseTypePlaneFor2D : public TForm
{
__published:        
	TButton *OKBtn;
	TButton *CancelBtn;
        TRadioGroup *rgChooseTypePlaneFor2D;
        void __fastcall FormClose(TObject *Sender, TCloseAction &Action);
private:
public:
	virtual __fastcall TfrmChooseTypePlaneFor2D(TComponent* AOwner);
};
//----------------------------------------------------------------------------
extern PACKAGE TfrmChooseTypePlaneFor2D *frmChooseTypePlaneFor2D;
//----------------------------------------------------------------------------
#endif    
