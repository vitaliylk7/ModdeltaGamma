//---------------------------------------------------------------------------
#ifndef DataWAH
#define DataWAH
#include <fstream.h>
#include <vector>
#include "Data.h"
#include "Settings.h"
//---------------------------------------------------------------------------
// Класс подготовки данных к вычислению весовой аппроксимации
//---------------------------------------------------------------------------
class DataWA {

protected:
  // Указатель на данные
  const Data* _Data;
  // Вектора для чистки данных в векторах
  vector <objData> tmp_XYZ;
  vector <Column> tmp_Column;
  vector <float> tmp_v;
  vector <vector<float> > tmp_vv;
  // Индексы точек исходных данных попавшие в рамки указанные пользователем
  vector <long> vSubIndex;
  // Координаты точек данных попавшие в рамки указанные пользователем
  vector <objData> vXYZ;
  // Номера колоннок участвующие в вычислении
  vector <Column> vColumn;
  // Данные
  vector <float> vx; // Количество записей
  vector <vector<float> > vData;
  // Среднее значение по каждой характеристике
  vector <float> vAverageValuesColumns;

  // Параметры для уровня
  // Порядковый номер уровня
  int NumLevel;
  // Настройки уровня
  TLevelSettings LevelSettings;

  // Получить значения колонки
  Column getColumn(String Name);
  // Получить строку данных
  int getRecord(const vector <Column> vCol, vector <float> &v, const int rec);
  // Подготовим список средних значений
  void PrepareAverageValueCols(const int countCols);
  // Вычислить среднее значение для каждой характеристике
  void CalcAverageValueCols();

public:
  // Конструктор
  DataWA(const Data* Data_);
  // Конструктор для уровней
  DataWA(const Data* Data_, const int NumLevel_);
  // Конструктор копирования
  DataWA(DataWA *DataWA_);
  // Деструктор
  ~DataWA();
  // Ввод в данные коэффициент анизотропии
  void setAnisotropyFactor(objData anisotropyFactors);
  // Подготовка данных к вычислению
  virtual int Create(){ return 1; };
  // Получить координату
  objData getXYZ(int i) const;
  // Оператор получить значение данных
  float getValue(const int col, const int rec) const;
  // Получить по индексу подиндекс в исходном массиве
  long getSubIndex(const long rec) const;
  // Получить кол-во колонок
  int getCountColumn() const;
  // Получить кол-во записей
  int getCountRecord() const;
  // Получить номер колонки по названию
  int getNameToNumColumn(String value) const;
  // Получить наименования колонки по индесу
  String getNameCol(int value) const;
  // Получить параметры колонки
  Column getCol(const int value) const;
  // Получить среднее значение колонки (характеристики)
  float getAverageValueCol(const int col) const;
};
//---------------------------------------------------------------------------
#endif
