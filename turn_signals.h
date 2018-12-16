#ifndef turn_signals_h
#define turn_signasl_h



#include <stdint.h>
#include <stdbool.h>
#include "inc/hw_memmap.h"
//#include "inc/tm4c123gh6pm.h"
//#include "signalSystem.h"
//#include "powerManagement.h"
//#include "ultrasonicSensor.h"
#include "inc/hw_types.h"
#include "driverlib/debug.h"
#include "driverlib/fpu.h"
#include "driverlib/gpio.h"
#include "driverlib/pin_map.h"
#include "driverlib/rom.h"
#include "driverlib/rom_map.h"
#include "driverlib/sysctl.h"
#include "driverlib/uart.h"
#include "utils/uartstdio.h"
#include "driverlib/ssi.h"
#include "inc/hw_ssi.h"
#include "driverlib/ssi.h"
#include"driverlib/uart.h"
#include "driverlib/timer.h"



#define SYS_TURN_BUTTONS_PORT   SYSCTL_PERIPH_GPIOF
#define TURN_BUTTONS_PORT       GPIO_PORTF_BASE 
#define left_turn_switch        GPIO_PIN_4
#define right_turn_switch       GPIO_PIN_0 
#define SYS_TURN_LED_PORT       SYSCTL_PERIPH_GPIOA
#define TURN_LIGHT_PORT         GPIO_PORTA_BASE
#define left_turn_light         GPIO_PIN_5
#define right_turn_light      GPIO_PIN_6
#define SYS_TURN_SIGNAL_TIMER   SYSCTL_PERIPH_TIMER0
#define TURN_SIGNAL_TIMER       TIMER2_BASE        


#define ONE_MS (uint32_t)(SysCtlClockGet() / 1000) // One millisecond

void enable_turn_signals();
void enable_timer();
void turn_button_isr();
void timer_2_isr();





#endif
