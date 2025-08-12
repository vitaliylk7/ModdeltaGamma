//---------------------------------------------------------------------------
#ifndef FactoryProcessWAH
#define FactoryProcessWAH
#include "ProcessWA.h"
#include "FactoryDataWA.h"
#include "FactoryParamWA.h"
#include "DataWA_Area.h"
//---------------------------------------------------------------------------
//   Создания экземпляра класса процесса оценки рассогласования
// весовой аппроксимации
//---------------------------------------------------------------------------
class FactoryProcessWA {

private:
  // Настройки
  const Settings *_Settings;
  // Данные
  const Data *_Data;
  // Данные облости оценки рассогласования
  DataWA_Area *_dataWA_Area;
  // Фабрика создания классов по подготовки данных
  FactoryDataWA *_FactoryDataWA;
  // Фабрика создания структуры для вычисления
  FactoryParamWA *_FactoryParamWA;
  // Данные
  DataWA *_DataWA;
  // Структура для вычисления весовой аппроксимации
  const ParamCalcWA *_ParamCalcWA;
  // Процесс вычисления весовой аппроксимации
  ProcessWA *_ProcessWA;
  // Номер уровня, есл уровней нет, тогда просто -1
  int NumLevel;
  // Параметры анизотропии
  objData _AnisotropyFactor;
  // Удалить экземпляр класса весовой аппроксимации
  void Destroy();

public:
  // Конструктор
  FactoryProcessWA(const Settings *Settings_, const Data *Data_,
    const objData AnisotropyFactor, float beta);
  // Конструктор с учётом уровней
  FactoryProcessWA(const Settings *Settings_, const Data *Data_,
    const int NumLevel_, const objData AnisotropyFactor);
  // Cоздать экземпляр класса весовой аппроксимации 2D
  ProcessWA* CreateProcessWA2D();
  // Деструктор
  ~FactoryProcessWA();
  // Cоздать экземпляр класса весовой аппроксимации
  ProcessWA *Create();

};
//---------------------------------------------------------------------------
#endif
