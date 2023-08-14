#include "Common.h"
#include "Draw.h"
#include "Keylist.h"
#include "Keyb.h"
#include "Loadgfx.h"
#include "Text.h"
#include "Video.h"

int running = 1;
extern Keyboard_t Keyboard;

Ball_t Pallura = {{10.0, 170.0}, {0.0, 0.0}, FALSE};
uint32_t program_time;
static void interrupt (far *old_Timer_ISR)(void);

int launch_speed;
int launch_height;
int angle_input;
float launch_angle;

void interrupt far Timer(void)
{
    static long last_clock_time = 0;

    program_time++;

    // keeps the PC clock ticking in the background
    if (last_clock_time + 182 < program_time)
    {
        last_clock_time = program_time;
        old_Timer_ISR();
    }
}

void setTimer(uint16_t new_count)
{
    outportb(CONTROL_8253, CONTROL_WORD);
    outportb(COUNTER_0, LOW_BYTE(new_count));
    outportb(COUNTER_0, HIGH_BYTE(new_count));
}

void menu()
{
    printf("Enter launch angle:\n");
    scanf("%d", &angle_input);
    launch_angle = degToRad(angle_input);
    printf("Enter launch speed:\n");
    scanf("%d", &launch_speed);
    printf("Enter launch height:\n");
    scanf("%d", &launch_height);
    Pallura.pos.y = (SCREEN_HEIGHT - launch_height);
}

void launchBall()
{
    Pallura.launched = TRUE;
    Pallura.vel.y -= launch_speed * sin(launch_angle);
    Pallura.vel.x += launch_speed * cos(launch_angle);
}

void getInput()
{
    if (KEY_WAS_HIT(KEY_SPACEBAR) && Pallura.launched == FALSE)
        launchBall();
    else if (KEY_WAS_HIT(KEY_F10))
        running = 0;
}

void doPhysics()
{
    Pallura.pos.y += Pallura.vel.y;
    Pallura.pos.x += Pallura.vel.x;
    Pallura.vel.y += GRAVITY;

    if (Pallura.pos.y >= SCREEN_HEIGHT)
    {
        Pallura.vel.y = 0.0;
        Pallura.vel.x = 0.0;
        Pallura.launched = FALSE;
    }
}

int main()
{
    int update_interval = 1000 / 33;
    long last_update = 0;
    loadFont();
    menu();
    setVideoMode(VGA_256_COLOR_MODE);
    initKeyboard();
     old_Timer_ISR = _dos_getvect(TIME_KEEPER_INT);
    _dos_setvect(TIME_KEEPER_INT, Timer);
    setTimer(TIMER_1000HZ);
    

    while (running == 1)
    {
        if (last_update + update_interval < program_time)
        {
            drawSymbol(64,64,52,4);
            drawSymbol(73,64,55,4);
            drawSymbol(82,64,52,4);
            drawMaths();
            getInput();
            if (Pallura.launched == TRUE)
                doPhysics();
            drawStuff();
            clearKeys();
            last_update = program_time;
        }
    }
    setVideoMode(TEXT_MODE);
    deinitKeyboard();
    setTimer(TIMER_18HZ);
    _dos_setvect(TIME_KEEPER_INT, old_Timer_ISR);
    return 0;
}