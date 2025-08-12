//---------------------------------------------------------------------------
#ifndef UtilsH
#define UtilsH
//---------------------------------------------------------------------------
#include <vcl.h>
#include <math.h>
#include "Structs.h"

// Получить наименование файла для сохранения
String getFileNameSave(String Title);
// Получить наименование файла для сохранения
String getFileNameSave(String Title, String DefaultFileName);
// Вычислить длину отрезка
float CalcL(PositionData &Point_1, PositionData &Point_2);
// Получить строку из пробелов
String getGaps(int count);

#endif
