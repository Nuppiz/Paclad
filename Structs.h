#ifndef STRUCTS_H
#define STRUCTS_H

#define KB_ARRAY_LENGTH     256
#define KB_QUEUE_LENGTH     256

typedef struct
{
    float x, y;
} Vec2;

typedef struct
{
    uint8_t r,g,b;
} Color_t;

typedef struct
{
    Color_t colors[256];
} Palette_t;

typedef struct
{
    uint8_t keycode;
    uint8_t type;
    uint32_t time;
} KeyEvent_t;

typedef struct
{
    KeyEvent_t queue[KB_QUEUE_LENGTH];
    uint8_t keystates[KB_ARRAY_LENGTH];
    uint8_t queue_head;
    uint8_t queue_tail;
} Keyboard_t;

typedef struct
{
    Vec2 pos;
    Vec2 vel;
    uint8_t launched;
} Ball_t;

#endif /* STRUCTS_H */
