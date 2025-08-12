//---------------------------------------------------------------------------
#ifndef DataWA_2DH
#define DataWA_2DH
#include "DataWA.h"
//---------------------------------------------------------------------------
// Класс подготовки данных к вычислению весовой аппроксимации 2D-3D
//---------------------------------------------------------------------------
class DataWA_2D : public DataWA {

private:
  // Указатель на настройки пользователя
  const SettingsApprox2D3D* _Settings;

public:
  // Конструктор
  DataWA_2D(const Data *Data_, const SettingsApprox2D3D *Settings_);
  // Конструктор для уровней
  DataWA_2D(const Data *Data_, const SettingsApprox2D3D *Settings_,
      const int NumLevel_);
	// Деструктор
  ~DataWA_2D();
  // Отбор данных
  virtual int Create();

};
//---------------------------------------------------------------------------
#endif
