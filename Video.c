#include "Common.h"

uint8_t *VGA=(uint8_t *)0xA0000000L;        /* this points to video memory. */
uint8_t far screen_buf [64000];             // Double screen buffer

void setVideoMode(uint8_t mode)
{
    union REGS regs;

    regs.h.ah = SET_MODE;
    regs.h.al = mode;
    int86(VIDEO_INT, &regs, &regs);
}

// loads the palette from a 256-colour bitmap file
void loadPalette(char* filename, Palette_t* pal)
{
    FILE *fp;
    int i;
	int x;
    
    // Open the file
    fp = fopen(filename, "rb");
    
    // skip forward and read the number of colours
    fseek(fp, 0x0036, SEEK_SET);
    
    // load palette
    for (i = 0; i < 256; i++)
    {
        uint8_t r,g,b;
        // VGA palette values only go up to 6 bits, (2 ^ 6 == 64 different shades)
        // while bitmap palettes go up to 8 bits, (2 ^ 8 == 256 different shades)
        // right shift (>>) the bits by two places so an 8-bit value becomes a 6-bit
        // this divides the shade value (0-255) by four, giving a value between 0-63
  
        pal->colors[i].b = fgetc(fp);
        pal->colors[i].g = fgetc(fp);
        pal->colors[i].r = fgetc(fp);

        fgetc(fp); // discarded  value
    }

    fclose(fp);
}

void setPalette_VGA(Palette_t* pal)
{
    unsigned i;
    outportb(PALETTE_WRITE, 0);

    for (i = 0; i < 256; i++)
    {
       outportb(PALETTE_DATA, (pal->colors[i].r>>2));
       outportb(PALETTE_DATA, (pal->colors[i].g>>2));
       outportb(PALETTE_DATA, (pal->colors[i].b>>2));
    }
}

void render()
{     
    // copy off-screen buffer to VGA memory
    memcpy(VGA, screen_buf, SCREEN_SIZE);

    // clear off-screen buffer so the screen updates properly
    _fmemset(screen_buf, 0, SCREEN_SIZE);
}