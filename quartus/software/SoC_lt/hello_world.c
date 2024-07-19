#include <stdio.h>
#include "io.h"
#include "system.h"
#include "altera_avalon_timer_regs.h"
#include "sys/alt_irq.h"

unsigned int hex_decode[10] = {1, 79, 18, 6, 76, 36, 32, 15, 0, 4};

//int seg_decoder(int s){
//	switch (s){
//	case 0: return 1;
//		break;
//	case 1:	return 79;
//		break;
//	case 2: return 18;
//		break;
//	case 3: return 6;
//		break;
//	case 4: return 76;
//		break;
//	case 5: return 36;
//		break;
//	case 6: return 32;
//		break;
//	case 7: return 15;
//		break;
//	case 8: return 0;
//		break;
//	case 9: return 4;
//		break;
//	default: break;
//	}
//}

volatile int* sw_ptr = (int*) SW_BASE;
volatile int* slave_ptr = (int*) SOC_SLAVE_0_BASE;
volatile int* h0_ptr = (int*) HEX_0_BASE;
volatile int* h1_ptr = (int*) HEX_1_BASE;
volatile int* h2_ptr = (int*) HEX_2_BASE;

unsigned int status = 1;

//Point
unsigned int point = 0;
unsigned int point_1 = 0;
unsigned int point_2 = 0;

//Clock
unsigned int minute = 0;
unsigned int second = 0;
//KEY
volatile int* key_ptr = (int*) KEY_BASE;

unsigned int unit(unsigned int number){
	return number%10;
}

unsigned int decade(unsigned int number){
	return number/10;
}


void point_handle(){
	int y;
	point = *(sw_ptr);
	point_1 = point & 0xf;
	point_2 = (point & 0xf0) >> 0x4;

	*(slave_ptr + 2) = hex_decode[point_2] << 7 | hex_decode[point_1];
	y = *(slave_ptr + 2);
	*(h2_ptr) = y;
}



void clock(){
	int second_h, minute_h;
	if(second == 60){
		second = 0;
		minute++;
	}
	if(minute == 90){
		IOWR_ALTERA_AVALON_TIMER_CONTROL(TIMER_0_BASE,
			ALTERA_AVALON_TIMER_CONTROL_CONT_MSK | // Continue counting mode
			ALTERA_AVALON_TIMER_CONTROL_ITO_MSK | // Interrupt enable
			ALTERA_AVALON_TIMER_CONTROL_STOP_MSK);
	}
	*(slave_ptr + 0) = hex_decode[decade(second)] << 7 | hex_decode[unit(second)];
	*(slave_ptr + 1) = hex_decode[decade(minute)] << 7 | hex_decode[unit(minute)];
	second_h = *(slave_ptr + 0);
	minute_h = *(slave_ptr + 1);
	*(h0_ptr) = second_h;
	*(h1_ptr) = minute_h;
}

void timer_Init(){
	unsigned int period = 0;
	// Stop Timer
	IOWR_ALTERA_AVALON_TIMER_CONTROL(TIMER_0_BASE, ALTERA_AVALON_TIMER_CONTROL_STOP_MSK);
	//Configure period
	period = 50000000 - 1;
	IOWR_ALTERA_AVALON_TIMER_PERIODL(TIMER_0_BASE, period);
	IOWR_ALTERA_AVALON_TIMER_PERIODH(TIMER_0_BASE, (period >> 16));
	IOWR_ALTERA_AVALON_TIMER_CONTROL(TIMER_0_BASE,
	ALTERA_AVALON_TIMER_CONTROL_CONT_MSK | // Continue counting mode
	ALTERA_AVALON_TIMER_CONTROL_ITO_MSK |// Interrupt enable
	ALTERA_AVALON_TIMER_CONTROL_START_MSK);// Start Timer
}
void Timer_IRQ_Handler(void* isr_context){
	//handle point
	point_handle();
	second++;
	// Clear Timer interrupt bit
	IOWR_ALTERA_AVALON_TIMER_STATUS(TIMER_0_BASE, ALTERA_AVALON_TIMER_STATUS_TO_MSK);
}
int main(){
	timer_Init();
	alt_ic_isr_register(0, TIMER_0_IRQ, Timer_IRQ_Handler, (void*)0,(void*)0);
	while(1){
		if(*(key_ptr) == 0){
			while(*(key_ptr) == 0);
			status = ~status & 1;
			if(status == 0){
				IOWR_ALTERA_AVALON_TIMER_CONTROL(TIMER_0_BASE,
					ALTERA_AVALON_TIMER_CONTROL_CONT_MSK | // Continue counting mode
					ALTERA_AVALON_TIMER_CONTROL_ITO_MSK | // Interrupt enable
					ALTERA_AVALON_TIMER_CONTROL_STOP_MSK);
			}
			else
			{
				IOWR_ALTERA_AVALON_TIMER_CONTROL(TIMER_0_BASE,
					ALTERA_AVALON_TIMER_CONTROL_CONT_MSK | // Continue counting mode
					ALTERA_AVALON_TIMER_CONTROL_ITO_MSK | // Interrupt enable
					ALTERA_AVALON_TIMER_CONTROL_START_MSK);
			}
		}

		clock();
	};
	return 0;
}



