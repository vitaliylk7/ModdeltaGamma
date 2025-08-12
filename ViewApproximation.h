//---------------------------------------------------------------------------

#ifndef ViewApproximationH
#define ViewApproximationH
//---------------------------------------------------------------------------
#include <Classes.hpp>
#include <Controls.hpp>
#include <StdCtrls.hpp>
#include <Forms.hpp>
#include <Grids.hpp>
#include "dxCntner.hpp"
#include "dxInspct.hpp"
#include "ProcessWA.h"
#include "ProcessWA_BetaStep.h"
//---------------------------------------------------------------------------
class TfrmViewApproximation : public TForm
{
__published:	// IDE-managed Components
  TStringGrid *sg;
  TdxInspector *dxI;
  TdxInspectorTextRow *dxIRow;
  void __fastcall FormClose(TObject *Sender, TCloseAction &Action);
  void __fastcall FormShow(TObject *Sender);
private:	// User declarations
  int _type;  // 0 - �������. �� �����, 1 - �������. �� �������� �����
  String _NameView;
  // ��������� �� ������� ������� �������������
  const ProcessWA *_ProcessWA;
  // ������ ���������
  listProcessWA _listProcessWA;
  // �������� ������ ���������
  void ViewStandart();
public:		// User declarations
  __fastcall TfrmViewApproximation(TComponent* Owner,
    long TypeView, String Caption, const ProcessWA *ProcessWA_);
  __fastcall TfrmViewApproximation(TComponent* Owner,
    long TypeView, String Caption, const listProcessWA listProcessWA_);
};
//---------------------------------------------------------------------------
extern PACKAGE TfrmViewApproximation *frmViewApproximation;
//---------------------------------------------------------------------------
#endif
