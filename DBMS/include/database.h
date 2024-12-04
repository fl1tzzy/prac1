#ifndef DATABASE_H 
#define DATABASE_H    

#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#include "list.h"

typedef struct DataNode {
    char *data;
    struct DataNode *next;
} DataNode;

typedef struct {
    char *name;
    DataNode *data;
} Column;

typedef struct {
    char *table_name;
    Column *columns;
    size_t column_count;
    size_t row_count; 
} Table;

typedef struct {
    char *name;
    int tuples_limit;
    Table *tables;
    size_t table_count;
} DataBase;

DataBase* create_database(const char *database_name, DataBase *db);

void add_table_to_database(DataBase *db, const char *table_name);
void add_column_to_table(Table *table, const char *column_name);
void add_data_to_table(Table *table, List *list);

Table* get_table(DataBase *db, const char *table_name);
int get_column_index(Table *table, const char *column_name);
List* get_row_in_table(Table *table, size_t row_index);

void delete_row(Table *table, size_t row_index);

void free_database(DataBase *schema);
void free_column_data(Column *column);
void free_table_data(Table *table);

#endif