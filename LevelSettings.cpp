//---------------------------------------------------------------------------
#include <vcl.h>
#pragma hdrstop
#include "LevelSettings.h"
//---------------------------------------------------------------------------
#pragma package(smart_init)
//---------------------------------------------------------------------------
// �������� �� �����
//---------------------------------------------------------------------------
int TLevelSettings::operator != (const TLevelSettings &right) const
{
  if ( (Number != right.Number) || (Name != right.Name) ||
       (CriterionFrom != right.CriterionFrom) ||
       (CriterionTill != right.CriterionTill) ||
       (_fAlpha != right._fAlpha) ||
       (_fGamma != right._fGamma) ||
       (_fSigma != right._fSigma) ||
       (_fBeta != right._fBeta) )
    return 1;
  else
    return 0;
}
//---------------------------------------------------------------------------
// �������� �����
//---------------------------------------------------------------------------
int TLevelSettings::operator == (const TLevelSettings &right) const
{
  if ( (Number != right.Number) && (Name != right.Name) &&
       (CriterionFrom != right.CriterionFrom) &&
       (CriterionTill != right.CriterionTill) &&
       (_fAlpha != right._fAlpha) &&
       (_fGamma != right._fGamma) &&
       (_fSigma != right._fSigma) &&
       (_fBeta != right._fBeta) )
    return 0;
  else
    return 1;
}
//---------------------------------------------------------------------------
// �������� ������������
//---------------------------------------------------------------------------
TLevelSettings & TLevelSettings::operator = (const TLevelSettings &right)
{
  Number = right.Number;
  Name = right.Name;
  CriterionFrom = right.CriterionFrom;
  CriterionTill = right.CriterionTill;
  _fAlpha = right._fAlpha;
  _fGamma = right._fGamma;
  _fSigma = right._fSigma;
  _fBeta = right._fBeta;
  return *this;
}
//---------------------------------------------------------------------------
