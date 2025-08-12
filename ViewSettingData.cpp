//---------------------------------------------------------------------------
#include <vcl.h>
#pragma hdrstop

#include "ViewSettingData.h"
#include "Ini.h"
//---------------------------------------------------------------------------
#pragma package(smart_init)
#pragma link "dxCntner"
#pragma link "dxInspct"
#pragma link "dxInspRw"
#pragma resource "*.dfm"
TfrmViewSettingData *frmViewSettingData;
//---------------------------------------------------------------------------
__fastcall TfrmViewSettingData::TfrmViewSettingData(TComponent* Owner,
        	SettingsApprox2D3D* SettingsApprox2D3D_, Data* Data_,
          String LevelCaption_)
        : TfrmFormSettings(Owner)
{
	_SettingsApprox2D3D = SettingsApprox2D3D_;
  _Data = Data_;
  LevelCaption = LevelCaption_;
  frmDialogBackground = new TfrmDialogBackground(this);
}
//---------------------------------------------------------------------------
void __fastcall TfrmViewSettingData::FormClose(TObject *Sender,
      TCloseAction &Action)
{
       if (SettingsDynCreate != 0)
         delete SettingsDynCreate;

			 Action = caFree;
}
//---------------------------------------------------------------------------
void __fastcall TfrmViewSettingData::FormShow(TObject *Sender)
{
  bX = false;
  bY = false;
  bZ = false;
  // Заполнение списков выбора x,y,z
  long iColumn = _Data->getCountColumn();
  String ColumnName, ColumnName_lg;
  for (long i = 0; i < iColumn; ++i)
  {
    ColumnName = _Data->getColumnName(i);
    dxIX->Items->Add(ColumnName);
    dxIY->Items->Add(ColumnName);
    dxIZ->Items->Add(ColumnName);
    chCriterion->Items->Add(ColumnName);
    frmDialogBackground->Add(ColumnName);
    ColumnName_lg = ColumnName + "_lg";
    chCriterion->Items->Add(ColumnName_lg);
    frmDialogBackground->Add(ColumnName_lg);
  }

  // Установка параметров из Ini
  TIni Ini;

  String NameX = Ini.read("TfrmViewSettingData", "NameX");
  int iX = dxIX->Items->IndexOf(NameX);
  if (iX != -1)
  {
    dxIX->Text = NameX;
    String AreaFromX = Ini.read("TfrmViewSettingData", "AreaFromX");
    if (AreaFromX != "")
      FromAreaX->Text = FormatFloat("0.00000", StrToFloat(AreaFromX));

    String AreaTillX = Ini.read("TfrmViewSettingData", "AreaTillX");
    if (AreaTillX != "")
      TillAreaX->Text = FormatFloat("0.00000", StrToFloat(AreaTillX));

    String DataFromX = Ini.read("TfrmViewSettingData", "DataFromX");
    if (DataFromX != "")
      FromDataX->Text = FormatFloat("0.00000", StrToFloat(DataFromX));

    String DataTillX = Ini.read("TfrmViewSettingData", "DataTillX");
    if (DataTillX != "")
      TillDataX->Text = FormatFloat("0.00000", StrToFloat(DataTillX));
  }

  String NameY = Ini.read("TfrmViewSettingData", "NameY");
  int iY = dxIY->Items->IndexOf(NameY);
  if (iY != -1)
  {
    dxIY->Text = NameY;
    String AreaFromY = Ini.read("TfrmViewSettingData", "AreaFromY");
    if (AreaFromY != "")
      FromAreaY->Text = FormatFloat("0.00000", StrToFloat(AreaFromY));

    String AreaTillY = Ini.read("TfrmViewSettingData", "AreaTillY");
    if (AreaTillY != "")
      TillAreaY->Text = FormatFloat("0.00000", StrToFloat(AreaTillY));

    String DataFromY = Ini.read("TfrmViewSettingData", "DataFromY");
    if (DataFromY != "")
      FromDataY->Text = FormatFloat("0.00000", StrToFloat(DataFromY));

    String DataTillY = Ini.read("TfrmViewSettingData", "DataTillY");
    if (DataTillY != "")
      TillDataY->Text = FormatFloat("0.00000", StrToFloat(DataTillY));
  }

  String NameZ = Ini.read("TfrmViewSettingData", "NameZ");
  int iZ = dxIZ->Items->IndexOf(NameZ);
  if (iZ != -1)
  {
    dxIZ->Text = NameZ;
    String AreaFromZ = Ini.read("TfrmViewSettingData", "AreaFromZ");
    if (AreaFromZ != "")
      FromAreaZ->Text = FormatFloat("0.00000", StrToFloat(AreaFromZ));

    String AreaTillZ = Ini.read("TfrmViewSettingData", "AreaTillZ");
    if (AreaTillZ != "")
      TillAreaZ->Text = FormatFloat("0.00000", StrToFloat(AreaTillZ));

    String DataFromZ = Ini.read("TfrmViewSettingData", "DataFromZ");
    if (DataFromZ != "")
      FromDataZ->Text = FormatFloat("0.00000", StrToFloat(DataFromZ));

    String DataTillZ = Ini.read("TfrmViewSettingData", "DataTillZ");
    if (DataTillZ != "")
      TillDataZ->Text = FormatFloat("0.00000", StrToFloat(DataTillZ));
  }

  // Удалим не нужные параметры в случае если счёт на уровни
  if (_SettingsApprox2D3D->CountLevels > 1)
  {
   delete dxICategorySettingsWA;
  }
  else
  {
    dxIAlpha->Text = Ini.read("TfrmViewSettingData", "Alpha");
    dxIGamma->Text = Ini.read("TfrmViewSettingData", "Gamma");
    dxISigma->Text = Ini.read("TfrmViewSettingData", "Sigma");
    dxIBetaFrom->Text = Ini.read("TfrmViewSettingData", "BetaFrom");
    dxIBetaTo->Text = Ini.read("TfrmViewSettingData", "BetaTo");
    dxIBetaStep->Text = Ini.read("TfrmViewSettingData", "BetaStep");
  }

  // Коэффициент анизотропии
  String xAnisotropyFactorTmp =
    Ini.read("TfrmViewSettingData", "xAnisotropyFactor");
  if (xAnisotropyFactorTmp != "") {
    xAnisotropyFactor->Text =
      FormatFloat("0.00", StrToFloat(xAnisotropyFactorTmp));
  }

  String yAnisotropyFactorTmp =
    Ini.read("TfrmViewSettingData", "yAnisotropyFactor");
  if (yAnisotropyFactorTmp != "") {
    yAnisotropyFactor->Text =
      FormatFloat("0.00", StrToFloat(yAnisotropyFactorTmp));
  }

  String zAnisotropyFactorTmp =
    Ini.read("TfrmViewSettingData", "zAnisotropyFactor");
  if (zAnisotropyFactorTmp != "") {
    zAnisotropyFactor->Text =
      FormatFloat("0.00", StrToFloat(zAnisotropyFactorTmp));
  }
 Change("Data",FromDataX->Text, TillDataX->Text, FromDataY->Text,
 TillDataY->Text, FromDataZ->Text, TillDataZ->Text);
 Change("Area",FromAreaX->Text, TillAreaX->Text, FromAreaY->Text,
 TillAreaY->Text, FromAreaZ->Text, TillAreaZ->Text);
  // Показать настройки уровней
  if (_SettingsApprox2D3D->CountLevels > 1)
  {
   if (SettingsDynCreate != 0)
     delete SettingsDynCreate;
   SettingsDynCreate = new TSettingsDynCreate(_SettingsApprox2D3D->CountLevels,
     dxI, _SettingsApprox2D3D->SettingsForLevels, LevelCaption);
  }

}
//---------------------------------------------------------------------------
void __fastcall TfrmViewSettingData::setSettingData(void)
{
  _SettingsApprox2D3D->Clear();

   // Установка параметров в Ini
   TIni Ini;

  _SettingsApprox2D3D->pTypeSection = mNormal;

  // Передадим признаки в случа если вычисление без уровней
  if (_SettingsApprox2D3D->CountLevels <= 1)
  {
    _SettingsApprox2D3D->Alpha = dxIAlpha->Text.ToDouble();
    Ini.write("TfrmViewSettingData", "Alpha", dxIAlpha->Text);

    _SettingsApprox2D3D->Gamma = dxIGamma->Text.ToDouble();
    Ini.write("TfrmViewSettingData", "Gamma", dxIGamma->Text);

    _SettingsApprox2D3D->Sigma = dxISigma->Text.ToDouble();
    Ini.write("TfrmViewSettingData", "Sigma", dxISigma->Text);

    _SettingsApprox2D3D->BetaFrom = dxIBetaFrom->Text.ToDouble();
    Ini.write("TfrmViewSettingData", "BetaFrom", dxIBetaFrom->Text);

    _SettingsApprox2D3D->BetaTo = dxIBetaTo->Text.ToDouble();
    Ini.write("TfrmViewSettingData", "BetaTo", dxIBetaTo->Text);

    _SettingsApprox2D3D->BetaStep = dxIBetaStep->Text.ToDouble();
    Ini.write("TfrmViewSettingData", "BetaStep", dxIBetaStep->Text);
  }

  _SettingsApprox2D3D->NameX = dxIX->Text;
  Ini.write("TfrmViewSettingData", "NameX", dxIX->Text);

  _SettingsApprox2D3D->NameY = dxIY->Text;
  Ini.write("TfrmViewSettingData", "NameY", dxIY->Text);

  _SettingsApprox2D3D->NameZ = dxIZ->Text;
  Ini.write("TfrmViewSettingData", "NameZ", dxIZ->Text);

  PositionData pd;
  pd.x = 0;
  pd.y = 0;
  pd.z = 0;
  _SettingsApprox2D3D->StepNet = pd;

  FromTill ft;
  ft.From = FromAreaX->Text.ToDouble();
  Ini.write("TfrmViewSettingData", "AreaFromX", FromAreaX->Text);
  ft.Till = TillAreaX->Text.ToDouble();
  Ini.write("TfrmViewSettingData", "AreaTillX", TillAreaX->Text);
  _SettingsApprox2D3D->xScopeAreaAprox = ft;

  ft.From = FromAreaY->Text.ToDouble();
  Ini.write("TfrmViewSettingData", "AreaFromY", FromAreaY->Text);
  ft.Till = TillAreaY->Text.ToDouble();
  Ini.write("TfrmViewSettingData", "AreaTillY", TillAreaY->Text);
  _SettingsApprox2D3D->yScopeAreaAprox = ft;

  ft.From = FromAreaZ->Text.ToDouble();
  Ini.write("TfrmViewSettingData", "AreaFromZ", FromAreaZ->Text);
  ft.Till = TillAreaZ->Text.ToDouble();
  Ini.write("TfrmViewSettingData", "AreaTillZ", TillAreaZ->Text);
  _SettingsApprox2D3D->zScopeAreaAprox = ft;

  ft.From = FromDataX->Text.ToDouble();
  Ini.write("TfrmViewSettingData", "DataFromX", FromDataX->Text);
  ft.Till = TillDataX->Text.ToDouble();
  Ini.write("TfrmViewSettingData", "DataTillX", TillDataX->Text);
  _SettingsApprox2D3D->xScopeDataAprox = ft;

  ft.From = FromDataY->Text.ToDouble();
  Ini.write("TfrmViewSettingData", "DataFromY", FromDataY->Text);
  ft.Till = TillDataY->Text.ToDouble();
  Ini.write("TfrmViewSettingData", "DataTillY", TillDataY->Text);
  _SettingsApprox2D3D->yScopeDataAprox = ft;

  ft.From = FromDataZ->Text.ToDouble();
  Ini.write("TfrmViewSettingData", "DataFromZ", FromDataZ->Text);
  ft.Till = TillDataZ->Text.ToDouble();
  Ini.write("TfrmViewSettingData", "DataTillZ", TillDataZ->Text);
  _SettingsApprox2D3D->zScopeDataAprox = ft;

  _SettingsApprox2D3D->pDimensionAreaAprox = mArea;
  Criterion _Criterion;
  Background _Background;
  for (long i = 0; i < chCriterion->Items->Count; i++)
  {
    if (chCriterion->Checked[i])
    {
      _Criterion.Name = chCriterion->Items->Strings[i];
      _Background = frmDialogBackground->getBackground(_Criterion.Name);
      _Criterion.TildeT = _Background.T;
      _Criterion.W = _Background.W;
      _SettingsApprox2D3D->setCriterion(_Criterion);
    }
  }

  // Вычисление аппроксимации на исходные точки
  _SettingsApprox2D3D->Standart = true;

  Ini.write("TfrmViewSettingData", "Standart", _SettingsApprox2D3D->Standart);

  // Коэффициент анизотропии
  _SettingsApprox2D3D->xAnisotropyFactor = StrToFloat(xAnisotropyFactor->Text);
  Ini.write("TfrmViewSettingData", "xAnisotropyFactor",
    xAnisotropyFactor->Text);

  _SettingsApprox2D3D->yAnisotropyFactor = StrToFloat(yAnisotropyFactor->Text);
  Ini.write("TfrmViewSettingData", "yAnisotropyFactor",
    yAnisotropyFactor->Text);

  _SettingsApprox2D3D->zAnisotropyFactor = StrToFloat(zAnisotropyFactor->Text);
  Ini.write("TfrmViewSettingData", "zAnisotropyFactor",
    zAnisotropyFactor->Text);


  // Передать настройки уровней
  if (_SettingsApprox2D3D->CountLevels > 1)
  {
    SettingsDynCreate->SendSettings();
  }
}
//---------------------------------------------------------------------------
void __fastcall TfrmViewSettingData::dxIXChange(TObject *Sender)
{
  bX = true;
}
//---------------------------------------------------------------------------
void __fastcall TfrmViewSettingData::dxIYChange(TObject *Sender)
{
  bY = true;
}
//---------------------------------------------------------------------------
void __fastcall TfrmViewSettingData::dxIZChange(TObject *Sender)
{
 bZ = true;
}
//---------------------------------------------------------------------------
// Обновить x
//---------------------------------------------------------------------------
void TfrmViewSettingData::update_x()
{
  bX = false;
  int num = _Data->getNumberForColumnName(dxIX->Text);
  if (-1 != num)
  {
    FromDataX->Text = FormatFloat("0.#####",_Data->getMin(num));
    TillDataX->Text = FormatFloat("0.#####",_Data->getMax(num));
    FromAreaX->Text = FromDataX->Text;
    TillAreaX->Text = TillDataX->Text;
    colX = _Data->getNumberForColumnName(dxIX->Text);

  }
}
//---------------------------------------------------------------------------
// Обновить y
//---------------------------------------------------------------------------
void TfrmViewSettingData::update_y()
{
  bY = false;
  int num = _Data->getNumberForColumnName(dxIY->Text);
  if (-1 != num)
  {
    FromDataY->Text = FormatFloat("0.#####",_Data->getMin(num));
    TillDataY->Text = FormatFloat("0.#####",_Data->getMax(num));
    FromAreaY->Text = FromDataY->Text;
    TillAreaY->Text = TillDataY->Text;
    colY = _Data->getNumberForColumnName(dxIY->Text);

  }
}
//---------------------------------------------------------------------------
// Обновить z
//---------------------------------------------------------------------------
void TfrmViewSettingData::update_z()
{
  bZ = false;
  int num = _Data->getNumberForColumnName(dxIZ->Text);
  if (-1 != num)
  {
    FromDataZ->Text = FormatFloat("0.#####",_Data->getMin(num));
    TillDataZ->Text = FormatFloat("0.#####",_Data->getMax(num));
    FromAreaZ->Text = FromDataZ->Text;
    TillAreaZ->Text = TillDataZ->Text;
    colZ = _Data->getNumberForColumnName(dxIZ->Text);
  }
}
//---------------------------------------------------------------------------
void __fastcall TfrmViewSettingData::dxIEdited(TObject *Sender,
      TdxInspectorNode *Node, TdxInspectorRow *Row)
{
   if (bX)
  {
    update_x();
  }
  else
  if (bY)
  {
    update_y();
  }
  else
  if (bZ)
  {
    update_z();
  }
  /*
 long num;
 float Max, Min;
 String sMax, sMin;
 if (bX){
   bX = false;
   num = _Data->getNumberForColumnName(dxIX->Text);
   if (-1 == num)  exit(EXIT_SUCCESS);
   Min = _Data->getMin(num);
   Max = _Data->getMax(num);
   sMin = FormatFloat("0.00000",Min);
   sMax = FormatFloat("0.00000",Max);
   FromDataX->Text = sMin;
   TillDataX->Text = sMax;
   FromAreaX->Text = sMin;
   TillAreaX->Text = sMax;
 }
 else
   if (bY){
     bY = false;
     num = _Data->getNumberForColumnName(dxIY->Text);
     if (-1 == num) exit(EXIT_SUCCESS);
     Min = _Data->getMin(num);
     Max = _Data->getMax(num);
     sMin = FormatFloat("0.00000",Min);
     sMax = FormatFloat("0.00000",Max);
     FromDataY->Text = sMin;
     TillDataY->Text = sMax;
     FromAreaY->Text = sMin;
     TillAreaY->Text = sMax;
   }
   else
    if (bZ){
      bZ = false;
      num = _Data->getNumberForColumnName(dxIZ->Text);
      if (-1 == num) exit(EXIT_SUCCESS);
      Min = _Data->getMin(num);
      Max = _Data->getMax(num);
      sMin = FormatFloat("0.00000",Min);
      sMax = FormatFloat("0.00000",Max);
      FromDataZ->Text = sMin;
      TillDataZ->Text = sMax;
      FromAreaZ->Text = sMin;
      TillAreaZ->Text = sMax;
    }
    */
}
//---------------------------------------------------------------------------
void __fastcall TfrmViewSettingData::bEnterAnisotropyClick(TObject *Sender)
{
  frmDialogBackground->Show();  
}
//---------------------------------------------------------------------------

void __fastcall TfrmViewSettingData::FormDestroy(TObject *Sender)
{
  delete frmDialogBackground;  
}
//---------------------------------------------------------------------------

void __fastcall TfrmViewSettingData::dxIKeyPress(TObject *Sender,
      char &Key)
{
if(Key =='\r')
  { Change("Data",FromDataX->Text, TillDataX->Text, FromDataY->Text,
       TillDataY->Text, FromDataZ->Text, TillDataZ->Text);
    Change("Area",FromAreaX->Text, TillAreaX->Text, FromAreaY->Text,
       TillAreaY->Text, FromAreaZ->Text, TillAreaZ->Text);
  }     
}

//---------------------------------------------------------------------------
// Пересчитать количество точек попадающих в границы
//---------------------------------------------------------------------------
void TfrmViewSettingData::Change(String type, String sx1, String sx2, String sy1, String sy2,
              String sz1, String sz2)
{
 float x1, x2, y1, y2, z1, z2;
 long numb;
 numb = 0;
 try
  {
  if (dxIX->Text != "")
  if (dxIX->Text != "")
  if (dxIX->Text != "")
  if (sx1 != "")
  if (sx2 != "")
  if (sy1 != "")
  if (sy2 != "")
  if (sz1 != "")
  if (sz2 != "")
    {
     x1 = StrToFloat(sx1);
     x2 = StrToFloat(sx2);
     y1 = StrToFloat(sy1);
     y2 = StrToFloat(sy2);
     z1 = StrToFloat(sz1);
     z2 = StrToFloat(sz2);
     if(x1 <= x2)
     if(y1 <= y2)
     if(z1 <= z2)
       {
        numb = 0;
        objData XYZ;
        colX = _Data->getNumberForColumnName(dxIX->Text);
        colY = _Data->getNumberForColumnName(dxIY->Text);
        colZ = _Data->getNumberForColumnName(dxIZ->Text);
        for(long i = 0; i < _Data->getCountRecord(); i++)
            {
             XYZ.x = _Data->getData(colX, i);
             XYZ.y = _Data->getData(colY, i);
             XYZ.z = _Data->getData(colZ, i);
             if (XYZ.x >= x1)
             if (XYZ.x <= x2)
             if (XYZ.y >= y1)
             if (XYZ.y <= y2)
             if (XYZ.z >= z1)
             if (XYZ.z <= z2)
                {
                  numb++ ;
                };
             };

       };
    };
  if(type == "Data")
    {
     NumbPointsData->Caption = "количество: " + IntToStr(numb);
     _SettingsApprox2D3D->CountPointData = numb;
     };
  if(type == "Area")
    {
    NumbPointsArea->Caption = "количество: " + IntToStr(numb);
    _SettingsApprox2D3D->CountPointArea = numb;
    };
  }
catch (Exception &exception)
{
if(type == "Data") NumbPointsData->Caption = "количество: (press key ""ENTER"")";
if(type == "Area") NumbPointsArea->Caption = "количество: (press key ""ENTER"")";
};
}
//---------------------------------------------------------------------------

void __fastcall TfrmViewSettingData::pmCalculationXYZClick(TObject *Sender)
{
 update_x();

 update_y();

 update_z();

 Change("Data",FromDataX->Text, TillDataX->Text, FromDataY->Text,
 TillDataY->Text, FromDataZ->Text, TillDataZ->Text);
 Change("Area",FromAreaX->Text, TillAreaX->Text, FromAreaY->Text,
 TillAreaY->Text, FromAreaZ->Text, TillAreaZ->Text);
}
//---------------------------------------------------------------------------

//long TfrmViewSettingData::getCountPointData(void)
//{
//return CountPointData;
//}
//---------------------------------------------------------------------------

//long TfrmViewSettingData::getCountPointArea(void)
//{
//return CountPointArea;
//}



void __fastcall TfrmViewSettingData::dxIExit(TObject *Sender)
{
 Change("Data",FromDataX->Text, TillDataX->Text, FromDataY->Text,
 TillDataY->Text, FromDataZ->Text, TillDataZ->Text);
 Change("Area",FromAreaX->Text, TillAreaX->Text, FromAreaY->Text,
 TillAreaY->Text, FromAreaZ->Text, TillAreaZ->Text);        
}
//---------------------------------------------------------------------------

void __fastcall TfrmViewSettingData::BitBtn1Click(TObject *Sender)
{
int x = 0;
}
//---------------------------------------------------------------------------

void __fastcall TfrmViewSettingData::BitBtn2Click(TObject *Sender)
{
frmMain->dxProcess->OnClick(Sender);
}
//---------------------------------------------------------------------------

void __fastcall TfrmViewSettingData::FromDataXChange(TObject *Sender)
{
//onChange        
}
//---------------------------------------------------------------------------



void __fastcall TfrmViewSettingData::FromDataXValidate(TObject *Sender,
      AnsiString &ErrorText, bool &Accept)
{
//OnValidate
}
//---------------------------------------------------------------------------

void __fastcall TfrmViewSettingData::N1Click(TObject *Sender)
{
 Change("Data",FromDataX->Text, TillDataX->Text, FromDataY->Text,
 TillDataY->Text, FromDataZ->Text, TillDataZ->Text);
 Change("Area",FromAreaX->Text, TillAreaX->Text, FromAreaY->Text,
 TillAreaY->Text, FromAreaZ->Text, TillAreaZ->Text);        
}
//---------------------------------------------------------------------------

