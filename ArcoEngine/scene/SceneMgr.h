#pragma once
#include <conio.h>
#include <iostream>
#include "../Pulgas.h"
#include "../MouseD.h"

struct ID3D11Device;
struct ID3D11DeviceContext;
class CCubo;
class CCuboP;
class CCuboT;
class CPanel;
class DXCamera;

class CSceneMgr
{
public:
	CSceneMgr(void);
	~CSceneMgr(void);

	void Initialize(ID3D11Device *device, ID3D11DeviceContext *dcontext);
	void update(float deltaTime);

	void draw(float deltaTime);
	void changeCamera(float x, float y, float z);
	void keyPress(float lx, float ly);

	void MouseActions(float lx, float ly);

private:
	float mClearColor[4];

	ID3D11Device *mpDevice;
	ID3D11DeviceContext *mpDcontext;

	CCubo *mCube;
	CCuboP *mCubePhong;
	CCuboT *mCubeTexture;
	CPanel *mPanel;

	Pulgas arena;
	Pulgas pulgas[12];
	Pulgas pin;

	DXCamera *mCamera;
	float mx;
	float my;
	float angle;
	float mRotationAngle = 0.0f;
	float mCubeX = 0.0f;
	float jumpTime;
	float size;
	int windowWidth;
	int windowHeight;
};





