#ifndef StructsH
#define StructsH

// Поле с фоновым значением
struct Criterion
{
  String Name;
  float TildeT;
  float W;
};

// Структура необходимая для вычисления весовой аппроксимации
struct ParamCalcWA
{
  float Alpha;
  float Beta;
  float Gamma;
  float Sigma;
  bool Standart;
  String x;
  String y;
  String z;

  const ParamCalcWA &operator = (const ParamCalcWA &right)
  {
     Alpha = right.Alpha;
     Beta = right.Beta;
     Gamma = right.Gamma;
     Standart = right.Standart;
     x = right.x;
     y = right.y;
     z = right.z;

     return *this;
  }
};

// Минимум и максимум
struct MinMax{
  float min;
  float max;
};

// Структура для координат
struct PositionData {
   float x;
   float y;
   float z;
   int operator != (const PositionData &right) const
   {
     if ((x != right.x)||(y != right.y)||(z != right.z))
       return 1;
     else
       return 0;
   }
   int operator == (const PositionData &right) const
   {
     if ((x == right.x)&&(y == right.y)&&(z == right.z))
       return 0;
     else
       return 1;
   }
   const PositionData &operator = (const PositionData &right)
   {
     x = right.x;
     y = right.y;
     z = right.z;
     return *this;
   }
};

// От и До
struct FromTill {
  float From;
  float Till;
   int operator != (const FromTill &right) const
   {
     if ((From != right.From)||(Till != right.Till))
       return 1;
     else
       return 0;
   }
   int operator == (const FromTill &right) const
   {
     if ((From == right.From)&&(Till == right.Till))
       return 0;
     else
       return 1;
   }
   const FromTill &operator = (const FromTill &right)
   {
     From = right.From;
     Till = right.Till;
     return *this;
   }
};

// Структура для одного объекта данных
struct objData {
  float x;
  float y;
  float z;
  // Перегрузка оператора присваевания
  const objData &operator = (const objData &right)
  {
     x = right.x;
     y = right.y;
     z = right.z;

     return *this;
  }
  // Перегрузка оператора умножения
  const objData &operator * (const objData &right)
  {
     x = x * right.x;
     y = y * right.y;
     z = z * right.z;

     return *this;
  }
};

// Структура для одного объекта сетки
struct Column {
  long n;
  bool bLog10;
  Criterion _Criterion;
};


#endif
