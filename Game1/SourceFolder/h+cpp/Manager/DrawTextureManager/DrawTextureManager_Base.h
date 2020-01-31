#pragma once
#include<d3dx9.h>
#include"../../GameSource/Struct.h"
#include<string>

class C_DrawTextureManager_Base {
public:
	virtual TEXTURE Get_Texture(const int *TexNo)=0;
protected:
	//�e�N�X�`���̃��[�h
	TEXTURE Texture_Load(std::string FileName, const int Width, const int Height);
	//�e�N�X�`���̃��[�h�ƐF�̍폜
	TEXTURE Texture_Load(std::string FileName, const int Width, const int Height, const int r, const int g, const int b);
private:
};