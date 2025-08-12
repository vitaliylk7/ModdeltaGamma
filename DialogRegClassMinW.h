//---------------------------------------------------------------------------

#ifndef DialogRegClassMinWH
#define DialogRegClassMinWH
//---------------------------------------------------------------------------
#include <Classes.hpp>
#include <Controls.hpp>
#include <StdCtrls.hpp>
#include <Forms.hpp>
#include <Grids.hpp>
//---------------------------------------------------------------------------
class TfrmDialogRegClassMinW : public TForm
{
__published:	// IDE-managed Components
  TButton *Ok;
  TStringGrid *sg;
  TGroupBox *GroupBox1;
  TEdit *edMinW;
  TButton *Button2;
  void __fastcall FormCreate(TObject *Sender);
  void __fastcall OkClick(TObject *Sender);
  void __fastcall FormShow(TObject *Sender);
private:	// User declarations
  float _ClassMinW, _ClassStMinW;
  void __fastcall SetClassMinW(float value);
  float __fastcall GetClassMinW();
public:		// User declarations
  __fastcall TfrmDialogRegClassMinW(TComponent* Owner);
  // Добавить справочную информацию
  void __fastcall Add(String Class, float Min, float Max);
  __property float ClassMinW  = { read=GetClassMinW, write=SetClassMinW };
};
//---------------------------------------------------------------------------
extern PACKAGE TfrmDialogRegClassMinW *frmDialogRegClassMinW;
//---------------------------------------------------------------------------
#endif
