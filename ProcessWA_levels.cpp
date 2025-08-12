//---------------------------------------------------------------------------
#include <vcl.h>
#pragma hdrstop
#include "ChooseVisualApproximation.h"
#include "ProcessWA_levels.h"
#include "ChooseVisualApproximation.h"
#include "ViewApproximation.h"
//---------------------------------------------------------------------------
#pragma package(smart_init)
//---------------------------------------------------------------------------
// Конструктор с учётом уровней
//---------------------------------------------------------------------------
ProcessWA_levels::ProcessWA_levels(const Settings *Settings_, const Data *Data_,
 const int CountLevels_, const objData AnisotropyFactor)
   : ProcessWA(Data_, 0, 0, 0, false, AnisotropyFactor)
{
  _Settings = Settings_;
  _Data = Data_;
  CountLevels = CountLevels_;
  _AnisotropyFactor = AnisotropyFactor;

  setStandart();

  if (CountLevels != -1)
  {
    _FactoryDataWA = new FactoryDataWA(_Data, _Settings);
    _FactoryParamWA = new FactoryParamWA(_Settings, 0);

    // Получим параметры колонок
    _ParamCalcWA = _FactoryParamWA->Create();
    // Произведём отбор данных
    _DataWA = _FactoryDataWA->Create();
    _DataWA->Create();
  }
}
//---------------------------------------------------------------------------
// Деструктор
//---------------------------------------------------------------------------
ProcessWA_levels::~ProcessWA_levels()
{
  for (_iterFactoryProcessWA = _listFactoryProcessWA.begin();
        _iterFactoryProcessWA != _listFactoryProcessWA.end();
        ++_iterFactoryProcessWA)
  {
    delete *_iterFactoryProcessWA;
  }

  delete _FactoryDataWA;
  delete _FactoryParamWA;
}
//---------------------------------------------------------------------------
// Создать процессы уровней весовой аппроксимации
//---------------------------------------------------------------------------
int ProcessWA_levels::Create()
{
  FactoryProcessWA *_FactoryProcessWA;
  const ProcessWA *_ProcessWA;
  for (int i = 0; i < CountLevels; ++i)
  {
    _FactoryProcessWA = new FactoryProcessWA(_Settings, _Data, i,
      _AnisotropyFactor);
    _ProcessWA = _FactoryProcessWA->Create();
    _listFactoryProcessWA.push_back(_FactoryProcessWA);
    _listProcessWA.push_back(_ProcessWA);
  }

  return 0;
}
//---------------------------------------------------------------------------
// Вычисление общей весовой аппроксимации на исходные точки
//---------------------------------------------------------------------------
int ProcessWA_levels::CalcStandart()
{
  int CountCol, CountRec;
  float W, T, TildeT, valueColT, sumT, sumW;

  vxTildeStandart.swap(tmp_v);
  vTildeStandart.swap(tmp_vv);
  vStandartW.swap(tmp_v);

  const ProcessWA* _ProcessWA = *_listProcessWA.begin();
  CountCol = _ProcessWA->getStCountCol();
  CountRec = _ProcessWA->getStCountRec();
  Column _Column;
  objData _objData;
  for (int rec = 0; rec < CountRec; ++rec)
  {
    sumW = 0;
    // Очистим запись
    vxTildeStandart.erase(vxTildeStandart.begin(), vxTildeStandart.end());
    for (int col = 0; col < CountCol; ++col)
    {
      _Column = _DataWA->getCol(col);
      sumT = 0;
      for (_iterProcessWA = _listProcessWA.begin();
        _iterProcessWA != _listProcessWA.end();  ++_iterProcessWA)
      {
        _ProcessWA = *_iterProcessWA;
        _objData = _ProcessWA->getStXYZ(rec);
        W = _ProcessWA->getStW(rec);
        valueColT = _ProcessWA->getStT(col, rec);
        T = W * valueColT;
        sumT += T;

        if (col == 0)
          sumW += W;
      }

      if (sumW != 0)
      {
        TildeT = (sumT + (_Column._Criterion.TildeT * _Column._Criterion.W)) / (sumW + _Column._Criterion.W);
      }
      else
      {
        TildeT = 0;
      }

      vxTildeStandart.push_back(TildeT);
    }

    vTildeStandart.push_back(vxTildeStandart);
    vStandartW.push_back(sumW);
  }

  // Вычислим минимумы и максимумы каждой колонки
  CalcMinMax(CountCol, CountRec, vTildeStandart,
      vMinTildeStandart, vMaxTildeStandart);

  return 0;
}
//---------------------------------------------------------------------------
// Вычисление минимума и максимума для весовой аппроксимации
//---------------------------------------------------------------------------
void ProcessWA_levels::CalcMinMax(const int CountCol, const int CountRec,
      const vector <vector<float> > &vv, vector <float> &vMin,
      vector <float> &vMax)
{
  float TildeT;
  // Очистим массивы
  vMin.swap(tmp_v);
  vMax.swap(tmp_v);
  // Зарезервируем память под массив для исключения фрагментации памяти
  vMin.reserve(CountCol);
  vMax.reserve(CountCol);
  // Заполним для индексного доступа к массиву
  for (int i = 0; i < CountCol; ++i)
  {
    vMin.push_back(0);
    vMax.push_back(0);
  }

  for (int rec = 0; rec < CountRec; ++rec)
  {
    for (int col = 0; col < CountCol; ++col)
    {
      TildeT = vv[rec][col];
      // Вычисление минимума и максимума весовой аппроксимации
      if (0 == rec)
      {
       vMin[col] = TildeT;
       vMax[col] = TildeT;
      }
      else
      {
        if (vMin[col] > TildeT)
         vMin[col] = TildeT;
        else
        if (vMax[col] < TildeT)
         vMax[col] = TildeT;
      }
    }
  }
}
//---------------------------------------------------------------------------
// Вычисление общего значения веса и значения всех уровней
//---------------------------------------------------------------------------
int ProcessWA_levels::Calculation()
{

  if (CalcStandart() != 0)
      return 1;

  bStatus = true;
  return 0;
}
//---------------------------------------------------------------------------
//  Запуск
//---------------------------------------------------------------------------
bool ProcessWA_levels::Run()
{
  if (Create() == 0)
  {
    const ProcessWA* _ProcessWA;
    for (_iterProcessWA = _listProcessWA.begin();
          _iterProcessWA != _listProcessWA.end();  ++_iterProcessWA)
    {
      _ProcessWA = *_iterProcessWA;
      if (_ProcessWA->Run() != true)
        return false;
    }

    if (0 == Calculation())
      return true;
  }

  return false;
}
//---------------------------------------------------------------------------
// Очистка
//---------------------------------------------------------------------------
bool ProcessWA_levels::Clear()
{
  // Статус
  bStatus = false;
  // Стандарт
  vxStandart.swap(tmp_v);
  vStandart.swap(tmp_vv);
  vStandartW.swap(tmp_v);
  // А это конечные данные весовой аппроксимации для стандарта
  vxTildeStandart.swap(tmp_v);
  vTildeStandart.swap(tmp_vv);
  // Минимум и максимум весовой аппроксимации для стандарта
  vMinTildeStandart.swap(tmp_v);
  vMaxTildeStandart.swap(tmp_v);
  MinTildeStandart = 0;
  MaxTildeStandart = 0;

  return true;
}
//---------------------------------------------------------------------------
// Сохранить весовую аппроксимацию на исходные точки
//---------------------------------------------------------------------------
bool ProcessWA_levels::SaveStandart(String FileName)
{
  objData _objNet;
  long CountRow, CountColumnAprox;
  int tmpT;

  CountRow = vTildeStandart.size();
  CountColumnAprox = _DataWA->getCountColumn();

  try
  {
    ofstream outFirmsFile(FileName.c_str(), ios::out);
    outFirmsFile << (CountColumnAprox + 4) << endl; // iAmo_Column
    outFirmsFile << 'x' << "\t\t" << 'y' << "\t\t" << 'z' << "\t\t";

    long tmpCountColumnAprox = CountColumnAprox -1;
    int iLength;
    String s;
    // Подпишим колонки в файле для уровней
    for (int level = 0; level < CountLevels; ++level)
    {
      outFirmsFile << (level + 1) << "W" << "\t\t";
      for (long i = 0; i < CountColumnAprox; i++)
      {
        s = _DataWA->getNameCol(i);
        s = getColName(s);
        outFirmsFile << (level + 1) << s.c_str() << "\t\t";
      }
    }

    // Подпишим колонки в файле для общих значений всех уровней
    outFirmsFile << "W" << "\t\t";
    for (long i = 0; i < CountColumnAprox; ++i)
    {
      s = _DataWA->getNameCol(i);
      s = getColName(s);
      outFirmsFile << "M" << s.c_str();

      if (tmpCountColumnAprox == i)
        outFirmsFile << endl;
      else
        outFirmsFile << "\t\t";
    }

    // Запишим значения колонок для уровней
    const ProcessWA* _ProcessWA;
    for (long rec = 0; rec < CountRow; ++rec)
    {
      // _objNet = _Net->getValue(rec);
      s = FormatFloat("0.00000",_objNet.x);
      outFirmsFile << s.c_str() << "\t\t";
      s = FormatFloat("0.00000",_objNet.y);
      outFirmsFile << s.c_str() << "\t\t";
      s = FormatFloat("0.00000",_objNet.z);
      outFirmsFile << s.c_str() << "\t\t";

      // Значения уровней
      for (_iterProcessWA = _listProcessWA.begin();
            _iterProcessWA != _listProcessWA.end();  ++_iterProcessWA)
      {
        _ProcessWA = *_iterProcessWA;
        s = FormatFloat("0.00000", _ProcessWA->getStW(rec));
        outFirmsFile << s.c_str() << "\t\t";
        for (int col = 0; col < CountColumnAprox; ++col)
        {
          s = FormatFloat("0.00000",_ProcessWA->getStT(col, rec));
          outFirmsFile << s.c_str() << "\t\t";
        }
      }

      // Значения общие для всех уровней
      s = FormatFloat("0.00000", vStandartW[rec]);
      outFirmsFile << s.c_str() << "\t\t";
      for (int col = 0; col < CountColumnAprox; ++col)
      {
        s = FormatFloat("0.00000",vTildeStandart[rec][col]);
        outFirmsFile << s.c_str();
        if (tmpCountColumnAprox == col)
          outFirmsFile << endl;
        else
          outFirmsFile << "\t\t";
      }
    }

    outFirmsFile.close();
  }
  __except(EXCEPTION_EXECUTE_HANDLER) {
    // outFirmsFile.close();
    ShowMessage("Ошибка сохранения файла модели весовой аппроксимации!");
    return false;
  }

  return true;
}
//---------------------------------------------------------------------------
// Показать значения результата
//---------------------------------------------------------------------------
bool ProcessWA_levels::VisualResultText()
{
  TfrmChooseVisualApproximation *frmCVA;
  // Произведём запрос у пользователя о том какие необходимо визуализировать уровни
  frmCVA = new TfrmChooseVisualApproximation(Application);
  frmCVA->chlCriterion->Items->Clear();
  frmCVA->Caption = "Просмотр составной модели в табличном виде";

  // Заполним список выбора уровнями
  String NameLevel;
  int level;
  for (level = 0; level < CountLevels; ++level)
  {
    NameLevel = "уровень " + IntToStr(level+1);
    frmCVA->chlCriterion->Items->Add(NameLevel);
    frmCVA->chlCriterion->Checked[level] = true;
  }

  NameLevel = "cоставная модель";
  frmCVA->chlCriterion->Items->Add(NameLevel);
  frmCVA->chlCriterion->Checked[level] = true;

  frmCVA->ShowModal();

  // Визуализируем уровни в случае выбора их пользователем
  const ProcessWA* _ProcessWA;
  level = 0;
  for (_iterProcessWA = _listProcessWA.begin();
        _iterProcessWA != _listProcessWA.end();  ++_iterProcessWA)
  {
    if (frmCVA->chlCriterion->Checked[level])
    {
      _ProcessWA = *_iterProcessWA;
      if (_ProcessWA->VisualResultText() != true)
        return false;
    }
    ++level;
  }

  // Визуалиируем составную модель в случае выбора её пользователем
  if (frmCVA->chlCriterion->Checked[level])
  {
    String LevelName = "Состовная модель. ";
    frmViewApproximation = new TfrmViewApproximation(Application, 0,
        LevelName + "Весовая аппроксимация на сетку", this);

    if (_bStandart)
    {
      frmViewApproximation = new TfrmViewApproximation(Application, 1,
        LevelName + "Весовая аппроксимация на исходные точки", this);
    }
  }
  return true;
}
//---------------------------------------------------------------------------
// Получить параметр о вычислении вес. аппрокс. на исходные точки
//---------------------------------------------------------------------------
void ProcessWA_levels::setStandart()
{
  switch (_Settings->TypeModel)
  {
    case mApprox2D:
    case mApprox3D:
      _bStandart = _Settings->mSettingsApprox2D3D->Standart;
      break;
    default :
      _bStandart = false;
  }

}
//---------------------------------------------------------------------------
// Показать график
//---------------------------------------------------------------------------
bool ProcessWA_levels::VisualResultGraph()
{
  return true;
}
//---------------------------------------------------------------------------
