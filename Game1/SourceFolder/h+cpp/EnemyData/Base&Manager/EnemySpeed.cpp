#include "EnemySpeed.h"

bool Speed::CountUpdate(void)
{
	if (CountDownNow <= 0) {
		CountDownNow = CountDown;
	}
	CountDownNow -= 1;
	if (CountDownNow <= 0)return false;
	return true;
}
