//---------------------------------------------------------------------------
#ifndef LevelSettingsH
#define LevelSettingsH
//---------------------------------------------------------------------------

// ��������� ��� ������ ������
struct TLevelSettings {
  // ����� ������
  int Number;
  // �������� ������
  String Name;
  // �������� ��� ��������
  float CriterionFrom;
  float CriterionTill;
  // ��������� ������� �������
  float _fAlpha;  // �����
  float _fBeta;   // ����
  float _fGamma;  // �����
  float _fSigma;  // �����
  // �������� �� �����
  int operator != (const TLevelSettings &right) const;
  // �������� �����
  int operator == (const TLevelSettings &right) const;
  // �������� ������������
  TLevelSettings &operator = (const TLevelSettings &right);
};

#endif
