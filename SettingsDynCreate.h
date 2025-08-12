//---------------------------------------------------------------------------

#ifndef SettingsDynCreateH
#define SettingsDynCreateH
//---------------------------------------------------------------------------
#include <vcl.h>
#include <vector>
#include <fstream.h>
#include "LevelSettingsVisual.h"

// ������ ��� �������� �������� � ������� � ��������� �������

// ����� ���������������� �������� ������� ��� ��������� �������
class TSettingsDynCreate {
private:
  // ������ �������� �������
  vector <TLevelSettingsVisual*> vLevelSettingsVisual;
  vector <TLevelSettingsVisual*> v_tmp;
public:
  // �����������
  TSettingsDynCreate(int iCountLevels, TdxInspector *Inspector,
    TSettingsForLevels* SettingsForLevels, String Caption_);
  // �������� ���������
  void SendSettings();
  // ����������
  ~TSettingsDynCreate();
};

#endif
