#pragma once
#include<d3dx9.h>
#include"../../GameSource/Struct.h"
#include<string>


class C_TextureBase {
public:
	
protected:

	/*�֐�*/

	//�e�N�X�`���̃��[�h
	void Texture_Load(std::string FailName, const int Width, const int Height);
	//�e�N�X�`���̃��[�h�ƐF�̍폜
	void Texture_Load(std::string FailName, const int Width, const int Height, const int r, const int g, const int b);
	//�e�N�X�`���̏��n��
	TEXTURE Get_S_Texture(void) {
		return M_Tex;
	}
private:
	TEXTURE M_Tex;
};