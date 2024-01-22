// Brushless motor PWM code
// Michael Granberry

#include <stdio.h>
#include "platform.h"
#include "xil_printf.h"
#include "xtmrctr.h"
#include "xgpio.h"
#include "xparameters.h"
#include "sleep.h"

#define TMR_CTR_0 0
#define GPIO_1 1
// Tmr clk is set to 100 MHz in Vivado
#define ONE_mSec (1e9)/1e3 // 1 mSec duty cycle
#define PWM_PER (ONE_mSec*20) // 20 mSec pwm period

XTmrCtr tmr;
XGpio switches;

void tmr_init() {
	int status = XTmrCtr_Initialize(&tmr, XPAR_TIMER0_DEVICE_ID);
	if(status == XST_SUCCESS) {
		xil_printf("TMR INIT SUCCUSSFUL\n\r");
	} else {
		xil_printf("TMR INIT FAILED\n\r");
	}
	 status = XTmrCtr_SelfTest(&tmr, TMR_CTR_0);
	if(status == XST_SUCCESS) {
		xil_printf("TMR SELF TEST SUCCUSSFUL\n\r");
	} else {
		xil_printf("TMR SELF TEST FAILED\n\r");
	}
}

void tmr_setup() {
	XTmrCtr_Stop(&tmr, TMR_CTR_0);
	u32 tmrctr0_option = XTmrCtr_GetOptions(&tmr, TMR_CTR_0);
	tmrctr0_option |= XTC_DOWN_COUNT_OPTION;
	XTmrCtr_SetOptions(&tmr, TMR_CTR_0, tmrctr0_option);
	XTmrCtr_PwmConfigure(&tmr, PWM_PER, ONE_mSec);
	XTmrCtr_PwmEnable(&tmr);
	XTmrCtr_Start(&tmr, TMR_CTR_0);
}

void switches_init() {
	int status = XGpio_Initialize(&switches, XPAR_SWITCH_DEVICE_ID);
	if(status == XST_SUCCESS) {
		xil_printf("SWITCHES INIT SUCCUSSFUL\n\r");
	} else {
		xil_printf("SWITCHES INIT FAILED\n\r");
	}
}

void switches_setup() {
	XGpio_SetDataDirection(&switches, GPIO_1, 0xF); // GPIO switches -> input
}

void set_new_pwm(int duty_cycle) {
	XTmrCtr_PwmDisable(&tmr);
	XTmrCtr_PwmConfigure(&tmr, PWM_PER, duty_cycle);
	XTmrCtr_PwmEnable(&tmr);
}

void update_pwm(int switch_value, int *curr_duty_cycle, int *prev_duty_cycle) {
	switch_value = XGpio_DiscreteRead(&switches, 1);
	xil_printf("Switch value : %d\n\r", switch_value);
	switch (switch_value) {
		case 0x1:
			*curr_duty_cycle = (12e8)/1e3; // 1.2 mSec
			break;
		case 0x3:
			*curr_duty_cycle = (14e8)/1e3; // 1.4 mSec
			break;
		case 0x7:
			*curr_duty_cycle = (16e8)/1e3; // 1.6 mSec
			break;
		case 0xf:
			*curr_duty_cycle = (19e8)/1e3; // 1.8 mSec
			break;
		default:
			*curr_duty_cycle = ONE_mSec; // 1 mSec
			break;

	}
	xil_printf("Current duty cycle value : %d nSec\n\r", (*curr_duty_cycle));
	if(*prev_duty_cycle != *curr_duty_cycle){
		set_new_pwm(*curr_duty_cycle);
	}
	*prev_duty_cycle = *curr_duty_cycle;
}

int main()
{
    init_platform();
    switches_init();
    switches_setup();
    tmr_init();
    tmr_setup();
    int switch_value = 0;
    int curr_duty_cycle = 0;
    int prev_duty_cycle = 0;
    while(1) {
    	update_pwm(switch_value, &curr_duty_cycle, &prev_duty_cycle);
    }
    cleanup_platform();
    return 0;
}