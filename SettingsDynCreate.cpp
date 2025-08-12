//---------------------------------------------------------------------------
#include <vcl.h>
#include "SettingsDynCreate.h"
#pragma hdrstop
//---------------------------------------------------------------------------
#pragma package(smart_init)

//---------------------------------------------------------------------------
// �����������
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
// �������� ���������
//---------------------------------------------------------------------------
void TSettingsDynCreate::SendSettings()
{
  for (unsigned int i = 0; i < vLevelSettingsVisual.size(); i++)
    vLevelSettingsVisual[i]->SendSettings();
}
//---------------------------------------------------------------------------
// ����������
//---------------------------------------------------------------------------
TSettingsDynCreate::~TSettingsDynCreate()
{
  for (unsigned int i = 0; i < vLevelSettingsVisual.size(); i++)
    delete vLevelSettingsVisual[i];
}
//---------------------------------------------------------------------------
