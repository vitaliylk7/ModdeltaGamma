//---------------------------------------------------------------------------

#ifndef DataViewH
#define DataViewH
//---------------------------------------------------------------------------
#include <Classes.hpp>
#include <Controls.hpp>
#include <StdCtrls.hpp>
#include <Forms.hpp>
#include <Grids.hpp>

//---------------------------------------------------------------------------
class TfrmDataView : public TForm
{
__published:	// IDE-managed Components
        TStringGrid *sg;
        void __fastcall FormClose(TObject *Sender, TCloseAction &Action);
        void __fastcall FormShow(TObject *Sender);
private:	// User declarations
public:		// User declarations
        __fastcall TfrmDataView(TComponent* Owner);
};
//---------------------------------------------------------------------------
extern PACKAGE TfrmDataView *frmDataView;
//---------------------------------------------------------------------------
#endif
