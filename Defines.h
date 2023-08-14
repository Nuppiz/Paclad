#ifndef DEFINES_H
#define DEFINES_H

#define VIDEO_INT           0x10      /* the BIOS video interrupt. */
#define SET_MODE            0x00      /* BIOS func to set the video mode. */
#define VGA_256_COLOR_MODE  0x13      /* use to set 256-color mode. */
#define TEXT_MODE           0x03      /* use to set 80x25 text mode. */
#define PALETTE_WRITE       0x03C8
#define PALETTE_DATA        0x03C9

#define SCREEN_WIDTH        320       /* width in pixels of mode 0x13 */
#define SCREEN_HEIGHT       200       /* height in pixels of mode 0x13 */
#define SCREEN_SIZE         SCREEN_WIDTH * SCREEN_HEIGHT

#define SET_PIXEL(x,y,color) screen_buf[(y)*SCREEN_WIDTH + (x)] = color

#define KEYHANDLER_INT      9
#define KEY_HIT_FLAG        1
#define KEY_PRESSED_FLAG    2
#define KEY_RELEASED_FLAG   0x80 // 128, MSB
#define KEY_SPECIAL_CODE    0xE0 // 224
#define KEY_IS_PRESSED(k)   (Keyboard.keystates[k] & KEY_PRESSED_FLAG)
#define KEY_WAS_HIT(k)      (Keyboard.keystates[k] & KEY_HIT_FLAG)
#define KEY_WAS_RELEASED(k) (Keyboard.keystates[k] & KEY_RELEASED_FLAG)
#define KEY_WAS_TOGGLED(k)  (Keyboard.keystates[k] & (KEY_HIT_FLAG|KEY_RELEASED_FLAG))

#define BALL_LAUNCH_SPEED   30
#define GRAVITY             5
#define TERMINAL_VELOCITY   50

#define CONTROL_8253        0x43
#define CONTROL_WORD        0x3C
#define COUNTER_0           0x40
#define TIME_KEEPER_INT     0x1C 
#define TIMER_18HZ          0xFFFF
#define LOW_BYTE(n)         (n & 0x00ff)
#define HIGH_BYTE(n)        ((n>>8) & 0x00ff)
#define TIMER_1000HZ        1193

#define degToRad(degree)    (degree * (M_PI / 180.0))

#define FONT_FILE_SIZE      7128
#define CHARACTER_WIDTH     8
#define CHARACTER_HEIGHT    8
#define CHARACTER_SIZE      72
#define TRANSPARENT_COLOR   36

#define TRUE                1
#define FALSE               0

#endif /* DEFINES_H */