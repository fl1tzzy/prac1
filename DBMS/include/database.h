#ifndef DATABASE_H  
#define DATABASE_H    

#include <stdio.h>
#include <stdlib.h>
#include <string.h>

// Структура для узла данных в связанном списке
typedef struct DataNode {
    char *data;             // Указатель на строку данных
    struct DataNode *next;  // Указатель на следующий узел в списке
} DataNode;

// Структура для представления колонки в таблице
typedef struct {
    char *name;             // Имя колонки
    DataNode *data;         // Указатель на первый узел данных в колонке
} Column;

// Структура для представления таблицы
typedef struct {
    char *table_name;       // Имя таблицы
    Column *columns;        // Указатель на массив колонок
    size_t column_count;    // Количество колонок в таблице
    size_t row_count;       // Количество строк в таблице
} Table;

// Структура для представления базы данных
typedef struct {
    char *name;             // Имя базы данных
    int tuples_limit;       // Ограничение на количество кортежей (строк)
    Table *tables;          // Указатель на массив таблиц
    size_t table_count;     // Количество таблиц в базе данных
} DataBase;

// Функция для создания базы данных
DataBase* create_database(const char *database_name, DataBase *db);

// Функция для добавления таблицы в базу данных
void add_table_to_database(DataBase *db, const char *table_name);

// Функция для добавления колонки в таблицу
void add_column_to_table(Table *table, const char *column_name);

// Функция для добавления данных в таблицу
void add_data_to_table(Table *table, char **data);

// Функция для получения таблицы по имени
Table* get_table(DataBase *db, const char *table_name);

// Функция для получения индекса колонки по имени
int get_column_index(Table *table, const char *column_name);

// Функция для удаления строки из таблицы
void delete_row(Table *table, size_t row_index);

// Функция для освобождения памяти, занятой базой данных
void free_database(DataBase *schema);

// Функция для освобождения памяти, занятой данными в колонке
void free_column_data(Column *column);

// Функция для освобождения памяти, занятой данными в таблице
void free_table_data(Table *table);

#endif // DATABASE_H