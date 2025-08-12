//---------------------------------------------------------------------------
#ifndef SkewWAProcessH
#define SkewWAProcessH
#include "WeigthApproximationProcess.h"

//----------------------------------------------------------------------
// Класс выполняющий вычисление весовой аппроксимации с косым сечением -
//----------------------------------------------------------------------

class SkewWAProcess : public WeigthApproximationProcess {
private:

  // Построение сетки
  virtual bool CreateNet() const;

  // Формирование данных
  virtual bool CreateData() const;

  // Вычисление весовой аппроксимации
  virtual bool Calculation() const;

  // Длина отрезка который и представляет само сечение
  float LBase, LHeight;
  // Процесс построения сетки для косого сечения
  bool CreateNetSkewSection();
  // Построение сетки для косого сечения параллельного x
  bool xNetSkewSectionBuild(Coordinate _TopRightPoint,
          Coordinate _TopLeftPoint, Coordinate _BottomRightPoint,
          Coordinate _BottomLeftPoint, float LBase, float LHeight,
          float StepBase, float StepHeight, int CountStepBase,
          int CountStepHeight);
  // Построение сетки для косого сечения параллельного y
  bool yNetSkewSectionBuild(Coordinate _TopRightPoint,
          Coordinate _TopLeftPoint, Coordinate _BottomRightPoint,
          Coordinate _BottomLeftPoint, float LBase, float LHeight,
          float StepBase, float StepHeight, int CountStepBase,
          int CountStepHeight);
  // Построение сетки для косого сечения параллельного z
  bool zNetSkewSectionBuild(Coordinate _TopRightPoint,
          Coordinate _TopLeftPoint, Coordinate _BottomRightPoint,
          Coordinate _BottomLeftPoint, float LBase, float LHeight,
          float StepBase, float StepHeight, int CountStepBase,
          int CountStepHeight);

public:

  // Конструктор
  SkewWAProcess(const Data *Data_, const Settings *Settings_);

  // Размер основания
  float getLBase();
  // Размер высоты
  float getLHeight();

};

#endif
