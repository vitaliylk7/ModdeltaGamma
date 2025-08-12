//---------------------------------------------------------------------------
#include <vcl.h>
#pragma hdrstop
#include "DataWA_Area.h"
//---------------------------------------------------------------------------
#pragma package(smart_init)
//---------------------------------------------------------------------------
// Конструктор
//---------------------------------------------------------------------------
DataWA_Area::DataWA_Area(const Data *data, const SettingsApprox2D3D *settings)
  : DataWA(data)
{
  _settings = settings;
}
//---------------------------------------------------------------------------
// Деструктор
//---------------------------------------------------------------------------
DataWA_Area::~DataWA_Area()
{

}
//---------------------------------------------------------------------------
// Отбор данных
//---------------------------------------------------------------------------
int DataWA_Area::Create()
{
  float xMin, xMax, yMin, yMax, zMin, zMax;
  long x, y, z, CountColumnCriterion, CountDataRow, NumColumn;
  FromTill tmpScopeAreaAprox;

  tmpScopeAreaAprox = _settings->xScopeAreaAprox;
  xMin = tmpScopeAreaAprox.From;
  xMax = tmpScopeAreaAprox.Till;

  tmpScopeAreaAprox = _settings->yScopeAreaAprox;
  yMin = tmpScopeAreaAprox.From;
  yMax = tmpScopeAreaAprox.Till;

  tmpScopeAreaAprox = _settings->zScopeAreaAprox;
  zMin = tmpScopeAreaAprox.From;
  zMax = tmpScopeAreaAprox.Till;

  CountColumnCriterion = _settings->getCountCriterion();
  if (0 == CountColumnCriterion){
    ShowMessage("Не выбраны признаки");
    return false;
  }
  CountDataRow = _Data->getCountRecord();
  x = _Data->getNumberForColumnName(_settings->NameX);
  y = _Data->getNumberForColumnName(_settings->NameY);
  z = _Data->getNumberForColumnName(_settings->NameZ);

  // Удаление данных
  vXYZ.swap(tmp_XYZ);

  // Сохраним номера всех графов участвующих в вычисленнии и проставим статус log10
  vColumn.swap(tmp_Column);

  Column _Column;
  String Name;
  Criterion _Criterion;
  for (long Col = 0; Col < CountColumnCriterion; Col++)
  {
    _Criterion = _settings->getCriterion(Col);
    _Column = getColumn(_Criterion.Name);
    _Column._Criterion = _Criterion;
    vColumn.push_back(_Column);
  }

  // Удаление данных
  vx.swap(tmp_v);
  vData.swap(tmp_vv);
  vSubIndex.erase(vSubIndex.begin(), vSubIndex.end());

  // Заполнение
  objData _objData;
  for (long DataRow = 0; DataRow < CountDataRow; DataRow++){
      // Очистим запись
      vx.erase(vx.begin(), vx.end());
      _objData.x = _Data->getData(x,DataRow);
      _objData.y = _Data->getData(y,DataRow);
      _objData.z = _Data->getData(z,DataRow);

      if ((_objData.x >= xMin)&&(_objData.x <= xMax)&&
          (_objData.y >= yMin)&&(_objData.y <= yMax))
      {
        if (zMax != zMin)
        {
           if ((_objData.z >= zMin)&&(_objData.z <= zMax))
           {
              if (getRecord(vColumn, vx, DataRow) != 0)
                return 1;
           }
        }
        else
        {
           if (getRecord(vColumn, vx, DataRow) != 0)
             return 1;
        }
      }

      if (vx.size() > 0)
      {
        vXYZ.push_back(_objData);
        vData.push_back(vx);
        vSubIndex.push_back(DataRow);
      }
  }
  // Вычислить среднее значение для каждой характеристики
  CalcAverageValueCols();
  return 0;
}
//---------------------------------------------------------------------------
