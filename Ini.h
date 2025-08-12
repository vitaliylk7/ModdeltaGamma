//---------------------------------------------------------------------------
#ifndef IniH
#define IniH
#include <IniFiles.hpp>
#include "Structs.h"
//---------------------------------------------------------------------------
// ����� ���������� ��������
//---------------------------------------------------------------------------
class TIni {
private:
 TIniFile *pWinIni;
public:
 TIni(void);
 // ����� ���������
 String read(String FormName, String Name);

 void write(String FormName, String Name, String value);
 void write(String FormName, String Name, int value);
 void write(String FormName, String Name, float value);
 void write(String FormName, String Name, bool value);

 ~TIni(void);
};
#endif
