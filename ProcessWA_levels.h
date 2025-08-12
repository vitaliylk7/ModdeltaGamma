//---------------------------------------------------------------------------
#ifndef ProcessWA_levelsH
#define ProcessWA_levelsH
#include <list>
#include <fstream.h>
#include "FactoryProcessWA.h"
//---------------------------------------------------------------------------
// Список Фабрик процессов вычисления весовой аппроксимации для нескольких уровней
//---------------------------------------------------------------------------
typedef std::list<FactoryProcessWA*> listFactoryProcessWA;
typedef std::list<FactoryProcessWA*>::iterator iterFactoryProcessWA;
//---------------------------------------------------------------------------
// Список процессов уровней
//---------------------------------------------------------------------------
typedef std::list <const ProcessWA*> listProcessWA;
typedef std::list <const ProcessWA*>::iterator iterProcessWA;
//---------------------------------------------------------------------------
// Класс вычисления весовой аппроксимации
//---------------------------------------------------------------------------
class ProcessWA_levels : public ProcessWA {

private:
  // Настройки
  const Settings *_Settings;
  // Фабрика данных
  FactoryDataWA *_FactoryDataWA;
  // Фабрика создания структуры для вычисления
  FactoryParamWA *_FactoryParamWA;

  // Список Фабрик процессов вычисления весовой аппроксимации для нескольких уровней
  listFactoryProcessWA _listFactoryProcessWA;
  // Итератор cписка Фабрик процессов
  iterFactoryProcessWA _iterFactoryProcessWA;
  // Список процессов уровней
  listProcessWA _listProcessWA;
  // Итератор списка процессов уровней
  iterProcessWA _iterProcessWA;
  // Количество уровней
  int CountLevels;
  // Параметры анизотропии
  objData _AnisotropyFactor;
  // Создать процессы уровней весовой аппроксимации
  int Create();
  // Вычисление общего значения веса и значения всех уровней
  virtual int Calculation();
  // Вычисление общей весовой аппроксимации на исходные точки
  int CalcStandart();
  // Вычисление минимума и максимума для весовой аппроксимации
  void CalcMinMax(const int CountCol, const int CountRec,
      const vector <vector<float> > &vv, vector <float> &vMin,
      vector <float> &vMax);
  // Получить параметр о вычислении вес. аппрокс. на исходные точки
  void setStandart();
  // Сохранить весовую аппроксимацию на исходные точки в файл
  virtual bool SaveStandart(String FileName);

public:
  // Конструктор с учётом уровней
  ProcessWA_levels(const Settings *Settings_, const Data *Data_,
      const int CountLevels_, const objData AnisotropyFactor);
  // Деструктор
  ~ProcessWA_levels();
  //  Запуск
  virtual bool Run();
  // Очистка
  virtual bool Clear();
  // Показать график
  virtual bool VisualResultGraph();
  // Показать значения результата
  virtual bool VisualResultText();

};
//---------------------------------------------------------------------------
#endif
