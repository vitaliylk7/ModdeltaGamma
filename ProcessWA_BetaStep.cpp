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
// ����������� � ������ �������
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
// ����������
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
  // ������� �����
  if (html != 0)
   delete html;

}
//---------------------------------------------------------------------------
// ������� �������� ������� ������� �������������
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
// ���������� ����� ������� ������������� �� �������� �����
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
    // ������� ������
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

  // �������� �������� � ��������� ������ �������
  CalcMinMax(CountCol, CountRec, vTildeStandart,
      vMinTildeStandart, vMaxTildeStandart);

  return 0;
}
//---------------------------------------------------------------------------
// ���������� �������� � ��������� ��� ������� �������������
//---------------------------------------------------------------------------
void ProcessWA_BetaStep::CalcMinMax(const int CountCol, const int CountRec,
      const vector <vector<float> > &vv, vector <float> &vMin,
      vector <float> &vMax)
{
  float TildeT;
  // ������� �������
  vMin.swap(tmp_v);
  vMax.swap(tmp_v);
  // ������������� ������ ��� ������ ��� ���������� ������������ ������
  vMin.reserve(CountCol);
  vMax.reserve(CountCol);
  // �������� ��� ���������� ������� � �������
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
      // ���������� �������� � ��������� ������� �������������
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
// ���������� ������ �������� ���� � �������� ���� �������
//---------------------------------------------------------------------------
int ProcessWA_BetaStep::Calculation()
{

  //if (CalcStandart() == 0) {
    // ��������� ���������� ���������������
    // int countRec = _dataWA_Area->getCountRecord();
    // int countCol = _dataWA_Area->getCountColumn();
    // CalcStatisticsD(countRec, countCol);
    // return 0;
  // }

  bStatus = true;
  return 0;
}
//---------------------------------------------------------------------------
// ������� ������������ ������� ���������� ��������
//---------------------------------------------------------------------------
void ProcessWA_BetaStep::ViewProgress(const long count) {
  if (NumLevel == -1)
    frmProgressWork->Caption = "��������� ��������...";
  else
    frmProgressWork->Caption = "��������� ��������. ������� " +
      IntToStr(NumLevel + 1) + ".";
  frmProgressWork->pb->Progress = 0;
  frmProgressWork->pb->MinValue = 0;
  frmProgressWork->pb->MaxValue = count;
  frmProgressWork->Show();

  Application->ProcessMessages();
}
//---------------------------------------------------------------------------
//  ������
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
// �������
//---------------------------------------------------------------------------
bool ProcessWA_BetaStep::Clear()
{
  // ������
  bStatus = false;
  // ��������
  vxStandart.swap(tmp_v);
  vStandart.swap(tmp_vv);
  vStandartW.swap(tmp_v);
  // � ��� �������� ������ ������� ������������� ��� ���������
  vxTildeStandart.swap(tmp_v);
  vTildeStandart.swap(tmp_vv);
  // ������� � �������� ������� ������������� ��� ���������
  vMinTildeStandart.swap(tmp_v);
  vMaxTildeStandart.swap(tmp_v);
  MinTildeStandart = 0;
  MaxTildeStandart = 0;

  return true;
}
//---------------------------------------------------------------------------
// ��������� ���������
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
    // ����� ���������� ��������
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

    // ����� �������� ��������
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
    ShowMessage("������ ���������� ����� ������ ������� �������������!");
    return false;
  }
  return true;
}
//---------------------------------------------------------------------------
// �������� �������� ����������
//---------------------------------------------------------------------------
bool ProcessWA_BetaStep::VisualResultText()
{
  frmViewApproximation = new TfrmViewApproximation(Application, 0,
    "����� ������ ���������������", _listProcessWA);
  return true;
}
//---------------------------------------------------------------------------
// �������� �������� � ���������� ���. �������. �� �������� �����
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
// ������� � ������� �������� � ��������
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
// ������ ��������� �������
//---------------------------------------------------------------------------
void ProcessWA_BetaStep::th(int width, String value) {
  html->Add("<th width=\"" + IntToStr(width) + "\">" + value + "</th>");
}
//---------------------------------------------------------------------------
// ������ �������
//---------------------------------------------------------------------------
void ProcessWA_BetaStep::td(int width, String value) {
  html->Add("<td align=\"center\" width=\"" + IntToStr(width) + "\"><b>" + value
    + "</b></td>");
}
//---------------------------------------------------------------------------
// ������ ������ ��������������� ��� ����� ��������������
//---------------------------------------------------------------------------
void ProcessWA_BetaStep::VisualDataD(const int col, String name) {
  const ProcessWA* processWA = *_listProcessWA.begin();
  html->Add("<table align=center width=\"560\" border=\"1\" cellpadding=\"1\" cellspacing=\"0\" bordercolor=\"black\">");
  html->Add("<tr>");
  th(60, "�����");
  th(70, "�����");
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
// �������� ������
//---------------------------------------------------------------------------
bool ProcessWA_BetaStep::VisualResultGraph() {
  html->Clear();
  html->Add("<html>");
  html->Add("<head>");
  html->Add("<meta http-equiv=Content-Type content=\"text/html; charset=windows-1251\">");
  html->Add("<title>��ר� &quot;�����A ���������������&quot;</title>");
  html->Add("</head>");
  html->Add("<body>");
  html->Add("<h3 align=center>��ר�<br> ������ ��������������� (��������� &quot;ModDeltaG&quot;)</h3>");
  html->Add("<br/>");
  html->Add("<table>");
  // ��� �����
  html->Add("<tr><td width=500><b>����: " + _Data->getFileName() + "</b></td></tr>");
  html->Add("<br>");

// ������� �������� ������
//---------------------------------------------------------------------------
  add_parval(html, "�������:", 500, "", 4);
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
  th(70, "���-�� �����");
  th(1, "|");
  html->Add("</tr>");

    // ������� �������� �����
  FromTill xFromTill = _Settings->mSettingsApprox2D3D->xScopeDataAprox;
  FromTill yFromTill = _Settings->mSettingsApprox2D3D->yScopeDataAprox;
  FromTill zFromTill = _Settings->mSettingsApprox2D3D->zScopeDataAprox;
  html->Add("<tr>");
  th(1, "|");
  th(70, "������� ����� ������");
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

    // ������� ������ ���������������
  xFromTill = _Settings->mSettingsApprox2D3D->xScopeAreaAprox;
  yFromTill = _Settings->mSettingsApprox2D3D->yScopeAreaAprox;
  zFromTill = _Settings->mSettingsApprox2D3D->zScopeAreaAprox;
  html->Add("<tr>");
  th(1, "|");
  th(70, "������� ������ ���������������");
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
// ������ ������ ��������������� ��� �������������
//---------------------------------------------------------------------------
  const ProcessWA* processWA = *_listProcessWA.begin();
  int countCharacteristics = processWA->getStCountCol();
  for (int col = 0; col < countCharacteristics; ++col) {
    html->Add("<tr  align=center><td><b> ��� ��������: " + processWA->getStNameCol(col)
    + "<b/><td> </tr>");
    html->Add("<br>");

    // ��������������� �� ������� ���������
     add_parval(html, "��������������� ���������� � ������� �������� ��������:", 600, "", 0);

    html->Add("<table align=center width=\"500\" border=\"1\" cellpadding=\"1\" cellspacing=\"0\" bordercolor=\"black\">");
  html->Add("<tr>");
  th(70, "-");
  th(70, "�������");
  th(70, "E");
  th(70, "E^2");
  th(70, "min e");
  th(70, "max e");
  th(80, "max-min e");
  html->Add("</tr>");

  html->Add("<tr>");
  th(70, "������� ����� ������");
  th(70, FormatFloat("0.####", processWA->getAverageData(col)));
  th(70, FormatFloat("0.####", processWA->getAverageE(col)));
  th(70, FormatFloat("0.####", processWA->getSquaredE(col)));
  th(70, FormatFloat("0.####", processWA->getMinE(col)));
  th(70, FormatFloat("0.####", processWA->getMaxE(col)));
  th(80, FormatFloat("0.####", processWA->getMaxE(col)
              - processWA->getMinE(col)));
  html->Add("</tr>");

  html->Add("<tr>");
  th(70, "������� ������ ������");
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
  // ��������������� �� ������� ��������� ������� ������ ���������������
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
  add_parval(html, "��������������� �� ������� ��������� ������� ������ ���������������:"
            , 200, tmp2, 440);
  html->Add("<br>");

  html->Add("</table>");
 */
  String paramtmp = " (��������� �������������: �����="
     + FormatFloat("0.##", _Settings->mSettingsApprox2D3D->Alpha)
     + ", ����=" + FormatFloat("0.##", _Settings->mSettingsApprox2D3D->Gamma)
     + ", �����=" + FormatFloat("0.##", _Settings->mSettingsApprox2D3D->BetaFrom)
     + " - " + FormatFloat("0.##", _Settings->mSettingsApprox2D3D->BetaTo)
     + ", �����=" + FormatFloat("0.##", _Settings->mSettingsApprox2D3D->Sigma)
     + "):";
  add_parval(html, "��������������� ���������� � ��������� �������� ��������:"
    + paramtmp ,600, "", 0);
    VisualDataD(col, processWA->getStNameCol(col));
    html->Add("</br>");
  }

  // ������������� �����
  frmReportText = new TfrmReportText(Application,
    "����� ""������ ���������������""", html);

  return true;
}
//---------------------------------------------------------------------------
