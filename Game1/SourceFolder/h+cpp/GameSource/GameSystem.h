#pragma once
#include<d3dx9.h>
#include"../Ground/Ground_Object.h"
#include<vector>

class C_GameSystem
{
public:
	// ’n–Ê‚Ì“–‚½‚è”»’è
	bool JudgNowGround(unsigned int *GroundNumber,float *Dis,
		const D3DXMATRIX Mat,std::vector<C_Ground_Object*>ground);
};