#include "EnemyParts.h"

C_EnemyParts::C_EnemyParts(const PARTS * InitGetParts, C_PartsMoveBase* GetMove, const int *MaxHp):C_PartsBase(InitGetParts)
{
	Move = GetMove;
	m_MaxHp = *MaxHp;
	InitHpFlg = true;
}

C_EnemyParts::~C_EnemyParts()
{
	if (Move != nullptr) {
		delete Move;
	}
}

bool C_EnemyParts::UpdateParts(const D3DXMATRIX * Mat, const D3DXVECTOR3 * ScalPos, int *Phase)
{
	ScalParts(ScalPos);

	if (Move != nullptr) {
		Move->Move(&Parts,Mat,&NowSpeed,&MaxSpeed,Phase);

		if ((Parts.HpLinkFlg == true) && (InitHpFlg == true)) {
			InitHpFlg = false;
			SetHp(&m_MaxHp);
			bool Flg = true;
			SetDamageFlg(&Flg);
		}
	}
	else {
		Parts.Base.Mat = *Mat;
	}
	return true;
}
