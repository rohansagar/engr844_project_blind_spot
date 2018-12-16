#include "turn_signals.h"

bool left_turn = 0;
bool right_turn = 0;

void enable_turn_signals()
{
 
    if(!SysCtlPeripheralReady(SYS_TURN_BUTTONS_PORT))
    {
         SysCtlPeripheralEnable(SYS_TURN_BUTTONS_PORT);
    }
    while(!SysCtlPeripheralReady(SYS_TURN_BUTTONS_PORT));

    
    // Enable SW1 and SW2 with weak pull ups
    GPIOPinTypeGPIOInput(TURN_BUTTONS_PORT, left_turn_switch | right_turn_switch);
    GPIOPadConfigSet(TURN_BUTTONS_PORT, left_turn_switch | right_turn_switch, GPIO_STRENGTH_8MA, GPIO_PIN_TYPE_STD_WPU);

    // Configure interrupts on SW1 and SW2
    GPIOIntRegister(TURN_BUTTONS_PORT, turn_button_isr);
    GPIOIntTypeSet(TURN_BUTTONS_PORT, left_turn_switch | right_turn_switch, GPIO_FALLING_EDGE);
    GPIOIntEnable(TURN_BUTTONS_PORT, left_turn_switch | right_turn_switch);

    // setup the timer
    enable_timer();
    }


void enable_timer(){
    SysCtlPeripheralEnable(SYS_TURN_SIGNAL_TIMER);
    while(!SysCtlPeripheralReady(SYS_TURN_SIGNAL_TIMER));

    TimerConfigure(TURN_SIGNAL_TIMER, TIMER_CFG_PERIODIC);

    TimerLoadSet(TURN_SIGNAL_TIMER, TIMER_A, 500 * ONE_MS);
    TimerIntRegister(TURN_SIGNAL_TIMER, TIMER_A, timer_2_isr);
    TimerIntEnable(TURN_SIGNAL_TIMER, TIMER_TIMA_TIMEOUT);

}



void turn_button_isr()
{

    // check which button turn is initiated
    if(!GPIOPinRead(TURN_BUTTONS_PORT, left_turn_switch))
    {
        left_turn = !left_turn;
    }

    if(!GPIOPinRead(TURN_BUTTONS_PORT, right_turn_switch))
    {
        right_turn = !right_turn;
    }

    if(left_turn | right_turn)
    {
        TimerEnable(TURN_SIGNAL_TIMER, TIMER_A);

    }
    else{
        TimerDisable(TURN_SIGNAL_TIMER, TIMER_A);
    }

}

void timer_2_isr()
{
    // clear timer interrupt
    TimerIntClear(TURN_SIGNAL_TIMER, TIMER_A);
    if(left_turn){
        GPIOPinWrite(TURN_LIGHT_PORT, left_turn_light, ~(GPIOPinRead(TURN_LIGHT_PORT, left_turn_light)));
        SysCtlDelay(3);
    }

    if(right_turn){
        GPIOPinWrite(TURN_LIGHT_PORT, right_turn_light, ~(GPIOPinRead(TURN_LIGHT_PORT, right_turn_light)));
        SysCtlDelay(3);
    }

}
