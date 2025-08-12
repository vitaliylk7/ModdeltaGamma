//---------------------------------------------------------------------------
#ifndef ProcessWA_levelsH
#define ProcessWA_levelsH
#include <list>
#include <fstream.h>
#include "FactoryProcessWA.h"
//---------------------------------------------------------------------------
// ������ ������ ��������� ���������� ������� ������������� ��� ���������� �������
//---------------------------------------------------------------------------
typedef std::list<FactoryProcessWA*> listFactoryProcessWA;
typedef std::list<FactoryProcessWA*>::iterator iterFactoryProcessWA;
//---------------------------------------------------------------------------
// ������ ��������� �������
//---------------------------------------------------------------------------
typedef std::list <const ProcessWA*> listProcessWA;
typedef std::list <const ProcessWA*>::iterator iterProcessWA;
//---------------------------------------------------------------------------
// ����� ���������� ������� �������������
//---------------------------------------------------------------------------
class ProcessWA_levels : public ProcessWA {

private:
  // ���������
  const Settings *_Settings;
  // ������� ������
  FactoryDataWA *_FactoryDataWA;
  // ������� �������� ��������� ��� ����������
  FactoryParamWA *_FactoryParamWA;

  // ������ ������ ��������� ���������� ������� ������������� ��� ���������� �������
  listFactoryProcessWA _listFactoryProcessWA;
  // �������� c����� ������ ���������
  iterFactoryProcessWA _iterFactoryProcessWA;
  // ������ ��������� �������
  listProcessWA _listProcessWA;
  // �������� ������ ��������� �������
  iterProcessWA _iterProcessWA;
  // ���������� �������
  int CountLevels;
  // ��������� �����������
  objData _AnisotropyFactor;
  // ������� �������� ������� ������� �������������
  int Create();
  // ���������� ������ �������� ���� � �������� ���� �������
  virtual int Calculation();
  // ���������� ����� ������� ������������� �� �������� �����
  int CalcStandart();
  // ���������� �������� � ��������� ��� ������� �������������
  void CalcMinMax(const int CountCol, const int CountRec,
      const vector <vector<float> > &vv, vector <float> &vMin,
      vector <float> &vMax);
  // �������� �������� � ���������� ���. �������. �� �������� �����
  void setStandart();
  // ��������� ������� ������������� �� �������� ����� � ����
  virtual bool SaveStandart(String FileName);

public:
  // ����������� � ������ �������
  ProcessWA_levels(const Settings *Settings_, const Data *Data_,
      const int CountLevels_, const objData AnisotropyFactor);
  // ����������
  ~ProcessWA_levels();
  //  ������
  virtual bool Run();
  // �������
  virtual bool Clear();
  // �������� ������
  virtual bool VisualResultGraph();
  // �������� �������� ����������
  virtual bool VisualResultText();

};
//---------------------------------------------------------------------------
#endif
