//---------------------------------------------------------------------------
#ifndef FactoryProcessH
#define FactoryProcessH
//---------------------------------------------------------------------------
#include "ProcessWA_levels.h"
#include "ProcessWA_BetaStep.h"

// Фабрика процессов
class FactoryProcess {
private:
  MainProcess* _MainProcess;
  // Фабрика процесса весовой аппроксимации
  FactoryProcessWA *_FactoryProcessWA;
  // Получить параметры анизотропии
  objData getAnisotropyFactor(const Settings *Settings_);
public:
  // Конструктор
  FactoryProcess();
  // Деструктор
  ~FactoryProcess();
  // Создать процесс
  const MainProcess* Create(const Data *Data_, const Settings *Settings_);
  // Создать процесс с установкой параметра Beta
  const MainProcess* Create(const Data *data, const Settings *settings,
    float beta);
	// Удалить процесс
  void Destroy();
};

#endif
