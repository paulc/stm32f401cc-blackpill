
#include <ctype.h>
#include <stdio.h>
#include <stdlib.h>
#include <stdarg.h>
#include <string.h> 
#include <strings.h> 
#include <miniprintf.h>

#include "usbcdc.h"
#include "vt.h"

void vt_get_screensize(pos_t *pos) {
    char buf[16], *rows, *cols;
    pos->row = 0;
    pos->col = 0;
    while (pos->row == 0 || pos->col == 0) {
        // Returns ESC[rows;colsR
        usb_puts("\x1b[999;999H\x1b[6n");
        usb_getdelim('R',buf,sizeof(buf));
        rows = buf+2;
        cols = strchr(buf+2,';');
        *cols = 0;
        cols++;
        pos->row = atoi(rows);
        pos->col = atoi(cols);
    }
}

void vt_attr(vt_attr_t attr) {
    char buf[6];
    mini_snprintf(buf,sizeof(buf),"\x1b[%dm",attr);
    usb_puts(buf);
}

void vt_cls(void) {
    usb_puts("\x1b[2J");
}

void vt_clearline(void) {
    usb_puts("\x1b[2K");
}

void vt_printf(pos_t *pos, vt_attr_t attr,char *format,...) {
    char buf[160];
    va_list args;
    // Move cursor
    // XXX ROWS start at 1, COLS at 0
    mini_snprintf(buf,sizeof(buf),"\x1b[%d;%dH",pos->row,pos->col);
    usb_puts(buf);
    // Set attrs
    mini_snprintf(buf,sizeof(buf),"\x1b[%dm",attr);
    usb_puts(buf);
    // Print message
    va_start(args,format);
    mini_vsnprintf(buf,sizeof(buf),format,args);
    va_end(args);
    usb_puts(buf);
    // Reset attrs
    mini_snprintf(buf,sizeof(buf),"\x1b[%dm",RESET);
    usb_puts(buf);
}
