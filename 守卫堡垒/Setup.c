#include"all.h"

int Setup(void)
{
	initWindow("��������", DEFAULT, DEFAULT, WIDTH, HEIGHT);
	
	registerTimerEvent(timerEvent);
	registerMouseEvent(mouseEvent);

	model();
	startTimer(0, INTERVAL);

	return 0;
}

void timerEvent(int tid)
{
	displayAll(&allObj);
	decideCrash(&allObj);
	changeAll(&allObj);
}