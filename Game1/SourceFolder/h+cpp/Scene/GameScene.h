#pragma once
#include<d3dx9.h>
#include<vector>
#include"SceneBase.h"
#include"../Ground/Sky.h"
#include"../Player/Aiming.h"
#include"../Player/Camera.h"
#include"../GameSource/Countdown.h"
#include"../GameSource/Debug.h"
#include"../GameSource/Text_Num.h"
#include"../Draw/2D/GameEnd/Game_End_Now.h"
#include"../GameSource/Struct.h"
#include"../Draw/2D/Warning.h"
#include"../Draw/2D/Pause.h"
#include"../GameSource/Judgment.h"
#include"../Draw/3D/Spear.h"
#include"../GameSource/Motion.h"
#include"../Draw/2D/Score.h"
#include"../Draw/Effect/3D/Spark/Spark2.h"
#include"../Key/CMouse.h"
#include"../Key/KeyTrue.h"
#include"../Player/PlayerA.h"
#include"../Enemy/EnemyA.h"
#include"../Player/PlayerBody.h"
#include"../Draw/Menu/PauseTouch.h"
#include"../Draw/Menu/OverTouch.h"
#include"../GameSource/Count.h"
#include"../Enemy/EnemySelect.h"
#include"../Enemy/Data/Base&Manager/EnemySpeedManager.h"
#include"../Const/Const_Draw_Judg.h"
#include"../Stage_Data/Car_Pop/Car_Pop_New.h"
#include"../Ground/Stage_Ground/Ground_Pop_New.h"
#include"../Sound/GameSoundManager.h"
#include"../Draw/Damage_Num/Damage_Move_A.h"
#include"../Draw/Damage_Num/Damage_Move_B.h"
#include"../Ground/Ground_Object.h"
#include"../GameSource/Option/Option.h"
#include"../Draw/Menu/ClearTouch.h"
#include"../Ground/GroundManager.h"
#include"../Draw/Effect/EffectBase.h"
#include"../Draw/2D/Screen/Screen.h"
#include"../Draw/Damage_Num/DamageNumDraw3DManager.h"

extern Motion motion;

//#ifndef GameScene_H
//#define GameScene_H

#define RadChara 200//�L�����N�^�[�͈̔�

class GameScene :public SceneBase
{
public:
	GameScene(const int stageNum);
	GameScene(const int stageNum,const bool *DebugFlg);
	~GameScene();

	// 3D�`��
	void Render3D(void);

	// 3D�`��̏ォ��̎��_
	void Render3DScreen(void);

	// 2D�`��
	void Render2D(void);

	// �J����
	void SetCamera(void);

	// �X�V����
	bool Update(void);

private:

	C_Option *option;

	//����p�̊֐��̃N���X
	Judg judg;

	//�f�o�b�O�p----------------
	int CountNum, MaxCount;//�X���[�Đ��p
	Spear *spear;
	D3DXMATRIX SpeMat;
	//--------------------------
	//�v���C���[�̏��
	C_PlayerBody *playerBody;
	//�v���C���[
	C_PlayerBase *player;//

	std::vector<C_EnemyAi*>enemy;
	bool eneFlg;//�o���̐؂�ւ�
	Sky *sky;
	Aiming *aiming;
	Camera *camera;
	Debug *debug;
	//�����\��
	C_Text_Num *textDraw;

	c_GroundManager *groundManager;

	C_Game_End_Base *gameEnd;

	Warning *war;

	int StageNo;


	Pause *pause;

	//�X�R�A
	C_Score *score;

	//�o���b�g�o�[�XFlg
	bool bulletBirthFlg;

	//�}�E�X
	C_Mouse *mouse;
	//�L�[
	C_KeyTrue key;

	//�e���RD
	std::vector<c_EffectBase*>effect;

	//�^�b�`
	C_NextTouch* Menu;

	/*�Ԃ̕������*/
	C_Car_Pop_New *carPop;

	//���̊Ǘ�
	c_GameSoundManager* soundGameManager;

	c_DamageNumDraw3DManager *damageNumDraw3DManager;

	c_Screen *screen;  // �~�j���

	// ������
	void Init(void);

	bool UpdateEnemy(void);

	//�ǂƎԑ̉��̔���
	bool SideJudg();
	bool SideJudg(const int * CarType, const unsigned int * CarNo, const float *MoveVecX);
	bool SideJudg(bool *WallJudgFlg,const s_CarType *carType, const float *MoveVecX);

	//�G�̒a���Ǝv�l
	bool UpdateEnemyAI(void);

	//�O�i���C����
	bool ForMoveJudg(void);
	bool ForMoveJudg(const D3DXMATRIX *EndMat, const int *CarType
		, const unsigned int *CarNo, const D3DXVECTOR3 *MoveVec, float *SpeedMul2
		, const D3DXVECTOR3 *ScalPos, const float *Radius, const bool *CollisionJudgTrueFlg);

	//�ړ���̍s��쐬
	void ForMoveEnd(D3DXMATRIX *Mat,const CONSTITUTION *Con,const QuaForMove *q,const D3DXMATRIX *TransMat);
	
	//BulletBirthFlg
	bool GetBulletBirthFlg(void);

	//�f���[�g�G�l�~�[
	bool EnemyDelete(const unsigned int *EnemyNo);

	//���j���[�̓���
	void SetMenu(C_NextTouch* NewMenu);

	//���j���[�̏���
	bool UpdateMenu(void);
	
	//Pos2D�v�Z
	void Pos2DUpdate(const D3DXMATRIX *mProj, const D3DXMATRIX *mView, const D3DVIEWPORT9 *Viewport);

	//�Q�[���{�҂̍X�V
	bool UpdateGame(void);

	//�Q�[���{�Ҏ��̃|�[�Y��ʈړ��֐�
	bool UpdateGamePause(void);

	//�Q�[���̃t���[�����̔���
	bool JudgGameFrame(void);

	//������Ԃŉ�����
	/*bool UpdateCarSideJudg(void);*/

	//�v���C���[�̉��ړ�����
	bool UpdatePlayerXTrans(void);

	//�Q�[���{�҂̍Ō�̍X�V
	bool UpdatePopEnd(void);

	//�Ԃ̏o���m�F
	bool GetCarPop(const int *CarType);

	//�Ԃ̏o���̍X�V�̒�~���ߓn��
	bool GetCarPopUpdateMoveFlg(void);

	//�Q�[���I�[�o�[��
	void SetGameOver(void);

	//�Q�[���N���A��
	void SetGameClear(void);

	//�S�Ă̒e�̍X�V
	bool UpdateBullet(void);

	//�e�̏o�������̍X�V
	void BulletInitPlayer(void);
	void BulletInitEnemy(void);

	//�e�̔���̍X�V
	bool UpdateBulletJudg(void);

	void NewSound(const int *Type, const int *Category, const int No, const int *Change);
	void NewSound(const int *Category, const int No,const D3DXVECTOR3* Pos, const int *Change);

	//�Q�[���I��Flg
	bool GetEndFlg(void);

	//�Q�[���̃��[�h�`�F���W
	void GemeEndChange(const int *Mode);

	//�G�̏o��
	void PopEnemy(void);

	//�Ԃ̏o���\����(�o���\�Ȃ�true)
	bool CarPopJudg(const D3DXMATRIX *GroundMat, const float *TransX);

	//�Ԃ̐����m�F

	/*�e*/

	//�e����W
	void RayJudgPlayer(BULLETJUDGDATA* BJD, const RAYDATA *RD, const float *Rad);
	void RayJudgEnemy(BULLETJUDGDATA* BJD,const RAYDATA *RD, const float *Rad);
	void BulletJudgEnemyBall(BULLETJUDGDATA* BJD, const RAYDATA *RD, const float *Rad);
	//�e����ɂ��_���[�W�v�Z
	bool SetBulletDamage(const BULLETJUDGDATA* BJD, const RAYDATA *RD,const int Damage);

	/*���̏Փ˔���*/

	//���̏Փ˔���̕ǂ̉ΉԂ̏o������
	void WallSparkInit(bool *SparkInitFlg, const D3DXMATRIX *RayHitMat, const D3DXVECTOR3 *RayHitPos, bool *LeftFlg);
	void CarSparkInit(const bool *SparkInitFlg, const D3DXMATRIX *RayHitMat, const D3DXVECTOR3 *RayHitPos);

	/*���C����*/
	
	//�Փ˂ɂ��G��Ai�ƍU����Stop������
	void EnemyStop(const unsigned int *e,const int *SideJudgCarType);

	//������J�����O
	void FrustumCulling(const D3DXMATRIX *mProj, const D3DXMATRIX *mView, const D3DVIEWPORT9 *Viewport);

	// �v���C���[�Ƌ�����
	void BallJudgPlayer(bool *JudgFlg, float *SmallDis,s_CarType * HitCar,const s_CarType * JudgCar,
		const D3DXMATRIX *Mat,const float *Radius,const bool *CollisionJudgTrueFlg);

	// �G�Ƌ�����
	void BallJudgEnemy(bool *JudgFlg, float *SmallDis, s_CarType * HitCar, const s_CarType * JudgCar,
		const D3DXMATRIX *Mat, const float *Radius, const bool *CollisionJudgTrueFlg);

	//�o�����Ă���Ԃ̏��̍쐬�ƎԂ̏o���̍X�V
	void CarPopDataUpdate(void);
};

//#endif // !GameScene_H
