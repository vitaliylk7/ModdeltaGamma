//---------------------------------------------------------------------------
#ifndef DataWAH
#define DataWAH
#include <fstream.h>
#include <vector>
#include "Data.h"
#include "Settings.h"
//---------------------------------------------------------------------------
// ����� ���������� ������ � ���������� ������� �������������
//---------------------------------------------------------------------------
class DataWA {

protected:
  // ��������� �� ������
  const Data* _Data;
  // ������� ��� ������ ������ � ��������
  vector <objData> tmp_XYZ;
  vector <Column> tmp_Column;
  vector <float> tmp_v;
  vector <vector<float> > tmp_vv;
  // ������� ����� �������� ������ �������� � ����� ��������� �������������
  vector <long> vSubIndex;
  // ���������� ����� ������ �������� � ����� ��������� �������������
  vector <objData> vXYZ;
  // ������ �������� ����������� � ����������
  vector <Column> vColumn;
  // ������
  vector <float> vx; // ���������� �������
  vector <vector<float> > vData;
  // ������� �������� �� ������ ��������������
  vector <float> vAverageValuesColumns;

  // ��������� ��� ������
  // ���������� ����� ������
  int NumLevel;
  // ��������� ������
  TLevelSettings LevelSettings;

  // �������� �������� �������
  Column getColumn(String Name);
  // �������� ������ ������
  int getRecord(const vector <Column> vCol, vector <float> &v, const int rec);
  // ���������� ������ ������� ��������
  void PrepareAverageValueCols(const int countCols);
  // ��������� ������� �������� ��� ������ ��������������
  void CalcAverageValueCols();

public:
  // �����������
  DataWA(const Data* Data_);
  // ����������� ��� �������
  DataWA(const Data* Data_, const int NumLevel_);
  // ����������� �����������
  DataWA(DataWA *DataWA_);
  // ����������
  ~DataWA();
  // ���� � ������ ����������� �����������
  void setAnisotropyFactor(objData anisotropyFactors);
  // ���������� ������ � ����������
  virtual int Create(){ return 1; };
  // �������� ����������
  objData getXYZ(int i) const;
  // �������� �������� �������� ������
  float getValue(const int col, const int rec) const;
  // �������� �� ������� ��������� � �������� �������
  long getSubIndex(const long rec) const;
  // �������� ���-�� �������
  int getCountColumn() const;
  // �������� ���-�� �������
  int getCountRecord() const;
  // �������� ����� ������� �� ��������
  int getNameToNumColumn(String value) const;
  // �������� ������������ ������� �� ������
  String getNameCol(int value) const;
  // �������� ��������� �������
  Column getCol(const int value) const;
  // �������� ������� �������� ������� (��������������)
  float getAverageValueCol(const int col) const;
};
//---------------------------------------------------------------------------
#endif
