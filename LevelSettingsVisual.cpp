//---------------------------------------------------------------------------
#include <vcl.h>
#pragma hdrstop
#include "LevelSettingsVisual.h"
#include "SettingsForLevels.h"
//---------------------------------------------------------------------------
#pragma package(smart_init)

//---------------------------------------------------------------------------
// �����������
//---------------------------------------------------------------------------
TLevelSettingsVisual::TLevelSettingsVisual(TdxInspector *Inspector, int Num,
    TSettingsForLevels *SettingsForLevels, String Caption_)
{
  _Inspector = Inspector;
  iNumber = Num;
  _SettingsForLevels = SettingsForLevels;
  Caption = Caption_;
  Create();
}
//---------------------------------------------------------------------------
// �������� ��������
//---------------------------------------------------------------------------
void TLevelSettingsVisual::Create()
{
  // �������� ������
  _NameLevel = (TdxInspectorTextRow*) _Inspector->CreateRow(_Inspector->GetDefaultRowClass());
  _NameLevel->Caption = IntToStr(iNumber + 1) + " " + Caption;
  _NameLevel->IsCategory = true;
  // �������� ��� ��������
  _CriterionFrom = (TdxInspectorTextRow*) _Inspector->CreateRow(_Inspector->GetDefaultRowClass());
  _CriterionFrom->Caption = "������ ���������";
  _CriterionTill = (TdxInspectorTextRow*) _Inspector->CreateRow(_Inspector->GetDefaultRowClass());
  _CriterionTill->Caption = "����� ���������";
  // ��������� ������� �������
  // �����
  _Gamma = (TdxInspectorTextRow*) _Inspector->CreateRow(_Inspector->GetDefaultRowClass());
  _Gamma->Caption = "�����";
  // ������ - �������� �� ���� (� ���������, �� � ���� ��� ��� � ���������� ��� ������)
  _Beta = (TdxInspectorTextRow*) _Inspector->CreateRow(_Inspector->GetDefaultRowClass());
  _Beta->Caption = "����";
  // �����
  _Alpha = (TdxInspectorTextRow*) _Inspector->CreateRow(_Inspector->GetDefaultRowClass());
  _Alpha->Caption = "�����";
  // Sigma
  _Sigma = (TdxInspectorTextRow*) _Inspector->CreateRow(_Inspector->GetDefaultRowClass());
  _Sigma->Caption = "�����";
}
//---------------------------------------------------------------------------
// �������� ���������
//---------------------------------------------------------------------------
void TLevelSettingsVisual::SendSettings()
{
  LevelSettings.Number = iNumber;
  LevelSettings.Name = _NameLevel->Caption;
  LevelSettings.CriterionFrom = StrToFloat(_CriterionFrom->Text);
  LevelSettings.CriterionTill = StrToFloat(_CriterionTill->Text);
  LevelSettings._fAlpha = StrToFloat(_Alpha->Text);
  LevelSettings._fGamma = StrToFloat(_Gamma->Text);
  LevelSettings._fBeta = StrToFloat(_Beta->Text);
  LevelSettings._fSigma = StrToFloat(_Sigma->Text);
  _SettingsForLevels->Add(LevelSettings);
}
//---------------------------------------------------------------------------
// ������� ��������
//---------------------------------------------------------------------------
void TLevelSettingsVisual::Clear()
{
  // �������� ������
  delete _NameLevel;
  // �������� ��� ��������
  delete _CriterionFrom;
  delete _CriterionTill;
  // ��������� ������� �������
  delete _Alpha;  // �����
  delete _Gamma;  // �����
  delete _Sigma;   // sigma
  delete _Beta;   // ����
}
//---------------------------------------------------------------------------
// ����������
//---------------------------------------------------------------------------
TLevelSettingsVisual::~TLevelSettingsVisual()
{
  Clear();
}
//---------------------------------------------------------------------------
