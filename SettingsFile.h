//---------------------------------------------------------------------------

#ifndef SettingsFileH
#define SettingsFileH
//---------------------------------------------------------------------------
#include <Classes.hpp>
#include <Controls.hpp>
#include <StdCtrls.hpp>
#include <Forms.hpp>
#include "dxCntner.hpp"
#include "dxInspct.hpp"
#include <Grids.hpp>

//---------------------------------------------------------------------------
class TfrmSettingsFile : public TForm
{
__published:	// IDE-managed Components
        TStringGrid *sg;
        TdxInspector *dxInspector1;
        TdxInspectorTextRow *dxIRow;
        TdxInspectorTextRow *dxIFile;
        TdxInspectorTextRow *dxIColumn;
        void __fastcall FormShow(TObject *Sender);
        void __fastcall FormClose(TObject *Sender, TCloseAction &Action);
private:	// User declarations
public:		// User declarations
        __fastcall TfrmSettingsFile(TComponent* Owner);
};
//---------------------------------------------------------------------------
extern PACKAGE TfrmSettingsFile *frmSettingsFile;
//---------------------------------------------------------------------------
#endif
