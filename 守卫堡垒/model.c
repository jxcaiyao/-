#include"all.h"

int random(int m, int n)
{
	int randnum;
	int i;
	srand((unsigned)time(NULL));
	for (i = 0; i < 5; i++) {
		//srand((unsigned)time(NULL));
		srand(rand() * (unsigned)time(NULL));
	}
	randnum = rand() % (n - m + 1) + m;
	return randnum;
}

const LIMIT PLANEX = { 0, 1 };
const LIMIT PLANEY = { HEIGHT / 10, 4 * HEIGHT / 10 };
const LIMIT PLANEVX = { WIDTH / 12, WIDTH / 8 };
const LIMIT PLANEVY = { 0, 0 };

void addPlane(planeList *pList)
{
	Plane *pl;
	pl = (Plane*)malloc(sizeof(Plane));
	pl->p.x = random((int)PLANEX.FLOOR, (int)PLANEX.CEIL) * WIDTH;
	pl->p.y = random((int)PLANEY.FLOOR, (int)PLANEY.CEIL);
	pl->v.vx = random((int)PLANEVX.FLOOR, (int)PLANEVX.CEIL);
	if (pl->p.x > 0) {
		pl->v.vx = -pl->v.vx;
	}
	pl->v.vy = random((int)PLANEVY.FLOOR, (int)PLANEVY.CEIL);
	pl->next = NULL;
	if (pList->head) {
		pl->last = pList->tail;
		pList->tail = pList->tail->next = pl;
	}
	else {
		pList->head = pList->tail = pl;
		pList->head->last = NULL;
	}
}

void changePlane(planeList *pList)
{
	Plane *pl = pList->head;
	while (pl) {
		pl->p.x += pl->v.vx * INTERVAL / 1000;
		pl->p.y += pl->v.vy * INTERVAL / 1000;
		if (pl->p.x > WIDTH || pl->p.x < 0) {
			deletePlane(pList, &pl);
		}
		else {
			pl = pl->next;
		}
	}
}

void deletePlane(planeList *pList, Plane **pl)
{
	if ((*pl)->last) {
		if ((*pl)->next) {
			(*pl)->last->next = (*pl)->next;
			(*pl)->next->last = (*pl)->last;
		}
		else {
			(*pl)->last->next = (*pl)->next;
			pList->tail = (*pl)->last;
		}
	}
	else if((*pl)->next){
		(*pl)->next->last = (*pl)->last;
		pList->head = (*pl)->next;
	}
	else {
		pList->head = pList->tail = NULL;
	}
	//*pl = (*pl)->next;
	Plane *temp;
	temp = (*pl)->next;
	free(*pl);
	*pl = temp;
}

void freePlane(planeList *pList)
{
	Plane *p, *q;
	for (p = pList->head; p; p = q) {
		q = p->next;
		free(p);
	}
}

const int BOMBV = WIDTH / 10;
const int BOMBD = 10;

void addBomb(bombList *bList, Point p)
{
	Bomb *bo;
	bo = (Bomb*)malloc(sizeof(Bomb));
	bo->p.x = p.x;
	bo->p.y = p.y;
	
	double a;
	a = atan((BATTERYX - (double)p.x) / (BATTERYY - (double)p.y));
	//beginPaint();
	//setPenWidth(5);
	//line(bo->p.x, bo->p.y, BATTERYX, BATTERYY);
	//endPaint();
	bo->v.vx = /*(int)*/(BOMBV * sin(a));
	bo->v.vy = /*(int)*/(BOMBV * cos(a));
	
	bo->next = NULL;
	if (bList->head) {
		bo->last = bList->tail;
		bList->tail = bList->tail->next = bo;
	}
	else {
		bList->head = bList->tail = bo;
		bList->head->last = NULL;
	}
}

void changeBomb(bombList *bList)
{
	Bomb *bo = bList->head;
	while (bo) {
		bo->p.x += bo->v.vx * INTERVAL / 1000;
		bo->p.y += bo->v.vy * INTERVAL / 1000;
		bo = bo->next;
	}
}

void deleteBomb(bombList *bList, Bomb **bo)
{
	if ((*bo)->last) {
		if ((*bo)->next) {
			(*bo)->last->next = (*bo)->next;
			(*bo)->next->last = (*bo)->last;
		}
		else {
			(*bo)->last->next = (*bo)->next;
			bList->tail = (*bo)->last;
		}
	}
	else if((*bo)->next){
		(*bo)->next->last = (*bo)->last;
		bList->head = (*bo)->next;
	}
	else {
		bList->head = bList->tail = NULL;
	}
	//*bo = (*bo)->next;
	Bomb *temp;
	temp = (*bo)->next;
	free(*bo);
	*bo = temp;
}

void freeBomb(bombList *bList)
{
	Bomb *p, *q;
	for (p = bList->head; p; p = q) {
		q = p->next;
		free(p);
	}
}

const int BULLETV = 300;
const int GRAVITY = 60;

void addBullet(bulletList *bList, double angle)
{
	Bullet *bu;
	bu = (Bullet*)malloc(sizeof(Bullet));
	bu->p.x = BATTERYX;
	bu->p.y = BATTERYY;
	bu->v.vx =  /*(int)*/(BULLETV * cos(angle));
	bu->v.vy = -/*(int)*/(BULLETV * sin(angle));
	bu->next = NULL;
	if (bList->head) {
		bu->last = bList->tail;
		bList->tail = bList->tail->next = bu;
	}
	else {
		bList->head = bList->tail = bu;
		bList->head->last = NULL;
	}
}

void changeBullet(bulletList *bList)
{
	Bullet *bu = bList->head;
	while (bu) {
		bu->p.x += bu->v.vx * INTERVAL / 1000;
		bu->p.y += bu->v.vy * INTERVAL / 1000;
		bu->v.vy += GRAVITY * INTERVAL / 1000;
		if (bu->p.x > WIDTH || bu->p.x < 0) {
			deleteBullet(bList, &bu);
		}
		else {
			bu = bu->next;
		}
	}
}

void deleteBullet(bulletList *bList, Bullet **bu)
{
	if ((*bu)->last) {
		if ((*bu)->next) {
			(*bu)->last->next = (*bu)->next;
			(*bu)->next->last = (*bu)->last;
		}
		else {
			(*bu)->last->next = (*bu)->next;
			bList->tail = (*bu)->last;
		}
	}
	else {
		(*bu)->next->last = (*bu)->last;
		bList->head = (*bu)->next;
	}
	Bullet* temp = (*bu)->next;
	free(*bu);
	*bu = temp;
}

void freeBullet(bulletList *bList)
{
	Bullet *p, *q;
	for (p = bList->head; p; p = q) {
		q = p->next;
		free(p);
	}
}

const int CRASHT = 500;

void addCrash(crashList *cList, Point p)
{
	Crash *cr;
	cr = (Crash*)malloc(sizeof(Crash));
	cr->p.x = p.x;
	cr->p.y = p.y;
	cr->time = CRASHT;
	cr->next = NULL;
	if (cList->head) {
		cr->last = cList->tail;
		cList->tail = cList->tail->next = cr;
	}
	else {
		cList->head = cList->tail = cr;
		cList->head->last = NULL;
	}
}

void changeCrash(crashList *cList)
{
	Crash *cr = cList->head;
	while (cr) {
		cr->time -= INTERVAL;
		if (cr->time <= 0) {
			deleteCrash(cList, &cr);
		}
		else {
			cr = cr->next;
		}
	}
}

void deleteCrash(crashList *cList, Crash **cr)
{
	if ((*cr)->last) {
		if ((*cr)->next) {
			(*cr)->last->next = (*cr)->next;
			(*cr)->next->last = (*cr)->last;
		}
		else {
			(*cr)->last->next = (*cr)->next;
			cList->tail = (*cr)->last;
		}
	}
	else if((*cr)->next){
		(*cr)->next->last = (*cr)->last;
		cList->head = (*cr)->next;
	}
	else {
		cList->head = cList->tail = NULL;
	}
	//*cr = (*cr)->next;
	Crash *temp = (*cr)->next;
	free(*cr);
	*cr = temp;
}

void freeCrash(crashList *cList)
{
	Crash *p, *q;
	for (p = cList->head; p; p = q) {
		q = p->next;
		free(p);
	}
}

const LIMIT BATTERYANGLE = { 20 * PI / 180, 70 * PI / 180 };

void changeBattery(Battery *ba, double dAngle)
{
	if (dAngle > 0 && ba->angle < BATTERYANGLE.CEIL) {
		ba->angle += dAngle;
	}
	else if (dAngle < 0 && ba->angle > BATTERYANGLE.FLOOR) {
		ba->angle += dAngle;
	}
}

void reductBattery(Battery *ba, int damage)
{
	if (ba->blood - damage > 0) {
		ba->blood -= damage;
	}
	else {
		ba->blood = 0;
	}
}

allObject allObj;

void model(void)
{
	initAll(&allObj);
}

void initAll(allObject *allObj)
{
	planeList *pll;
	bombList *bol;
	bulletList *bul;
	crashList *crl;
	Battery *bat;

	pll = (planeList*)malloc(sizeof(planeList));
	bol = (bombList*)malloc(sizeof(bombList));
	bul = (bulletList*)malloc(sizeof(bulletList));
	crl = (crashList*)malloc(sizeof(crashList));
	bat = (Battery*)malloc(sizeof(Battery));

	allObj->pll = pll;
	allObj->bol = bol;
	allObj->bul = bul;
	allObj->crl = crl;
	allObj->bat = bat;
	
	pll->head = pll->tail = NULL;
	bol->head = bol->tail = NULL;
	bul->head = bul->tail = NULL;
	crl->head = crl->tail = NULL;
	bat->p.x = BATTERYX;
	bat->p.y = BATTERYY;
	bat->blood = BATTERYB;
	bat->angle = PI / 2;
}

void changeAll(allObject *allObj)
{
	randPlane(allObj->pll);
	randBomb(allObj->bol, allObj->pll);
	changePlane(allObj->pll);
	changeBomb(allObj->bol);
	changeBullet(allObj->bul);
	changeCrash(allObj->crl);
}

int probability(double p)
{
	int ret = 0;
	if (random(0, 1000) <= 1000 * p) {
		ret = 1;
	}
	return ret;
}

//const double PLANEPROB = 0.1;

void randPlane(planeList *pList)
{
	static int i = 0;
	if (i == 0) {
			addPlane(pList);
			i = 3000 / INTERVAL;
	}
	else {
		i--;
	}
}

const double BOMBPROB = 0.1;

void randBomb(bombList *bList, planeList *pList)
{
	Plane *pl = pList->head;
	static int i = 0;
	if (i == 0) {
		while (pl) {
			if (probability(BOMBPROB)) {
				addBomb(bList, pl->p);
				i = 1000 / INTERVAL;
				//break;
			}
			pl = pl->next;
		}
	}
	else {
		i--;
	}
}

void decideCrash(allObject *allObj)
{
	PlBuCrash(allObj->pll, allObj->bul, allObj->crl);
	BoBuCrash(allObj->bol, allObj->bul, allObj->crl);
	BoBaCrash(allObj->bol, allObj->bat, allObj->crl);
}

void PlBuCrash(planeList *pList, bulletList *bList, crashList *cList)
{
	Bullet *bu = bList->head;
	while (bu) {
		Plane *pl = pList->head;
		while (pl) {
			if (PlBuCrashCondi(pl, bu)) {
				addCrash(cList, pl->p);
				deletePlane(pList, &pl);
				deleteBullet(bList, &bu);
				break;
			}
			else {
				pl = pl->next;
			}
		}
		bu = bu->next;
	}
}

int PlBuCrashCondi(Plane *pl, Bullet *bu)
{
	int ret = 0;
	if (sqrt(pow(pl->p.x - bu->p.x, 2) + pow(pl->p.y - bu->p.y, 2)) <= 20) {
		ret = 1;
	}
	return ret;
}

void BoBuCrash(bombList *boList, bulletList *buList, crashList *crList)
{
	Bullet *bu = buList->head;
	while (bu) {
		Bomb *bo = boList->head;
		while (bo) {
			if (BoBuCrashCondi(bo, bu)) {
				addCrash(crList, bo->p);
				deleteBomb(boList, &bo);
				deleteBullet(buList, &bu);
				break;
			}
			else {
				bo = bo->next;
			}
		}
		bu = bu->next;
	}
}

int BoBuCrashCondi(Bomb *bo, Bullet *bu)
{
	int ret = 0;
	if (sqrt(pow(bo->p.x - bu->p.x, 2) + pow(bo->p.y - bu->p.y, 2)) <= 40) {
		ret = 1;
	}
	return ret;
}

void BoBaCrash(bombList *boList, Battery *ba, crashList *crList)
{
	Bomb *bo = boList->head;
	while (bo) {
		if (BoBaCrashCondi(bo, ba)) {
			addCrash(crList, bo->p);
			deleteBomb(boList, &bo);
			reductBattery(ba, BOMBD);
		}
		else {
			bo = bo->next;
		}
	}
}

int BoBaCrashCondi(Bomb *bo, Battery *ba)
{
	int ret = 0;
	if (sqrt(pow(bo->p.x - ba->p.x, 2) + pow(bo->p.y - ba->p.y, 2)) <= 30) {
		ret = 1;
	}
	return ret;
}