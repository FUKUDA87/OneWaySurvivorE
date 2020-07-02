#pragma once
#include<d3dx9.h>
#include"../Key/CMouse.h"
#include"../Ground/GroundManager.h"

#ifndef Camera_H
#define Camera_H


class Camera{
public:
	void Init();
	Camera();
	Camera(D3DXMATRIX PlayerMat);
	~Camera();
	//TPS�pUpdate
	virtual bool UpdateM(bool MouFlg);
	virtual bool UpdateM(bool MouFlg,C_Mouse *mouse);
	virtual bool Update(D3DXMATRIX mat);
	//�N�H�[�^�j�I���̃A�b�v�f�[�g
	virtual bool UpdateQua(const bool *KeyFlg,const D3DXMATRIX *PlayerMat);
	D3DXVECTOR3 GetLook();
	D3DXVECTOR3 GetPos();
	float GetSize(D3DXVECTOR3 Pos, D3DXVECTOR3 Look);
	float GetAngX() { return camAngX; };
	float GetAngY() { return camAngY; };
	D3DXVECTOR3 GetVec();
	//�J�����ʒu�����
	void SetCamPos(const D3DXVECTOR3 *Pos) {
		camPos = *Pos;
	}
	void SetAngY(float y) {
		camAngY = y;
	}
	void SetAngX(float x) {
		camAngX = x;
	}

	//�J�����̍s��n��
	D3DXMATRIX GetMat(void);

	//�N�H�[�^�j�I���̃t���O�n��
	bool GetQuaFlg(void) {
		return QuaFlg;
	}

	//�N�H�[�^�j�I���̃Z�b�g
	void SetQuaMat(const D3DXMATRIX *EndQuaRotXMat, const D3DXMATRIX *EndQuaRotYMat, const float *QuaFrameUp);
	//X��]�n��
	D3DXMATRIX GetRotX(void) {
		return CamRotX;
	}
	//X��]����
	void SetRotX(const D3DXMATRIX *RotX) {
		CamRotX = *RotX;
	}
	//Y��]�n��
	D3DXMATRIX GetRotY(void) {
		return CamRotY;
	}
	//Y��]����
	void SetRotY(const D3DXMATRIX *RotY) {
		CamRotY = *RotY;
	}
	void RotXJudg(const D3DXMATRIX *PlayerMat);

	// �ǂƓ����蔻��
	void WallJudg(const int *RadF,c_GroundManager *groundManager);

protected:
	D3DXVECTOR3 camPos, camLook;
	float camAngY, camAngX;
	float camSize, Big, Small;
	D3DXMATRIX CamMat,CamRotX,CamRotY;
	//�O���Ɍ����N�H�[�^�j�I��
	float Anime, FrameUp;
	bool QuaFlg;
	D3DXMATRIX StartRotXMat,EndRotXMat, StartRotYMat, EndRotYMat;
	//�}�E�X�̃C���N�������gFlg
	bool IncFlg;

private:
	// �J�������Ԑ��ʂɌ����鏈��
	void InitCarCameraMove(const bool *KeyFlg, const D3DXMATRIX *PlayerMat);
};

#endif // !Camera_H
