//---------------------------------------------------------------------------
#ifndef LevelSettingsVisualH
#define LevelSettingsVisualH
//---------------------------------------------------------------------------
#include "dxInspct.hpp"
#include "dxInspRw.hpp"
#include "SettingsForLevels.h"

// Настройки для одного уровня
class TLevelSettingsVisual {
private:
  // Номер уровня
  int iNumber;
  // Заголовок уровня (класса)
  String Caption;
  // Название уровня
  TdxInspectorTextRow* _NameLevel;
  // Интервал для признака
  TdxInspectorTextRow* _CriterionFrom;
  TdxInspectorTextRow* _CriterionTill;
  // Параметры весовой функции
  TdxInspectorTextRow* _Alpha;  // Альфа
  TdxInspectorTextRow* _Gamma;  // Гамма
  TdxInspectorTextRow* _Beta;   // Бета
  TdxInspectorTextRow* _Sigma;   // sigma
  // Указатель на инспектор в котором будет создоваться уровень
  TdxInspector* _Inspector;
  // Структура для передачи настроек
  TLevelSettings LevelSettings;
  // Класс настроек уровней
  TSettingsForLevels* _SettingsForLevels;
  // Создание объектов
  void Create();
  // Очистка объектов
  void Clear();
public:
  // Конструктор
  TLevelSettingsVisual(TdxInspector *Inspector, int Num,
    TSettingsForLevels *SettingsForLevels, String Caption_);
  // Передать настройки
  void SendSettings();
  // Деструктор
  ~TLevelSettingsVisual();
};

#endif
