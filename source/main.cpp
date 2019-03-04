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
#define PI 3.14159265

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
    
    // Initialize Classes
    class entity {
        public:
        s16 barrelX1;
        s16 barrelX2;
        s16 barrelX3;
        s16 barrelX4;
        s16 barrelY1;
        s16 barrelY2;
        s16 barrelY3;
        s16 barrelY4;
        s8 xSpeed;
        s8 ySpeed;
        s16 xCoord;
        s16 yCoord;
        s8 bDiameter;
        u8 barrelWidth;
        u8 barrelLength;
    };
    class lowscreen {
        public:
        s32 centerX;
        s32 centerY;
        s16 diffX;
        s16 diffY;
        float angle;
    };
    class target {
        public:
        s16 x;
        s16 y;
    };
    
    // Initialize Objects
    entity player;
    circlePosition pos;
    touchPosition touch;
    lowscreen lowscrn;
    target target;
    // Initialize Variables
    player.xCoord = 100;
    player.yCoord = 20;
    player.barrelX1 = player.xCoord - 10;
    player.barrelX2 = player.xCoord - 10;
    player.barrelX3 = player.xCoord + 10;
    player.barrelX4 = player.xCoord + 10;
    player.barrelY1 = player.yCoord;
    player.barrelY2 = player.yCoord - 40;
    player.barrelY3 = player.yCoord;
    player.barrelY4 = player.yCoord - 40;
    player.xSpeed = 0;
    player.ySpeed = 0;
    player.bDiameter = 40;
    player.barrelWidth = 20;
    player.barrelLength = 40;
    
    lowscrn.centerX = 160;
    lowscrn.centerY = 120;
    lowscrn.diffX = 0;
    lowscrn.diffY = 0;
    lowscrn.angle = 90;
    
    target.x = 0;
    target.y = 0;
    // Begin Main Loop
    while (aptMainLoop())
    {
        //Read User Input
        hidScanInput();
        hidCircleRead(&pos);
        hidTouchRead(&touch);
        
        // Set Key Variables
        u32 kDown = hidKeysDown();
        // u32 kHeld = hidKeysHeld();
        // u32 kUp = hidKeysUp();
        
        // Close Game if User Presses Start
        if (kDown & KEY_START) {
            break;
        }
        // Update Variables

        
        // Calculate User Aim Box
        target.x = trsltLowX(touch.px);
        target.y = trsltLowY(touch.py);
        
        // Calculate Angle of TouchScreen Stylus from Center in Degrees
        lowscrn.diffY = getTouchYDiff(target.y, player.yCoord);
        lowscrn.diffX = getTouchXDiff(target.x, player.xCoord);
        lowscrn.angle = -atan2(lowscrn.diffY, lowscrn.diffX);

        // Calculate User Tank Body Coordinates
        player.xSpeed = getXSpeed(pos.dx, player.xSpeed);
        player.ySpeed = getYSpeed(pos.dy, player.ySpeed);
        player.xCoord = getXCoord(player.xSpeed, player.xCoord);
        player.yCoord = getYCoord(player.ySpeed, player.yCoord);  
        player.barrelX1 = calcBarrelX1(lowscrn.angle, player.barrelWidth, player.xCoord);
        player.barrelX2 = calcBarrelX2(lowscrn.angle, player.barrelWidth, player.barrelLength, player.xCoord);
        player.barrelX3 = calcBarrelX3(lowscrn.angle, player.barrelWidth, player.xCoord);
        player.barrelX4 = calcBarrelX4(lowscrn.angle, player.barrelWidth, player.barrelLength, player.xCoord);
        player.barrelY1 = calcBarrelY1(lowscrn.angle, player.barrelWidth, player.yCoord);
        player.barrelY2 = calcBarrelY2(lowscrn.angle, player.barrelWidth, player.barrelLength, player.yCoord);
        player.barrelY3 = calcBarrelY3(lowscrn.angle, player.barrelWidth, player.yCoord);
        player.barrelY4 = calcBarrelY4(lowscrn.angle, player.barrelWidth, player.barrelLength, player.yCoord);
        
        // Clear the console
        consoleClear();
        // Print: Press Start to Exit
        printf("\x1b[2;1HPress Start to exit.");
        // Print: D-Pad Coordinates
        printf("\x1b[3;1HD-Pad Coordinates: ");
        printf("%04d; %04d", pos.dx, pos.dy);
        // Print: Player Coordinates
        printf("\x1b[5;1HPlayer Coordinates: ");
        printf("%04d; %04d", player.xCoord, player.yCoord);
        // Print: Player Speed
        printf("\x1b[7;1HPlayer Speed: ");
        printf("%04d; %04d", player.xSpeed, player.ySpeed);
        //Print: Touch Screen Coordinates
        printf("\x1b[9;1HTouch Screen position: ");
        printf("%03d; %03d", target.x, target.y);
        //Print: Differences
        printf("\x1b[10;1HDifferences: ");
        printf("%04d; %04d", lowscrn.diffX, lowscrn.diffY);
        //Print: Angle
        printf("\x1b[11;1HAngle: ");
        printf("%04f", lowscrn.angle  * 180 / PI);
        
        
        C3D_FrameBegin(C3D_FRAME_SYNCDRAW);
        // Clear Top Screen
	C2D_TargetClear(top, clrClear);
        // Begin Rendering Top Screen
	C2D_SceneBegin(top);
        C2D_DrawTriangle(
            player.barrelX2, player.barrelY2, gray,
            player.barrelX4, player.barrelY4, gray,
            player.barrelX1, player.barrelY1, gray,
            0);
        C2D_DrawTriangle(
            player.barrelX3, player.barrelY3, gray,
            player.barrelX4, player.barrelY4, gray,
            player.barrelX1, player.barrelY1, gray,
            0);
        C2D_DrawRectSolid(
            target.x - 10, target.y - 10, 0, 20, 20,
            red);
        C2D_DrawEllipseSolid(player.xCoord - player.bDiameter / 2, player.yCoord - player.bDiameter / 2, 0, player.bDiameter, player.bDiameter, red);
        
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
