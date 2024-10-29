#include "../include/csv_reader.h"

void csv_reader(Table *table, char *db_name) {
    char filepath[1024];
    snprintf(filepath, sizeof(filepath), "%s/%s/1.csv", db_name, table->table_name);  // Формируем путь к файлу

    FILE *file = fopen(filepath, "r");  // Открываем файл для чтения

    char line[1024];

    fgets(line, sizeof(line), file);  // Пропускаем первую строку с именами колонок

    while (fgets(line, sizeof(line), file)) {  // Читаем строки из файла

        line[strcspn(line, "\n")] = '\0';  // Убираем символ новой строки

        char *elements[table->column_count];
        char *token = strtok(line, ",");  // Разбиваем строку на элементы по запятым
        int idx = 0;

        while (token != NULL && idx < table->column_count) {
            elements[idx] = token;

            token = strtok(NULL, ",");
            idx++;
        }

        add_data_to_table(table, elements);  // Добавляем данные в таблицу
    }

    fclose(file);  // Закрываем файл
}