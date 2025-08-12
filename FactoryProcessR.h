//---------------------------------------------------------------------------
#ifndef FactoryProcessRH
#define FactoryProcessRH
#include "ProcessR.h"
#include "FactoryDataWA.h"
#include "FactoryNet.h"
#include "FactoryParamWA.h"
//---------------------------------------------------------------------------
// Создания экземпляра класса процесса районирования
// 1D - линия
// 2D - плоскость
// 3D - объём
//---------------------------------------------------------------------------
class FactoryProcessR {

private:
  // Настройки
  const Settings *_Settings;
  // Данные
  const Data *_Data;
  // Фабрика создания классов по подготовки данных
  FactoryDataWA *_FactoryDataWA;
  // Фабрика создания классов по подготовки аппроксимационных сеток
  FactoryNet *_FactoryNet;
  // Фабрика создания структуры для вычисления
  FactoryParamWA *_FactoryParamWA;
  // Данные
  DataWA *_DataWA;
  // Сетка
  Net *_Net;
  // Структура для вычисления весовой аппроксимации
  const ParamCalcWA *_ParamCalcWA;
  // Процесс вычисления весовой аппроксимации
  ProcessR *_ProcessR;
  // Номер уровня, есл уровней нет, тогда просто -1
  int NumLevel;
  // Параметры анизотрапии
  objData _AnisotropyFactor;
  // Удалить экземпляр класса весовой аппроксимации
  void Destroy();

public:
  // Конструктор
  FactoryProcessR(const Settings *Settings_, const Data *Data_,
    const objData AnisotropyFactor);
  // Конструктор с учётом уровней
  FactoryProcessR(const Settings *Settings_, const Data *Data_,
    const int NumLevel_, const objData AnisotropyFactor);
  // Деструктор
  ~FactoryProcessR();
  // Cоздать экземпляр класса весовой аппроксимации
  ProcessR *Create();

};
//---------------------------------------------------------------------------
#endif
