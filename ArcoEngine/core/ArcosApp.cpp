#include "ArcosApp.h"
#include <string>
#include "../render/DXCore.h"
#include "../render/DXRenderToTexture.h"
#include "../scene/logic/SceneLoader.h"

#define KEY_DOWN(vk_code) ((GetAsyncKeyState(vk_code) & 0x8000) ? 1 : 0)
#define KEY_UP(vk_code) ((GetAsyncKeyState(vk_code) & 0x8000) ? 0 : 1)

ArcosApp pApp;

ArcosApp::ArcosApp(void)
    : WinApplication(), mpDXCore(nullptr)
{
    mTimer.setTockTime(0.050f);
}

ArcosApp::~ArcosApp(void)
{
    if (mpDXCore) { delete mpDXCore; mpDXCore = nullptr; }
}

void ArcosApp::logDebugMessage(const std::string& message)
{
    std::ofstream debugFile;
    debugFile.open("debug.log", std::ios_base::app); // Abre el archivo en modo append
    if (debugFile.is_open()) {
        debugFile << message << std::endl;
        debugFile.close();
    }
}

void ArcosApp::InitializeScene()
{
    CSceneLoader sceneLoader;
    sceneLoader.LoadXML("gameobjs.xml");
    mSceneMgr.Initialize(mpDXCore->Get3DDevice(), mpDXCore->GetDeviceContext());

    mMouse.Initialize(GetAppHwnd());
}

void ArcosApp::BuildObjects()
{

}

void ArcosApp::ReleaseObjects()
{

}

void ArcosApp::ProcessInput()
{
    int lx = mMouse.GETX();
    int ly = mMouse.GETY();

    if (KEY_DOWN(VK_RIGHT)) {
        numeros.push_back(8);
    }
    if (KEY_DOWN(VK_LEFT)) {
        numeros.push_back(9);
    }
    if (KEY_DOWN(VK_UP)) {
    }
    if (KEY_DOWN(VK_DOWN)) {
    }
    if (KEY_DOWN(VK_SPACE)) {
    }
    if (KEY_DOWN(0x57)) {
    }
    if (KEY_DOWN(0x41)) {
    }
    if (KEY_DOWN(0x53)) {
    }
    if (KEY_DOWN(0x44)) {
    }

    if (mMouse.IsLeftPressed()) {
       // logDebugMessage("Mouse left click detected at (" + std::to_string(lx) + ", " + std::to_string(ly) + ")");
        mSceneMgr.keyPress(lx, ly);
    }

    mSceneMgr.MouseActions(lx, ly);
}


bool ArcosApp::AppBegin()
{
    long w = 0, h = 0;
    GetWindowDims(w, h);

    mpDXCore = new DXCore();
    mpDXCore->Initialize(GetAppHwnd(), w, h);

    //mDXRenderToTexture = new DXRenderToTexture();
    //mDXRenderToTexture->Initialize(mpDXCore->Get3DDevice(), w, h);

    InitializeScene();
    BuildObjects();

    return true;
}

bool ArcosApp::AppUpdate()
{
    int lx = mMouse.GETX();
    int ly = mMouse.GETY();
    mTimer.Tick();
    mMouse.Poll();
    float elapsedTime = mTimer.GetTimeElapsed();
    if (mTimer.IsTock()) {
        if (mMouse.IsLeftPressed()) {
            mSceneMgr.keyPress(lx, ly);
        }
        ProcessInput();
    }

    // Actualizar las acciones del mouse para mover las pinzas con el mouse
    mSceneMgr.MouseActions(lx, ly);

    const float colorClear[4] = { 0.1961f, 0.0f, 0.9f, 1.0f };
    mpDXCore->ClearColor(colorClear);

    mSceneMgr.update(elapsedTime);
    mSceneMgr.draw(elapsedTime);

    mpDXCore->Present();
    return true;
}


bool ArcosApp::AppEnd()
{
    mpDXCore->Close();
    return true;
}