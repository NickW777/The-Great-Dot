#include <3ds.h>
#include <stdio.h>
#include <citro3d.h>
#include <citro2d.h>
#include <string.h>
#include <stdlib.h>
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
int getYCoord ( int ySpeed, int yCoord)
{
    // Change the Y Coordinate of the Player
    yCoord = yCoord + ySpeed;
    return yCoord;
}
