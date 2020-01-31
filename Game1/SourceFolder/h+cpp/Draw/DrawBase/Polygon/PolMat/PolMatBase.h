#pragma once
#include"../PolygonBase.h"

class C_PolMatBase:public C_PolygonBase {
public:
	C_PolMatBase();
	~C_PolMatBase();
	//�|���S���Ɉړ��ʂ̉��Z
	void SetMat_MoveVec(const D3DXVECTOR3* MoveVec);

	//�s��̂��炢��
	void SetMat_Mat(const D3DXMATRIX *Mat);
protected:
	//�|���S���Ǘ��̕ϐ�
	S_Pol M_Polygon;

	/*�֐�*/

	//null�`�F�b�N�ƃ|���S�����̃`�F�b�N(<=)
	bool PolMat_Judg(void);

	//null�`�F�b�N�ƃ|���S�����̃`�F�b�N(<=)
	bool PolMat_Judg(const int PolNum);

	//�\���|���S�����̍s��̕ύX
	void Init_PolMat(const int PolNum);
	//�|���S�����̍s��̍폜
	void Delete_PolMat(void);
	//�|���S�����̍s��ɒʏ�̍s�������
	void Init_PolMat_Mat(const D3DXMATRIX *Mat);

	int Get_PolMatNum(void) {
		return M_Polygon.PolNum;
	}
private:

};