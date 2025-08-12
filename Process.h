//---------------------------------------------------------------------------
#ifndef ProcessH
#define ProcessH

#include <fstream.h>
#include <vector>

#include "Data.h"
#include "Settings.h"

 // ����� ����������� ��� �������� ����������
class MainProcess{
public:
  // �����������
  MainProcess(){ };
  //  ������
  virtual bool Run() = 0;
  // �������
  virtual bool Clear() { return false; };
  // ��������� ���������
  virtual bool SaveResult() = 0;
  // �������� ������
  virtual bool VisualResultGraph() = 0;
  // �������� �������� ����������
  virtual bool VisualResultText() = 0;
  // ����������
  virtual ~MainProcess(){ };
};

//---------------------------------------------------------------------------
#endif
