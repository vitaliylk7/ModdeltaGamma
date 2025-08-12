//---------------------------------------------------------------------------
#include <vcl.h>
#pragma hdrstop
#include "FactoryProcessWA.h"
#include "ProcessWA_2D.h"
#include "ProcessWA_BetaStep.h"
#include "Structs.h"
//---------------------------------------------------------------------------
#pragma package(smart_init)
//---------------------------------------------------------------------------
// Конструктор
//---------------------------------------------------------------------------
FactoryProcessWA::FactoryProcessWA(const Settings *Settings_, const Data *Data_,
  const objData AnisotropyFactor, float beta)
{
  NumLevel = -1;
  _ProcessWA = 0;
  _Settings = Settings_;
  _Data = Data_;
  _AnisotropyFactor = AnisotropyFactor;
  _FactoryDataWA = new FactoryDataWA(_Data, _Settings);
  _FactoryParamWA = new FactoryParamWA(_Settings, beta);
  _dataWA_Area = 0;
}
//---------------------------------------------------------------------------
// Конструктор с учётом уровней
//---------------------------------------------------------------------------
FactoryProcessWA::FactoryProcessWA(const Settings *Settings_, const Data *Data_,
  const int NumLevel_, const objData AnisotropyFactor)
{
  NumLevel = NumLevel_;
  _ProcessWA = 0;
  _Settings = Settings_;
  _Data = Data_;
  _AnisotropyFactor = AnisotropyFactor;
  _FactoryDataWA = new FactoryDataWA(_Data, _Settings, NumLevel);
  _FactoryParamWA = new FactoryParamWA(_Settings, NumLevel);
  _dataWA_Area = 0;
}
//---------------------------------------------------------------------------
// Деструктор
//---------------------------------------------------------------------------
FactoryProcessWA::~FactoryProcessWA()
{
  Destroy();

  if (_FactoryDataWA != 0)
    delete _FactoryDataWA;

  if (_FactoryParamWA != 0)
    delete _FactoryParamWA;

  if (_dataWA_Area != 0)
    delete _dataWA_Area;
}
//---------------------------------------------------------------------------
// Cоздать экземпляр класса весовой аппроксимации
//---------------------------------------------------------------------------
ProcessWA *FactoryProcessWA::Create()
{
  Destroy();

  _DataWA = _FactoryDataWA->Create();
  _ParamCalcWA = _FactoryParamWA->Create();


  switch (_Settings->TypeModel)
  {
  	case mApprox2D:
    case mApprox3D:
      // Создать область оценки рассогласования
      _dataWA_Area = new DataWA_Area(_Data, _Settings->mSettingsApprox2D3D);
      if (NumLevel == -1)
        _ProcessWA = new ProcessWA_BetaStep(_Settings, _Data, _DataWA,
          _dataWA_Area, _ParamCalcWA, _AnisotropyFactor);
      //else
      //  _ProcessWA = new ProcessWA_BetaStep(_Settings, _Data, _DataWA,
      //    _dataWA_Area, _ParamCalcWA, _AnisotropyFactor);
      break;
  }

	return  _ProcessWA;
}
//---------------------------------------------------------------------------
// Cоздать экземпляр класса весовой аппроксимации 2D
//---------------------------------------------------------------------------
ProcessWA *FactoryProcessWA::CreateProcessWA2D()
{
  Destroy();

  _DataWA = _FactoryDataWA->Create();
  _ParamCalcWA = _FactoryParamWA->Create();
  // Создать область оценки рассогласования
  _dataWA_Area = new DataWA_Area(_Data, _Settings->mSettingsApprox2D3D);
  return new ProcessWA_2D(_Settings->mSettingsApprox2D3D, _Data,
    _DataWA, _dataWA_Area, _ParamCalcWA, _AnisotropyFactor);
}
//---------------------------------------------------------------------------
// Удалить экземпляр класса весовой аппроксимации
//---------------------------------------------------------------------------
void FactoryProcessWA::Destroy()
{
  if (_ProcessWA != 0)
  {
    delete _ProcessWA;
    _ProcessWA = 0;
  }
}
