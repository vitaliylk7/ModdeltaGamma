//---------------------------------------------------------------------------
#ifndef ProcessWAH
#define ProcessWAH
#include "Process.h"
#include "DataWA.h"
#include "DataWA_Area.h"
//---------------------------------------------------------------------------
// ����� ���������� ������� �������������
//---------------------------------------------------------------------------
class ProcessWA : public MainProcess {

protected:
  // ���������
  bool bStatus;
  // ������
  DataWA *_DataWA;
  // ������ ���������� � ������������ � �������� ������ ���������������
  DataWA *_dataWA_Area;
  // ������ � ��������� ������������
  DataWA *_DataWAAnisotropyFactor;

  // ������ ��� ���������� ������������ �� �������� �����
  const Data *_Data;
  // ��������� ����������
  const ParamCalcWA *_ParamCalcWA;
  // ������� ��� ������ ������ � ��������
  vector <float> tmp_v;
  vector <vector<float> > tmp_vv;
  // ������������� ������ ������� ������������, �� ���� ��� ������������� �����,
  // ��� ������ ���������� �� ���� �� ������
  bool _bStandart;
  vector <float> vxStandart;
  vector <vector<float> > vStandart;
  vector <float> vStandartW;
  vector <float> vStandartWS; // ����������� ������������
  vector <float> vStandartS; // ������������ ������������
  // � ��� �������� ������ ������� ������������� ��� ���������
  vector <float> vxTildeStandart;
  vector <vector<float> > vTildeStandart;
  // ������� � �������� ������� ������������� ��� ���������
  vector <float> vMinTildeStandart;
  vector <float> vMaxTildeStandart;
  float MinTildeStandart, MaxTildeStandart;
  // ���������������
  vector <float> vxD;
  vector <vector <float> > vD;
  // �������������� ���������� �� ���������������
  vector <float> vMinD;       // ������� ���������������
  vector <float> vMaxD;       // �������� ���������������
  vector <float> vAverageD;   // ������� ���������������
  vector <float> vModuleD;    // ������ ���������������
  vector <float> vSquaredD;   // ������� ���������������

  // ��� ������� �����
  // ��������������� ������������ �������� �������� (��� �������� �������������)
  vector <float> vxE;
  vector <vector <float> > vE;
  // �������������� ���������� �� ��������������� ������������ �������� ��������
  vector <float> vMinE;       // ������� ���������������
  vector <float> vMaxE;       // �������� ���������������
  vector <float> vAverageE;   // ������� ���������������
  vector <float> vSquaredE;   // ������� ���������������

  // ��� ������� ���������� ���������������
  // ��������������� ������������ �������� �������� (��� �������� �������������)
  vector <float> vxE1;
  vector <vector <float> > vE1;
  // �������������� ���������� �� ��������������� ������������ �������� ��������
  vector <float> vMinE1;       // ������� ���������������
  vector <float> vMaxE1;       // �������� ���������������
  vector <float> vAverageE1;   // ������� ���������������
  vector <float> vSquaredE1;   // ������� ���������������

  // ����� ������, ���� ������� ���, ����� ������ -1
  int NumLevel;
  // ��������� �����������
  objData _AnisotropyFactor;
  // ���������� ���������� ����� ����� �������
  float CalcR(const objData _objData, const objData _objNet);
  // ��������� ���
  float CalcW(const float R, const float Beta, const float Gamma,
      const float Alpha);
  // ���������� ������� �������������
  virtual int Calculation();
  // ��������� ������������� �� �������� �����
  virtual bool SaveStandart(String FileName);
  // ��������� ������� �������������
  virtual bool SaveModel(String FileName);
  // �������� ������������ ��������
  String getColName(String s);

private:
  // ���� ��������� �����������
  void EnterAnisotropyFactor();
  // ������� ������ ����������� �� �������� �����
  void ClearDataStandart();
  // ���������� ������ ����������� �� �������� �����
  void PrepareDataStandart(const int countCol, const int countRec);
  // ������� ������������ ������� ���������� ��������
  void ViewProgress(const int countRec);
  // ���������� ���� � ���������� ��������
  void CalcWT(const int countRecData, const int countColData);
  // ������� ������ ��� ��������� ���������� ��������
  void ClearTildeData();
  // ���������� ������ ��� ��������� ���������� ��������
  void PrepareTildeData(const int countCol);
  // ���������� �������� � ��������� ���������� �������� ������� �������������
  void CalcMinMaxTildeStandart(const float TildeStandartT, const int col,
    const int rec);
  // ���� �������� ��������
  void EnterBackground(float &Background_TildeT, float &Background_W,
    const int numLevel, const Column column);

  // ������� ���������� ���������������
  void ClearStatisticsD();
  // ���������� ���������� ��������������
  void PrepareStatisticsD(const int countCol);
  // ���������� ���������� ���������������
  void CalcStatisticsD(const int countRec, const int countCol);

  // ������� ���������� ���������������
  void ClearStatisticsE();
  // ���������� ���������� ��������������
  void PrepareStatisticsE(const int countCol);
  // ���������� ���������� ���������������
  void CalcStatisticsE(const int countRec, const int countCol);

  // ������� ���������� ���������������
  void ClearStatisticsE1();
  // ���������� ���������� ��������������
  void PrepareStatisticsE1(const int countCol);
  // ���������� ���������� ���������������
  void CalcStatisticsE1(const int countRec, const int countCol);

  // ���������� ���������� ������������ �������� ��������
  void CalcE(const int countRecArea, const int countColArea);

  // ���������� ���������� ������������ �������� ��������
  void CalcE1(const int countRecArea, const int countColArea);

public:
  // ������������
  ProcessWA(const Data *Data_, DataWA *DataWA_, DataWA *dataWA_Area,
      const ParamCalcWA *ParamCalcWA_, const bool bStandart_,
      objData AnisotropyFactor);
  // ����������� � ������ �������
  ProcessWA(const Data *Data_, DataWA *DataWA_, DataWA *dataWA_Area,
      const ParamCalcWA *ParamCalcWA_, const int NumLevel_,
      const bool bStandart_, objData AnisotropyFactor);
  // ����������
  ~ProcessWA();
  //  ������
  virtual bool Run(){ return false; };
  // �������
  virtual bool Clear();
  // ��������� ���������
  virtual bool SaveResult();
  // �������� ������
  virtual bool VisualResultGraph(){ return false; };
  // �������� �������� ����������
  virtual bool VisualResultText();

  // �������� �������� �������� ��������������
  float getRealValue(const int col, const int rec) const;
  // �������� ������� �������� �������������� � ������� �����
  float getAverageData(const int col) const;
  // �������� ������� �������� �������������� � ������� ������
  float getAverageArea(const int col) const;
  // �������� �������� �.�. �� �������� ����� �� ������ ������� � ������ ������
  float getStT(const int col, const int rec) const;
  // �������� �������� ���� �� ������ ������ ��� �.�. �� �������� �����
  float getStW(const int rec) const;
  // �������� ����������� �������� ����
  float getStMinW();
  // �������� ������������ �������� ����
  float getStMaxW();
  // �������� ����� ������� �� �������� ��� �.�. �� �������� �����
  int getStNumColumn(String value) const;
  // �������� ���������� ����� �� �������� ������ ������ ��� �.�. �� �������� �����
  objData getStXYZ(const int rec) const;
  // �������� ���������� ��������� ��� �.�. �� �������� �����
  int getStCountCol() const;
  // �������� ���������� ������� ��� �.�. �� �������� �����
  int getStCountRec() const;
  // �������� ������������ ������� �� �������� ������� ��� �.�. �� �������� �����
  String getStNameCol(int value) const;

  // �������� �������� ���������������
  float getD(const int col, const int rec) const;
  // �������� �������� ������� ���������������
  float getMinD(const int col) const;
  // �������� �������� ��������� ���������������
  float getMaxD(const int col) const;
  // �������� �������� �������� ���������������
  float getAverageD(const int col) const;
  // �������� �������� ������ ���������������
  float getModuleD(const int col) const;
  // �������� �������� ������� ���������������
  float getSquaredD(const int col) const;

  // �������� �������� ����
  float getBeta() const;

  // ������� �����
  // ��������������� ������������ �������� �������� (��� �������� �������������)
  float getE(const int col, const int rec) const;
  // �������� �������� ������� ���������������
  float getMinE(const int col) const;
  // �������� �������� ��������� ���������������
  float getMaxE(const int col) const;
  // �������� �������� �������� ���������������
  float getAverageE(const int col) const;
  // �������� �������� ������ ���������������
//  float getModuleE(const int col) const;
  // �������� �������� ������� ���������������
  float getSquaredE(const int col) const;

  // ������� ������ ���������������
  // ��������������� ������������ �������� �������� (��� �������� �������������)
  float getE1(const int col, const int rec) const;
  // �������� �������� ������� ���������������
  float getMinE1(const int col) const;
  // �������� �������� ��������� ���������������
  float getMaxE1(const int col) const;
  // �������� �������� �������� ���������������
  float getAverageE1(const int col) const;
  // �������� �������� ������ ���������������
//  float getModuleE1(const int col) const;
  // �������� �������� ������� ���������������
  float getSquaredE1(const int col) const;

};
//---------------------------------------------------------------------------
#endif
