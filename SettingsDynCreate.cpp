//---------------------------------------------------------------------------
#include <vcl.h>
#include "SettingsDynCreate.h"
#pragma hdrstop
//---------------------------------------------------------------------------
#pragma package(smart_init)

//---------------------------------------------------------------------------
// Конструктор
//---------------------------------------------------------------------------
TSettingsDynCreate::TSettingsDynCreate(int iCountLevels, TdxInspector *Inspector,
     TSettingsForLevels* SettingsForLevels, String Caption_)
{
   for (int i = 0; i < iCountLevels; i++)
   {
     TLevelSettingsVisual* LS = new TLevelSettingsVisual(Inspector, i,
        SettingsForLevels, Caption_);
     vLevelSettingsVisual.push_back(LS);
   }
}
//---------------------------------------------------------------------------
// Передать настройки
//---------------------------------------------------------------------------
void TSettingsDynCreate::SendSettings()
{
  for (unsigned int i = 0; i < vLevelSettingsVisual.size(); i++)
    vLevelSettingsVisual[i]->SendSettings();
}
//---------------------------------------------------------------------------
// Деструктор
//---------------------------------------------------------------------------
TSettingsDynCreate::~TSettingsDynCreate()
{
  for (unsigned int i = 0; i < vLevelSettingsVisual.size(); i++)
    delete vLevelSettingsVisual[i];
}
//---------------------------------------------------------------------------
