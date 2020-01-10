#include "Spark2.h"
#include"../../GameSource/Judgment.h"
#include"../../GameSource/InvBi.h"
#include"../../GameSource/TextureManager.h"

extern Inv inv;

extern Judg judg;
extern TextureManager textureManager;
//extern LPDIRECT3DDEVICE9		lpD3DDevice;

C_Spark2::C_Spark2(const D3DXMATRIX * Mat, const D3DXVECTOR3 * Pos):C_Spark(Mat,Pos)
{
	//移動処理の初期化
	yDown = -0.005f;
	zDown = -(float)(rand()%(20-15)+15)/100.0f;

	//角度の初期化
	spark.Base.Mat = *Mat;
	//X軸の回転角度を求める
	int Big = 6000, Small = -6000;
	Big = Big - Small;
	float Ang = (float)(rand() % Big + Small) / 100.0f;
	yUp = 0.0f;
	yDown = -0.01f;
	if (yDown > 0.0f)yDown *= -1.0f;
	//存在時間の計算
	if (Ang < -3000.0f)NowCount = 3;
	if(Ang > -3000.0f)NowCount = 6;
	if (Ang > 0.0f)NowCount = 20;
	if (Ang > 3000.0f)NowCount = 30;
	//X回転と移動行列
	D3DXMATRIX Rot, Trans;
	//回転
	D3DXMatrixRotationX(&Rot, D3DXToRadian(Ang));
	//ずらす
	D3DXMatrixTranslation(&Trans, 0.0f, 0.0f, 0.15f);
	//位置の初期化
	judg.SetMatP(&spark.Base.Mat, *Pos);
	spark.Base.Mat = Rot * Trans * spark.Base.Mat;
	//他の行列を初期化
	for (int p = 0; p < PNum; p++) {
		spark.PolMat[p] = spark.Base.Mat;
	}
	for (int i = 0; i < PNum; i++) {
		//上移動と後ろ移動
		D3DXMATRIX Tmp, Rot;
		/*if (yUp < 0.0f) {
			D3DXMatrixTranslation(&Tmp, 0.0f,0.0f, zDown*0.5f);
		}
		else {*/
		D3DXMatrixTranslation(&Tmp, 0.0f, 0.0f, zDown);
		//}
		D3DXMatrixRotationX(&Rot, D3DXToRadian(0));
		spark.Base.Mat = Rot * Tmp*spark.Base.Mat;
		spark.Base.Mat._42 += yUp;
		//ジャンプ処理
		/*if (yUp < 0.0f) {
			yUp += yDown * 1.5f;
		}
		else {
			yUp += yDown;
		}*/
		yUp += yDown;
		//行列の更新
		for (int i = (PNum - 1); i > 0; i--) {
			spark.PolMat[i] = spark.PolMat[i - 1];
		}
		//先頭に一番新しい行列の代入
		spark.PolMat[0] = spark.Base.Mat;
	}
}

C_Spark2::C_Spark2(const D3DXMATRIX * Mat, const D3DXVECTOR3 * Pos, const bool * InitFlg) :C_Spark(Mat, Pos)
{
	//画像のロード
	int SparkType;
	if ((rand() % 15) != 1) {
		SparkType = 3;
	}
	else {
		SparkType = 6;
		//ポリゴンサイズの初期化
		PolSize = 0.01f;
	}
	char TexName[100];
	sprintf_s(TexName, sizeof(TexName),"../GameFolder/Material/Texture/Spark1-9-%d.png" , SparkType);
	spark.TEX.Tex = textureManager.GetTexture(TexName, spark.TEX.Width, spark.TEX.Height, NULL);

	//移動処理の初期化
	yDown = -0.005f;
	zDown = -(float)(rand() % (20 - 5) + 5) / 10.0f;

	//角度の初期化
	spark.Base.Mat = *Mat;
	//X軸の回転角度を求める
	int Big = 6000, Small = -6000;
	Big = Big - Small;
	float Ang = (float)(rand() % Big + Small) / 100.0f;
	yUp = Ang / 100.0f*0.5f;
	yDown = yUp / 10.0f;
	if (yDown > 0.0f)yDown *= -1.0f;
	//存在時間の計算
	if (Ang < -3000.0f)NowCount = 3;
	if (Ang > -3000.0f)NowCount = 6;
	if (Ang > 0.0f)NowCount = 20;
	if (Ang > 3000.0f)NowCount = 30;
	if (*InitFlg == true)NowCount = 1;
	//X回転と移動行列
	D3DXMATRIX Rot, Trans;
	//回転とずらし
	float AngY;// , zMove;
	AngY = (float)(rand() % 50)/10.0f;
	if ((rand() % 2) == 1)AngY *= -1.0f;
	//zMove = 0.15f;
	D3DXMatrixRotationY(&Rot, D3DXToRadian(AngY));
	//ずらす
	//D3DXMatrixTranslation(&Trans, 0.0f, 0.0f, zMove);
	//位置の初期化
	judg.SetMatP(&spark.Base.Mat, *Pos);
	spark.Base.Mat = Rot /** Trans*/ * spark.Base.Mat;
	//他の行列を初期化
	for (int p = 0; p < PNum; p++) {
		spark.PolMat[p] = spark.Base.Mat;
	}
	for (int i = 0; i < PNum; i++) {
		//上移動と後ろ移動
		D3DXMATRIX Tmp;
		D3DXMatrixTranslation(&Tmp, 0.0f, 0.0f, zDown);
		spark.Base.Mat = Tmp * spark.Base.Mat;
		spark.Base.Mat._42 += yUp;
		//ジャンプ処理
		yUp += yDown;
		//行列の更新
		for (int i = (PNum - 1); i > 0; i--) {
			spark.PolMat[i] = spark.PolMat[i - 1];
		}
		//先頭に一番新しい行列の代入
		spark.PolMat[0] = spark.Base.Mat;
	}
}

C_Spark2::C_Spark2(const D3DXMATRIX * Mat, const D3DXVECTOR3 * Pos, const bool * LeftFlg, const bool * InitFlg) :C_Spark(Mat, Pos)
{
		PNum = rand() % 1 + 2;
	//ポリゴン表示用のMatの初期化
	if (spark.PolMat != nullptr) {
		delete[] spark.PolMat;
	}
	spark.PolMat = new D3DXMATRIX[PNum];
	//移動処理の初期化
	zDown = -(float)(rand() % 11 + 20) / 100.0f;
	yUp = 0.0f;

	//角度の初期化
	spark.Base.Mat = *Mat;
	//X軸の回転角度を求める
	int Big = 2800, Small = -2000;
	Big = Big - Small;
	float Ang = (float)(rand() % Big + Small) / 100.0f;
	int Mul = (int)Ang;
	if (Mul <= 0)Mul =1;
	yDown = -0.013f-0.003f*(float)Mul;
	//存在時間の計算
	if (Ang < -2000.0f)NowCount = 2;
	if (Ang > -2000.0f)NowCount = 4;
	if (Ang > 0.0f)NowCount = 30;
	if (Ang > 3000.0f)NowCount = 40;
	PolSize = 0.025f;
	//X回転と移動行列
	D3DXMATRIX RotY,RotX, Trans;
	//回転とずらし
	float AngY,zMove;
	AngY = (float)(rand() % 75);
	if (*InitFlg == true)AngY *= 0.8f;
	zMove = -0.3f-(float)(rand()%10)/100.0f;
	if (Ang < 0.0f)zMove*=-1.0f;
	if (*LeftFlg == true) {
		//左
		AngY *= -1.0f;
		zMove *= -1.0f;
	}
	else {
		//右
		AngY += 180.0f;
	}
	if (*InitFlg == true) {
		PolSize = 0.1f;
		zDown = -0.7f+(float)(rand()%3)/10.0f;
		NowCount = 2;

		Small = (int)((float)Small*0.45f);
		Big = (int)((float)Big * 0.45f) - Small;
		Ang = (float)(rand() % Big + Small) / 100.0f;

	}
	D3DXMatrixRotationY(&RotY, D3DXToRadian(AngY));
	D3DXMatrixRotationX(&RotX, D3DXToRadian(Ang));
	//ずらす
	D3DXMatrixTranslation(&Trans, 0.0f, (float)(rand()%100)/1000.0f*-1.0f, zMove);
	//位置の初期化
	judg.SetMatP(&spark.Base.Mat, *Pos);
	spark.Base.Mat = RotX*RotY *Trans * spark.Base.Mat;
	//他の行列を初期化
	for (int p = 0; p < PNum; p++) {
		spark.PolMat[p] = spark.Base.Mat;
	}

	if (*InitFlg == false) {
		spark.Base.Mat._42 += yUp;
		for (int s = 0; s < (PNum - 1); s++) {
			//上移動と後ろ移動
			D3DXMATRIX Tmp;
			D3DXMatrixTranslation(&Tmp, 0.0f, 0.0f, zDown);
			spark.Base.Mat = Tmp * spark.Base.Mat;
			//ジャンプ処理
			//行列の更新
			for (int i = (PNum - 1); i > 0; i--) {
				spark.PolMat[i] = spark.PolMat[i - 1];
			}
			//先頭に一番新しい行列の代入
			spark.PolMat[0] = spark.Base.Mat;
		}
		yUp += yDown;
		if (NowCount > 2 + 3) {
			for (int i = 3; i > 0; i--) {
				Update();
			}
		}
	}
	else {
		spark.Base.Mat._42 += yUp;
			//上移動と後ろ移動
			D3DXMATRIX Tmp;
			D3DXMatrixTranslation(&Tmp, 0.0f, 0.0f, zDown);
			spark.Base.Mat = Tmp * spark.Base.Mat;
			//ジャンプ処理
			//行列の更新
			for (int i = (PNum - 1); i > 0; i--) {
				spark.PolMat[i] = spark.PolMat[i - 1];
			}
			//先頭に一番新しい行列の代入
			spark.PolMat[0] = spark.Base.Mat;
		yUp += yDown;
	}
}

bool C_Spark2::Update(void)
{
	spark.Base.Mat._42 += yUp;
	//for (int s = 0; s < PNum; s++) {
		//上移動と後ろ移動
		D3DXMATRIX Tmp;
		D3DXMatrixTranslation(&Tmp, 0.0f, 0.0f, zDown);
		spark.Base.Mat = Tmp * spark.Base.Mat;
		//行列の更新
		for (int i = (PNum - 1); i > 0; i--) {
			spark.PolMat[i] = spark.PolMat[i - 1];
		}
		//先頭に一番新しい行列の代入
		spark.PolMat[0] = spark.Base.Mat;
	//}
	//ジャンプ処理
		if (yUp < -0.001f) {
			yUp += yDown*0.15f;
		}
		else {
			yUp += yDown;
		}
	return CountUpdate();
}
