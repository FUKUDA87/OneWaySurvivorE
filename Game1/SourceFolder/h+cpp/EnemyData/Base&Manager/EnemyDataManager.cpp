#include "EnemyDataManager.h"

C_EnemyDataBase * C_EnemyDataManager::GetEnemyData(const int * EnemyNo)
{
	/*ŒŸõ*/
	if (*EnemyNo == EnemyNo1)return new C_EnemyDataNo1();
	if (*EnemyNo == EnemyBossNo101)return new C_EnemyDataNo101();

	//ŒŸõ‚Éˆø‚Á‚©‚©‚ç‚È‚¢ê‡
	return new C_EnemyDataNo1();
}
