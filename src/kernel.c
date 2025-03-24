#include "printf.h"
#include "utils.h"
#include "timer.h"
#include "irq.h"
#include "fork.h"
#include "sched.h"
#include "mini_uart.h"



void kernel_main(void)
{
	uart_init();
	init_printf(0, putc);
	irq_init_vectors();
	timer_init();
	enable_interrupt_controller();
	irq_enable();

	int res = copy_process((unsigned long)&process, (unsigned long)"12345");
	if (res != 0) {
		printf("error while starting process 1");
		return;
	}
	res = copy_process((unsigned long)&process, (unsigned long)"abcde");
	if (res != 0) {
		printf("error while starting process 2");
		return;
	}

	while (1){
		schedule();
	}	
}