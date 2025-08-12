//---------------------------------------------------------------------------
#include <vcl.h>
#include <algorithm>
#pragma hdrstop
#include "ProcessWA.h"
#include "ProgressWork.h"
#include "Utils.h"
#include "ViewApproximation.h"
#include "Math.hpp"
//---------------------------------------------------------------------------
#pragma package(smart_init)
//---------------------------------------------------------------------------
// Заметки
// _dataWA_Area-> - исходные значения в обл. вычисления рассогласования точек
// _DataWA-> - исходные значения в обл. учета точек
// _DataWAAnisotropyFactor-> исходные значения в обл. учета точек с анизотропией
//
//
//---------------------------------------------------------------------------

//---------------------------------------------------------------------------
// Конструкторы
//---------------------------------------------------------------------------
ProcessWA::ProcessWA(const Data *Data_, DataWA *DataWA_, DataWA *dataWA_Area,
  const ParamCalcWA *ParamCalcWA_, const bool bStandart_,
  objData AnisotropyFactor)
{
  NumLevel = -1;
  _Data = Data_;
  _DataWA = DataWA_;
  _dataWA_Area = dataWA_Area;
  _ParamCalcWA = ParamCalcWA_;
  _bStandart = bStandart_;
  _AnisotropyFactor = AnisotropyFactor;
  _DataWAAnisotropyFactor = 0;
}
//---------------------------------------------------------------------------
// Конструктор с учётом уровней
//---------------------------------------------------------------------------
ProcessWA::ProcessWA(const Data *Data_, DataWA *DataWA_, DataWA *dataWA_Area,
  const ParamCalcWA *ParamCalcWA_, const int NumLevel_,
  const bool bStandart_, objData AnisotropyFactor)
{
  NumLevel = NumLevel_;
  _Data = Data_;
  _DataWA = DataWA_;
  _dataWA_Area = dataWA_Area;
  _ParamCalcWA = ParamCalcWA_;
  _bStandart = bStandart_;
  _AnisotropyFactor = AnisotropyFactor;
  _DataWAAnisotropyFactor = 0;
}
//---------------------------------------------------------------------------
// Деструктор
//---------------------------------------------------------------------------
ProcessWA::~ProcessWA()
{
  if (_DataWAAnisotropyFactor != 0) {
    delete _DataWAAnisotropyFactor;
    _DataWAAnisotropyFactor = 0;
  }
}
//---------------------------------------------------------------------------
// Очистка памяти
//---------------------------------------------------------------------------
bool ProcessWA::Clear()
{
  // Удаление данных
  // Стандарт
  vxStandart.swap(tmp_v);
  vStandart.swap(tmp_vv);
  vStandartW.swap(tmp_v);
  vStandartWS.swap(tmp_v);
  vStandartS.swap(tmp_v);
  // А это конечные данные весовой аппроксимации для стандарта
  vxTildeStandart.swap(tmp_v);
  vTildeStandart.swap(tmp_vv);
  // Минимум и максимум весовой аппроксимации для стандарта
  vMinTildeStandart.swap(tmp_v);
  vMaxTildeStandart.swap(tmp_v);

  MinTildeStandart = 0;
  MaxTildeStandart = 0;
  _bStandart = false;
  bStatus = false;

  if (_DataWAAnisotropyFactor != 0) {
    delete _DataWAAnisotropyFactor;
    _DataWAAnisotropyFactor = 0;
  }

  return true;
}
//---------------------------------------------------------------------------
// Получить наименование признака
//---------------------------------------------------------------------------
String ProcessWA::getColName(String s)
{

  int iLength = s.Length();
  int q = 1;
   while (q <= iLength)
   {
     if (s[q] == ' ')
     {
       s.SetLength(q-1);
       s = s + "_lg";
       break;
     }
     q++;
   }

   return s;
}
//---------------------------------------------------------------------------
// Вычисление расстояния между двумя точками
//---------------------------------------------------------------------------
float ProcessWA::CalcR(objData _objData, objData _objNet)
{
  return sqrt( pow((_objData.x - _objNet.x),2) +
               pow((_objData.y - _objNet.y),2) +
               pow((_objData.z - _objNet.z),2)
             );
}
//---------------------------------------------------------------------------
// Вычислить вес
//---------------------------------------------------------------------------
float ProcessWA::CalcW(const float R, const float Beta,
    const float Gamma, const float Alpha)
{
  return 1 / (1 + Beta * pow((R / Gamma),Alpha));
}
//---------------------------------------------------------------------------
// Ввод локальной анизотропии
//---------------------------------------------------------------------------
void ProcessWA::EnterAnisotropyFactor() {
  // Выполним подмену данных для ввода локальной анизотропии
  if (_DataWAAnisotropyFactor != 0) {
    delete _DataWAAnisotropyFactor;
    _DataWAAnisotropyFactor = 0;
  }

  _DataWAAnisotropyFactor = new DataWA(_DataWA);
  _DataWAAnisotropyFactor->setAnisotropyFactor(_AnisotropyFactor);
}
//---------------------------------------------------------------------------
// Очистка данных анизотропии на исходные точки
//---------------------------------------------------------------------------
void ProcessWA::ClearDataStandart() {
  vxStandart.swap(tmp_v);
  vStandart.swap(tmp_vv);
  vStandartW.swap(tmp_v);
  vStandartWS.swap(tmp_v);
  vStandartS.swap(tmp_v);
}
//---------------------------------------------------------------------------
// Подготовка данных анизотропии на исходные точки
//---------------------------------------------------------------------------
void ProcessWA::PrepareDataStandart(const int countCol, const int countRec) {
  vxStandart.reserve(countCol);
  for (long x = 0; x < countCol; x++)
    vxStandart.push_back(0);

  vStandart.reserve(countRec);
  for (long y = 0; y < countRec; y++)
    {
    vStandart.push_back(vxStandart);
    };
  vStandartW.reserve(countRec);
  vStandartWS.reserve(countRec);
  vStandartS.reserve(countRec);
  for (long n = 0; n < countRec; n++)
    {
    vStandartW.push_back(0);
    vStandartWS.push_back(0);
    vStandartS.push_back(0);
    };
}
//---------------------------------------------------------------------------
// Покажем пользователю процент выполнения процесса
//---------------------------------------------------------------------------
void ProcessWA::ViewProgress(const int countRec) {
  if (NumLevel == -1)
    frmProgressWork->Caption = "Состояние процесса...";
  else
    frmProgressWork->Caption = "Состояние процесса. Уровень " +
      IntToStr(NumLevel + 1) + ".";
  frmProgressWork->pb->Progress = 0;
  frmProgressWork->pb->MinValue = 0;
  frmProgressWork->pb->MaxValue = countRec;
  frmProgressWork->Show();

  Application->ProcessMessages();
}
//---------------------------------------------------------------------------
// Вычисление отклонения относительно среднего значения области учёта
//---------------------------------------------------------------------------
void ProcessWA::CalcE(const int countRecArea, const int countColArea) {
  float realValue, e;
  for (long rec = 0; rec < countRecArea; ++rec) {
    // Вычисляем все признаки в одном цикле
    vxE.erase(vxE.begin(), vxE.end());
    for (long col = 0; col < countColArea; ++col) {
      realValue = _dataWA_Area->getValue(col,rec);
      // Вычислить рассогласование относительно среднего значения
      e = realValue - _DataWAAnisotropyFactor->getAverageValueCol(col);
      //e = realValue - ( countRecAreaData *
         /** (countRecAreaData * (realValue
          - _DataWAAnisotropyFactor->getAverageValueCol(col)))
          / (countRecAreaData - 1); */
      vxE.push_back(e);
    }
    vE.push_back(vxE);
  }
}
//---------------------------------------------------------------------------
// Вычисление отклонения относительно среднего значения области оценки рассогласования
//---------------------------------------------------------------------------
void ProcessWA::CalcE1(const int countRecArea, const int countColArea) {
  float realValue, e1;
  for (long rec = 0; rec < countRecArea; ++rec) {
    // Вычисляем все признаки в одном цикле
    vxE1.erase(vxE1.begin(), vxE1.end());
    for (long col = 0; col < countColArea; ++col) {
      realValue = _dataWA_Area->getValue(col,rec);
      // Вычислить рассогласование относительно среднего значения
      e1 = realValue - _dataWA_Area->getAverageValueCol(col);
      //e = realValue - ( countRecAreaData *
         /** (countRecAreaData * (realValue
          - _DataWAAnisotropyFactor->getAverageValueCol(col)))
          / (countRecAreaData - 1); */
      vxE1.push_back(e1);
    }
    vE1.push_back(vxE1);
  }
}
//---------------------------------------------------------------------------
// Вычисление веса и модельного значения
//---------------------------------------------------------------------------
void ProcessWA::CalcWT(const int countRecData, const int countColData)
{
  float Alpha, Beta, Gamma,Sigma;
  Alpha = _ParamCalcWA->Alpha;
  Beta = _ParamCalcWA->Gamma;
  Gamma = _ParamCalcWA->Beta;
  Sigma = _ParamCalcWA->Sigma;
  float W, WS, T, R, E, realValue;
  int countRecAreaData = _dataWA_Area->getCountRecord();// точек в области учета
  objData _objData, _objDataArea;
  float x1,x2,y1,y2,z1,z2;

  // Вычисляем веса для определения коэффициентов микширования
  for (long d = 0; d < countRecData; d++)
  {
    _objData = _DataWAAnisotropyFactor->getXYZ(d);
    for (long n = 0; n < countRecData; ++n)
    {
      _objDataArea = _DataWAAnisotropyFactor->getXYZ(n);
  /*    x1= _objData.x;
      y1= _objData.y;
      z1= _objData.z;
      x2= _objDataArea.x;
      y2= _objDataArea.y;
      z2= _objDataArea.z;
  */
      // Вычислить расстояние
      R = CalcR(_objData, _objDataArea);
      // Вычислить вес
      W = CalcW(R, Beta, Gamma, Alpha);
      // Норма
      vStandartW[n] = vStandartW[n] + W;

    };
  frmProgressWork->pb->Progress++;
  };

  // вычисляем коэффициент микширования
  for (long d = 0; d < countRecData; ++d)
    {
    vStandartS[d] = pow(vStandartW[d], Sigma - 1);
    };
  // Очистка векторов весов
  for (long n = 0; n < countRecData; n++)
    vStandartW[n] = 0;



  for (long n = 0; n < countRecAreaData; ++n)
    {
    _objDataArea = _dataWA_Area->getXYZ(n);
    for (long d = 0; d < countRecData; d++)
      {
      _objData = _DataWAAnisotropyFactor->getXYZ(d);
      // Вычислить расстояние
      R = CalcR(_objData, _objDataArea);
      // Вычислить вес
      if (R == 0)
        W = 0;
      else
        W = CalcW(R, Beta, Gamma, Alpha) * vStandartS[d];
      // Вычисляем все признаки в одном цикле
      //vxE.erase(vxE.begin(), vxE.end());
      for (long col = 0; col < countColData; ++col)
      {
        realValue = _DataWAAnisotropyFactor->getValue(col,d);
        T = W * realValue ;
        vStandart[n][col] = vStandart[n][col] + T;
      }
      // Норма
      vStandartW[n] = vStandartW[n] + W;
    }
    frmProgressWork->pb->Progress++;
  }

}
//---------------------------------------------------------------------------
// Очистка данных для конечного модельного значения
//---------------------------------------------------------------------------
void ProcessWA::ClearTildeData() {

  vxTildeStandart.swap(tmp_v);
  vTildeStandart.swap(tmp_vv);
  // Минимум и максимум весовой аппроксимации для стандарта
  vMinTildeStandart.swap(tmp_v);
  vMaxTildeStandart.swap(tmp_v);

}
//---------------------------------------------------------------------------
// Подготовка данных для конечного модельного значения
//---------------------------------------------------------------------------
void ProcessWA::PrepareTildeData(const int countCol) {

  vMinTildeStandart.reserve(countCol);
  for (long i = 0; i < countCol; i++) {
    vMinTildeStandart.push_back(0);
  }

  vMaxTildeStandart.reserve(countCol);
  for (long i = 0; i < countCol; i++) {
    vMaxTildeStandart.push_back(0);
  }

}
//---------------------------------------------------------------------------
// Вычисление минимума и максимума модельного значения весовой аппроксимации
//---------------------------------------------------------------------------
void ProcessWA::CalcMinMaxTildeStandart(const float TildeStandartT,
  const int col, const int rec)
{

  if (0 == rec) {
    vMinTildeStandart[col] = TildeStandartT;
    vMaxTildeStandart[col] = TildeStandartT;
  }
  else {
    if (vMinTildeStandart[col] > TildeStandartT)
      vMinTildeStandart[col] = TildeStandartT;
    else
    if (vMaxTildeStandart[col] < TildeStandartT)
      vMaxTildeStandart[col] = TildeStandartT;
  }
}
//---------------------------------------------------------------------------
// Ввод фонового значения
//---------------------------------------------------------------------------
void ProcessWA::EnterBackground(float &Background_TildeT, float &Background_W,
  const int numLevel, const Column column)
{
  // При вычислении уровней фон не вводиться
  // (единственное отличие в алгоритме вычисления уровней)
  if (numLevel != -1) {
    Background_TildeT = 0;
    Background_W = 0;
  }
  else {
    Background_TildeT = column._Criterion.TildeT;
    Background_W = column._Criterion.W;
  }

}
//---------------------------------------------------------------------------
// Вычисление весовой аппроксимации
//---------------------------------------------------------------------------
int ProcessWA::Calculation()
{
  bStatus = false;
  // Выполним отбор данных
  if (_DataWA->Create() != 0) {
    return 1;
  }
  else
  if (_dataWA_Area->Create() != 0) {
    return 1;
  }

  // Ввод локальной анизотропии
  EnterAnisotropyFactor();
  int CountRecData = _DataWAAnisotropyFactor->getCountRecord();//точек в области учета
  int CountRecArea = _dataWA_Area->getCountRecord();//точек в области вычислени
  int CountColumnData = _DataWAAnisotropyFactor->getCountColumn();
  // Не выполнять вычисления в случае если отобранных точек 0
  if (CountRecData == 0) {
    bStatus = true;
    return 0;
  }

  // Очистка данных анизотропии на исходные точки
  ClearDataStandart();
  // Подготовка данных анизотропии на исходные точки
  PrepareDataStandart(CountColumnData, CountRecData);
  // Покажем пользователю процент выполнения процесса
//  ViewProgress(CountRecData + CountRecArea);
  // Вычисление веса и модельного значения
  CalcWT(CountRecData, CountColumnData);
//  Application->ProcessMessages();

  // Конечное вычисление весовой аппроксимации на исходные точки
  // Очистка данных для конечного модельного значения
  ClearTildeData();
  // Подготовка данных для конечного модельного значения
  PrepareTildeData(CountRecData);

  float TildeStandartT = 0;
  float TildeT, Background_TildeT, Background_W, T, d;
  Column _Column;
  for (long recArea = 0; recArea < CountRecArea; ++recArea)
  {
    // Очистим запись
    vxTildeStandart.erase(vxTildeStandart.begin(), vxTildeStandart.end());
    vxD.erase(vxD.begin(), vxD.end());
    for (long col = 0; col < CountColumnData; ++col)
    {
      _Column = _DataWAAnisotropyFactor->getCol(col);
   //   T = _DataWAAnisotropyFactor->getValue(col,recArea);

      // Ввод фонового значения
      EnterBackground(Background_TildeT, Background_W, NumLevel, _Column);

      TildeStandartT = (vStandart[recArea][col]
        + (Background_TildeT * Background_W))
          / (vStandartW[recArea] + Background_W);
      //TildeStandartT = vStandart[_dataWA_Area->getSubIndex[recArea]][col]
      //    / vStandartW[_dataWA_Area->getSubIndex[recArea]];


      // убираем из модельного значения влияние исходной точки,
      // лежащей в той же точке пространства
          TildeStandartT = (CountRecArea * TildeStandartT
          - _dataWA_Area->getValue(col,recArea)) / (CountRecArea - 1);
     //TildeStandartT = (CountRecData * TildeStandartT
     //- _dataWA_Area->getValue(col,_dataWA_Area->getSubIndex[recArea]))
      // ( vStandartW[_dataWA_Area->getSubIndex[recArea]]
      //- vStandartS[_dataWA_Area->getSubIndex[recArea]]);



      // Вычислим отклонение
      d = _dataWA_Area->getValue(col,recArea) - TildeStandartT;



      vxTildeStandart.push_back(TildeStandartT);
      vxD.push_back(d);

     // Вычисление минимума и максимума модельного значения
     CalcMinMaxTildeStandart(TildeStandartT, col, recArea);

    }
    vTildeStandart.push_back(vxTildeStandart);
    vD.push_back(vxD);
  }

  CalcStatisticsD(CountRecArea, CountColumnData);
  // Вычисление отклонения относительно среднего значения
  int countColArea = _dataWA_Area->getCountColumn();
  CalcE(CountRecArea, countColArea);
  CalcStatisticsE(CountRecArea, countColArea);
  CalcE1(CountRecArea, countColArea);
  CalcStatisticsE1(CountRecArea, countColArea);
//  frmProgressWork->Close();
  bStatus = true;
  return 0;
}
//---------------------------------------------------------------------------
// Очистка статистики рассогласования
//---------------------------------------------------------------------------
void ProcessWA::ClearStatisticsD()
{
  vMinD.swap(tmp_v);     // Минимум рассогласования
  vMaxD.swap(tmp_v);     // Максимум рассогласования
  vAverageD.swap(tmp_v); // Среднее рассогласования
  vModuleD.swap(tmp_v);  // Модуль рассогласования
  vSquaredD.swap(tmp_v); // Квадрат рассогласования

}
//---------------------------------------------------------------------------
// Подготовка статистики рассогласовани
//---------------------------------------------------------------------------
void ProcessWA::PrepareStatisticsD(const int countCol)
{
  vMinD.reserve(countCol);      // Минимум рассогласования
  vMaxD.reserve(countCol);      // Максимум рассогласования
  vAverageD.reserve(countCol);  // Среднее рассогласования
  vModuleD.reserve(countCol);   // Модуль рассогласования
  vSquaredD.reserve(countCol);  // Квадрат рассогласования

  // Заполним для индексного доступа к массиву
  for (int i = 0; i < countCol; ++i) {
    vMinD.push_back(0);
    vMaxD.push_back(0);
    vAverageD.push_back(0);
    vModuleD.push_back(0);
    vSquaredD.push_back(0);
  }
}
//---------------------------------------------------------------------------
// Вычисление статистики рассогласования
//---------------------------------------------------------------------------
void ProcessWA::CalcStatisticsD(const int countRec, const int countCol)
{
  ClearStatisticsD();    // Очистка статистики рассогласования
  PrepareStatisticsD(countCol);  // Подготовка статистики рассогласовани

  float d, modul;
  for (int rec = 0; rec < countRec; ++rec)
  {
    for (int col = 0; col < countCol; ++col)
    {
      d = vD[rec][col];
      vAverageD[col] += d;

      if (d > 0 )
         vModuleD[col] += d;
      else
         vModuleD[col] += (d * -1);

      vSquaredD[col] += (d * d);
      // Вычисление минимума и максимума весовой аппроксимации
      if (0 == rec)
      {
       vMinD[col] = d;
       vMaxD[col] = d;
      }
      else
      {
        if (vMinD[col] > d)
         vMinD[col] = d;
        else
        if (vMaxD[col] < d)
         vMaxD[col] = d;
      }
    }
  }

  if (countRec != 0) {
    for (int col = 0; col < countCol; ++col) {
      vAverageD[col] = vAverageD[col] / countRec;
      vModuleD[col] = vModuleD[col] / countRec;
      vSquaredD[col] = vSquaredD[col] / countRec;
    }
  }
  else {
    ShowMessage("X: [ProcessWA_BetaStep::CalcStatisticsD] Деление на 0!!!");
  }
}
//---------------------------------------------------------------------------
// Очистка статистики рассогласования  области учета
//---------------------------------------------------------------------------
void ProcessWA::ClearStatisticsE()
{
  vMinE.swap(tmp_v);     // Минимум рассогласования
  vMaxE.swap(tmp_v);     // Максимум рассогласования
  vAverageE.swap(tmp_v); // Среднее рассогласования
//  vModuleE.swap(tmp_v);  // Модуль рассогласования
  vSquaredE.swap(tmp_v); // Квадрат рассогласования

}
//---------------------------------------------------------------------------
// Очистка статистики рассогласования области рассогласования
//---------------------------------------------------------------------------
void ProcessWA::ClearStatisticsE1()
{
  vMinE1.swap(tmp_v);     // Минимум рассогласования
  vMaxE1.swap(tmp_v);     // Максимум рассогласования
  vAverageE1.swap(tmp_v); // Среднее рассогласования
//  vModuleE.swap(tmp_v);  // Модуль рассогласования
  vSquaredE1.swap(tmp_v); // Квадрат рассогласования

}
//---------------------------------------------------------------------------
// Подготовка статистики рассогласовани области учёта
//---------------------------------------------------------------------------
void ProcessWA::PrepareStatisticsE(const int countCol)
{
  vMinE.reserve(countCol);      // Минимум рассогласования
  vMaxE.reserve(countCol);      // Максимум рассогласования
  vAverageE.reserve(countCol);  // Среднее рассогласования
 // vModuleE.reserve(countCol);   // Модуль рассогласования
  vSquaredE.reserve(countCol);  // Квадрат рассогласования

  // Заполним для индексного доступа к массиву
  for (int i = 0; i < countCol; ++i) {
    vMinE.push_back(0);
    vMaxE.push_back(0);
    vAverageE.push_back(0);
//    vModuleE.push_back(0);
    vSquaredE.push_back(0);
  }
}
//---------------------------------------------------------------------------
// Подготовка статистики рассогласовани области оценки
//---------------------------------------------------------------------------
void ProcessWA::PrepareStatisticsE1(const int countCol)
{
  vMinE1.reserve(countCol);      // Минимум рассогласования
  vMaxE1.reserve(countCol);      // Максимум рассогласования
  vAverageE1.reserve(countCol);  // Среднее рассогласования
 // vModuleE.reserve(countCol);   // Модуль рассогласования
  vSquaredE1.reserve(countCol);  // Квадрат рассогласования

  // Заполним для индексного доступа к массиву
  for (int i = 0; i < countCol; ++i) {
    vMinE1.push_back(0);
    vMaxE1.push_back(0);
    vAverageE1.push_back(0);
//    vModuleE1.push_back(0);
    vSquaredE1.push_back(0);
  }
}
//---------------------------------------------------------------------------
// Вычисление статистики рассогласования с областью учёта данных
//---------------------------------------------------------------------------
void ProcessWA::CalcStatisticsE(const int countRec, const int countCol)
{
  ClearStatisticsE();    // Очистка статистики рассогласования
  PrepareStatisticsE(countCol);  // Подготовка статистики рассогласовани

  float e, modul;
  for (int rec = 0; rec < countRec; ++rec)
  {
    for (int col = 0; col < countCol; ++col)
    {
      e = vE[rec][col];
      vAverageE[col] += e;

//      if (e > 0 )
//         vModuleE[col] += e;
//      else
//         vModuleE[col] += (e * -1);

      vSquaredE[col] += (e * e);
      // Вычисление минимума и максимума весовой аппроксимации
      if (0 == rec)
      {
       vMinE[col] = e;
       vMaxE[col] = e;
      }
      else
      {
        if (vMinE[col] > e)
         vMinE[col] = e;
        else
        if (vMaxE[col] < e)
         vMaxE[col] = e;
      }
    }
  }

  if (countRec != 0) {
    for (int col = 0; col < countCol; ++col) {
      vAverageE[col] = vAverageE[col] / countRec;
 //     vModuleE[col] = vModuleE[col] / countRec;
      vSquaredE[col] = vSquaredE[col] / countRec;
    }
  }
  else {
    ShowMessage("X: [ProcessWA_BetaStep::CalcStatisticsE] Деление на 0!!!");
  }
}
//---------------------------------------------------------------------------
// Вычисление статистики рассогласования для области оценки рассогласования
//---------------------------------------------------------------------------
void ProcessWA::CalcStatisticsE1(const int countRec, const int countCol)
{
  ClearStatisticsE1();    // Очистка статистики рассогласования
  PrepareStatisticsE1(countCol);  // Подготовка статистики рассогласовани

  float e, modul;
  for (int rec = 0; rec < countRec; ++rec)
  {
    for (int col = 0; col < countCol; ++col)
    {
      e = vE1[rec][col];
      vAverageE1[col] += e;

//      if (e > 0 )
//         vModuleE[col] += e;
//      else
//         vModuleE[col] += (e * -1);

      vSquaredE1[col] += (e * e);
      // Вычисление минимума и максимума весовой аппроксимации
      if (0 == rec)
      {
       vMinE1[col] = e;
       vMaxE1[col] = e;
      }
      else
      {
        if (vMinE1[col] > e)
         vMinE1[col] = e;
        else
        if (vMaxE1[col] < e)
         vMaxE1[col] = e;
      }
    }
  }

  if (countRec != 0) {
    for (int col = 0; col < countCol; ++col) {
      vAverageE1[col] = vAverageE1[col] / countRec;
 //     vModuleE[col] = vModuleE[col] / countRec;
      vSquaredE1[col] = vSquaredE1[col] / countRec;
    }
  }
  else {
    ShowMessage("X: [ProcessWA_BetaStep::CalcStatisticsE1] Деление на 0!!!");
  }
}
//---------------------------------------------------------------------------
// Сохранить весовую аппроксимацию на исходные точки в файл
//---------------------------------------------------------------------------
bool ProcessWA::SaveStandart(String FileName)
{
  objData _objData;
  long CountRow;
  long CountColumnAprox;
  int tmpT;
  CountRow = vTildeStandart.size();
  CountColumnAprox = _DataWA->getCountColumn();

  //  Работа с устройством вывода
  try
  {
    ofstream outFirmsFile(FileName.c_str(), ios::out);
    outFirmsFile << (4 + CountColumnAprox) << endl; // iAmo_Column
    outFirmsFile << 'x' << '\t' << 'y' << '\t' << 'z' << '\t' << "W" << '\t';

    long tmpCountColumnAprox = CountColumnAprox -1;
    int iLength;
    String s;
    for (long i = 0; i < CountColumnAprox; i++){
      s = _DataWA->getNameCol(i);
      iLength = s.Length();
      int q = 1;
       while (q <= iLength)
       {
         if (s[q] == ' ')
         {
           s.SetLength(q-1);
           s = s + "_lg";
           break;
         }
         q++;
       }

       outFirmsFile << s.c_str();

       if (tmpCountColumnAprox == i)
         outFirmsFile << endl;
       else
         outFirmsFile << '\t';
    }

    for (long rec = 0; rec < CountRow; ++rec)
    {
      _objData = getStXYZ(rec);
      s = FormatFloat("0.00000",_objData.x);
      outFirmsFile << s.c_str() << '\t';
      s = FormatFloat("0.00000",_objData.y);
      outFirmsFile << s.c_str() << '\t';
      s = FormatFloat("0.00000",_objData.z);
      outFirmsFile << s.c_str() << '\t';
      s = FormatFloat("0.00000",vStandartW[rec]);
      outFirmsFile << s.c_str() << '\t';
      for (long col = 0; col < CountColumnAprox; ++col)
      {
        s = FormatFloat("0.00000",vTildeStandart[rec][col]);
        outFirmsFile << s.c_str();
        if (tmpCountColumnAprox == col)
          outFirmsFile << endl;
        else
          outFirmsFile << '\t';
      }
    }

    outFirmsFile.close();
  }
  __except(EXCEPTION_EXECUTE_HANDLER)
  {
    // outFirmsFile.close();
    ShowMessage("Ошибка сохранения файла на исходные точки!");
    return false;
  }

  return true;
}
//---------------------------------------------------------------------------
// Сохранить весовую аппроксимацию в файл
//---------------------------------------------------------------------------
bool ProcessWA::SaveModel(String FileName)
{
  return false;
}
//---------------------------------------------------------------------------
// Сохранить результат
//---------------------------------------------------------------------------
bool ProcessWA::SaveResult()
{
  if (bStatus != true){
    ShowMessage("Данные не сформированы");
    return false;
  }

  String sFileName;

  // Сохранить аппроксимацию на исходные точки
  if (_bStandart == true)
  {
    sFileName = getFileNameSave("Модель (исходные точки)",
    	_Data->getFileName());
    if (sFileName != "")
      SaveStandart(sFileName);
  }

  // Сохранить модель весовой аппроксимации
  sFileName = getFileNameSave("Модель (сетка)");
  if (sFileName != "")
     SaveModel(sFileName);

  return true;
}
//---------------------------------------------------------------------------
// Показать значения результата в таблице
//---------------------------------------------------------------------------
bool ProcessWA::VisualResultText()
{
  String LevelName;
  if (NumLevel == -1)
    LevelName = "";
  else
    LevelName = "Уровень " + IntToStr(NumLevel + 1) + ". ";

  frmViewApproximation = new TfrmViewApproximation(Application, 0,
      LevelName + "Весовая аппроксимация на сетку", this);

  if (_bStandart)
  {
    frmViewApproximation = new TfrmViewApproximation(Application, 1,
      LevelName + "Весовая аппроксимация на исходные точки", this);
  }

  return true;
}
//===========================================================================
// Интерфейс St
//===========================================================================
// Получить реальное значение характеристики
//---------------------------------------------------------------------------
float ProcessWA::getRealValue(const int col, const int rec) const {
  return _dataWA_Area->getValue(col, rec);
}
//---------------------------------------------------------------------------
// Получить среднее значение характеристики в области учёта
//---------------------------------------------------------------------------
float ProcessWA::getAverageData(const int col) const
{
 return _DataWAAnisotropyFactor->getAverageValueCol(col);
}
//---------------------------------------------------------------------------
// Получить среднее значение характеристики в области оценки
//---------------------------------------------------------------------------
float ProcessWA::getAverageArea(const int col) const
{
 return _dataWA_Area->getAverageValueCol(col);
}
//---------------------------------------------------------------------------
// Получить значение в.а. на исходные точки по номеру колонки и номеру записи
//---------------------------------------------------------------------------
float ProcessWA::getStT(const int col, const int rec) const {
  return vTildeStandart[rec][col];
}
//---------------------------------------------------------------------------
// Получить значение веса по номеру записи для в.а. на исходные точки
//---------------------------------------------------------------------------
float ProcessWA::getStW(const int rec) const
{
  return vStandartW[rec];
}
//---------------------------------------------------------------------------
// Получить минимальное значения веса
//---------------------------------------------------------------------------
float ProcessWA::getStMinW()
{
  float *p;
  p = min_element(vStandartW.begin(), vStandartW.end());
  return *p;
}
//---------------------------------------------------------------------------
// Получить максимальное значения веса
//---------------------------------------------------------------------------
float ProcessWA::getStMaxW()
{
  float *p;
  p = max_element(vStandartW.begin(), vStandartW.end());
  return *p;
}

//---------------------------------------------------------------------------
// Получить номер колонки по названию для в.а. на исходные точки
//---------------------------------------------------------------------------
int ProcessWA::getStNumColumn(String value) const
{
  return _dataWA_Area->getNameToNumColumn(value);
}
//---------------------------------------------------------------------------
// Получить координаты сетки по значению номера записи для в.а. на исходные точки
//---------------------------------------------------------------------------
objData ProcessWA::getStXYZ(const int rec) const {

  return _dataWA_Area->getXYZ(rec);
}
//---------------------------------------------------------------------------
// Получить количество признаков для в.а. на исходные точки
//---------------------------------------------------------------------------
int ProcessWA::getStCountCol() const
{
  return _dataWA_Area->getCountColumn();
}
//---------------------------------------------------------------------------
// Получить количество записей для в.а. на исходные точки
//---------------------------------------------------------------------------
int ProcessWA::getStCountRec() const
{
  return _dataWA_Area->getCountRecord();
}
//---------------------------------------------------------------------------
// Получить наименование колонки по значению индекса для в.а. на исходные точки
//---------------------------------------------------------------------------
String ProcessWA::getStNameCol(int value) const
{
  return _dataWA_Area->getNameCol(value);
}

// ==========================================================================

//---------------------------------------------------------------------------
// Получить значение рассогласования
//---------------------------------------------------------------------------
float ProcessWA::getD(const int col, const int rec) const {
  return vD[rec][col];
}
//---------------------------------------------------------------------------
// Получить значение минимум рассогласования
//---------------------------------------------------------------------------
float ProcessWA::getMinD(const int col) const {
  return vMinD[col];
}
//---------------------------------------------------------------------------
// Получить значение максимума рассогласования
//---------------------------------------------------------------------------
float ProcessWA::getMaxD(const int col) const {
  return vMaxD[col];
}
//---------------------------------------------------------------------------
// Получить значение среднего рассогласования
//---------------------------------------------------------------------------
float ProcessWA::getAverageD(const int col) const {
  return vAverageD[col];
}
//---------------------------------------------------------------------------
// Получить значение модуль рассогласования
//---------------------------------------------------------------------------
float ProcessWA::getModuleD(const int col) const {
  return vModuleD[col];
}
//---------------------------------------------------------------------------
// Получить значение квадрат рассогласования
//---------------------------------------------------------------------------
float ProcessWA::getSquaredD(const int col) const {
  return vSquaredD[col];
}
//---------------------------------------------------------------------------
// Получить значение бета
//---------------------------------------------------------------------------
float ProcessWA::getBeta() const {
  return _ParamCalcWA->Beta;
}

// ==========================================================================

//---------------------------------------------------------------------------
// Рассогласование относительно среднего значения (без вессовой аппроксимации)
// для области учёта
//---------------------------------------------------------------------------
float ProcessWA::getE(const int col, const int rec) const {
  return vE[rec][col];
}
//---------------------------------------------------------------------------
// Получить значение минимум рассогласования
//---------------------------------------------------------------------------
float ProcessWA::getMinE(const int col) const {
  return vMinE[col];
}
//---------------------------------------------------------------------------
// Получить значение максимума рассогласования
//---------------------------------------------------------------------------
float ProcessWA::getMaxE(const int col) const {
  return vMaxE[col];
}
//---------------------------------------------------------------------------
// Получить значение среднего рассогласования
//---------------------------------------------------------------------------
float ProcessWA::getAverageE(const int col) const {
  return vAverageE[col];
}
//---------------------------------------------------------------------------
// Получить значение модуль рассогласования
//---------------------------------------------------------------------------
//float ProcessWA::getModuleE(const int col) const {
//  return 0; //vModuleE[col];
//}
//---------------------------------------------------------------------------
// Получить значение квадрат рассогласования
//---------------------------------------------------------------------------
float ProcessWA::getSquaredE(const int col) const {
  return vSquaredE[col];
}
//---------------------------------------------------------------------------
//---------------------------------------------------------------------------
// Рассогласование относительно среднего значения (без вессовой аппроксимации)
// для области оценки рассогласования
//---------------------------------------------------------------------------
float ProcessWA::getE1(const int col, const int rec) const {
  return vE1[rec][col];
}
//---------------------------------------------------------------------------
// Получить значение минимум рассогласования
//---------------------------------------------------------------------------
float ProcessWA::getMinE1(const int col) const {
  return vMinE1[col];
}
//---------------------------------------------------------------------------
// Получить значение максимума рассогласования
//---------------------------------------------------------------------------
float ProcessWA::getMaxE1(const int col) const {
  return vMaxE1[col];
}
//---------------------------------------------------------------------------
// Получить значение среднего рассогласования
//---------------------------------------------------------------------------
float ProcessWA::getAverageE1(const int col) const {
  return vAverageE1[col];
}
//---------------------------------------------------------------------------
// Получить значение модуль рассогласования
//---------------------------------------------------------------------------
//float ProcessWA::getModuleE1(const int col) const {
//  return 0; //vModuleE1[col];
//}
//---------------------------------------------------------------------------
// Получить значение квадрат рассогласования
//---------------------------------------------------------------------------
float ProcessWA::getSquaredE1(const int col) const {
  return vSquaredE1[col];
}
//---------------------------------------------------------------------------
