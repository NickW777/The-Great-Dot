#include <3ds.h>
#include <stdio.h>
#include <citro3d.h>
#include <citro2d.h>
#include <string.h>
#include <stdlib.h>
#include <math.h>

#include "characterCalc.h"

#define SCREEN_WIDTH  400
#define SCREEN_HEIGHT 240

// Initialize the App
int main(int argc, char *argv[])
{
    

    gfxInitDefault();
    C3D_Init(C3D_DEFAULT_CMDBUF_SIZE);
    C2D_Init(C2D_DEFAULT_MAX_OBJECTS);
    C2D_Prepare();
    consoleInit(GFX_BOTTOM, NULL);

   
    C3D_RenderTarget* top = C2D_CreateScreenTarget(GFX_TOP, GFX_LEFT);
    
    // Initialize Colors
    u32 red = C2D_Color32(255, 0, 0, 255);
    u32 clrClear = C2D_Color32(255, 255, 255, 255);
    u32 gray = C2D_Color32(80,80,80,255);
    

    
    printf("\x1b[1;1HPress Start to exit.");
    printf("\x1b[10;15HMade by Nick Wierzbowski!");
    // Initialize Classes
    class entity {
        public:
        s8 xSpeed;
        s8 ySpeed;
        s16 xCoord;
        s16 yCoord;
        s8 bDiameter;
    };
    // Initialize Objects
    entity player;
    circlePosition pos;
    touchPosition touch;
    // Initialize Variables
    player.xSpeed = 0;
    player.ySpeed = 0;
    player.xCoord = 100;
    player.yCoord = 20;
    player.bDiameter = 40;
    
    // Begin Main Loop
    while (aptMainLoop())
    {
        
        hidScanInput();
        hidCircleRead(&pos);
        hidTouchRead(&touch);
        u32 kDown = hidKeysDown();
        u32 kHeld = hidKeysHeld();
        u32 kUp = hidKeysUp();
        if (kDown & KEY_START) {
            break;
        }
        
        // Calculate Player
        player.xSpeed = getXSpeed(pos.dx, player.xSpeed);
        player.ySpeed = getYSpeed(pos.dy, player.ySpeed);
        player.xCoord = getXCoord(player.xSpeed, player.xCoord);
        player.yCoord = getYCoord(player.ySpeed, player.yCoord);
        
        // Clear the console
        consoleClear();
        // Print: Press Start to Exit
        printf("\x1b[2;1HPress Start to exit.");
        // Print: D-Pad Coordinates
        printf("\x1b[3;1HD-Pad Coordinates: xxxx, yyyy");
        printf("\x1b[4;1H%04d; %04d", pos.dx, pos.dy);
        // Print: Player Coordinates
        printf("\x1b[5;1HPlayer Coordinates:  xxxx, yyyy");
        printf("\x1b[6;1H%04d; %04d", player.xCoord, player.yCoord);
        // Print: Player Speed
        printf("\x1b[7;1HPlayer Speed: xxxx, yyyy");
        printf("\x1b[8;1H%04d; %04d", player.xSpeed, player.ySpeed);
        
        
        
        C3D_FrameBegin(C3D_FRAME_SYNCDRAW);
        // Clear Top Screen
	C2D_TargetClear(top, clrClear);
        // Begin Rendering Top Screen
	C2D_SceneBegin(top);
        C2D_DrawTriangle(
            player.xCoord + 10, player.yCoord - 20, gray,
            player.xCoord + 30, player.yCoord - 20, gray,
            player.xCoord + 10, player.yCoord + 20, gray,
            0);
        C2D_DrawTriangle(
            player.xCoord + 30, player.yCoord + 20, gray,
            player.xCoord + 30, player.yCoord - 20, gray,
            player.xCoord + 10, player.yCoord + 20, gray,
            0);
        C2D_DrawEllipseSolid(player.xCoord, player.yCoord, 0, player.bDiameter, player.bDiameter, red);
        
        // End the Frame
	C3D_FrameEnd(0);


	//Wait for VBlank
	gspWaitForVBlank();
    }
    C2D_Fini();
    C3D_Fini();
    gfxExit();
    return 0;
}
