//---------------------------------------------------------------------------
#ifndef FactoryParamWAH
#define FactoryParamWAH
#include "Structs.h"
#include "Settings.h"
//---------------------------------------------------------------------------
// Создания параметров для вычисления весовой аппроксимации
//---------------------------------------------------------------------------
class FactoryParamWA {

private:
  // Настройки процесса 2D и 3D
  const SettingsApprox2D3D *_settingsApprox2D3D;
  // Тип весовой аппроксимации
  int _typeModel;
  // Параметры для вычисления весовой аппроксимации
  ParamCalcWA *_paramCalcWA;
  // Номер уровня
  int _numLevel;
  // Значение бета
  float _beta;

public:
  // Конструктор
  FactoryParamWA(const Settings *settings_, float beta);
  // Конструктор для уровней
  FactoryParamWA(const Settings *settings_, const int numLevel_);
  // Деструктор
  ~FactoryParamWA();
  // Создать параметры
  const ParamCalcWA *Create();
  // Удалить параметры
  void Destroy();

};
//---------------------------------------------------------------------------
#endif
