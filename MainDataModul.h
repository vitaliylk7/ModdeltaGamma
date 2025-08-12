//---------------------------------------------------------------------------

#ifndef MainDataModulH
#define MainDataModulH
//---------------------------------------------------------------------------
#include <Classes.hpp>
#include <Controls.hpp>
#include <StdCtrls.hpp>
#include <Forms.hpp>
#include <Dialogs.hpp>
//---------------------------------------------------------------------------
class TdmGlobal : public TDataModule
{
__published:	// IDE-managed Components
private:	// User declarations
public:		// User declarations
        __fastcall TdmGlobal(TComponent* Owner);
};
//---------------------------------------------------------------------------
extern PACKAGE TdmGlobal *dmGlobal;
//---------------------------------------------------------------------------
#endif
