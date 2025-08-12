//---------------------------------------------------------------------------
#ifndef FactoryProcessRH
#define FactoryProcessRH
#include "ProcessR.h"
#include "FactoryDataWA.h"
#include "FactoryNet.h"
#include "FactoryParamWA.h"
//---------------------------------------------------------------------------
// �������� ���������� ������ �������� �������������
// 1D - �����
// 2D - ���������
// 3D - �����
//---------------------------------------------------------------------------
class FactoryProcessR {

private:
  // ���������
  const Settings *_Settings;
  // ������
  const Data *_Data;
  // ������� �������� ������� �� ���������� ������
  FactoryDataWA *_FactoryDataWA;
  // ������� �������� ������� �� ���������� ����������������� �����
  FactoryNet *_FactoryNet;
  // ������� �������� ��������� ��� ����������
  FactoryParamWA *_FactoryParamWA;
  // ������
  DataWA *_DataWA;
  // �����
  Net *_Net;
  // ��������� ��� ���������� ������� �������������
  const ParamCalcWA *_ParamCalcWA;
  // ������� ���������� ������� �������������
  ProcessR *_ProcessR;
  // ����� ������, ��� ������� ���, ����� ������ -1
  int NumLevel;
  // ��������� �����������
  objData _AnisotropyFactor;
  // ������� ��������� ������ ������� �������������
  void Destroy();

public:
  // �����������
  FactoryProcessR(const Settings *Settings_, const Data *Data_,
    const objData AnisotropyFactor);
  // ����������� � ������ �������
  FactoryProcessR(const Settings *Settings_, const Data *Data_,
    const int NumLevel_, const objData AnisotropyFactor);
  // ����������
  ~FactoryProcessR();
  // C������ ��������� ������ ������� �������������
  ProcessR *Create();

};
//---------------------------------------------------------------------------
#endif
