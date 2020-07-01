#pragma once
#include"../../GameSource/Struct.h"
#include<string>

class C_Object_Base {
public:
	C_Object_Base();
	//�\��
	virtual void Draw(void);

	//�\���s��̍X�V
	virtual void Update_DrawMat(const D3DXMATRIX *Mat);

	//���n��
	S_Base3D_2 Get_Data(void) {
		return M_Base;
	}

	//�\��Mesh�n��
	LPD3DXMESH Get_Mesh(void) {
		return M_Mesh.Mesh.lpMesh;
	}

	//�\��Flg�̃Z�b�g
	void Set_DrawFlg(const bool *Flg) {
		M_Base.Base.DrawFlg = *Flg;
	}

	//�s��̎�ޓn��
	unsigned int Get_Mat_No(void) {
		return M_Set_Mat_No;
	}

protected:
	//�\��Mesh
	XFILE_B M_Mesh;

	//�\���s��
	S_Base3D_2 M_Base;

	//�s��̑���̎��
	unsigned int M_Set_Mat_No;

	//���b�V���̃��[�h
	void Mesh_Load(std::string FileName);

	//������
	virtual void Init(void);

private:


};