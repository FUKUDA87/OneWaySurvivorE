#pragma once
#include<d3dx9.h>
#include<stdio.h>

#ifndef Option_H
#define Option_H


class Option {
private:
	//感度
	//リバース上下
	//リバース左右
	//難易度
protected:
public:
   Option();
   ~Option();
   bool Update();
};

#endif // !Option.h