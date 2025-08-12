//---------------------------------------------------------------------------
#pragma hdrstop
#include "Settings.h"
//---------------------------------------------------------------------------
#pragma package(smart_init)

//---------------------------------------------------------------------------
void Settings::Clear()
{
  // ������
  _bStatus = false;
  // ������� �������� �������
  mSettingsApprox2D3D->Clear();
}
//---------------------------------------------------------------------------
void Settings::Check()
{
	mSettingsApprox2D3D->Clear();
}
//---------------------------------------------------------------------------
Settings::Settings()
{
	mSettingsApprox2D3D = new SettingsApprox2D3D();
  Clear();
}
//---------------------------------------------------------------------------
Settings::~Settings(void)
{
  // �������� �������� ���������
  delete mSettingsApprox2D3D;
}
//---------------------------------------------------------------------------
void __fastcall Settings::SetTypeModel(TypeModels value)
{
	if(_TypeModel != value) {
		_TypeModel = value;
	}
}
//---------------------------------------------------------------------------
TypeModels __fastcall Settings::GetTypeModel() const
{
	return _TypeModel;
}
//---------------------------------------------------------------------------
bool __fastcall Settings::GetStatus() const
{
	return _bStatus;
}
//---------------------------------------------------------------------------
// �������� ���-�� ������� ��� ������� �������������
//---------------------------------------------------------------------------
int Settings::getCountLevelsWA() const
{
  int CountLevels = -1;
  switch (_TypeModel)
  {
  	case mApprox2D:
    case mApprox3D:
    case mReg2D:
    case mReg3D:
      CountLevels = mSettingsApprox2D3D->CountLevels;
  		break;
  }

  return CountLevels;
}
