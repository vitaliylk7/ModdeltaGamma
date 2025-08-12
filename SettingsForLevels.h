//---------------------------------------------------------------------------
#ifndef SettingsForLevelsH
#define SettingsForLevelsH
//---------------------------------------------------------------------------
#include <vcl.h>
#include <vector>
#include <fstream.h>
#include "LevelSettings.h"

// ********************************************
// Настройки для составных моделей
// ********************************************

class TSettingsForLevels {
private:
    // Вектор содержащий в себе настройки уровней
    vector<TLevelSettings> vLevelSettings;
    vector<TLevelSettings> v_tmp;
public:
    // Конструктор
    TSettingsForLevels(){  };
    // Добавить уровень
    void Add(TLevelSettings LS);
    // Очистить
    void Clear();
    // Получить уровень по индексу
    TLevelSettings getLevel(unsigned int i);
    // Получить кол-во уровней
    int getCountLevels();
    // Деструктор
    ~TSettingsForLevels(){  };
};


#endif
