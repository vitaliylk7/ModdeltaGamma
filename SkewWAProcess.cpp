//---------------------------------------------------------------------------
#include <vcl.h>
#pragma hdrstop
#include "SkewWAProcess.h"
//---------------------------------------------------------------------------
#pragma package(smart_init)

// ***************
// * Конструктор *
// ***************
SkewWAProcess::SkewWAProcess(const Data *Data_, const Settings *Settings_)
 : WeigthApproximationProcess(Data_, Settings_)
{

}

// ***************************************
// * Построение сетки для косого сечения *
// ***************************************
bool SkewWAProcess::CreateNet() const
{
  bStatus = false;
  // Объявим координаты точек плоскости
  Coordinate _TopRightPoint;
  Coordinate _TopLeftPoint;
  Coordinate _BottomRightPoint;
  Coordinate _BottomLeftPoint;

  // Длина шага по x и y(относительно самой плоскости)
  float StepBase, StepHeight;
  // Кол-во шагов
  int CountStepBase, CountStepHeight;

  // Получаем все настройки из Settings
  _TopRightPoint = _Settings->TopRightPoint;
  _TopLeftPoint = _Settings->TopLeftPoint;
  _BottomRightPoint = _Settings->BottomRightPoint;
  _BottomLeftPoint = _Settings->BottomLeftPoint;

  StepBase = _Settings->StepNet.x;
  StepHeight = _Settings->StepNet.y;

  // Вычисляем длину оси котрая пересекает
  LBase = sqrt(pow(_BottomRightPoint.x - _BottomLeftPoint.x, 2) +
               pow(_BottomRightPoint.y - _BottomLeftPoint.y,2) +
               pow(_BottomRightPoint.z - _BottomLeftPoint.z,2));

  if (0 == LBase)
   CountStepBase = 0;
  else {
   CountStepBase = abs(LBase / StepBase);
   if (0 == CountStepBase)
    CountStepBase = 1;
  }
  // Для оси z
  LHeight = sqrt(pow(_BottomRightPoint.x - _TopRightPoint.x, 2) +
                 pow(_BottomRightPoint.y - _TopRightPoint.y,2) +
                 pow(_BottomRightPoint.z - _TopRightPoint.z,2));

  if (0 == LHeight)
   CountStepHeight = 0;
  else {
   CountStepHeight = abs(LHeight / StepHeight);
   if (0 == CountStepHeight)
    CountStepHeight = 1;
  }

  // Проветка шага сетки
  if ((0 >= StepBase) || (0 >= StepHeight)){
   ShowMessage("Шаг сетки не должен быть равен 0");
   return false;
  }
  // Проверка возможности построения сетки
  if ((0 == CountStepHeight)||(0 == CountStepHeight)){
   ShowMessage("Не возможно с заданными границами обл. апроксимации построить сетку");
   return false;
  }

  // Получим название оси, которой параллельна наша плоскость
  String sPlane = _Settings->WhichParallelPlane;

  if (sPlane == "x")
    xNetSkewSectionBuild(_TopRightPoint, _TopLeftPoint, _BottomRightPoint,
                    _BottomLeftPoint, LBase, LHeight, StepBase, StepHeight,
                    CountStepBase, CountStepHeight);
  else
  if (sPlane == "y")
    yNetSkewSectionBuild(_TopRightPoint, _TopLeftPoint, _BottomRightPoint,
                    _BottomLeftPoint, LBase, LHeight, StepBase, StepHeight,
                    CountStepBase, CountStepHeight);
  else
  if (sPlane == "z")
    zNetSkewSectionBuild(_TopRightPoint, _TopLeftPoint, _BottomRightPoint,
                    _BottomLeftPoint, LBase, LHeight, StepBase, StepHeight,
                    CountStepBase, CountStepHeight);
  else {
    ShowMessage("Не верно указано значение плоскости для которой параллельно сечение!");
    return false;
  }


  return true;
}

// *******************************************************
// * Построение сетки для косого сечения параллельного x *
// *******************************************************
bool SkewWAProcess::xNetSkewSectionBuild(Coordinate _TopRightPoint,
          Coordinate _TopLeftPoint, Coordinate _BottomRightPoint,
          Coordinate _BottomLeftPoint, float LBase, float LHeight,
          float StepBase, float StepHeight, int CountStepBase,
          int CountStepHeight)
{
  bStatus = false;
  // Для вычисления, так как нужно менять местами если y2 < y1, z2 < z1, x2 < x1
  Coordinate tmp1, tmp2;

  // Проверка границ сетки
  if ((_BottomRightPoint.z != _TopRightPoint.z) ||
      (_BottomLeftPoint.y  != _TopLeftPoint.y))
  {
     ShowMessage("Не верно указанны границы аппроксимации");
     return false;
  }

  // Меняем местами в случае необходимости
  if (_BottomLeftPoint.z < _BottomRightPoint.z)
  {
   tmp1 = _BottomLeftPoint;
   tmp2 = _BottomRightPoint;
   _BottomLeftPoint = tmp2;
   _BottomRightPoint = tmp1;

   tmp1 = _TopLeftPoint;
   tmp2 = _TopRightPoint;
   _TopLeftPoint = tmp2;
   _TopRightPoint = tmp1;
  }

  // Удаление данных
  vNet.swap(tmp_Net);

  // Построение линии сечения
  vector <objNet> vSkewLine;

  objNet _objNet;

  _objNet.x = _BottomRightPoint.x;
  _objNet.y = _BottomRightPoint.y;
  _objNet.z = _BottomRightPoint.z;
  vSkewLine.push_back(_objNet);

  for (int i = 1; i < CountStepBase; i++){
      _objNet.y = _BottomRightPoint.y + (_BottomLeftPoint.y - _BottomRightPoint.y) / StepBase * i;
      _objNet.z = _BottomRightPoint.z + (_BottomLeftPoint.z - _BottomRightPoint.z) / StepBase * i;
      _objNet.x = _BottomRightPoint.x;
      vSkewLine.push_back(_objNet);
  }

  // Построение сетки вдоль x

  objNet _objNet_x;
  for (int j = 0; j < CountStepHeight; j++){
    for (int q = 0; q < vSkewLine.size(); q++){

       _objNet = vSkewLine[q];

       _objNet_x.y = _objNet.y;
       _objNet_x.z = _objNet.z;
       _objNet_x.x = _objNet.x + StepHeight * j;

       vNet.push_back(_objNet_x);
    }
  }

  return true;
}

// *******************************************************
// * Построение сетки для косого сечения параллельного y *
// *******************************************************
bool SkewWAProcess::yNetSkewSectionBuild(Coordinate _TopRightPoint,
          Coordinate _TopLeftPoint, Coordinate _BottomRightPoint,
          Coordinate _BottomLeftPoint, float LBase, float LHeight,
          float StepBase, float StepHeight, int CountStepBase,
          int CountStepHeight)
{
  bStatus = false;
  // Для вычисления, так как нужно менять местами если y2 < y1, z2 < z1, x2 < x1
  Coordinate tmp1, tmp2;

  // Проверка границ сетки
  if ((_BottomRightPoint.z != _TopRightPoint.z) ||
      (_BottomLeftPoint.x  != _TopLeftPoint.x))
  {
     ShowMessage("Не верно указанны границы аппроксимации");
     return false;
  }

  // Меняем местами в случае необходимости
  if (_BottomLeftPoint.x < _BottomRightPoint.x)
  {
   tmp1 = _BottomLeftPoint;
   tmp2 = _BottomRightPoint;
   _BottomLeftPoint = tmp2;
   _BottomRightPoint = tmp1;

   tmp1 = _TopLeftPoint;
   tmp2 = _TopRightPoint;
   _TopLeftPoint = tmp2;
   _TopRightPoint = tmp1;
  }

  // Удаление данных
  vNet.swap(tmp_Net);

  // Построение линии сечения
  vector <objNet> vSkewLine;

  objNet _objNet;

  _objNet.x = _BottomRightPoint.x;
  _objNet.y = _BottomRightPoint.y;
  _objNet.z = _BottomRightPoint.z;
  vSkewLine.push_back(_objNet);

  for (int i = 1; i < CountStepBase; i++){
      _objNet.z = _BottomRightPoint.z + (_BottomLeftPoint.z - _BottomRightPoint.z) / StepBase * i;
      _objNet.x = _BottomRightPoint.x + (_BottomLeftPoint.x - _BottomRightPoint.x) / StepBase * i;
      _objNet.y = _BottomRightPoint.y;
      vSkewLine.push_back(_objNet);
  }

  // Построение сетки вдоль y
  objNet _objNet_y;
  for (int j = 0; j < CountStepHeight; j++){
    for (int q = 0; q < vSkewLine.size(); q++){

       _objNet = vSkewLine[q];

       _objNet_y.z = _objNet.z;
       _objNet_y.x = _objNet.x;
       _objNet_y.y = _objNet.y + StepHeight * j;

       vNet.push_back(_objNet_y);
    }
  }

  return true;
}

// *******************************************************
// * Построение сетки для косого сечения параллельного z *
// *******************************************************
bool SkewWAProcess::zNetSkewSectionBuild(Coordinate _TopRightPoint,
          Coordinate _TopLeftPoint, Coordinate _BottomRightPoint,
          Coordinate _BottomLeftPoint, float LBase, float LHeight,
          float StepBase, float StepHeight, int CountStepBase,
          int CountStepHeight)
{
  bStatus = false;
  // Для вычисления, так как нужно менять местами если y2 < y1, z2 < z1, x2 < x1
  Coordinate tmp1, tmp2;

  // Проверка границ сетки
  if ((_BottomRightPoint.x != _TopRightPoint.x) ||
      (_BottomLeftPoint.y  != _TopLeftPoint.y))
  {
     ShowMessage("Не верно указанны границы аппроксимации");
     return false;
  }

  // Меняем местами в случае необходимости
  if (_BottomLeftPoint.y < _BottomRightPoint.y)
  {
   tmp1 = _BottomLeftPoint;
   tmp2 = _BottomRightPoint;
   _BottomLeftPoint = tmp2;
   _BottomRightPoint = tmp1;

   tmp1 = _TopLeftPoint;
   tmp2 = _TopRightPoint;
   _TopLeftPoint = tmp2;
   _TopRightPoint = tmp1;
  }

  // Удаление данных
  vNet.swap(tmp_Net);

  // Построение линии сечения
  vector <objNet> vSkewLine;

  objNet _objNet;

  _objNet.x = _BottomRightPoint.x;
  _objNet.y = _BottomRightPoint.y;
  _objNet.z = _BottomRightPoint.z;
  vSkewLine.push_back(_objNet);

  for (int i = 1; i < CountStepBase; i++){
      _objNet.x = _BottomRightPoint.x + (_BottomLeftPoint.x - _BottomRightPoint.x) / StepBase * i;
      _objNet.y = _BottomRightPoint.y + (_BottomLeftPoint.y - _BottomRightPoint.y) / StepBase * i;
      _objNet.z = _BottomRightPoint.z;
      vSkewLine.push_back(_objNet);
  }

  // Построение сетки вдоль y
  objNet _objNet_z;
  for (int j = 0; j < CountStepHeight; j++){
    for (int q = 0; q < vSkewLine.size(); q++){

       _objNet = vSkewLine[q];

       _objNet_z.x = _objNet.x;
       _objNet_z.y = _objNet.y;
       _objNet_z.z = _objNet.z + StepHeight * j;

       vNet.push_back(_objNet_z);
    }
  }

  return true;
}

// **********************************
// * Подготовка данных к вычислению *
// **********************************
bool SkewWAProcess::CreateData() const
{
  bStatus = false;
  float xMin, xMax;
  float yMin, yMax;
  float zMin, zMax;
  long x, y, z;
  long CountColumnCriterion;
  long CountDataRow;
  long NumColumn;
  FromTill tmpScopeDataAprox;

  tmpScopeDataAprox = _Settings->xScopeDataAprox;
  xMin = tmpScopeDataAprox.From;
  xMax = tmpScopeDataAprox.Till;

  tmpScopeDataAprox = _Settings->yScopeDataAprox;
  yMin = tmpScopeDataAprox.From;
  yMax = tmpScopeDataAprox.Till;

  tmpScopeDataAprox = _Settings->zScopeDataAprox;
  zMin = tmpScopeDataAprox.From;
  zMax = tmpScopeDataAprox.Till;

  CountColumnCriterion = _Settings->getCountCriterion();
  if (0 == CountColumnCriterion){
    ShowMessage("Не выбраны признаки");
    return false;
  }
  CountDataRow = _Data->getCountRecord();
  x = _Data->getNumberForColumnName(_Settings->NameX);
  y = _Data->getNumberForColumnName(_Settings->NameY);
  z = _Data->getNumberForColumnName(_Settings->NameZ);

  // Удаление данных
  vXYZ.swap(tmp_XYZ);

  // Сохраним номера всех графов участвующих в вычисленнии и проставим статус log10
  vColumn.swap(tmp_Column);

  Column _Column;
  String s;
  bool bGap;
  for (long Col = 0; Col < CountColumnCriterion; Col++){
    s = _Settings->getCriterion(Col);
    int iLength = s.Length();
    bGap = false;
    int i = 1;
    while (i <= iLength){
     if (s[i] == ' '){
      bGap = true;
      s.SetLength(i-1);
      break;
     }
     i++;
    }
    if (bGap){
      _Column.n = _Data->getNumberForColumnName(s);
      _Column.bLog10 = true;
      if (-1 == _Column.n){
       ShowMessage("Ошибка подготовка данных к вычислению");
       return false;
      }
    }
    else {
     _Column.n = _Data->getNumberForColumnName(s);
     _Column.bLog10 = false;
    }
    vColumn.push_back(_Column);
  }

  // Удаление данных
  vx.swap(tmp_v);
  vData.swap(tmp_vv);

  // Заполнение
  float fData;
  float fMinColumn;
  objData _objData;
  for (long DataRow = 0; DataRow < CountDataRow; DataRow++){
      // Очистим запись
      vx.erase(vx.begin(), vx.end());
      _objData.x = _Data->getData(x,DataRow);
      _objData.y = _Data->getData(y,DataRow);
      _objData.z = _Data->getData(z,DataRow);

      if ((_objData.x >= xMin)&&(_objData.x <= xMax)&&
          (_objData.y >= yMin)&&(_objData.y <= yMax)) {
        if (zMax != zMin){
           if ((_objData.z >= zMin)&&(_objData.z <= zMax)){
              // Получим минимум для замены нулей
              for (long i = 0; i < vColumn.size(); i++){
                fMinColumn = _Data->getMin(_Column.n);
                _Column = vColumn[i];
                fData = _Data->getData(_Column.n,DataRow);
                if (_Column.bLog10)
                {
                  if (0 >= fData)
                   fData = log10(fMinColumn);
                  else
                   fData = log10(fData);
                }
                vx.push_back(fData);
              }
           }
        }
        else {
              for (long i = 0; i < vColumn.size(); i++){
                _Column = vColumn[i];
                fData = _Data->getData(_Column.n,DataRow);
                if (_Column.bLog10){
                  if (0 >= fData)
                   fData = log10(fMinColumn);
                  else
                   fData = log10(fData);
                }
                vx.push_back(fData);
              }
        }
      }

      vXYZ.push_back(_objData);
      vData.push_back(vx);
  }

  return true;
}

// ********************************************
// * Процесс вычисления весовой аппроксимации *
// ********************************************
bool SkewWAProcess::Calculation() const
{
  bStatus = false;

  // Проверка условия построения сетки
  if (_Settings->pTypeSection == mSkew){
    if (!CreateNetSkewSection())
      return false;
  }

  // Отбор данных
  if (!CreateData())
   return false;

  float Alpha, Lambda, Gamma;

  Alpha = _Settings->Alpha;
  Lambda = _Settings->Lambda;
  Gamma = _Settings->Gamma;

  long CountPointData = vData.size();
  long CountPointNet = vNet.size();

  // Удаление данных
  vxNetT.swap(tmp_v);
  vNetT.swap(tmp_vv);
  vNetW.swap(tmp_v);


  // Инициализация для того чтобы иметь индексный доступ
  vxNetT.reserve(vColumn.size());
  for (long x = 0; x < vColumn.size(); x++)
    vxNetT.push_back(0);
  vNetT.reserve(CountPointNet);
  for (long y = 0; y < CountPointNet; y++)
    vNetT.push_back(vxNetT);

  vNetW.reserve(CountPointNet);
  for (long n = 0; n < CountPointNet; n++){
    vNetW.push_back(0);
  }

  // Очистка данных стандарта
  vxStandart.swap(tmp_v);
  vStandart.swap(tmp_vv);
  vStandartW.swap(tmp_v);

  // Если требуеться вычислить стандарт, тогда
  // Инициализируем вектор для того, чтобы иметь индексный доступ
  _bStandart = _Settings->Standart;
  if (_bStandart){

    vxStandart.reserve(vColumn.size());
    for (long x = 0; x < vColumn.size(); x++)
      vxStandart.push_back(0);

    vStandart.reserve(vData.size());
    for (long y = 0; y < vData.size(); y++)
      vStandart.push_back(vxStandart);

    vStandartW.reserve(vData.size());
    for (long n = 0; n < vData.size(); n++)
      vStandartW.push_back(0);
  }

  // Покажем пользователю процент выполнения работы
  frmProgressWork->Caption = "Состояние процесса...";
  frmProgressWork->pb->Progress = 0;
  frmProgressWork->pb->MinValue = 0;
  frmProgressWork->pb->MaxValue = CountPointData;
  frmProgressWork->Show();

  Application->ProcessMessages();


  long CountColumnPointData = vColumn.size();
  float W;
  float T;
  objData _objData;
  objNet _objNet;
  objData _objDataStandart;
  float R;
  for (long d = 0; d < CountPointData; d++){
   _objData = vXYZ[d];
   for (long n = 0; n < CountPointNet; n++){
     _objNet = vNet[n];
     R = sqrt( pow((_objData.x - _objNet.x),2) +
               pow((_objData.y - _objNet.y),2) +
               pow((_objData.z - _objNet.z),2) );
     W = 1/(1 + Lambda * pow((R/Gamma),Alpha));

     // Вычисляем все признаки в одном цикле
     for (long col = 0; col < CountColumnPointData; col++){
      T = W * vData[d][col];
      vNetT[n][col] = vNetT[n][col] + T;
     }

     // Норма
     vNetW[n] = vNetW[n] + W;
   }

   if (_bStandart){

     for (long s = 0; s < CountPointData; s++){

       _objDataStandart = vXYZ[s];

       R = sqrt( pow((_objData.x - _objDataStandart.x),2) +
                 pow((_objData.y - _objDataStandart.y),2) +
                 pow((_objData.z - _objDataStandart.z),2) );
       W = 1/(1 + Lambda * pow((R/Gamma),Alpha));

       // Вычисляем все признаки в одном цикле
       for (long col = 0; col < CountColumnPointData; col++){
        T = W * vData[d][col];
        vStandart[s][col] = vStandart[s][col] + T;
       }

       // Норма
       vStandartW[s] = vStandartW[s] + W;
     }

   }

   frmProgressWork->pb->Progress++;
  }

  Application->ProcessMessages();

  // Вычисление конечного результата
  vxTildeT.swap(tmp_v);
  vTildeT.swap(tmp_vv);

  vMinTildeT.swap(tmp_v);
  vMaxTildeT.swap(tmp_v);

  vMinTildeT.reserve(CountColumnPointData);
  for (long i = 0; i < CountColumnPointData; i++){
    vMinTildeT.push_back(0);
  }

  vMaxTildeT.reserve(CountColumnPointData);
  for (long i = 0; i < CountColumnPointData; i++){
    vMaxTildeT.push_back(0);
  }

  float TildeT;
  for (long n = 0; n < CountPointNet; n++){
    // Очистим запись
    vxTildeT.erase(vxTildeT.begin(), vxTildeT.end());
    for (long col = 0; col < CountColumnPointData; col++){
      TildeT = vNetT[n][col]/vNetW[n];
      vxTildeT.push_back(TildeT);

      // Вычисление минимума и максимума весовой аппроксимации
      if (0 == n){
       vMinTildeT[col] = TildeT;
       vMaxTildeT[col] = TildeT;
      }
      else {
      if (vMinTildeT[col] > TildeT)
       vMinTildeT[col] = TildeT;
      else
      if (vMaxTildeT[col] < TildeT)
       vMaxTildeT[col] = TildeT;
      }

    }

    vTildeT.push_back(vxTildeT);
  }

  // Вычисление конечного результата для стандарта
  vxTildeStandart.swap(tmp_v);
  vTildeStandart.swap(tmp_vv);
  // Минимум и максимум весовой аппроксимации для стандарта
  vMinTildeStandart.swap(tmp_v);
  vMaxTildeStandart.swap(tmp_v);

  vMinTildeT.reserve(CountColumnPointData);
  vMinTildeStandart.reserve(CountColumnPointData);

  for (long i = 0; i < CountColumnPointData; i++){
    vMinTildeStandart.push_back(0);
  }

  vMaxTildeStandart.reserve(CountColumnPointData);
  for (long i = 0; i < CountColumnPointData; i++){
    vMaxTildeStandart.push_back(0);
  }

  float TildeStandartT = 0;
  for (long s = 0; s < CountPointData; s++){
    // Очистим запись
    vxTildeStandart.erase(vxTildeStandart.begin(), vxTildeStandart.end());
    for (long col = 0; col < CountColumnPointData; col++){

      TildeStandartT = vStandart[s][col]/vStandartW[s];
      vxTildeStandart.push_back(TildeStandartT);

      // Вычисление минимума и максимума весовой аппроксимации
      if (0 == s){
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

    vTildeStandart.push_back(vxTildeStandart);
  }

  frmProgressWork->Close();
  bStatus = true;
  return true;
}

/* Интерфейс для получения данных весовой аппроксимации для косого сечения */

// ********************
// * Размер основания *
// ********************
float SkewWAProcess::getLBase()
{
 if (_Settings->pTypeSection == mSkew){
  return LBase;
 }
 else
  return NULL;
}

// *****************
// * Размер высоты *
// *****************
float SkewWAProcess::getLHeight()
{
 if (_Settings->pTypeSection == mSkew){
  return LHeight;
 }
 else
  return NULL;
}

