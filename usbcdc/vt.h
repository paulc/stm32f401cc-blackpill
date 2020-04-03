
typedef enum {
    RESET = 0,
    BRIGHT,
    DIM,
    UNDERSCORE,
    BLINK,
    REVERSE,
    HIDDEN,
    FG_BLACK = 30,
    FG_RED,
    FG_GREEN,
    FG_YELLOW,
    FG_BLUE,
    FG_MAGENTA,
    FG_CYAN,
    FG_WHITE,
    BG_BLACK = 40,
    BG_RED,
    BG_GREEN,
    BG_YELLOW,
    BG_BLUE,
    BG_MAGENTA,
    BG_CYAN,
    BG_WHITE
} vt_attr_t;

typedef struct {
    int row;
    int col;
} pos_t;

void vt_get_screensize(pos_t *pos);
void vt_attr(vt_attr_t attr);
void vt_cls(void);
void vt_clearline(void);
void vt_printf(pos_t *pos, vt_attr_t attr,char *format,...);
