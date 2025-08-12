//---------------------------------------------------------------------------
#include <Dialogs.hpp>
#pragma hdrstop
#include "Utils.h"
#include "MainDataModul.h"
//---------------------------------------------------------------------------
#pragma package(smart_init)
//---------------------------------------------------------------------------
// �������� ������������ ����� ��� ����������
//---------------------------------------------------------------------------
String getFileNameSave(String Title)
{

  TSaveDialog* SaveDialog = new TSaveDialog(dmGlobal);
  SaveDialog->Title = Title;
  AnsiString sFileName = "1";

  if (SaveDialog->Execute())
    sFileName = SaveDialog->FileName;

  delete SaveDialog;

  if (sFileName != ""){
    return sFileName;
  }
  else {
    ShowMessage("�� ������ ��� �����");
    return "";
  }
}
//---------------------------------------------------------------------------
// �������� ������������ ����� ��� ����������
//---------------------------------------------------------------------------
String getFileNameSave(String Title, String DefaultFileName)
{

  TSaveDialog* SaveDialog = new TSaveDialog(dmGlobal);
  SaveDialog->Title = Title;
  AnsiString sFileName = "1";
  SaveDialog->FileName = DefaultFileName;

  if (SaveDialog->Execute())
    sFileName = SaveDialog->FileName;

  delete SaveDialog;

  if (sFileName != ""){
    return sFileName;
  }
  else {
    ShowMessage("�� ������ ��� �����");
    return "";
  }
}
//---------------------------------------------------------------------------
// ��������� ����� �������
//---------------------------------------------------------------------------
float CalcL(PositionData &Point_1, PositionData &Point_2)
{
	return sqrt(pow(Point_2.x - Point_1.x,2) +
  						pow(Point_2.y - Point_1.y,2) +
              pow(Point_2.z - Point_1.z,2));
}
// ---------------------------------------------------------------------------
// �������� ������ �� ��������
// ---------------------------------------------------------------------------
String getGaps(int count)
{
  String str = "";
  for (int i = 0; i < count; ++i)
  {
    str += " ";
  }

  return str;
}
// ---------------------------------------------------------------------------
