#pragma once
#include<d3dx9.h>
#include<vector>
#include"SceneBase.h"
#include"../Ground/Sky.h"
#include"../Player/Aiming.h"
#include"../3DDraw/Effect_3D/Explosion.h"
#include"../Player/Camera.h"
#include"../GameSource/Countdown.h"
#include"../GameSource/Debug.h"
#include"../GameSource/Text_Num.h"
#include"../2DDraw/Game_End/Game_End_Now.h"
#include"../GameSource/Struct.h"
#include"../2DDraw/Warning.h"
#include"../2DDraw/Pause.h"
#include"../GameSource/Judgment.h"
#include"../3DDraw/Spear.h"
#include"../GameSource/Motion.h"
#include"../3DDraw/Effect_3D/Smoke2.h"
#include"../2DDraw/Score.h"
#include"../3DDraw/Effect_3D/SpaekDamage.h"
#include"../3DDraw/Effect_3D/Smog.h"
#include"../3DDraw/Effect_3D/BulletGround.h"
#include"../3DDraw/Effect_3D/Spark2.h"
#include"../Key/CMouse.h"
#include"../Key/KeyTrue.h"
#include"../2DDraw/Fade.h"
#include"../3DDraw/Effect_3D/BulletHole3D.h"
#include"../Player/PlayerA.h"
#include"../Enemy/EnemyA.h"
#include"../Player/PlayerBody.h"
#include"../2DDraw/PauseTouch.h"
#include"../2DDraw/OverTouch.h"
#include"../GameSource/Count.h"
#include"../Enemy/EnemySelect.h"
#include"../EnemyData/Base&Manager/EnemySpeedManager.h"
#include"../3DDraw/Effect_3D/CarSmog.h"
#include"../Const/Const_Draw_Judg.h"
#include"../Stage_Data/Car_Pop/Car_Pop_New.h"
#include"../Ground/Stage_Ground/Ground_Pop_New.h"
#include"../Sound/Sound_Manager_Base.h"
#include"../Draw/Damage_Num/Damage_Move_A.h"
#include"../Draw/Damage_Num/Damage_Move_B.h"
#include"../Ground/Ground_Object.h"

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
	void Render3D(void);
	void Render3D_Screen(void);
	void Render2D(void);
	void SetCamera(void);
	bool Update(void);
	bool UpdateE(void);
	
	//�e�̃��C����
	void BulletJudg(const int *TypeCar,const unsigned int *CarNo);

	//�ǂƎԑ̉��̔���
	void Side_Judg(const int *Car_Type, const unsigned int *Car_No);
	bool Side_Judg(const bool *Left_Flg,const int *Car_Type,const unsigned int *Car_No);

	//�G�̒a���Ǝv�l
	bool UpdateEnemyAI(void);
	//�G�̈ړ�
	bool UpdateEnemyMove(void);

	//�O�i���C����
	bool ForMoveJudg(const CONSTITUTION *Con,const D3DXMATRIX *StartMat,const D3DXMATRIX *EndMat,
		const int *Car_Type,const unsigned int *Car_No,const D3DXVECTOR3 *RayVec1,const D3DXVECTOR3 *RayVec2,
		const D3DXVECTOR3 *RayVec3,float *SpeedMul2,const D3DXVECTOR3 *ScalPos,const bool *CollisionJudg_TrueFlg);


	//�ړ���̍s��쐬
	void ForMoveEnd(D3DXMATRIX *Mat,const CONSTITUTION *Con,const QuaForMove *q,const D3DXMATRIX *TransMat);
	//�J�����ƕǔ���
	void CameraWallJudg(void);
	//BulletBirthFlg
	bool GetBulletBirthFlg(void);
	//�����C���X�^���X���֐�
	void BombInit(const D3DXMATRIX *Mat);
	//�f���[�g�G�l�~�[
	bool EnemyDelete(const unsigned int *EnemyNo);

	//�`�F���W�V�[���p
	void ChangeSceneFade(int ChangeSceneNo);
	void ChangeSceneFade(int ChangeSceneNo, int NextStageNo);
	bool SetScene(void);

	//���j���[�̓���
	void SetMenu(bool PauseFlg, bool ClearFlg, bool OverFlg);
	//���j���[�̍폜
	void DeleteMenu(void);
	//���j���[�̏���
	bool UpdateMenu(void);
	//�n�ʂ̎�������
	bool GroundCreate(unsigned int *GNo);
	//Pos2D�v�Z
	void Pos2DUpdate(const D3DXMATRIX *mProj, const D3DXMATRIX *mView, const D3DVIEWPORT9 *Viewport);

protected:
	//�^�C�g���ɖ߂�L�[
	bool Change_TitleScene(void);

	//�R���X�g���N�^�֐�
	void AllNew(void);
	//�f�X�g���N�^�֐�
	void AllDelete(void);

	/*�A�b�v�f�[�g*/

	//�f�o�b�N�̍X�V
	bool Update_Debug(void);

	//�t�F�[�h�̍X�V
	bool Update_Fade(void);

	//�Q�[���{�҂̍X�V
	bool Update_Game(void);

	//�Q�[���{�Ҏ��̃|�[�Y��ʈړ��֐�
	bool Update_Game_Pause(void);

	//�Q�[���̃t���[�����̔���
	bool Judg_Game_Frame(void);

	//�n�ʂ̍X�V
	bool Update_Ground(void);

	//�����̍X�V
	bool Update_Explo(void);

	//�ΉԂ̍X�V
	bool Update_Spark(void);

	//�Ԃ̉��̍X�V
	bool Update_CarSmoke(void);

	//�e���̍X�V
	bool Update_Bullet_Hole(void);

	//�Ԃ̑O���ɃJ�����������鏈��
	bool Update_Camera_Car(void);

	//�v���C���[�̏Ə��ɂ�郌�C����ƒe�̌��ƍX�V
	bool Update_Player_Bullet(void);

	//������ԂőO�i����
	bool Update_Car_ForMove(void);

	//������Ԃŉ�����
	bool Update_Car_SideJudg(void);

	//�v���C���[�̉��ړ�����
	bool Update_Player_XTrans(void);

	//�v���C���[�̍X�V
	bool Update_Player(void);

	//�Ԃ̍��̈ʒu�̍X�V
	bool Update_Car_SetMat(void);

	//�J�����s��̎擾
	bool Update_CameraMat(void);

	//�n�ʂ̏o��
	int Init_Ground_Push(const D3DXMATRIX *Mat1, const D3DXMATRIX *Mat0,const int *Type);

	//�Q�[���{�҂̍Ō�̍X�V
	bool Update_Pop_End(void);

	//�Ԃ̏o���m�F
	bool Get_Car_Pop(const int *Car_Type);

	//�Ԃ̏o���̍X�V�̒�~���ߓn��
	bool Get_Car_Pop_Update_MoveFlg(void);

	//�n�ʂ̏�����
	void Set_Ground_Data(void);

	//�Q�[���I�[�o�[��
	void Set_Game_Over(void);

	//�Q�[���N���A��
	void Set_Game_Clear(void);

	//�S�Ă̒e�̍X�V
	bool Update_Bullet(void);

	//�e��MoveVec�̉��Z�̍X�V
	bool Update_Bullet_MoveVec(void);

	//�e�̏o�������̍X�V
	bool Update_Bullet_Enemy_Init(void);

	//�e�̏o���̍X�V
	bool Update_Bullet_Init(void);

	//�e�̔���̍X�V
	bool Update_Bullet_Judg(void);

	//�e�̍X�V
	bool Update_Bullet_Move(void);

	//���[���̑���
	int Get_Rail_Num(const int *Way_Rail_Num, const int *Pop_Rail_Num);

	//���̊Ǘ�
	bool Update_Sound(void);

	void New_Sound(const int *Type, const int *Category, const int No, const int *Change);
	void New_Sound(const int *Category, const int No,const D3DXVECTOR3* Pos, const int *Change);

	bool Update_Damage_Num_Draw(void);

	//�Q�[���I��Flg
	bool Get_End_Flg(void);

	//�Q�[���̃��[�h�`�F���W
	void Geme_End_Change(const int *Mode);

	//�G�̏o��
	void Pop_Enemy(void);

	//�Ԃ̏o���\����(�o���\�Ȃ�true)
	bool Car_Pop_Judg(const D3DXMATRIX *GroundMat, const float *TransX);

	//�o������Ԃƃv���C���[�̏o������
	bool Car_Pop_Judg_Player(const D3DXVECTOR3 *Pop_Pos, const float *Pop_Radius);

	//�o������ԂƃG�l�~�[�̏o������
	bool Car_Pop_Judg_Enemy(const D3DXVECTOR3 *Pop_Pos, const float *Pop_Radius);

	//�f�o�b�N�p�̕����\��
	void Debug_Text(void);

	//�Ԃ̐����m�F

	/*�폜*/
	void Delete_Damage_Num_Draw(unsigned int *vector_No);
	void New_Damage_Num_Draw(const int *Character_Type, const D3DXMATRIX* Ray_Mat, const D3DXVECTOR3* Ray_Vec
		,const float *Ray_Dis, const int *Damage, const bool *DamageFlg);

	/*�e*/

	//�e����̏�񏉊���
	BULLETJUDGDATA GetInitBJD(const float *InitDis);
	//�e����W
	void BulletJudgGround(BULLETJUDGDATA* BJD,const RAYDATA *RD,bool *HitFlg,const float *Rad);
	void BulletJudgPlayer(BULLETJUDGDATA* BJD, const RAYDATA *RD, const float *Rad);
	void BulletJudgEnemy(BULLETJUDGDATA* BJD,const RAYDATA *RD, const float *Rad,const unsigned int *EnemyNo);
	void BulletJudgEnemy_Ball(BULLETJUDGDATA* BJD, const RAYDATA *RD, const float *Rad);
	//�e����ɂ��_���[�W�v�Z
	bool SetBulletDamage(const BULLETJUDGDATA* BJD, const RAYDATA *RD,const int Damage);
	bool SetBulletDamageGround(const BULLETJUDGDATA* BJD, const RAYDATA *RD);
	bool SetBulletDamageWall(const BULLETJUDGDATA* BJD, const RAYDATA *RD);
	bool SetBulletDamagePlaCar(const BULLETJUDGDATA* BJD, const RAYDATA *RD, const int *Damage);
	bool SetBulletDamagePlaParts(const BULLETJUDGDATA* BJD, const RAYDATA *RD, const int *Damage);
	bool SetBulletDamagePlaGun(const BULLETJUDGDATA* BJD, const RAYDATA *RD, const int *Damage);
	bool SetBulletDamageEneCar(const BULLETJUDGDATA* BJD, const RAYDATA *RD, const int *Damage);
	bool SetBulletDamageEneParts(const BULLETJUDGDATA* BJD, const RAYDATA *RD, const int *Damage);
	bool SetBulletDamageEneGun(const BULLETJUDGDATA* BJD, const RAYDATA *RD, const int *Damage);

	/*���̏Փ˔���*/

	//���̏Փ˔���̏���
	bool SideJudg_Preparation(S_SideJudgChara *Judg_Car, D3DXMATRIX *JudgMat,
		D3DXVECTOR3 *JudgVec, float *SmallDis, float *Over_Dis, const int *JudgMat_Num);

	//���̏Փ˔���Ńv���C���[�Ɣ���
	int Side_Judg_Player(S_SideJudgChara *Next_Data, float *Small_Dis,int *RayHit_No,
		D3DXMATRIX *RayHit_Mat, float *Over_Dis, bool *Over_Flg,const S_SideJudgChara *Data,
		const int *JudgMat_Num,const D3DXMATRIX *JudgMat,const D3DXVECTOR3 *Ray_Vec);

	//���̏Փ˔���œG�Ɣ���
	int Side_Judg_Enemy(S_SideJudgChara *Next_Data, float *Small_Dis, int *RayHit_No,
		D3DXMATRIX *RayHit_Mat, float *Over_Dis, bool *Over_Flg, const S_SideJudgChara *Data,
		const int *JudgMat_Num, const D3DXMATRIX *JudgMat, const D3DXVECTOR3 *Ray_Vec);

	//���̏Փ˔���Œn�ʂƔ���
	bool Side_Judg_Ground(const S_SideJudgChara *Data,
		const D3DXMATRIX *JudgMat_Base,const D3DXVECTOR3 *Ray_Vec, float *Small_Dis,
		int *RayHit_No, D3DXMATRIX *RayHit_Mat);

	//���̏Փ˔���
	int Side_Judg_Ray(S_SideJudgChara *Next_Data, float *Small_Dis, int *RayHit_No,
		D3DXMATRIX *RayHit_Mat, float *Over_Dis, bool *Over_Flg, const int *Judg_Car_Type,
		const unsigned int *Car_No, const S_SideJudgChara *Data, const int *JudgMat_Num,
		const D3DXMATRIX *JudgMat, const D3DXVECTOR3 *Ray_Vec);

	int Side_Judg_Ray(const int *Judg_Car_Type, const unsigned int *Car_No, const float *Car_Rad, S_SideJudgChara *Next_Data
		, float *Small_Dis,int *RayHit_No, D3DXMATRIX *RayHit_Mat,const float *Ray_Hit_Dis,const D3DXMATRIX *Judg_Car_Mat,const int *RayPos_No);

	//���̏Փ˔���̕ǂ̉ΉԂ̏o������
	void Wall_Spark_Init(bool *Spark_Init_Flg, const D3DXMATRIX *RayHit_Mat, const D3DXVECTOR3 *RayHit_Pos, bool *LeftFlg);
	void Car_Spark_Init(const bool *Spark_Init_Flg, const D3DXMATRIX *RayHit_Mat, const D3DXVECTOR3 *RayHit_Pos);

	/*���C����*/
	//�v���C���[�̃R���W�������f��
	bool Ray_Judg_Player_ColModel(const D3DXVECTOR3* Ray_Pos, const D3DXVECTOR3* Ray_Vec, float *Dis);
	//�G�̃R���W�������f��
	bool Ray_Judg_Enemy_ColModel(const unsigned int *Enemy_No,const D3DXVECTOR3* Ray_Pos, const D3DXVECTOR3* Ray_Vec, float *Dis);

	//�Փ˂ɂ��G��Ai�ƍU����Stop������
	void Enemy_Stop(const unsigned int *e,const int *Side_Judg_Car_Type);

private:
	//����p�̊֐��̃N���X
	Judg judg;

	//�f�o�b�O�p----------------
	int CountNum, MaxCount;//�X���[�Đ��p
	Spear *spear;
	D3DXMATRIX SpeMat;
	//--------------------------
	//�v���C���[�̏��
	C_PlayerBody *PlayerBody;
	//�v���C���[
	C_PlayerBase *player;//

	//�n�ʂ̃����o
	std::vector<C_Ground_Object*>ground;
	Cou *cou;//bill
	std::vector<Cou*>GroCou;
	//�O���\���p�J�E���g�_�E��
	C_Count *LightCount;

	std::vector<C_EnemyAi*>enemy;
	bool eneFlg;//�o���̐؂�ւ�
	Sky *sky;
	Aiming *aiming;
	std::vector<Explo*>explo;
	Camera *camera;
	Debug *debug;
	//�����\��
	C_Text_Num *M_Text_Num;
	
	C_Game_End_Base* M_C_Game_End;

	Warning *war;

	int StageNo;
	

	Pause *pause;

	//�Ήԕϐ�
	std::vector<C_Spark*>SparkV;

	//�X�R�A
	C_Score *score;

	//�o���b�g�o�[�XFlg
	bool BulletBirthFlg;

	//�}�E�X
	C_Mouse *mouse;
	//�L�[
	C_KeyTrue key;
	//�t�F�[�h
	Fade *fade;
	//�`�F���W�V�[���p
	int SceneNo;
	bool SceneChangeFlg;
	int ChangeStageNo;

	//�e���RD
	std::vector<C_BulHol3D*>BHole3D;

	//�^�b�`
	std::vector<C_NextTouch*>Menu;

	//�ԗp�̉��G�t�F�N�g
	C_SmokeCar* M_C_SmokeCar;

	/*�Ԃ̕������*/
	C_Car_Pop_New *M_C_Car_Pop;

	/*�n�ʂ̏��*/
	C_Ground_Pop_New* M_C_Ground_Pop;

	//���̊Ǘ�
	C_Sound_Manager_Base* M_C_Sound_Manager;

	std::vector<C_Damage_Num_Base*>M_Damage_Num_Draw;

	//�~�j��ʂ̕\��
	S_SCREEN_2D M_S_Screen;

	//�~�j��ʂ̏�����
	void Debug_Screen_Init(void);
	//�~�j��ʂ̏I������
	void Debug_Screen_End(void);
	//�~�j��ʂ̕\��
	void Debug_Screen_Draw(void);

	//������J�����O
	void FrustumCulling(const D3DXMATRIX *mProj, const D3DXMATRIX *mView, const D3DVIEWPORT9 *Viewport);

	//�n�ʂ̎�����J�����O
	void FrustumCulling_Ground(const S_Frustum_Vec *FV_Data);

	//�n�ʂ̕ǂ̎�����J�����O
	void FrustumCulling_Ground_Wall(const unsigned int *gNo, const S_Frustum_Vec *FV_Data);

	//�n�ʂ̕\�����̎�����J�����O
	void FrustumCulling_Ground_Object(const unsigned int *gNo, const S_Frustum_Vec *FV_Data);

	//��e���𗬂�����
	void Set_BulletHit_Sound(const int *BulletHit_Type, const D3DXVECTOR3 *Sound_Pos);
	void Set_BulletHit_Sound(const int *BulletHit_Type, const D3DXVECTOR3 *Sound_Pos,const bool *DamageFlg);
	void Set_BulletHit_Sound(const int *BulletHit_Type, const BULLETJUDGDATA* BJD, const RAYDATA * RD,const bool *DamageFlg);

	/*���ʏՓ˔���*/

	//�v���C���[�Ɛ��ʏՓ˔���
	void M_ForMoveJudg_Player(bool *JudgFlg, float *SmallDis,int *Hit_CarType,
		unsigned int *Hit_CarNumber, const int *Car_Type,
		const D3DXMATRIX *StartMat, const D3DXMATRIX *EndMat, const D3DXMATRIX *TransMat,
		const int *TransNum, const D3DXVECTOR3 *MoveVec, const D3DXVECTOR3 *PosBig,
		const D3DXVECTOR3 *PosSmall, const D3DXVECTOR3 *ScalPos,
		const bool *CollisionJudg_TrueFlg);

	//�G�Ɛ��ʏՓ˔���
	void M_ForMoveJudg_Enemy(bool *JudgFlg, float *SmallDis, int *Hit_CarType,
		unsigned int *Hit_CarNumber,const int *Car_Type,const unsigned int *Car_No,
		const D3DXMATRIX *StartMat, const D3DXMATRIX *EndMat, const D3DXMATRIX *TransMat, const int *TransNum,
		const D3DXVECTOR3 *MoveVec, const D3DXVECTOR3 *PosBig, const D3DXVECTOR3 *PosSmall,
		const D3DXVECTOR3 *ScalPos, const bool *CollisionJudg_TrueFlg);

	//���ʏՓ˔���̈ړ���̎Ԃ̃��C�̔��ˈʒu�ƃx�N�g���̍쐬
	bool M_ForMoveJudg_AfterMovingRay(D3DXVECTOR3 *Ray_Pos, D3DXVECTOR3 *Ray_Vec,const int *Vec_No,
		const D3DXVECTOR3 *PosBig,const D3DXVECTOR3 *PosSmall,const D3DXVECTOR3 *ScalPos,const D3DXMATRIX *EndMat);

	//���S�m�F
	bool Get_Dead_Flg(const int *Car_Type,const unsigned int *Car_Number);

	//����̃^�[�Q�b�g�����S������
	void M_Dead_Car(const int *Car_Type, const unsigned int *Car_Number);

	//�o�����Ă���Ԃ̏��̍쐬�ƎԂ̏o���̍X�V
	void M_Car_Pop_Data_Update(void);

};

//#endif // !GameScene_H
