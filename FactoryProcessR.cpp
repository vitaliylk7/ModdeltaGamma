//---------------------------------------------------------------------------
#include <vcl.h>
#pragma hdrstop
#include "FactoryProcessR.h"
//---------------------------------------------------------------------------
#pragma package(smart_init)
//---------------------------------------------------------------------------
// Конструктор
//---------------------------------------------------------------------------
FactoryProcessR::FactoryProcessR(const Settings *Settings_, const Data *Data_,
  const objData AnisotropyFactor)
{
  NumLevel = -1;
  _ProcessR = 0;
  _Settings = Settings_;
  _Data = Data_;
  _AnisotropyFactor = AnisotropyFactor;
  _FactoryDataWA = new FactoryDataWA(_Data, _Settings);
  _FactoryNet = new FactoryNet(_Settings);
  _FactoryParamWA = new FactoryParamWA(_Settings);
}
//---------------------------------------------------------------------------
// Конструктор с учётом уровней
//---------------------------------------------------------------------------
FactoryProcessR::FactoryProcessR(const Settings *Settings_, const Data *Data_,
    const int NumLevel_, const objData AnisotropyFactor)
{
  NumLevel = NumLevel_;
  _ProcessR = 0;
  _Settings = Settings_;
  _Data = Data_;
  _AnisotropyFactor = AnisotropyFactor;
  _FactoryDataWA = new FactoryDataWA(_Data, _Settings, NumLevel);
  _FactoryNet = new FactoryNet(_Settings);
  _FactoryParamWA = new FactoryParamWA(_Settings, NumLevel);
}
//---------------------------------------------------------------------------
// Деструктор
//---------------------------------------------------------------------------
FactoryProcessR::~FactoryProcessR()
{
  Destroy();

  if (_FactoryDataWA != 0)
    delete _FactoryDataWA;

  if (_FactoryNet != 0)
    delete _FactoryNet;

  if (_FactoryParamWA != 0)
    delete _FactoryParamWA;
}
//---------------------------------------------------------------------------
// Cоздать экземпляр класса весовой аппроксимации
//---------------------------------------------------------------------------
ProcessR *FactoryProcessR::Create()
{
  Destroy();

  _DataWA = _FactoryDataWA->Create();
  _Net = _FactoryNet->Create();
  _ParamCalcWA = _FactoryParamWA->Create();

  bool bStandart = false;
  switch (_Settings->TypeModel)
  {
  	case mReg1D:
      bStandart = _Settings->mSettingsApproxLine->Standart;
      break;
  	case mReg2D:
    case mReg3D:
      bStandart = _Settings->mSettingsApprox2D3D->Standart;
      break;

    default:
      bStandart = false;
  }

  if (NumLevel == -1)
    _ProcessR = new ProcessR(_Data, _DataWA, _Net, _ParamCalcWA, bStandart,
      _AnisotropyFactor);
  else
    _ProcessR = new ProcessR(_Data, _DataWA, _Net, _ParamCalcWA, NumLevel,
      bStandart, _AnisotropyFactor);


	return  _ProcessR;
}
//---------------------------------------------------------------------------
// Удалить экземпляр класса весовой аппроксимации
//---------------------------------------------------------------------------
void FactoryProcessR::Destroy()
{
  if (_ProcessR != 0)
  {
    delete _ProcessR;
    _ProcessR = 0;
  }
}