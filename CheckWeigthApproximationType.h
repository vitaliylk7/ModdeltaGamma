//----------------------------------------------------------------------------
#ifndef CheckWeigthApproximationTypeH
#define CheckWeigthApproximationTypeH
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
class TfrmCheckWeigthApproximationType : public TForm
{
__published:
	TButton *OKBtn;
	TButton *CancelBtn;
        TRadioGroup *rgTypeWeightApproximation;
        TGroupBox *GroupBox1;
        TEdit *edCountLevels;
        TLabel *Label1;
        void __fastcall FormClose(TObject *Sender, TCloseAction &Action);
private:
public:
	virtual __fastcall TfrmCheckWeigthApproximationType(TComponent* AOwner);
};
//----------------------------------------------------------------------------
extern PACKAGE TfrmCheckWeigthApproximationType *frmCheckWeigthApproximationType;
//----------------------------------------------------------------------------
#endif    
