#include"all.h"

void mouseEvent(int x, int y, int bt, int event)
{
	allObj.bat->p.x = x;
	allObj.bat->p.y = y;
	//int i;
	//if(bt == LEFT_BUTTON)
	//	for (i = 0; i <= 18; i++)
	//		addBullet(allObj.bul, i*PI / 9);
	return;
}

void KeyboardEvent(int key, int event)
{
	if (event != KEY_DOWN)
		return;
	Battery *ba = allObj.bat;
	bulletList *bList = allObj.bul;
	int i;
	static int j = 0;
	switch (key) {
	case VK_UP:
		ba->p.y -= 10;
		break;
	case VK_DOWN:
		ba->p.y += 10;
		break;
	case VK_LEFT:
		ba->p.x -= 10;
		break;
	case VK_RIGHT:
		ba->p.x += 10;
		break;
	case 'A':
		ba->angle += PI / 18;
		break;
	case 'D':
		ba->angle -= PI / 18;
		break;
	case ' ':
  		if (j == 120) {
  			j = 0;
		}
		//for (i = 1; i <= 8; i++) {
		//	addBullet(bList, i * PI / 4 + j * PI / 4 / 3);
		//}
		addBullet(bList, j * 21 * PI / 180);
		addBullet(bList, j * 21 * PI / 180 + 2 * PI / 3);
		addBullet(bList, j * 21 * PI / 180 + 4 * PI / 3);
		j++;
		break;
	}
}