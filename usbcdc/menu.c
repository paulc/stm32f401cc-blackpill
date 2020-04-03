#include <FreeRTOS.h>
#include <task.h>
#include <semphr.h>

#include <libopencm3/stm32/rcc.h>
#include <libopencm3/stm32/gpio.h>
#include <libopencm3/cm3/nvic.h>

#include <ctype.h>
#include <stdio.h>
#include <stdlib.h>
#include <stdarg.h>
#include <string.h> 
#include <strings.h> 
#include <miniprintf.h>

#include "usbcdc.h"
#include "vt.h"
#include "menu.h"

void menu(void *args) {

    int c = 0;
    pos_t size,pos;
    //SemaphoreHandle_t sem_blink = *(SemaphoreHandle_t *)args; 
    //xSemaphoreTake(sem_blink,portMAX_DELAY);

    usb_getc();

    while (1) {
        vt_cls();
        vt_get_screensize(&size);

        pos.row = size.row;
        pos.col = 0;
        vt_printf(&pos,FG_BLUE|BG_YELLOW,">> Rows: %d Cols: %d",size.row,size.col);

        for (pos.col=0;pos.col<=size.col-10;pos.col+=10) {
            for (pos.row=1;pos.row<size.row;pos.row+=2) {
                vt_printf(&pos,FG_RED,"[%d,%d]",pos.row,pos.col);
            }
        }

        //usb_getline(buf,sizeof(buf));

        c = usb_waitc(5000);
    }
}

