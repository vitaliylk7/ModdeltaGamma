//---------------------------------------------------------------------------
#include <vcl.h>
#pragma hdrstop
#include "FactoryProcess.h"
//---------------------------------------------------------------------------
#pragma package(smart_init)
//---------------------------------------------------------------------------
// Конструктор
//---------------------------------------------------------------------------
FactoryProcess::FactoryProcess()
{
  _MainProcess = 0;
  _FactoryProcessWA = 0;
};
// --------------------------------------------------------------------------
// Получить параметры анизотропии
// --------------------------------------------------------------------------
objData FactoryProcess::getAnisotropyFactor(const Settings *_Settings)
{
  objData result;

  switch (_Settings->TypeModel)
  {
  	case mApprox2D:
    case mApprox3D:
      result.x = _Settings->mSettingsApprox2D3D->xAnisotropyFactor;
      result.y = _Settings->mSettingsApprox2D3D->yAnisotropyFactor;
      result.z = _Settings->mSettingsApprox2D3D->zAnisotropyFactor;
  		break;
    default :
      result.x = 1;
      result.y = 1;
      result.z = 1;
  }

  return result;
}
//---------------------------------------------------------------------------
// Создать процесс весовой аппроксимации
//---------------------------------------------------------------------------
const MainProcess* FactoryProcess::Create(const Data *Data_,
  const Settings *Settings_)
{
  Destroy();
  int CountLevels;
  switch (Settings_->TypeModel)
  {
  	case mApprox1D:
    case mApprox3D:
  	case mApprox2D:
      CountLevels = Settings_->getCountLevelsWA();
      if (CountLevels > 1)
      {
        _MainProcess = new ProcessWA_levels(Settings_, Data_, CountLevels,
          getAnisotropyFactor(Settings_));
      }
      else
      {
        _FactoryProcessWA = new FactoryProcessWA(Settings_, Data_,
          getAnisotropyFactor(Settings_), 0);
        _MainProcess = _FactoryProcessWA->Create();
      }
      break;
  }

	return  _MainProcess;
}
// --------------------------------------------------------------------------
// Создать процесс с установкой параметра Beta
// --------------------------------------------------------------------------
const MainProcess* FactoryProcess::Create(const Data *data,
  const Settings *settings, float beta)
{
  _FactoryProcessWA = new FactoryProcessWA(settings, data,
    getAnisotropyFactor(settings), beta);
  _MainProcess = _FactoryProcessWA->Create();
}
//---------------------------------------------------------------------------
// Удалить процесс
//---------------------------------------------------------------------------
void FactoryProcess::Destroy()
{
  _MainProcess = 0;

  if (_FactoryProcessWA != 0)
  {
    delete _FactoryProcessWA;
    _FactoryProcessWA = 0;
  }
}
//---------------------------------------------------------------------------
// Деструктор
//---------------------------------------------------------------------------
FactoryProcess::~FactoryProcess()
{
	if (_MainProcess != 0)
  	delete _MainProcess;
}
