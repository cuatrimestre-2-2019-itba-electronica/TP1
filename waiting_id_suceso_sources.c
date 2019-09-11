//
// Created by mlste on 9/1/2019.
//
#include <stdbool.h>
#include <stdlib.h>

#include "waiting_id_suceso_sources.h"

#define GET_NUM_MAX 10
#define DELAYS_UNTIL_TIMEOUT 10 //todo: fijarme bien este valor


union SUCESO_SOURCE_DATA;
typedef union SUCESO_SOURCE_DATA SUCESO_SOURCE_DATA;

typedef suceso_t(*get_suceso_fun_p)(SUCESO_SOURCE_DATA * data, cqp_t cqp);

/********************************************************
 * ******************************************************
 * DATOS MIEMBROS
 * ******************************************************
 * ******************************************************/

/****************
 *   GET_DELAY
 * *************/

typedef struct SUCESO_SOURCE_GET_DELAY_DATA
{
    //Cuenta cuantas PASA_DELAY llegan ininterrumpidas por otras CQP
    unsigned int max_count;
    unsigned int count;
} SUCESO_SOURCE_GET_DELAY_DATA;

suceso_t get_delay_fun(SUCESO_SOURCE_GET_DELAY_DATA * data, cqp_t cqp)
{
    if(cqp == PASA_DELAY)
    {
        data->count++;
        if(data->count == data->max_count){
            return SUC_DELAY;
        }
    }
    return SUC_N;
}

typedef struct SUCESO_SOURCE_GET_DELAY
{
    SUCESO_SOURCE_TYPE type;
    get_suceso_fun_p fun;
    SUCESO_SOURCE_GET_DELAY_DATA data;
} SUCESO_SOURCE_GET_DELAY;


/****************
 *   GET_NUM
 * *************/

typedef struct SUCESO_SOURCE_GET_NUM_DATA
{
    bool swiping;
} SUCESO_SOURCE_GET_NUM_DATA;

suceso_t get_num_fun(SUCESO_SOURCE_GET_NUM_DATA * data, cqp_t cqp)
{
    // Si no esta swiping, lo unico relevante que puede pasar es
    // que empiece a swipear
    if(!data->swiping){
        if(cqp == PASA_SWIPE_START){
        data->swiping = true;
        }
        return SUC_N;
    }

    //Si esta swiping:
    switch (cqp)
    {
        case PASA_0: case PASA_1: case PASA_2:
        case PASA_3: case PASA_4: case PASA_5:
        case PASA_6: case PASA_7: case PASA_8:
        case PASA_9:
            return (suceso_t)cqp;
        case PASA_SWIPE_END:
            data->swiping = false;
            return SUC_SWIPE_END;
        case PASA_RIGHT: case PASA_LEFT:
        case PASA_PRESS: case PASA_RELEASE:
        //si el usuario movio el encoder mientras pasaba la tarjeta:
            return SUC_SWIPE_INTERRUPTED;
        default: case PASA_DELAY: case CQP_N:
            return SUC_N;
    }
}

typedef struct SUCESO_SOURCE_GET_NUM
{
    SUCESO_SOURCE_TYPE type;
    get_suceso_fun_p fun;
    SUCESO_SOURCE_GET_NUM_DATA data;
} SUCESO_SOURCE_GET_NUM;

/****************
 *   GET_TAP
 * *************/

typedef struct SUCESO_SOURCE_GET_TAP_DATA
{
    //es true cuando se presiono el encoder
    // && todavia no se solto
    // && no hubo un delay
    // && no hubo una rotacion
    bool pressed;

    // es true cuando se presiono y solto el encoder
    // && entremedio no se roto el encoder
    // && entremedio no hubo un delay
    bool tap_detected;
} SUCESO_SOURCE_GET_TAP_DATA;

suceso_t get_tap_fun(SUCESO_SOURCE_GET_TAP_DATA * data, cqp_t cqp)
{
    if(cqp == PASA_PRESS)
    {
        data->pressed = true;    //Se presiono el encoder
        data->tap_detected = false;
    }
    else if(cqp == PASA_RELEASE && data->pressed)
    {
        data->pressed = false;
        data->tap_detected = true;
    }
    else
    {
        data->pressed = false;
        data->tap_detected = false;
    }
    return data->tap_detected ? SUC_TAP_DETECTED : SUC_N;
}

typedef struct SUCESO_SOURCE_GET_TAP
{
    SUCESO_SOURCE_TYPE type;
    get_suceso_fun_p fun;
    SUCESO_SOURCE_GET_TAP_DATA data;
} SUCESO_SOURCE_GET_TAP;

/****************
 *   GET_CURSOR_MOVE_DATA
 * *************/

typedef struct SUCESO_SOURCE_GET_CURSOR_MOVE_DATA
{
    bool pressed;
    bool moving;
} SUCESO_SOURCE_GET_CURSOR_MOVE_DATA;

suceso_t get_cursor_move_fun(SUCESO_SOURCE_GET_CURSOR_MOVE_DATA * data, cqp_t cqp)
{
    // Si no esta apretado, lo unico relevante
    // que puede pasar es que
    // 1) se aprete
    // 2) se gire para la derecha
    // 3) se gire para la izquierda
    // No es posible registrar movimiento del cursor
    // en sentido lateral sin antes registrar que se
    // presiono.
    if(!data->pressed)
    {
        if(cqp == PASA_PRESS){ data->pressed = true; return SUC_N; }
        else if (cqp == PASA_RIGHT) { return SUC_SCROLL_DOWN; }
        else if (cqp == PASA_LEFT)  { return SUC_SCROLL_UP; }
    }

    //Si ya estaba apretado, puede
    // * moverse el cursor a ambos lados, en cuyo casp
    // se entra en modo "moviendo cursor" y se ignoran
    // los delays (moving = pressed = true)
    // * pasar un delay, en cuyo caso se entra en modo
    // "cambiando intensidad de display" y para este
    // generador es equivalente a que se desaprete
    // * desapretarse

    switch (cqp)
    {
        case PASA_RIGHT:
            data->moving = true;
            return SUC_MOVE_CURSOR_RIGHT;
        case PASA_LEFT:
            data->moving = true;
            return SUC_MOVE_CURSOR_LEFT;
        case PASA_DELAY:
            if(!data->moving)
            {
                data->pressed = false;
            }
            return SUC_N;
        case PASA_RELEASE: default:
            data->moving = false;
            data->pressed = false;
            return SUC_N;
    }
}

typedef struct SUCESO_SOURCE_GET_CURSOR_MOVE
{
    SUCESO_SOURCE_TYPE type;
    get_suceso_fun_p fun;
    SUCESO_SOURCE_GET_CURSOR_MOVE_DATA data;
} SUCESO_SOURCE_GET_CURSOR_MOVE;

/****************
 *   GET_INC_DISP_INT_DATA
 * *************/

typedef struct SUCESO_SOURCE_GET_INC_DISP_INT_DATA
{
    bool pressed;
} SUCESO_SOURCE_GET_INC_DISP_INT_DATA;

suceso_t get_inc_disp_int_fun(SUCESO_SOURCE_GET_INC_DISP_INT_DATA * data, cqp_t cqp)
{

    // Si no esta apretado, lo unico relevante
    // que puede pasar es que se aprete.
    // No es posible cambiar intensidad display
    // sin antes registrar que se presiono el
    // encoder
    if(!data->pressed)
    {
        if(cqp == PASA_PRESS)
        {
            data->pressed = true;
        }
        return SUC_N;
    }
    //Si el encoder ya estaba apretado, puede
    // * haber un delay => cambia la intensidad del display
    // * desapretarse
    switch (cqp)
    {
        case PASA_DELAY:
            return SUC_INC_DIS_INTENSITY;
        case PASA_RELEASE: default:
            data->pressed = false;
            return SUC_N;
    }
}

typedef struct SUCESO_SOURCE_GET_INC_DISP_INT
{
    SUCESO_SOURCE_TYPE type;
    get_suceso_fun_p fun;
    SUCESO_SOURCE_GET_INC_DISP_INT_DATA data;
} SUCESO_SOURCE_GET_INC_DISP_INT;


/****************
 *   SUCESO_SOURCE
 * *************/

union SUCESO_SOURCE_DATA
{
    SUCESO_SOURCE_GET_DELAY_DATA get_delay_data;
    SUCESO_SOURCE_GET_NUM_DATA get_num_data;
    SUCESO_SOURCE_GET_TAP_DATA get_tap_data;
    SUCESO_SOURCE_GET_CURSOR_MOVE_DATA get_cursor_move_data;
    SUCESO_SOURCE_GET_INC_DISP_INT_DATA get_inc_disp_int_data;
};

//para acceder a los campos fun y data sin analizar type:
typedef struct SUCESO_SOURCE_ANY
{
    SUCESO_SOURCE_TYPE type;
    get_suceso_fun_p fun;
    SUCESO_SOURCE_DATA data;
} SUCESO_SOURCE_ANY;


union SUCESO_SOURCE
{
    SUCESO_SOURCE_TYPE type;    //para saber el tipo rapido
    SUCESO_SOURCE_ANY any;
    SUCESO_SOURCE_GET_DELAY get_delay;
    SUCESO_SOURCE_GET_NUM get_num;
    SUCESO_SOURCE_GET_TAP get_tap;
    SUCESO_SOURCE_GET_CURSOR_MOVE get_cursor_move;
    SUCESO_SOURCE_GET_INC_DISP_INT get_inc_disp_int;
};



/********************************************************
 * ******************************************************
 * FUNCIONES MIEMBRO
 * ******************************************************
 * ******************************************************/


// Constructor (without allocation)
void suceso_source__init(SUCESO_SOURCE* self, SUCESO_SOURCE_TYPE type)
{
    self->type = type;
    switch (type)
    {
        case SUCESO_SOURCE_GET_NUM_TYPE:
            self->any.fun = (get_suceso_fun_p)get_num_fun;
            self->get_num.data.swiping = false;
            break;
        case SUCESO_SOURCE_GET_TAP_TYPE:
            self->any.fun = (get_suceso_fun_p)get_tap_fun;
            self->get_tap.data.pressed = false;
            self->get_tap.data.tap_detected = false;
            break;
        case SUCESO_SOURCE_GET_CURSOR_MOVE_TYPE:
            self->any.fun = (get_suceso_fun_p)get_cursor_move_fun;
            self->get_cursor_move.data.pressed = false;
            self->get_cursor_move.data.moving = false;
            break;
        case SUCESO_SOURCE_GET_INC_DISP_INT_TYPE:
            self->any.fun = (get_suceso_fun_p)get_inc_disp_int_fun;
            self->get_inc_disp_int.data.pressed = false;
            break;
        case SUCESO_SOURCE_GET_DELAY_TYPE:
            self->any.fun = (get_suceso_fun_p)get_delay_fun;
            self->get_delay.data.max_count = DELAYS_UNTIL_TIMEOUT;
            break;
        default:
            self->type = SUCESO_SOURCE_TYPE_N;
            self->any.fun = NULL;
    }
}

// new suceso_source(type);
SUCESO_SOURCE * suceso_source__create(SUCESO_SOURCE_TYPE type) {
    SUCESO_SOURCE * result = (SUCESO_SOURCE *) malloc(sizeof(SUCESO_SOURCE));
    suceso_source__init(result, type);
    return result;
}

// Destructor (without deallocation)
void suceso_source__reset(SUCESO_SOURCE* self)
{}

// Destructor + deallocation (equivalent to "delete suceso_source")
void suceso_source__destroy(SUCESO_SOURCE* self) {
    if (self) {
        suceso_source__reset(self);
        free(self);
    }
}

void suceso_source_restart(SUCESO_SOURCE *self) {
    suceso_source__reset(self);
    suceso_source__init(self, self->type);
}

suceso_t get_suceso(SUCESO_SOURCE *self, cqp_t cqp) {
    if(self->any.fun == NULL)
    {
        return SUC_N;
    }
    return self->any.fun(&self->any.data, cqp);
}
