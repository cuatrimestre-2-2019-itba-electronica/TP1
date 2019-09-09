//
// Created by mlste on 9/9/2019.
//

#ifndef DATABASE_H
#define DATABASE_H

#include <stdbool.h>
#include <stdint-gcc.h>


typedef struct DATABASE_ENTRY_VALUE{
    uint8_t * ID_buffer;
    uint8_t ID_buffer_len;
    uint8_t * PIN_buffer;
    uint8_t PIN_buffer_len;
}DATABASE_ENTRY_VALUE;

typedef struct DATABASE_ENTRY {
    uint8_t key;
    DATABASE_ENTRY_VALUE value;
} DATABASE_ENTRY;

//false si out of bounds
bool database_set_cursor_pos(unsigned int cursor_pos);

//Si esta vacio, devuelve -1.
//Si hay elementos, devuelve la posicion del cursor
int database_get_cursor_pos();

//Si esta vacio, devuelve NULL.
//Si hay elementos, devuelve el elemento al cual apunta el cursor
//No entrega ownership. Si se modifica el contenido, se modifica
//en la base de datos tambien
const DATABASE_ENTRY * database_get_entry_at_cursor();

//Si esta vacio o si la posicion excede a la longitud, devuelve
//NULL.
//Si hay elementos, devuelve el elemento al cual apunta el cursor
//No entrega ownership. Si se modifica el contenido, se modifica
//en la base de datos tambien
const DATABASE_ENTRY * database_get_entry_at(unsigned int pos);

//bool database_delete_entry_at_cursor();

//bool database_delete_entry_at(unsigned int pos);

//false si out of bounds
//toma ownership de la memoria en entry
bool database_set_entry_at_cursor(DATABASE_ENTRY * entry);

//false si out of bounds
//toma ownership de la memoria en entry
bool database_set_entry_at(DATABASE_ENTRY * entry, unsigned int pos);

//no modifica el cursor
void database_append_entry(DATABASE_ENTRY * entry);

unsigned int database_get_size(DATABASE_ENTRY * entry);

unsigned int database_empty();

#endif //DATABASE_H
