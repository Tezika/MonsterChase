#pragma once
#include <Windows.h>
namespace Engine
{
	bool Initialize( HINSTANCE i_hInstance, int i_nCmdShow, int i_wWidth, int i_wHeight );
	void Destroy();
}