#include "../include/input_buffer.h"
#include "../include/meta_commands.h"
#include "../include/statements.h"
#include "../include/database.h"
#include "../include/json_parser.h"
#include "../include/json_reader.h"
#include "../include/build_database_file_system.h"

#include <stdbool.h>

int main(int argc, char* argv[]) {
    DataBase *database = parse_json(load_json_data("scheme.json"));  // Парсим JSON-файл и создаем базу данных
    build_database_file_system(database);  // Создаем файловую систему для базы данных

    InputBuffer *input_buffer = new_input_buffer();  // Создаем буфер ввода
    while (true) {
        print_prompt(database->name);  // Выводим приглашение ввода
        read_input(input_buffer);  // Читаем ввод пользователя

        if (input_buffer->buffer[0] == '.') {
            switch (do_meta_command(input_buffer)) {
                case (META_COMMAND_SUCCESS):
                    continue;
                case (META_COMMAND_UNRECOGNIZED_COMMAND):
                    printf("Unrecognized command '%s'\n", input_buffer->buffer);
                    continue;
            }
        }

        Statement statement;
        switch (prepare_statement(input_buffer, &statement)) {
            case (PREPARE_SUCCESS):
                break;
            case (PREPARE_UNRECOGNIZED_STATEMENT):
                printf("Unrecognized keyword at start of '%s'.\n", input_buffer->buffer);
                continue;
        }

        execute_statement(database, &statement, input_buffer);  // Выполняем оператор
        printf("Executed.\n");
    }

    close_input_buffer(input_buffer);  // Закрываем буфер ввода
}