//---------------------------------------------------------------------------
#ifndef SettingsApprox2D3DH
#define SettingsApprox2D3DH

#include "Structs.h"
#include "SettingsForLevels.h"
//---------------------------------------------------------------------------

// ��� �������
typedef enum {mNormal=0, mSkew} TypeSection;

// ����������� ���. �������������
typedef enum {mArea=0, mFlat, mLine} DimensionAreaAprox;

class SettingsApprox2D3D
{
	private:
        // ���-�� �������
        int _CountLevels;
        // ��� �������
        TypeSection _TypeSection;
        // ��� ������� X
        String _NameX;
        // ��� ������� Y
        String _NameY;
        // ��� ������� Z
        String _NameZ;
        // ����������� ���. �������������
        DimensionAreaAprox _DimensionAreaAprox;
        // ������� ���. �������������
        FromTill _xScopeAreaAprox;
        FromTill _yScopeAreaAprox;
        FromTill _zScopeAreaAprox;
        // ����� ��� ����������� ���������
        String _WhichParallelPlane;
        // ������� ���. ������������� ��� ������ �������
        PositionData _TopRightPoint;
        PositionData _TopLeftPoint;
        PositionData _BottomRightPoint;
        PositionData _BottomLeftPoint;
        // ������� ����� �������� �����
        FromTill _xScopeDataAprox;
        FromTill _yScopeDataAprox;
        FromTill _zScopeDataAprox;
        // ���� �����
        PositionData _StepNet;
        // ��������� ������� �������
        float _fAlpha;  // �����
        float _fGamma;  // �����
        float _fBetaFrom;       //
        float _fBetaTo;         // � ��������� ������ ��������� �������� �����
        float _fBetaStep;       //
        float _fSigma;  // �����
        // ����������� �����������
        float _xAnisotropyFactor;
        float _yAnisotropyFactor;
        float _zAnisotropyFactor;
        // ��������� ��������
        vector<Criterion> vCriterion;
        vector<Criterion> tmp_Criterion;

        // ���������� ���������, �� ���� ���������� �� �� �����, � �� ���� �� ����� ������
        bool _bStandart;
        void __fastcall setStandart(bool value);
        bool __fastcall getStandart() const;

        // ������� ��� ������ � ����������
        void __fastcall setAlpha(float value);
        float __fastcall getAlpha() const;
        void __fastcall setGamma(float value);
        float __fastcall getGamma() const;
        void __fastcall setSigma(float value);
        float __fastcall getSigma() const;
        void __fastcall setBetaFrom(float value);
        float __fastcall getBetaFrom() const;
        void __fastcall setBetaTo(float value);
        float __fastcall getBetaTo() const;
        void __fastcall setBetaStep(float value);
        float __fastcall getBetaStep() const;
        void __fastcall setNameX(String value);
        String __fastcall getNameX() const;
        void __fastcall setNameY(String value);
        String __fastcall getNameY() const;
        void __fastcall setNameZ(String value);
        String __fastcall getNameZ() const;
        void __fastcall SetStepNet(PositionData value);
        PositionData __fastcall GetStepNet() const;
        void __fastcall setxScopeAreaAprox(FromTill value);
        FromTill __fastcall getxScopeAreaAprox() const;
        void __fastcall setyScopeAreaAprox(FromTill value);
        FromTill __fastcall getyScopeAreaAprox() const;
        void __fastcall setzScopeAreaAprox(FromTill value);
        FromTill __fastcall getzScopeAreaAprox() const;
        // ������� ����� �������� �����
        void __fastcall setxScopeDataAprox(FromTill value);
        FromTill __fastcall getxScopeDataAprox() const;
        void __fastcall setyScopeDataAprox(FromTill value);
        FromTill __fastcall getyScopeDataAprox() const;
        void __fastcall setzScopeDataAprox(FromTill value);
        FromTill __fastcall getzScopeDataAprox() const;

        void __fastcall setDimensionAreaAprox(DimensionAreaAprox value);
        DimensionAreaAprox __fastcall getDimensionAreaAprox() const;
        void __fastcall SetBottomLeftPoint(PositionData value);
        PositionData __fastcall GetBottomLeftPoint() const;
        void __fastcall SetBottomRightPoint(PositionData value);
        PositionData __fastcall GetBottomRightPoint() const;
        void __fastcall SetTopLeftPoint(PositionData value);
        PositionData __fastcall GetTopLeftPoint() const;
        void __fastcall SetTopRightPoint(PositionData value);
        PositionData __fastcall GetTopRightPoint() const;
        void __fastcall SetWhichParallelPlane(String value);
        String __fastcall GetWhichParallelPlane() const;
        void __fastcall SetpTypeSection(TypeSection value);
        TypeSection __fastcall GetpTypeSection() const;
        void __fastcall SetCountLevels(int value);
        int __fastcall GetCountLevels() const;
        void __fastcall SetxAnisotropyFactor(float value);
        float __fastcall GetxAnisotropyFactor();
        void __fastcall SetyAnisotropyFactor(float value);
        float __fastcall GetyAnisotropyFactor();
        void __fastcall SetzAnisotropyFactor(float value);
        float __fastcall GetzAnisotropyFactor();

	public:
  			// �����������
        SettingsApprox2D3D();
        // ����������
        ~SettingsApprox2D3D();
        // �������� ��������� ������������
        void Clear();
        // �������� ��������
        void Check();
        // ��������� �������
        TSettingsForLevels* SettingsForLevels;
        // ���������� ���������
        void setCriterion(Criterion value);
        // ���������� ���������
        long getCountCriterion() const;
        // �������� �������
        Criterion getCriterion(long num) const;
        // ��������
        __property float Alpha  = { read=getAlpha, write=setAlpha };
        __property float Gamma  = { read=getGamma, write=setGamma };
        __property float Sigma  = { read=getSigma, write=setSigma };
        __property float BetaFrom  = { read=getBetaFrom, write=setBetaFrom };
        __property float BetaTo  = { read=getBetaTo, write=setBetaTo };
        __property float BetaStep  = { read=getBetaStep, write=setBetaStep };
        __property String NameX  = { read=getNameX, write=setNameX };
        __property String NameY  = { read=getNameY, write=setNameY };
        __property String NameZ  = { read=getNameZ, write=setNameZ };
        __property PositionData StepNet  = { read=GetStepNet, write=SetStepNet };
        __property FromTill xScopeAreaAprox  = { read=getxScopeAreaAprox, write=setxScopeAreaAprox };
        __property FromTill yScopeAreaAprox  = { read=getyScopeAreaAprox, write=setyScopeAreaAprox };
        __property FromTill zScopeAreaAprox  = { read=getzScopeAreaAprox, write=setzScopeAreaAprox };
        __property FromTill xScopeDataAprox  = { read=getxScopeDataAprox, write=setxScopeDataAprox };
        __property FromTill yScopeDataAprox  = { read=getyScopeDataAprox, write=setyScopeDataAprox };
        __property FromTill zScopeDataAprox  = { read=getzScopeDataAprox, write=setzScopeDataAprox };
        __property DimensionAreaAprox pDimensionAreaAprox  = { read=getDimensionAreaAprox, write=setDimensionAreaAprox };
        __property bool Standart = { read=getStandart, write=setStandart };
        __property PositionData BottomLeftPoint  = { read=GetBottomLeftPoint, write=SetBottomLeftPoint };
        __property PositionData BottomRightPoint  = { read=GetBottomRightPoint, write=SetBottomRightPoint };
        __property PositionData TopLeftPoint  = { read=GetTopLeftPoint, write=SetTopLeftPoint };
        __property PositionData TopRightPoint  = { read=GetTopRightPoint, write=SetTopRightPoint };
        __property String WhichParallelPlane  = { read=GetWhichParallelPlane, write=SetWhichParallelPlane };
        __property TypeSection pTypeSection  = { read=GetpTypeSection, write=SetpTypeSection };
        __property int CountLevels  = { read=GetCountLevels, write=SetCountLevels };
        __property float xAnisotropyFactor  = { read=GetxAnisotropyFactor, write=SetxAnisotropyFactor };
        __property float yAnisotropyFactor  = { read=GetyAnisotropyFactor, write=SetyAnisotropyFactor };
        __property float zAnisotropyFactor  = { read=GetzAnisotropyFactor, write=SetzAnisotropyFactor };
        long CountPointData;
        long CountPointArea;
};

#endif
