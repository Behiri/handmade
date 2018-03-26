#include <Windows.h>

LRESULT CALLBACK
MainWindowsCallback(HWND   Window,
	UINT   Message,
	WPARAM WParam,
	LPARAM LParam)
{

	LRESULT Result = 0;

	switch (Message)
	{
	case WM_CREATE:
	{
		OutputDebugStringA("WM_CREATE\n");
	} break;

	case WM_SIZE:
	{
		OutputDebugStringA("WM_SIZE\n");
	} break;

	case WM_DESTROY:
	{
		OutputDebugStringA("WM_DESTROY\n");
	} break;

	case WM_CLOSE:
	{
		OutputDebugStringA("WM_CLOSE\n");
	} break;

	case WM_ACTIVATEAPP:
	{
		OutputDebugStringA("WM_ACTIVATEAPP\n");
	} break;

	case WM_PAINT:
	{
  	  PAINTSTRUCT Paint;
      HDC DeviceContex =  BeginPaint(Window, &Paint);
	
      int Width = Paint.rcPaint.right - Paint.rcPaint.left;
      int Height = Paint.rcPaint.bottom - Paint.rcPaint.top;
      int x = Paint.rcPaint.top;
      int y = Paint.rcPaint.left;
      static DWORD Operation = WHITENESS;
      PatBlt(DeviceContex, x, y, Width, Height, Operation);
	  Operation = (Operation == WHITENESS) ? BLACKNESS : WHITENESS;

      EndPaint(Window, &Paint);
	} break;

	default:
	{
		OutputDebugStringA("WM_SIZE\n");
		Result = DefWindowProc(Window, Message, WParam, LParam);
	} break;
	}
	return(Result);
}

int CALLBACK
WinMain(HINSTANCE Instance,
	HINSTANCE PrevInstance,
	LPSTR     CommandLine,
	int       ShowCode)
{
	WNDCLASS WindowClass = {};

	// Todo(Behiri): Check to see if CS_OWNDC|CS_HREDRAW|CS_VREDRAW still matters
	WindowClass.style = CS_OWNDC | CS_HREDRAW | CS_VREDRAW;
	WindowClass.lpfnWndProc = MainWindowsCallback;
	WindowClass.hInstance = Instance;
	//WindowClass.hIcon = ;
	WindowClass.lpszClassName = "HandmadeHeroWindowClass";

	HWND WINAPI
		CreateWindowEx(
		);

	
	
	if (RegisterClass(&WindowClass))
	{
		HWND WindowHandle = ::CreateWindowEx(
			0,
			WindowClass.lpszClassName,
			"Handmade Hero",
			WS_OVERLAPPEDWINDOW | WS_VISIBLE,
			CW_USEDEFAULT,
			CW_USEDEFAULT,
			CW_USEDEFAULT,
			CW_USEDEFAULT,
			0,
			0,
			Instance,
			0);


		if (WindowHandle)
		{
			MSG Message;
			for (;;)
			{
				BOOL MessageResult = GetMessage(&Message, 0, 0, 0);
				if (MessageResult > 0)
				{
					TranslateMessage(&Message);
					DispatchMessage(&Message);
				}
				else
				{
					break;
				}
			}


		}
		else
		{
			//TODO(Behiri): Logging
		}

	}
	else
	{
		//TODO(Behiri): Logging
	}

	return 0;
}
