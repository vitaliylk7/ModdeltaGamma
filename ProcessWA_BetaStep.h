//---------------------------------------------------------------------------
#ifndef ProcessWA_BetaStepH
#define ProcessWA_BetaStepH
#include <list>
#include <fstream.h>
#include "FactoryProcessWA.h"
#include "ReportText.h"
#include "Structs.h"
#include "ProgressWork.h"
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
class ProcessWA_BetaStep : public ProcessWA {

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
  // ������� ������������ ������� ���������� ��������
  void ViewProgress(const long count);  
  // ���������� �������
  int CountLevels;
  // ���������� �������� ��������� �����
  int numbIteration;
  // ��������� �����������
  objData _AnisotropyFactor;

  // �����
  TStrings *html;
  // �����
  TfrmReportText *frmReportText;


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
  // ������� � ������� ������� � ��������
  void add_parval(TStrings *html, String par, int width_par, String val,
    int width_val);
  // ������ ��������� �������
  void th(int width, String value);
  // ������ �������
  void td(int width, String value);
  // ������ ������ ��������������� ��� ����� ��������������
  void VisualDataD(const int col, String name);

public:
  // ����������� � ������ �������
  ProcessWA_BetaStep(const Settings *settings, const Data *data,
    DataWA *dataWA, DataWA *dataWA_Area, const ParamCalcWA *paramCalcWA,
    const objData anisotropyFactor);
  // ����������
  ~ProcessWA_BetaStep();
  //  ������
  virtual bool Run();
  // �������
  virtual bool Clear();
  // ��������� ���������
  virtual bool SaveResult();
  // �������� ������
  virtual bool VisualResultGraph();
  // �������� �������� ����������
  virtual bool VisualResultText();

};
//---------------------------------------------------------------------------
#endif
