//---------------------------------------------------------------------------

#include <vcl.h>
#pragma hdrstop

#include "Main.h"
#include "About.h"
#include "SettingsFile.h"
#include "DataView.h"
#include "ViewSettingData.h"
#include "CheckWeigthApproximationType.h"
#include "ChooseTypePlaneFor2D.h"
#include "FormSettings.h"
//---------------------------------------------------------------------------
#pragma package(smart_init)
#pragma link "dxBar"
#pragma resource "*.dfm"
TfrmMain *frmMain;
// Настройки процессов
TfrmFormSettings *frmFormSettings;
//---------------------------------------------------------------------------
__fastcall TfrmMain::TfrmMain(TComponent* Owner)
        : TForm(Owner)
{
  _FactoryProcess = new FactoryProcess();
  rSetting = new Settings();
  fData = new Data();
  _MainProcess = 0;
  frmFormSettings = 0;
}
//---------------------------------------------------------------------------
void __fastcall TfrmMain::mExitClick(TObject *Sender)
{
  Close();
}
//---------------------------------------------------------------------------
void __fastcall TfrmMain::mAboutClick(TObject *Sender)
{
  const auto_ptr<TAboutBox> AboutBox(new TAboutBox(0));
  AboutBox->ShowModal();
}
//---------------------------------------------------------------------------
void __fastcall TfrmMain::mOpenClick(TObject *Sender)
{
	// Удалим процесс
	_FactoryProcess->Destroy();
  mService->Enabled = false;
  mView->Enabled = true;
  mSettingsFile->Enabled = true;
  mSaveAs->Enabled = false;

	for (int i = MDIChildCount-1; i >= 0; --i)
    MDIChildren[i]->Close();

 StatusBar->SimpleText = "";

 try {
  String sFileName;
  OpenDialogFileData->Filter = "Text files (*.*)|*.*";
  if (OpenDialogFileData->Execute())
    sFileName = OpenDialogFileData->FileName;
  // Загрузка данных из файла
  if (fData->Create(sFileName)){
    frmSettingsFile = new TfrmSettingsFile(Application);
    mService->Enabled = true;
    dxProcess->Enabled = false;
    mTypeModelling->Enabled = true;
  }
 }
 __except(EXCEPTION_EXECUTE_HANDLER) {
    ShowMessage("Не удалось открыть файл данных!");
 }
}
//---------------------------------------------------------------------------
// Запуск процесса настройки вессовой аппроксимации
//---------------------------------------------------------------------------
void __fastcall TfrmMain::CreateWeigthApproximationProcess()
{
	frmCheckWeigthApproximationType =
  	new TfrmCheckWeigthApproximationType(Application);
	frmCheckWeigthApproximationType->ShowModal();
	if (frmCheckWeigthApproximationType->ModalResult == mrOk)
	{
  	mService->Enabled = true;
		mView->Enabled = true;
		mSettingsFile->Enabled = true;
		mSaveAs->Enabled = false;
	        dxProcess->Enabled = true;
		dxTest->Enabled = false;
		dxViewApproximation->Enabled = false;

		switch (frmCheckWeigthApproximationType->
			    	rgTypeWeightApproximation->ItemIndex)
		{ 
			// Процесс аппроксимации на плоскую сетку, в том числе и косое сечение
      case 1: // Настройка составной модели
				rSetting->TypeModel = mApprox2D;
				rSetting->mSettingsApprox2D3D->CountLevels =
        	StrToInt(frmCheckWeigthApproximationType->edCountLevels->Text);
       	frmFormSettings = new TfrmViewSettingData(Application,
  				rSetting->mSettingsApprox2D3D, fData, "уровень");
				rSetting->mSettingsApprox2D3D->WhichParallelPlane = mNormal;
        break;
			// Процесс аппроксимации на объёмную сетку
			case 2:
				rSetting->TypeModel = mApprox3D;
				// Получить количество уровней составной модели
				rSetting->mSettingsApprox2D3D->CountLevels =
        	StrToInt(frmCheckWeigthApproximationType->edCountLevels->Text);
				frmFormSettings = new TfrmViewSettingData(Application,
					rSetting->mSettingsApprox2D3D, fData, "уровень");
				break;
    }
	}
}
//---------------------------------------------------------------------------
// Запуск процесса настройки вессового районирования
//---------------------------------------------------------------------------
void __fastcall TfrmMain::CreateWeigthRegProcess() {

}
//---------------------------------------------------------------------------
void __fastcall TfrmMain::mSettingsFileClick(TObject *Sender)
{
  if (frmMain->fData->getStatus()){
   frmSettingsFile = new TfrmSettingsFile(Application);
  }
}
//---------------------------------------------------------------------------
void __fastcall TfrmMain::mViewClick(TObject *Sender)
{
  if (frmMain->fData->getStatus()){
   frmDataView = new TfrmDataView(Application);
  }
}
//---------------------------------------------------------------------------
void __fastcall TfrmMain::mCascadeClick(TObject *Sender)
{
  Cascade();
}
//---------------------------------------------------------------------------
void __fastcall TfrmMain::mTileHorizClick(TObject *Sender)
{
  TileMode = tbHorizontal;
  Tile();
}
//---------------------------------------------------------------------------
void __fastcall TfrmMain::mTileVertClick(TObject *Sender)
{
  TileMode = tbVertical;
  Tile();
}
//---------------------------------------------------------------------------
void __fastcall TfrmMain::mArrangeIconClick(TObject *Sender)
{
  ArrangeIcons();
}
//---------------------------------------------------------------------------
void __fastcall TfrmMain::mStyleStandartClick(TObject *Sender)
{
  dxBarManager->Style = bmsStandard;
}
//---------------------------------------------------------------------------
void __fastcall TfrmMain::mStyleFlatClick(TObject *Sender)
{
 dxBarManager->Style = bmsFlat;
}
//---------------------------------------------------------------------------
void __fastcall TfrmMain::mStyleEnhancedClick(TObject *Sender)
{
 dxBarManager->Style = bmsEnhanced;
}
//---------------------------------------------------------------------------
// Процесс вычисления весовой аппроксимации
//---------------------------------------------------------------------------
void __fastcall TfrmMain::dxProcessClick(TObject *Sender)
{
  // Передача настроек из окна настроек
  rSetting->Clear();

	// Сохраним настройки
  frmFormSettings->setSettingData();

  // Создать процесс
  _MainProcess = _FactoryProcess->Create(fData, rSetting);

  if (_MainProcess->Run() == true)
  {
  	dxTest->Enabled = true;
    dxViewApproximation->Enabled = true;
    mSaveAs->Enabled = true;
  	ShowMessage("Модель построена");
  }
}
//---------------------------------------------------------------------------
// Визуализация процесса в текстовом виде
//---------------------------------------------------------------------------
void __fastcall TfrmMain::dxViewApproximationClick(TObject *Sender)
{
  if (_MainProcess != 0)
  {
    _MainProcess->VisualResultText();
  }
}
//---------------------------------------------------------------------------
// Визуализация процесса в графическом виде
//---------------------------------------------------------------------------
void __fastcall TfrmMain::dxTestClick(TObject *Sender)
{
  if (_MainProcess != 0)
  {
    _MainProcess->VisualResultGraph();
  }
}
//---------------------------------------------------------------------------
// Созранить модель процесса
//---------------------------------------------------------------------------
void __fastcall TfrmMain::mSaveAsClick(TObject *Sender)
{
	if (_MainProcess != 0)
	  _MainProcess->SaveResult();
}
//---------------------------------------------------------------------------
void __fastcall TfrmMain::mWeigthApproximationClick(TObject *Sender)
{
  StatusBar->SimpleText = mWeigthApproximation->Caption;
  // Выполнить диалог процесса весовой аппроксимации
  CreateWeigthApproximationProcess();
}
//---------------------------------------------------------------------------
void __fastcall TfrmMain::FormDestroy(TObject *Sender)
{
  if (0 != _FactoryProcess)
  	delete _FactoryProcess;

  if (0 != rSetting)
  	delete rSetting;

	if (0 != fData)
  	delete fData;
}
//---------------------------------------------------------------------------


