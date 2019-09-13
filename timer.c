/***************************************************************************//**
  @file     timer.c
  @brief    Timer driver. Simple implementation, support multiple timers
  @author   Nicolás Magliola
 ******************************************************************************/

/*******************************************************************************
 * INCLUDE HEADER FILES
 ******************************************************************************/

#include "timer.h"

#include "SysTick.h"


//NOTA DE CLASE: este esta separado en MCAL y HAL

/*******************************************************************************
 * CONSTANT AND MACRO DEFINITIONS USING #DEFINE
 ******************************************************************************/

#if TIMER_TICK_MS != (1000U/SYSTICK_ISR_FREQUENCY_HZ)
#error Las frecuencias no coinciden!!
#endif // TIMER_TICK_MS != (1000U/SYSTICK_ISR_FREQUENCY_HZ)


/*******************************************************************************
 * ENUMERATIONS AND STRUCTURES AND TYPEDEFS
 ******************************************************************************/

/*******************************************************************************
 * VARIABLES WITH GLOBAL SCOPE
 ******************************************************************************/

/*******************************************************************************
 * FUNCTION PROTOTYPES FOR PRIVATE FUNCTIONS WITH FILE LEVEL SCOPE
 ******************************************************************************/

/**
 * @brief Periodic service
 */
static void timer_isr(void);


/*******************************************************************************
 * ROM CONST VARIABLES WITH FILE LEVEL SCOPE
 ******************************************************************************/

/*******************************************************************************
 * STATIC VARIABLES AND CONST VARIABLES WITH FILE LEVEL SCOPE
 ******************************************************************************/

static volatile ticks_t timer_main_counter;


/*******************************************************************************
 *******************************************************************************
                        GLOBAL FUNCTION DEFINITIONS
 *******************************************************************************
 ******************************************************************************/

void timerInit(void)
{
    static bool yaInit = false;
    if (yaInit)
        return;
    
    SysTick_Init(timer_isr); // init peripheral
    
    yaInit = true;
}


ticks_t timerStart(ticks_t ticks)
{
    ticks_t now_copy;
    
    if (ticks < 0)
        ticks = 0; // truncate min wait time
    
    //disable_interrupts();
    now_copy = timer_main_counter; // esta copia debe ser atomic!!
    //enable_interrupts();

    now_copy += ticks;

    return now_copy;
}


bool timerExpired(ticks_t timeout)
{
    ticks_t now_copy;

    //disable_interrupts();
    now_copy = timer_main_counter; // esta copia debe ser atomic!!
    //enable_interrupts();

    now_copy -= timeout;
    return (now_copy >= 0);
}


void timerDelay(ticks_t ticks)
{
    ticks_t tim;
    
    tim = timerStart(ticks);
    while (!timerExpired(tim))
    {
        // wait...
    }
}


/*******************************************************************************
 *******************************************************************************
                        LOCAL FUNCTION DEFINITIONS
 *******************************************************************************
 ******************************************************************************/

static void timer_isr(void)
{
    ++timer_main_counter; // update main counter
}


/******************************************************************************/
