//---------------------------------------------------------------------------
#ifndef FactoryParamWAH
#define FactoryParamWAH
#include "Structs.h"
#include "Settings.h"
//---------------------------------------------------------------------------
// �������� ���������� ��� ���������� ������� �������������
//---------------------------------------------------------------------------
class FactoryParamWA {

private:
  // ��������� �������� 2D � 3D
  const SettingsApprox2D3D *_settingsApprox2D3D;
  // ��� ������� �������������
  int _typeModel;
  // ��������� ��� ���������� ������� �������������
  ParamCalcWA *_paramCalcWA;
  // ����� ������
  int _numLevel;
  // �������� ����
  float _beta;

public:
  // �����������
  FactoryParamWA(const Settings *settings_, float beta);
  // ����������� ��� �������
  FactoryParamWA(const Settings *settings_, const int numLevel_);
  // ����������
  ~FactoryParamWA();
  // ������� ���������
  const ParamCalcWA *Create();
  // ������� ���������
  void Destroy();

};
//---------------------------------------------------------------------------
#endif
