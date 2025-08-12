//---------------------------------------------------------------------------
#include <vcl.h>
#pragma hdrstop
#include "FactoryParamWA.h"
//---------------------------------------------------------------------------
#pragma package(smart_init)
//---------------------------------------------------------------------------
// Конструктор
//---------------------------------------------------------------------------
FactoryParamWA::FactoryParamWA(const Settings *settings_, float beta)
{
  _numLevel = -1;
  _typeModel = settings_->TypeModel;
  _settingsApprox2D3D = settings_->mSettingsApprox2D3D;
  _paramCalcWA = new ParamCalcWA();
  _beta = beta;
}
//---------------------------------------------------------------------------
// Конструктор для уровней
//---------------------------------------------------------------------------
FactoryParamWA::FactoryParamWA(const Settings *settings_, const int numLevel_)
{
  _numLevel = numLevel_;
  _typeModel = settings_->TypeModel;
  _settingsApprox2D3D = settings_->mSettingsApprox2D3D;
  _paramCalcWA = new ParamCalcWA();
}
//---------------------------------------------------------------------------
// Деструктор
//---------------------------------------------------------------------------
FactoryParamWA::~FactoryParamWA()
{
  Destroy();
}
//---------------------------------------------------------------------------
// Создать параметры
//---------------------------------------------------------------------------
const ParamCalcWA *FactoryParamWA::Create()
{
  switch (_typeModel)
  {
  	case mApprox2D:
    case mApprox3D:
      _paramCalcWA->Standart = _settingsApprox2D3D->Standart;
      _paramCalcWA->x = _settingsApprox2D3D->NameX;
      _paramCalcWA->y = _settingsApprox2D3D->NameY;
      _paramCalcWA->z = _settingsApprox2D3D->NameZ;

      if (_numLevel == -1)
      {
        _paramCalcWA->Alpha = _settingsApprox2D3D->Alpha;
        _paramCalcWA->Sigma = _settingsApprox2D3D->Sigma;
        _paramCalcWA->Beta = _beta;
        _paramCalcWA->Gamma = _settingsApprox2D3D->Gamma;
      }
      else
      {
        TLevelSettings levelSettings;
        // Получим настройки уровня
        levelSettings =
            _settingsApprox2D3D->SettingsForLevels->getLevel(_numLevel);
        _paramCalcWA->Alpha = levelSettings._fAlpha;
        _paramCalcWA->Sigma = levelSettings._fSigma;
        _paramCalcWA->Beta = levelSettings._fBeta;
        _paramCalcWA->Gamma = levelSettings._fGamma;
      }
  		break;
  }

	return  _paramCalcWA;
}
//---------------------------------------------------------------------------
// Удалить параметры
//---------------------------------------------------------------------------
void FactoryParamWA::Destroy()
{
  if (_paramCalcWA != 0)
    delete _paramCalcWA;
}
//---------------------------------------------------------------------------
