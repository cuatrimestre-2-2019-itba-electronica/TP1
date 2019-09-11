#include "cqp_queue.h"

#include <stdint.h>
#include <stdlib.h>
#include <stdio.h>
#include "SysTick.h"
#include "encoder.h"
#include "circular_buffer/utringbuffer.h"

#define TIME_FREC 1
#define TIME_PRESCALER (SYSTICK_ISR_FREQUENCY_HZ/TIME_FREC)

//#define CQP_VERBOSE

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



//#define CQP_SOURCES_EMULATOR_A
#define CQP_QUEUE_SIZE 20

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
         PASA_PRESS, PASA_RELEASE,
         PASA_LEFT,
         PASA_PRESS, PASA_RELEASE,
         PASA_LEFT,
         PASA_PRESS, PASA_RELEASE,
         PASA_LEFT,
         PASA_LEFT,
         PASA_LEFT,
         CQP_N
        };

static unsigned int front = 0;
static unsigned int cqp_queue_size = 0;
static bool get_next = false;

//Para el ring buffer
UT_icd cqp_icd = {sizeof(cqp_t), NULL, NULL, NULL};

void time_init(void);

typedef struct CQP_QUEUE {
    UT_ringbuffer * CQP_queue;
    cqp_t * last_cqp;
    unsigned int cqp_queue_size;
}CQP_QUEUE;

CQP_QUEUE q;



static cqp_t cqp_queue_pop_front(CQP_QUEUE *self);
static bool cqp_queue_push_back(CQP_QUEUE *self, cqp_t cqp);

void cqp_queue_input_CW();
void cqp_queue_input_CCW();
void cqp_queue_input_PRESS();
void cqp_queue_input_RELEASE();


bool is_cqp_queue_empty(CQP_QUEUE *self) {
    return !self->cqp_queue_size;
}

cqp_t get_next_cqp(CQP_QUEUE *self) {
#ifdef CQP_SOURCES_EMULATOR_A
	if(!get_next){ return CQP_N; }
	get_next = false;
    if(cqp_queue_size && cqp[front] != CQP_N)
    {
#ifdef CQP_VERBOSE
        printf("%s \n", cqp_debug_codes[cqp[front]]);
#endif
        cqp_queue_size--;
        return cqp[front++];
    } else {
        return CQP_N;
    }
#else

    if(is_cqp_queue_empty(self))
    {
        return CQP_N;
    }

    cqp_t cqp = cqp_queue_pop_front(self);

    return cqp;
#endif
}

void cqp_queue__init(CQP_QUEUE * self)
{
	if(self == NULL){ return; }

	//creacion del buffer circular de sucesos (para la salida)
	utringbuffer_new(self->CQP_queue, CQP_QUEUE_SIZE, &cqp_icd);
	self->last_cqp = utringbuffer_front(self->CQP_queue);
	self->cqp_queue_size = 0;

	encoder_set_callback_CW(cqp_queue_input_CW);
	encoder_set_callback_CCW(cqp_queue_input_CCW);
	encoder_set_callback_SW_PRESS(cqp_queue_input_PRESS);
	encoder_set_callback_SW_RELEASE(cqp_queue_input_RELEASE);
}

CQP_QUEUE *cqp_queue__create() {
    cqp_queue__init(&q);
//    time_init();
    return &q;
}

void cqp_queue__destroy(CQP_QUEUE *self) {

}

void cqp_queue_update(CQP_QUEUE *self) {
#ifdef CQP_SOURCES_EMULATOR_A
    if(cqp[front + cqp_queue_size] != CQP_N && get_next)
    {
        cqp_queue_size++;
    }
#else

#endif
}

void time_IRQ(void){
	static uint32_t counter=0;
	if((counter%=TIME_PRESCALER)==0){
		get_next = true;
	}
	counter++;
}

void time_init(void){
	SysTick_append(time_IRQ);
}


void cqp_queue_input_CW(){
	cqp_queue_push_back(&q, PASA_RIGHT);
}

void cqp_queue_input_CCW(){
	cqp_queue_push_back(&q, PASA_LEFT);
}

void cqp_queue_input_PRESS(){
	cqp_queue_push_back(&q, PASA_PRESS);
}

void cqp_queue_input_RELEASE(){
	cqp_queue_push_back(&q, PASA_RELEASE);
}

static bool cqp_queue_push_back(CQP_QUEUE *self, cqp_t cqp ){
    if(cqp != CQP_N)
    {
        utringbuffer_push_back(self->CQP_queue, &cqp);
        self->cqp_queue_size++;
        return true;
    }
    return false;
}

cqp_t cqp_queue_pop_front(CQP_QUEUE *self){
    if(self->cqp_queue_size)
    {
        self->last_cqp = utringbuffer_next(self->CQP_queue, self->last_cqp);
        self->cqp_queue_size--;
        return *(self->last_cqp);
    }
    return CQP_N;
}


