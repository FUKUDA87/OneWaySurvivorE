#include "StageCar.h"

StageCar::StageCar(const BODYDATA * Data):C_PlayerA(Data)
{
	D3DXMatrixTranslation(&Car.Base.Mat, 0.0f, 0.0f, 0.0f);
	Car.Con.NowSpeed = 0;
}

bool StageCar::UpdateAll(void)
{
	//�W���p�[�c�̃A�b�v�f�[�g
	Update_Car_Parts();
	//Update_Gun();

	return true;
}
