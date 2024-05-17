#pragma once
#include <vector>
#include <string>
#include <iostream>
#include <fstream>
#include "../ArcoEngine/scene/model/CuboT.h"

class Pulgas
{
public:
	Pulgas();
	~Pulgas();

	void Initialize(ID3D11Device* device, ID3D11DeviceContext* context, DXCamera* camera, const std::wstring& textname, const std::string &modelname);
	void update(float elapsedTime);
	void draw();

	void setPosition(float x, float y, float z);
	float getYPosition() const;

	void drawModel(float x, float y, float z, float angX, float angY);

private:

	CCuboT* mPulga;
	CCuboT* mPulgapatas;
	CCuboT* mPulgaojos;

	float neckLength;

	float mPosX;
	float mPosY;
	float mPosZ;

	//std::vector<CCuboT*> mHippoHead;
	//std::vector<glm::vec3> posiciones;
};

