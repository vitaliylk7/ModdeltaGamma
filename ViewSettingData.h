//---------------------------------------------------------------------------

#ifndef ViewSettingDataH
#define ViewSettingDataH
//---------------------------------------------------------------------------
#include <Classes.hpp>
#include <Controls.hpp>
#include <StdCtrls.hpp>
#include <Forms.hpp>
#include "dxCntner.hpp"
#include "dxInspct.hpp"
#include <CheckLst.hpp>
#include <ExtCtrls.hpp>
#include "dxInspRw.hpp"
#include <ImgList.hpp>
#include <Grids.hpp>
#include <AppEvnts.hpp>
#include "FormSettings.h"
#include "SettingsApprox2D3D.h"
#include "SettingsDynCreate.h"
#include "Data.h"
#include <Buttons.hpp>
#include "DialogBackground.h"
#include <Menus.hpp>
#include "Main.h"

//---------------------------------------------------------------------------
class TfrmViewSettingData : public TfrmFormSettings
{
__published:	// IDE-managed Components
        TdxInspector *dxI;
        TPanel *Panel1;
        TLabel *Label1;
        TdxInspectorTextRow *dxIPosition;
        TdxInspectorTextPickRow *dxIX;
        TdxInspectorTextPickRow *dxIY;
        TdxInspectorTextPickRow *dxIZ;
        TImageList *ImageList;
	TdxInspectorTextRow *dxIScopeAreaWA;
        TdxInspectorTextRow *dxIRow8;
        TdxInspectorTextRow *TillAreaX;
        TdxInspectorTextRow *dxIRow11;
        TdxInspectorTextRow *FromAreaY;
        TdxInspectorTextRow *TillAreaY;
        TdxInspectorTextRow *dxIRow14;
        TdxInspectorTextRow *FromAreaZ;
        TdxInspectorTextRow *TillAreaZ;
        TCheckListBox *chCriterion;
	TdxInspectorTextRow *dxICategorySettingsWA;
        TdxInspectorTextRow *dxIAlpha;
        TdxInspectorTextRow *dxIGamma;
  TdxInspectorTextRow *dxIBeta;
        TSplitter *Splitter1;
        TdxInspectorTextMaskRow *FromAreaX;
	TdxInspectorTextRow *dxIScope;
        TdxInspectorTextRow *dxIPointX;
        TdxInspectorTextRow *FromDataX;
        TdxInspectorTextRow *TillDataX;
        TdxInspectorTextRow *dxIPontY;
        TdxInspectorTextRow *FromDataY;
        TdxInspectorTextRow *TillDataY;
        TdxInspectorTextRow *PointZ;
        TdxInspectorTextRow *FromDataZ;
        TdxInspectorTextRow *TillDataZ;
  TPanel *Panel2;
  TSpeedButton *bEnterAnisotropy;
  TdxInspectorTextRow *dxIRow35;
  TdxInspectorTextRow *xAnisotropyFactor;
  TdxInspectorTextRow *yAnisotropyFactor;
  TdxInspectorTextRow *zAnisotropyFactor;
  TdxInspectorTextRow *dxIBetaFrom;
  TdxInspectorTextRow *dxIBetaTo;
  TdxInspectorTextRow *dxIBetaStep;
        TdxInspectorTextRow *dxISigma;
        TdxInspectorTextRow *NumbPointsData;
        TdxInspectorTextRow *NumbPointsArea;
        TPopupMenu *PopupMenu1;
        TMenuItem *pmCalculationXYZ;
        TMenuItem *N1;
        void __fastcall FormClose(TObject *Sender, TCloseAction &Action);
        void __fastcall FormShow(TObject *Sender);
        void __fastcall dxIXChange(TObject *Sender);
        void __fastcall dxIYChange(TObject *Sender);
        void __fastcall dxIZChange(TObject *Sender);
        void __fastcall dxIEdited(TObject *Sender, TdxInspectorNode *Node,
          TdxInspectorRow *Row);
  void __fastcall bEnterAnisotropyClick(TObject *Sender);
  void __fastcall FormDestroy(TObject *Sender);
        void __fastcall dxIKeyPress(TObject *Sender, char &Key);
        void __fastcall pmCalculationXYZClick(TObject *Sender);
        void __fastcall dxIExit(TObject *Sender);
        void __fastcall BitBtn1Click(TObject *Sender);
        void __fastcall BitBtn2Click(TObject *Sender);
        void __fastcall FromDataXChange(TObject *Sender);
        void __fastcall FromDataXValidate(TObject *Sender,
          AnsiString &ErrorText, bool &Accept);
        void __fastcall N1Click(TObject *Sender);
private:	// User declarations
  bool bX;
  bool bY;
  bool bZ;
  // ���������� ����� �������� � �������� �������
  //long CountPointData;
  //long CountPointArea;
  // ����� �������� ��� ��������� ������
  SettingsApprox2D3D* _SettingsApprox2D3D;
  // ����� ������
  Data* _Data;
  // ����� �������
  TSettingsDynCreate* SettingsDynCreate;
  // ��������� ������ (������)
  String LevelCaption;
  // ���� ����
  TfrmDialogBackground *frmDialogBackground;
  // �������� x
  void update_x();
  // �������� y
  void update_y();
  // �������� z
  void update_z();
  // ����������� ���������� ����� ���������� � �������
  void Change(String type, String sx1, String sx2, String sy1, String sy2,
              String sz1, String sz2);
   // ������� ��������� x, y, z .
  long colX;
  long colY;
  long colZ;
  public:		// User declarations
        __fastcall TfrmViewSettingData(TComponent* Owner,
        	SettingsApprox2D3D* SettingsApprox2D3D_, Data* Data_,
          String LevelCaption_);
        // ������ �������� � �������� ���������
        void __fastcall setSettingData(void);
  long getCountPointData(void);
  long getCountPointArea(void);
};
//---------------------------------------------------------------------------
extern PACKAGE TfrmViewSettingData *frmViewSettingData;
//---------------------------------------------------------------------------
#endif
