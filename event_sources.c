//
// Created by mlste on 9/4/2019.
//

#include <stdint-gcc.h>
#include <stdbool.h>
#include <stdlib.h>
#include "event_sources.h"

#include "config.h"
#include "cqp.h"


// todo: #dato Probablemente me convenga incorporar el caracter espacio

union EVENTO_SOURCE_DATA;
typedef union EVENTO_SOURCE_DATA EVENTO_SOURCE_DATA;

typedef evento_t(*get_evento_fun_p)(EVENTO_SOURCE_DATA * data, suceso_t suceso);

/********************************************************
 * ******************************************************
 * DATOS MIEMBROS
 * ******************************************************
 * ******************************************************/

/* Posibles eventos que devuelve:
    - EVENTO_FAILED_NUM_INPUT_TYPE
    - EVENTO_CORRECT_NUM_INPUT_TYPE */
/****************
 *   GET_NUM_BUFF
 * *************/

typedef struct EVENTO_SOURCE_GET_NUM_BUFF_DATA
{
//    uint8_t num_buff[GET_ID_MAX_LENGTH];
    uint8_t * ID_buffer;
    uint8_t cursor;
    bool changing_num;  //true si se esta cambiando el valor de un digito y todavia no se confirmo con un tap

    uint8_t max_length;
    uint8_t min_length; //todo: dejar de ignorar min_length
    uint8_t cur_length; //longitud actual del arreglo

    get_num_buff_cb is_num_buff_correct;
    get_num_buff_cb show_num_buff;

} EVENTO_SOURCE_GET_NUM_BUFF_DATA;

evento_t
get_num_buff_fun(EVENTO_SOURCE_GET_NUM_BUFF_DATA * data, suceso_t suceso)
{
    evento_t ev;
    ev.type = EVENTO_N;

    // si es un numero
    if(suceso <= SUC_NUM_9 && data->cursor < data->max_length)
    {
        data->ID_buffer[data->cursor] = (uint8_t)suceso;
        data->changing_num = true;
        if(data->cursor >= data->cur_length) { data->cur_length = data->cursor + 1; }
//        return ev;
    } else {
        // si no es un numero:
        //todo: implementar borrar el ultimo caracter.
        switch(suceso)
        {
            case SUC_TAP_DETECTED:
                if(!(data->changing_num)) { break; }

                if(data->cursor < data->max_length - 1)
                {
                    //si no es la ultima posicion
                    (data->cursor)++;
                    break;
                }

                //si estoy en la ultima posicion
                if(data->is_num_buff_correct(data->ID_buffer,data->cur_length))
                {
                    //Si el numero es valido
                    if((ev.correct_num_input.num_buff = malloc(data->cur_length)) == NULL) {
                        ev.type = EVENTO_N;
                        break;
                    };
                    ev.type = EVENTO_CORRECT_NUM_INPUT_TYPE;
                    ev.correct_num_input.num_buff_len = data->cur_length;
                    for (int i = 0; i < data->max_length; ++i) {
                        ev.correct_num_input.num_buff[i] = data->ID_buffer[i];
                    }
                    break;
                }
                //Si el numero no es valido
                if((ev.failed_num_input.num_buff = malloc(data->cur_length)) == NULL) {
                    ev.type = EVENTO_N;
                    break;
                };
                ev.type = EVENTO_FAILED_NUM_INPUT_TYPE;
                ev.failed_num_input.num_buff_len = data->cur_length;
                for (int i = 0; i < data->max_length; ++i) {
                    ev.failed_num_input.num_buff[i] = data->ID_buffer[i];
                }
                break;
            case SUC_MOVE_CURSOR_LEFT:
                //decremento sin underflow
                if(data->cursor) { (data->cursor)--; }
                break;
            case SUC_MOVE_CURSOR_RIGHT:
                //incremento sin overflow
                if(data->cursor < data->max_length - 1){ data->cursor++; }
                break;
            default:
                break;
        }
        data->changing_num = false;
    }

    if(data->show_num_buff != NULL){ data->show_num_buff(data->ID_buffer, data->cur_length); }
    return ev;
}

typedef struct EVENTO_SOURCE_GET_NUM_BUFF
{
    EVENTO_SOURCE_TYPE type;
    get_evento_fun_p fun;
    EVENTO_SOURCE_GET_NUM_BUFF_DATA data;
} EVENTO_SOURCE_GET_NUM_BUFF;


/* Posibles eventos que devuelve:
    - EVENTO_TIMEOUT_TYPE */
/****************
 *   GET_TIME_OUT
 * *************/

typedef struct EVENTO_SOURCE_GET_TIME_OUT_DATA
{
    unsigned int count;
    unsigned int timeout_count;
} EVENTO_SOURCE_GET_TIME_OUT_DATA;

evento_t get_time_out_fun(EVENTO_SOURCE_GET_TIME_OUT_DATA * data, suceso_t suceso)
{
    evento_t ev;
    ++(data->count);
    if(data->count >= data->timeout_count){ //Despues de X tiempo de inactividad
        ev.type = EVENTO_TIMEOUT_TYPE;
    } else {
        ev.type = EVENTO_N;
    }
    return ev;
}

typedef struct EVENTO_SOURCE_GET_TIME_OUT
{
    EVENTO_SOURCE_TYPE type;
    get_evento_fun_p fun;
    EVENTO_SOURCE_GET_TIME_OUT_DATA data;
} EVENTO_SOURCE_GET_TIME_OUT;


/* Posibles eventos que devuelve:
    - EVENTO_CANCEL_TYPE */
/****************
 *   GET_CANCEL_DATA
 * *************/

typedef struct EVENTO_SOURCE_GET_CANCEL_DATA
{
    unsigned int taps;
} EVENTO_SOURCE_GET_CANCEL_DATA;

evento_t get_cancel_fun(EVENTO_SOURCE_GET_CANCEL_DATA * data, suceso_t suceso)
{
    // Se genera evento CANCEL despues de 3 taps
    evento_t ev;
    ev.type = EVENTO_N;

    if(suceso != SUC_TAP_DETECTED)
    {
        data->taps = 0;
    }
    else if(++(data->taps) == TAPS_TO_CANCEL) {
        data->taps = 0;
        ev.type = EVENTO_CANCEL_TYPE;
    }
    return ev;
}

typedef struct EVENTO_SOURCE_GET_CANCEL
{
    EVENTO_SOURCE_TYPE type;
    get_evento_fun_p fun;
    EVENTO_SOURCE_GET_CANCEL_DATA data;
} EVENTO_SOURCE_GET_CANCEL;


/****************
 *   EVENTO_SOURCE
 * *************/

union EVENTO_SOURCE_DATA
{
    EVENTO_SOURCE_GET_NUM_BUFF_DATA get_id_data;
    EVENTO_SOURCE_GET_TIME_OUT_DATA get_time_out_data;
    EVENTO_SOURCE_GET_CANCEL_DATA get_cancel_data;
};

//para acceder a los campos fun y data sin analizar type:
typedef struct EVENTO_SOURCE_ANY
{
    EVENTO_SOURCE_TYPE type;
    get_evento_fun_p fun;
    EVENTO_SOURCE_DATA data;
} EVENTO_SOURCE_ANY;


union EVENTO_SOURCE
{
    EVENTO_SOURCE_TYPE type;    //para saber el tipo rapido
    EVENTO_SOURCE_ANY any;
    EVENTO_SOURCE_GET_NUM_BUFF get_id;
    EVENTO_SOURCE_GET_TIME_OUT get_time_out;
    EVENTO_SOURCE_GET_CANCEL get_cancel;
};




/********************************************************
 * ******************************************************
 * FUNCIONES MIEMBRO
 * ******************************************************
 * ******************************************************/


// Constructor (without allocation for evento_source)
static void evento_source__init(EVENTO_SOURCE* self, EVENTO_SOURCE_TYPE type, void * _params)
{
    self->type = type;
    switch (type)
    {
        case EVENTO_SOURCE_GET_NUM_BUFF_TYPE:
            self->get_id.fun = (get_evento_fun_p)get_num_buff_fun;

            EVENTO_SOURCE_GET_NUM_BUFF_PARAMS * params = (EVENTO_SOURCE_GET_NUM_BUFF_PARAMS *)_params;
            self->get_id.data.cursor = 0;
            self->get_id.data.changing_num = false;
            self->get_id.data.max_length = params->max_length;
            self->get_id.data.min_length = params->min_length;
            self->get_id.data.is_num_buff_correct = params->is_num_buff_correct;
            self->get_id.data.show_num_buff = params->show_num_buff;
            self->get_id.data.cur_length = 0;
            self->get_id.data.ID_buffer = malloc(params->max_length + 1);
            if(params->initial_num_buff && params->initial_num_buff_len){
                //si se indica un arreglo inicial especifico, lo copio
                //y guardo su longitud
                int i;
                for(i = 0; i < params->initial_num_buff_len && i < params->max_length; i++){
                    self->get_id.data.ID_buffer[i] = params->initial_num_buff[i];
                }
                self->get_id.data.cur_length = i;
            } else {
                //si no se indica ningun arreglo inicial, pongo t_odo en 0xFF
                //para indicar que esta vacio
                for(int i = 0; i < params->max_length; i++){
                    self->get_id.data.ID_buffer[i] = UINT8_MAX;
                }
            }
            break;
        case EVENTO_SOURCE_GET_TIME_OUT_TYPE:
            self->any.fun = NULL;
            break;
        case EVENTO_SOURCE_GET_CANCEL_TYPE:
            self->get_cancel.fun = (get_evento_fun_p)get_cancel_fun;

            self->get_cancel.data.taps = 0;
            break;
        default:
            self->type = EVENTO_SOURCE_TYPE_N;
            self->any.fun = NULL;
    }
}

// new evento_source(type);
EVENTO_SOURCE * evento_source__create(EVENTO_SOURCE_TYPE type, void * params) {
    EVENTO_SOURCE * result = (EVENTO_SOURCE *) malloc(sizeof(EVENTO_SOURCE));
    evento_source__init(result, type, params);
    return result;
}

// Destructor (without deallocation)
void evento_source__reset(EVENTO_SOURCE* self)
{
    if(self->type == EVENTO_SOURCE_GET_NUM_BUFF_TYPE)
    {
        if(self->get_id.data.ID_buffer) {
            free(self->get_id.data.ID_buffer);
            self->get_id.data.ID_buffer = NULL;
        }
    }
    self->type = EVENTO_SOURCE_TYPE_N;
}

// Destructor + deallocation (equivalent to "delete evento_source")
void evento_source__destroy(EVENTO_SOURCE* self) {
    if (self) {
        evento_source__reset(self);
        free(self);
    }
}

void evento_source_restart(EVENTO_SOURCE *self, void * params) {
    EVENTO_SOURCE_TYPE type = self->type;
    evento_source__reset(self);
    evento_source__init(self, type, params);
}

evento_t get_evento(EVENTO_SOURCE *self, suceso_t suceso) {
    if(self->any.fun == NULL){
        evento_t ev;
        ev.type = EVENTO_N;
        return ev;
    }
    return self->any.fun(&self->any.data, suceso);
}

