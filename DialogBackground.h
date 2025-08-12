//----------------------------------------------------------------------------
#ifndef DialogBackgroundH
#define DialogBackgroundH
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
#include <Grids.hpp>
struct Background {
  float T;
  float W;
};
//----------------------------------------------------------------------------
class TfrmDialogBackground : public TForm
{
__published:        
	TButton *OKBtn;
	TButton *CancelBtn;
	TBevel *Bevel1;
  TStringGrid *sg;
  void __fastcall FormCreate(TObject *Sender);
  void __fastcall OKBtnClick(TObject *Sender);
  void __fastcall CancelBtnClick(TObject *Sender);
private:
public:
	virtual __fastcall TfrmDialogBackground(TComponent* AOwner);
  // Добавить признак
  void Add(String Name);
  // Получить значения анизотропии для признака
  Background getBackground(String Name);
};
//----------------------------------------------------------------------------
//extern PACKAGE TfrmDialogBackground *frmDialogBackground;
//----------------------------------------------------------------------------
#endif    
