//---------------------------------------------------------------------------
#ifndef LevelSettingsVisualH
#define LevelSettingsVisualH
//---------------------------------------------------------------------------
#include "dxInspct.hpp"
#include "dxInspRw.hpp"
#include "SettingsForLevels.h"

// ��������� ��� ������ ������
class TLevelSettingsVisual {
private:
  // ����� ������
  int iNumber;
  // ��������� ������ (������)
  String Caption;
  // �������� ������
  TdxInspectorTextRow* _NameLevel;
  // �������� ��� ��������
  TdxInspectorTextRow* _CriterionFrom;
  TdxInspectorTextRow* _CriterionTill;
  // ��������� ������� �������
  TdxInspectorTextRow* _Alpha;  // �����
  TdxInspectorTextRow* _Gamma;  // �����
  TdxInspectorTextRow* _Beta;   // ����
  TdxInspectorTextRow* _Sigma;   // sigma
  // ��������� �� ��������� � ������� ����� ����������� �������
  TdxInspector* _Inspector;
  // ��������� ��� �������� ��������
  TLevelSettings LevelSettings;
  // ����� �������� �������
  TSettingsForLevels* _SettingsForLevels;
  // �������� ��������
  void Create();
  // ������� ��������
  void Clear();
public:
  // �����������
  TLevelSettingsVisual(TdxInspector *Inspector, int Num,
    TSettingsForLevels *SettingsForLevels, String Caption_);
  // �������� ���������
  void SendSettings();
  // ����������
  ~TLevelSettingsVisual();
};

#endif
