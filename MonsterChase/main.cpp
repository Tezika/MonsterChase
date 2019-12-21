#include <assert.h>
#include <stdio.h>
#include <stdint.h>
#include <Windows.h>

#if defined _DEBUG
#define _CRTDBG_MAP_ALLOC
#include <stdlib.h>
#include <crtdbg.h>
#endif // _DEBUG

#include "game.h"
#include "Engine-init.h"

typedef TPong::Game FinalGame;
int WINAPI wWinMain( HINSTANCE i_hInstance, HINSTANCE i_hPrevInstance, LPWSTR i_lpCmdLine, int i_nCmdShow )
{
	Engine::Initialize( i_hInstance, i_nCmdShow, 800, 600, "TPong" );
	bool bSuccess = FinalGame::GetInstance().Initialize();
	if (bSuccess)
	{
		FinalGame::GetInstance().Run();
		FinalGame::GetInstance().Destroy();
	}
	Engine::Destroy();
#if defined _DEBUG
	_CrtDumpMemoryLeaks();
#endif // _DEBUG
}