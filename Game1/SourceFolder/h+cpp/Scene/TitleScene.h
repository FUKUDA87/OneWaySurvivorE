#pragma once
#include<d3dx9.h>
#include"SceneBase.h"
#include"../TitleParts/TitleTex.h"
#include"../TitleParts/StartTex.h"
#include"../TitleParts/TitelCamera.h"
#include"../Ground/Bill1.h"
#include"../Ground/BillBase.h"
#include"../Ground/Sky.h"
#include"../GameSource/Countdown.h"
#include"../Ground/Wall.h"
#include"../2DDraw/BulletHole.h"
#include"../Key/CMouse.h"
#include"../Key/Key.h"
#include"../2DDraw/Fade.h"
#include"../Player/PlayerBody.h"
#include"../Player/PlayerA.h"
#include"../GameSource/Count.h"
#include"../Sound/Sound_Manager_Base.h"

template<class T>
inline void SafeRelease(T& lpAdd)
{
	if (lpAdd != nullptr) {
		lpAdd->Release();
		lpAdd = nullptr;
	}
}
class TitleScene :public SceneBase
{

public:
	TitleScene();
	~TitleScene();
	void Render2D(void);
	void Render3D(void);
	bool Update(void);
	void SetCamera(void);
	bool NowGroNum(D3DXMATRIX Mat, unsigned int *Num, float *Dis);

	//�`�F���W�V�[���p
	void ChangeSceneFade(int ChangeSceneNo);
	bool SetScene(void);

private:
	//<�n��
	std::vector<BillBase*>ground;
	Cou *cou;//bill
	std::vector<Cou*>GroCou;
	int GroType, GroKNum, *CurType, NowCur;
	float AngGro;//�J�[�u���̊p�x
	bool GroLenFlg;//�����̕ύX
	//�O���\���p�J�E���g�_�E��
	C_Count *LightCount;

	LPDIRECT3DTEXTURE9 Tex;
	TitleTex *titleTex;
	StartTex *startTex;
	
	//�v���C���[
	C_PlayerBase *player;
	//�v���C���[�̏��
	C_PlayerBody *PlaBodData;

	TitleCamera *camera;
	Sky *sky;
	//�e��
	std::vector<C_BulletHole*>BulHol;

	//�}�E�X
	C_Mouse *mouse;
	//�L�[
	Key key;
	//�t�F�[�h
	Fade *fade;
	//�`�F���W�V�[���p
	int SceneNo;
	bool SceneChangeFlg;

	//�Q�[���̏I��
	bool Game_End(void);

	C_Sound_Manager_Base* M_C_Sound_Manager;
};
