//---------------------------------------------------------------------------
#ifndef ProcessWA_2DH
#define ProcessWA_2DH
#include "ProcessWA.h"
//---------------------------------------------------------------------------
// Класс вычисления весовой аппроксимации на плоскость и
// предоставления интерфейса к полученным результатам
//---------------------------------------------------------------------------
class ProcessWA_2D : public ProcessWA {

private:
  // Настройки пользователя
    const SettingsApprox2D3D* _Settings;
public:
  // Конструктор
  ProcessWA_2D(const SettingsApprox2D3D* Settings_, const Data *Data_,
      DataWA *DataWA_, DataWA_Area *_dataWA_Area,
      const ParamCalcWA *ParamCalcWA_, objData AnisotropyFactor);
  // Конструктор для уровней
  ProcessWA_2D(const SettingsApprox2D3D* Settings_, const Data *Data_,
      DataWA *DataWA_, DataWA_Area *_dataWA_Area,
      const ParamCalcWA *ParamCalcWA_,
      const int NumLevel_, objData AnisotropyFactor);
  // Деструктор
  ~ProcessWA_2D();
  //  Запуск
  virtual bool Run();
  // Показать график
  virtual bool VisualResultGraph();
};
//---------------------------------------------------------------------------
#endif
