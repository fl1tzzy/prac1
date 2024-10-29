#include "../include/database.h"

// Функция для создания базы данных
DataBase* create_database(const char *database_name, DataBase *db) {
    db->name = strdup(database_name);  // Копируем имя базы данных
    db->table_count = 0;  // Инициализируем количество таблиц
    db->tables = NULL;  // Инициализируем указатель на таблицы
    db->tuples_limit = 0;  // Инициализируем ограничение на количество кортежей

    return db;
}

// Функция для добавления таблицы в базу данных
void add_table_to_database(DataBase *db, const char *table_name) {
    db->table_count++;  // Увеличиваем количество таблиц
    db->tables = realloc(db->tables, db->table_count * sizeof(Table));  // Перераспределяем память для таблиц
    db->tables[db->table_count - 1].table_name = strdup(table_name);  // Копируем имя таблицы
    db->tables[db->table_count - 1].columns = NULL;  // Инициализируем указатель на колонки
    db->tables[db->table_count - 1].column_count = 0;  // Инициализируем количество колонок
}

// Функция для добавления колонки в таблицу
void add_column_to_table(Table *table, const char *column_name) {
    table->column_count++;  // Увеличиваем количество колонок
    table->columns = realloc(table->columns, table->column_count * sizeof(Column));  // Перераспределяем память для колонок
    table->columns[table->column_count - 1].name = strdup(column_name);  // Копируем имя колонки
    table->columns[table->column_count - 1].data = NULL;  // Инициализируем указатель на данные
}

// Функция для добавления данных в таблицу
void add_data_to_table(Table *table, char **data) {
    for (size_t i = 0; i < table->column_count; i++) {
        DataNode *new_node = malloc(sizeof(DataNode));  // Выделяем память для нового узла данных

        new_node->data = strdup(data[i]);  // Копируем данные в узел
        new_node->next = NULL;  // Инициализируем указатель на следующий узел

        if (table->columns[i].data == NULL) {
            table->columns[i].data = new_node;  // Если данных еще нет, устанавливаем новый узел как первый
        } 
        
        else {
            DataNode *current = table->columns[i].data;
            while (current->next != NULL) {
                current = current->next;  // Ищем последний узел в списке
            }
            current->next = new_node;  // Добавляем новый узел в конец списка
        }
    }

    table->row_count++;  // Увеличиваем количество строк в таблице
}

// Функция для получения таблицы по имени
Table* get_table(DataBase *db, const char *table_name) {
    for (size_t i = 0; i < db->table_count; i++) {
        if (strcmp(db->tables[i].table_name, table_name) == 0) {
            return &db->tables[i];  // Возвращаем указатель на таблицу, если найдена
        }
    }

    return NULL;  // Возвращаем NULL, если таблица не найдена
}

// Функция для получения индекса колонки по имени
int get_column_index(Table *table, const char *column_name) {
    for (size_t i = 0; i < table->column_count; i++) {
        if (strcmp(table->columns[i].name, column_name) == 0) {
            return i;  // Возвращаем индекс колонки, если найдена
        }
    }
    return -1;  // Возвращаем -1, если колонка не найдена
}

// Функция для удаления строки из таблицы
void delete_row(Table *table, size_t row_index) {
    for (size_t j = 0; j < table->column_count; j++) {
        DataNode *prev = NULL;
        DataNode *current = table->columns[j].data;
        
        for (size_t k = 0; k < row_index && current != NULL; k++) {
            prev = current;
            current = current->next;  // Ищем узел, который нужно удалить
        }

        if (prev != NULL) {
            prev->next = current->next;  // Обновляем указатель предыдущего узла
        } else {
            table->columns[j].data = current->next;  // Если удаляем первый узел, обновляем указатель на первый узел
        }

        free(current->data);  // Освобождаем память, занятую данными
        free(current);  // Освобождаем память, занятую узлом
    }

    table->row_count--;  // Уменьшаем количество строк в таблице
}

// Функция для освобождения памяти, занятой данными в колонке
void free_column_data(Column *column) {
    DataNode *current = column->data;
    while (current != NULL) {
        DataNode *next = current->next;  // Сохраняем указатель на следующий узел
        free(current->data);  // Освобождаем память, занятую данными
        free(current);  // Освобождаем память, занятую узлом
        current = next;  // Переходим к следующему узлу
    }
    column->data = NULL;  // Обнуляем указатель на данные в колонке
}

// Функция для освобождения памяти, занятой данными в таблице
void free_table_data(Table *table) {
    for (size_t i = 0; i < table->column_count; i++) {
        free_column_data(&table->columns[i]);  // Освобождаем данные в каждой колонке
    }
    table->row_count = 0;  // Обнуляем количество строк в таблице
}