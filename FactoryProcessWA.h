//---------------------------------------------------------------------------
#ifndef FactoryProcessWAH
#define FactoryProcessWAH
#include "ProcessWA.h"
#include "FactoryDataWA.h"
#include "FactoryParamWA.h"
#include "DataWA_Area.h"
//---------------------------------------------------------------------------
//   �������� ���������� ������ �������� ������ ���������������
// ������� �������������
//---------------------------------------------------------------------------
class FactoryProcessWA {

private:
  // ���������
  const Settings *_Settings;
  // ������
  const Data *_Data;
  // ������ ������� ������ ���������������
  DataWA_Area *_dataWA_Area;
  // ������� �������� ������� �� ���������� ������
  FactoryDataWA *_FactoryDataWA;
  // ������� �������� ��������� ��� ����������
  FactoryParamWA *_FactoryParamWA;
  // ������
  DataWA *_DataWA;
  // ��������� ��� ���������� ������� �������������
  const ParamCalcWA *_ParamCalcWA;
  // ������� ���������� ������� �������������
  ProcessWA *_ProcessWA;
  // ����� ������, ��� ������� ���, ����� ������ -1
  int NumLevel;
  // ��������� �����������
  objData _AnisotropyFactor;
  // ������� ��������� ������ ������� �������������
  void Destroy();

public:
  // �����������
  FactoryProcessWA(const Settings *Settings_, const Data *Data_,
    const objData AnisotropyFactor, float beta);
  // ����������� � ������ �������
  FactoryProcessWA(const Settings *Settings_, const Data *Data_,
    const int NumLevel_, const objData AnisotropyFactor);
  // C������ ��������� ������ ������� ������������� 2D
  ProcessWA* CreateProcessWA2D();
  // ����������
  ~FactoryProcessWA();
  // C������ ��������� ������ ������� �������������
  ProcessWA *Create();

};
//---------------------------------------------------------------------------
#endif
