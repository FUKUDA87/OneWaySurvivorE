#include "EnemySpeedManager.h"

C_Speed_Update * C_EnemySpeedManager::GetEnemySpeed(const int * EnemyNo)
{
	switch (*EnemyNo)
	{
	case EnemyNo1:
		return new SpeedUp1();
		break;
	case EnemyBossNo101:
		return new C_Enemy101_Speed_1();
		break;
	default://�����Ɉ���������Ȃ���
		return new SpeedUp1();
		break;
	}

	//�����Ɉ���������Ȃ���
	return new SpeedUp1();
}
