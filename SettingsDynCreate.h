//---------------------------------------------------------------------------

#ifndef SettingsDynCreateH
#define SettingsDynCreateH
//---------------------------------------------------------------------------
#include <vcl.h>
#include <vector>
#include <fstream.h>
#include "LevelSettingsVisual.h"

// Модуля для создания настроек в журнале в составных моделях

// Класс визуализирования настроек уровней для составных моделей
class TSettingsDynCreate {
private:
  // Вектор настроек уровней
  vector <TLevelSettingsVisual*> vLevelSettingsVisual;
  vector <TLevelSettingsVisual*> v_tmp;
public:
  // Конструктор
  TSettingsDynCreate(int iCountLevels, TdxInspector *Inspector,
    TSettingsForLevels* SettingsForLevels, String Caption_);
  // Передать настройки
  void SendSettings();
  // Деструктор
  ~TSettingsDynCreate();
};

#endif
