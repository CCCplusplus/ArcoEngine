#include <d3d11.h>
#include "SceneMgr.h"
#include "model/Cubo.h"
#include "model/CuboP.h"
#include "model/CuboT.h"
#include "model/Panel.h"
#include "../render/DXCamera.h"
#include "../MouseD.h"
#define _USE_MATH_DEFINES
#include "math.h"
#include "cmath"

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
    , windowWidth(680)
    , windowHeight(680)
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

void CSceneMgr::keyPress(float lx, float ly)
{
    MouseActions(lx, ly); // Actualizamos las coordenadas del mouse

    // Verificamos si se hace clic en alguna pulga
    for (int i = 0; i < 12; ++i)
    {
        if (pulgas[i].alive)
        {
            float pulgaX = pulgas[i].getXPosition();
            float pulgaY = pulgas[i].getYPosition();
            float pulgaZ = pulgas[i].getZPosition();

            // Aquí, la lógica depende del tamaño y posición de la pulga.
            // Ajusta estas condiciones según la geometría exacta de tus pulgas.
            if (mx >= pulgaX - 0.6f && mx <= pulgaX + 0.6f &&
                my >= pulgaY - 0.6f && my <= pulgaY + 0.6f)
            {
                pulgas[i].Kill();
                break; // Opcional: si solo quieres eliminar una pulga por clic
            }
        }
    }
}


void CSceneMgr::MouseActions(float lx, float ly)
{
    
    mx = (lx / windowWidth) * 2.0f - 1.0f;
    my = 2.0f - (ly / windowHeight) * 2.0f;

    //pin.setPosition(-mx, my, pin.getZPosition());
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

    mx = 0.0;
    my = 0.0;

	arena.Initialize(device, dcontext, mCamera, L"mosaic.png", "data/arena.obj");
    pin.Initialize(device, dcontext, mCamera, L"Pinzas.png", "data/tweezers.obj");
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

    
    jumpTime += deltaTime;

    // Parámetros del salto
    const float jumpHeight = 0.5f;
    const float jumpFrequency = 2.0f;

    // Calculo del desplazamiento en y para las pulgas
    for (int i = 0; i < 12; ++i)
    {
        float jumpOffset = jumpHeight * fabs(sinf(jumpFrequency * jumpTime + i)); // Desplazamiento de salto basado en el tiempo y la posición de la pulga
        pulgas[i].setPosition(pulgas[i].getXPosition(), jumpOffset, pulgas[i].getZPosition()); // Asignar la nueva posición en Y a la pulga
    }

    float sizeMax = 1.5f;
    float sizeMin = 1.0f;
    const float sizeFrequency = 0.5f;

    size = sizeMin + (sizeMax - sizeMin) * 0.5f * (1.0f + sinf(sizeFrequency * jumpTime * 2.0f * M_PI));
}

void CSceneMgr::draw(float deltaTime)
{
    // Rotación de la arena
    arena.drawModel(0, 0, 0, 0, angle, 1.2);

    // Dibujar las pinzas en la nueva posición del mouse
    pin.drawModel(-mx, my, 2, 90, -90, 1);

    // Dibujo de las pulgas con su posición actualizada
    const float maxRadius = 0.5f; // Radio máximo del plato

    for (int i = 0; i < 12; ++i)
    {
        // Obtener la posición de la pulga
        float x = pulgas[i].getXPosition();
        float y = pulgas[i].getYPosition();
        float z = pulgas[i].getZPosition();

        // Si la pulga está tocando el plato (condición puede ajustarse según el tamaño de la pulga y el plato)
        if (y <= 0.01f)
        {
            // Mover la pulga en la dirección de la rotación del plato
            float movementSpeed = 0.1f; // Velocidad de movimiento, ajustar según sea necesario
            float deltaX = movementSpeed * cos(angle);
            float deltaZ = movementSpeed * sin(angle);

            float newX = x + deltaX;
            float newZ = z + deltaZ;

            // Verificar que la nueva posición no exceda el radio máximo del plato
            float distanceFromCenter = sqrt(newX * newX + newZ * newZ);
            if (distanceFromCenter <= maxRadius)
            {
                x = newX;
                z = newZ;
            }

            // Actualizar la posición de la pulga
            pulgas[i].setPosition(x, y, z);
        }
        
        pulgas[i].drawModel(x + (i * 0.045), y, z + (i * 0.045), 0, 0, 1);
    }
}