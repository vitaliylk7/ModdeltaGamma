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
// �������
// _dataWA_Area-> - �������� �������� � ���. ���������� ��������������� �����
// _DataWA-> - �������� �������� � ���. ����� �����
// _DataWAAnisotropyFactor-> �������� �������� � ���. ����� ����� � ������������
//
//
//---------------------------------------------------------------------------

//---------------------------------------------------------------------------
// ������������
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
// ����������� � ������ �������
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
// ����������
//---------------------------------------------------------------------------
ProcessWA::~ProcessWA()
{
  if (_DataWAAnisotropyFactor != 0) {
    delete _DataWAAnisotropyFactor;
    _DataWAAnisotropyFactor = 0;
  }
}
//---------------------------------------------------------------------------
// ������� ������
//---------------------------------------------------------------------------
bool ProcessWA::Clear()
{
  // �������� ������
  // ��������
  vxStandart.swap(tmp_v);
  vStandart.swap(tmp_vv);
  vStandartW.swap(tmp_v);
  vStandartWS.swap(tmp_v);
  vStandartS.swap(tmp_v);
  // � ��� �������� ������ ������� ������������� ��� ���������
  vxTildeStandart.swap(tmp_v);
  vTildeStandart.swap(tmp_vv);
  // ������� � �������� ������� ������������� ��� ���������
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
// �������� ������������ ��������
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
// ���������� ���������� ����� ����� �������
//---------------------------------------------------------------------------
float ProcessWA::CalcR(objData _objData, objData _objNet)
{
  return sqrt( pow((_objData.x - _objNet.x),2) +
               pow((_objData.y - _objNet.y),2) +
               pow((_objData.z - _objNet.z),2)
             );
}
//---------------------------------------------------------------------------
// ��������� ���
//---------------------------------------------------------------------------
float ProcessWA::CalcW(const float R, const float Beta,
    const float Gamma, const float Alpha)
{
  return 1 / (1 + Beta * pow((R / Gamma),Alpha));
}
//---------------------------------------------------------------------------
// ���� ��������� �����������
//---------------------------------------------------------------------------
void ProcessWA::EnterAnisotropyFactor() {
  // �������� ������� ������ ��� ����� ��������� �����������
  if (_DataWAAnisotropyFactor != 0) {
    delete _DataWAAnisotropyFactor;
    _DataWAAnisotropyFactor = 0;
  }

  _DataWAAnisotropyFactor = new DataWA(_DataWA);
  _DataWAAnisotropyFactor->setAnisotropyFactor(_AnisotropyFactor);
}
//---------------------------------------------------------------------------
// ������� ������ ����������� �� �������� �����
//---------------------------------------------------------------------------
void ProcessWA::ClearDataStandart() {
  vxStandart.swap(tmp_v);
  vStandart.swap(tmp_vv);
  vStandartW.swap(tmp_v);
  vStandartWS.swap(tmp_v);
  vStandartS.swap(tmp_v);
}
//---------------------------------------------------------------------------
// ���������� ������ ����������� �� �������� �����
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
// ������� ������������ ������� ���������� ��������
//---------------------------------------------------------------------------
void ProcessWA::ViewProgress(const int countRec) {
  if (NumLevel == -1)
    frmProgressWork->Caption = "��������� ��������...";
  else
    frmProgressWork->Caption = "��������� ��������. ������� " +
      IntToStr(NumLevel + 1) + ".";
  frmProgressWork->pb->Progress = 0;
  frmProgressWork->pb->MinValue = 0;
  frmProgressWork->pb->MaxValue = countRec;
  frmProgressWork->Show();

  Application->ProcessMessages();
}
//---------------------------------------------------------------------------
// ���������� ���������� ������������ �������� �������� ������� �����
//---------------------------------------------------------------------------
void ProcessWA::CalcE(const int countRecArea, const int countColArea) {
  float realValue, e;
  for (long rec = 0; rec < countRecArea; ++rec) {
    // ��������� ��� �������� � ����� �����
    vxE.erase(vxE.begin(), vxE.end());
    for (long col = 0; col < countColArea; ++col) {
      realValue = _dataWA_Area->getValue(col,rec);
      // ��������� ��������������� ������������ �������� ��������
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
// ���������� ���������� ������������ �������� �������� ������� ������ ���������������
//---------------------------------------------------------------------------
void ProcessWA::CalcE1(const int countRecArea, const int countColArea) {
  float realValue, e1;
  for (long rec = 0; rec < countRecArea; ++rec) {
    // ��������� ��� �������� � ����� �����
    vxE1.erase(vxE1.begin(), vxE1.end());
    for (long col = 0; col < countColArea; ++col) {
      realValue = _dataWA_Area->getValue(col,rec);
      // ��������� ��������������� ������������ �������� ��������
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
// ���������� ���� � ���������� ��������
//---------------------------------------------------------------------------
void ProcessWA::CalcWT(const int countRecData, const int countColData)
{
  float Alpha, Beta, Gamma,Sigma;
  Alpha = _ParamCalcWA->Alpha;
  Beta = _ParamCalcWA->Gamma;
  Gamma = _ParamCalcWA->Beta;
  Sigma = _ParamCalcWA->Sigma;
  float W, WS, T, R, E, realValue;
  int countRecAreaData = _dataWA_Area->getCountRecord();// ����� � ������� �����
  objData _objData, _objDataArea;
  float x1,x2,y1,y2,z1,z2;

  // ��������� ���� ��� ����������� ������������� ������������
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
      // ��������� ����������
      R = CalcR(_objData, _objDataArea);
      // ��������� ���
      W = CalcW(R, Beta, Gamma, Alpha);
      // �����
      vStandartW[n] = vStandartW[n] + W;

    };
  frmProgressWork->pb->Progress++;
  };

  // ��������� ����������� ������������
  for (long d = 0; d < countRecData; ++d)
    {
    vStandartS[d] = pow(vStandartW[d], Sigma - 1);
    };
  // ������� �������� �����
  for (long n = 0; n < countRecData; n++)
    vStandartW[n] = 0;



  for (long n = 0; n < countRecAreaData; ++n)
    {
    _objDataArea = _dataWA_Area->getXYZ(n);
    for (long d = 0; d < countRecData; d++)
      {
      _objData = _DataWAAnisotropyFactor->getXYZ(d);
      // ��������� ����������
      R = CalcR(_objData, _objDataArea);
      // ��������� ���
      if (R == 0)
        W = 0;
      else
        W = CalcW(R, Beta, Gamma, Alpha) * vStandartS[d];
      // ��������� ��� �������� � ����� �����
      //vxE.erase(vxE.begin(), vxE.end());
      for (long col = 0; col < countColData; ++col)
      {
        realValue = _DataWAAnisotropyFactor->getValue(col,d);
        T = W * realValue ;
        vStandart[n][col] = vStandart[n][col] + T;
      }
      // �����
      vStandartW[n] = vStandartW[n] + W;
    }
    frmProgressWork->pb->Progress++;
  }

}
//---------------------------------------------------------------------------
// ������� ������ ��� ��������� ���������� ��������
//---------------------------------------------------------------------------
void ProcessWA::ClearTildeData() {

  vxTildeStandart.swap(tmp_v);
  vTildeStandart.swap(tmp_vv);
  // ������� � �������� ������� ������������� ��� ���������
  vMinTildeStandart.swap(tmp_v);
  vMaxTildeStandart.swap(tmp_v);

}
//---------------------------------------------------------------------------
// ���������� ������ ��� ��������� ���������� ��������
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
// ���������� �������� � ��������� ���������� �������� ������� �������������
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
// ���� �������� ��������
//---------------------------------------------------------------------------
void ProcessWA::EnterBackground(float &Background_TildeT, float &Background_W,
  const int numLevel, const Column column)
{
  // ��� ���������� ������� ��� �� ���������
  // (������������ ������� � ��������� ���������� �������)
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
// ���������� ������� �������������
//---------------------------------------------------------------------------
int ProcessWA::Calculation()
{
  bStatus = false;
  // �������� ����� ������
  if (_DataWA->Create() != 0) {
    return 1;
  }
  else
  if (_dataWA_Area->Create() != 0) {
    return 1;
  }

  // ���� ��������� �����������
  EnterAnisotropyFactor();
  int CountRecData = _DataWAAnisotropyFactor->getCountRecord();//����� � ������� �����
  int CountRecArea = _dataWA_Area->getCountRecord();//����� � ������� ���������
  int CountColumnData = _DataWAAnisotropyFactor->getCountColumn();
  // �� ��������� ���������� � ������ ���� ���������� ����� 0
  if (CountRecData == 0) {
    bStatus = true;
    return 0;
  }

  // ������� ������ ����������� �� �������� �����
  ClearDataStandart();
  // ���������� ������ ����������� �� �������� �����
  PrepareDataStandart(CountColumnData, CountRecData);
  // ������� ������������ ������� ���������� ��������
//  ViewProgress(CountRecData + CountRecArea);
  // ���������� ���� � ���������� ��������
  CalcWT(CountRecData, CountColumnData);
//  Application->ProcessMessages();

  // �������� ���������� ������� ������������� �� �������� �����
  // ������� ������ ��� ��������� ���������� ��������
  ClearTildeData();
  // ���������� ������ ��� ��������� ���������� ��������
  PrepareTildeData(CountRecData);

  float TildeStandartT = 0;
  float TildeT, Background_TildeT, Background_W, T, d;
  Column _Column;
  for (long recArea = 0; recArea < CountRecArea; ++recArea)
  {
    // ������� ������
    vxTildeStandart.erase(vxTildeStandart.begin(), vxTildeStandart.end());
    vxD.erase(vxD.begin(), vxD.end());
    for (long col = 0; col < CountColumnData; ++col)
    {
      _Column = _DataWAAnisotropyFactor->getCol(col);
   //   T = _DataWAAnisotropyFactor->getValue(col,recArea);

      // ���� �������� ��������
      EnterBackground(Background_TildeT, Background_W, NumLevel, _Column);

      TildeStandartT = (vStandart[recArea][col]
        + (Background_TildeT * Background_W))
          / (vStandartW[recArea] + Background_W);
      //TildeStandartT = vStandart[_dataWA_Area->getSubIndex[recArea]][col]
      //    / vStandartW[_dataWA_Area->getSubIndex[recArea]];


      // ������� �� ���������� �������� ������� �������� �����,
      // ������� � ��� �� ����� ������������
          TildeStandartT = (CountRecArea * TildeStandartT
          - _dataWA_Area->getValue(col,recArea)) / (CountRecArea - 1);
     //TildeStandartT = (CountRecData * TildeStandartT
     //- _dataWA_Area->getValue(col,_dataWA_Area->getSubIndex[recArea]))
      // ( vStandartW[_dataWA_Area->getSubIndex[recArea]]
      //- vStandartS[_dataWA_Area->getSubIndex[recArea]]);



      // �������� ����������
      d = _dataWA_Area->getValue(col,recArea) - TildeStandartT;



      vxTildeStandart.push_back(TildeStandartT);
      vxD.push_back(d);

     // ���������� �������� � ��������� ���������� ��������
     CalcMinMaxTildeStandart(TildeStandartT, col, recArea);

    }
    vTildeStandart.push_back(vxTildeStandart);
    vD.push_back(vxD);
  }

  CalcStatisticsD(CountRecArea, CountColumnData);
  // ���������� ���������� ������������ �������� ��������
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
// ������� ���������� ���������������
//---------------------------------------------------------------------------
void ProcessWA::ClearStatisticsD()
{
  vMinD.swap(tmp_v);     // ������� ���������������
  vMaxD.swap(tmp_v);     // �������� ���������������
  vAverageD.swap(tmp_v); // ������� ���������������
  vModuleD.swap(tmp_v);  // ������ ���������������
  vSquaredD.swap(tmp_v); // ������� ���������������

}
//---------------------------------------------------------------------------
// ���������� ���������� ��������������
//---------------------------------------------------------------------------
void ProcessWA::PrepareStatisticsD(const int countCol)
{
  vMinD.reserve(countCol);      // ������� ���������������
  vMaxD.reserve(countCol);      // �������� ���������������
  vAverageD.reserve(countCol);  // ������� ���������������
  vModuleD.reserve(countCol);   // ������ ���������������
  vSquaredD.reserve(countCol);  // ������� ���������������

  // �������� ��� ���������� ������� � �������
  for (int i = 0; i < countCol; ++i) {
    vMinD.push_back(0);
    vMaxD.push_back(0);
    vAverageD.push_back(0);
    vModuleD.push_back(0);
    vSquaredD.push_back(0);
  }
}
//---------------------------------------------------------------------------
// ���������� ���������� ���������������
//---------------------------------------------------------------------------
void ProcessWA::CalcStatisticsD(const int countRec, const int countCol)
{
  ClearStatisticsD();    // ������� ���������� ���������������
  PrepareStatisticsD(countCol);  // ���������� ���������� ��������������

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
      // ���������� �������� � ��������� ������� �������������
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
    ShowMessage("X: [ProcessWA_BetaStep::CalcStatisticsD] ������� �� 0!!!");
  }
}
//---------------------------------------------------------------------------
// ������� ���������� ���������������  ������� �����
//---------------------------------------------------------------------------
void ProcessWA::ClearStatisticsE()
{
  vMinE.swap(tmp_v);     // ������� ���������������
  vMaxE.swap(tmp_v);     // �������� ���������������
  vAverageE.swap(tmp_v); // ������� ���������������
//  vModuleE.swap(tmp_v);  // ������ ���������������
  vSquaredE.swap(tmp_v); // ������� ���������������

}
//---------------------------------------------------------------------------
// ������� ���������� ��������������� ������� ���������������
//---------------------------------------------------------------------------
void ProcessWA::ClearStatisticsE1()
{
  vMinE1.swap(tmp_v);     // ������� ���������������
  vMaxE1.swap(tmp_v);     // �������� ���������������
  vAverageE1.swap(tmp_v); // ������� ���������������
//  vModuleE.swap(tmp_v);  // ������ ���������������
  vSquaredE1.swap(tmp_v); // ������� ���������������

}
//---------------------------------------------------------------------------
// ���������� ���������� �������������� ������� �����
//---------------------------------------------------------------------------
void ProcessWA::PrepareStatisticsE(const int countCol)
{
  vMinE.reserve(countCol);      // ������� ���������������
  vMaxE.reserve(countCol);      // �������� ���������������
  vAverageE.reserve(countCol);  // ������� ���������������
 // vModuleE.reserve(countCol);   // ������ ���������������
  vSquaredE.reserve(countCol);  // ������� ���������������

  // �������� ��� ���������� ������� � �������
  for (int i = 0; i < countCol; ++i) {
    vMinE.push_back(0);
    vMaxE.push_back(0);
    vAverageE.push_back(0);
//    vModuleE.push_back(0);
    vSquaredE.push_back(0);
  }
}
//---------------------------------------------------------------------------
// ���������� ���������� �������������� ������� ������
//---------------------------------------------------------------------------
void ProcessWA::PrepareStatisticsE1(const int countCol)
{
  vMinE1.reserve(countCol);      // ������� ���������������
  vMaxE1.reserve(countCol);      // �������� ���������������
  vAverageE1.reserve(countCol);  // ������� ���������������
 // vModuleE.reserve(countCol);   // ������ ���������������
  vSquaredE1.reserve(countCol);  // ������� ���������������

  // �������� ��� ���������� ������� � �������
  for (int i = 0; i < countCol; ++i) {
    vMinE1.push_back(0);
    vMaxE1.push_back(0);
    vAverageE1.push_back(0);
//    vModuleE1.push_back(0);
    vSquaredE1.push_back(0);
  }
}
//---------------------------------------------------------------------------
// ���������� ���������� ��������������� � �������� ����� ������
//---------------------------------------------------------------------------
void ProcessWA::CalcStatisticsE(const int countRec, const int countCol)
{
  ClearStatisticsE();    // ������� ���������� ���������������
  PrepareStatisticsE(countCol);  // ���������� ���������� ��������������

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
      // ���������� �������� � ��������� ������� �������������
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
    ShowMessage("X: [ProcessWA_BetaStep::CalcStatisticsE] ������� �� 0!!!");
  }
}
//---------------------------------------------------------------------------
// ���������� ���������� ��������������� ��� ������� ������ ���������������
//---------------------------------------------------------------------------
void ProcessWA::CalcStatisticsE1(const int countRec, const int countCol)
{
  ClearStatisticsE1();    // ������� ���������� ���������������
  PrepareStatisticsE1(countCol);  // ���������� ���������� ��������������

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
      // ���������� �������� � ��������� ������� �������������
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
    ShowMessage("X: [ProcessWA_BetaStep::CalcStatisticsE1] ������� �� 0!!!");
  }
}
//---------------------------------------------------------------------------
// ��������� ������� ������������� �� �������� ����� � ����
//---------------------------------------------------------------------------
bool ProcessWA::SaveStandart(String FileName)
{
  objData _objData;
  long CountRow;
  long CountColumnAprox;
  int tmpT;
  CountRow = vTildeStandart.size();
  CountColumnAprox = _DataWA->getCountColumn();

  //  ������ � ����������� ������
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
    ShowMessage("������ ���������� ����� �� �������� �����!");
    return false;
  }

  return true;
}
//---------------------------------------------------------------------------
// ��������� ������� ������������� � ����
//---------------------------------------------------------------------------
bool ProcessWA::SaveModel(String FileName)
{
  return false;
}
//---------------------------------------------------------------------------
// ��������� ���������
//---------------------------------------------------------------------------
bool ProcessWA::SaveResult()
{
  if (bStatus != true){
    ShowMessage("������ �� ������������");
    return false;
  }

  String sFileName;

  // ��������� ������������� �� �������� �����
  if (_bStandart == true)
  {
    sFileName = getFileNameSave("������ (�������� �����)",
    	_Data->getFileName());
    if (sFileName != "")
      SaveStandart(sFileName);
  }

  // ��������� ������ ������� �������������
  sFileName = getFileNameSave("������ (�����)");
  if (sFileName != "")
     SaveModel(sFileName);

  return true;
}
//---------------------------------------------------------------------------
// �������� �������� ���������� � �������
//---------------------------------------------------------------------------
bool ProcessWA::VisualResultText()
{
  String LevelName;
  if (NumLevel == -1)
    LevelName = "";
  else
    LevelName = "������� " + IntToStr(NumLevel + 1) + ". ";

  frmViewApproximation = new TfrmViewApproximation(Application, 0,
      LevelName + "������� ������������� �� �����", this);

  if (_bStandart)
  {
    frmViewApproximation = new TfrmViewApproximation(Application, 1,
      LevelName + "������� ������������� �� �������� �����", this);
  }

  return true;
}
//===========================================================================
// ��������� St
//===========================================================================
// �������� �������� �������� ��������������
//---------------------------------------------------------------------------
float ProcessWA::getRealValue(const int col, const int rec) const {
  return _dataWA_Area->getValue(col, rec);
}
//---------------------------------------------------------------------------
// �������� ������� �������� �������������� � ������� �����
//---------------------------------------------------------------------------
float ProcessWA::getAverageData(const int col) const
{
 return _DataWAAnisotropyFactor->getAverageValueCol(col);
}
//---------------------------------------------------------------------------
// �������� ������� �������� �������������� � ������� ������
//---------------------------------------------------------------------------
float ProcessWA::getAverageArea(const int col) const
{
 return _dataWA_Area->getAverageValueCol(col);
}
//---------------------------------------------------------------------------
// �������� �������� �.�. �� �������� ����� �� ������ ������� � ������ ������
//---------------------------------------------------------------------------
float ProcessWA::getStT(const int col, const int rec) const {
  return vTildeStandart[rec][col];
}
//---------------------------------------------------------------------------
// �������� �������� ���� �� ������ ������ ��� �.�. �� �������� �����
//---------------------------------------------------------------------------
float ProcessWA::getStW(const int rec) const
{
  return vStandartW[rec];
}
//---------------------------------------------------------------------------
// �������� ����������� �������� ����
//---------------------------------------------------------------------------
float ProcessWA::getStMinW()
{
  float *p;
  p = min_element(vStandartW.begin(), vStandartW.end());
  return *p;
}
//---------------------------------------------------------------------------
// �������� ������������ �������� ����
//---------------------------------------------------------------------------
float ProcessWA::getStMaxW()
{
  float *p;
  p = max_element(vStandartW.begin(), vStandartW.end());
  return *p;
}

//---------------------------------------------------------------------------
// �������� ����� ������� �� �������� ��� �.�. �� �������� �����
//---------------------------------------------------------------------------
int ProcessWA::getStNumColumn(String value) const
{
  return _dataWA_Area->getNameToNumColumn(value);
}
//---------------------------------------------------------------------------
// �������� ���������� ����� �� �������� ������ ������ ��� �.�. �� �������� �����
//---------------------------------------------------------------------------
objData ProcessWA::getStXYZ(const int rec) const {

  return _dataWA_Area->getXYZ(rec);
}
//---------------------------------------------------------------------------
// �������� ���������� ��������� ��� �.�. �� �������� �����
//---------------------------------------------------------------------------
int ProcessWA::getStCountCol() const
{
  return _dataWA_Area->getCountColumn();
}
//---------------------------------------------------------------------------
// �������� ���������� ������� ��� �.�. �� �������� �����
//---------------------------------------------------------------------------
int ProcessWA::getStCountRec() const
{
  return _dataWA_Area->getCountRecord();
}
//---------------------------------------------------------------------------
// �������� ������������ ������� �� �������� ������� ��� �.�. �� �������� �����
//---------------------------------------------------------------------------
String ProcessWA::getStNameCol(int value) const
{
  return _dataWA_Area->getNameCol(value);
}

// ==========================================================================

//---------------------------------------------------------------------------
// �������� �������� ���������������
//---------------------------------------------------------------------------
float ProcessWA::getD(const int col, const int rec) const {
  return vD[rec][col];
}
//---------------------------------------------------------------------------
// �������� �������� ������� ���������������
//---------------------------------------------------------------------------
float ProcessWA::getMinD(const int col) const {
  return vMinD[col];
}
//---------------------------------------------------------------------------
// �������� �������� ��������� ���������������
//---------------------------------------------------------------------------
float ProcessWA::getMaxD(const int col) const {
  return vMaxD[col];
}
//---------------------------------------------------------------------------
// �������� �������� �������� ���������������
//---------------------------------------------------------------------------
float ProcessWA::getAverageD(const int col) const {
  return vAverageD[col];
}
//---------------------------------------------------------------------------
// �������� �������� ������ ���������������
//---------------------------------------------------------------------------
float ProcessWA::getModuleD(const int col) const {
  return vModuleD[col];
}
//---------------------------------------------------------------------------
// �������� �������� ������� ���������������
//---------------------------------------------------------------------------
float ProcessWA::getSquaredD(const int col) const {
  return vSquaredD[col];
}
//---------------------------------------------------------------------------
// �������� �������� ����
//---------------------------------------------------------------------------
float ProcessWA::getBeta() const {
  return _ParamCalcWA->Beta;
}

// ==========================================================================

//---------------------------------------------------------------------------
// ��������������� ������������ �������� �������� (��� �������� �������������)
// ��� ������� �����
//---------------------------------------------------------------------------
float ProcessWA::getE(const int col, const int rec) const {
  return vE[rec][col];
}
//---------------------------------------------------------------------------
// �������� �������� ������� ���������������
//---------------------------------------------------------------------------
float ProcessWA::getMinE(const int col) const {
  return vMinE[col];
}
//---------------------------------------------------------------------------
// �������� �������� ��������� ���������������
//---------------------------------------------------------------------------
float ProcessWA::getMaxE(const int col) const {
  return vMaxE[col];
}
//---------------------------------------------------------------------------
// �������� �������� �������� ���������������
//---------------------------------------------------------------------------
float ProcessWA::getAverageE(const int col) const {
  return vAverageE[col];
}
//---------------------------------------------------------------------------
// �������� �������� ������ ���������������
//---------------------------------------------------------------------------
//float ProcessWA::getModuleE(const int col) const {
//  return 0; //vModuleE[col];
//}
//---------------------------------------------------------------------------
// �������� �������� ������� ���������������
//---------------------------------------------------------------------------
float ProcessWA::getSquaredE(const int col) const {
  return vSquaredE[col];
}
//---------------------------------------------------------------------------
//---------------------------------------------------------------------------
// ��������������� ������������ �������� �������� (��� �������� �������������)
// ��� ������� ������ ���������������
//---------------------------------------------------------------------------
float ProcessWA::getE1(const int col, const int rec) const {
  return vE1[rec][col];
}
//---------------------------------------------------------------------------
// �������� �������� ������� ���������������
//---------------------------------------------------------------------------
float ProcessWA::getMinE1(const int col) const {
  return vMinE1[col];
}
//---------------------------------------------------------------------------
// �������� �������� ��������� ���������������
//---------------------------------------------------------------------------
float ProcessWA::getMaxE1(const int col) const {
  return vMaxE1[col];
}
//---------------------------------------------------------------------------
// �������� �������� �������� ���������������
//---------------------------------------------------------------------------
float ProcessWA::getAverageE1(const int col) const {
  return vAverageE1[col];
}
//---------------------------------------------------------------------------
// �������� �������� ������ ���������������
//---------------------------------------------------------------------------
//float ProcessWA::getModuleE1(const int col) const {
//  return 0; //vModuleE1[col];
//}
//---------------------------------------------------------------------------
// �������� �������� ������� ���������������
//---------------------------------------------------------------------------
float ProcessWA::getSquaredE1(const int col) const {
  return vSquaredE1[col];
}
//---------------------------------------------------------------------------
