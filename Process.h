//---------------------------------------------------------------------------
#ifndef ProcessH
#define ProcessH

#include <fstream.h>
#include <vector>

#include "Data.h"
#include "Settings.h"

 // Класс выполняющий все основные вычисления
class MainProcess{
public:
  // Конструктор
  MainProcess(){ };
  //  Запуск
  virtual bool Run() = 0;
  // Очистка
  virtual bool Clear() { return false; };
  // Сохранить результат
  virtual bool SaveResult() = 0;
  // Показать график
  virtual bool VisualResultGraph() = 0;
  // Показать значения результата
  virtual bool VisualResultText() = 0;
  // Деструктор
  virtual ~MainProcess(){ };
};

//---------------------------------------------------------------------------
#endif
