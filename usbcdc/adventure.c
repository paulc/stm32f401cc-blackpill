
#include <FreeRTOS.h>
#include <task.h>

#include <libopencm3/stm32/rcc.h>
#include <libopencm3/stm32/gpio.h>
#include <libopencm3/cm3/nvic.h>

#include <ctype.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h> 
#include <strings.h> 

#include "usbcdc.h"
#include "common.h"

/* Line of user input */
char buffer[40];

/* Prompt user and get a line of input */
static void prompt(void)
{
    usb_printf("? ");        
    usb_getline(buffer,sizeof(buffer));
}

/* Main program (obviously) */
void adventure(void *arg __attribute__((unused)))
{
	int i = 0;
    usb_getc();     // Wait for user to start
	while (1) {
        usb_printf(">> [%d] <<%s>>\n",++i,buffer);
		prompt();
	}
}
