#pragma once
#include"Spark.h"

class C_SparkDamage :public C_Spark {
public:
	C_SparkDamage(const D3DXMATRIX *Mat, const D3DXVECTOR3 *Pos);
	//�n��(0)�ƕ�(1,2)�Ǝ�(3)�ɒe�������������̉Ή�
	C_SparkDamage(const D3DXMATRIX *Mat, const D3DXVECTOR3 *Pos, const int *SparkFlg, const float *Ang);
	~C_SparkDamage();
	
	// �X�V����
	bool Update(void);

	// �\��
	void Draw3D(const D3DXVECTOR3 *CameraPos);
protected:
	//�A�b�v�f�[�g
	bool UpdateSD(void);
	bool UpdateCar(void);

	//�\��
	void DrawSD(const D3DXVECTOR3 *CameraPos);
private:
	//�ϐ�----------------------------------------------------------------------------------
	Pol Flash;
	//�ŏ������\��Flg
	bool DrawSDFlg;
	//�|���S���T�C�YSD
	float PolSizeSD;
	//Update�̎d��Flg
	bool UpdateFlg;
	//�֐�----------------------------------------------------------------------------------
	//�n�ʔ���
	void SparkJudgGround(const D3DXMATRIX *Mat, const D3DXVECTOR3 *Pos, const int *SparkFlg);
	//�ǔ���
	void SparkJudgWall(const D3DXMATRIX *Mat, const D3DXVECTOR3 *Pos, const int *SparkFlg);
	//�Ԕ���
	void SparkJudgCar(const D3DXMATRIX *Mat, const D3DXVECTOR3 *Pos, const int *SparkFlg, const float *Ang);
};