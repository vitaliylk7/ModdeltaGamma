//---------------------------------------------------------------------------
#ifndef FactoryProcessH
#define FactoryProcessH
//---------------------------------------------------------------------------
#include "ProcessWA_levels.h"
#include "ProcessWA_BetaStep.h"

// ������� ���������
class FactoryProcess {
private:
  MainProcess* _MainProcess;
  // ������� �������� ������� �������������
  FactoryProcessWA *_FactoryProcessWA;
  // �������� ��������� �����������
  objData getAnisotropyFactor(const Settings *Settings_);
public:
  // �����������
  FactoryProcess();
  // ����������
  ~FactoryProcess();
  // ������� �������
  const MainProcess* Create(const Data *Data_, const Settings *Settings_);
  // ������� ������� � ���������� ��������� Beta
  const MainProcess* Create(const Data *data, const Settings *settings,
    float beta);
	// ������� �������
  void Destroy();
};

#endif
