#pragma once
#include <wrl/client.h>

#define DIRECTINPUT_VERSION 0x0800
#include  <dinput.h>

class MouseD
{
public:
	MouseD();

	~MouseD();


	bool Initialize(HWND windHandle);

	void Poll();

	int GETX() const { return mMousePos.x; }
	int GETY() const { return mMousePos.y; }
	int GETDX() const { return mMouseState.lX; }
	int GETDY() const { return mMouseState.lY; }

	bool IsLeftPressed() const { return (mMouseState.rgbButtons[0] & 0x80) != 0; }
	bool IsRightPressed() const { return (mMouseState.rgbButtons[1] & 0x80) != 0; }
	bool IsMiddlePressed() const { return (mMouseState.rgbButtons[2] & 0x80) != 0; }

	bool IsLeftDoubleClicked() const { return mLeftButtonDoubleClicked; }

	void HideCursor();
	void ShowCursor();

	void SetExclusive(bool inExclusive = true);

private:

	void Reset();

	void ResetMouse();

	enum
	{
		BUFFERSIZE = 64,
		DCLICKTIME = 300
	};

	HWND mWindowHandle;

	Microsoft::WRL::ComPtr<IDirectInput8> mDI;
	Microsoft::WRL::ComPtr<IDirectInputDevice8> mMouse;

	DIMOUSESTATE mMouseState;
	bool mMousePosInitialized = false;
	POINT mMousePos;
	DIDEVICEOBJECTDATA mDOD[BUFFERSIZE];
	DWORD mDODLenght;
	int mTimeLeftButtonLastRealeased;
	bool mLeftButtonDoubleClicked;

	void Shutdown();
	
};