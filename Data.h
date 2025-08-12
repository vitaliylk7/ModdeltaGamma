//---------------------------------------------------------------------------
#ifndef DataH
#define DataH

#include <fstream.h>
#include <vector>
#include "Structs.h"

class Data
{
  private:
    // �������� �����
    String _File;
    // ����� ��� ������ � ������
    ifstream fileOut;
    // ���-�� �����
    long _iColumns;
    // ���-�� �������
    long _iRecords;
    // �������� �����
    std::vector<String> vColumnName;
    std::vector<String> tmp_ColumnName;
    // ������
    std::vector <float> vx; // ���������� �������
    std::vector <std::vector<float> > vData;
    // ������� ��� ������ ������
    std::vector <float> tmp_vx;
    std::vector <std::vector<float> > tmp_Data;
    // ������
    bool _bStatus;
    // ������ ������� ����������
    String ReadStr(const char *ss, bool bNewStringsLine);
    // ��������� ��� ����������
    struct Stat {
     float Min;
     float Max;
     float MinBiggerZero;
    } rStat;
    // ������ �������� ��� ����������
    std::vector <Stat> vStat;
    std::vector <Stat> tmp_Stat;

    // ���������� ����������
    void Statistics();
  public:
    // �����������
    Data();
    // ����������� � �������
    Data(const Data *data);
    // ������������ ��������� ������������
    const Data &operator=(const Data &right);
    // ����������
    ~Data(void);
    // ���� � ����� ����������� �����������
    void setAnisotropyFactor(long x, long y, long z, objData anisotropyFactors);
    // ������������� ������, ���������� ��������, �������� ����������
    bool Create(String File);
    // �������� ������������ �����
    String getFileName() const;
    // ������������� �� ������ ������ �� �����
    bool getStatus() const;
    // �������� ������
    float getData(const long col, const long rec) const;
    // ���-�� �����
    long getCountColumn() const;
    // ���-�� �������
    long getCountRecord() const;
    // �������� �������� ����
    String getColumnName(long iColumn) const;
    // �������� ����� ������� �� �������� ����, -1 � ������ ��������� ����� �������
    long getNumberForColumnName(String name) const;
    // �������� Min �� ������ ����
    float getMin(long iColumn) const;
    // �������� Max �� ������ ����
    float getMax(long iColumn) const;
    // �������� Min, ������� ������ 0
    float getMinBiggerZero(long iColumn) const;
};

//---------------------------------------------------------------------------
#endif
