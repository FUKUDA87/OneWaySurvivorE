#pragma once
#include<d3dx9.h>
#include"../../../GameSource/Struct.h"
#include"../../Bullet/BulletBase.h"
#include"../../../GameSource/XfileManager.h"
#include"../../Muz/MuzFlaBase.h"
#include"../../Laser/LaserBase.h"
#include"../../../GameSource/Judgment.h"
#include"../../../GameSource/CharaBase.h"
#include"../../../EnemyData/Base&Manager/EnemyDataBase.h"
#include"../../../EnemyData/Base&Manager/EnemyGunMoveBase.h"
#include"../../../EnemyData/Base&Manager/EnemyDataManager.h"

class C_GunBase2:public C_CharaBase {
public:
	C_GunBase2() {
		Gun.Base.DrawFlg = true;
	};
	C_GunBase2(const GUNINITDATA* GunInitDataS);
	~C_GunBase2();
	//初期化
	void Init_Gun(const GUNINITDATA* GunInitDataS);
	//表示
	void Draw3D_Gun();
	////継承アップデート
	bool Update();
	////継承表示
	bool Update_Gun(const D3DXMATRIX *Mat, int *NowPhase);

	//銃の情報渡し
	GUNDATA GetGunData(void) {
		return Gun;
	}

	//拡大入れ
	void SetScalPos(const D3DXVECTOR3 *sPos) {
		Gun.Base.ScaPos = *sPos;
	}

	////////////////////////////////////////////////////////////////////////////////////////

	//表示用行列の渡し
	D3DXMATRIX GetDrawMatGun(void) {
		return judg.GetDrawMat(&Gun.Base.Mat, &Gun.Base.Scal, &Gun.Base.ScaPos);
	}

	//表示３Dの切り替え
	void SetMeshGun(int MeshNo);

	void GetTargetPos(const D3DXVECTOR3* Pos) {
		s_Data.TargetPos = *Pos;
	}

	bool GetRayJudgFlg(void) {
		return s_Data.RayJudgFlg;
	}
	S_ENEMYGUNDATA GetEnemyGunData(void) {
		return s_Data;
	}
	
	void SetHitRayFlg(const bool *Flg) {
		s_Data.RayHitFlg = *Flg;
	}
	void SetBulletFlg(const bool *Flg) {
		s_Data.BulletFlg = *Flg;
	}

protected:
	GUNDATA Gun;

	S_ENEMYGUNDATA s_Data;

	C_E_GunMoveBase *m_Move;

	Judg judg;
};