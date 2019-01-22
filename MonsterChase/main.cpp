#include <assert.h>
#include <stdio.h>
#include <stdint.h>
#include <Windows.h>

#if defined _DEBUG
#define _CRTDBG_MAP_ALLOC
#include <crtdbg.h>
#endif // _DEBUG

#include "game.h"
#include "Engine-init.h"

typedef MonsterChase::Game MCGame;
int WINAPI wWinMain( HINSTANCE i_hInstance, HINSTANCE i_hPrevInstance, LPWSTR i_lpCmdLine, int i_nCmdShow )
{
	Engine::Initialize();
	bool bSuccess = MCGame::GetInstance().Initialize( i_hInstance, i_nCmdShow );
	if ( bSuccess )
	{
		MCGame::GetInstance().Run();
		MCGame::GetInstance().Destroy();
	}
	Engine::Destroy();

#if defined _DEBUG
	_CrtDumpMemoryLeaks();
#endif // _DEBUG
	system( "pause" );
}