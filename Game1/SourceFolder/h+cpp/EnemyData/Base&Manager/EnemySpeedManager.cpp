#include "EnemySpeedManager.h"

Speed * C_EnemySpeedManager::GetEnemySpeed(int EnemyNo)
{
	//No1
	if (EnemyNo == EnemyNo1)return new SpeedUp1();
	//No101
	if (EnemyNo == EnemyBossNo101)return new C_EnemySpeedNo201();

	//ŒŸõ‚Éˆø‚Á‚©‚©‚ç‚È‚¢
	return new SpeedUp1();
}
