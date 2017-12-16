#ifndef __MODEL__
#define __MODEL__

#define INTERVAL 10

#define PI 3.1415926

#define BATTERYX (WIDTH/2)
#define BATTERYY (7*HEIGHT/8)
#define BATTERYB 100

typedef struct _point {
	double x;
	double y;
} Point;

typedef struct _velocity {
	double vx;
	double vy;
} Velocity;

typedef struct _plane {
	Point p;
	Velocity v;
	struct _plane *last;
	struct _plane *next;
} Plane;

typedef struct _planeList {
	Plane *head;
	Plane *tail;
} planeList;

typedef struct _bomb {
	Point p;
	Velocity v;
	struct _bomb *last;
	struct _bomb *next;
} Bomb;

typedef struct _bombList {
	Bomb *head;
	Bomb *tail;
} bombList;

typedef struct _soldier {
	Point p;
	Velocity v;
	struct _soldier *last;
	struct _soldier *next;
} Soldier;

typedef struct _soldierList {
	Soldier *head;
	Soldier *tail;
} soldierList;

typedef struct _battery {
	Point p;
	int blood;
	double angle;
} Battery;

typedef struct _bullet {
	Point p;
	Velocity v;
	struct _bullet *last;
	struct _bullet *next;
} Bullet;

typedef struct _bulletList {
	Bullet *head;
	Bullet *tail;
} bulletList;

typedef struct _crash {
	Point p;
	int time;
	struct _crash *last;
	struct _crash *next;
} Crash;

typedef struct _crashList {
	Crash *head;
	Crash *tail;
} crashList;

typedef struct _limit {
	double FLOOR;
	double CEIL;
} LIMIT;

typedef struct _allObject {
	planeList *pll;
	bombList *bol;
	bulletList *bul;
	crashList *crl;
	Battery *bat;
} allObject;

extern allObject allObj;

int random(int m, int n);
int sgn(double x);

void addPlane(planeList *pList);
void changePlane(planeList *pList);
void deletePlane(planeList *pList, Plane **pl);
void freePlane(planeList *pList);

void addBomb(bombList *bList, Point p);
void changeBomb(bombList *bList);
void deleteBomb(bombList *bList, Bomb **bo);
void freeBomb(bombList *bList);

void addBullet(bulletList *bList, double angle);
void changeBullet(bulletList *bList);
void deleteBullet(bulletList *bList, Bullet **bu);
void freeBullet(bulletList *bList);

void addCrash(crashList *cList, Point p);
void changeCrash(crashList *cList);
void deleteCrash(crashList *cList, Crash **cr);
void freeCrash(crashList *cList);

void changeBattery(Battery *ba, double dAngle);
void reductBattery(Battery *ba, int damage);

void model(void);
void initAll(allObject *allObj);
void changeAll(allObject *allObj);

int probability(double p);
void randPlane(planeList *pList);
void randBomb(bombList *bList, planeList *pList);

void decideCrash(allObject *allObj);
void PlBuCrash(planeList *pList, bulletList *bList, crashList *cList);
int PlBuCrashCondi(Plane *pl, Bullet *bu);
void BoBuCrash(bombList *boList, bulletList *buList, crashList *crList);
int BoBuCrashCondi(Bomb *bo, Bullet *bu);
void BoBaCrash(bombList *boList, Battery *ba, crashList *crList);
int BoBaCrashCondi(Bomb *bo, Battery *ba);

#endif