#include <stdio.h>
#include <stdlib.h>
#include <stdint.h>
#include <stddef.h>
#include <stdbool.h>
#include <assert.h>

//#include "circular_buffer/circular_buffer.h"
//#include "waiting_id_suceso_queue.h"
//#include "waiting_id_suceso_sources.h"
//#include "circular_buffer/utringbuffer.h"

//#include "waiting_id_suceso_queue.h"
//#include "evento_queue.h"

//#include "fsm.h"

#include "database.h"

int main(void)
{
//    FSM * machine  = FSM__create();
//    unsigned int i = 1;
//    while(!FSM_cycle(machine) && i++);
//    return 0;


//    SUCESO_QUEUE * suQ = suceso_queue__create();
//    //append_suceso_source(q, suceso_source__create(SUCESO_SOURCE_GET_NUM_TYPE));
//    for (int i = 0; i < 8; ++i) {
//        suceso_queue_update(suQ);
//        suceso_t suceso = get_next_suceso(suQ);
//        printf("%d\t %s \n", (int) suceso, suc_debug_codes[(uint8_t) suceso]);
//    }
//    suceso_queue__destroy(suQ);

//    EVENTO_QUEUE * evQ = evento_queue__create();
//    for(int i = 0; i < 24; i++){
//        evento_queue_update(evQ);
//        if(!is_evento_queue_empty(evQ))
//        {
//            evento_t ev = get_next_event(evQ);
//            printf("evento: %d\n", (int)ev.type);
//        }
//
//    }

//    evento_queue__destroy(evQ);


//    CQP_QUEUE * q = cqp_queue__create();
//    cqp_t cqp = CQP_N;
//    bool b = is_cqp_queue_empty(q);
//    cqp_queue_update(q);
//    cqp_queue_update(q);
//    b = is_cqp_queue_empty(q);
//    cqp = get_next_cqp(q);
//    cqp = get_next_cqp(q);
//    cqp = get_next_cqp(q);

//
//    UT_ringbuffer *pairs;
//    intpair_t ip, *p;
//    utringbuffer_new(pairs, 6, &intpair_icd);
//
//    ip.a=1;  ip.b=2;  utringbuffer_push_back(pairs, &ip);
//    ip.a=20; ip.b=20; utringbuffer_push_back(pairs, &ip);
//    ip.a=30; ip.b=20; utringbuffer_push_back(pairs, &ip);
//    ip.a=40; ip.b=20; utringbuffer_push_back(pairs, &ip);
//
//
//    p=(intpair_t*)utringbuffer_next(pairs,p);
//    printf("%d %d\n\n", p->a, p->b);
//    ip.a=50; ip.b=20; utringbuffer_push_back(pairs, &ip);
//
//    p=(intpair_t*)utringbuffer_next(pairs,p);
//    printf("%d %d\n\n", p->a, p->b);
//
//    for(p=(intpair_t*)utringbuffer_front(pairs);
//        p!=NULL;
//        p=(intpair_t*)utringbuffer_next(pairs,p)) {
//        printf("%d %d\n", p->a, p->b);
//    }
//
//    utringbuffer_free(pairs);
//
//    /////////////
//    SUCESO_QUEUE * q = suceso_queue__create();
////    append_suceso_source(q, get_num);
////    append_suceso_source(q, get_tap);
////    append_suceso_source(q, get_cursor_move);
////    append_suceso_source(q, get_increase_display_intensity);
//
//    cqp_t array[] = {PASA_RIGHT,    //
//                     PASA_LEFT,    //
//                     PASA_LEFT,    //
//                     PASA_PRESS,
//                     PASA_LEFT,    //
//                     PASA_RIGHT,
//                     PASA_RELEASE,
//                     PASA_LEFT,    //
//
//                    };
//    suceso_t s;
//    for(int i = 0; i < 8; i++)
//    {
////        dispatch(q, array[i]);
//        if(!is_suceso_queue_empty(q))
//        {
//            s = get_next_suceso(q);
//            printf("%s \n", suc_debug_codes[(int) s]);
//        }
//    }
//
//    suceso_queue__destroy(q);
//

//    uint8_t * buffer  = malloc(EXAMPLE_BUFFER_SIZE * sizeof(uint8_t));
//
//    printf("\n=== C Circular Buffer Check ===\n");
//
//    cbuf_handle_t cbuf = circular_buf_init(buffer, EXAMPLE_BUFFER_SIZE);
//
//    printf("Buffer initialized. ");
//    print_buffer_status(cbuf);
//
//    printf("\n******\nAdding %d values\n", EXAMPLE_BUFFER_SIZE - 1);
//    for(uint8_t i = 0; i < (EXAMPLE_BUFFER_SIZE - 1); i++)
//    {
//        circular_buf_put(cbuf, i);
//        printf("Added %u, Size now: %d\n", i, (int)circular_buf_size(cbuf));
//    }
//
//    print_buffer_status(cbuf);
//
//    printf("\n******\nAdding %d values\n", EXAMPLE_BUFFER_SIZE);
//    for(uint8_t i = 0; i < EXAMPLE_BUFFER_SIZE; i++)
//    {
//        circular_buf_put(cbuf, i);
//        printf("Added %u, Size now: %d\n", i, (int)circular_buf_size(cbuf));
//    }
//
//    print_buffer_status(cbuf);
//
//    printf("\n******\nReading back values: ");
//    while(!circular_buf_empty(cbuf))
//    {
//        uint8_t data;
//        circular_buf_get(cbuf, &data);
//        printf("%u ", data);
//    }
//    printf("\n");
//
//    print_buffer_status(cbuf);
//
//    printf("\n******\nAdding %d values\n", EXAMPLE_BUFFER_SIZE + 5);
//    for(uint8_t i = 0; i < EXAMPLE_BUFFER_SIZE + 5; i++)
//    {
//        circular_buf_put(cbuf, i);
//        printf("Added %u, Size now: %d\n", i, circular_buf_size(cbuf));
//    }
//
//    print_buffer_status(cbuf);
//
//    printf("\n******\nReading back values: ");
//    while(!circular_buf_empty(cbuf))
//    {
//        uint8_t data;
//        circular_buf_get(cbuf, &data);
//        printf("%u ", data);
//    }
//    printf("\n");
//
//    printf("\n******\nAdding %d values using non-overwrite version\n", EXAMPLE_BUFFER_SIZE + 5);
//    for(uint8_t i = 0; i < EXAMPLE_BUFFER_SIZE + 5; i++)
//    {
//        circular_buf_put2(cbuf, i);
//    }
//
//    print_buffer_status(cbuf);
//
//    printf("\n******\nReading back values: ");
//    while(!circular_buf_empty(cbuf))
//    {
//        uint8_t data;
//        circular_buf_get(cbuf, &data);
//        printf("%u ", data);
//    }
//    printf("\n");
//
//    free(buffer);
//    circular_buf_free(cbuf);
//
//    return 0;
}

