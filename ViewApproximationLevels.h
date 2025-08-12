//---------------------------------------------------------------------------

#ifndef ViewApproximationLevelsH
#define ViewApproximationLevelsH
//---------------------------------------------------------------------------
#include <Classes.hpp>
#include <Controls.hpp>
#include <StdCtrls.hpp>
#include <Forms.hpp>
#include <Grids.hpp>
#include "dxCntner.hpp"
#include "dxInspct.hpp"
#include "WeigthApproximationLevelsProcess.h"
//---------------------------------------------------------------------------
class TfrmViewApproximationLevels : public TForm
{
__published:	// IDE-managed Components
        TStringGrid *sg;
        TdxInspector *dxI;
        TdxInspectorTextRow *dxIRow;
        void __fastcall FormClose(TObject *Sender, TCloseAction &Action);
        void __fastcall FormShow(TObject *Sender);
private:	// User declarations
        int _type;
        String _NameView;
        // Указатель на процесс весовой аппроксимации
        const WeigthApproximationLevelsProcess* _WeigthApproximationProcess;
        // Показать данные весовой аппроксимации
        void ViewApproximation();
        // Показать данные стандарта
        void ViewStandart();
public:		// User declarations
        __fastcall TfrmViewApproximationLevels(TComponent* Owner, long TypeView, String NameView, const WeigthApproximationLevelsProcess* WeigthApproximationProcess_);
};
//---------------------------------------------------------------------------
extern PACKAGE TfrmViewApproximationLevels *frmViewApproximationLevels;
//---------------------------------------------------------------------------
#endif
