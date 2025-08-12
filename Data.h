//---------------------------------------------------------------------------
#ifndef DataH
#define DataH

#include <fstream.h>
#include <vector>
#include "Structs.h"

class Data
{
  private:
    // Название файла
    String _File;
    // Поток для работы с файлом
    ifstream fileOut;
    // Кол-во полей
    long _iColumns;
    // Кол-во записей
    long _iRecords;
    // Название полей
    std::vector<String> vColumnName;
    std::vector<String> tmp_ColumnName;
    // Данные
    std::vector <float> vx; // Количество записей
    std::vector <std::vector<float> > vData;
    // Вектора для чистки памяти
    std::vector <float> tmp_vx;
    std::vector <std::vector<float> > tmp_Data;
    // Статус
    bool _bStatus;
    // Чтение единицы информации
    String ReadStr(const char *ss, bool bNewStringsLine);
    // Структура для статистики
    struct Stat {
     float Min;
     float Max;
     float MinBiggerZero;
    } rStat;
    // Массив структур для статистики
    std::vector <Stat> vStat;
    std::vector <Stat> tmp_Stat;

    // Вычисление статистики
    void Statistics();
  public:
    // Конструктор
    Data();
    // Конструктор с данными
    Data(const Data *data);
    // Перезагрузка оператора присваивания
    const Data &operator=(const Data &right);
    // Деструктор
    ~Data(void);
    // Ввод в сетку коэффициент анизотропии
    void setAnisotropyFactor(long x, long y, long z, objData anisotropyFactors);
    // Инициализация данных, заполнение массивов, создание статистики
    bool Create(String File);
    // Получить наименование файла
    String getFileName() const;
    // Производилось ли чтение данных из файла
    bool getStatus() const;
    // Получить данные
    float getData(const long col, const long rec) const;
    // Кол-во полей
    long getCountColumn() const;
    // Кол-во записей
    long getCountRecord() const;
    // Получить название поля
    String getColumnName(long iColumn) const;
    // Получить номер колонки по названию поля, -1 в случае неверного имени столбца
    long getNumberForColumnName(String name) const;
    // Получить Min по номеру поля
    float getMin(long iColumn) const;
    // Получить Max по номеру поля
    float getMax(long iColumn) const;
    // Получить Min, которое больше 0
    float getMinBiggerZero(long iColumn) const;
};

//---------------------------------------------------------------------------
#endif
