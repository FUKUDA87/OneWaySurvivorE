#include "CarDataManager.h"

int C_CarDataManager::GetDrawNum(int CarNo, bool SaveFlg)
{
	if (SaveFlg == true)LoadSaveDN(CarNo);
	return LoadDN(CarNo);
}

PARTSBASE C_CarDataManager::GetDrawSet(int CarNo, const int * DrawNo, bool SaveFlg)
{
	if (SaveFlg == true)LoadSaveDS(CarNo,DrawNo);
	return LoadDS(CarNo,DrawNo);
}

bool C_CarDataManager::DrawNumJudg(int CarNo)
{
	return false;
}

bool C_CarDataManager::DrawSetJudg(int CarNo, const int * DrawNo)
{
	return false;
}

