//---------------------------------------------------------------------------
#ifndef ProcessWA_BetaStepH
#define ProcessWA_BetaStepH
#include <list>
#include <fstream.h>
#include "FactoryProcessWA.h"
#include "ReportText.h"
#include "Structs.h"
#include "ProgressWork.h"
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
class ProcessWA_BetaStep : public ProcessWA {

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
  // Покажем пользователю процент выполнения процесса
  void ViewProgress(const long count);  
  // Количество уровней
  int CountLevels;
  // Количество итераций параметра Гамма
  int numbIteration;
  // Параметры анизотропии
  objData _AnisotropyFactor;

  // Отчёт
  TStrings *html;
  // Отчёт
  TfrmReportText *frmReportText;


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
  // Вставка в таблицу парметр и значение
  void add_parval(TStrings *html, String par, int width_par, String val,
    int width_val);
  // Ячейка заголовка таблицы
  void th(int width, String value);
  // Ячейка таблицы
  void td(int width, String value);
  // Печать данных рассогласования для одной характеристики
  void VisualDataD(const int col, String name);

public:
  // Конструктор с учётом уровней
  ProcessWA_BetaStep(const Settings *settings, const Data *data,
    DataWA *dataWA, DataWA *dataWA_Area, const ParamCalcWA *paramCalcWA,
    const objData anisotropyFactor);
  // Деструктор
  ~ProcessWA_BetaStep();
  //  Запуск
  virtual bool Run();
  // Очистка
  virtual bool Clear();
  // Сохранить результат
  virtual bool SaveResult();
  // Показать график
  virtual bool VisualResultGraph();
  // Показать значения результата
  virtual bool VisualResultText();

};
//---------------------------------------------------------------------------
#endif
