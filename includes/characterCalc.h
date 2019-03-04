

#ifndef CHARACTERCALC_H
#define CHARACTERCALC_H

#include <3ds.h>
#include <stdio.h>
#include <citro3d.h>
#include <citro2d.h>
#include <string.h>
#include <stdlib.h>
#include <math.h>

int getXSpeed (int dx, int xSpeed);
int getYSpeed (int dy, int ySpeed);
int getXCoord (int xSpeed, int xCoord);
int getYCoord (int ySpeed, int yCoord);
int getTouchXDiff (int stylusX, int centerX);
int getTouchYDiff (int stylusY, int centerY);
int trsltLowX (int lowX);
int trsltLowY (int lowY);
int calcBarrelX4 (float angle, int width, int length, int x);
int calcBarrelY4 (float angle, int width, int length, int y);
int calcBarrelX2 (float angle, int width, int length, int x);
int calcBarrelY2 (float angle, int width, int length, int y);
int calcBarrelX3 (float angle, int width, int x);
int calcBarrelY3 (float angle, int width, int y);
int calcBarrelX1 (float angle, int width, int x);
int calcBarrelY1 (float angle, int width, int y);
#endif /* CHARACTERCALC_H */

