#include"all.h"

void displayAll(allObject *allObj)
{
	beginPaint();

	displayBackground();
	clearDevice();
	displayPlane(allObj->pll);
	displayBullet(allObj->bul);
	//displayBattery(allObj->bat);
	displayBomb(allObj->bol);
	displayCrash(allObj->crl);

	endPaint();
}

void displayBackground(void)
{
	setBrushColor(WHITE);
	setPenColor(BLACK);
	setPenWidth(3);
	rectangle(0, 0, WIDTH, HEIGHT);
}

void displayPlane(planeList *pList)
{
	Plane *pl = pList->head;
	while (pl) {
		planeImg(pl);
		pl = pl->next;
	}
}

void planeImg(Plane *pl)
{
	setBrushColor(BLACK);
	setPenColor(BLACK);
	setPenWidth(1);
	rectangle(pl->p.x - 15, pl->p.y - 10, pl->p.x + 15, pl->p.y + 10);
}

void displayBomb(bombList *bList)
{
	Bomb *bo = bList->head;
	while (bo) {
		bombImg(bo);
		bo = bo->next;
	}
}

void bombImg(Bomb *bo)
{
	setBrushColor(RED);
	setPenColor(BLACK);
	setPenWidth(3);
	ellipse(bo->p.x - 10, bo->p.y - 10, bo->p.x + 10, bo->p.y + 10);
}

void displayBattery(Battery *ba)
{
	//barrelImg(ba);
	batteryImg(ba);
}

void batteryImg(Battery *ba)
{
	setBrushColor(GREEN);
	setPenColor(BLACK);
	setPenWidth(3);
	rectangle(ba->p.x - 30, ba->p.y - 20, ba->p.x + 30, ba->p.y + 20);
}

const double BARRELL = 50;

void barrelImg(Battery *ba)
{
	//setBrushColor(GREEN);
	setPenColor(GREEN);
	setPenWidth(20);
	Point p;
	p.x = ba->p.x + BARRELL * cos(ba->angle);
	p.y = ba->p.y - BARRELL * sin(ba->angle);

	line(ba->p.x, ba->p.y, p.x, p.y);
}

void displayCrash(crashList *cList)
{
	Crash *cr = cList->head;
	while (cr) {
		crashImg(cr);
		cr = cr->next;
	}
}

void crashImg(Crash *cr)
{
	setBrushColor(YELLOW);
	setPenColor(MAGENTA);
	setPenWidth(3);
	ellipse(cr->p.x - 20, cr->p.y - 20, cr->p.x + 20, cr->p.y + 20);
}

void displayBullet(bulletList *bList)
{
	Bullet *bu = bList->head;
	while(bu) {
		bulletImg(bu);
		bu = bu->next;
	}
}

void bulletImg(Bullet *bu)
{
	setBrushColor(BLUE);
	setPenColor(CYAN);
	setPenWidth(3);
	ellipse(bu->p.x - 10, bu->p.y - 10, bu->p.x + 10, bu->p.y + 10);
}