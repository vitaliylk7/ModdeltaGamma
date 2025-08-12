//---------------------------------------------------------------------------
#include <vcl.h>
#include <string>
#include "Math.h"
#pragma hdrstop
#include "ProcessWA_2D.h"
#include "DialogSaveResult.h"
#include "Process.h"
#include "ProgressWork.h"
#include "Utils.h"
#include "ChooseVisualApproximation.h"

//---------------------------------------------------------------------------
#pragma package(smart_init)
//---------------------------------------------------------------------------
// Конструкторы
//---------------------------------------------------------------------------
ProcessWA_2D::ProcessWA_2D(const SettingsApprox2D3D* Settings_,
    const Data *Data_, DataWA *DataWA_, DataWA_Area *_dataWA_Area,
    const ParamCalcWA *ParamCalcWA_, objData AnisotropyFactor)
    : ProcessWA(Data_, DataWA_, _dataWA_Area, ParamCalcWA_,
        Settings_->Standart, AnisotropyFactor)
{
  _Settings = Settings_;
}
//---------------------------------------------------------------------------
// Конструктор для уровней
//---------------------------------------------------------------------------
ProcessWA_2D::ProcessWA_2D(const SettingsApprox2D3D* Settings_,
    const Data *Data_, DataWA *DataWA_, DataWA_Area *_dataWA_Area,
    const ParamCalcWA *ParamCalcWA_, const int NumLevel_,
    objData AnisotropyFactor)
    : ProcessWA(Data_, DataWA_, _dataWA_Area, ParamCalcWA_, NumLevel_,
        Settings_->Standart, AnisotropyFactor)
{
  _Settings = Settings_;
}
//---------------------------------------------------------------------------
// Деструктор
//---------------------------------------------------------------------------
ProcessWA_2D::~ProcessWA_2D()
{

}
//---------------------------------------------------------------------------
// Запуск процесса
//---------------------------------------------------------------------------
bool ProcessWA_2D::Run()
{
   if ( Calculation() == 0)
     return true;

   return false;
}
//---------------------------------------------------------------------------
// Показать график
//---------------------------------------------------------------------------
bool ProcessWA_2D::VisualResultGraph()
{
  if (bStatus != true){
    ShowMessage("Модель не сформирована");
    return false;
  }

  return true;
}
//---------------------------------------------------------------------------
