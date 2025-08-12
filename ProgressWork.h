//---------------------------------------------------------------------------

#ifndef ProgressWorkH
#define ProgressWorkH
//---------------------------------------------------------------------------
#include <Classes.hpp>
#include <Controls.hpp>
#include <StdCtrls.hpp>
#include <Forms.hpp>
#include <ComCtrls.hpp>
#include "CGAUGES.h"
//---------------------------------------------------------------------------
class TfrmProgressWork : public TForm
{
__published:	// IDE-managed Components
        TCGauge *pb;
private:	// User declarations
public:		// User declarations
        __fastcall TfrmProgressWork(TComponent* Owner);
};
//---------------------------------------------------------------------------
extern PACKAGE TfrmProgressWork *frmProgressWork;
//---------------------------------------------------------------------------
#endif
