/* usbcdcdemo.c : USBCDC Example (adventure)
 * Warren Gay
 */
#include <FreeRTOS.h>
#include <task.h>
#include <semphr.h>

#include <libopencm3/stm32/rcc.h>
#include <libopencm3/stm32/gpio.h>
#include <libopencm3/cm3/nvic.h>

#include "usbcdc.h"
#include "menu.h"
#include "blink.h"

int main(void) {

	rcc_clock_setup_in_hse_8mhz_out_72mhz();	// Use this for "blue pill"
	rcc_periph_clock_enable(RCC_GPIOC);
	gpio_set_mode(GPIOC,GPIO_MODE_OUTPUT_2_MHZ,GPIO_CNF_OUTPUT_PUSHPULL,GPIO13);

	usb_start();
    SemaphoreHandle_t sem_blink = xSemaphoreCreateMutex();

	xTaskCreate(blinker,"blinker",300,&sem_blink,configMAX_PRIORITIES-1,NULL);
	xTaskCreate(menu,"menu",300,&sem_blink,configMAX_PRIORITIES-1,NULL);

	vTaskStartScheduler();
	for (;;);
	return 0;
}

// End main.c
