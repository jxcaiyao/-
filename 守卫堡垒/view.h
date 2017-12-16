#include"model.h"

#ifndef __VIEW__
#define __VIEW__

#define WIDTH 800
#define HEIGHT 600

void displayAll(allObject *allObj);
void displayBackground(void);
void displayPlane(planeList *pList);
void planeImg(Plane *pl);
void displayBomb(bombList *bList);
void bombImg(Bomb *bo);
void displayBattery(Battery *ba);
void batteryImg(Battery *ba);
void barrelImg(Battery *ba);
void displayCrash(crashList *cList);
void crashImg(Crash *cr);
void displayBullet(bulletList *bList);
void bulletImg(Bullet *bu);

#endif