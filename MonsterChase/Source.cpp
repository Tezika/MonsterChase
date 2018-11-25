#include "game.h"
#include  "Engine-init.h"

using namespace MonsterChase;

int main()
{
	// insert code here...
	Engine::Initialize();
	Game::GetInstance().Initialize();
	while (!Game::GetInstance().ShouldEnd())
	{
		Game::GetInstance().Run();
	}
	Game::GetInstance().Stop();
	Engine::Destroy();
	_CrtDumpMemoryLeaks();
	system("pause");
}