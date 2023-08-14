#include "Common.h"

extern uint8_t far screen_buf [];
extern Ball_t Pallura;

void drawMaths()
{
    char pos_x_str[30];
    char pos_y_str[30];
    char vel_x_str[30];
    char vel_y_str[30];

    sprintf(pos_x_str, "POS_X: %f", Pallura.pos.x);
    sprintf(pos_y_str, "POS_Y: %f", Pallura.pos.y);
    sprintf(vel_x_str, "VEL_X: %f", Pallura.vel.x);
    sprintf(vel_y_str, "VEL_Y: %f", Pallura.vel.y);

    drawText(1, 1, pos_x_str, 15);
    drawText(1, 11, pos_y_str, 15);
    drawText(1, 21, vel_x_str, 15);
    drawText(1, 31, vel_y_str, 15);
}

void drawOctants(int center_x, int offset_x, int center_y, int offset_y, uint8_t color)
{
    SET_PIXEL(center_x + offset_x, center_y + offset_y, color); // lower right octant
    SET_PIXEL(center_x - offset_x, center_y + offset_y, color); // lower left octant
    SET_PIXEL(center_x + offset_x, center_y - offset_y, color); // upper right octant
    SET_PIXEL(center_x - offset_x, center_y - offset_y, color); // upper left octant
    SET_PIXEL(center_x + offset_y, center_y + offset_x, color); // bottom right octant
    SET_PIXEL(center_x - offset_y, center_y + offset_x, color); // bottom left octant
    SET_PIXEL(center_x + offset_y, center_y - offset_x, color); // top right octant
    SET_PIXEL(center_x - offset_y, center_y - offset_x, color); // top left octant   
}

void drawCircle(Vec2 position, int radius, uint8_t color)
{
    int offset_x;
    int offset_y;

    offset_y = 0;

    do
    {
        offset_x = sqrt((float)radius*radius - (float)offset_y*offset_y);
        drawOctants(position.x, offset_x, position.y, offset_y, color);
        offset_y++;
    }
    while (offset_y < offset_x);
}

void drawStuff()
{
    drawCircle(Pallura.pos, 10, 5);
    render();
}