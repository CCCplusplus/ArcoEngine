#include "Mouse.h"

Mouse::Mouse()
{
}

Mouse::~Mouse()
{
	Shutdown();
}

void Mouse::Reset()
{
	mDI = nullptr;
	mMouse = nullptr;
	mMousePos.x = 0;
	mMousePos.y = 0;

	ResetMouse();
}

void Mouse::ResetMouse()
{
	memset(&mMouseState, 0, sizeof(mMouseState));
	mMousePosInitialized = false;
	memset(&mDOD, 0, sizeof(mDOD));
    mDODLenght = 0;
    mTimeLeftButtonLastRealeased = 0;
    mLeftButtonDoubleClicked = false;
}

bool Mouse::Initialize(HWND windHandle)
{
	mWindowHandle = windHandle;
	if (FAILED(CoCreateInstance(CLSID_DirectInput8, nullptr, CLSCTX_INPROC_SERVER, IID_IDirectInput8W, (void**)&mDI)))
		return false;
	if (FAILED(mDI->Initialize((HINSTANCE)GetModuleHandle(nullptr), DIRECTINPUT_VERSION)))
		return false;
	if (FAILED(mDI->CreateDevice(GUID_SysMouse, &mMouse, nullptr)))
		return false;
	SetExclusive(false);
    if (FAILED(mMouse->SetDataFormat(&c_dfDIMouse)))
        return false;

    DIPROPDWORD dipdw;
    dipdw.diph.dwSize = sizeof(DIPROPDWORD);
    dipdw.diph.dwHeaderSize = sizeof(DIPROPHEADER);
    dipdw.diph.dwObj = 0;
    dipdw.diph.dwHow = DIPH_DEVICE;
    dipdw.dwData = BUFFERSIZE;
    if (FAILED(mMouse->SetProperty(DIPROP_BUFFERSIZE, &dipdw.diph)))
        return false;
    
    return true;
}

void Mouse::Poll()
{
    POINT old_mouse_pos = mMousePos;
    if (!GetCursorPos(&mMousePos))
    {
        ResetMouse();
        return;
    }
    if (!mMousePosInitialized)
    {
        old_mouse_pos = mMousePos;
        mMousePosInitialized = true;
    }
    if (!ScreenToClient(mWindowHandle, &mMousePos))
    {
        ResetMouse();
        return;
    }
    if (FAILED(mMouse->GetDeviceState(sizeof(mMouseState), &mMouseState)))
    {
        mMouse->Acquire();

        if (FAILED(mMouse->GetDeviceState(sizeof(mMouseState), &mMouseState)))
        {
            ResetMouse();
            return;
        }
    }
    if (GetSystemMetrics(SM_REMOTESESSION))
    {
        mMouseState.lX = mMousePos.x - old_mouse_pos.x;
        mMouseState.lY = mMousePos.y - old_mouse_pos.y;
    }
    if (FAILED(mMouse->GetDeviceData(sizeof(DIDEVICEOBJECTDATA), mDOD, &mDODLenght, 0)))
    {
        mMouse->Acquire();

        if (FAILED(mMouse->GetDeviceData(sizeof(DIDEVICEOBJECTDATA), mDOD, &mDODLenght, 0)))
        {
            mTimeLeftButtonLastRealeased = 0;
            mLeftButtonDoubleClicked = false;
            return;
        }
    }
    for (DWORD d = 0; d < mDODLenght; d++)
    {
        if (mDOD[d].dwOfs == DIMOFS_BUTTON0)
        {
            if (mDOD[d].dwData & 0x80)
            {
                if (mDOD[d].dwTimeStamp - mTimeLeftButtonLastRealeased <= DCLICKTIME)
                {
                    mTimeLeftButtonLastRealeased = 0;
                    mLeftButtonDoubleClicked = true;
                }
            }
            else
                mTimeLeftButtonLastRealeased = mDOD[d].dwTimeStamp;
        }
    }
}

void Mouse::HideCursor()
{
    ::ShowCursor(false);
}

void Mouse::ShowCursor()
{
    ::ShowCursor(true);
}

void Mouse::SetExclusive(bool inExclusive)
{
    mMouse->SetCooperativeLevel(mWindowHandle, (inExclusive ? DISCL_EXCLUSIVE : DISCL_NONEXCLUSIVE) | DISCL_FOREGROUND);
}

void Mouse::Shutdown()
{
    if (mMouse)
    {
        mMouse->Unacquire();
        mMouse = nullptr;
    }

    mDI = nullptr;

    Reset();
}
