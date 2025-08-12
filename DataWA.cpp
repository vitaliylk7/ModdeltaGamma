//---------------------------------------------------------------------------
#include <vcl.h>
#pragma hdrstop
#include "DataWA.h"
//---------------------------------------------------------------------------
#pragma package(smart_init)
//---------------------------------------------------------------------------
// �����������
//---------------------------------------------------------------------------
DataWA::DataWA(const Data* Data_)
{
  NumLevel = -1;
  _Data = Data_;

}
//---------------------------------------------------------------------------
// ����������� ��� �������
//---------------------------------------------------------------------------
DataWA::DataWA(const Data* Data_, const int NumLevel_)
{
  NumLevel = NumLevel_;
  _Data = Data_;
}
//---------------------------------------------------------------------------
// ����������
//---------------------------------------------------------------------------
DataWA::~DataWA()
{

}
//---------------------------------------------------------------------------
// ����������� �����������
//---------------------------------------------------------------------------
DataWA::DataWA(DataWA *DataWA_) {
  long countCol = DataWA_->getCountColumn();
  long countRec = DataWA_->getCountRecord();

  // ��������� ����������
  for (long rec = 0; rec < countRec; ++rec) {
    vXYZ.push_back(DataWA_->getXYZ(rec));
    vx.erase(vx.begin(), vx.end());
		vx.swap(tmp_v);
    for (long col = 0; col < countCol; ++col) {
      vx.push_back(DataWA_->getValue(col, rec));
    }
    vData.push_back(vx);
  }

  // ��������� �������� �������
  for (long rec = 0; rec < countCol; ++rec) {
    vColumn.push_back(DataWA_->getCol(rec));
  }

  // ��������� ������� �������� ��� ������ ��������������
  CalcAverageValueCols();
}
//---------------------------------------------------------------------------
// ���� � ������ ����������� �����������
//---------------------------------------------------------------------------
void DataWA::setAnisotropyFactor(objData anisotropyFactors) {

  for (long rec = 0; rec < vXYZ.size(); ++rec) {
    objData currObjData = vXYZ[rec];
    vXYZ[rec] = currObjData * anisotropyFactors;
  }
}
//---------------------------------------------------------------------------
// �������� �������� �������
//---------------------------------------------------------------------------
Column DataWA::getColumn(String Name)
{
    Column _Column;
    String s = Name;
    bool hasLgSuffix = false;

    // ���������, ������������� �� ��� �� "_lg"
    if (s.Length() >= 3) {
        String suffix = s.SubString(s.Length() - 2, 3); // ��������� 3 �������
        if (suffix == "_lg") {
            hasLgSuffix = true;
            s.SetLength(s.Length() - 3); // ������� "_lg" �� ����� ��� ������
        }
    }

    // ������� ��������� ������� � ������/�����
    s = s.Trim();

    // ����� ������� � �������� ������ �� ����� (��� "_lg")
    _Column.n = _Data->getNumberForColumnName(s);

    if (-1 == _Column.n) {
        ShowMessage("������: �� ������� �������� ���� '" + s + "' ��� �������� '" + Name + "'");
    }

    _Column.bLog10 = hasLgSuffix;
    _Column._Criterion.Name = Name; // ��������� ������������ ��� (� _lg)

    return _Column;
}
//---------------------------------------------------------------------------
// �������� ������ ������
//---------------------------------------------------------------------------
int DataWA::getRecord(const vector <Column> vCol, vector <float> &v,
    const int rec)
{
  Column _Column;
  float fData, fMinCol;
  if ((NumLevel != -1) && (vCol.size() > 1))
  {
    ShowMessage("��� ������ � �������� ��������� ������ ���� �������.");
    return 1;
  }

  for (unsigned int i = 0; i < vCol.size(); ++i)
  {
    _Column = vCol[i];
    fData = _Data->getData(_Column.n, rec);
    // ���������� ������ � ������ ���� �������� �� ������ � ���������� ������
    // � ����� ������������� ��� ������
    if (NumLevel != -1)
    {
      if ((fData < LevelSettings.CriterionFrom) ||
          (fData > LevelSettings.CriterionTill))
        return 0;
    }

    if (_Column.bLog10)
    {
      if (0 >= fData)
      {
        // ������� ������� ��� ������ �����
        fMinCol = _Data->getMinBiggerZero(_Column.n);
        fData = log10(fMinCol);
      }
      else
      {
        fData = log10(fData);
      }
    }
    v.push_back(fData);
  }
  return 0;
}
//---------------------------------------------------------------------------
// �������� ����������
//---------------------------------------------------------------------------
objData DataWA::getXYZ(int i) const
{
  return vXYZ[i];
}
//---------------------------------------------------------------------------
// �������� �������� �������� ������
//---------------------------------------------------------------------------
float DataWA::getValue(const int col, const int rec) const
{
   return vData[rec][col];
}
//---------------------------------------------------------------------------
// �������� �� ������� ��������� � �������� �������
//---------------------------------------------------------------------------
long DataWA::getSubIndex(const long rec) const
{
  return vSubIndex[rec];
}
//---------------------------------------------------------------------------
// �������� ���-�� �������
//---------------------------------------------------------------------------
int DataWA::getCountColumn() const
{
  return vColumn.size();
}
//---------------------------------------------------------------------------
// �������� ���-�� �������
//---------------------------------------------------------------------------
int DataWA::getCountRecord() const
{
  return vData.size();
}
//---------------------------------------------------------------------------
// �������� ����� ������� �� ��������
//---------------------------------------------------------------------------
int DataWA::getNameToNumColumn(String value) const
{
	for (unsigned int i = 0; i < vColumn.size(); ++i)
  {
  	if (value == vColumn[i]._Criterion.Name)
    	return i;
  }

 	return -1;
}
//---------------------------------------------------------------------------
// �������� ������������ ������� �� ������
//---------------------------------------------------------------------------
String DataWA::getNameCol(int value) const
{
  return vColumn[value]._Criterion.Name;
}
//---------------------------------------------------------------------------
// �������� ��������� �������
//---------------------------------------------------------------------------
Column DataWA::getCol(const int value) const
{
  return vColumn[value];
}
//---------------------------------------------------------------------------
// ���������� ������ ������� ��������
//---------------------------------------------------------------------------
void DataWA::PrepareAverageValueCols(const int countCols) {
  vAverageValuesColumns.swap(tmp_v);
  // vAverageValuesColumns.reserve(countCols);
  for (int rec = 0; rec < countCols; ++rec) {
    vAverageValuesColumns.push_back(0.0f);
  }
}
//---------------------------------------------------------------------------
// ��������� ������� �������� ��� ������ ��������������
//---------------------------------------------------------------------------
void DataWA::CalcAverageValueCols() {
  float valq, valDataq, sq;
  int countCols = vColumn.size();
  int countRecs = vData.size();

  // ���������� ������ ������� ��������
  PrepareAverageValueCols(countCols);
  for (int col = 0; col < countCols; ++col) {
    for (int rec = 0; rec < countRecs; ++rec) {
      sq = vAverageValuesColumns[col];
      valDataq = vData[rec][col];
      valq = valDataq + sq;
      vAverageValuesColumns[col] = valq;
    }
  }

  if (countRecs != 0) {
    for (int col = 0; col < countCols; ++col) {
      vAverageValuesColumns[col] = vAverageValuesColumns[col] / countRecs;
    }
  }
}
//---------------------------------------------------------------------------
// �������� ������� �������� ������� (��������������)
//---------------------------------------------------------------------------
float DataWA::getAverageValueCol(const int col) const {
  return vAverageValuesColumns[col];
}
//---------------------------------------------------------------------------
