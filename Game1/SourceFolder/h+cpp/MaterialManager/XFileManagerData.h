#pragma once
#include<d3dx9.h>
#include<string>
#include<map>
#include"../GameSource/Struct.h"
class XFileManagerData {
private:
	std::map<std::string, S_Mesh_Data*>MeshDataList;
public:
	~XFileManagerData();
	XFILE_B GetMesh(std::string FileName);
	void AllDelete(void);
};