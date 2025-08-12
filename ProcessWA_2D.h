//---------------------------------------------------------------------------
#ifndef ProcessWA_2DH
#define ProcessWA_2DH
#include "ProcessWA.h"
//---------------------------------------------------------------------------
// ����� ���������� ������� ������������� �� ��������� �
// �������������� ���������� � ���������� �����������
//---------------------------------------------------------------------------
class ProcessWA_2D : public ProcessWA {

private:
  // ��������� ������������
    const SettingsApprox2D3D* _Settings;
public:
  // �����������
  ProcessWA_2D(const SettingsApprox2D3D* Settings_, const Data *Data_,
      DataWA *DataWA_, DataWA_Area *_dataWA_Area,
      const ParamCalcWA *ParamCalcWA_, objData AnisotropyFactor);
  // ����������� ��� �������
  ProcessWA_2D(const SettingsApprox2D3D* Settings_, const Data *Data_,
      DataWA *DataWA_, DataWA_Area *_dataWA_Area,
      const ParamCalcWA *ParamCalcWA_,
      const int NumLevel_, objData AnisotropyFactor);
  // ����������
  ~ProcessWA_2D();
  //  ������
  virtual bool Run();
  // �������� ������
  virtual bool VisualResultGraph();
};
//---------------------------------------------------------------------------
#endif
