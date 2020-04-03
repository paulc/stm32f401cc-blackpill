/* Simple LED task demo, using timed delays:
 *
 * The LED on PC13 is toggled in task1.
 */
#include "FreeRTOS.h"
#include "task.h"

#include <libopencm3/stm32/rcc.h>
#include <libopencm3/stm32/gpio.h>

// FreeRTOS Hooks
extern void vApplicationStackOverflowHook(xTaskHandle *pxTask, signed portCHAR *pcTaskName);
extern void vApplicationIdleHook(xTaskHandle *pxTask, signed portCHAR *pcTaskName);

void vApplicationStackOverflowHook(xTaskHandle *pxTask __attribute((unused)), signed portCHAR *pcTaskName __attribute((unused))) {
    for (;;) {
    }
}

void vApplicationIdleHook(xTaskHandle *pxTask __attribute((unused)), signed portCHAR *pcTaskName __attribute((unused))) {
}

// GPIO Pin
struct pin {
    uint32_t gpioport;
    uint16_t gpios;
};

struct blink_params {
    struct pin p;
    int ms;
};

static void gpio_setup(struct pin p) {
    gpio_mode_setup(p.gpioport, GPIO_MODE_OUTPUT, GPIO_PUPD_NONE, p.gpios);
}

//static void led_on(struct pin p) {
//    gpio_clear(p.gpioport,p.gpios);	/* LED on */
//}
//
//static void led_off(struct pin p) {
//    gpio_set(p.gpioport,p.gpios);	/* LED on */
//}

static void led_toggle(struct pin p) {
    gpio_toggle(p.gpioport,p.gpios);	/* LED on */
}

static inline void sleep_ms(int ms) {
    vTaskDelay(pdMS_TO_TICKS(ms));
}

//static void blink(struct pin p, int on, int count) {
//    while (count--) {
//        led_on(p);
//        sleep_ms(on);
//        led_off(p);
//        sleep_ms(on);
//    }
//}

static void led_task(void *args) {
    struct blink_params *bp = (struct blink_params *) args;
    for (;;) {
        led_toggle(bp->p);
        sleep_ms(bp->ms);
    }
}

struct pin p1 = {GPIOC,GPIO13};
struct pin p2 = {GPIOB,GPIO9};
struct blink_params bp1 = {{GPIOC,GPIO13},500};
struct blink_params bp2 = {{GPIOB,GPIO9},2500};

int main(void) {

    // Setup clocks
    rcc_clock_setup_pll(&rcc_hse_25mhz_3v3[RCC_CLOCK_3V3_84MHZ]);
    rcc_periph_clock_enable(RCC_GPIOB);
    rcc_periph_clock_enable(RCC_GPIOC);

    // Setup GPIO
    gpio_setup(p1);
    gpio_setup(p2);

    // Create Tasks
	xTaskCreate(led_task, "LED_A", 200, &bp1, configMAX_PRIORITIES-1, NULL);
	xTaskCreate(led_task, "LED_B", 200, &bp2, configMAX_PRIORITIES-1, NULL);
	vTaskStartScheduler();

	for (;;) {
    }
	return 0;
}

