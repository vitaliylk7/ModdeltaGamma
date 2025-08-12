//---------------------------------------------------------------------------

#ifndef MainH
#define MainH
//---------------------------------------------------------------------------
#include <Classes.hpp>
#include <Controls.hpp>
#include <StdCtrls.hpp>
#include <Forms.hpp>
#include <ImgList.hpp>
#include <Dialogs.hpp>
#include <ComCtrls.hpp>

#include "dxBar.hpp"
#include "FactoryProcess.h"

//---------------------------------------------------------------------------
class TfrmMain : public TForm
{
__published:	// IDE-managed Components
        TdxBarManager *dxBarManager;
        TdxBarPopupMenu *dxBarPopupMenu;
        TdxBarButton *mOpen;
        TdxBarButton *mPrint;
        TdxBarButton *mExit;
        TdxBarButton *mHelp;
        TdxBarButton *mAbout;
        TdxBarSubItem *mFile;
        TdxBarSubItem *mService;
        TdxBarSubItem *dxBarSubItem1;
        TdxBarSubItem *dxBarSubItem2;
        TOpenDialog *OpenDialogFileData;
        TdxBarButton *mSettingsFile;
        TdxBarButton *mView;
        TImageList *ImageList;
        TdxBarButton *mCascade;
        TdxBarButton *mTileHoriz;
        TdxBarButton *mTileVert;
        TdxBarButton *mArrangeIcon;
        TdxBarSubItem *mStyle;
        TdxBarButton *mStyleStandart;
        TdxBarButton *mStyleFlat;
        TdxBarButton *mStyleEnhanced;
        TdxBarButton *dxProcess;
        TdxBarButton *dxTest;
        TdxBarButton *dxViewApproximation;
        TdxBarButton *mSaveAs;
        TStatusBar *StatusBar;
        TdxBarSubItem *mTypeModelling;
        TdxBarButton *mWeigthApproximation;
        void __fastcall mExitClick(TObject *Sender);
        void __fastcall mAboutClick(TObject *Sender);
        void __fastcall mOpenClick(TObject *Sender);
        void __fastcall mSettingsFileClick(TObject *Sender);
        void __fastcall mViewClick(TObject *Sender);
        void __fastcall mCascadeClick(TObject *Sender);
        void __fastcall mTileHorizClick(TObject *Sender);
        void __fastcall mTileVertClick(TObject *Sender);
        void __fastcall mArrangeIconClick(TObject *Sender);
        void __fastcall mStyleStandartClick(TObject *Sender);
        void __fastcall mStyleFlatClick(TObject *Sender);
        void __fastcall mStyleEnhancedClick(TObject *Sender);
        void __fastcall dxProcessClick(TObject *Sender);
        void __fastcall dxViewApproximationClick(TObject *Sender);
        void __fastcall dxTestClick(TObject *Sender);
        void __fastcall mSaveAsClick(TObject *Sender);
        void __fastcall mWeigthApproximationClick(TObject *Sender);
	void __fastcall FormDestroy(TObject *Sender);
private:	// User declarations
  // Запуск процесса настройки вессовой аппроксимации
	void __fastcall CreateWeigthApproximationProcess();
  // Запуск процесса настройки вессового районирования
	void __fastcall CreateWeigthRegProcess();
public:		// User declarations
        bool bStatus;
        // Фабрика процессов
        FactoryProcess* _FactoryProcess;
        Data *fData;
        Settings *rSetting;
        const MainProcess *_MainProcess;
        __fastcall TfrmMain(TComponent* Owner);
};
//---------------------------------------------------------------------------
extern PACKAGE TfrmMain *frmMain;
//---------------------------------------------------------------------------
#endif
