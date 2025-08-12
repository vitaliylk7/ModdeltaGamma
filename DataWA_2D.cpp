//---------------------------------------------------------------------------
#include <vcl.h>
#pragma hdrstop
#include "DataWA_2D.h"
//---------------------------------------------------------------------------
#pragma package(smart_init)
//---------------------------------------------------------------------------
// Конструктор
//---------------------------------------------------------------------------
DataWA_2D::DataWA_2D(const Data *Data_, const SettingsApprox2D3D *Settings_)
  : DataWA(Data_)
{
  _Settings = Settings_;
}
//---------------------------------------------------------------------------
// Конструктор для уровней
//---------------------------------------------------------------------------
DataWA_2D::DataWA_2D(const Data *Data_, const SettingsApprox2D3D *Settings_,
      const int NumLevel_)
  : DataWA(Data_, NumLevel_)
{
  _Settings = Settings_;
  LevelSettings = _Settings->SettingsForLevels->getLevel(NumLevel);
}
//---------------------------------------------------------------------------
// Деструктор
//---------------------------------------------------------------------------
DataWA_2D::~DataWA_2D()
{

}
//---------------------------------------------------------------------------
// Отбор данных
//---------------------------------------------------------------------------
int DataWA_2D::Create()
{
  float xMin, xMax, yMin, yMax, zMin, zMax;
  long x, y, z, CountColumnCriterion, CountDataRow, NumColumn;
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
  String Name;
  Criterion _Criterion;
  for (long Col = 0; Col < CountColumnCriterion; Col++)
  {
    _Criterion = _Settings->getCriterion(Col);
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
      vSubIndex.erase(vSubIndex.begin(), vSubIndex.end());
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
  return 0;
}
