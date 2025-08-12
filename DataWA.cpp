//---------------------------------------------------------------------------
#include <vcl.h>
#pragma hdrstop
#include "DataWA.h"
//---------------------------------------------------------------------------
#pragma package(smart_init)
//---------------------------------------------------------------------------
// Конструктор
//---------------------------------------------------------------------------
DataWA::DataWA(const Data* Data_)
{
  NumLevel = -1;
  _Data = Data_;

}
//---------------------------------------------------------------------------
// Конструктор для уровней
//---------------------------------------------------------------------------
DataWA::DataWA(const Data* Data_, const int NumLevel_)
{
  NumLevel = NumLevel_;
  _Data = Data_;
}
//---------------------------------------------------------------------------
// Деструктор
//---------------------------------------------------------------------------
DataWA::~DataWA()
{

}
//---------------------------------------------------------------------------
// Конструктор копирования
//---------------------------------------------------------------------------
DataWA::DataWA(DataWA *DataWA_) {
  long countCol = DataWA_->getCountColumn();
  long countRec = DataWA_->getCountRecord();

  // Скопируем координаты
  for (long rec = 0; rec < countRec; ++rec) {
    vXYZ.push_back(DataWA_->getXYZ(rec));
    vx.erase(vx.begin(), vx.end());
		vx.swap(tmp_v);
    for (long col = 0; col < countCol; ++col) {
      vx.push_back(DataWA_->getValue(col, rec));
    }
    vData.push_back(vx);
  }

  // Скопируем название колонок
  for (long rec = 0; rec < countCol; ++rec) {
    vColumn.push_back(DataWA_->getCol(rec));
  }

  // Вычислить среднее значение для каждой характеристике
  CalcAverageValueCols();
}
//---------------------------------------------------------------------------
// Ввод в данные коэффициент анизотропии
//---------------------------------------------------------------------------
void DataWA::setAnisotropyFactor(objData anisotropyFactors) {

  for (long rec = 0; rec < vXYZ.size(); ++rec) {
    objData currObjData = vXYZ[rec];
    vXYZ[rec] = currObjData * anisotropyFactors;
  }
}
//---------------------------------------------------------------------------
// Получить значения колонки
//---------------------------------------------------------------------------
Column DataWA::getColumn(String Name)
{
  Column _Column;
  bool bGap;
  String s = Name;
  int iLength = s.Length();
  bGap = false;
  int i = 1;
  while (i <= iLength)
  {
    if (s[i] == ' ')
    {
      bGap = true;
      s.SetLength(i-1);
      break;
    }
    i++;
  }

  if (bGap)
  {
    _Column.n = _Data->getNumberForColumnName(s);
    _Column.bLog10 = true;
    _Column._Criterion.Name = Name;
    if (-1 == _Column.n)
    {
      ShowMessage("Ошибка подготовка данных к вычислению");
    }
  }
  else
  {
    _Column.n = _Data->getNumberForColumnName(s);
    _Column.bLog10 = false;
    _Column._Criterion.Name = Name;
  }

  return _Column;
}
//---------------------------------------------------------------------------
// Получить строку данных
//---------------------------------------------------------------------------
int DataWA::getRecord(const vector <Column> vCol, vector <float> &v,
    const int rec)
{
  Column _Column;
  float fData, fMinCol;
  if ((NumLevel != -1) && (vCol.size() > 1))
  {
    ShowMessage("При работе с уровнями необходим только один признак.");
    return 1;
  }

  for (unsigned int i = 0; i < vCol.size(); ++i)
  {
    _Column = vCol[i];
    fData = _Data->getData(_Column.n, rec);
    // Пропустить сироку в случае если значение не входит в допустимый придел
    // и отбор производиться для уровня
    if (NumLevel != -1)
    {
      if ((fData < LevelSettings.CriterionFrom) ||
          (fData > LevelSettings.CriterionTill))
        return 0;
    }

    if (_Column.bLog10)
    {
      if (0 >= fData)
      {
        // Получим минимум для замены нулей
        fMinCol = _Data->getMinBiggerZero(_Column.n);
        fData = log10(fMinCol);
      }
      else
      {
        fData = log10(fData);
      }
    }
    v.push_back(fData);
  }
  return 0;
}
//---------------------------------------------------------------------------
// Получить координату
//---------------------------------------------------------------------------
objData DataWA::getXYZ(int i) const
{
  return vXYZ[i];
}
//---------------------------------------------------------------------------
// Оператор получить значение данных
//---------------------------------------------------------------------------
float DataWA::getValue(const int col, const int rec) const
{
   return vData[rec][col];
}
//---------------------------------------------------------------------------
// Получить по индексу подиндекс в исходном массиве
//---------------------------------------------------------------------------
long DataWA::getSubIndex(const long rec) const
{
  return vSubIndex[rec];
}
//---------------------------------------------------------------------------
// Получить кол-во колонок
//---------------------------------------------------------------------------
int DataWA::getCountColumn() const
{
  return vColumn.size();
}
//---------------------------------------------------------------------------
// Получить кол-во записей
//---------------------------------------------------------------------------
int DataWA::getCountRecord() const
{
  return vData.size();
}
//---------------------------------------------------------------------------
// Получить номер колонки по названию
//---------------------------------------------------------------------------
int DataWA::getNameToNumColumn(String value) const
{
	for (unsigned int i = 0; i < vColumn.size(); ++i)
  {
  	if (value == vColumn[i]._Criterion.Name)
    	return i;
  }

 	return -1;
}
//---------------------------------------------------------------------------
// Получить наименования колонки по индесу
//---------------------------------------------------------------------------
String DataWA::getNameCol(int value) const
{
  return vColumn[value]._Criterion.Name;
}
//---------------------------------------------------------------------------
// Получить параметры колонки
//---------------------------------------------------------------------------
Column DataWA::getCol(const int value) const
{
  return vColumn[value];
}
//---------------------------------------------------------------------------
// Подготовим список средних значений
//---------------------------------------------------------------------------
void DataWA::PrepareAverageValueCols(const int countCols) {
  vAverageValuesColumns.swap(tmp_v);
  // vAverageValuesColumns.reserve(countCols);
  for (int rec = 0; rec < countCols; ++rec) {
    vAverageValuesColumns.push_back(0.0f);
  }
}
//---------------------------------------------------------------------------
// Вычислить среднее значение для каждой характеристики
//---------------------------------------------------------------------------
void DataWA::CalcAverageValueCols() {
  float valq, valDataq, sq;
  int countCols = vColumn.size();
  int countRecs = vData.size();

  // Подготовим список средних значений
  PrepareAverageValueCols(countCols);
  for (int col = 0; col < countCols; ++col) {
    for (int rec = 0; rec < countRecs; ++rec) {
      sq = vAverageValuesColumns[col];
      valDataq = vData[rec][col];
      valq = valDataq + sq;
      vAverageValuesColumns[col] = valq;
    }
  }

  if (countRecs != 0) {
    for (int col = 0; col < countCols; ++col) {
      vAverageValuesColumns[col] = vAverageValuesColumns[col] / countRecs;
    }
  }
}
//---------------------------------------------------------------------------
// Получить среднее значение колонки (характеристики)
//---------------------------------------------------------------------------
float DataWA::getAverageValueCol(const int col) const {
  return vAverageValuesColumns[col];
}
//---------------------------------------------------------------------------
