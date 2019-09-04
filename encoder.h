/***************************************************************************//**
  @file     encoder.h
  @brief    Encoder driver
  @author   Arturo
 ******************************************************************************/

#ifndef _ENCODER_H_
#define _ENCODER_H_

#include "gpio.h"
#include "board.h"

static int counter;
static void (*callback_CW)(void);
static void (*callback_CCW)(void);
static void (*callback_SW)(void);

int encoder_init(); // Init the encoder

int encoder_get_counter(); // Return the counter

void encoder_set_counter(int userCounter); // Set the counter

void encoder_action_CW();	// Function executed when the encoder is turned CW

void encoder_action_CCW();	// Function executed when the encoder is turned CCW

void encoder_action_SW();	// Function executed when the encoder is pressed

void encoder_set_callback_CW(void (*userCallback_CW)(void));	// Set the function to do when the encoder is turned CW

void encoder_set_callback_CCW(void (*userCallback_CCW)(void));	// Set the function to do when the encoder is turned CCW

void encoder_set_callback_SW(void (*userCallback_SW)(void));	// Set the function to do when the encoder is pressed

#endif // _ENCODER_H_
