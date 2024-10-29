#ifndef STATEMENTS_H  
#define STATEMENTS_H    

#include "input_buffer.h"
#include "database.h"
#include "insert.h"
#include "select.h"
#include "delete.h"

// Перечисление для результата подготовки оператора
typedef enum {
    PREPARE_SUCCESS,               // Успешное выполнение подготовки
    PREPARE_UNRECOGNIZED_STATEMENT  // Нераспознанный оператор
} PrepareResult;

// Перечисление для типа оператора
typedef enum { STATEMENT_INSERT, STATEMENT_SELECT, STATEMENT_DELETE } StatementType;

// Структура для представления оператора
typedef struct {
    StatementType type;            // Тип оператора
} Statement;

// Функция для подготовки оператора
PrepareResult prepare_statement(InputBuffer *input_buffer, Statement *statement);

// Функция для выполнения оператора
void execute_statement(DataBase *db, Statement *statement, InputBuffer *input_buffer);

#endif 