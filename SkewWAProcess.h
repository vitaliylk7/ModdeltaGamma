//---------------------------------------------------------------------------
#ifndef SkewWAProcessH
#define SkewWAProcessH
#include "WeigthApproximationProcess.h"

//----------------------------------------------------------------------
// ����� ����������� ���������� ������� ������������� � ����� �������� -
//----------------------------------------------------------------------

class SkewWAProcess : public WeigthApproximationProcess {
private:

  // ���������� �����
  virtual bool CreateNet() const;

  // ������������ ������
  virtual bool CreateData() const;

  // ���������� ������� �������������
  virtual bool Calculation() const;

  // ����� ������� ������� � ������������ ���� �������
  float LBase, LHeight;
  // ������� ���������� ����� ��� ������ �������
  bool CreateNetSkewSection();
  // ���������� ����� ��� ������ ������� ������������� x
  bool xNetSkewSectionBuild(Coordinate _TopRightPoint,
          Coordinate _TopLeftPoint, Coordinate _BottomRightPoint,
          Coordinate _BottomLeftPoint, float LBase, float LHeight,
          float StepBase, float StepHeight, int CountStepBase,
          int CountStepHeight);
  // ���������� ����� ��� ������ ������� ������������� y
  bool yNetSkewSectionBuild(Coordinate _TopRightPoint,
          Coordinate _TopLeftPoint, Coordinate _BottomRightPoint,
          Coordinate _BottomLeftPoint, float LBase, float LHeight,
          float StepBase, float StepHeight, int CountStepBase,
          int CountStepHeight);
  // ���������� ����� ��� ������ ������� ������������� z
  bool zNetSkewSectionBuild(Coordinate _TopRightPoint,
          Coordinate _TopLeftPoint, Coordinate _BottomRightPoint,
          Coordinate _BottomLeftPoint, float LBase, float LHeight,
          float StepBase, float StepHeight, int CountStepBase,
          int CountStepHeight);

public:

  // �����������
  SkewWAProcess(const Data *Data_, const Settings *Settings_);

  // ������ ���������
  float getLBase();
  // ������ ������
  float getLHeight();

};

#endif
