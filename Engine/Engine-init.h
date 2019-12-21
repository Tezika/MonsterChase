#pragma once
#include <Windows.h>
namespace Engine
{
	bool Initialize( HINSTANCE i_hInstance, int i_nCmdShow, int i_wWidth, int i_wHeight, const char* i_pWindowName );
	void Destroy();
}