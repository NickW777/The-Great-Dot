#include <3ds.h>
#include <stdio.h>
#include <citro3d.h>
#include <citro2d.h>
#include <string.h>
#include <stdlib.h>
#include <math.h>

#define PI 3.14159265
int getXSpeed (int dx, int xSpeed)
{
    // Set Horizontal Movement Speed
    if (dx > 20) {
        xSpeed = 1;
    } else if (dx < -20) {
        xSpeed = -1;
    } else {
        xSpeed = 0;
    } 
    return xSpeed;
}

int getYSpeed (int dy, int ySpeed)
{
    // Set Horizontal Movement Speed
    if (dy > 20) {
        ySpeed = -1;
    } else if (dy < -20) {
        ySpeed = 1;
    } else {
        ySpeed = 0;
    } 
    return ySpeed;
}

int getXCoord (int xSpeed, int xCoord)
{ 
    // Change the X Coordinate of the Player
    xCoord = xCoord + xSpeed;
    return xCoord;
}

int getYCoord (int ySpeed, int yCoord)
{
    // Change the Y Coordinate of the Player
    yCoord = yCoord + ySpeed;
    return yCoord;
}

int getTouchXDiff (int stylusX, int centerX)
{
    s16 diffX;
    diffX = stylusX - centerX;
    return diffX;
}

int getTouchYDiff (int stylusY, int centerY)
{
    s16 diffY;
    diffY = stylusY - centerY;
    return diffY;
}

int trsltLowX (int lowX)
{
    s16 topX = lowX * 1.25;
    return topX;
}

int trsltLowY (int lowY)
{
    s16 topY = lowY;
    return topY;
}

int calcBarrelX4 (float angle, int width, int length, int x)
{
    s16 xDist;
    s16 barrelX4;
    float endAngle;
    xDist = cos (angle) * length;
    endAngle = (PI / 2 - angle);
    barrelX4 = xDist + x + (cos (endAngle) * (width / 2)); 
    return barrelX4;
}

int calcBarrelY4 (float angle, int width, int length, int y)
{
    s16 yDist;
    s16 barrelY4;
    float endAngle;
    yDist = sin(angle) * length;
    endAngle = (PI / 2 - angle);
    barrelY4 = y - yDist + (sin(endAngle) * (width / 2));
    return barrelY4;
}

int calcBarrelX2 (float angle, int width, int length, int x)
{
    s16 xDist;
    s16 barrelX4;
    float endAngle;
    xDist = cos(angle) * length;
    endAngle = (PI / 2 - angle);
    barrelX4 = xDist + x - (cos(endAngle) * (width / 2)); 
    return barrelX4;
}
int calcBarrelY2 (float angle, int width, int length, int y)
{
    s16 yDist;
    s16 barrelY2;
    float endAngle;
    yDist = sin(angle) * length;
    endAngle = (PI / 2 + angle);
    barrelY2 = y - yDist - (sin(endAngle) * (width / 2));
    return barrelY2;
}

int calcBarrelX3 (float angle, int width, int x)
{
    s16 barrelX3;
    float endAngle;
    endAngle = (PI / 2 - angle);
    barrelX3 = x + (cos(endAngle) * (width / 2));
    return barrelX3;
}

int calcBarrelY3 (float angle, int width, int y)
{
    s16 barrelY3;
    float endAngle;
    endAngle = (PI / 2 - angle);
    barrelY3 = y + (sin(endAngle) * (width / 2));
    return barrelY3;
}
    
int calcBarrelX1 (float angle, int width, int x)
{
    s16 barrelX1;
    float endAngle;
    endAngle = (PI / 2 - angle);
    barrelX1 = x - (cos(endAngle) * (width / 2));
    return barrelX1;
}
int calcBarrelY1 (float angle, int width, int y)
{
    s16 barrelY1;
    float endAngle;
    endAngle = (PI / 2 - angle);
    barrelY1 = y - (sin(endAngle) * (width / 2));
    return barrelY1;
}
