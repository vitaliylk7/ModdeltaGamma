//---------------------------------------------------------------------------
#ifndef IniH
#define IniH
#include <IniFiles.hpp>
#include "Structs.h"
//---------------------------------------------------------------------------
// Класс сохранения настроек
//---------------------------------------------------------------------------
class TIni {
private:
 TIniFile *pWinIni;
public:
 TIni(void);
 // Общий интерфейс
 String read(String FormName, String Name);

 void write(String FormName, String Name, String value);
 void write(String FormName, String Name, int value);
 void write(String FormName, String Name, float value);
 void write(String FormName, String Name, bool value);

 ~TIni(void);
};
#endif
