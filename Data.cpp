//---------------------------------------------------------------------------
#include <vcl.h>
#pragma hdrstop
#include "Data.h"
//---------------------------------------------------------------------------
#pragma package(smart_init)

//---------------------------------------------------------------------------
// Конструктор
//---------------------------------------------------------------------------
Data::Data()
{
 _bStatus = false;
 _iColumns = 0;
 _iRecords = 0;
}
//---------------------------------------------------------------------------
// Конструктор с данными
//---------------------------------------------------------------------------
Data::Data(const Data *data)
{
  _File = data->getFileName();
  _iColumns = data->getCountColumn();
  _iRecords = data->getCountRecord();

  // Скопируем название колонок
  for (long rec = 0; rec < _iColumns; ++rec) {
    vColumnName.push_back(data->getColumnName(rec));
  }

  // Скопируем данные
  for (long rec = 0; rec < _iRecords; ++rec) {
    vx.erase(vx.begin(), vx.end());
		vx.swap(tmp_vx);
    for (long col = 0; col < _iColumns; ++col) {
      vx.push_back(data->getData(col, rec));
    }
    vData.push_back(vx);
  }

  _bStatus = data->getStatus();

  // Скопируем статистику
  for (long col = 0; col < _iColumns; ++col) {
    rStat.Min = data->getMin(col);
    rStat.Max = data->getMax(col);
    rStat.MinBiggerZero = data->getMinBiggerZero(col);
    vStat.push_back(rStat);
  }

}
//---------------------------------------------------------------------------
// Перезагрузка оператора присваивания
//---------------------------------------------------------------------------
const Data &Data::operator=(const Data &right)
{
  // Проверка самоприсваевания
  if (&right != this) {
    _File = right._File;
    _iColumns = right._iColumns;
    _iRecords = right._iRecords;
    vColumnName = right.vColumnName;
    vData = right.vData;
    _bStatus = right._bStatus;
    rStat = right.rStat;
    vStat = right.vStat;
  }
}
//---------------------------------------------------------------------------
// Инициализация данных, заполнение массивов
//---------------------------------------------------------------------------
bool Data::Create(String File)
{
	char buff[1000];
  _File = File;
  String s;
	try
  {
  	fileOut.open(_File.c_str());
  	if (!fileOut)
    {
   		ShowMessage("Ошибка! Не удалось открыть файл " + _File + "!");
  	}
		else
    {
   		// Подсчёт колличества записей
   		_iRecords = 0;
   		while (!fileOut.eof())
      {
    		fileOut.get(buff,sizeof(buff),'\n');
    		fileOut.get();
    		++_iRecords;
   		}
   		_iRecords = _iRecords - 2; // Удаление строк не относящихся к записям
			fileOut.close();
			fileOut.open(_File.c_str());

			// Installing count columns
			fileOut.getline(buff,sizeof(buff));
			s = ReadStr(buff,true);
			_iColumns = s.ToInt();

			if (_iColumns > 0)
			{
				// Installing name columns
				fileOut.get(buff,sizeof(buff),'\n');
				fileOut.get();

				bool bNew = true;
				// Очистка
				vColumnName.erase(vColumnName.begin(), vColumnName.end());
				vColumnName.swap(tmp_ColumnName);

				// Заполнение
				for (long i = 0; i < _iColumns; ++i)
				{
					vColumnName.push_back(ReadStr(buff,bNew));
					if (bNew)
          	bNew = false;
        }

				// Удаление данных
				vx.erase(vx.begin(), vx.end());
				vx.swap(tmp_vx);
				vData.erase(vData.begin(), vData.end());
				vData.swap(tmp_Data);

				// Резервирование памяти под данные
				vx.reserve(_iColumns);
				vData.reserve(_iRecords);

				// Заполнение
				float ft;
				while (!fileOut.eof())
				{
					fileOut.get(buff,sizeof(buff),'\n');
					fileOut.get();
					if (buff[0] != '\0')
					{
						bNew = true;
						vx.erase(vx.begin(), vx.end());
						for (long x = 0; x < _iColumns; ++x)
						{
							s = ReadStr(buff,bNew);
							ft = s.ToDouble();
							vx.push_back(ft);
							if (bNew)
              	bNew = false;
						}
						vData.push_back(vx);
					}
				}
			}
			else
    	{
				ShowMessage("Количество столбцов в файле должно быть больше 0!");
				_bStatus = false;
			}

			fileOut.close();
			_bStatus = true;
		}
	}
	catch (Exception &exception)
	{
		fileOut.close();
		_bStatus = false;
		ShowMessage("Ошибка. Не верный формат файла.");
	}

  // Вычисление Статистики
	Statistics();
	return _bStatus;
}
//---------------------------------------------------------------------------
// Получить наименование файла
//---------------------------------------------------------------------------
String Data::getFileName() const
{
  return _File;
}
//---------------------------------------------------------------------------
// Чтение еденицы информации
//---------------------------------------------------------------------------
String Data::ReadStr(const char *ss, bool bNewStringsLine)
{
  static int iPosition;
  String sResult = "";
  if (bNewStringsLine)
   iPosition = 0;
  bool bStringStart = false;

  int slength = strlen(ss);
  while (slength > iPosition)
  {
    if ((ss[iPosition] != '\t') && (ss[iPosition] != ' ') &&
        (ss[iPosition] != '\n'))
    {
      bStringStart =  true;
      sResult += ss[iPosition];
    }
    else if (bStringStart)
    {
       return sResult;
    }
    ++iPosition;
  }

  return sResult;
}
//---------------------------------------------------------------------------
// Состояние подготовки данных
//---------------------------------------------------------------------------
bool Data::getStatus() const
{
 return _bStatus;
}
//---------------------------------------------------------------------------
// Получить ячейку данных
//---------------------------------------------------------------------------
float Data::getData(const long col, const long rec) const
{
   return vData[rec][col];
}
//---------------------------------------------------------------------------
// Получить кол-во колонок
//---------------------------------------------------------------------------
long Data::getCountColumn() const
{
  return _iColumns;
}
//---------------------------------------------------------------------------
// Получить кол-во строк
//---------------------------------------------------------------------------
long Data::getCountRecord() const
{
  return  vData.size();
}
//---------------------------------------------------------------------------
// Получить название колонки
//---------------------------------------------------------------------------
String Data::getColumnName(long iColumn) const
{
  return vColumnName[iColumn];
}
//---------------------------------------------------------------------------
// Получить номер колонки по названию поля
//---------------------------------------------------------------------------
long Data::getNumberForColumnName(String name) const
{
	// Регистр не должен влиять
	name = UpperCase(name);
  for (unsigned int i = 0; i < vColumnName.size(); ++i)
  {
		if (UpperCase(vColumnName[i]) == name)
    	return i;
	}

  return -1;
}
//---------------------------------------------------------------------------
// Вычисление статистики
//---------------------------------------------------------------------------
void Data::Statistics()
{
	// Удаление выделенной памяти
	vStat.erase(vStat.begin(), vStat.end());
	vStat.swap(tmp_Stat);

  // Инициализация
  for (long i = 0; i < _iColumns; ++i)
  {
    rStat.Min = vData[0][i];
    rStat.Max = vData[0][i];
    rStat.MinBiggerZero = 0;
    vStat.push_back(rStat);
  }

  // Вычисление статистики
  for (long x = 0; x < _iColumns; ++x)
  {
    for (unsigned long y = 0; y < vData.size(); ++y)
    {
      if (vData[y][x] < vStat[x].Min)
				vStat[x].Min = vData[y][x];
      if (vData[y][x] > vStat[x].Max)
				vStat[x].Max = vData[y][x];
      if ((vData[y][x] > 0) && (vData[y][x] < vStat[x].MinBiggerZero))
				vStat[x].MinBiggerZero = vData[y][x];
    }
  }

  // Вычисли минимальные значения больше 0
  for (long i = 0; i < _iColumns; ++i)
  {
    if (vStat[i].Max < 0)
    {
     vStat[i].MinBiggerZero = 0.1;
    }
    else
    {
     if (vStat[i].Min > 0)
       vStat[i].MinBiggerZero = vStat[i].Min;
     else
       vStat[i].MinBiggerZero = vStat[i].Max;
    }
  }

  for (long x = 0; x < _iColumns; ++x)
  {
    for (unsigned long y = 0; y < vData.size(); ++y){
    	if ((vData[y][x] > 0) && (vData[y][x] < vStat[x].MinBiggerZero))
      	vStat[x].MinBiggerZero = vData[y][x];
    }
  }
}
//---------------------------------------------------------------------------
// Получить Min по номеру поля
//---------------------------------------------------------------------------
float Data::getMin(long iColumn) const
{
   return vStat[iColumn].Min;
}
//---------------------------------------------------------------------------
// Получить Max по номеру поля
//---------------------------------------------------------------------------
float Data::getMax(long iColumn) const
{
   return vStat[iColumn].Max;
}
//---------------------------------------------------------------------------
// Получить Min, которое больше 0
//---------------------------------------------------------------------------
float Data::getMinBiggerZero(long iColumn) const
{
   return vStat[iColumn].MinBiggerZero;
}
//---------------------------------------------------------------------------
// Ввод в сетку коэффициент анизотропии
//---------------------------------------------------------------------------
void Data::setAnisotropyFactor(long x, long y, long z,
  objData anisotropyFactors)
{

  objData currobjData, resultobjData;

  for (long rec = _iRecords; rec < _iRecords; ++rec) {
    // x
    currobjData.x = vData[rec][x];
    currobjData.y = vData[rec][y];
    currobjData.z = vData[rec][z];

    resultobjData = currobjData * anisotropyFactors;

    vData[rec][x] = resultobjData.x;
    vData[rec][y] = resultobjData.y;
    vData[rec][z] = resultobjData.z;
  }
}
//---------------------------------------------------------------------------
// Деструктор
//---------------------------------------------------------------------------
Data::~Data(void)
{

}
