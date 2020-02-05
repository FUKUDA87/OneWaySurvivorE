#include "Car_Parts_Size.h"

C_Car_Parts_Size::~C_Car_Parts_Size()
{
	Delete_All_Parts_Size();
}

void C_Car_Parts_Size::New_Car_Parts_Size(const int TypeNo, const int JointNo, const D3DXVECTOR3 * ScalPos)
{
	M_Parts_Size.push_back(new C_Parts_Set_Size(&TypeNo, &JointNo, ScalPos));
}

void C_Car_Parts_Size::New_Car_Parts_Size(const int TypeNo, const int JointNo, const float Size)
{
	M_Parts_Size.push_back(new C_Parts_Set_Size(&TypeNo, &JointNo, &D3DXVECTOR3(Size,Size,Size)));
}

D3DXVECTOR3 C_Car_Parts_Size::Get_Car_Parts_Size(const S_PARTS_SET_DATA_No * No)
{
	if (M_Parts_Size.size() < 1)return D3DXVECTOR3(1.0f,1.0f,1.0f);
	
	for (auto && p : M_Parts_Size) {
		if (No->MeshTypeNo == p->Get_Data().No.MeshTypeNo) {
			if (No->MeshJointNo == p->Get_Data().No.MeshJointNo) {
				return p->Get_Data().ScalPos;
			}
		}
	}

	return D3DXVECTOR3(1.0f, 1.0f, 1.0f);
}

S_PARTS_SET_DATA_No C_Car_Parts_Size::Get_Data_No(const int TypeNo, const int JointNo)
{
	S_PARTS_SET_DATA_No No;
	No.MeshTypeNo = TypeNo;
	No.MeshJointNo = JointNo;
	return No;
}

void C_Car_Parts_Size::Delete_All_Parts_Size(void)
{
	if (M_Parts_Size.size() < 1)return;

	for (unsigned int p = 0; p < M_Parts_Size.size(); p++) {
		delete M_Parts_Size[p];
		M_Parts_Size.erase(M_Parts_Size.begin() + p);
		p--;
	}
}
