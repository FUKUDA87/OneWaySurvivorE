#pragma once
#include<d3dx9.h>
#include"../../GameSource/Struct.h"

class C_Smog {
public:
	C_Smog(const D3DXMATRIX *Mat);
	C_Smog(const D3DXMATRIX *Mat,const S_Smog *H_Smog);
	~C_Smog();
	//������
	void Init();
	//�A�b�v�f�[�g
	virtual bool Update(void);
	//������
	bool CountUpdate(void);
	//�\��
	virtual void Draw3D(D3DXVECTOR3 CamPos);

	void Init_Num(void);

	int GetNum(void) {
		return M_S_Smog.Draw_No;
	}

	void NumJudg(void);

	void SetNum(const int s_Num);

	//�ʒu�̕␳
	void PosMoveVec(const D3DXVECTOR3*MoveVec);
protected:
	Pol smog;
	//�����폜�p
	int NowCount;
	//�g��p
	float ScalSize;

	//�ʒu�̕␳����
	bool MoveVecJudg(void);
	//�ړ��s��̏�����
	void Init_Mat(void);
private:
	//�\�����@�̍\����
	S_Smog M_S_Smog;

	//�ړ���
	bool MoveVecFlg;

	//�����x�̃A�b�v�f�[�g
	void Update_Alpha(void);
	//�����̐��l�쐬
	float RandPlus(const int *Num);
	//�|���S���T�C�Y�̕ω�
	float GetPolSize(void);

};