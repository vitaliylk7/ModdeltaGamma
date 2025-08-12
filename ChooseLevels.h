//----------------------------------------------------------------------------
#ifndef ChooseLevelsH
#define ChooseLevelsH
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
class TfrmChooseLevels : public TForm
{
__published:        
	TButton *OKBtn;
	TButton *CancelBtn;
        TLabel *Label1;
        TListBox *ListBox;
        void __fastcall FormClose(TObject *Sender, TCloseAction &Action);
private:
        int _CountLevels;
        void __fastcall SetCountLevels(int value);
        int __fastcall GetCountLevels();
        void CreateLevels();
public:
	virtual __fastcall TfrmChooseLevels(TComponent* AOwner,
  	String Caption_);
        __property int CountLevels  = { read=GetCountLevels, write=SetCountLevels };
};
//----------------------------------------------------------------------------
extern PACKAGE TfrmChooseLevels *frmChooseLevels;
//----------------------------------------------------------------------------
#endif    
