//---------------------------------------------------------------------------
#ifndef SettingsForLevelsH
#define SettingsForLevelsH
//---------------------------------------------------------------------------
#include <vcl.h>
#include <vector>
#include <fstream.h>
#include "LevelSettings.h"

// ********************************************
// ��������� ��� ��������� �������
// ********************************************

class TSettingsForLevels {
private:
    // ������ ���������� � ���� ��������� �������
    vector<TLevelSettings> vLevelSettings;
    vector<TLevelSettings> v_tmp;
public:
    // �����������
    TSettingsForLevels(){  };
    // �������� �������
    void Add(TLevelSettings LS);
    // ��������
    void Clear();
    // �������� ������� �� �������
    TLevelSettings getLevel(unsigned int i);
    // �������� ���-�� �������
    int getCountLevels();
    // ����������
    ~TSettingsForLevels(){  };
};


#endif
