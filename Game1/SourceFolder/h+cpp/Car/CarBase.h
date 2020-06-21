#pragma once
#include<d3dx9.h>
#include"../GameSource/Struct.h"
#include<vector>
#include"../Ground/Ground_Object.h"
#include"../Draw3DBase/Draw3DManager/CarMeshManager.h"
#include"../GameSource/CharaBase.h"
#include"../GameSource/Const.h"

class C_CarBase:public C_CharaBase {
public:
	C_CarBase();

	//������
	void InitCar(void);

	//�A�b�v�f�[�g
	virtual bool UpdateCar(void);
	//�O�i�A�b�v�f�[�g
	virtual bool UpdateCarFM(std::vector<C_Ground_Object*>ground);

	//3D�\��
	virtual void Draw3DCar(void);

	//�p�[�c�̈ʒu����
	virtual void SetParts(std::vector<C_Ground_Object*>ground);

	//==========================================
	//Get�ESet
	//==========================================

	//�ԑ̍s��n��
	D3DXMATRIX GetMatCar(void) {
		return Car.Base.Mat;
	}
	//�ԑ̍s�����
	void SetMatCar(const D3DXMATRIX *Mat) {
		Car.Base.Mat = *Mat;
	}
	//�Ԃ̕\���s��n��
	virtual D3DXMATRIX GetDrawMatCar(void) {
		return judg.GetDrawMat(&Car.Base.Mat, &Car.Base.Scal, &Car.Base.ScaPos);
	}
	//������n�ʂ�No����
	void SetGroNum(const unsigned int *GroundNo) {
		Car.Con.GroNum = *GroundNo; 
	};
	
	//���S�m�F(true�Ŏ�)
	bool Dead(void);

	//����Hp����
	virtual bool SetHP(int Damage);

	//����Hp����(�ǂƒe�̋�ʕt)
	virtual bool SetHP(int Damage,bool WallFlg);

	//�Ԃ̃��f���n��
	LPD3DXMESH GetMeshCar() {
		return Car.Mesh.lpMesh;
	}
	//�Ԃ̑���Flg�n��
	bool GetFlgCar(void) {
		return Car.Base.Flg;
	}
	//�Ԃ̑���Flg����
	void SetFlgCar(const bool *Flg) {
		Car.Base.Flg=*Flg;
	}
	//�����蔻��̔��a�n��
	float GetBodRadCar(void) {
		return Car.Base.BodRad;
	}
	
	//player��TransMat�n��
	D3DXMATRIX GetTransMatCar(void) {
		return Car.Base.Trans;
	}
	//player��TransMat����
	void SetTransMatCar(const D3DXMATRIX *TransMat) {
		Car.Base.Trans = *TransMat;
	}
	//�R���W�������f���n��
	LPD3DXMESH GetColMod(void) {
		return Car.Con.ColModMesh.lpMesh;
	}
	//�ړ��̏��n��
	CONSTITUTION GetCon(void) {
		return Car.Con;
	}
	
	//�X�s�[�h����
	void SetSpeedCar(const D3DXVECTOR3 *spe) {
		Car.Con.Speed = *spe;
	}
	
	//�X�s�[�h����
	void SetNowSpeedCar(int spe) {
		Car.Con.NowSpeed = spe;
	}


	//�Փ˔���̏�Ԃ̓n��
	int Get_JudgeType(void) {
		return M_JudgeType;
	}

	//�e�o��������
	void SetBPos(D3DXVECTOR3 RayPos, bool RayJudgFlg);

	//player���
	CHARAData GetData(void);

	//�g��n��
	D3DXVECTOR3 GetScalPosCar(void) {
		return Car.Base.ScaPos;
	}

	//�O�i����p�֐�-----------------------------------------------
	//�ړ��̏���n��
	QuaForMove GetQuaForMove(void);
	//�ړ��x�N�g���̒�������
	void SetQuaVecSize(const float *size) {
		CarFM.SpeedMulJudg = *size;
	}
	//�O�i����p�̈ړ��x�N�g���n��
	D3DXVECTOR3 GetForMoveVec(const int *i) {
		return ForMoveVec[*i];
	}
	//�O�i����p�̈ړ��x�N�g������
	void SetForMoveVec(const D3DXVECTOR3 *Vec,const int *i) {
		ForMoveVec[*i] = *Vec;
	}
	//�O�i����p�̈ړ���Mat�n��
	D3DXMATRIX GetForMoveEndMat(void) {
		return ForMoveEndMat;
	}
	//�O�i����p�̈ړ���Mat����
	void SetForMoveEndMat(const D3DXMATRIX *Mat) {
		ForMoveEndMat = *Mat;
	}

	//���G�A�b�v�f�[�g
	bool UpdateCountM(void);

	//���쐬�ɕK�v�ȏ��̎擾�ƃA�b�v�f�[�g
	virtual void GetPos2DSet(const D3DXMATRIX *mProj, const D3DXMATRIX *mView, const D3DVIEWPORT9 *Viewport) {};

	//�ړ��x�N�g���n��
	D3DXVECTOR3 GetMoveVec(void) {
		return brj.MoveVec;
	}

	//�O�̎Ԃ̈ʒu�̃Z�b�g
	void SetCarMoveMat(void) {
		PlaMovMat = Car.Base.Trans*Car.Con.JudgMat;
	}

	//�J�����̍s��̃Z�b�g
	virtual void Set_CameraMat(const D3DXMATRIX *CameraMat) {
		M_S_Gun_Update_Data.CameraMat = *CameraMat;
	}

	//����E����ł���܂ł̎��Ԃ̓n��
	int Get_Move_Stop_Time(void) {
		return MMove_Stop_Time;
	}

	//����E����ł���܂ł̎��Ԃ̓���
	void Set_Move_Stop_Time(const int *Time, const int *Speed);

	//�Ԃ̑���҂̓n��
	int Get_DriverNo(void) {
		return M_Driver;
	}

	/*�Փ˔���̏�Ԃ̊֐�*/

	//�Փ˔��肷�邱�Ƃ�������t���O�̓n��
	bool Get_CollisionJudg_TrueFlg(void) {
		return M_CollisionJudg_TrueFlg;
	}

	//�Փ˔��肷�邱�Ƃ�������t���O�̃Z�b�g
	void Set_CollisionJudg_TrueFlg(const bool *Flg) {
		M_CollisionJudg_TrueFlg = *Flg;
	}

	//�蓮�Ǝ����̑����������N���X
	S_GUN_UPDATE_DATA Get_Gun_Update_Data(void) {
		return M_S_Gun_Update_Data;
	}

protected:
	//�Ԃ̃f�[�^
	BODYDATA BodyData;

	//�Ԃ̃��f������
	void SetMeshCar(int MeshNo);

	//�Ԃ̏��
	CHARA3D Car;

	QuaForMove CarFM;

	D3DXMATRIX PlaMovMat;//player�̈ړ��O��Mat

	//�o���b�g�p
	BULLETRAYJUDG brj;

	Judg judg;

	//�蓮�Ǝ����̑����������N���X
	S_GUN_UPDATE_DATA M_S_Gun_Update_Data;

	//�Ԃ̑����
	int M_Driver;

	//�e�̏��̍X�V
	void Update_Gun_Data(void);

	//����E����ł���܂ł̎��Ԃ����炷�X�V�̏���
	void Update_Move_Stop_Time(void);

	//�e�̓����̒�~����
	bool Get_Stop_Flg(void);

	//�Փ˔���̏�Ԃ̃Z�b�g
	void Set_JudgeType(const int *Type) {
		M_JudgeType = *Type;
	}

private:
	//�Փ˔���̏��
	int M_JudgeType;

	//����E����ł���܂ł̎���
	int MMove_Stop_Time;

	//�Փ˔��肷�邱�Ƃ�������t���O
	bool M_CollisionJudg_TrueFlg;

	//�O�i�N�H�[�^�j�I���p
	D3DXMATRIX ForMoveEndMat;//�O�i��������Mat
	D3DXVECTOR3 ForMoveVec[3];//�ړ��O����ړ����Vec
	QuaForMove Q;//�O�i����p�N�H�[�^�j�I��

	//���G�^�C��
	int CountMNum,CountMStart;

	//����̍\���̂̏�����
	void Init_S_Gun_Update_Data(void);

};