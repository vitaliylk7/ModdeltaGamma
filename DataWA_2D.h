//---------------------------------------------------------------------------
#ifndef DataWA_2DH
#define DataWA_2DH
#include "DataWA.h"
//---------------------------------------------------------------------------
// ����� ���������� ������ � ���������� ������� ������������� 2D-3D
//---------------------------------------------------------------------------
class DataWA_2D : public DataWA {

private:
  // ��������� �� ��������� ������������
  const SettingsApprox2D3D* _Settings;

public:
  // �����������
  DataWA_2D(const Data *Data_, const SettingsApprox2D3D *Settings_);
  // ����������� ��� �������
  DataWA_2D(const Data *Data_, const SettingsApprox2D3D *Settings_,
      const int NumLevel_);
	// ����������
  ~DataWA_2D();
  // ����� ������
  virtual int Create();

};
//---------------------------------------------------------------------------
#endif
