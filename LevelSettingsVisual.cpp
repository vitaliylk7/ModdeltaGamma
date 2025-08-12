//---------------------------------------------------------------------------
#include <vcl.h>
#pragma hdrstop
#include "LevelSettingsVisual.h"
#include "SettingsForLevels.h"
//---------------------------------------------------------------------------
#pragma package(smart_init)

//---------------------------------------------------------------------------
// Конструктор
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
// Создание объектов
//---------------------------------------------------------------------------
void TLevelSettingsVisual::Create()
{
  // Название уровня
  _NameLevel = (TdxInspectorTextRow*) _Inspector->CreateRow(_Inspector->GetDefaultRowClass());
  _NameLevel->Caption = IntToStr(iNumber + 1) + " " + Caption;
  _NameLevel->IsCategory = true;
  // Интервал для признака
  _CriterionFrom = (TdxInspectorTextRow*) _Inspector->CreateRow(_Inspector->GetDefaultRowClass());
  _CriterionFrom->Caption = "Начало интервала";
  _CriterionTill = (TdxInspectorTextRow*) _Inspector->CreateRow(_Inspector->GetDefaultRowClass());
  _CriterionTill->Caption = "Конец интервала";
  // Параметры весовой функции
  // Гамма
  _Gamma = (TdxInspectorTextRow*) _Inspector->CreateRow(_Inspector->GetDefaultRowClass());
  _Gamma->Caption = "Гамма";
  // Лямбда - заменили на Бета (к сожалению, но в коде она так и останиться как Лямбда)
  _Beta = (TdxInspectorTextRow*) _Inspector->CreateRow(_Inspector->GetDefaultRowClass());
  _Beta->Caption = "Бета";
  // Альфа
  _Alpha = (TdxInspectorTextRow*) _Inspector->CreateRow(_Inspector->GetDefaultRowClass());
  _Alpha->Caption = "Альфа";
  // Sigma
  _Sigma = (TdxInspectorTextRow*) _Inspector->CreateRow(_Inspector->GetDefaultRowClass());
  _Sigma->Caption = "Сигма";
}
//---------------------------------------------------------------------------
// Передать настройки
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
// Очистка объектов
//---------------------------------------------------------------------------
void TLevelSettingsVisual::Clear()
{
  // Название уровня
  delete _NameLevel;
  // Интервал для признака
  delete _CriterionFrom;
  delete _CriterionTill;
  // Параметры весовой функции
  delete _Alpha;  // Альфа
  delete _Gamma;  // Гамма
  delete _Sigma;   // sigma
  delete _Beta;   // Бета
}
//---------------------------------------------------------------------------
// Деструктор
//---------------------------------------------------------------------------
TLevelSettingsVisual::~TLevelSettingsVisual()
{
  Clear();
}
//---------------------------------------------------------------------------
