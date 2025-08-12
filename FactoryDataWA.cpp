//---------------------------------------------------------------------------
#include <vcl.h>
#pragma hdrstop
#include "FactoryDataWA.h"
//---------------------------------------------------------------------------
#pragma package(smart_init)
//---------------------------------------------------------------------------
// Конструктор
//---------------------------------------------------------------------------
FactoryDataWA::FactoryDataWA(const Data *Data_, const Settings *Settings_)
{
  NumLevel = -1;
  _Data = Data_;
  _Settings = Settings_;
  DataWA_ = 0;
}
//---------------------------------------------------------------------------
// Конструктор с учётом уровней
//---------------------------------------------------------------------------
FactoryDataWA::FactoryDataWA(const Data *Data_, const Settings *Settings_,
    const int NumLevel_)
{
  NumLevel = NumLevel_;
  _Data = Data_;
  _Settings = Settings_;
  DataWA_ = 0;
}
//---------------------------------------------------------------------------
// Деструктор
//---------------------------------------------------------------------------
FactoryDataWA::~FactoryDataWA()
{
	Destroy();
}
//---------------------------------------------------------------------------
// Cоздать экземпляр класса аппроксимационной сетки
//---------------------------------------------------------------------------
DataWA *FactoryDataWA::Create()
{
	Destroy();

  switch (_Settings->TypeModel)
  {
  	case mApprox2D:
    case mApprox3D:
    case mReg2D:
    case mReg3D:
      if (NumLevel == -1)
        DataWA_ = new DataWA_2D(_Data, _Settings->mSettingsApprox2D3D);
      else
        DataWA_ = new DataWA_2D(_Data, _Settings->mSettingsApprox2D3D,NumLevel);
  		break;
  }

	return  DataWA_;
}
//---------------------------------------------------------------------------
// Удалить экземпляр класса аппроксимационной сетки
//---------------------------------------------------------------------------
void FactoryDataWA::Destroy()
{
	if (DataWA_ != 0)
  {
  	delete DataWA_;
    DataWA_ = 0;
  }
}
//---------------------------------------------------------------------------
