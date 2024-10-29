#include "../include/input_buffer.h"

#include <stdio.h>
#include <stdlib.h>

// Функция для создания нового буфера ввода
InputBuffer* new_input_buffer() {
    InputBuffer* input_buffer = malloc(sizeof(InputBuffer));
    input_buffer->buffer = NULL;
    input_buffer->buffer_length = 0;
    input_buffer->input_length = 0;

    return input_buffer;
}

// Функция для вывода приглашения ввода
void print_prompt(char *database_name) { printf("%s > ", database_name); }

// Функция для чтения ввода пользователя
void read_input(InputBuffer* input_buffer) {
    size_t bytes_read = getline(&(input_buffer->buffer), &(input_buffer->buffer_length), stdin);

    if (bytes_read <= 0) {
        printf("Error reading input\n");
        exit(EXIT_FAILURE);
    }

    input_buffer->input_length = bytes_read - 1;
    input_buffer->buffer[bytes_read - 1] = 0;
}

// Функция для закрытия буфера ввода
void close_input_buffer(InputBuffer* input_buffer) {
    free(input_buffer->buffer);
    free(input_buffer);
}