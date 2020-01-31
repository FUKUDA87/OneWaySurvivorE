#pragma once
#include"Draw3D_Base2.h"
#include"../../Draw3DBase/Draw3DManager/MeshManager_Manager.h"

#include<string>


class C_Draw_Mesh_Base:public C_Draw3D_Base2 {
public:
	C_Draw_Mesh_Base();
	C_Draw_Mesh_Base(std::string FileName);

	//�\���֐�
	virtual void Draw3D(const D3DXVECTOR3 *CameraPos);

	//�ړ��ʂ̃Z�b�g
	virtual void Set_MoveVec(const D3DXVECTOR3 *MoveVec);

	//���b�V���n��
	LPD3DXMESH Get_Mesh(void);

	//�|���S���̒��_�n��
	D3DXVECTOR3 Get_Pol_Pos(const int *PosNo);

protected:

	/*�����o�[�ϐ�*/
	XFILE M_Mesh;

	////////////////////////////////////////////
	/*�����o�[�֐�*/
	///////////////////////////////////////////

	/*������*/
	void Init_Mesh(void);

	/*�\��*/
	void Mesh_Draw_No1(void);

	//���b�V���̃��[�h
	void Mesh_Load(std::string FileName);
	
private:
};