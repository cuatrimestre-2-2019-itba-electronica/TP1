#include "cqp_queue.h"

#include <stdint.h>
#include <stdlib.h>
#include <stdio.h>
#include <conio.h>

#define CQP_VERBOSE

#ifdef CQP_VERBOSE

const char * cqp_debug_codes[] = \
{    "PASA_0",
     "PASA_1",
     "PASA_2",
     "PASA_3",
     "PASA_4",
     "PASA_5",
     "PASA_6",
     "PASA_7",
     "PASA_8",
     "PASA_9",
     "PASA_SWIPE_START",
     "PASA_SWIPE_END",
     "PASA_RIGHT",
     "PASA_LEFT",
     "PASA_PRESS",
     "PASA_RELEASE",
     "PASA_ID",
     "PASA_DELAY",
     "CQP_N"
};

#endif

#define CQP_SOURCES_EMULATOR_A

#ifdef CQP_SOURCES_EMULATOR_A

static cqp_t cqp[] =
        {PASA_LEFT,
         PASA_LEFT,
         PASA_PRESS, PASA_RELEASE,
         PASA_LEFT,
         PASA_LEFT,
         PASA_PRESS, PASA_RELEASE,
         PASA_LEFT,
         PASA_LEFT,
         PASA_LEFT,
         PASA_PRESS, PASA_RELEASE,
         PASA_LEFT,
         PASA_LEFT,
         PASA_LEFT,
         PASA_LEFT,
         PASA_LEFT,
         PASA_PRESS, PASA_RELEASE,
         PASA_LEFT,
         PASA_LEFT,
         PASA_LEFT,
         CQP_N
        };

static unsigned int front = 0;
static unsigned int cqp_queue_size = 0;

#endif

typedef struct CQP_QUEUE {int a; int b;}CQP_QUEUE; //TODO: solo para que no sea un incomplete type y poder hacerle sizeof() para el malloc

bool is_cqp_queue_empty(CQP_QUEUE *self) {
    return !cqp_queue_size;
}

cqp_t get_next_cqp(CQP_QUEUE *self) {
#ifdef CQP_SOURCES_EMULATOR_A
    if(cqp_queue_size && cqp[front] != CQP_N)
    {
#ifdef CQP_VERBOSE
        printf("%s \n", cqp_debug_codes[cqp[front]]);
#endif
        cqp_queue_size--;
        return cqp[front++];
    } else{
        return CQP_N;
    }
#else
#endif
}

void cqp_queue__init(CQP_QUEUE * self)
{
    //TODO: inicializacion del ahrdware necesario
}

CQP_QUEUE *cqp_queue__create() {
    CQP_QUEUE * result = (CQP_QUEUE *) malloc(sizeof(CQP_QUEUE));
    cqp_queue__init(result);
    return result;
}

void cqp_queue__destroy(CQP_QUEUE *self) {

}

void cqp_queue_update(CQP_QUEUE *self) {
#ifdef CQP_SOURCES_EMULATOR_A
    if(cqp[front + cqp_queue_size] != CQP_N)
    {
        cqp_queue_size++;
    }
#else

#endif
}


