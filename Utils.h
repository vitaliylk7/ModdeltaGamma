//---------------------------------------------------------------------------
#ifndef UtilsH
#define UtilsH
//---------------------------------------------------------------------------
#include <vcl.h>
#include <math.h>
#include "Structs.h"

// �������� ������������ ����� ��� ����������
String getFileNameSave(String Title);
// �������� ������������ ����� ��� ����������
String getFileNameSave(String Title, String DefaultFileName);
// ��������� ����� �������
float CalcL(PositionData &Point_1, PositionData &Point_2);
// �������� ������ �� ��������
String getGaps(int count);

#endif
