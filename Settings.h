//---------------------------------------------------------------------------

#ifndef SettingsH
#define SettingsH

#include <vcl.h>
#include <vector>
#include <fstream.h>
#include "Ini.h"
#include "SettingsApprox2D3D.h"

// ���� �������
typedef enum {mApprox1D = 0, mApprox2D, mApprox3D, mReg1D, mReg2D, mReg3D,
    mPVO} TypeModels;

// ��������� ������������
class Settings
{
  private:
        // ������
        bool _bStatus;
        // ��� ������
        TypeModels _TypeModel;
				void __fastcall SetTypeModel(TypeModels value);
				TypeModels __fastcall GetTypeModel() const;
				bool __fastcall GetStatus() const;
  public:
        // �����������
        Settings();
        // ����������
        ~Settings(void);
        // �������� ��������� ������������
        void Clear();
        // �������� ��������
        void Check();
				// ��� ������
        __property TypeModels TypeModel  = { read=GetTypeModel, write=SetTypeModel };
				__property bool Status  = { read=GetStatus };        
        // ��������� ��� ������ ���������
        SettingsApprox2D3D *mSettingsApprox2D3D;
        // �������� ���-�� ������� ��� ������� �������������
        int getCountLevelsWA() const;
};

//---------------------------------------------------------------------------
#endif
