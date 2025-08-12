//---------------------------------------------------------------------------
#include <vcl.h>
#pragma hdrstop
#include "SettingsApprox2D3D.h"
//---------------------------------------------------------------------------
#pragma package(smart_init)

//---------------------------------------------------------------------------
void SettingsApprox2D3D::Clear()
{
    // Имя столбца X
    _NameX = "";
    // Имя столбца Y
    _NameY = "";
    // Имя столбца Z
    _NameZ = "";
    // Тип сечения
    _TypeSection = mNormal;
    // Размерность обл. аппроксимации
    _DimensionAreaAprox = mArea;
    // Границы обл. апроксимации
    _xScopeAreaAprox.From = 0;
    _xScopeAreaAprox.Till = 0;
    _yScopeAreaAprox.From = 0;
    _yScopeAreaAprox.Till = 0;
    _zScopeAreaAprox.From = 0;
    _zScopeAreaAprox.Till = 0;
    _xScopeDataAprox.From = 0;
    _xScopeDataAprox.Till = 0;
    _yScopeDataAprox.From = 0;
    _yScopeDataAprox.Till = 0;
    _zScopeDataAprox.From = 0;
    _zScopeDataAprox.Till = 0;
    // Шаги сетки
    _StepNet.x = 0;
    _StepNet.y = 0;
    _StepNet.z = 0;
    // Параметры весовой функции
    _fAlpha = 0;  // Альфа
    _fGamma = 0;  // Гамма
    _fSigma = 0;  //  sigma
    _fBetaFrom = 0;
    _fBetaTo = 0;
    _fBetaStep = 0;

    _xAnisotropyFactor = 1;
    _yAnisotropyFactor = 1;
    _zAnisotropyFactor = 1;

    // Удаление данных
    vCriterion.erase(vCriterion.begin(), vCriterion.end());
    vCriterion.swap(tmp_Criterion);
    // Очистка настроек уровней
    SettingsForLevels->Clear();
}
//---------------------------------------------------------------------------
void SettingsApprox2D3D::Check()
{
    // Имя столбца X
    if (_NameX == "")
      ShowMessage("Не правильное имя столбца Х");
    // Имя столбца Y
    if (_NameY == "")
      ShowMessage("Не правильное имя столбца Y");
    // Имя столбца Z
    if (_NameZ == "")
      ShowMessage("Не правильное имя столбца Z");
    // Размерность обл. аппроксимации
    if ((_DimensionAreaAprox != 0) ||
        (_DimensionAreaAprox != 1) ||
        (_DimensionAreaAprox != 2))
      ShowMessage("Не правильно указана размерность области аппроксимации");
    // Границы обл. апроксимации
    if (_xScopeAreaAprox.From >= _xScopeAreaAprox.Till)
      ShowMessage("Не правильно указаны границы области аппроксимации для х");
    if (_yScopeAreaAprox.From >= _yScopeAreaAprox.Till)
      ShowMessage("Не правильно указаны границы области аппроксимации для y");
    if (_zScopeAreaAprox.From >= _zScopeAreaAprox.Till)
      ShowMessage("Не правильно указаны границы области аппроксимации для z");
    // Шаги сетки
    if (_StepNet.x <= 0)
      ShowMessage("Шаг сетки для х не может быть меньше или равен 0");
    if (_StepNet.y <= 0)
      ShowMessage("Шаг сетки для y не может быть меньше или равен 0");
}
//---------------------------------------------------------------------------
SettingsApprox2D3D::SettingsApprox2D3D()
{
  SettingsForLevels = new TSettingsForLevels();
  Clear();
}
//---------------------------------------------------------------------------
// Добавление признаков
//---------------------------------------------------------------------------
void SettingsApprox2D3D::setCriterion(Criterion value)
{
  vCriterion.push_back(value);
}
//---------------------------------------------------------------------------
// Количество признаков
//---------------------------------------------------------------------------
long SettingsApprox2D3D::getCountCriterion() const
{
  return vCriterion.size();
}
//---------------------------------------------------------------------------
// Получить признак
//---------------------------------------------------------------------------
Criterion SettingsApprox2D3D::getCriterion(long num) const
{
   return vCriterion[num];
}
//---------------------------------------------------------------------------
SettingsApprox2D3D::~SettingsApprox2D3D()
{
  //  Удаление настроек для уровней
  delete SettingsForLevels;
}
//---------------------------------------------------------------------------
void __fastcall SettingsApprox2D3D::setAlpha(float value)
{
        if(_fAlpha != value) {
                _fAlpha = value;
        }
}
//---------------------------------------------------------------------------
float __fastcall SettingsApprox2D3D::getAlpha() const
{
        return _fAlpha;
}
//---------------------------------------------------------------------------
void __fastcall SettingsApprox2D3D::setGamma(float value)
{
        if(_fGamma != value) {
                _fGamma = value;
        }
}
//---------------------------------------------------------------------------
float __fastcall SettingsApprox2D3D::getGamma() const
{
        return _fGamma;
}
//---------------------------------------------------------------------------
void __fastcall SettingsApprox2D3D::setSigma(float value)
{
        if(_fSigma != value) {
                _fSigma = value;
        }
}
//---------------------------------------------------------------------------
float __fastcall SettingsApprox2D3D::getSigma() const
{
        return _fSigma;
}
//---------------------------------------------------------------------------
void __fastcall SettingsApprox2D3D::setBetaFrom(float value)
{
        if(_fBetaFrom != value) {
                _fBetaFrom = value;
        }
}
//---------------------------------------------------------------------------
float __fastcall SettingsApprox2D3D::getBetaFrom() const
{
        return _fBetaFrom;
}
//---------------------------------------------------------------------------
void __fastcall SettingsApprox2D3D::setBetaTo(float value)
{
        if(_fBetaTo != value) {
                _fBetaTo = value;
        }
}
//---------------------------------------------------------------------------
float __fastcall SettingsApprox2D3D::getBetaTo() const
{
        return _fBetaTo;
}
//---------------------------------------------------------------------------
void __fastcall SettingsApprox2D3D::setBetaStep(float value)
{
        if(_fBetaStep != value) {
                _fBetaStep = value;
        }
}
//---------------------------------------------------------------------------
float __fastcall SettingsApprox2D3D::getBetaStep() const
{
        return _fBetaStep;
}
//---------------------------------------------------------------------------
void __fastcall SettingsApprox2D3D::setNameX(String value)
{
        if(_NameX != value) {
                _NameX = value;
        }
}
//---------------------------------------------------------------------------
String __fastcall SettingsApprox2D3D::getNameX() const
{
        return _NameX;
}
//---------------------------------------------------------------------------
void __fastcall SettingsApprox2D3D::setNameY(String value)
{
        if(_NameY != value) {
                _NameY = value;
        }
}
//---------------------------------------------------------------------------
String __fastcall SettingsApprox2D3D::getNameY() const
{
        return _NameY;
}
//---------------------------------------------------------------------------
void __fastcall SettingsApprox2D3D::setNameZ(String value)
{
        if(_NameZ != value) {
                _NameZ = value;
        }
}
//---------------------------------------------------------------------------
String __fastcall SettingsApprox2D3D::getNameZ() const
{
        return _NameZ;
}
//---------------------------------------------------------------------------
void __fastcall SettingsApprox2D3D::SetStepNet(PositionData value)
{
        if(_StepNet != value) {
                _StepNet = value;
        }
}
//---------------------------------------------------------------------------
PositionData __fastcall SettingsApprox2D3D::GetStepNet() const
{
        return _StepNet;
}
//---------------------------------------------------------------------------
void __fastcall SettingsApprox2D3D::setxScopeAreaAprox(FromTill value)
{
        if(_xScopeAreaAprox != value) {
                _xScopeAreaAprox = value;
        }
}
//---------------------------------------------------------------------------
FromTill __fastcall SettingsApprox2D3D::getxScopeAreaAprox() const
{
        return _xScopeAreaAprox;
}
//---------------------------------------------------------------------------
void __fastcall SettingsApprox2D3D::setyScopeAreaAprox(FromTill value)
{
        if(_yScopeAreaAprox != value) {
                _yScopeAreaAprox = value;
        }
}
//---------------------------------------------------------------------------
FromTill __fastcall SettingsApprox2D3D::getyScopeAreaAprox() const
{
        return _yScopeAreaAprox;
}
//---------------------------------------------------------------------------
void __fastcall SettingsApprox2D3D::setzScopeAreaAprox(FromTill value)
{
        if(_zScopeAreaAprox != value) {
                _zScopeAreaAprox = value;
        }
}
//---------------------------------------------------------------------------
FromTill __fastcall SettingsApprox2D3D::getzScopeAreaAprox() const
{
        return _zScopeAreaAprox;
}
//---------------------------------------------------------------------------
void __fastcall SettingsApprox2D3D::setDimensionAreaAprox(DimensionAreaAprox value)
{
        if(_DimensionAreaAprox != value) {
                _DimensionAreaAprox = value;
        }
}
//---------------------------------------------------------------------------
DimensionAreaAprox __fastcall SettingsApprox2D3D::getDimensionAreaAprox() const
{
        return _DimensionAreaAprox;
}
//---------------------------------------------------------------------------
void __fastcall SettingsApprox2D3D::setxScopeDataAprox(FromTill value)
{
        if(_xScopeDataAprox != value) {
                _xScopeDataAprox = value;
        }
}
//---------------------------------------------------------------------------
FromTill __fastcall SettingsApprox2D3D::getxScopeDataAprox() const
{
        return _xScopeDataAprox;
}
//---------------------------------------------------------------------------
void __fastcall SettingsApprox2D3D::setyScopeDataAprox(FromTill value)
{
        if(_yScopeDataAprox != value) {
                _yScopeDataAprox = value;
        }
}
//---------------------------------------------------------------------------
FromTill __fastcall SettingsApprox2D3D::getyScopeDataAprox() const
{
        return _yScopeDataAprox;
}
//---------------------------------------------------------------------------
void __fastcall SettingsApprox2D3D::setzScopeDataAprox(FromTill value)
{
        if(_zScopeDataAprox != value) {
                _zScopeDataAprox = value;
        }
}
//---------------------------------------------------------------------------
FromTill __fastcall SettingsApprox2D3D::getzScopeDataAprox() const
{
        return _zScopeDataAprox;
}
//---------------------------------------------------------------------------
void __fastcall SettingsApprox2D3D::setStandart(bool value)
{
        if(_bStandart != value) {
               _bStandart = value;
        }
}
//---------------------------------------------------------------------------
bool __fastcall SettingsApprox2D3D::getStandart() const
{
        return _bStandart;
}
//---------------------------------------------------------------------------
void __fastcall SettingsApprox2D3D::SetBottomLeftPoint(PositionData value)
{
        if(_BottomLeftPoint != value) {
               _BottomLeftPoint = value;
        }
}
//---------------------------------------------------------------------------
PositionData __fastcall SettingsApprox2D3D::GetBottomLeftPoint() const
{
        return _BottomLeftPoint;
}
//---------------------------------------------------------------------------
void __fastcall SettingsApprox2D3D::SetBottomRightPoint(PositionData value)
{
        if(_BottomRightPoint != value) {
               _BottomRightPoint = value;
        }
}
//---------------------------------------------------------------------------
PositionData __fastcall SettingsApprox2D3D::GetBottomRightPoint() const
{
        return _BottomRightPoint;
}
//---------------------------------------------------------------------------
void __fastcall SettingsApprox2D3D::SetTopLeftPoint(PositionData value)
{
        if(_TopLeftPoint != value) {
               _TopLeftPoint = value;
        }
}
//---------------------------------------------------------------------------
PositionData __fastcall SettingsApprox2D3D::GetTopLeftPoint() const
{
        return _TopLeftPoint;
}
//---------------------------------------------------------------------------
void __fastcall SettingsApprox2D3D::SetTopRightPoint(PositionData value)
{
        if(_TopRightPoint != value) {
               _TopRightPoint = value;
        }
}
//---------------------------------------------------------------------------
PositionData __fastcall SettingsApprox2D3D::GetTopRightPoint() const
{
        return _TopRightPoint;
}
//---------------------------------------------------------------------------
void __fastcall SettingsApprox2D3D::SetWhichParallelPlane(String value)
{
        if(_WhichParallelPlane != value) {
                _WhichParallelPlane = value;
        }
}
//---------------------------------------------------------------------------
String __fastcall SettingsApprox2D3D::GetWhichParallelPlane() const
{
        return _WhichParallelPlane;
}
//---------------------------------------------------------------------------
void __fastcall SettingsApprox2D3D::SetpTypeSection(TypeSection value)
{
        if(_TypeSection != value) {
                _TypeSection = value;
        }
}
//---------------------------------------------------------------------------
TypeSection __fastcall SettingsApprox2D3D::GetpTypeSection() const
{
        return _TypeSection;
}
//---------------------------------------------------------------------------
void __fastcall SettingsApprox2D3D::SetCountLevels(int value)
{
        if(_CountLevels != value) {
                _CountLevels = value;
        }
}
//---------------------------------------------------------------------------
int __fastcall SettingsApprox2D3D::GetCountLevels() const
{
        return _CountLevels;
}
//---------------------------------------------------------------------------
void __fastcall SettingsApprox2D3D::SetxAnisotropyFactor(float value)
{
  if(_xAnisotropyFactor != value) {
    _xAnisotropyFactor = value;
  }
}
//---------------------------------------------------------------------------
float __fastcall SettingsApprox2D3D::GetxAnisotropyFactor()
{
  if (_xAnisotropyFactor == 0)
    return 1;
  return _xAnisotropyFactor;
}
//---------------------------------------------------------------------------
void __fastcall SettingsApprox2D3D::SetyAnisotropyFactor(float value)
{
  if(_yAnisotropyFactor != value) {
    _yAnisotropyFactor = value;
  }
}
//---------------------------------------------------------------------------
float __fastcall SettingsApprox2D3D::GetyAnisotropyFactor()
{
  if (_yAnisotropyFactor == 0)
    return 1;
  return _yAnisotropyFactor;
}
//---------------------------------------------------------------------------
void __fastcall SettingsApprox2D3D::SetzAnisotropyFactor(float value)
{
  if(_zAnisotropyFactor != value) {
    _zAnisotropyFactor = value;
  }
}
//---------------------------------------------------------------------------
float __fastcall SettingsApprox2D3D::GetzAnisotropyFactor()
{
  if (_zAnisotropyFactor == 0)
    return 1;
  return _zAnisotropyFactor;
}
//---------------------------------------------------------------------------
