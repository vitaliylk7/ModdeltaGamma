//---------------------------------------------------------------------------

#ifndef SettingsH
#define SettingsH

#include <vcl.h>
#include <vector>
#include <fstream.h>
#include "Ini.h"
#include "SettingsApprox2D3D.h"

// Типы моделей
typedef enum {mApprox1D = 0, mApprox2D, mApprox3D, mReg1D, mReg2D, mReg3D,
    mPVO} TypeModels;

// настройки пользователя
class Settings
{
  private:
        // Статус
        bool _bStatus;
        // Тип модели
        TypeModels _TypeModel;
				void __fastcall SetTypeModel(TypeModels value);
				TypeModels __fastcall GetTypeModel() const;
				bool __fastcall GetStatus() const;
  public:
        // Конструктор
        Settings();
        // Деструктор
        ~Settings(void);
        // Очистить настройки пользователя
        void Clear();
        // Проверка настроек
        void Check();
				// Тип модели
        __property TypeModels TypeModel  = { read=GetTypeModel, write=SetTypeModel };
				__property bool Status  = { read=GetStatus };        
        // Настройки для разных процессов
        SettingsApprox2D3D *mSettingsApprox2D3D;
        // Получить кол-во уровней для весовой аппроксимации
        int getCountLevelsWA() const;
};

//---------------------------------------------------------------------------
#endif
