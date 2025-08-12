//---------------------------------------------------------------------------
#ifndef LevelSettingsH
#define LevelSettingsH
//---------------------------------------------------------------------------

// Настройки для одного уровня
struct TLevelSettings {
  // Номер уровня
  int Number;
  // Название уровня
  String Name;
  // Интервал для признака
  float CriterionFrom;
  float CriterionTill;
  // Параметры весовой функции
  float _fAlpha;  // Альфа
  float _fBeta;   // Бета
  float _fGamma;  // Гамма
  float _fSigma;  // Сигма
  // Оператор не равно
  int operator != (const TLevelSettings &right) const;
  // Оператор равно
  int operator == (const TLevelSettings &right) const;
  // Оператор присваевания
  TLevelSettings &operator = (const TLevelSettings &right);
};

#endif
