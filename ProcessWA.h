//---------------------------------------------------------------------------
#ifndef ProcessWAH
#define ProcessWAH
#include "Process.h"
#include "DataWA.h"
#include "DataWA_Area.h"
//---------------------------------------------------------------------------
// Класс вычисления весовой аппроксимации
//---------------------------------------------------------------------------
class ProcessWA : public MainProcess {

protected:
  // Состояние
  bool bStatus;
  // Данные
  DataWA *_DataWA;
  // Данные отобранные в соответствии с областью оценки рассогласования
  DataWA *_dataWA_Area;
  // Данные с локальной анизатропией
  DataWA *_DataWAAnisotropyFactor;

  // Данные для вычисления аппроксмации на исходные точки
  const Data *_Data;
  // Параметры вычисления
  const ParamCalcWA *_ParamCalcWA;
  // Вектора для чистки данных в векторах
  vector <float> tmp_v;
  vector <vector<float> > tmp_vv;
  // промежуточный массив весовой апроксимации, то есть без использования сетки,
  // что значит вычисление на сами же данные
  bool _bStandart;
  vector <float> vxStandart;
  vector <vector<float> > vStandart;
  vector <float> vStandartW;
  vector <float> vStandartWS; // коэффициент микширования
  vector <float> vStandartS; // коэффициенты микширования
  // А это конечные данные весовой аппроксимации для стандарта
  vector <float> vxTildeStandart;
  vector <vector<float> > vTildeStandart;
  // Минимум и максимум весовой аппроксимации для стандарта
  vector <float> vMinTildeStandart;
  vector <float> vMaxTildeStandart;
  float MinTildeStandart, MaxTildeStandart;
  // Рассогласование
  vector <float> vxD;
  vector <vector <float> > vD;
  // Статистическая информация по рассогласованию
  vector <float> vMinD;       // Минимум рассогласования
  vector <float> vMaxD;       // Максимум рассогласования
  vector <float> vAverageD;   // Среднее рассогласования
  vector <float> vModuleD;    // Модуль рассогласования
  vector <float> vSquaredD;   // Квадрат рассогласования

  // Для области учёта
  // Рассогласование относительно среднего значения (без вессовой аппроксимации)
  vector <float> vxE;
  vector <vector <float> > vE;
  // Статистическая информация по рассогласованию относительно среднего значения
  vector <float> vMinE;       // Минимум рассогласования
  vector <float> vMaxE;       // Максимум рассогласования
  vector <float> vAverageE;   // Среднее рассогласования
  vector <float> vSquaredE;   // Квадрат рассогласования

  // Для области вычисления рассогласований
  // Рассогласование относительно среднего значения (без вессовой аппроксимации)
  vector <float> vxE1;
  vector <vector <float> > vE1;
  // Статистическая информация по рассогласованию относительно среднего значения
  vector <float> vMinE1;       // Минимум рассогласования
  vector <float> vMaxE1;       // Максимум рассогласования
  vector <float> vAverageE1;   // Среднее рассогласования
  vector <float> vSquaredE1;   // Квадрат рассогласования

  // Номер уровня, если уровней нет, тогда просто -1
  int NumLevel;
  // Параметры анизотропии
  objData _AnisotropyFactor;
  // Вычисление расстояния между двумя точками
  float CalcR(const objData _objData, const objData _objNet);
  // Вычислить вес
  float CalcW(const float R, const float Beta, const float Gamma,
      const float Alpha);
  // Вычисление весовой аппроксимации
  virtual int Calculation();
  // Сохранить аппроксимацию на исходные точки
  virtual bool SaveStandart(String FileName);
  // Сохранить Весовую аппроксимацию
  virtual bool SaveModel(String FileName);
  // Получить наименование признака
  String getColName(String s);

private:
  // Ввод локальной анизотропии
  void EnterAnisotropyFactor();
  // Очистка данных анизотропии на исходные точки
  void ClearDataStandart();
  // Подготовка данных анизотропии на исходные точки
  void PrepareDataStandart(const int countCol, const int countRec);
  // Покажем пользователю процент выполнения процесса
  void ViewProgress(const int countRec);
  // Вычисление веса и модельного значения
  void CalcWT(const int countRecData, const int countColData);
  // Очистка данных для конечного модельного значения
  void ClearTildeData();
  // Подготовка данных для конечного модельного значения
  void PrepareTildeData(const int countCol);
  // Вычисление минимума и максимума модельного значения весовой аппроксимации
  void CalcMinMaxTildeStandart(const float TildeStandartT, const int col,
    const int rec);
  // Ввод фонового значения
  void EnterBackground(float &Background_TildeT, float &Background_W,
    const int numLevel, const Column column);

  // Очистка статистики рассогласования
  void ClearStatisticsD();
  // Подготовка статистики рассогласовани
  void PrepareStatisticsD(const int countCol);
  // Вычисление статистики рассогласования
  void CalcStatisticsD(const int countRec, const int countCol);

  // Очистка статистики рассогласования
  void ClearStatisticsE();
  // Подготовка статистики рассогласовани
  void PrepareStatisticsE(const int countCol);
  // Вычисление статистики рассогласования
  void CalcStatisticsE(const int countRec, const int countCol);

  // Очистка статистики рассогласования
  void ClearStatisticsE1();
  // Подготовка статистики рассогласовани
  void PrepareStatisticsE1(const int countCol);
  // Вычисление статистики рассогласования
  void CalcStatisticsE1(const int countRec, const int countCol);

  // Вычисление отклонения относительно среднего значения
  void CalcE(const int countRecArea, const int countColArea);

  // Вычисление отклонения относительно среднего значения
  void CalcE1(const int countRecArea, const int countColArea);

public:
  // Конструкторы
  ProcessWA(const Data *Data_, DataWA *DataWA_, DataWA *dataWA_Area,
      const ParamCalcWA *ParamCalcWA_, const bool bStandart_,
      objData AnisotropyFactor);
  // Конструктор с учётом уровней
  ProcessWA(const Data *Data_, DataWA *DataWA_, DataWA *dataWA_Area,
      const ParamCalcWA *ParamCalcWA_, const int NumLevel_,
      const bool bStandart_, objData AnisotropyFactor);
  // Деструктор
  ~ProcessWA();
  //  Запуск
  virtual bool Run(){ return false; };
  // Очистка
  virtual bool Clear();
  // Сохранить результат
  virtual bool SaveResult();
  // Показать график
  virtual bool VisualResultGraph(){ return false; };
  // Показать значения результата
  virtual bool VisualResultText();

  // Получить реальное значение характеристики
  float getRealValue(const int col, const int rec) const;
  // Получить среднее значение характеристики в области учёта
  float getAverageData(const int col) const;
  // Получить среднее значение характеристики в области оценки
  float getAverageArea(const int col) const;
  // Получить значение в.а. на исходные точки по номеру колонки и номеру записи
  float getStT(const int col, const int rec) const;
  // Получить значение веса по номеру записи для в.а. на исходные точки
  float getStW(const int rec) const;
  // Получить минимальное значения веса
  float getStMinW();
  // Получить максимальное значения веса
  float getStMaxW();
  // Получить номер колонки по названию для в.а. на исходные точки
  int getStNumColumn(String value) const;
  // Получить координаты сетки по значению номера записи для в.а. на исходные точки
  objData getStXYZ(const int rec) const;
  // Получить количество признаков для в.а. на исходные точки
  int getStCountCol() const;
  // Получить количество записей для в.а. на исходные точки
  int getStCountRec() const;
  // Получить наименование колонки по значению индекса для в.а. на исходные точки
  String getStNameCol(int value) const;

  // Получить значение рассогласования
  float getD(const int col, const int rec) const;
  // Получить значение минимум рассогласования
  float getMinD(const int col) const;
  // Получить значение максимума рассогласования
  float getMaxD(const int col) const;
  // Получить значение среднего рассогласования
  float getAverageD(const int col) const;
  // Получить значение модуль рассогласования
  float getModuleD(const int col) const;
  // Получить значение квадрат рассогласования
  float getSquaredD(const int col) const;

  // Получить значение бета
  float getBeta() const;

  // Область учёта
  // Рассогласование относительно среднего значения (без вессовой аппроксимации)
  float getE(const int col, const int rec) const;
  // Получить значение минимум рассогласования
  float getMinE(const int col) const;
  // Получить значение максимума рассогласования
  float getMaxE(const int col) const;
  // Получить значение среднего рассогласования
  float getAverageE(const int col) const;
  // Получить значение модуль рассогласования
//  float getModuleE(const int col) const;
  // Получить значение квадрат рассогласования
  float getSquaredE(const int col) const;

  // Область оценки рассогласования
  // Рассогласование относительно среднего значения (без вессовой аппроксимации)
  float getE1(const int col, const int rec) const;
  // Получить значение минимум рассогласования
  float getMinE1(const int col) const;
  // Получить значение максимума рассогласования
  float getMaxE1(const int col) const;
  // Получить значение среднего рассогласования
  float getAverageE1(const int col) const;
  // Получить значение модуль рассогласования
//  float getModuleE1(const int col) const;
  // Получить значение квадрат рассогласования
  float getSquaredE1(const int col) const;

};
//---------------------------------------------------------------------------
#endif
