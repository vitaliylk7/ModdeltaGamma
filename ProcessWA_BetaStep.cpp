//---------------------------------------------------------------------------
#include <vcl.h>
#pragma hdrstop
#include "ProcessWA_BetaStep.h"
#include "ChooseVisualApproximation.h"
#include "ChooseVisualApproximation.h"
#include "ViewApproximation.h"
#include "ProcessWA_2D.h"
#include "Utils.h"
#include "ViewSettingData.h"
//---------------------------------------------------------------------------
#pragma package(smart_init)
//---------------------------------------------------------------------------
// Конструктор с учётом уровней
//---------------------------------------------------------------------------
ProcessWA_BetaStep::ProcessWA_BetaStep(const Settings *settings,
  const Data *data, DataWA *dataWA, DataWA *dataWA_Area,
  const ParamCalcWA *paramCalcWA, const objData anisotropyFactor)
    : ProcessWA(data, dataWA, dataWA_Area, paramCalcWA, 0,
        false, anisotropyFactor)
{
  _Settings = settings;
  _Data = data;
  _AnisotropyFactor = anisotropyFactor;
  _FactoryDataWA = 0;
  _FactoryParamWA = 0;
  html = new TStringList();
  setStandart();
}
//---------------------------------------------------------------------------
// Деструктор
//---------------------------------------------------------------------------
ProcessWA_BetaStep::~ProcessWA_BetaStep()
{
  for (_iterFactoryProcessWA = _listFactoryProcessWA.begin();
        _iterFactoryProcessWA != _listFactoryProcessWA.end();
        ++_iterFactoryProcessWA)
  {
    delete *_iterFactoryProcessWA;
  }

  if (0 != _FactoryParamWA)
    delete _FactoryDataWA;
  if (0 != _FactoryParamWA)
    delete _FactoryParamWA;
  // Удалить отчёт
  if (html != 0)
   delete html;

}
//---------------------------------------------------------------------------
// Создать процессы уровней весовой аппроксимации
//---------------------------------------------------------------------------
int ProcessWA_BetaStep::Create()
{
  float betaFrom = _Settings->mSettingsApprox2D3D->BetaFrom;
  float betaTo = _Settings->mSettingsApprox2D3D->BetaTo;
  float betaStep = _Settings->mSettingsApprox2D3D->BetaStep;
  numbIteration = 0;
  float betaCurrent = betaFrom;
  FactoryProcessWA *_FactoryProcessWA;
  const ProcessWA *_ProcessWA;
  while (betaCurrent <= betaTo) {
    _FactoryProcessWA = new FactoryProcessWA(_Settings, _Data,
      _AnisotropyFactor, betaCurrent);
    _ProcessWA = _FactoryProcessWA->CreateProcessWA2D();
    _listFactoryProcessWA.push_back(_FactoryProcessWA);
    _listProcessWA.push_back(_ProcessWA);
    betaCurrent += betaStep;
    numbIteration++;
  }

  return 0;
}
//---------------------------------------------------------------------------
// Вычисление общей весовой аппроксимации на исходные точки
//---------------------------------------------------------------------------
int ProcessWA_BetaStep::CalcStandart() {
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
      _Column = _dataWA_Area->getCol(col);
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
        TildeT = (sumT + (_Column._Criterion.TildeT * _Column._Criterion.W))
          / (sumW + _Column._Criterion.W);
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
void ProcessWA_BetaStep::CalcMinMax(const int CountCol, const int CountRec,
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
int ProcessWA_BetaStep::Calculation()
{

  //if (CalcStandart() == 0) {
    // Посчитаем статистику рассогласования
    // int countRec = _dataWA_Area->getCountRecord();
    // int countCol = _dataWA_Area->getCountColumn();
    // CalcStatisticsD(countRec, countCol);
    // return 0;
  // }

  bStatus = true;
  return 0;
}
//---------------------------------------------------------------------------
// Покажем пользователю процент выполнения процесса
//---------------------------------------------------------------------------
void ProcessWA_BetaStep::ViewProgress(const long count) {
  if (NumLevel == -1)
    frmProgressWork->Caption = "Состояние процесса...";
  else
    frmProgressWork->Caption = "Состояние процесса. Уровень " +
      IntToStr(NumLevel + 1) + ".";
  frmProgressWork->pb->Progress = 0;
  frmProgressWork->pb->MinValue = 0;
  frmProgressWork->pb->MaxValue = count;
  frmProgressWork->Show();

  Application->ProcessMessages();
}
//---------------------------------------------------------------------------
//  Запуск
//---------------------------------------------------------------------------
bool ProcessWA_BetaStep::Run()
{
  if (Create() == 0)
  {
    ViewProgress((_Settings->mSettingsApprox2D3D->CountPointData
     + _Settings->mSettingsApprox2D3D->CountPointArea) * numbIteration);
    const ProcessWA* _ProcessWA;
    for (_iterProcessWA = _listProcessWA.begin();
          _iterProcessWA != _listProcessWA.end();  ++_iterProcessWA)
    {
      _ProcessWA = *_iterProcessWA;
      if (_ProcessWA->Run() != true)
        return false;
    }
    frmProgressWork->Close();
    if (0 == Calculation())
      return true;
  }

  return false;
}
//---------------------------------------------------------------------------
// Очистка
//---------------------------------------------------------------------------
bool ProcessWA_BetaStep::Clear()
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
// Сохранить результат
//---------------------------------------------------------------------------
bool ProcessWA_BetaStep::SaveResult() {
  objData _objNet;
  long CountRow, CountColumnAprox;
  int tmpT;
  objData _objDataStandart;
  long CountColumn;
  const ProcessWA* processWA = *_listProcessWA.begin();
  int countBetaSteps = _listProcessWA.size();


  try
  {
    CountRow = processWA->getStCountRec();
    CountColumn = processWA->getStCountCol();
    String fileName = getFileNameSave("ModDelta", "");
    ofstream outFirmsFile(fileName.c_str(), ios::out);
    outFirmsFile << (4 + (CountColumn *(2 + countBetaSteps * 3)))
      << endl;
    // вывод заголовков столбцов
    outFirmsFile << "num" << "\t" << "x" << "\t" << "y" << "\t"
      << 'z' << "\t";

      String tmp, s;
      for (int colCharacters = 0; colCharacters < CountColumn; ++colCharacters)
      {
      s = processWA->getStNameCol(colCharacters);
      outFirmsFile << s.c_str() << "\t";
      tmp = "e";
      outFirmsFile << tmp.c_str() << "\t";

      for (iterProcessWA _iterProcessWA = _listProcessWA.begin();
        _iterProcessWA != _listProcessWA.end();  ++_iterProcessWA)
        {
         processWA = *_iterProcessWA;
         tmp = s + "_G" + FormatFloat("0.###",processWA->getBeta());
         outFirmsFile << tmp.c_str() << "\t";
         tmp = "w_G" + FormatFloat("0.###",processWA->getBeta()) + "\t";
         outFirmsFile << tmp.c_str();
         tmp = "d_G" + FormatFloat("0.###",processWA->getBeta());
         outFirmsFile << tmp.c_str() << "\t";
        }
     }

    outFirmsFile << endl;

    // вывод значений столбцов
    for (int rec = 0; rec < CountRow; ++rec)
    {
      _objDataStandart = processWA->getStXYZ(rec);
      outFirmsFile << (rec + 1) << "\t";
      tmp = FormatFloat("0.00000",_objDataStandart.x);
      outFirmsFile << tmp.c_str() << "\t";
      tmp = FormatFloat("0.00000",_objDataStandart.y);
      outFirmsFile << tmp.c_str() << "\t";
      tmp = FormatFloat("0.00000",_objDataStandart.z);
      outFirmsFile << tmp.c_str() << "\t";

        for (long col = 0; col < CountColumn; ++col)
          {
          // Real value
          tmp = FormatFloat("0.00000",processWA->getRealValue(col, rec));
          outFirmsFile << tmp.c_str() << "\t";
          // E
          tmp = FormatFloat("0.00000",processWA->getE(col, rec));
          outFirmsFile << tmp.c_str() << "\t";

          for (iterProcessWA _iterProcessWA = _listProcessWA.begin();
             _iterProcessWA != _listProcessWA.end();  ++_iterProcessWA)
             {
             processWA = *_iterProcessWA;
             // T
             tmp = FormatFloat("0.00000",processWA->getStT(col, rec));
             outFirmsFile << tmp.c_str() << "\t";
             // W
             tmp = FormatFloat("0.00000",processWA->getStW(rec));
             outFirmsFile << tmp.c_str() << "\t";
             // D
             tmp = FormatFloat("0.00000",processWA->getD(col, rec));
             outFirmsFile << tmp.c_str() << "\t";
             }
          }
      outFirmsFile << endl;
    }

    outFirmsFile.close();
  } __except(EXCEPTION_EXECUTE_HANDLER) {
    // outFirmsFile.close();
    ShowMessage("Ошибка сохранения файла модели весовой аппроксимации!");
    return false;
  }
  return true;
}
//---------------------------------------------------------------------------
// Показать значения результата
//---------------------------------------------------------------------------
bool ProcessWA_BetaStep::VisualResultText()
{
  frmViewApproximation = new TfrmViewApproximation(Application, 0,
    "Отчёт оценки рассогласования", _listProcessWA);
  return true;
}
//---------------------------------------------------------------------------
// Получить параметр о вычислении вес. аппрокс. на исходные точки
//---------------------------------------------------------------------------
void ProcessWA_BetaStep::setStandart()
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
// Вставка в таблицу параметр и значение
//---------------------------------------------------------------------------
void ProcessWA_BetaStep::add_parval(TStrings *html, String par, int width_par,
    String val, int width_val)
{
  html->Add("	<tr align=\"center\">");
  html->Add("		<td width=" + IntToStr(width_par) + "><b>" + par
    + "</b></td>");
  html->Add("		<td width=" + IntToStr(width_val) + "><b>" + val
    + "</b></td>");
  html->Add("	</tr>");
}
//---------------------------------------------------------------------------
// Ячейка заголовка таблицы
//---------------------------------------------------------------------------
void ProcessWA_BetaStep::th(int width, String value) {
  html->Add("<th width=\"" + IntToStr(width) + "\">" + value + "</th>");
}
//---------------------------------------------------------------------------
// Ячейка таблицы
//---------------------------------------------------------------------------
void ProcessWA_BetaStep::td(int width, String value) {
  html->Add("<td align=\"center\" width=\"" + IntToStr(width) + "\"><b>" + value
    + "</b></td>");
}
//---------------------------------------------------------------------------
// Печать данных рассогласования для одной характеристики
//---------------------------------------------------------------------------
void ProcessWA_BetaStep::VisualDataD(const int col, String name) {
  const ProcessWA* processWA = *_listProcessWA.begin();
  html->Add("<table align=center width=\"560\" border=\"1\" cellpadding=\"1\" cellspacing=\"0\" bordercolor=\"black\">");
  html->Add("<tr>");
  th(60, "Номер");
  th(70, "Гамма");
  th(70, "D");
 // th(70, "|D|");
  th(70, "D^2");
  th(70, "min d");
  th(70, "max d");
  th(80, "max-min d");
  html->Add("</tr>");

  int number = 1;
  for (_iterProcessWA = _listProcessWA.begin();
    _iterProcessWA != _listProcessWA.end();  _iterProcessWA++)
  {
    processWA = *_iterProcessWA;
    html->Add("<tr>");
    td(60, IntToStr(number));
    td(70, FormatFloat("0.####", processWA->getBeta()));
    td(70, FormatFloat("0.####", processWA->getAverageD(col)));
   // td(70, FormatFloat("0.####", processWA->getModuleD(col)));
    td(70, FormatFloat("0.####", processWA->getSquaredD(col)));
    td(70, FormatFloat("0.####", processWA->getMinD(col)));
    td(70, FormatFloat("0.####", processWA->getMaxD(col)));
    td(80, FormatFloat("0.####", processWA->getMaxD(col)
                            - processWA->getMinD(col)));
    html->Add("</tr>");
    ++number;
  }

  html->Add("</table>");
}
//---------------------------------------------------------------------------
// Показать график
//---------------------------------------------------------------------------
bool ProcessWA_BetaStep::VisualResultGraph() {
  html->Clear();
  html->Add("<html>");
  html->Add("<head>");
  html->Add("<meta http-equiv=Content-Type content=\"text/html; charset=windows-1251\">");
  html->Add("<title>ОТЧЁТ &quot;ОЦЕНКA РАССОГЛАСОВАНИЯ&quot;</title>");
  html->Add("</head>");
  html->Add("<body>");
  html->Add("<h3 align=center>ОТЧЁТ<br> Анализ рассогласования (программа &quot;ModDeltaG&quot;)</h3>");
  html->Add("<br/>");
  html->Add("<table>");
  // Имя файла
  html->Add("<tr><td width=500><b>Файл: " + _Data->getFileName() + "</b></td></tr>");
  html->Add("<br>");

// Таблица исходных данных
//---------------------------------------------------------------------------
  add_parval(html, "Границы:", 500, "", 4);
  html->Add("<table align=center width=\"560\" border=\"1\" cellpadding=\"1\" cellspacing=\"0\" bordercolor=\"black\">");
  html->Add("<tr>");
  th(1, "|");
  th(70, "-");
  th(1, "|");
  th(70, "min X");
  th(70, "max X");
  th(1, "|");
  th(70, "min Y");
  th(70, "max Y");
  th(1, "|");
  th(70, "min Z");
  th(70, "max Z");
  th(1, "|");
  th(70, "кол-во точек");
  th(1, "|");
  html->Add("</tr>");

    // Область исходных точек
  FromTill xFromTill = _Settings->mSettingsApprox2D3D->xScopeDataAprox;
  FromTill yFromTill = _Settings->mSettingsApprox2D3D->yScopeDataAprox;
  FromTill zFromTill = _Settings->mSettingsApprox2D3D->zScopeDataAprox;
  html->Add("<tr>");
  th(1, "|");
  th(70, "область учёта данных");
  th(1, "|");
  th(70, FormatFloat("0.##", xFromTill.From));
  th(70, FormatFloat("0.##", xFromTill.Till));
  th(1, "|");
  th(70, FormatFloat("0.##", yFromTill.From));
  th(70, FormatFloat("0.##", yFromTill.Till));
  th(1, "|");
  th(70, FormatFloat("0.##", zFromTill.From));
  th(70, FormatFloat("0.##", zFromTill.Till));
  th(1, "|");
  th(70, IntToStr(_Settings->mSettingsApprox2D3D->CountPointData));
  th(1, "|");
  html->Add("</tr>");

    // Область оценки рассогласования
  xFromTill = _Settings->mSettingsApprox2D3D->xScopeAreaAprox;
  yFromTill = _Settings->mSettingsApprox2D3D->yScopeAreaAprox;
  zFromTill = _Settings->mSettingsApprox2D3D->zScopeAreaAprox;
  html->Add("<tr>");
  th(1, "|");
  th(70, "область оценки рассогласования");
  th(1, "|");
  th(70, FormatFloat("0.##", xFromTill.From));
  th(70, FormatFloat("0.##", xFromTill.Till));
  th(1, "|");
  th(70, FormatFloat("0.##", yFromTill.From));
  th(70, FormatFloat("0.##", yFromTill.Till));
  th(1, "|");
  th(70, FormatFloat("0.##", zFromTill.From));
  th(70, FormatFloat("0.##", zFromTill.Till));
  th(1, "|");
  th(70, IntToStr(_Settings->mSettingsApprox2D3D->CountPointArea));
  th(1, "|");
  html->Add("</tr>");

  html->Add("</table>");
  html->Add("<br>");
//---------------------------------------------------------------------------
// Печать данных рассогласования для характеристик
//---------------------------------------------------------------------------
  const ProcessWA* processWA = *_listProcessWA.begin();
  int countCharacteristics = processWA->getStCountCol();
  for (int col = 0; col < countCharacteristics; ++col) {
    html->Add("<tr  align=center><td><b> Имя признака: " + processWA->getStNameCol(col)
    + "<b/><td> </tr>");
    html->Add("<br>");

    // Рассогласование со средним значением
     add_parval(html, "Рассогласование измеренных и средних значений признака:", 600, "", 0);

    html->Add("<table align=center width=\"500\" border=\"1\" cellpadding=\"1\" cellspacing=\"0\" bordercolor=\"black\">");
  html->Add("<tr>");
  th(70, "-");
  th(70, "среднее");
  th(70, "E");
  th(70, "E^2");
  th(70, "min e");
  th(70, "max e");
  th(80, "max-min e");
  html->Add("</tr>");

  html->Add("<tr>");
  th(70, "Область учёта данных");
  th(70, FormatFloat("0.####", processWA->getAverageData(col)));
  th(70, FormatFloat("0.####", processWA->getAverageE(col)));
  th(70, FormatFloat("0.####", processWA->getSquaredE(col)));
  th(70, FormatFloat("0.####", processWA->getMinE(col)));
  th(70, FormatFloat("0.####", processWA->getMaxE(col)));
  th(80, FormatFloat("0.####", processWA->getMaxE(col)
              - processWA->getMinE(col)));
  html->Add("</tr>");

  html->Add("<tr>");
  th(70, "Область оценки данных");
  th(70, FormatFloat("0.####", processWA->getAverageArea(col)));
  th(70, FormatFloat("0.####", processWA->getAverageE1(col)));
  th(70, FormatFloat("0.####", processWA->getSquaredE1(col)));
  th(70, FormatFloat("0.####", processWA->getMinE1(col)));
  th(70, FormatFloat("0.####", processWA->getMaxE1(col)));
  th(80, FormatFloat("0.####", processWA->getMaxE1(col)
              - processWA->getMinE1(col)));
  html->Add("</tr>");

  html->Add("<table/>");
  html->Add("<br>");
 /* html->Add("<table>");



  */

  /*
  // Рассогласование со средним значением области оценки рассогласования
  String tmp2;
  tmp2 = "<font size=3> E = " + FormatFloat("0.####", processWA->getAverageE1(col))
    + ";&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;"
    //+ "|E| = " + FormatFloat("0.####", processWA->getModuleE(col))
    //+ ";&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;"
    + "E^2 = " + FormatFloat("0.####", processWA->getSquaredE1(col))
    +";<br>"
    + "&nbsp;&nbsp;&nbsp;&nbsp;"
    + "min e = " + FormatFloat("0.####", processWA->getMinE1(col))
    + ";&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;"
    + "max e = " + FormatFloat("0.####", processWA->getMaxE1(col))
    + ";</font>";
  add_parval(html, "Рассогласование со средним значением области оценки рассогласования:"
            , 200, tmp2, 440);
  html->Add("<br>");

  html->Add("</table>");
 */
  String paramtmp = " (параметры моделирования: Альфа="
     + FormatFloat("0.##", _Settings->mSettingsApprox2D3D->Alpha)
     + ", Бета=" + FormatFloat("0.##", _Settings->mSettingsApprox2D3D->Gamma)
     + ", Гамма=" + FormatFloat("0.##", _Settings->mSettingsApprox2D3D->BetaFrom)
     + " - " + FormatFloat("0.##", _Settings->mSettingsApprox2D3D->BetaTo)
     + ", Сигма=" + FormatFloat("0.##", _Settings->mSettingsApprox2D3D->Sigma)
     + "):";
  add_parval(html, "Рассогласование измеренных и модельных значений признака:"
    + paramtmp ,600, "", 0);
    VisualDataD(col, processWA->getStNameCol(col));
    html->Add("</br>");
  }

  // Визуализируем отчёт
  frmReportText = new TfrmReportText(Application,
    "Отчёт ""Оценка рассогласования""", html);

  return true;
}
//---------------------------------------------------------------------------
