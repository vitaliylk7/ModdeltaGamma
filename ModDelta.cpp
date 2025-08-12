//---------------------------------------------------------------------------

#include <vcl.h>
#pragma hdrstop
USERES("ModDelta.res");
USEFORM("Main.cpp", frmMain);
USEFORM("About.cpp", AboutBox);
USEUNIT("Data.cpp");
USEFORM("ViewSettingData.cpp", frmViewSettingData);
USEFORM("SettingsFile.cpp", frmSettingsFile);
USEFORM("DataView.cpp", frmDataView);
USEUNIT("Settings.cpp");
USEUNIT("Process.cpp");
USEFORM("ProgressWork.cpp", frmProgressWork);
USEFORM("ViewApproximation.cpp", frmViewApproximation);
USEFORM("ChooseVisualApproximation.cpp", frmChooseVisualApproximation);
USEUNIT("Ini.cpp");
USEFORM("CheckWeigthApproximationType.cpp", frmCheckWeigthApproximationType);
USEFORM("ChooseTypePlaneFor2D.cpp", frmChooseTypePlaneFor2D);
USEUNIT("SettingsDynCreate.cpp");
USEUNIT("LevelSettings.cpp");
USEUNIT("SettingsForLevels.cpp");
USEUNIT("LevelSettingsVisual.cpp");
USEUNIT("FactoryProcess.cpp");
USEUNIT("Utils.cpp");
USEFORM("MainDataModul.cpp", dmGlobal); /* TDataModule: File Type */
USEFORM("DialogSaveResult.cpp", frmDialogSaveResult);
USEFORM("ChooseLevels.cpp", frmChooseLevels);
USEUNIT("SettingsApprox2D3D.cpp");
USEFORM("FormSettings.cpp", frmFormSettings);
USEFORM("DialogSetMinMax.cpp", frmDialogSetMinMax);
USEFORM("ReportText.cpp", frmReportText);
USEUNIT("DataWA.cpp");
USEUNIT("DataWA_2D.cpp");
USEUNIT("FactoryDataWA.cpp");
USEUNIT("ProcessWA.cpp");
USEUNIT("ProcessWA_2D.cpp");
USEUNIT("FactoryProcessWA.cpp");
USEUNIT("FactoryParamWA.cpp");
USEUNIT("ProcessWA_levels.cpp");
USEFORM("DialogBackground.cpp", frmDialogBackground);
USEFORM("DialogRegClassMinW.cpp", frmDialogRegClassMinW);
USEUNIT("ProcessWA_BetaStep.cpp");
USEUNIT("DataWA_Area.cpp");
//---------------------------------------------------------------------------
WINAPI WinMain(HINSTANCE, HINSTANCE, LPSTR, int)
{
  try
  {
    Application->Initialize();
    Application->Title = "ModDelta";
     Application->CreateForm(__classid(TfrmMain), &frmMain);
     Application->CreateForm(__classid(TfrmProgressWork), &frmProgressWork);
     Application->CreateForm(__classid(TdmGlobal), &dmGlobal);
     Application->Run();
  }
  catch (Exception &exception)
  {
    Application->ShowException(&exception);
  }
  return 0;
}
//---------------------------------------------------------------------------
