//----------------------------------------------------------------------------
#ifndef ChooseVisualApproximationH
#define ChooseVisualApproximationH
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
class TfrmChooseVisualApproximation : public TForm
{
__published:        
	TButton *OKBtn;
	TButton *CancelBtn;
        TCheckListBox *chlCriterion;
        void __fastcall FormShow(TObject *Sender);
        void __fastcall OKBtnClick(TObject *Sender);
        void __fastcall CancelBtnClick(TObject *Sender);
private:
public:
        bool bOk;
	virtual __fastcall TfrmChooseVisualApproximation(TComponent* AOwner);
};
//----------------------------------------------------------------------------
extern PACKAGE TfrmChooseVisualApproximation *frmChooseVisualApproximation;
//----------------------------------------------------------------------------
#endif    
