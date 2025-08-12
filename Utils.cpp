//---------------------------------------------------------------------------
#include <Dialogs.hpp>
#pragma hdrstop
#include "Utils.h"
#include "MainDataModul.h"
//---------------------------------------------------------------------------
#pragma package(smart_init)
//---------------------------------------------------------------------------
// Получить наименование файла для сохранения
//---------------------------------------------------------------------------
String getFileNameSave(String Title)
{

  TSaveDialog* SaveDialog = new TSaveDialog(dmGlobal);
  SaveDialog->Title = Title;
  SaveDialog->DefaultExt = "txt"; // Set default extension to .txt
  SaveDialog->Filter = "Text files (*.txt)|*.txt|All files (*.*)|*.*"; // Set filter for .txt files
  SaveDialog->FilterIndex = 1; // Select the .txt filter by default
  AnsiString sFileName = "1";

  if (SaveDialog->Execute())
    sFileName = SaveDialog->FileName;

  delete SaveDialog;

  if (sFileName != ""){
    return sFileName;
  }
  else {
    ShowMessage("Не верное имя файла");
    return "";
  }
}
//---------------------------------------------------------------------------
// Получить наименование файла для сохранения
//---------------------------------------------------------------------------
String getFileNameSave(String Title, String DefaultFileName)
{

  TSaveDialog* SaveDialog = new TSaveDialog(dmGlobal);
  SaveDialog->Title = Title;
  SaveDialog->DefaultExt = "txt"; // Set default extension to .txt
  SaveDialog->Filter = "Text files (*.txt)|*.txt|All files (*.*)|*.*"; // Set filter for .txt files
  SaveDialog->FilterIndex = 1; // Select the .txt filter by default
  AnsiString sFileName = "1";
  SaveDialog->FileName = DefaultFileName;

  if (SaveDialog->Execute())
    sFileName = SaveDialog->FileName;

  delete SaveDialog;

  if (sFileName != ""){
    return sFileName;
  }
  else {
    ShowMessage("Не верное имя файла");
    return "";
  }
}
//---------------------------------------------------------------------------
// Вычислить длину отрезка
//---------------------------------------------------------------------------
float CalcL(PositionData &Point_1, PositionData &Point_2)
{
	return sqrt(pow(Point_2.x - Point_1.x,2) +
  						pow(Point_2.y - Point_1.y,2) +
              pow(Point_2.z - Point_1.z,2));
}
// ---------------------------------------------------------------------------
// Получить строку из пробелов
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
