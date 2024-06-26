#pragma once

#include "winapplication.h"
#include "timer/Timer.h"
#include "../scene/SceneMgr.h"
#include "../MouseD.h"
#include <vector>
#include <fstream>


class DXCore;
class DXRenderToTexture;

class ArcosApp : public WinApplication
{
private:
    CTimer mTimer;
    DXCore* mpDXCore;
    //DXRenderToTexture* mDXRenderToTexture;

    CSceneMgr mSceneMgr;

private:
    virtual bool AppBegin();
    virtual bool AppUpdate();
    virtual bool AppEnd();

    void InitializeScene();
    void BuildObjects();
    void ReleaseObjects();
    void ProcessInput();

public:
    ArcosApp(void);
    virtual ~ArcosApp(void);

    void logDebugMessage(const std::string& message);

private:
    std::vector<int> numeros;
    MouseD mMouse;
};

