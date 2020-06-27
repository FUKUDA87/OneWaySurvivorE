#include "Effect_Base.h"

C_Effect_Base::~C_Effect_Base()
{
	Delete_ALL();
}

void C_Effect_Base::Set_MoveVec(const D3DXVECTOR3 * MoveVec)
{
	if (M_Draw.size() < 1)return;

	for (auto && d : M_Draw)d->Set_MoveVec(MoveVec);
	
}

void C_Effect_Base::Draw(const D3DXVECTOR3 * CameraPos)
{
	if (M_Draw.size() < 1)return;

	for (auto && d : M_Draw) d->Draw3D(CameraPos);
}

bool C_Effect_Base::Update(void)
{
	if (M_Draw.size() < 1)return false;

	for (unsigned int d = 0; d < M_Draw.size();d++) {
		if (M_Draw[d]->Update() != true) {
			delete M_Draw[d];
			M_Draw.erase(M_Draw.begin() + d);
			d--;
		}
	}

	return Delete_Flg();
}

void C_Effect_Base::Delete_ALL(void)
{
	if (M_Draw.size() <1)return;

	for (unsigned int d = 0; d < M_Draw.size(); d++) {
		delete M_Draw[d];
		M_Draw.erase(M_Draw.begin() + d);
		d--;
	}

}

bool C_Effect_Base::Delete_Flg(void)
{
	if (M_Draw.size() > 0)return true;

	return false;
}
