//
// Created by mlste on 9/9/2019.
//

#include "database.h"

#include <stdint.h>
#include <stdlib.h>

#define DATABASE_MAX_ENTRIES 20

static DATABASE_ENTRY * database[DATABASE_MAX_ENTRIES];
static DATABASE_ENTRY * cursor = NULL; //en desuso. Para ampliar horizontes
static int cursor_pos = -1;
static unsigned int len = 0;


static void database_entry__destroy(DATABASE_ENTRY * entry);

//false si out of bounds
bool database_set_cursor_pos(unsigned int _cursor_pos){
    if(cursor_pos >= len){ return  false; }
    cursor_pos = _cursor_pos;
}
int database_get_cursor_pos(){
    return cursor_pos;
}

const DATABASE_ENTRY * database_get_entry_at_cursor(){
    if(len){ return database[cursor_pos];}
    return NULL;
}

const DATABASE_ENTRY * database_get_entry_at(unsigned int pos){
    if(pos >= len){ return NULL;}
    return database[pos];
}

//bool database_delete_entry_at_cursor();

//bool database_delete_entry_at(unsigned int pos);

//false si out of bounds

bool database_set_entry_at_cursor(DATABASE_ENTRY * entry){
    if(len){
        database[cursor_pos] = entry;
        return true;
    }
    return false;
}
//false si out of bounds

bool database_set_entry_at(DATABASE_ENTRY * entry, unsigned int pos){
    if(pos >= len){ return false; }
    database[pos] = entry;
    return true;
}
//no modifica el cursor
void database_append_entry(DATABASE_ENTRY * entry){
    database[len] = entry;
}

unsigned int database_get_size(DATABASE_ENTRY * entry){
    return len;
}

unsigned int database_empty(){
    for (int i = 0; i < len; ++i) {
        database_entry__delete(database[i]);
    }
}

static void database_entry__destroy(DATABASE_ENTRY * entry){
    if(entry == NULL){ return; }
    if(entry->value.ID_buffer  != NULL){ free(entry->value.ID_buffer); }
    if(entry->value.PIN_buffer != NULL){ free(entry->value.PIN_buffer); }
    free(entry);
}
