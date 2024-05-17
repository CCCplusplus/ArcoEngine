#include <d3d11.h>
#include "SceneMgr.h"
#include "model/Cubo.h"
#include "model/CuboP.h"
#include "model/CuboT.h"
#include "model/Panel.h"
#include "../render/DXCamera.h"

static float cblack[3] = { 0.0f, 0.0f, 0.0f };
static float cblue[3] = { 0.01176f, 0.01568f, 0.43529f };

CSceneMgr::CSceneMgr(void)
	: mpDevice(nullptr)
	, mpDcontext(nullptr)
	, mCamera(nullptr)
	, mCube(nullptr)
	, mCubePhong(nullptr)
	, mCubeTexture(nullptr)
	, mPanel(nullptr)
	, angle(0.f)
	, jumpTime(0.f)
{
}

CSceneMgr::~CSceneMgr(void)
{
	if (mCube) delete mCube;
	if (mCubePhong) delete mCubePhong;
	if (mCubeTexture) delete mCubeTexture;
	if (mPanel) delete mPanel;
}

void CSceneMgr::changeCamera(float x, float y, float z)
{
	mCamera->setCameraView(x, y, z);
}

void CSceneMgr::Initialize(
	ID3D11Device* device, ID3D11DeviceContext* dcontext)
{
	mpDevice = device;
	mpDcontext = dcontext;

	mCamera = new DXCamera();
	mCamera->setCameraView(1.f, 2.5f, 5.f);
	mCamera->setCameraProjection(MathUtil::Pi / 4.f, 1, 0.02f, 200.f);

	mPanel = new CPanel(device, dcontext);
	mPanel->Initialize(mCamera);
	mPanel->InsertModel();

	arena.Initialize(device, dcontext, mCamera, L"mosaic.png", "data/arena.obj");
	pulgas[0].Initialize(device, dcontext, mCamera, L"Pulga-Verde.png", "data/pulga.obj");
	pulgas[1].Initialize(device, dcontext, mCamera, L"Pulga-azul.png", "data/pulga.obj");
	pulgas[2].Initialize(device, dcontext, mCamera, L"Pulga-roja.png", "data/pulga.obj");
	pulgas[3].Initialize(device, dcontext, mCamera, L"Pulga-Naranja.png", "data/pulga.obj");
	pulgas[4].Initialize(device, dcontext, mCamera, L"Pulga-Verde.png", "data/pulga.obj");
	pulgas[5].Initialize(device, dcontext, mCamera, L"Pulga-azul.png", "data/pulga.obj");
	pulgas[6].Initialize(device, dcontext, mCamera, L"Pulga-roja.png", "data/pulga.obj");
	pulgas[7].Initialize(device, dcontext, mCamera, L"Pulga-Naranja.png", "data/pulga.obj");
	pulgas[8].Initialize(device, dcontext, mCamera, L"Pulga-Verde.png", "data/pulga.obj");
	pulgas[9].Initialize(device, dcontext, mCamera, L"Pulga-azul.png", "data/pulga.obj");
	pulgas[10].Initialize(device, dcontext, mCamera, L"Pulga-roja.png", "data/pulga.obj");
	pulgas[11].Initialize(device, dcontext, mCamera, L"Pulga-Naranja.png", "data/pulga.obj");
}

void CSceneMgr::update(float deltaTime)
{
	angle += deltaTime; // Para la rotación de la arena

	// Actualización del tiempo de salto
	jumpTime += deltaTime;

	// Parámetros del salto
	const float jumpHeight = 0.5f;
	const float jumpFrequency = 2.0f;

	// Calculo del desplazamiento en y para las pulgas
	for (int i = 0; i < 12; ++i)
	{
		float jumpOffset = jumpHeight * fabs(sinf(jumpFrequency * jumpTime + i)); // Desplazamiento de salto basado en el tiempo y la posición de la pulga
		pulgas[i].setPosition(0.0f, jumpOffset, 0.0f); // Asignar la nueva posición a la pulga
	}
}

void CSceneMgr::draw(float deltaTime)
{
	// Rotación de la arena
	arena.drawModel(0, 0, 0, 0, angle);

	// Dibujo de las pulgas con su posición actualizada
	pulgas[0].drawModel(0.1, pulgas[0].getYPosition(), 0, 0, 0);
	pulgas[1].drawModel(0.1, pulgas[1].getYPosition(), 0.5, 0, 0);
	pulgas[2].drawModel(-0.4, pulgas[2].getYPosition(), 0, 0, 0);
	pulgas[3].drawModel(0.2, pulgas[3].getYPosition(), 0.3, 0, 0);
	pulgas[4].drawModel(0.36, pulgas[4].getYPosition(), 0, 0, 0);
	pulgas[5].drawModel(0.3, pulgas[5].getYPosition(), 0.5, 0, 0);
	pulgas[6].drawModel(-0.6, pulgas[6].getYPosition(), 0, 0, 0);
	pulgas[7].drawModel(-0.1, pulgas[7].getYPosition(), 0.3, 0, 0);
	pulgas[8].drawModel(0.4, pulgas[8].getYPosition(), -0.4, 0, 0);
	pulgas[9].drawModel(0.2, pulgas[9].getYPosition(), 0.8, 0, 0);
	pulgas[10].drawModel(-.7, pulgas[10].getYPosition(), 0.4, 0, 0);
	pulgas[11].drawModel(-0.2, pulgas[11].getYPosition(), 0.45, 0, 0);
}