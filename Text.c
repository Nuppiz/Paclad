#include "Common.h"

extern uint8_t far screen_buf [];
extern uint8_t alphabet[];

void drawSymbol(int x, int y, int symbol_index, uint8_t color)
{
    uint8_t index_x = 0;
    uint8_t index_y = 0;
    symbol_index = symbol_index * CHARACTER_SIZE; // pixel index of the symbol in the bitmap file

    for (index_y = 0; index_y < CHARACTER_HEIGHT;index_y++)
    {
        for (index_x = 0; index_x < CHARACTER_WIDTH; index_x++)
        {
            if (alphabet[symbol_index] != TRANSPARENT_COLOR)
            {
                SET_PIXEL(x, y, alphabet[symbol_index] + color);
                symbol_index++;
                x++;
            }
            else
            {
                symbol_index++;
                x++;
            }
        }
        index_x = 0;
        x = x - CHARACTER_WIDTH;
        y++;
    }
    index_y = 0;
    symbol_index = 0;
}

void drawText(int x, int y, char* string, uint8_t color)
{
    int i = 0;
    int start_x = x;
    char c;
    
    while ((c = string[i++]) != 0)
    {
        if (c == '\n')
        {
            x = start_x;
            y += 10;
            continue;
        }
        drawSymbol(x, y, c - 24, color);
        x += 10;
    }
}