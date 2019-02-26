

#ifndef CHARCTRL_H
#define CHARCTRL_H

#include <3ds.h>
#include <stdio.h>
#include <citro3d.h>
#include <citro2d.h>
#include <string.h>
#include <stdlib.h>

int getXSpeed(int dx, int xSpeed);
int getYSpeed(int dy, int ySpeed);
int getXCoord(int xSpeed, int xCoord);
int getYCoord( int ySpeed, int yCoord);

#endif /* CHARCTRL_H */

