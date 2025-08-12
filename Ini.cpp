//---------------------------------------------------------------------------

#include <vcl.h>
#pragma hdrstop

#include "Ini.h"

//---------------------------------------------------------------------------

#pragma package(smart_init)
//---------------------------------------------------------------------------
TIni::TIni(void)
{
 pWinIni = new TIniFile("WeigthApproximation.ini");
}
//---------------------------------------------------------------------------
String TIni::read(String FormName, String Name)
{
  return pWinIni->ReadString(FormName, Name, "");
}
//---------------------------------------------------------------------------
void TIni::write(String FormName, String Name, String value)
{
  pWinIni->WriteString(FormName, Name, value);
}
//---------------------------------------------------------------------------
void TIni::write(String FormName, String Name, int value)
{
  pWinIni->WriteString(FormName, Name, IntToStr(value));
}
//---------------------------------------------------------------------------
void TIni::write(String FormName, String Name, float value)
{
  pWinIni->WriteString(FormName, Name, FloatToStr(value));
}
//---------------------------------------------------------------------------
void TIni::write(String FormName, String Name, bool value)
{
  String s;
  if (value)
    s = "true";
  else
    s = "false";

  pWinIni->WriteString(FormName, Name, s);
}
//---------------------------------------------------------------------------
TIni::~TIni(void)
{
 delete pWinIni;
}
//---------------------------------------------------------------------------
