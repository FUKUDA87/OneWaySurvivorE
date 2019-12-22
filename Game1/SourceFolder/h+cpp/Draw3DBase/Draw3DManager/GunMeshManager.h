#pragma once
#include"MeshManager.h"
//eŒû
#include"../../Gun/GunDraw/GunData/GunDataBase.h"

class C_GunMeshManager :public C_MeshManager {
public:
	XFILE GetMesh(int MeshNo);
	//e‚ÌeŒû”‚ÆPos‚Ìæ“¾
	C_GunDataBase* GetGunData(const int MeshNo);
private:
	//ƒ‚ƒfƒ‹î•ñ’T‚µ
	bool GetMeshJudg(int MeshNo);
	//No1
	bool GetGunNo1(int MeshNo);
	//No2
	bool GetGunNo2(int MeshNo);
	//No3
	bool GetGunNo3(int MeshNo);
};